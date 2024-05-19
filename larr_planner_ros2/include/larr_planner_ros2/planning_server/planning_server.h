//
// Created by larr on 24. 5. 17.
//

#ifndef LARR_PLANNER_PLANNING_SERVER_H
#define LARR_PLANNER_PLANNING_SERVER_H

// #include <pcl/PCLPointCloud2.h>
// #include <pcl_conversions/pcl_conversions.h>
#include <cmath>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <larr_planner/wrapper/Wrapper.h>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

using RobotStateMsg = geometry_msgs::msg::PoseStamped;
using StateSubscriber = rclcpp::Subscription<RobotStateMsg>::SharedPtr;
using RosTimer = rclcpp::TimerBase::SharedPtr;
using TwsitControlInputMsg = geometry_msgs::msg::TwistStamped;
using TwistInputPublisher = rclcpp::Publisher<TwsitControlInputMsg>::SharedPtr;
namespace larr_planner {

class PlanningServer : public rclcpp::Node {
private:
  Wrapper *wrapper_ptr_;
  // Subscriber
  StateSubscriber state_subscriber_;

  // Subscriber callback
  void RobotStateCallback(const RobotStateMsg::ConstSharedPtr &msg);
  RobotState ConvertToRobotState(const RobotStateMsg &state_msg);

  // Publisher
  TwistInputPublisher twsit_input_publisher_;

  // Timer
  RosTimer planning_timer_;
  RosTimer control_timer_;
  // Timer Callback
  void PlanningTimerCallback();
  void ControlTimerCallback();

  TwsitControlInputMsg ConvertToTwsitMsg(const LinearSystemControlInput &control_input);

public:
  PlanningServer(const rclcpp::NodeOptions &options_input);
};

} // namespace larr_planner

#endif // LARR_PLANNER_PLANNING_SERVER_H
