#include "rclcpp/rclcpp.hpp"
// #include "umv_msgs"
#include "umv_msgs/msg/local_ref_path.hpp"
#include "umv_msgs/msg/obstacles.hpp" // ~/Desktop/larr_project/umv_control/install/umv_msgs/include/umv_msgs/umv_msgs/msg
#include "umv_msgs/msg/acu_cmd.hpp"
#include "umv_msgs/msg/host_vehicle_filter.hpp"

#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/point_cloud2_iterator.hpp>

#include "yj_utils_project.cuh"
// #include "hello.cuh"

using namespace std;

#define GEAR_RATIO 4.0

const float steeringAngleMax = 32.0 / 180.0 * 3.141592;

const float handle_velocity_max = 200.0;
const float j_max = 5.0f;
const float j_min = -5.0f;

// cu file - cpp file ros linki
const int  N = 30;
const float dt = 0.1;
const float ds = 1.0;
const float ego_vehicle_R = 1.5;
const float veh_whlbase = 2.7/2.0;

float ego_v = 0;
float ego_x = 0;
float ego_s = 0;
float ego_y = 0;
float ego_yaw = 0; //-20/180 * 3.141592;

float pred_ego_y = 0;
float pred_ego_x = 0;
float pred_ego_ey = 0;
float pred_ego_eyaw = 0;
float pred_ego_yaw = 0;

// state
int ref_len = N;
float local_ref_xs[40] = {0,};
float local_ref_ss[40] = {0,};
float local_ref_ys[40] = {0,};
float local_ref_yaws[40] = {0,};
float local_ref_yaws_for_eyaws[40] = {0,};
float local_ref_curvs[40] = {0,};
int brake_flag = 0;
float ey = 0;
float eyaw = 0;

float *Actual_steers = new float[40-1];
float *Actual_accs = new float[40-1];
float *pre_Actual_steers = new float[40-1];
float *pre_Actual_accs = new float[40-1];

std::vector<float *> choosed_obs_traj_ss;
std::vector<float *> choosed_obs_traj_ds;
std::vector<float *> choosed_obs_traj_eys;
std::vector<float *> choosed_obs_traj_yaws;


int obs_cnt = 0;
// int pred_cnt = 3;
// float a_values[3] = {0, 0.5, -0.8};
int pred_cnt = 1;
float a_values[3] = {0};

float safe_bound = 1.5;

// not lane
// float *road_boundary_real, *road_boundary_car, *lane_mids, *lane_pos;
// float lane_width = 3.5;
// int lane_cnt = 1;
// float lane_mid = 0;

float moving_obstacle_R = 2.7;
float obs_L = 3.5;
float pre_a = 0.0f;
float pre_s = 0.0f;
float Vx_des = (20.0/3.6); // m/s

int road_info_flag = 0;
int frenet_ego_flag = 0;


float* pre_path_xs = new float[N-1];
float *pre_path_ys = new float[N-1];


float *Traj_xs = new float[N];
float *Traj_ys = new float[N];
float *Traj_vs = new float[N];
float *Traj_yaws = new float[N];


