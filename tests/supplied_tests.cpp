#include "startup_planner.hpp"

#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace {

void require(bool condition, std::string_view message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << '\n';
        std::exit(1);
    }
}

void require_error(const StartupPlan& plan,
                   PlanStatus expected,
                   std::string_view message) {
    require(plan.status == expected, message);
    require(plan.order.empty(), "error result has an empty order");
}

void test_empty_input() {
    const StartupPlan plan = make_startup_plan({});
    require(plan.status == PlanStatus::ready, "empty input is ready");
    require(plan.order.empty(), "empty input has an empty order");
}

void test_deterministic_branching_order() {
    const std::vector<ModuleSpec> modules{
        {"telemetry", {"sensor", "logger"}},
        {"clock", {}},
        {"sensor", {"spi"}},
        {"gpio", {"clock"}},
        {"logger", {"gpio"}},
        {"spi", {"gpio", "clock"}}};

    const StartupPlan plan = make_startup_plan(modules);
    const std::vector<std::string> expected{
        "clock", "gpio", "spi", "sensor", "logger", "telemetry"};

    require(plan.status == PlanStatus::ready, "branching graph is ready");
    require(plan.order == expected, "branching graph has deterministic order");
}

void test_duplicate_precedes_unknown_dependency() {
    const std::vector<ModuleSpec> modules{
        {"clock", {}},
        {"clock", {"missing"}}};

    require_error(make_startup_plan(modules),
                  PlanStatus::duplicate_module,
                  "duplicate validation occurs first");
}

void test_unknown_dependency() {
    const std::vector<ModuleSpec> modules{
        {"clock", {}},
        {"sensor", {"spi"}}};

    require_error(make_startup_plan(modules),
                  PlanStatus::unknown_dependency,
                  "unknown prerequisite is rejected");
}

void test_indirect_cycle() {
    const std::vector<ModuleSpec> modules{
        {"clock", {"sensor"}},
        {"gpio", {"clock"}},
        {"sensor", {"gpio"}}};

    require_error(make_startup_plan(modules),
                  PlanStatus::cycle,
                  "indirect dependency cycle is rejected");
}

}  // namespace

void run_supplied_tests() {
    test_empty_input();
    test_deterministic_branching_order();
    test_duplicate_precedes_unknown_dependency();
    test_unknown_dependency();
    test_indirect_cycle();
}
