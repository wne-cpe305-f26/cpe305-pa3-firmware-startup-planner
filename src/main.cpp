#include "startup_planner.hpp"

#include <iostream>
#include <string_view>
#include <vector>

namespace {

std::string_view status_name(PlanStatus status) {
    switch (status) {
        case PlanStatus::ready:
            return "ready";
        case PlanStatus::duplicate_module:
            return "duplicate module";
        case PlanStatus::unknown_dependency:
            return "unknown dependency";
        case PlanStatus::cycle:
            return "cycle";
    }
    return "unknown status";
}

}  // namespace

int main() {
    const std::vector<ModuleSpec> modules{
        {"telemetry", {"sensor", "logger"}},
        {"clock", {}},
        {"sensor", {"spi"}},
        {"gpio", {"clock"}},
        {"logger", {"gpio"}},
        {"spi", {"clock", "gpio"}}};

    const StartupPlan plan = make_startup_plan(modules);
    std::cout << "Status: " << status_name(plan.status) << '\n';
    if (plan.status == PlanStatus::ready) {
        std::cout << "Startup order:\n";
        for (const std::string& name : plan.order) {
            std::cout << "  " << name << '\n';
        }
    }
}
