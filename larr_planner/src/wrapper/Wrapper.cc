//
// Created by larr on 24. 5. 17.
//
#include "larr_planner/wrapper/Wrapper.h"
void larr_planner::Wrapper::SetRobotState(const larr_planner::RobotState &robot_state) {}

void larr_planner::Wrapper::OnPlanningTimerCallback() {}

std::optional<larr_planner::LinearSystemControlInput>
larr_planner::Wrapper::GenerateControlInputFromPlanning(const double &time) {
  return std::optional<LinearSystemControlInput>();
}