class MppiClass : public rclcpp::Node
{
public:
    MppiClass(): Node("Mppi_node")
    {
        ref_path_sub_ = this->create_subscription<umv_msgs::msg::LocalRefPath>("/local_ref_path", 10, std::bind(&MppiClass::ref_path_cb, this, std::placeholders::_1));
        host_filter_sub_ = this->create_subscription<umv_msgs::msg::HostVehicleFilter>("/host_vehicle_filter_msg", 10, std::bind(&MppiClass::host_filter_cb, this, std::placeholders::_1));

        virtual_target_sub_ = this->create_subscription<umv_msgs::msg::Obstacles>("/virtual_target", 10, std::bind(&MppiClass::virtual_target_cb, this, std::placeholders::_1));

        publisher_ = this->create_publisher<umv_msgs::msg::AcuCmd>("/acu_cmd", 10);  // publisher 
        publisher_rviz_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("/mppi_path", 10);  // rviz
        timer_ = this->create_wall_timer(50ms, std::bind(&MppiClass::timer_cb, this)); //timer
    }
  

private:
    void publish_point_cloud()
    {
        cout << endl << "MPPI PATH PUB START!" << endl;
        auto msg = sensor_msgs::msg::PointCloud2();
        msg.header.stamp = this->get_clock()->now();
        msg.header.frame_id = "map";
        msg.height = 1;
        msg.width = N;
        msg.is_dense = false;
        msg.is_bigendian = false;

        sensor_msgs::PointCloud2Modifier modifier(msg);
        modifier.setPointCloud2FieldsByString(2, "xyz", "rgb");
        modifier.resize(N);

        sensor_msgs::PointCloud2Iterator<float> iter_x(msg, "x");
        sensor_msgs::PointCloud2Iterator<float> iter_y(msg, "y");
        sensor_msgs::PointCloud2Iterator<float> iter_z(msg, "z");

        // float points[4][3] = {
        //     {1.0, 1.0, 1.0},
        //     {2.0, 2.0, 2.0},
        //     {3.0, 3.0, 3.0},
        //     {4.0, 4.0, 4.0}
        // };

        for (int i = 0; i < N; ++i, ++iter_x, ++iter_y, ++iter_z) {
            *iter_x = Traj_xs[i];
            *iter_y = Traj_ys[i];
            *iter_z = 0;
        }

        publisher_rviz_->publish(msg);
        cout << endl << "MPPI PATH PUB FINISH!" << endl;
    }


