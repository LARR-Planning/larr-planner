//
// Created by larr on 24. 5. 17.
//

#include "larr_planner_ros2/planning_server/planning_server.h"

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);

  auto options = rclcpp::NodeOptions().automatically_declare_parameters_from_overrides(true);
  auto planning_server = std::make_shared<larr_planner::PlanningServer>(options);

  rclcpp::executors::MultiThreadedExecutor executor;
  executor.add_node(planning_server);
  executor.spin();
  rclcpp::shutdown();

  return 0;
}