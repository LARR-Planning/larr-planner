#ifndef __MPPI__
#define __MPPI__

#include <vector>

// extern const double M_PI;
// extern const int sampling_cnt;
// extern const int N;
// extern const float dt;
// extern const float jmin;
// extern const float jmax;
// extern const float veh_whlbase;
// extern const float umin;
// extern const float umax;
// extern const float steeringAngleMax; // 40 / 180 * pi
// extern const float ego_vehicle_R;
// extern const float HARD_CST;
// extern const int BLOCKSIZE_X;

void sssss_hello();

void feasibleTrajSamplingParallelSetting();

void feasibleTrajSamplingParallelFree();

// void feasibleTrajSamplingParallel(float *ref_ss, float *ref_yaws, float *curvs, 
//                                     int ref_len, float ey, float eyaw, float ego_s, float ego_v, float yaw, float ego_x, float ego_y,
//                                     float pre_a, float pre_s,
//                                     const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_eys, 
//                                     int obs_cnt, int pred_cnt, float *Actual_accs, float *Actual_steers, float Vx_des);

void feasibleTrajSamplingParallel(float *ref_ss, float *ref_yaws, float *curvs, 
                                    int ref_len, float ey, float eyaw, float ego_s, float ego_v, float yaw, float ego_x, float ego_y,
                                    float *lane_pos, int lane_cnt, float lane_width, float pre_a, float pre_s,
                                    const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_eys, 
                                    int obs_cnt, int pred_cnt, float *Actual_accs, float *Actual_steers, float Vx_des, float *pre_path_x, float *pre_path_y);

#endif