    void timer_cb()
    {   
        // RCLCPP_INFO(this->get_logger(), "SSSSSIIIIIIIIBBBBBBBBBBBBAAAAAAAAAAAAALLLLLLLLLLL");
        sssss_hello();
        // ego_v = 30/3.6;
        // pre_a = 1;
        // pre_s = 0;
        // 
        // feasibleTrajSamplingParallel(local_ref_ss, local_ref_yaws, local_ref_curvs, 
        //                 ref_len, ey, eyaw, ego_s, ego_v, ego_yaw, ego_x, ego_y,
        //                 pre_a, pre_s,
        //                 choosed_obs_traj_ss, choosed_obs_traj_eys, obs_cnt, pred_cnt, Actual_accs, Actual_steers, Vx_des);

        // 240822 modify
        float lane_width = 5.0f;
        int lane_cnt = 4;
        float *lane_pos = new float[lane_cnt];
        lane_pos[3] = - lane_width - lane_width/2; //4.0;
        lane_pos[2] = - lane_width/2; //4.0;
        lane_pos[1] =  lane_width/2;
        lane_pos[0] = lane_width/2 + lane_width;

        if (brake_flag == 1){
            Vx_des = 0;
            cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ brake @@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\n";
        }else{
            Vx_des = (20.0/3.6); 
            cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ go @@@@@@@@@@@@@@@@@@@@@@@@@@@ \n\n";
        }

        feasibleTrajSamplingParallel(local_ref_ss, local_ref_yaws, local_ref_curvs, 
                                ref_len, ey, eyaw, ego_s, ego_v, ego_yaw, ego_x, ego_y,
                                lane_pos, lane_cnt, lane_width, pre_a, pre_s,
                                choosed_obs_traj_ss, choosed_obs_traj_eys, obs_cnt, pred_cnt, Actual_accs, Actual_steers, Vx_des, pre_path_xs, 
                                pre_path_ys);


        if(isnan(Actual_steers[0]) || isnan(Actual_accs[0]) || (Actual_accs[0] * Actual_accs[1] * Actual_accs[2] * Actual_accs[3] == 0)){
            for(int i=0; i<N-1; i++){
                Actual_steers[i] = pre_Actual_steers[i];
                Actual_accs[i] = pre_Actual_accs[i];
            }
        }

        cout << endl << "############################## Actual Steers ###################################" << endl;
        for(int i=0; i<N-1; i++){
            cout << Actual_steers[i] * 180 / float(M_PI) << "deg, ";
            // traj_steers[i+1] = Actual_steers[i];
        }
        cout << endl;
        cout << endl;

        cout << endl << "############################## Actual accels ###################################" << endl;
        for(int i=0; i<N-1; i++){
            cout << Actual_accs[i] << "m/s^2, ";
            // traj_steers[i+1] = Actual_steers[i];
        }
        cout << endl;
        cout << endl;


        Traj_xs[0] = ego_x;
        Traj_ys[0] = ego_y;
        Traj_vs[0] = ego_v;
        Traj_yaws[0] = ego_yaw;
        for(int i=0; i<N-1; i++){
            float next_x = Traj_xs[i] + Traj_vs[i] * cos(Traj_yaws[i]) * dt;
            float next_y = Traj_ys[i] + Traj_vs[i] * sin(Traj_yaws[i]) * dt;
            float next_v = Traj_vs[i] + Actual_accs[i] * dt;
            float next_yaw = Traj_yaws[i] + Traj_vs[i] / veh_whlbase * tan(Actual_steers[i]) * dt;

            Traj_xs[i+1] = next_x;
            Traj_ys[i+1] = next_y;
            Traj_vs[i+1] = next_v;
            Traj_yaws[i+1] = next_yaw;
        }
        // cout << endl << "############################## Traj xs ###################################" << endl;
        // for(int i=0; i<N; i++){
        //     cout << Traj_xs[i] << ", ";
        //     // traj_steers[i+1] = Actual_steers[i];
        // }
        // cout << endl;
        // cout << endl << "############################## Traj ys ###################################" << endl;
        // for(int i=0; i<N; i++){
        //     cout << Traj_ys[i] << ", ";
        //     // traj_steers[i+1] = Actual_steers[i];
        // }
        // cout << endl;
        // cout << endl << "############################## Traj vs ###################################" << endl;
        // for(int i=0; i<N; i++){
        //     cout << Traj_vs[i] << ", ";
        //     // traj_steers[i+1] = Actual_steers[i];
        // }
        // cout << endl;
        publish_point_cloud();
        



        /////////////////////////////
        // ----- acu input --------//
        /////////////////////////////
        auto acu_cmd_msg = umv_msgs::msg::AcuCmd();

        float real_steer = pre_s * 0.0 + 1.0 * Actual_steers[0]; // soft filtering
        float real_acc = pre_a * 0.0 + 1.0 * Actual_accs[0];

        float period = 0.05; // 50ms
        if ((real_steer - pre_s)/period > handle_velocity_max/GEAR_RATIO/180.0 * 3.141592){
            real_steer = pre_s + handle_velocity_max/GEAR_RATIO/180.0 * 3.141592 * period;
        }else if((real_steer - pre_s)/period < -1.0 * handle_velocity_max/GEAR_RATIO/180 * 3.141592){
            real_steer = pre_s - handle_velocity_max/GEAR_RATIO/180.0 * 3.141592 * period;
        }

        // float period = 0.05;
        if ((real_acc - pre_a)/period > j_max){
            real_acc = pre_a + j_max * period;
        }else if((real_acc - pre_a)/period < j_min){
            real_acc = pre_a + j_min * period;
        }
        cout << "real_steer: " << real_steer << endl;
        cout << "real_acc: " << real_acc << endl;

        // real_steer = real_steer * 0.80 + 0.20 * pred_steer;
        real_steer =  real_steer * GEAR_RATIO * 180 / (3.141592);
        acu_cmd_msg.sas = double(real_steer);
        acu_cmd_msg.ax = double(real_acc);

        
        float pred_steer = real_steer / GEAR_RATIO / 180 * (3.141592);


        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        // back up /////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////
        for(int i=0; i<N-2; i++){
            pre_Actual_steers[i] = Actual_steers[i+1];
            pre_Actual_accs[i] = Actual_accs[i+1];
        }

        float eyaw_ = eyaw;
        float ey_ = ey;
        float ego_yaw_ = ego_yaw;

        ego_yaw = ego_yaw + ego_v * dt / veh_whlbase * tan(pre_s);
        if (ego_yaw > 3.141592)
            ego_yaw = ego_yaw - 2*3.141592;
        else if (ego_yaw < -3.141592)
            ego_yaw = ego_yaw + 2*3.141592;


        eyaw = ego_yaw - local_ref_yaws[0];
        if (eyaw > 3.141592)
            eyaw = eyaw - 2*3.141592;
        else if (eyaw < -3.141592)
            eyaw = eyaw + 2*3.141592;

        ey = ey + ego_v * dt * sin(eyaw_);
        ego_s = ego_s + ego_v * dt * cos(eyaw) / (1 - local_ref_curvs[0] * ey);
        ego_v = ego_v + pre_a * dt;


        pre_s = pred_steer;
        cout << "######################################";
        cout << "pres: " << pre_s;
        cout << "######################################";
        pre_a = real_acc;



        if (ego_v < 0){
            pre_a = 0.0;
        }


        /////////////
        // publish //
        /////////////
        publisher_->publish(acu_cmd_msg);
        RCLCPP_INFO(this->get_logger(), "Published acu_cmd data: ax=%f, sas=%f", acu_cmd_msg.ax, acu_cmd_msg.sas);
    }


