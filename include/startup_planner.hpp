#ifndef STARTUP_PLANNER_HPP
#define STARTUP_PLANNER_HPP

#include <string>
#include <vector>

struct ModuleSpec {
    std::string name;
    std::vector<std::string> prerequisites;
};

enum class PlanStatus {
    ready,
    duplicate_module,
    unknown_dependency,
    cycle
};

struct StartupPlan {
    PlanStatus status;
    std::vector<std::string> order;
};

StartupPlan make_startup_plan(const std::vector<ModuleSpec>& modules);

#endif
