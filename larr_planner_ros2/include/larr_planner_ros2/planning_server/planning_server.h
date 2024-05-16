//
// Created by larr on 24. 5. 17.
//

#ifndef LARR_PLANNER_PLANNING_SERVER_H
#define LARR_PLANNER_PLANNING_SERVER_H

// #include <pcl/PCLPointCloud2.h>
// #include <pcl_conversions/pcl_conversions.h>
#include <rclcpp/rclcpp.hpp>

namespace larr_planner {

class PlanningServer : public rclcpp::Node {

private:
public:
  PlanningServer(const rclcpp::NodeOptions &options_input);
};

} // namespace larr_planner

#endif // LARR_PLANNER_PLANNING_SERVER_H
