//
// Created by larr on 24. 5. 17.
//

#ifndef LARR_PLANNER_PLANNING_SERVER_H
#define LARR_PLANNER_PLANNING_SERVER_H

// #include <pcl/PCLPointCloud2.h>
// #include <pcl_conversions/pcl_conversions.h>
#include <rclcpp/rclcpp.hpp>
#include <larr_planner/wrapper/Wrapper.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

using RobotStateMsg = geometry_msgs::msg::PoseStamped;
using StateSubscriber = rclcpp::Subscription<RobotStateMsg>::SharedPtr;


namespace larr_planner {


class PlanningServer : public rclcpp::Node {
private:
  Wrapper *wrapper_ptr_;
  StateSubscriber state_subscriber_;

  void RobotStateCallback(const RobotStateMsg::ConstSharedPtr &msg);
  RobotState ConvertToRobotState(const RobotStateMsg &state_msg);


public:
  PlanningServer(const rclcpp::NodeOptions &options_input);
};

} // namespace larr_planner

#endif // LARR_PLANNER_PLANNING_SERVER_H
