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
      "~/state", rclcpp::QoS(1), std::bind(&PlanningServer::RobotStateCallback, this, std::placeholders::_1), options);

  using namespace std::chrono_literals;
  control_timer_ = this->create_wall_timer(20ms, std::bind(&PlanningServer::ControlTimerCallback, this));
  planning_timer_ = this->create_wall_timer(200ms, std::bind(&PlanningServer::PlanningTimerCallback, this));

  // Publish
  twsit_input_publisher_ = create_publisher<TwsitControlInputMsg>("twist_control_input", rclcpp::QoS(1));
}

void PlanningServer::RobotStateCallback(const geometry_msgs::msg::PoseStamped::ConstSharedPtr &msg) {
  wrapper_ptr_->SetRobotState(ConvertToRobotState(*msg));
}

RobotState PlanningServer::ConvertToRobotState(const RobotStateMsg &state_msg) {
  RobotState state;
  state.t_sec = state_msg.header.stamp.sec + state_msg.header.stamp.nanosec * 1E-9;
  state.pos.px = state_msg.pose.position.x;
  state.pos.py = state_msg.pose.position.y;
  state.pos.pz = state_msg.pose.position.z;

  state.orientation.qw = state_msg.pose.orientation.w;
  state.orientation.qx = state_msg.pose.orientation.x;
  state.orientation.qy = state_msg.pose.orientation.y;
  state.orientation.qz = state_msg.pose.orientation.z;

  return state;
}
void PlanningServer::PlanningTimerCallback() { wrapper_ptr_->OnPlanningTimerCallback(); }

void PlanningServer::ControlTimerCallback() {
  auto time = now();
  auto linear_control_input = wrapper_ptr_->GenerateControlInputFromPlanning(time.seconds());
  if (linear_control_input.has_value()) {
    twsit_input_publisher_->publish(ConvertToTwsitMsg(linear_control_input.value()));
  } else {
    LinearSystemControlInput linear_control_input_at_fail;
    linear_control_input_at_fail.t_sec = time.seconds();
    linear_control_input_at_fail.vx = 0.0, linear_control_input_at_fail.vy = 0.0, linear_control_input_at_fail.vz = 0.0;
    linear_control_input_at_fail.wx = 0.0, linear_control_input_at_fail.wy = 0.0, linear_control_input_at_fail.wz = 0.0;
    twsit_input_publisher_->publish(ConvertToTwsitMsg(linear_control_input_at_fail));
  }
}

TwsitControlInputMsg PlanningServer::ConvertToTwsitMsg(const LinearSystemControlInput &control_input) {
  TwsitControlInputMsg msg;
  control_input.t_sec;
  msg.header.frame_id = "map";
  msg.header.stamp.sec = floor(control_input.t_sec);
  msg.header.stamp.nanosec = floor(1E9 * (control_input.t_sec - msg.header.stamp.sec));
  msg.twist.linear.x = control_input.vx, msg.twist.linear.y = control_input.vy, msg.twist.linear.z = control_input.vz;
  msg.twist.angular.x = control_input.wx, msg.twist.angular.y = control_input.wy,
  msg.twist.angular.z = control_input.wz;
  return msg;
}
