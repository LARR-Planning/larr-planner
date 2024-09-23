#include <cmath>
#include <algorithm>
#include <random>
#include <iostream>
#include <vector>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>
#include <curand.h>
#include <curand_kernel.h>
#include <cmath>
#include <algorithm>

#include <fstream>
using namespace std;


///////////////////////// test //////////////////////////////
__global__ void cuda_hello22222(){
    printf("Hello World from GPU!\n");
}

void sssss_hello(){
    cuda_hello22222<<<1,1>>>();
    cout << "asd" << "\n";
    cudaDeviceSynchronize();
}
////////////////////////////////////////////////////////////


const int sampling_cnt = 10000;
const int N = 5;

const int sampling_cnt_N0 = sampling_cnt * N;
const int sampling_cnt_N1 = sampling_cnt * (N-1);
const int sampling_cnt_N2 = sampling_cnt * (N-2);

const int BLOCKSIZE_X = 512; // 128

// const float eyaw_boundary = 12.0 / 180 * 3.141592; // 15
const float steeringAngleMax = 40.0 / 180 * 3.141592; // 40

const float a_max = 3.0f;
const float a_min = -6.0f;
const float j_max = 5.0f;
const float j_min = -5.0f;

const float handle_velocity_max = 200.0;
const float gear_ratio = 15.0;
const float ds = 1.0f;
const float dt = 0.1f;
float steer_interval = handle_velocity_max / gear_ratio / 180.0 * 3.141592 * dt; // 10
const float veh_whlbase = 2.7/2.0;
const float ego_vehicle_R = 1.5;
const float pi = 3.141592;
const float obs_L = 2.8/2;
const float moving_obstacle_R = 1.5;

float *d_instant_sampling_cnt_N1_0; //계속 재사용하는 쿠다 변수 

float *d_instant_sampling_cnt_N0_0; //계속 재사용하는 쿠다 변수 
float *d_instant_sampling_cnt_N0_1; //계속 재사용하는 쿠다 변수 
float *d_instant_sampling_cnt_N0_2; //계속 재사용하는 쿠다 변수 
// float *d_instant_sampling_cnt_N0_3; //계속 재사용하는 쿠다 변수 
// float *d_instant_sampling_cnt_N0_4; //계속 재사용하는 쿠다 변수 

int *d_ref_idxs;
float *d_reference_curvs, *d_reference_next_curvs, *d_reference_yaws, *d_reference_ss;


float *d_curvs, *d_yaw_refs, *d_next_curvs;
float *d_f_steer_mins, *d_f_steer_maxs;
float *d_eys, *d_eyaws, *d_yaws, *d_vs, *d_dss, *d_ss, *d_dvs, *d_vx_dess, *d_xs, *d_ys;
float *d_next_eys, *d_next_eyaws, *d_next_yaws, *d_next_vs, *d_next_ss, *d_next_dss, *d_next_xs, *d_next_ys;
float *d_traj_eys, *d_traj_eyaws, *d_traj_vs, *d_traj_dss, *d_traj_ss, *d_traj_yaws, *d_traj_dvs;
float *d_traj_xs, *d_traj_ys;
float *d_pre_steers, *d_pre_as;
float *d_steers, *d_Ss, *d_first_steers, *d_next_steers;
float *d_accs, *d_As, *d_first_accs, *d_next_accs;

float *d_Actual_steers, *d_Actual_as; 


float *means;  
float *d_means; // sampling_cnt
curandState *devStates; // sampling_cnt

float *d_longi_cost, *d_lat_cost; // sampling_cnt
float *d_A, *d_B, *d_reachable_yaw_min;
double *d_exp_cost;
double *d_double_total;
double *d_exp_cost_;
float *d_j_mins, *d_j_maxs;
float *d_total, *d_global_min; 

cudaStream_t stream;
// d_lat_C == d_C
float *d_FS, *d_C, *d_AC, *d_S, *d_SR, *d_V, *d_Ey, *d_Eyaw;


float *f_steer_mins, *f_steer_maxs;
float *b_steer_mins, *b_steer_maxs;
float *steer_mins, *steer_maxs;
float *eys, *eyaws, *xs, *ys, *yaws;
float *next_eys, *next_eyaws, *next_xs, *next_ys, *next_yaws;
float *traj_eys, *traj_eyaws, *traj_xs, *traj_ys, *traj_yaws;
float *pre_steers;
float *steers;


__global__ void cuda_insert_step(const float* A, float* ret, int step) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    ret[step] = A[0];
}

__global__ void cuda_double_sum_Kernel(const double* A, double* ret, int size) {
    __shared__ double temp[BLOCKSIZE_X];
    int tid = threadIdx.x;
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    // 각 스레드에서 배열 요소를 읽어와서 합 계산
    if (index < size) {
        if (!isnan(A[index]))
            temp[tid] = A[index];
        else
            temp[tid] = 0;
    } else {
        temp[tid] = 0;
    }

    __syncthreads();

    // 각 블록별 합 계산
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            temp[tid] += temp[tid + stride];
        }
        __syncthreads();
    }

    // 0번 쓰레드의 역할. 0번만 전역에 접근 가능!
    if (tid == 0) {
        ret[blockIdx.x] = temp[0];
    }
}


__global__ void cuda_sum_Kernel(const float* A, float* ret, int size) {
    __shared__ float temp[BLOCKSIZE_X];
    int tid = threadIdx.x;
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    // 각 스레드에서 배열 요소를 읽어와서 합 계산
    if (index < size) {
        if (!isnan(A[index]))
            temp[tid] = A[index];
        else
            temp[tid] = 0;
    } else {
        temp[tid] = 0;
    }

    __syncthreads();

    // 각 블록별 합 계산
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            temp[tid] += temp[tid + stride];
        }
        __syncthreads();
    }

    // 0번 쓰레드의 역할. 0번만 전역에 접근 가능!
    if (tid == 0) {
        ret[blockIdx.x] = temp[0];
    }
}

__global__ void cuda_all_substitue_Kernel(const float* A, float* ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if(idx < size){
        ret[idx] = A[idx];
    }
}

__global__ void cuda_double_all_substitue_Kernel(const double* A, double* ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if(idx < size){
        ret[idx] = A[idx];
    }
}


__global__ void cuda_sub_instant_Kernel(float* cost, float* global_min, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if(idx < size){
        cost[idx] = cost[idx] - global_min[0];
    }
}

__global__ void cuda_array_local_min_Kernel(const float* cost, float* global_min, int size, int range) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    // width: sampling_cnt
    // height: horizon_len

    int range_idx = idx/range;
    int check = idx%range;

    if(idx < size & check == 0){
        float local_min = 1e20;
        
        for(int i=0; i<range; i++){
            int cost_idx = range_idx * range + i;
            
            if (cost_idx >= size)
                break;

            if(!isnan(cost[cost_idx])){
                local_min = local_min < cost[cost_idx] ? local_min : cost[cost_idx];
            }
        }

        global_min[range_idx] = local_min;
    }
}

__global__ void cuda_exp_Kernel(float* cost, double *exp_cost, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    // width: sampling_cnt
    // height: horizon_len
    float lambda = 1;
    if(idx < size){
        if (cost[idx] >= 1e8){
            exp_cost[idx] = 0.0f;
        }
        else{
            exp_cost[idx] = double(exp(-1/lambda * double(cost[idx])));
        }

        // if (cost[idx] <= 0.1){
        //     exp_cost[idx] = (exp(-1/lambda * double(cost[idx])));
        // }else{
        //     exp_cost[idx] = 0.0f;
        // }
    }
}


// cuda_lat_cost_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_lat_T, d_Ey, d_Eyaw, d_S, d_SR, d_FS, d_V, d_A,
//     Eyc, Eyawc, Sc, SRc, FSc, Vc, Ac);
__global__ void cuda_lat_cost_Kernel(float *d_T, const float *d_Ey, const float *d_Eyaw, const float *d_S, const float *d_SR, 
const float *d_FS, const float *d_V, const float *d_A, float Eyc, float Eyawc, float Sc, float SRc, float FSc, float Vc, float Ac) {
    int i = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    // width: sampling_cnt
    // height: horizon_len
    
    if (i < sampling_cnt) {
        d_T[i] = Eyc * d_Ey[i] + Eyawc * d_Eyaw[i] + Sc * d_S[i] + SRc * d_SR[i] + FSc * d_FS[i] + Vc * d_V[i] + Ac * d_A[i];
        d_T[i] = abs(d_T[i]);
        if (d_T[i] <= 0){
            d_T[i] = 1e5;
        }
    }
}

__global__ void cuda_longi_cost_Kernel(float *d_T, const float *d_C, const float *d_V, const float *d_A, float Cc, float Vc, float Ac) {
    int i = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    // width: sampling_cnt
    // height: horizon_len
    
    if (i < sampling_cnt) {
        d_T[i] = Cc * d_C[i] + Vc * d_V[i] + Ac * d_A[i];
        d_T[i] = abs(d_T[i]);
        if (d_T[i] <= 0){
            d_T[i] = 1e5;
        }
    }
}

