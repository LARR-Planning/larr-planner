//
// Created by larr on 24. 5. 17.
//
#include "larr_planner_ros2/planning_server/planning_server.h"
using namespace larr_planner;

PlanningServer::PlanningServer(const rclcpp::NodeOptions &options_input)
    : Node("planning_server_node", options_input) {}