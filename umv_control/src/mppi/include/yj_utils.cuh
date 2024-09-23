#ifndef __MPPI__
#define __MPPI__

#include <vector>

extern const double M_PI;
extern const int sampling_cnt;
extern const int N;
extern const float dt;
extern const float jmin;
extern const float jmax;
extern const float veh_whlbase;
extern const float umin;
extern const float umax;
extern const float steeringAngleMax; // 40 / 180 * pi
extern const float ego_vehicle_R;
extern const float HARD_CST;
extern const int BLOCKSIZE_X;

void getCostParallel(const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_ds,
                                const std::vector<float *> &choosed_obs_traj_vs, const std::vector<float *> &choosed_obs_traj_yaws, int obs_cnt, int pred_cnt,
                                float obs_L, float moving_obs_R, float* lane_pos, int lane_cnt, float Vx_des, float* road_boundary_real, float* road_boundary_car,
                                float *cuda_ego_xs, float *cuda_ego_ys, float *cuda_ego_vs, float *cuda_ego_yaws, float *cuda_As, float *cuda_Ss, float *cuda_next_Ss, 
                                float *pre_path_x, float *pre_path_y, float* cuda_sm_ego_xs, float *cuda_sm_ego_ys,
                                float target_d, float *cuda_T);


void feasibleTrajSamplingParallelSetting(float x, float y, float v, float yaw, float pre_a);

void feasibleTrajSamplingParallelFree();

void feasibleTrajSamplingParallel(float x, float y, float v, float yaw, float Vx_des, float *lane_mids, float *lane_pos, int lane_cnt, float pre_a, float pre_s, float* pre_path_x, float *pre_path_y,
                                    float* road_boundary_real, float* road_boundary_car, const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_ds,
                                    const std::vector<float *> &choosed_obs_traj_vs, const std::vector<float *> &choosed_obs_traj_yaws, int obs_cnt, int pred_cnt,
                                    float* Actual_as, float *Actual_steers);

#endif