__global__ void cuda_sum_axis_Kernel(const float* A, float* ret, int width, int height) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width
    
    if (idx < width) {
        ret[idx] = 0.0f;

        for(int j=0; j<height; j++){
            ret[idx] += A[idx*height + j];
        }
    }
}



__global__ void cuda_plus_instant_Kernel(const float* A, float* ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if (idx < size) {
        ret[idx] = ret[idx] + A[idx];
    }
}


__global__ void cuda_sub_Kernel(const float* yaws, const float* dyaws, float* ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if (idx < size) {
        ret[idx] = yaws[idx] - dyaws[idx];
    }
}



__global__ void cuda_plus_Kernel(const float* yaws, const float* dyaws, float* ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if (idx < size) {
        ret[idx] = yaws[idx] + dyaws[idx];
    }
}


__global__ void cuda_clip_Kernel(const float min, const float max, float* ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    
    if (idx < size) {
        ret[idx] = ret[idx] > max ? max : ret[idx];
        ret[idx] = ret[idx] < min ? min : ret[idx];
    }
}

__global__ void cuda_square_Kernel(const float* As, float* cost, int size) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if(idx < size){
        cost[idx] = As[idx] * As[idx];
    }
}


__global__ void cuda_ratio_interp_Kernel(const float* ss_ref, const float* dis_ref, const float* info_ref, float *ret, 
                                        int horizon, int size, float distance_interval) {
    // ss_ref: d_ss, dis_ref: s_ref, info_ref: ref_curvs, ret: 
    // ERROR CHECK
    // horizon: dis_ref length
    // size: sampling_cnt
    int idx = blockIdx.x * blockDim.x + threadIdx.x; // width

    if (idx < size) {
        float cmp = 0.0f;
        int ret_idx = 0;   
        for(int j = 0; j < horizon; j++){
            cmp = (ss_ref[idx] - dis_ref[j]);
        
            if (cmp < 0){
                ret_idx = j;
                break;
            }
        }

        float info_ref_idx = info_ref[ret_idx];
        if (abs(info_ref[ret_idx]) <= 1e-6){
            info_ref_idx = 0;
        }

        float alpha = (dis_ref[ret_idx] - ss_ref[idx]);
        ret[idx] = float(distance_interval - alpha)/distance_interval * info_ref_idx + (alpha)/distance_interval * info_ref_idx; 
    }
}


__global__ void cuda_vx_des_Kernel(float* curvs, int size, float vx_des, float *vx_dess) {
    // ERROR CHECK
    // horizon: dis_ref length
    // size: sampling_cnt
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width

    if (idx < size) {
        float cmp_vx_des = sqrt(0.08 * 9.81 * 1.0 / (abs(curvs[idx]) + 1e-6)); 
        vx_dess[idx] = cmp_vx_des < vx_des ? cmp_vx_des : vx_des;
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
__global__ void carPotentialKernel(const float* obs_s, const float* obs_ey, 
                                   const float* ego_s, const float* ego_ey,
                                   const float obs_L, const float moving_obs_R, float* Ucar, int size, float ego_L, float flag) {
    // flag == 1 // lon, 0 // lat
    int idx = threadIdx.x + blockIdx.x * blockDim.x;  // Assuming 1D kernel launch
    float hard_cst = 2.3;
    float mid_cst = 2.7;

    if (idx < size) {
        // (ego_x, ego_y)
        // (obs_x, obs_y)

        Ucar[idx] = 0.0f;

        // 2d gaussian 이용해서 x은 크게, y은 작게 만들자
        float k_obs = 500 * flag + (1-flag) * 500;
        float d_var = 16 * flag + (1-flag) * 8;
        float d_front_var = 5 * flag + (1-flag) * 1.0;
        float ey_var = 1.2 * flag + (1-flag) * 1.6;
        float C_veh_upper = k_obs * 0.7 * flag + (1-flag) * 500;

        if (ego_s[idx] < obs_s[idx]){
            Ucar[idx] = k_obs * exp(-(ego_s[idx] - obs_s[idx]) * (ego_s[idx] - obs_s[idx]) /d_var /d_var 
                                        - (ego_ey[idx] - obs_ey[idx]) * (ego_ey[idx] - obs_ey[idx]) /ey_var /ey_var);
        }else{
            Ucar[idx] = k_obs * exp(-(ego_s[idx] - obs_s[idx]) * (ego_s[idx] - obs_s[idx]) /d_front_var /d_front_var 
                                        - (ego_ey[idx] - obs_ey[idx]) * (ego_ey[idx] - obs_ey[idx]) /ey_var /ey_var);
        }

        if (Ucar[idx] >  C_veh_upper){
            Ucar[idx] = C_veh_upper;
        }

        // if (abs(ego_ey[idx] - obs_ey[idx]) >= (1.4 * 2 + 0.4)){
        //     Ucar[idx] = 0;
        // }

        if (abs(ego_ey[idx] - obs_ey[idx]) <= (1.3*2 + 0.5)){
            if (abs(ego_s[idx] - obs_s[idx]) <= 4.0){
                Ucar[idx] = Ucar[idx] + 1e2; // 충돌
            }
        }
    }
}

__global__ void cuda_init_Kernel(float *ret, const float n, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    
    if (idx < size) {
        // ret[idx] = 0.0f;
        ret[idx] = n;
    }
}

__global__ void cuda_int_init_Kernel(int *ret, const int n, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    
    if (idx < size) {
        // ret[idx] = 0.0f;
        ret[idx] = n;
    }
}


__global__ void cuda_init_pos_Kernel(float *ret, float n, int step_idx, int width, int height) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    // width: sampling_cnt
    // height: horizon_len
    
    if (idx < width) {
        int ret_idx = idx * height + step_idx;

        ret[ret_idx] = n;
    }
}

__global__ void cuda_init_specific_pos_Kernel(float *ret, float n, int pos, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    // width: sampling_cnt
    // height: horizon_len
    
    if (idx < size) {
        ret[pos] = n;
    }
}

__global__ void cuda_substitute_Kernel(const float *A, float *ret, int step_idx, int width, int height) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    int ret_idx = idx * height + step_idx;
    
    if (idx < width) {
        ret[ret_idx] = A[idx];
    }
}