    // void car_state_cb(const umv_msgs::msg::LocalRefPath::SharedPtr state_msg)
    // {
    //     ego_x = float(msg.pose.pose.position.x);
    //     ego_y = float(msg.pose.pose.position.x);
    //     ego_yaw = float(msg.pose.pose.position.x);
    // }
    
    void ref_path_cb(const umv_msgs::msg::LocalRefPath::SharedPtr local_ref_path_msg)
    {
        RCLCPP_INFO(this->get_logger(), "ref path fuck ");

        auto last_received_local_msg = local_ref_path_msg;  // 마지막으로 받은 메시지 저장
        brake_flag = last_received_local_msg -> brake_flag;
        // cout << "????" << last_received_local_msg -> brake_flag << \n;

        for(int i=0; i<ref_len; i++){
            local_ref_xs[i] = last_received_local_msg->local_ref_xs[i];
            local_ref_ys[i] = last_received_local_msg->local_ref_ys[i];
            local_ref_yaws[i] = last_received_local_msg->local_ref_yaws[i];
            local_ref_curvs[i] = last_received_local_msg->local_ref_curvs[i];
            // local_ref_yaws_for_eyaws[i] = last_received_local_msg.local_ref_yaws_for_eyaws[i];
            local_ref_ss[i] = last_received_local_msg->local_ref_ss[i];
            // RCLCPP_INFO(this->get_logger(), "local_ref_xs: %lf elements", local_ref_xs[i]);
            // RCLCPP_INFO(this->get_logger(), "local_ref_ys: %lf elements", local_ref_ys[i]);
        }

        ego_s = last_received_local_msg->ego_s;
        ey = last_received_local_msg->ey;
        eyaw = last_received_local_msg->eyaw;
        
        ego_x = last_received_local_msg->ego_x;
        ego_y = last_received_local_msg->ego_y;
        ego_yaw = last_received_local_msg->ego_yaw;

        // RCLCPP_INFO(this->get_logger(), "Received local_ref_path data:");
        // RCLCPP_INFO(this->get_logger(), "local_ref_ss: %zu elements", last_received_local_msg->local_ref_ss.size());
        // RCLCPP_INFO(this->get_logger(), "local_ref_yaws: %zu elements", last_received_local_msg->local_ref_yaws.size());
        // RCLCPP_INFO(this->get_logger(), "local_ref_curvs: %zu elements", last_received_local_msg->local_ref_curvs.size());
        // RCLCPP_INFO(this->get_logger(), "ey: %f", last_received_local_msg->ey);
        // RCLCPP_INFO(this->get_logger(), "eyaw: %f", last_received_local_msg->eyaw);
        // RCLCPP_INFO(this->get_logger(), "ego_s: %f", last_received_local_msg->ego_s);
        // check_and_publish();
    }
   

    void host_filter_cb(const umv_msgs::msg::HostVehicleFilter::SharedPtr host_vehicle_filter_msg)
    {
        auto last_received_filter_msg = host_vehicle_filter_msg;  // 마지막으로 받은 메시지 저장

        ego_v = last_received_filter_msg->vx; // m/s
        // pre_a = last_received_filter_msg.ax;

        RCLCPP_INFO(this->get_logger(), "Received host_vehicle_filter_msg data:");
        RCLCPP_INFO(this->get_logger(), "vx: %f", last_received_filter_msg->vx);
        RCLCPP_INFO(this->get_logger(), "yawrate: %f", last_received_filter_msg->yawrate);
        RCLCPP_INFO(this->get_logger(), "as: %f", last_received_filter_msg->ax);
        RCLCPP_INFO(this->get_logger(), "sas: %f", last_received_filter_msg->sas);
        // check_and_publish();
    }


