//
// Created by larr on 24. 5. 17.
//

#ifndef LARR_PLANNER_WRAPPER_H
#define LARR_PLANNER_WRAPPER_H

#include "larr_planner/type_manager/TypeManager.h"
#include <optional>

namespace larr_planner {

class Wrapper {
public:
  void SetRobotState(const RobotState &robot_state);
  void OnPlanningTimerCallback();
  std::optional<LinearSystemControlInput> GenerateControlInputFromPlanning(const double &time);

private:
};

} // namespace larr_planner

#endif // LARR_PLANNER_WRAPPER_H