__global__ void cuda_check_Kernal(const float *A, float *ret, int step_idx, int width, int height) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x; // width idx
    int ret_idx = idx * height + step_idx;
    
    if (idx < width) {
        if (A[idx] <= 0){
            ret[ret_idx] = 0.0;
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
__global__ void cuda_means_Kernel(const float *A, const float *B, float *ret, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;

    if(idx < size){
        ret[idx] = (A[idx] + B[idx])/2;
    }
}

__global__ void curand_setup_kernel(curandState *state, unsigned long seed) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    curand_init(seed, idx, 0, &state[idx]);
}


__global__ void generate_normal(curandState *state, const float *mins, const float *maxs, const float* means, float *result, int size) {
    int idx = threadIdx.x + blockIdx.x * blockDim.x;
    curandState localState = state[idx];
    
    if(idx < size){
        float mean = means[idx]; // 평균
        float stddev = (maxs[idx] - mins[idx])/2.5  ; // 표준편차

        // float cmpstddev = (maxs[idx] - means[idx])/3;
        // float cmpstddev2 = (means[idx] - mins[idx])/3;
        // stddev = stddev < cmpstddev2 ? stddev: cmpstddev2;
        // stddev = stddev < cmpstddev ? stddev: cmpstddev;
        
        // curand_normal 함수를 사용하여 정규 분포를 따르는 난수 생성
        result[idx] = float(curand_normal(&localState) * stddev) + mean;

        result[idx] = float(floor(result[idx] * 10000)/10000.0);

        result[idx] = result[idx] < mins[idx] ? mins[idx] : result[idx];
        result[idx] = result[idx] > maxs[idx] ? maxs[idx] : result[idx];
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

__global__ void Forward_Kernel(int size, float *steer_mins, float *steer_maxs, float *steers, float delta_steer, float steering_angle_max){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < size) {
        float steer = steers[idx];

        float steer_min = steer - delta_steer;
        steer_min = steer_min < steering_angle_max ? steer_min : steering_angle_max;  
        steer_mins[idx] = steer_min < (-1 * steering_angle_max) ? (-1 * steering_angle_max) : steer_min; 

        float steer_max = steer + delta_steer;
        steer_max = steer_max < (-1 * steering_angle_max) ? (-1 * steering_angle_max) : steer_max;
        steer_maxs[idx] = steer_max < steering_angle_max ? steer_max : steering_angle_max; 
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// 240320 LRFS ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// __global__ void Next_Ey_Kernel(int size, float *eys, float *eyaws, float *next_eys, float curv, float distance_interval){
//     int idx = blockIdx.x * blockDim.x + threadIdx.x;

//     if (idx < size) {
//         next_eys[idx] = eys[idx] + distance_interval * (1-curv*eys[idx])*tan(eyaws[idx]);
//     }                                        
// }

__global__ void Lateral_spatialKernel(float *eys, float *eyaws, float* yaws, float *dss, float *vs, float *ss, float *xs, float *ys,
                                     float *next_eys, float *next_eyaws, float *next_ss, float *next_dss, float *next_vs, float *next_yaws, 
                                     float *next_xs, float *next_ys, 
                                     float *curvs, int size, float ego_L, float time_interval, float *accs, float *steers, float *yaw_ref) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < size) {
        float x = xs[idx];
        float y = ys[idx];
        float yaw = yaws[idx];
        float ey = eys[idx];
        float eyaw = eyaws[idx];
        float v = vs[idx];
        float distance_interval = dss[idx];
        float steer = steers[idx];
        float acc = accs[idx];
        float next_yaw_ref = yaw_ref[idx];
        float curv = curvs[idx];
        float ssss = ss[idx];

        if (idx == 0){
            acc = 0;
            accs[idx] = 0;
        }
        // else if(idx == 1){
        //     acc = -1 * v/time_interval;
        //     accs[idx ] = acc;
        // }


        float next_v = v + acc * time_interval;
        if (next_v <= 0){
            next_v = 0;
            accs[idx] = -1 * v/time_interval; // make v = 0's acceleration
        }

        float next_ey = ey + distance_interval * (1-curv*ey)*tan(eyaw);
        // float next_eyaw = eyaw + distance_interval * (1-curv*ey) / (ego_L * cos(eyaw)) * tan(steer) - distance_interval * curv;
        float next_yaw = yaw + distance_interval/ego_L * tan(steer); 

        if (next_yaw < -3.141592){
            next_yaw = next_yaw + 2 * 3.141592;
        }else if(next_yaw > 3.141592){
            next_yaw = next_yaw - 2 * 3.141592;
        }

        float next_eyaw = next_yaw - next_yaw_ref;
        if (next_eyaw < -3.141592){
            next_eyaw = next_eyaw + 2 * 3.141592;
        }else if(next_eyaw > 3.141592){
            next_eyaw = next_eyaw - 2 * 3.141592;
        }

        // next_eyaw = atan2(next_ey - ey, distance_interval);

        next_xs[idx] = x + cos(yaw) * distance_interval;
        next_ys[idx] = y + sin(yaw) * distance_interval; 

        next_yaws[idx] = next_yaw;
        next_eyaws[idx] = next_eyaw;
        next_eys[idx] = next_ey;
        next_vs[idx] = next_v;
        next_dss[idx] = next_v * time_interval * cos(next_eyaw) / (1 - curv * next_ey);
        next_ss[idx] = ssss + next_dss[idx];
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__global__ void mppi_step_Kernel(float *Ss, double *exp_costs, float *Actual_steers, double *total, int step_idx, int size, int horizon_len) {
    // Actual_as[step_idx]
    // Actual_steers[step_idx]
    
    __shared__ float temp_a[BLOCKSIZE_X];
    __shared__ float temp_s[BLOCKSIZE_X];

    int tid = threadIdx.x;
    int index = blockIdx.x * blockDim.x + threadIdx.x;

    // 각 스레드에서 배열 요소를 읽어와서 합 계산
    if (index < size) {
        if(!isnan(exp_costs[index]) & !isnan(Ss[index * horizon_len + step_idx]))
            temp_s[tid] = Ss[index * horizon_len + step_idx] * exp_costs[index] / float(total[0]);
        else
            temp_s[tid] = 0;

    } else {
        temp_a[tid] = 0;
        temp_s[tid] = 0;
    }

    __syncthreads();

    // 각 블록별 합 계산
    for (int stride = blockDim.x / 2; stride > 0; stride >>= 1) {
        if (tid < stride) {
            temp_s[tid] += temp_s[tid + stride];
        }

        __syncthreads();
    }

    // 블록 내 합을 전역 메모리에 저장
    if (tid == 0) {
        Actual_steers[blockIdx.x] = temp_s[0];
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

__global__ void RoadBoundaryOutPotentialKernel(int size, float *Rs, float *cuda_ego_eys, float ey_min, float ey_max){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if(idx < size){
        Rs[idx] = 0.0f;

        float min_margin = 1.0; // 1.5
        float max_margin = 3;
        float Rs_bound = 1e2; // 1e3;

        if (cuda_ego_eys[idx] < ey_min){
            Rs[idx] = 1e2 * abs(cuda_ego_eys[idx] - ey_min) + Rs_bound;
        } else if(cuda_ego_eys[idx] > ey_max){
            Rs[idx] = 1e2 * abs(cuda_ego_eys[idx] - ey_max) + Rs_bound;
        }
    }
}



__global__ void onelanePotentialParallelKernel(float* d_ego_eys, float* d_Ulane, float d_lanes, float A_lane, float oy, float ego_L, int width, int height) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if(idx < (width * height)){
        // choose which thread using
        float ey = d_ego_eys[idx];
        //float ego_y_head = d_ego_y[idx] + ego_L * sin(d_ego_yaw[idx]);

        float lane = d_lanes;
        float U1 = A_lane * expf(-1 * powf((ey - lane), 2) / (2 * powf(oy, 2)));
        //float U2 = A_lane * expf(-1 * powf((ego_y_head - lane), 2) / (2 * powf(oy, 2)));
    
        d_Ulane[idx] = U1;// + U2;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void feasibleTrajSamplingParallelSetting(){
    cudaStreamCreate(&stream);

    cudaMalloc((void**)&d_reachable_yaw_min, sampling_cnt * sizeof(float));

    cudaMalloc((void**)&d_A, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_B, sampling_cnt * sizeof(float));
    //////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_pre_steers, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_pre_as, sampling_cnt * sizeof(float));

    cudaMalloc((void**)&d_first_steers, sampling_cnt * sizeof(float));    
    cudaMalloc((void**)&d_first_accs, sampling_cnt * sizeof(float));    
    //////////////////////////////////////////////////////////////////////
    // ss = new float[sampling_cnt];

    cudaMalloc((void**)&d_steers, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_accs, sampling_cnt * sizeof(float));
    pre_steers = new float[sampling_cnt];

    /////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_xs, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_ys, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_vs, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_vx_dess, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_dvs, sampling_cnt * sizeof(float));

    cudaMalloc((void**)&d_dss, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_ss, sampling_cnt * sizeof(float));
    
    cudaMalloc((void**)&d_yaws, sampling_cnt * sizeof(float));

    /////////////////////////////////////////////////////////////////////  
    means = new float[sampling_cnt];    
    cudaMalloc((void**)&d_means, sampling_cnt * sizeof(float));

    /////////////////////////////////////////////////////////////////////    
    cudaMalloc((void **)&devStates, sampling_cnt * sizeof(curandState));

    /////////////////////////////////////////////////////////////////////
    // d_ys, d_vs, d_yaws, d_next_ys, d_as, d_ss

    cudaMalloc((float **)&d_reference_curvs, 40 * sizeof(float));
    cudaMalloc((float **)&d_reference_next_curvs, 40 * sizeof(float));
    cudaMalloc((float **)&d_reference_yaws, 40 * sizeof(float));
    cudaMalloc((float **)&d_reference_ss, 40 * sizeof(float));


    cudaMalloc((void **)&d_eys, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_eyaws, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_curvs, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_curvs, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_ref_idxs, sampling_cnt * sizeof(int));
    cudaMalloc((void **)&d_yaw_refs, sampling_cnt * sizeof(float));

    cudaMalloc((void **)&d_next_xs, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_ys, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_vs, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_dss, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_ss, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_yaws, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_eys, sampling_cnt * sizeof(float));
    cudaMalloc((void **)&d_next_eyaws, sampling_cnt * sizeof(float));

    /////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_traj_xs, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_ys, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_eys, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_eyaws, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_vs, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_dss, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_ss, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_dvs, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_traj_yaws, sampling_cnt_N0 * sizeof(float));

    cudaMalloc((void**)&d_Ss, sampling_cnt_N1 * sizeof(float));
    cudaMalloc((void**)&d_As, sampling_cnt_N1 * sizeof(float));
    
    cudaMalloc((void**)&d_next_steers, sampling_cnt_N1 * sizeof(float));
    cudaMalloc((void**)&d_next_accs, sampling_cnt_N1 * sizeof(float));
    /////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////
    // cudaMalloc((void**)&d_longi_cost, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_lat_cost, sampling_cnt * sizeof(float));

    cudaMalloc((void**)&d_exp_cost, sampling_cnt * sizeof(double));
    
    cudaMalloc((void**)&d_exp_cost_, sampling_cnt * sizeof(double));
    
    cudaMalloc((void**)&d_double_total, (sampling_cnt) * sizeof(double));
    cudaMalloc((void**)&d_total, (sampling_cnt) * sizeof(float));

    cudaMalloc((void**)&d_global_min, (sampling_cnt) * sizeof(float));

    /////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_Actual_steers, (N-1) * sizeof(float));
    cudaMalloc((void**)&d_Actual_as, (N-1) * sizeof(float));
    /////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_f_steer_mins, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_f_steer_maxs, sampling_cnt * sizeof(float));
    /////////////////////////////////////////////////////////////////////

    
    /////////////////////////////////////////////////////////////////////////////
    // Longitudinal /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_j_mins, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_j_maxs, sampling_cnt * sizeof(float));

    int numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    float j_interval_min = j_min * dt;
    float j_interval_max = j_max * dt;
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_j_mins, j_interval_min, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_j_maxs, j_interval_max, sampling_cnt);

    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    /////////////////////////////////////////////////////////////////////
    // COST /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////

    cudaMalloc((void**)&d_C, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_V, sampling_cnt * sizeof(float));
    // cudaMalloc((void**)&d_A, sampling_cnt * sizeof(float));


    cudaMalloc((void**)&d_Ey, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_Eyaw, sampling_cnt * sizeof(float));

    cudaMalloc((void**)&d_S, sampling_cnt * sizeof(float));
    cudaMalloc((void**)&d_SR, sampling_cnt * sizeof(float));
    
    cudaMalloc((void**)&d_FS, sampling_cnt * sizeof(float));


    ////////////////////////////////////////////////////////////////////////
    // instant /////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////
    cudaMalloc((void**)&d_instant_sampling_cnt_N1_0, sampling_cnt_N1 * sizeof(float));

    cudaMalloc((void**)&d_instant_sampling_cnt_N0_0, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_instant_sampling_cnt_N0_1, sampling_cnt_N0 * sizeof(float));
    cudaMalloc((void**)&d_instant_sampling_cnt_N0_2, sampling_cnt_N0 * sizeof(float));
    // cudaMalloc((void**)&d_instant_sampling_cnt_N0_3, sampling_cnt_N0 * sizeof(float));
    // cudaMalloc((void**)&d_instant_sampling_cnt_N0_4, sampling_cnt_N0 * sizeof(float));
}


void feasibleTrajSamplingParallelFree(){
    cudaStreamDestroy(stream);
    cudaFree(d_reachable_yaw_min);
    ////////////////////////////////////////////////////////////////////////
    cudaFree(devStates);
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_means);
    ////////////////////////////////////////////////////////////////////////
    cudaFree(d_reference_curvs);
    cudaFree(d_reference_next_curvs);
    cudaFree(d_reference_yaws);
    cudaFree(d_reference_ss);

    cudaFree(d_eys);
    cudaFree(d_eyaws);

    cudaFree(d_xs);
    cudaFree(d_ys);
    cudaFree(d_vs);
    cudaFree(d_dvs);
    cudaFree(d_vx_dess);
    cudaFree(d_dss);
    cudaFree(d_ss);
    cudaFree(d_next_eyaws);
    cudaFree(d_next_eys);
    cudaFree(d_next_xs);
    cudaFree(d_next_ys);
    cudaFree(d_next_vs);
    cudaFree(d_next_dss);
    cudaFree(d_next_ss);
    cudaFree(d_next_yaws);

    cudaFree(d_steers);
    cudaFree(d_accs);
    // free(ss);

    free(pre_steers);

    cudaFree(d_yaws);

    // cout << "Free 5" << endl;

    free(means);
    //////////////////////////////////////////////////
    cudaFree(d_f_steer_mins);
    cudaFree(d_f_steer_maxs);

    cudaFree(d_traj_xs);
    cudaFree(d_traj_ys);
    cudaFree(d_traj_eys);
    cudaFree(d_traj_eyaws);

    cudaFree(d_traj_dss);
    cudaFree(d_traj_ss);
    cudaFree(d_traj_vs);
    cudaFree(d_traj_dvs);
    cudaFree(d_traj_yaws);

    cudaFree(d_Actual_steers);
    cudaFree(d_Actual_as);

    cudaFree(d_Ss);
    cudaFree(d_As);
    cudaFree(d_next_steers);
    cudaFree(d_next_accs);

    cudaFree(d_j_mins);
    cudaFree(d_j_maxs);
    cudaFree(d_yaw_refs);
    cudaFree(d_curvs);
    cudaFree(d_next_curvs);
    cudaFree(d_ref_idxs);

    cudaFree(d_C);
    cudaFree(d_Ey);
    cudaFree(d_Eyaw);
    cudaFree(d_S);
    cudaFree(d_SR);
    cudaFree(d_FS);

    cudaFree(d_instant_sampling_cnt_N0_0);
    cudaFree(d_instant_sampling_cnt_N0_1);
    cudaFree(d_instant_sampling_cnt_N0_2);
    // cudaFree(d_instant_sampling_cnt_N0_3);
    // cudaFree(d_instant_sampling_cnt_N0_4);

    cudaFree(d_first_steers);
    cudaFree(d_first_accs);
    // cudaFree(d_Rs);
    // cudaFree(d_obs_x);
    // cudaFree(d_obs_y);
    // cudaFree(d_obs_v);
    // cudaFree(d_obs_yaw);
    // cudaFree(d_Ucar);
    // cudaFree(d_Cs);
    // cudaFree(d_Ls);
    // cudaFree(d_cLs);
    // cudaFree(d_Vx_dess);
    // cudaFree(d_diff_Vs);
    // cudaFree(d_SM1);
    // cudaFree(d_SM2);
    // cudaFree(d_diff_path_x);
    // cudaFree(d_diff_path_y);
    // cudaFree(d_stacked_pre_path_x);
    // cudaFree(d_stacked_pre_path_y);
    // cudaFree(d_SMs);
    // cudaFree(d_target_ds);
    // cudaFree(d_diff_xs);
    // cudaFree(d_diff_ys);

    // cudaFree(d_costsN0);
    // cudaFree(d_costsN1);
    // cudaFree(d_longi_cost);
    cudaFree(d_lat_cost);
    cudaFree(d_exp_cost);
    cudaFree(d_exp_cost_);
    cudaFree(d_double_total);
}


void getCostParallel(const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_eys,
                                int obs_cnt, int pred_cnt, float obs_L, float moving_obs_R,
                                float *cuda_ego_ss, float *cuda_ego_eys, float *cuda_ego_eyaws, float *cuda_dvs,
                                float *cuda_As, float *cuda_next_As, float *cuda_first_as, float *pre_as, 
                                float *cuda_Ss, float * cuda_next_Ss, float *cuda_first_ss, float *pre_ss, float *cuda_longi_T, float *cuda_lat_T) {
    ////////////////
    // total_cost //
    ////////////////
    float ratio = 1;
    float Rc = 1.2 * 1; 
    float Lc = 1.0 * 1; // 1.8
    float Eyc = 00; // 10
    float Cc = 2.0f;
    float Eyawc = 1.2 * 1e3 * 1; // 3e3
    float Sc = 1e2 * 1; 
    float FSc = 2e3 * 1;
    float SRc = 2e3 * 1;
    float Ac = 0.10f;
    float Vc = 1.70f;

    // float *T = new float[sampling_cnt];

    int numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_longi_T, 0.0f, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_lat_T, 0.0f, sampling_cnt);

    //////////
    // TEST //
    //////////
    // float *traj_eys = new float[sampling_cnt_N0];
    // float *traj_eyaws = new float[sampling_cnt_N0];
    // float *traj_dvs = new float[sampling_cnt_N0];
    // float *traj_ss = new float[sampling_cnt_N0];

    // cudaMemcpy(traj_eys, cuda_ego_eys, sizeof(float)*sampling_cnt_N0, cudaMemcpyDeviceToHost);
    // cudaMemcpy(traj_eyaws, cuda_ego_eyaws, sizeof(float)*sampling_cnt_N0, cudaMemcpyDeviceToHost);
    // cudaMemcpy(traj_ss, cuda_ego_ss, sizeof(float)*sampling_cnt_N0, cudaMemcpyDeviceToHost);
    // cudaMemcpy(traj_dvs, cuda_dvs, sizeof(float)*sampling_cnt_N0, cudaMemcpyDeviceToHost);
    // cudaDeviceSynchronize();

    // cout << "############## traj eys ##############" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_eys[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;


    // cout << "############## traj eyaws ##############" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_eyaws[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;


    // cout << "############## traj ss ##############" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_ss[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;

    // cout << "############## traj dvs ##############" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_dvs[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;


    clock_t start_time = clock();
    clock_t end_time = clock() - start_time;

    //////////////////////////////
    // Start steering rate cost //
    //////////////////////////////
    start_time = clock();

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sub_instant_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_first_ss, pre_ss, sampling_cnt);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(pre_ss, d_FS, sampling_cnt);

    end_time = clock() - start_time;
    // cout << "start steering rate end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////
    // Car Potential //
    ///////////////////
    start_time = clock();

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_C, 0.0f, sampling_cnt);

    // cout << "############ obs cnt #############" << endl;
    // cout << "obs_cnt: " << obs_cnt << endl;
    
    for(int i=0; i<obs_cnt; i++){
        float *obs_ss = choosed_obs_traj_ss[i];
        // float *obs_ds = choosed_obs_traj_eys[i];
        // float *obs_yaws = choosed_obs_traj_ys[i];
        float *obs_eys = choosed_obs_traj_eys[i];

        float *d_obs_s = d_instant_sampling_cnt_N0_0;
        // float *d_obs_y = d_instant_sampling_cnt_N0_1;
        // float *d_obs_yaw = d_instant_sampling_cnt_N0_2;
        float *d_obs_ey = d_instant_sampling_cnt_N0_1;
        float *d_Ucar = d_instant_sampling_cnt_N0_2;

        for(int j=0; j<N; j++){
            numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
            cuda_init_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_obs_s, obs_ss[j], j, sampling_cnt, N);
            // cuda_init_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_obs_y, obs_ds[j], j, sampling_cnt, N);
            // cuda_init_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_obs_yaw, obs_yaws[j], j, sampling_cnt, N);
            cuda_init_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_obs_ey, obs_eys[j], j, sampling_cnt, N);
        }


        numBlocks = ceil((sampling_cnt_N0 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        // lateral
        carPotentialKernel<<<numBlocks, BLOCKSIZE_X>>>(d_obs_s, d_obs_ey,  cuda_ego_ss, cuda_ego_eys, obs_L, moving_obs_R, 
        d_Ucar, sampling_cnt_N0, veh_whlbase, 1.0);

        float *d_Cs = d_instant_sampling_cnt_N0_0;
        
        // lateral
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_Ucar, d_Cs, sampling_cnt, N);
        //lateral
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        cuda_plus_instant_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_Cs, d_C, sampling_cnt);
    }


    end_time = clock() - start_time;
    // cout << "car_potential end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // //////////////
    // // Yaw Cost //
    // //////////////
    // start_time = clock();

    // float *d_Ys = d_instant_sampling_cnt_N0_0;

    // numBlocks = ceil((sampling_cnt_N0 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_ego_yaws, d_Ys, sampling_cnt_N0);
    
    // numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_Ys, d_Y, sampling_cnt, N);

    

    // end_time = clock() - start_time;
    // // cout << "Yaw cost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    // ////////////
    // // Ey //
    // ////////////
    // float *d_stacked_ref_path_x = d_instant_sampling_cnt_N0_0;
    // float *d_stacked_ref_path_y = d_instant_sampling_cnt_N0_1;

    // numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // for(int i=0; i<(N); i++){
    //     cuda_init_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_stacked_ref_path_x, ref_xs[i], i, sampling_cnt, N);
    //     cuda_init_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_stacked_ref_path_y, ref_ys[i], i, sampling_cnt, N);
    // }

    // float *d_diff_path_x = d_instant_sampling_cnt_N0_2;
    // float *d_diff_path_y = d_instant_sampling_cnt_N0_3;

    // numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // cuda_sub_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_ego_xs, d_stacked_ref_path_x, d_diff_path_x, sampling_cnt_N0);
    // cuda_sub_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_ego_ys, d_stacked_ref_path_y, d_diff_path_y, sampling_cnt_N0);


    // float *d_SM1 = d_instant_sampling_cnt_N0_0;
    // float *d_SM2 = d_instant_sampling_cnt_N0_1;

    // numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_diff_path_x, d_SM1, sampling_cnt_N0);
    // cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_diff_path_y, d_SM2, sampling_cnt_N0);

    // float *d_SMs = d_instant_sampling_cnt_N0_2;

    // numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // cuda_plus_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_SM1, d_SM2, d_SMs, sampling_cnt_N0);

    // numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    // cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_SMs, d_Ey, sampling_cnt, N);

    // end_time = clock() - start_time;

    
    /////////////
    // Ey Cost //
    /////////////
    start_time = clock();

    float *d_Eys = d_instant_sampling_cnt_N0_0;

    numBlocks = ceil((sampling_cnt_N0 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_ego_eys, d_Eys, sampling_cnt_N0);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_Eys, d_Ey, sampling_cnt, N);

    end_time = clock() - start_time;


    ///////////////
    // Eyaw Cost //
    ///////////////
    start_time = clock();

    float *d_Eyaws = d_instant_sampling_cnt_N0_0;

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt_N0 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_ego_eyaws, d_Eyaws, sampling_cnt_N0);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_Eyaws, d_Eyaw, sampling_cnt, N);

    
    end_time = clock() - start_time;



    ///////////////////
    // Steering Cost //
    ///////////////////
    start_time = clock();

    float *d_SCs = d_instant_sampling_cnt_N1_0;

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_Ss, d_SCs, sampling_cnt_N1);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_SCs, d_S, sampling_cnt, N-1);

    end_time = clock() - start_time;
    // cout << "Steering cost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;



    ///////////////////////
    // Acceleration Cost //
    ///////////////////////
    start_time = clock();

    float *d_ACs = d_instant_sampling_cnt_N1_0;

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_As, d_ACs, sampling_cnt_N1);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ACs, d_A, sampling_cnt, N-1);
    
    end_time = clock() - start_time;
    // cout << "Steering cost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;



    //////////////
    // dvs Cost //
    //////////////
    start_time = clock();

    float *d_VCs = d_instant_sampling_cnt_N0_0;

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt_N0 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_dvs, d_VCs, sampling_cnt_N0);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_VCs, d_V, sampling_cnt, N);
    
    end_time = clock() - start_time;
    // cout << "Steering cost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;



    ///////////////////////
    // Memory over test //
    //////////////////////
    // float *ego_vs = new float[sampling_cnt_N0];
    // cudaMemcpy(ego_vs, cuda_ego_vs, sampling_cnt_N0 * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "####################### ego_v #########################" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_vs[i*N+j] - ego_vs[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
    // free(ego_vs);


    ////////////////////////
    // Steering Rate Cost //
    ////////////////////////
    start_time = clock();

    float *d_SRs = d_instant_sampling_cnt_N0_0;

    cudaDeviceSynchronize();
    numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sub_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_next_Ss, cuda_Ss, d_SR, sampling_cnt_N1);

    numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_square_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_SR, d_SRs, sampling_cnt_N1);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_sum_axis_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_SRs, d_SR, sampling_cnt, N-1);

    end_time = clock() - start_time;
    // cout << "steering rate cost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    ///////////////////////
    // Memory over test //
    //////////////////////
    // ego_vs = new float[sampling_cnt_N0];
    // cudaMemcpy(ego_vs, cuda_ego_vs, sampling_cnt_N0 * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "####################### ego_v #########################" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_vs[i*N+j] - ego_vs[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
    // free(ego_vs);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ego_vs = new float[sampling_cnt_N0];
    // cudaMemcpy(ego_vs, cuda_ego_vs, sampling_cnt_N0 * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "####################### ego_v #########################" << endl;
    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<N; j++){
    //         cout << traj_vs[i*N+j] - ego_vs[i * N + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
    // free(ego_vs);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    end_time = clock() - start_time;
    // cout << "velocity cost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;


    // Memory deallocation and data copying back to CPU goes here

    start_time = clock();
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cudaDeviceSynchronize();
    // lateral
    cuda_lat_cost_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_lat_T, d_Ey, d_Eyaw, d_S, d_SR, d_FS, d_V, d_A,
     Eyc, Eyawc, Sc, SRc, FSc, Vc, Ac);
    cudaDeviceSynchronize();
    // // longitudinal
    // cuda_longi_cost_Kernel<<<numBlocks, BLOCKSIZE_X>>>(cuda_longi_T, d_longi_C, d_V, d_A, longi_Cc, Vc, Ac);
    // cudaDeviceSynchronize();

    // ///////////////////////////
    // // GETCOSTPARALLEL PRINT //
    // ///////////////////////////
    // cout << "###################### total lateral cost ######################" << endl;
    // float *cost_test = new float[sampling_cnt];
    // cudaMemcpy(cost_test, cuda_lat_T, sizeof(float)*sampling_cnt, cudaMemcpyDeviceToHost);
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << cost_test[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(cost_test);

    // // cout << "###################### total longitudinal cost ######################" << endl;
    // // cost_test = new float[sampling_cnt];
    // // cudaMemcpy(cost_test, cuda_longi_T, sizeof(float)*sampling_cnt, cudaMemcpyDeviceToHost);
    // // for(int i=0; i<sampling_cnt; i++){
    // //     if(i%1000 == 0)
    // //         cout << cost_test[i] << ' ';
    // // }
    // // cout << endl;
    // // cout << endl;
    // // free(cost_test);

    // float *R = new float[sampling_cnt];
    // cudaMemcpy(R, d_R, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Road potential ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << R[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(R);

    // // float *C = new float[sampling_cnt];
    // // cudaMemcpy(C, d_C, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // // cout << "######################## Car potential ########################" << endl;
    // // for(int i=0; i<sampling_cnt; i++){
    // //     if(i%1000 == 0)
    // //         cout << C[i] << ' ';
    // // }
    // // cout << endl;
    // // cout << endl;
    // // free(C);
    
    // float *LC = new float[sampling_cnt];
    // cudaMemcpy(LC, d_L, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << " ######################## Lane potential ########################" << endl;
    // cout << "lane_cnt: " << lane_cnt << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << LC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(LC);

    // float *EYC = new float[sampling_cnt];
    // cudaMemcpy(EYC, d_Ey, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Ey Cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << EYC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(EYC);

    // float *EYAWC = new float[sampling_cnt];
    // cudaMemcpy(EYAWC, d_Eyaw, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Eyaw Cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << EYAWC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(EYAWC);

    // float *AC = new float[sampling_cnt];
    // cudaMemcpy(AC, d_AC, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Accel Cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << AC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(AC);

    // // float *YC = new float[sampling_cnt];
    // // cudaMemcpy(YC, d_Y, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // // cout << "######################## Yaw cost ########################" << endl;
    // // for(int i=0; i<sampling_cnt; i++){
    // //     if(i%1000 == 0)
    // //         cout << YC[i] << ' ';
    // // }
    // // cout << endl;
    // // cout << endl;
    // // free(YC);

    // float *SC = new float[sampling_cnt];
    // cudaMemcpy(SC, d_S, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Steering cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << SC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(SC);

    // float *SRC = new float[sampling_cnt];
    // cudaMemcpy(SRC, d_SR, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Steering rate cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << SRC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(SRC);

    // float *VC = new float[sampling_cnt];
    // cudaMemcpy(VC, d_V, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cudaDeviceSynchronize();
    // cout << "######################## Velocity cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << VC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(VC);

    // float *SMC = new float[sampling_cnt];
    // cudaMemcpy(SMC, d_SM, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Smooth cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << SMC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(SMC);

    // float *TLC = new float[sampling_cnt];
    // cudaMemcpy(TLC, d_TLC, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## Target Lane cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << TLC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(TLC);

    // float *GC = new float[sampling_cnt];
    // cudaMemcpy(GC, d_G, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## GO cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << GC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(GC);

    // float *FSC = new float[sampling_cnt];
    // cudaMemcpy(FSC, d_FS, sampling_cnt * sizeof(float), cudaMemcpyDeviceToHost);
    // cout << "######################## first steering rate cost ########################" << endl;
    // for(int i=0; i<sampling_cnt; i++){
    //     if(i%1000 == 0)
    //         cout << FSC[i] << ' ';
    // }
    // cout << endl;
    // cout << endl;
    // free(FSC);

    // cout << "calculate total cost: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // float *As_test2 = new float[sampling_cnt_N1];
    // cudaMemcpy(As_test2, cuda_As, sizeof(float)*sampling_cnt_N1, cudaMemcpyDeviceToHost);

    // for(int i=0; i<sampling_cnt/5000; i++){
    //     for(int j=0; j<(N-1); j++){
    //         cout << As_test[i * (N-1) + j] - As_test2[i*(N-1) + j] << ' ';
    //     }
    //     cout << endl;
    // }
    // cout << endl;
    // cout << endl;
    // free(As_test);
    // free(As_test2);
}