    // obstacle check
    void virtual_target_cb(const umv_msgs::msg::Obstacles::SharedPtr msg) 
    {
        cout << "###################### obstacle_callback ########################" << endl;
        
        // memory free
        if(obs_cnt != 0){
            choosed_obs_traj_ss.clear();
            choosed_obs_traj_ds.clear();
            choosed_obs_traj_eys.clear();
            choosed_obs_traj_yaws.clear();
        }

        obs_cnt = msg->obs_cnt;
        // try{
        //     ROS_INFO("obstacle count check ...");
        //     obs_cnt = msg.target_array[0].lane_id;
        //     ROS_INFO("obstacle count check OK");
        // }catch(int expn){
        //     ROS_WARN("############ NO OBSTACLE ############");
        //     return;
        // }

        cout << "#################### obs_cnt ####################";
        cout << obs_cnt << endl << endl << endl;

        int check = 0;
        int total_obs_cnt = obs_cnt;
        for(int i=0; i<total_obs_cnt; i++){
            cout << "obstacle predict!" << endl;
            float obs_x = msg->obs_xs[i]; // 절대 좌표
            float obs_y = msg->obs_ys[i]; // float(msg.target_array[i].pos_y); // 절대 좌표
            float obs_s = msg->obs_ss[i];
            float obs_ey = msg->obs_eys[i];
            // float obs_yaw = msg->obs_yaws[i]; // float(msg.target_array[i].yaw); // 절대 좌표

            cout << "obstacle_position: " << obs_x << " " << obs_y << '\n';

            if ((ego_x - obs_x)*(ego_x - obs_x) + (ego_y - obs_y)*(ego_y - obs_y) >= 1600){
                obs_cnt = obs_cnt - 1;
                continue;
            }

            for(int kk=0; kk<pred_cnt; kk++){
                float ax = a_values[kk];

                float *obs_xs = new float[N];
                float *obs_ys = new float[N];
                float *obs_ss = new float[N];
                float *obs_eys = new float[N];
                // float *obs_yaws = new float[N];

                obs_xs[0] = obs_x;
                obs_ys[0] = obs_y;
                obs_ss[0] = obs_s;
                obs_eys[0] = obs_ey;
                // obs_yaws[0] = obs_yaw;
                
                for(int j=1; j<N; j++){
                    obs_xs[j] = obs_xs[j-1];
                    obs_ys[j] = obs_ys[j-1];
                    obs_ss[j] = obs_ss[j-1];
                    obs_eys[j] = obs_eys[j-1];
                    // obs_yaws[j] = obs_yaws[j-1];

                    // cout << obs_xs[j] << ' ';
                }
                cout << endl;

                // for(int j=0; j<N; j++){
                //     cout << obs_ys[j] << ' ';
                // }
                cout << endl;
                cout << endl;

                choosed_obs_traj_ss.push_back(obs_ss);
                // choosed_obs_traj_ds.push_back(obs_ys);
                choosed_obs_traj_eys.push_back(obs_eys);
                // choosed_obs_traj_yaws.push_back(obs_yaws);
            }
        }
    }


    // // obstacle check
    // void obstacle_callback(const umv_msgs::msg::obstacle msg) {
    //     cout << "obstacle_callback" << endl;

    //     // memory free
    //     if(obs_cnt != 0){
    //         ROS_INFO("clear start");
    //         choosed_obs_traj_ss.clear();
    //         choosed_obs_traj_ds.clear();
    //         choosed_obs_traj_eys.clear();
    //         choosed_obs_traj_yaws.clear();
    //         ROS_INFO("obstacle predict clear");
    //     }

    //     ROS_INFO("obstacle count check ...");
    //     obs_cnt = msg.obs_cnt;
    //     ROS_INFO("obstacle count check OK");
    //     // try{
    //     //     ROS_INFO("obstacle count check ...");
    //     //     obs_cnt = msg.target_array[0].lane_id;
    //     //     ROS_INFO("obstacle count check OK");
    //     // }catch(int expn){
    //     //     ROS_WARN("############ NO OBSTACLE ############");
    //     //     return;
    //     // }

    //     ROS_WARN("#################### obs_cnt ####################");
    //     cout << obs_cnt << endl << endl << endl;

