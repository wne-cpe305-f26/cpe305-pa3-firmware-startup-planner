#include "startup_planner.hpp"

StartupPlan make_startup_plan(const std::vector<ModuleSpec>& modules) {
    // TODO: Validate the specification, build an ordered directed graph,
    // detect cycles with three-state DFS, and reverse finish order.
    static_cast<void>(modules);
    return {PlanStatus::ready, {}};
}