void feasibleTrajSamplingParallel(float *ref_ss, float *ref_yaws, float *curvs, 
                                    int ref_len, float ey, float eyaw, float ego_s, float ego_v, float yaw, float ego_x, float ego_y,
                                    float pre_a, float pre_s,
                                    const std::vector<float *> &choosed_obs_traj_ss, const std::vector<float *> &choosed_obs_traj_eys, 
                                    int obs_cnt, int pred_cnt, float *Actual_accs, float *Actual_steers, float Vx_des) {
    // for (int i = 0; i<N; i++){
    //     cout << "ref_s: " <<  ref_ss[i] << ' ';
    // }
    // cout << '\n';
    // cout << "ego_v: " << ego_v << endl;
    // cout << "pre_a: " << pre_a << endl;
    // cout << "pre_s: " << pre_s << endl;
    // cout << '\n';


    cout << endl << "---------------------------- FEASIBLESAMPLING TIME ----------------------------" << endl;
    clock_t feasible_sampling_time = clock();
    clock_t start_time, end_time;
    
    // cuda_init_specific_pos_Kernel(float *ret, float n, int pos, int size) 
    int numBlocks = ceil((1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    for (int i=0; i<ref_len; i++){
        cuda_init_specific_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_reference_curvs, curvs[i], i, 1);
        cuda_init_specific_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_reference_next_curvs, curvs[i], i, 1);
        cuda_init_specific_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_reference_yaws, ref_yaws[i], i, 1);
        cuda_init_specific_pos_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_reference_ss, ref_ss[i], i, 1);
    }
        

    float distance_interval = ego_v * dt * cos(eyaw) / (1 - curvs[0] * ey);
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_pre_as, pre_a, sampling_cnt); //longitudinal
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_pre_steers, pre_s, sampling_cnt); //lateral


    // step
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_xs, ego_x, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ys, ego_y, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_eys, ey, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_eyaws, eyaw, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_vs, ego_v, sampling_cnt); //velocity
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_dss, distance_interval, sampling_cnt); // distance_interval
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ss, ego_s, sampling_cnt); // longitudinal_distance

    cuda_int_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ref_idxs, 0, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_curvs, 0.0f, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_curvs, 0.0f, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_yaws, yaw, sampling_cnt);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_dvs, 0.0f, sampling_cnt);


    // Traj
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_xs, d_traj_xs, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ys, d_traj_ys, 0, sampling_cnt, N);
    
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_eys, d_traj_eys, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_eyaws, d_traj_eyaws, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_vs, d_traj_vs, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_dss, d_traj_dss, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ss, d_traj_ss, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_dvs, d_traj_dvs, 0, sampling_cnt, N);
    cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_yaws, d_traj_yaws, 0, sampling_cnt, N);

    // next control input
    numBlocks = ceil((sampling_cnt_N1 + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_accs, pre_a, sampling_cnt_N1);
    cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_steers, pre_s, sampling_cnt_N1);
    
    return;

    for(int kk=0; kk<(N-1); kk++){
    cudaDeviceSynchronize();
        start_time = clock();

        // //////////////////
        // // longitudinal //
        // //////////////////
        // float *sssssss = new float[sampling_cnt];
        // cudaMemcpy(sssssss, d_ss, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 

        // cout << "############## longitudinal distance ##############" << endl;
        // // cout << steer_interval << '\n\n';
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << sssssss[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;

        // free(sssssss);
        // // break;


        ////////////////////////
        // steer inverval set //
        ////////////////////////
        // steer_interval = 1.0 * 1.0 / 180 * 3.141592 + 3.0 * 1.0 / 180 * 3.141592  * 10 * prev_curv;


        // // /////////////////////
        // // // pre_steer check //
        // // /////////////////////
        // float *pre_ss = new float[sampling_cnt];
        // cudaDeviceSynchronize();
        // cudaMemcpy(pre_ss, d_pre_steers, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        // cout << "############## pre_ss ##############" << endl;
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << pre_ss[i] << ' ';
        // }

        // cout << endl;
        // cout << endl;

        float *pre_as = new float[sampling_cnt];
        cudaDeviceSynchronize();
        cudaMemcpy(pre_as, d_pre_as, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        cout << "############## pre_as ##############" << endl;
        for(int i=0; i<sampling_cnt/1000; i++){
            cout << pre_as[i] << ' ';
        }

        free(pre_as);
        cout << endl;
        cout << endl;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////
        // longitudinal //
        //////////////////
        numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        cuda_plus_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_pre_as, d_j_maxs, d_f_steer_maxs, sampling_cnt); // acc_max
        cuda_plus_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_pre_as, d_j_mins, d_f_steer_mins, sampling_cnt); // acc_min

        cuda_clip_Kernel<<<numBlocks, BLOCKSIZE_X>>>(a_min, a_max, d_f_steer_maxs, sampling_cnt);
        cuda_clip_Kernel<<<numBlocks, BLOCKSIZE_X>>>(a_min, a_max, d_f_steer_mins, sampling_cnt);

        float *a_mins = new float[sampling_cnt];
        float *a_maxs = new float[sampling_cnt];
        float *j_mins = new float[sampling_cnt];
        float *j_maxs = new float[sampling_cnt];
        cudaMemcpy(j_mins, d_j_mins, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        cudaMemcpy(j_maxs, d_j_maxs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        cudaMemcpy(a_mins, d_f_steer_mins, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        cudaMemcpy(a_maxs, d_f_steer_maxs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 

        cout << "############## j_min ##############" << endl;
        for(int i=0; i<sampling_cnt/1000; i++){
            cout << j_mins[i] << ' ';
        }
        cout << endl;
        cout << endl;


        cout << "############## j_max ##############" << endl;
        for(int i=0; i<sampling_cnt/1000; i++){
            cout << j_maxs[i] << ' ';
        }
        cout << endl;
        cout << endl;
        

        cout << "############## acc_min ##############" << endl;
        for(int i=0; i<sampling_cnt/1000; i++){
            cout << a_mins[i] << ' ';
        }
        cout << endl;
        cout << endl;


        cout << "############## acc_max ##############" << endl;
        for(int i=0; i<sampling_cnt/1000; i++){
            cout << a_maxs[i] << ' ';
        }
        cout << endl;
        cout << endl;
        free(a_mins);
        free(a_maxs);
        free(j_mins);
        free(j_maxs);


        ///////////////////////////
        // sampling acceleration //
        ///////////////////////////
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        cuda_means_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_f_steer_mins, d_f_steer_maxs, d_means, sampling_cnt);
    
        // cudaDeviceSynchronize();
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        curand_setup_kernel<<<numBlocks, BLOCKSIZE_X>>>(devStates, (unsigned long)clock());
        cudaDeviceSynchronize();

        // cudaDeviceSynchronize();
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        generate_normal<<<numBlocks, BLOCKSIZE_X>>>(devStates, d_f_steer_mins, d_f_steer_maxs, d_means, d_accs, sampling_cnt);
        cudaDeviceSynchronize();

        // float *as = new float[sampling_cnt];
        // cudaDeviceSynchronize();
        // cudaMemcpy(as, d_accs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        
        // cout << "############## sampled acc ##############" << endl;
        // // cout << steer_interval << '\n\n';
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << as[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;
        // cout << endl;
        // cout << endl;

        // free(as);


        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // feasibleSampling2stepCUDA /////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////
        // prev_curv //
        ///////////////
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        // cuda_ratio_interp_Kernel(const float* ss_ref, const float* dis_ref, const float* info_ref, float *ret, 
        //                                 int horizon, int size, float distance_interval)
        cuda_ratio_interp_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ss, d_reference_ss, d_reference_curvs, d_curvs, ref_len, sampling_cnt, ds); //이게 문제인듯 
        // cuda에 넘기는 값은 무조건 device 값.
        // cudaDeviceSynchronize();


        ///////////////
        // next_curv //
        ///////////////
        cuda_plus_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_ss, d_dss, d_next_ss, sampling_cnt);
        cuda_ratio_interp_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_ss, d_reference_ss, d_reference_next_curvs, d_next_curvs, pred_cnt, sampling_cnt, ds);

        //////////////////
        // prev_yaw_ref //
        //////////////////
        cuda_ratio_interp_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_ss, d_reference_ss, d_reference_yaws, d_yaw_refs, ref_len, sampling_cnt, ds);

        ////////////
        // Vx_des //
        ////////////
        cuda_vx_des_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_curvs, sampling_cnt, Vx_des, d_vx_dess);


        // float *curvssss = new float[sampling_cnt];
        // float *ref_yawsss = new float[sampling_cnt];
        // float *Vx_desss = new float[sampling_cnt];
        // cudaMemcpy(curvssss, d_curvs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        // cudaMemcpy(ref_yawsss, d_yaw_refs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        // cudaMemcpy(Vx_desss, d_vx_dess, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 


        // cout << "############## curvs ##############" << endl;
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << curvssss[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;


        // cout << "############## ref_yaws ##############" << endl;
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << ref_yawsss[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;


        // cout << "############## Vx_des ##############" << endl;
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << Vx_desss[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;

        // free(curvssss);
        // // free(ref_yawsss);
        // free(Vx_desss);
        // break;

        
        /////////////
        // lateral //
        /////////////
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        // Forward_Kernel(int size, float *steer_mins, float *steer_maxs, float *steers, float delta_steer, float steering_angle_max){
        Forward_Kernel<<<numBlocks, BLOCKSIZE_X>>>(sampling_cnt, d_f_steer_mins, d_f_steer_maxs, d_pre_steers, steer_interval, steeringAngleMax);


        /////////////////////////////
        // sampling steering angle //
        /////////////////////////////
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        cuda_means_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_f_steer_mins, d_f_steer_maxs, d_means, sampling_cnt);
    
        // cudaDeviceSynchronize();
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        curand_setup_kernel<<<numBlocks, BLOCKSIZE_X>>>(devStates, (unsigned int)clock());
        cudaDeviceSynchronize();

        // cudaDeviceSynchronize();
        numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        generate_normal<<<numBlocks, BLOCKSIZE_X>>>(devStates, d_f_steer_mins, d_f_steer_maxs, d_means, d_steers, sampling_cnt);
        cudaDeviceSynchronize();

        // float *ss = new float[sampling_cnt];
        // cudaDeviceSynchronize();
        // cudaMemcpy(ss, d_steers, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        
        // cout << "############## sampled steer ##############" << endl;
        // // cout << steer_interval << '\n\n';
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << ss[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;

        // free(ss);

        //////////
        // STEP //
        //////////
        numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        Lateral_spatialKernel<<<numBlocks, BLOCKSIZE_X>>>(d_eys, d_eyaws, d_yaws, d_dss, d_vs, d_ss, d_xs, d_ys,
                                                          d_next_eys, d_next_eyaws, d_next_ss, d_next_dss, d_next_vs, d_next_yaws, 
                                                          d_next_xs, d_next_ys,
                                                          d_curvs, sampling_cnt, veh_whlbase, dt, d_accs, d_steers, d_yaw_refs);
        
        cuda_sub_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_vx_dess, d_next_vs, d_dvs, sampling_cnt);

        // float *dvs = new float[sampling_cnt];
        // float *next_vs = new float[sampling_cnt];
        // float *vx_dess = new float[sampling_cnt];
        // cudaDeviceSynchronize();
        // cudaMemcpy(dvs, d_dvs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        // cudaMemcpy(next_vs, d_next_vs, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        // cudaMemcpy(vx_dess, d_vx_dess, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost); 
        
        // cout << "############## dvs ##############" << endl;
        // // cout << steer_interval << '\n\n';
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << dvs[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;

        // cout << "############## next_vs ##############" << endl;
        // // cout << steer_interval << '\n\n';
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << next_vs[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;

        // cout << "############## vx_dess ##############" << endl;
        // // cout << steer_interval << '\n\n';
        // for(int i=0; i<sampling_cnt/1000; i++){
        //     cout << vx_dess[i] << ' ';
        // }
        // cout << endl;
        // cout << endl;

        // free(dvs);
        // free(next_vs);
        // free(vx_dess);

        //////////
        // SAVE //
        //////////
        // cudaDeviceSynchronize();
        numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        
        // input
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_steers, d_Ss, kk, sampling_cnt, N-1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_accs, d_As, kk, sampling_cnt, N-1);

        // state update
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_xs, d_xs, 0, sampling_cnt, 1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_ys, d_ys, 0, sampling_cnt, 1);

        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_eys, d_eys, 0, sampling_cnt, 1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_eyaws, d_eyaws, 0, sampling_cnt, 1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_vs, d_vs, 0, sampling_cnt, 1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_dss, d_dss, 0, sampling_cnt, 1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_ss, d_ss, 0, sampling_cnt, 1);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_yaws, d_yaws, 0, sampling_cnt, 1);

        // pre_a, pre_s
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_steers, d_pre_steers, 0, sampling_cnt, 1);

        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_accs, d_pre_as, 0, sampling_cnt, 1);
        cuda_check_Kernal<<<numBlocks, BLOCKSIZE_X>>>(d_next_vs, d_pre_as, 0, sampling_cnt, 1);

        // traj_update
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_xs, d_traj_xs, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_ys, d_traj_ys, kk+1, sampling_cnt, N);

        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_eys, d_traj_eys, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_eyaws, d_traj_eyaws, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_vs, d_traj_vs, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_dss, d_traj_dss, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_ss, d_traj_ss, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_next_yaws, d_traj_yaws, kk+1, sampling_cnt, N);
        cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_dvs, d_traj_dvs, kk+1, sampling_cnt, N);

        if (kk < N-2){
            cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_steers, d_next_steers, kk+1, sampling_cnt, N-1); // 수정
            cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_accs, d_next_accs, kk+1, sampling_cnt, N-1); // 수정
        }

        if (kk == 0){
            cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_steers, d_first_steers, 0, sampling_cnt,1);
            cuda_substitute_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_accs, d_first_accs, 0, sampling_cnt,1);
        }

        end_time = clock() - start_time;
    }

    end_time = clock() - feasible_sampling_time;
    cout << "* total feasibleTrajSamplingParallel end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    // //////////
    // // PLOT //
    // //////////
    // float *traj_xs = new float[sampling_cnt_N0];
    // float *traj_ys = new float[sampling_cnt_N0];

    // cudaMemcpy(traj_xs, d_traj_xs, sizeof(float) * sampling_cnt_N0, cudaMemcpyDeviceToHost);
    // cudaMemcpy(traj_ys, d_traj_ys, sizeof(float) * sampling_cnt_N0, cudaMemcpyDeviceToHost);

    // std::ofstream outFile("traj_data_2.txt");

    // if (outFile.is_open()) {
    //     outFile << sampling_cnt << std::endl;

    //     for(int i=0; i<sampling_cnt; i++){
    //         for(int j=0; j<N; j++){
    //             outFile << traj_xs[i * N + j] << ' ';
    //         }
    //         outFile << std::endl;

    //         for(int j=0; j<N; j++){
    //             outFile << traj_ys[i * N + j] << ' ';
    //         }
    //         outFile << std::endl;
    //     }

    //     outFile.close();
    // }
    

    //////////////
    // get cost //
    //////////////
    cout << endl << "######################### COST TIME #########################" << endl;
    start_time = clock();
    cudaDeviceSynchronize();
    getCostParallel(choosed_obs_traj_ss, choosed_obs_traj_eys, obs_cnt, pred_cnt, obs_L, moving_obstacle_R, 
    d_traj_ss, d_traj_eys, d_traj_eyaws, d_traj_dvs, d_As, d_next_accs, d_first_accs, d_pre_as, d_Ss, d_next_steers, d_first_steers, d_pre_steers, d_longi_cost, d_lat_cost);
   
    end_time = clock() - start_time;
    cout << "* getCost end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;



    ////////////////////////////////////////
    // mppi 1111111111111111111111 //
    ////////////////////////////////////////
    cout << endl << "######################### MPPI TIME #########################" << endl;
    start_time = clock();
    numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;


    //////////////
    // Find min //
    //////////////
    // global min을 찾는 다른 방법을 생각해야 함.
    int start_range = sampling_cnt;
    numBlocks = (start_range + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
    cuda_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_lat_cost, d_A, sampling_cnt);
    

    for(;;){
        int range = 2;
        int range_size = (ceil(double(start_range) / range));

        numBlocks = (start_range + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        cuda_array_local_min_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_A, d_global_min, start_range, range); 

        start_range = range_size;
        numBlocks = (start_range + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        cuda_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_global_min, d_A, sampling_cnt);

        if(range_size == 1){
            // cout << "find global min" << endl;
            break;
        }
        // cout << "yet!: " << range_size << endl;
    }

    end_time = clock() - start_time;
    cout << "* global min Find end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
    cuda_sub_instant_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_lat_cost, d_global_min, sampling_cnt);

    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_exp_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_lat_cost, d_exp_cost, sampling_cnt);

    ///////////
    // Print //
    ///////////
    double *exp_costs = new double[sampling_cnt];
    float *lat_costs = new float[sampling_cnt];
    cudaMemcpy(exp_costs, d_exp_cost, sizeof(double) * sampling_cnt, cudaMemcpyDeviceToHost);
    cudaMemcpy(lat_costs, d_lat_cost, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost);

    cout << "################ lat cost - global min #####################" << endl;
    for(int jjjjj = 1; jjjjj < sampling_cnt; jjjjj++){
        if (jjjjj%1000 == 0){
            cout << lat_costs[jjjjj] << ' ';
        }
    }
    cout << endl;
    cout << endl;


    cout << "################ lat exp costs #####################" << endl;
    for(int jjjjj = 1; jjjjj < sampling_cnt; jjjjj++){
        if (jjjjj%1000 == 0){
            cout << exp_costs[jjjjj] << ' ';
        }
    }
    cout << endl;
    cout << endl;
    free(exp_costs);
    free(lat_costs);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////
    // CAL TOTAL //
    ///////////////
    int next_size = sampling_cnt;
    numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_double_sum_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_exp_cost, d_double_total, next_size);

    for(;;){
        next_size = int(ceil(next_size/BLOCKSIZE_X));
        cuda_double_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_double_total, d_exp_cost_, next_size);

        numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        cuda_double_sum_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_exp_cost_, d_double_total, next_size);

        if(next_size < BLOCKSIZE_X){
            break;
        }
    }


    //////////////
    // CAL MPPI //
    //////////////
    cuda_init_Kernel<<<1, N-1>>>(d_Actual_steers, 0.0f, N-1);


    ///////////////////
    // Actual steers //
    ///////////////////
    for(int i=0; i<(N-1); i++){
        float *d_mppi_a = d_A;
        float *d_mppi_s = d_B;

        next_size = sampling_cnt;
        numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        mppi_step_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_Ss, d_exp_cost, d_mppi_s, d_double_total, i, sampling_cnt, N-1);

        for(;;){
            float *d_mppi_s_int = d_reachable_yaw_min;
            
            next_size = int(ceil(next_size/BLOCKSIZE_X));
            cuda_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_mppi_s, d_mppi_s_int, next_size);

            numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
            cuda_sum_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_mppi_s_int, d_mppi_s, next_size);

            if(next_size < BLOCKSIZE_X){
                break;
            }
        }

        cuda_insert_step<<<1, 1>>>(d_mppi_s, d_Actual_steers, i);
    }




    //////////////////////////////
    // mppi 222222222222 //
    //////////////////////////////
    cout << endl << "######################### MPPI TIME #########################" << endl;
    start_time = clock();
    numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
    // cuda_init_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_total, 0.0f, sampling_cnt);

    //////////////
    // Find min //
    //////////////
    start_range = sampling_cnt;
    numBlocks = (start_range + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
    cuda_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_lat_cost, d_A, sampling_cnt);


    for(;;){
        int range = 2;
        int range_size = (ceil(double(start_range) / range));

        numBlocks = (start_range + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        cuda_array_local_min_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_A, d_global_min, start_range, range); 
        
        start_range = range_size;
        numBlocks = (start_range + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
        cuda_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_global_min, d_A, sampling_cnt);

        if(range_size == 1){
            // cout << "find global min" << endl;
            break;
        }
        // cout << "yet!: " << range_size << endl;
    }

    end_time = clock() - start_time;
    cout << "* global min Find end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    numBlocks = (sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X;
    cuda_sub_instant_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_lat_cost, d_global_min, sampling_cnt);
    
    numBlocks = ceil((sampling_cnt + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_exp_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_lat_cost, d_exp_cost, sampling_cnt);

    ///////////
    // Print //
    ///////////
    exp_costs = new double[sampling_cnt];
    lat_costs = new float[sampling_cnt];
    cudaMemcpy(exp_costs, d_exp_cost, sizeof(double) * sampling_cnt, cudaMemcpyDeviceToHost);
    cudaMemcpy(lat_costs, d_lat_cost, sizeof(float) * sampling_cnt, cudaMemcpyDeviceToHost);

    // cout << "################ longi cost - global min #####################" << endl;
    // for(int jjjjj = 0; jjjjj < sampling_cnt; jjjjj++){
    //     if (jjjjj%1000 == 0){
    //         cout << lat_costs[jjjjj] << ' ';
    //     }
    // }
    // cout << endl;
    // cout << endl;


    // cout << "################ longi exp costs #####################" << endl;
    // for(int jjjjj = 0; jjjjj < sampling_cnt; jjjjj++){
    //     if (jjjjj%1000 == 0){
    //         cout << exp_costs[jjjjj] << ' ';
    //     }
    // }
    // cout << endl;
    // cout << endl;
    // free(exp_costs);
    // free(lat_costs);

    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////
    // CAL TOTAL //
    ///////////////
    next_size = sampling_cnt;
    numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
    cuda_double_sum_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_exp_cost, d_double_total, next_size);

    for(;;){
        next_size = int(ceil(next_size/BLOCKSIZE_X));
        cuda_double_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_double_total, d_exp_cost_, next_size);

        numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        cuda_double_sum_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_exp_cost_, d_double_total, next_size);

        if(next_size < BLOCKSIZE_X){
            break;
        }
    }

    //////////////
    // CAL MPPI //
    //////////////
    cuda_init_Kernel<<<1, N-1>>>(d_Actual_as, 0.0f, N-1);


    /////////////////
    // Actual accs //
    /////////////////
    for(int i=0; i<(N-1); i++){
        float *d_mppi_a = d_A;
        float *d_mppi_s = d_B;

        next_size = sampling_cnt;
        numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
        mppi_step_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_As, d_exp_cost, d_mppi_s, d_double_total, i, sampling_cnt, N-1);

        for(;;){
            float *d_mppi_s_int = d_reachable_yaw_min;
            
            next_size = int(ceil(next_size/BLOCKSIZE_X));
            cuda_all_substitue_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_mppi_s, d_mppi_s_int, next_size);

            numBlocks = ceil((next_size + BLOCKSIZE_X - 1) / BLOCKSIZE_X);
            cuda_sum_Kernel<<<numBlocks, BLOCKSIZE_X>>>(d_mppi_s_int, d_mppi_s, next_size);

            if(next_size < BLOCKSIZE_X){
                break;
            }
        }
        
        cuda_insert_step<<<1, 1>>>(d_mppi_s, d_Actual_as, i);
    }

    end_time = clock() - start_time;
    cout << "* mppi end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    start_time = clock();
    cudaDeviceSynchronize(); // takes long time.. cudaMemcpy은 호출전에 cudaDeviceSynchronize을 수행한다. << 이게 시간이 오래 걸림.
    end_time = clock() - start_time;
    cout << "* kernel synchronize end_time: " << double(end_time)/CLOCKS_PER_SEC * 1000 << "ms" << endl;

    cudaMemcpy(Actual_steers, d_Actual_steers, sizeof(float) * (N-1), cudaMemcpyDeviceToHost);
    cudaMemcpy(Actual_accs, d_Actual_as, sizeof(float) * (N-1), cudaMemcpyDeviceToHost);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////
    // TEST //
    //////////
    // float *AASS = new float[sampling_cnt_N1];
    // float *SSSS = new float[sampling_cnt_N1];
    // cudaMemcpy(AASS, d_As, sizeof(float) * (sampling_cnt_N1), cudaMemcpyDeviceToHost);
    // cudaMemcpy(SSSS, d_Ss, sizeof(float) * (sampling_cnt_N1), cudaMemcpyDeviceToHost);

    // cout << endl << "#################### nan check ####################" << endl;
    // for(int i=0; i<sampling_cnt_N1; i++){
    //     if(isnan(AASS[i])){
    //         cout << "nan!!!!!!!!!!!!" << endl;
    //     }
    // }
    // cout << endl;

    // cout << endl << "#################### nan check ####################" << endl;
    // for(int i=0; i<sampling_cnt_N1; i++){
    //     if(isnan(SSSS[i])){
    //         cout << "nan!!!!!!!!!!!!" << endl;
    //     }
    // }
    // cout << endl;
    // cout << endl;
}