    //     int check = 0;
    //     int total_obs_cnt = obs_cnt;
    //     for(int i=0; i<total_obs_cnt; i++){
    //         cout << "obstacle predict!" << endl;
    //         float obs_x = msg.obs_xs[i]; // 절대 좌표
    //         float obs_y = msg.obs_ys[i]; // float(msg.target_array[i].pos_y); // 절대 좌표
    //         float obs_s = msg.obs_ss[i];
    //         float obs_ey = msg.obs_eys[i];
    //         float obs_yaw = msg.obs_yaws[i]; // float(msg.target_array[i].yaw); // 절대 좌표

    //         if ((ego_x - obs_x)*(ego_x - obs_x) + (ego_y - obs_y)*(ego_y - obs_y) >= 1600){
    //             obs_cnt = obs_cnt - 1;
    //             continue;
    //         }

    //         for(int kk=0; kk<pred_cnt; kk++){
    //             float ax = a_values[kk];

    //             float *obs_xs = new float[N];
    //             float *obs_ys = new float[N];
    //             float *obs_ss = new float[N];
    //             float *obs_eys = new float[N];
    //             float *obs_yaws = new float[N];

    //             obs_xs[0] = obs_x;
    //             obs_ys[0] = obs_y;
    //             obs_ss[0] = obs_s;
    //             obs_eys[0] = obs_ey;
    //             obs_yaws[0] = obs_yaw;
                
    //             for(int j=1; j<N; j++){
    //                 obs_xs[j] = obs_xs[j-1];
    //                 obs_ys[j] = obs_ys[j-1];
    //                 obs_ss[j] = obs_ss[j-1];
    //                 obs_eys[j] = obs_eys[j-1];
    //                 obs_yaws[j] = obs_yaws[j-1];

    //                 // cout << obs_xs[j] << ' ';
    //             }
    //             cout << endl;

    //             // for(int j=0; j<N; j++){
    //             //     cout << obs_ys[j] << ' ';
    //             // }
    //             cout << endl;
    //             cout << endl;

    //             choosed_obs_traj_ss.push_back(obs_ss);
    //             // choosed_obs_traj_ds.push_back(obs_ys);
    //             choosed_obs_traj_eys.push_back(obs_eys);
    //             // choosed_obs_traj_yaws.push_back(obs_yaws);
    //         }
    //     }
    // }

    rclcpp::Subscription<umv_msgs::msg::LocalRefPath>::SharedPtr ref_path_sub_;
    rclcpp::Subscription<umv_msgs::msg::HostVehicleFilter>::SharedPtr host_filter_sub_;

    rclcpp::Subscription<umv_msgs::msg::Obstacles>::SharedPtr virtual_target_sub_;

    rclcpp::Publisher<umv_msgs::msg::AcuCmd>::SharedPtr publisher_;  // 퍼블리셔 선언
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_rviz_;  // 퍼블리셔 선언

    rclcpp::TimerBase::SharedPtr timer_;
    umv_msgs::msg::LocalRefPath::SharedPtr last_received_local_msg;  // 마지막으로 받은 메시지 저장 변수
    umv_msgs::msg::HostVehicleFilter::SharedPtr last_received_filter_msg;  // 마지막으로 받은 메시지 저장 변수
    umv_msgs::msg::Obstacles::SharedPtr last_received_virtual_target_msg;  // 마지막으로 받은 메시지 저장 변수
};






int main(int argc, char *argv[])
{


    for(int i=0; i<N-1; i++){
        pre_path_xs[i] = 0.0f;
        pre_path_ys[i] = 0.0f;
    }

    ///////////////
    // MPPI work //
    ///////////////
    feasibleTrajSamplingParallelSetting();



    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MppiClass>());
    rclcpp::shutdown();



    /////////////////
    // memory free //
    /////////////////
    feasibleTrajSamplingParallelFree();

    free(Actual_steers);
    free(pre_Actual_steers);
    free(Actual_accs);
    free(pre_Actual_accs);

    for(int i=obs_cnt-1; i>=0; i--){
        free(choosed_obs_traj_ss[i]);
        free(choosed_obs_traj_ds[i]);
        free(choosed_obs_traj_eys[i]);
        free(choosed_obs_traj_yaws[i]);
    }

    free(Traj_xs);
    free(Traj_vs);
    free(Traj_ys);
    free(Traj_yaws);

    return 0;
}
