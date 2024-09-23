#ifndef __MPPI__
#define __MPPI__

#include <vector>
#endif


void sssss_hello();

void feasibleTrajSamplingParallelSetting();

void feasibleTrajSamplingParallelFree();


void feasibleTrajSamplingParallel(float *ref_ss, float *ref_yaws, float *curvs, 
                                    int ref_len, float ey, float eyaw, float ego_s, float ego_v, float yaw, float ego_x, float ego_y,
                                    float pre_a, float pre_s,
                                    const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_eys, 
                                    int obs_cnt, int pred_cnt, float *Actual_accs, float *Actual_steers, float Vx_des);
