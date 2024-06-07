#include "rclcpp/rclcpp.hpp"
#include "umv_msgs/msg/local_ref_path.hpp"
#include "umv_msgs/msg/acu_cmd.hpp"
#include "umv_msgs/msg/host_vehicle_filter.hpp"

class MppiClass : public rclcpp::Node
{
public:
    MppiClass()
        : Node("Mppi_node")
    {
        ref_path_sub_ = this->create_subscription<umv_msgs::msg::LocalRefPath>("/local_ref_path", 10, std::bind(&MppiClass::ref_path_cb, this, std::placeholders::_1));
        host_filter_sub_ = this->create_subscription<umv_msgs::msg::HostVehicleFilter>("/host_vehicle_filter_msg", 10, std::bind(&MppiClass::host_filter_cb, this, std::placeholders::_1));

        publisher_ = this->create_publisher<umv_msgs::msg::AcuCmd>("/acu_cmd", 10);  // publisher
    }
  
private:
    void publish_acu_cmd() const
    {
        // acu_cmd msg
        auto acu_cmd_msg = umv_msgs::msg::AcuCmd();
        acu_cmd_msg.ax = calculate_ax(last_received_local_msg);  // ex
        acu_cmd_msg.sas = calculate_sas(last_received_local_msg);  // ex

        publisher_->publish(acu_cmd_msg);
        RCLCPP_INFO(this->get_logger(), "Published acu_cmd data: ax=%f, sas=%f", acu_cmd_msg.ax, acu_cmd_msg.sas);
    }

 
    void ref_path_cb(const umv_msgs::msg::LocalRefPath::SharedPtr local_ref_path_msg)
    {
        last_received_local_msg = local_ref_path_msg;  // 마지막으로 받은 메시지 저장

        RCLCPP_INFO(this->get_logger(), "Received local_ref_path data:");
        // RCLCPP_INFO(this->get_logger(), "local_ref_xs: %zu elements", last_received_local_msg->local_ref_xs.size());
        // RCLCPP_INFO(this->get_logger(), "local_ref_ys: %zu elements", last_received_local_msg->local_ref_ys.size());
        // RCLCPP_INFO(this->get_logger(), "local_ref_ss: %zu elements", last_received_local_msg->local_ref_ss.size());
        // RCLCPP_INFO(this->get_logger(), "local_ref_yaws: %zu elements", last_received_local_msg->local_ref_yaws.size());
        // RCLCPP_INFO(this->get_logger(), "local_ref_curvs: %zu elements", last_received_local_msg->local_ref_curvs.size());
        // RCLCPP_INFO(this->get_logger(), "ey: %f", last_received_local_msg->ey);
        // RCLCPP_INFO(this->get_logger(), "eyaw: %f", last_received_local_msg->eyaw);
        // RCLCPP_INFO(this->get_logger(), "ego_s: %f", last_received_local_msg->ego_s);
        check_and_publish();
    }
   
    void host_filter_cb(const umv_msgs::msg::HostVehicleFilter::SharedPtr host_vehicle_filter_msg)
    {
        last_received_filter_msg = host_vehicle_filter_msg;  // 마지막으로 받은 메시지 저장

        RCLCPP_INFO(this->get_logger(), "Received host_vehicle_filter_msg data:");
        // RCLCPP_INFO(this->get_logger(), "vx: %f", last_received_filter_msg->vx);
        // RCLCPP_INFO(this->get_logger(), "yawrate: %f", last_received_filter_msg->yawrate);
        // RCLCPP_INFO(this->get_logger(), "as: %f", last_received_filter_msg->ax);
        // RCLCPP_INFO(this->get_logger(), "sas: %f", last_received_filter_msg->sas);
        check_and_publish();
    }

    void check_and_publish()
    {
        if (last_received_local_msg && last_received_filter_msg)
        {
            publish_acu_cmd();
            // 메시지를 퍼블리시한 후, 다음 번 퍼블리시를 위해 수신 메시지를 초기화합니다.
            last_received_local_msg.reset();
            last_received_filter_msg.reset();
        }
    }


    double calculate_ax(const umv_msgs::msg::LocalRefPath::SharedPtr msg) const
    {   
        //need to change
        double ax = msg->ey * 0.1;  
        return ax;
        //return 0.1;
    }

    double calculate_sas(const umv_msgs::msg::LocalRefPath::SharedPtr msg) const
    {
        //need to change
        double sas = msg->eyaw * 15.0;  
        return sas;
        //return 0.1;
    }

    rclcpp::Subscription<umv_msgs::msg::LocalRefPath>::SharedPtr ref_path_sub_;
    rclcpp::Subscription<umv_msgs::msg::HostVehicleFilter>::SharedPtr host_filter_sub_;

    rclcpp::Publisher<umv_msgs::msg::AcuCmd>::SharedPtr publisher_;  // 퍼블리셔 선언
    umv_msgs::msg::LocalRefPath::SharedPtr last_received_local_msg;  // 마지막으로 받은 메시지 저장 변수
    umv_msgs::msg::HostVehicleFilter::SharedPtr last_received_filter_msg;  // 마지막으로 받은 메시지 저장 변수

};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MppiClass>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
