//
// Created by larr on 24. 5. 17.
//
#include "larr_planner_ros2/planning_server/planning_server.h"
using namespace larr_planner;

PlanningServer::PlanningServer(const rclcpp::NodeOptions &options_input) : Node("planning_server_node", options_input) {
  rclcpp::SubscriptionOptions options;
  // Subscribe Robot State {POSITION, ORIENTATION}
  options.callback_group = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
  state_subscriber_ = create_subscription<RobotStateMsg>(
      "~/state", rclcpp::QoS(1), std::bind(&PlanningServer::RobotStateCallback,this, std::placeholders::_1),options);
}

void PlanningServer::RobotStateCallback(const geometry_msgs::msg::PoseStamped::ConstSharedPtr &msg) {
  wrapper_ptr_-> SetRobotState(ConvertToRobotState(*msg));
}

RobotState PlanningServer::ConvertToRobotState(const RobotStateMsg &state_msg) {
  RobotState state;
  state.t_sec = state_msg.header.stamp.sec + state_msg.header.stamp.nanosec*1E-9;
  state.pos.px = state_msg.pose.position.x;
  state.pos.py = state_msg.pose.position.y;
  state.pos.pz = state_msg.pose.position.z;

  state.orientation.qw = state_msg.pose.orientation.w;
  state.orientation.qx = state_msg.pose.orientation.x;
  state.orientation.qy = state_msg.pose.orientation.y;
  state.orientation.qz = state_msg.pose.orientation.z;

  return state;
}
