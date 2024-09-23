import math
import rclpy
from rclpy.node import Node
from airsim_interfaces.msg import CarState
from airsim_interfaces.msg import CarControls
from umv_msgs.msg import HostVehicleFilter
import numpy as np
from copy import deepcopy



class HostVehiclePublisher(Node):
    def state_cb(self, msg):
        # current time
        current_time = self.get_clock().now()
        time_diff = (current_time - self.prev_time).nanoseconds / 1e9  # time interval(s)

        # linear velocity # sacle check # m/s
        self.linear_velocity_x = msg.twist.twist.linear.x 
        self.linear_velocity_y = msg.twist.twist.linear.y
        self.linear_velocity_z = msg.twist.twist.linear.z
        
        # angular velocity
        self.angular_velocity_x = msg.twist.twist.angular.x
        self.angular_velocity_y = msg.twist.twist.angular.y
        self.angular_velocity_z = msg.twist.twist.angular.z
        
        # acceleration
        if self.prev_linear_velocity_x is not None:
            self.acceleration_x = (self.linear_velocity_x - self.prev_linear_velocity_x) / time_diff
        else:
            self.acceleration_x = 0.0
        
        # PoseTwist
        self.position_x = msg.pose.pose.position.x
        self.position_y = msg.pose.pose.position.y
        self.position_z = msg.pose.pose.position.z
        
        self.orientation_x = msg.pose.pose.orientation.x
        self.orientation_y = msg.pose.pose.orientation.y
        self.orientation_z = msg.pose.pose.orientation.z
        self.orientation_w = msg.pose.pose.orientation.w
        
        
        self.prev_linear_velocity_x = self.linear_velocity_x
        self.prev_time = current_time
        
        # print
        # self.get_logger().info(f'Linear Velocity - x: {self.linear_velocity_x}, y: {self.linear_velocity_y}, z: {self.linear_velocity_z}')
        # self.get_logger().info(f'Angular Velocity - x: {self.angular_velocity_x}, y: {self.angular_velocity_y}, z: {self.angular_velocity_z}')
        # self.get_logger().info(f'Acceleration - x: {self.acceleration_x} m/s^2')
        # self.get_logger().info(f'Position - x: {self.position_x}, y: {self.position_y}, z: {self.position_z}')
        # self.get_logger().info(f'Orientation - x: {self.orientation_x}, y: {self.orientation_y}, z: {self.orientation_z}, w: {self.orientation_w}')


    def steering_cb(self, msg):
        self.steering = msg.steering

        # print
        self.get_logger().info(f'steering: {self.steering}')



    def init_parameter(self):
        ######## host vehicle filter #################################################################################################
        self.X_dim = 4 # vx w ax angle
        self.Z_dim = 4 # vx w ax angle
        
        self.Vx = 0
        self.w = 0
        self.Ax = 0
        self.angle = 0
        
        self.gear_ratio = 14.267
        self.angle_bias = 0.05
        
        # self.dt = 0.04 # ros period
        
        self.e = 1.849
        self.L = 2.875 + 2
        self.tau = 0.002 # experiment data
        self.Kus = 0.0034 # experiment data
        
        self.pre_time = 0
        self.elapsed_time = 0
        # self.dt = 0
        
        self.wbias = 0
        self.Aw = 0
        
        self.bias = [0, 0, 0, 0]
        self.cov = [0, 0, 0, 0]
        
        self.P = np.zeros((self.X_dim, self.X_dim))
        #################################################################################################################################



    def __init__(self):
        super().__init__('host_vehicle_publisher_node')
        self.subscription = self.create_subscription(CarState, '/airsim_node/PhysXCar/car_state', self.state_cb, 10)
        self.subscription  # prevent unused variable warning

        self.subscription = self.create_subscription(CarControls, '/airsim_node/PhysXCar/car_cmd', self.steering_cb, 10)
        self.subscription 

        self.publisher_ = self.create_publisher(HostVehicleFilter, '/host_vehicle_filter_msg', 10)


        #need to change
        timer_period = 0.04  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        
        self.prev_linear_velocity_x = None  # 초기 선형 속도 저장 변수
        self.prev_time = self.get_clock().now()  # 초기 시간 저장 변수


        # state cb
        self.linear_velocity_x = 0
        self.linear_velocity_y = 0
        self.linear_velocity_z = 0

        self.angular_velocity_x = 0
        self.angular_velocity_y = 0
        self.angular_velocity_z = 0

        self.acceleration_x = 0
        
        self.position_x = 0
        self.position_y = 0
        self.position_z = 0

        self.orientation_x = 0
        self.orientation_y = 0
        self.orientation_z = 0
        self.orientation_w = 0


        # steering cb
        self.steering = 0
        


        ############# host vehicle parameter variable #############
        self.X_dim = 0 # vx w ax angle
        self.Z_dim = 0 # vx w ax angle
        
        self.Vx = 0  # state parameter
        self.w = 0
        self.Ax = 0
        self.angle = 0
        
        self.gear_ratio = 0
        self.angle_bias = 0
        
        self.dt = timer_period
        
        self.e = 0
        self.L = 0
        self.tau = 0 # experiment data
        self.Kus = 0 # experiment data
        
        self.pre_time = 0
        self.elapsed_time = 0
        
        self.wbias = 0
        self.Aw = 0
        
        self.bias = [0, 0, 0, 0]
        self.cov = [0, 0, 0, 0]
        
        self.P = np.zeros((self.X_dim, self.X_dim))
        ############################################################
        self.init_parameter()



    ##################################################################################################
    def get_EKF_matrix(self, Vx, w, e, L, dt, tau, Kus, angle):
        M_PI = 3.14
        
        EH = np.zeros((self.Z_dim, self.X_dim))

        # Low pass filter
        EH[0,0] = 1
        EH[1,1] = 1
        EH[2,2] = 1
        EH[3,3] = 1

        # EKF A matrix: EA
        EA = np.zeros((self.X_dim, self.X_dim))
        EA[0,2] = 1
        EA[1,1] = -1/tau
        EA[1,3] = 1/tau * Vx / (L + Kus * (Vx)**2) * abs(angle)
    

        # EKF B matrix: EB
        EB = np.identity(self.X_dim)
        #rospy.logerr("EB: ", EB)
        # EKF F matrix: EF
        EF = np.identity(self.X_dim) + EA*dt

        # state noise
        N = EB*dt
        Q = np.zeros((self.X_dim,self.X_dim))
        factor = 1
        # Q[0,0] = (factor * 4*3.00/3)**2
        # Q[1,1] = (factor *10* 3.00/180*M_PI)**2
        # Q[2,2] = (factor *3.00/3)**2
        # Q[3,3] = (factor *10* 3.00/180*M_PI)**2
        # Q[4,4] = (factor *0.83)**2  
        Q[0,0] = (factor * 100)
        Q[1,1] = (factor * 0.01)
        Q[2,2] = (factor * 1)      
        Q[3,3] = (factor * 1)
        #Q[4,4] = (factor *1)**2

        EQ = np.matmul(np.matmul(N, Q), np.transpose(N))

        # measurement noise
        Vd = np.zeros((self.Z_dim, self.Z_dim))
        factor = 1
        Vd[0,0] = (factor * self.cov[0])
        Vd[1,1] = (factor * self.cov[1])
        Vd[2,2] = (factor * self.cov[2])
        Vd[3,3] = (factor * self.cov[3])
        
        return EH, EF, EQ, Vd
    
    
    def update(self, F, P, Q, X):
        type_check = np.array(1)
        
        if type(F) != type(type_check):
            F = np.array(F)
        if type(P) != type(type_check):
            P = np.array(P)
        if type(Q) != type(type_check):
            Q = np.array(Q)
        if type(X) != type(type_check):
            X = np.array(X)
        
        prior_X = np.matmul(F, X)
        prior_P = np.matmul(np.matmul(F,P), np.transpose(F)) + Q
        
        return prior_X, prior_P

        
    def measurement_update(self, H, R, Z, prior_X, prior_P):
        type_check = np.array(1)
        
        if type(H) != type(type_check):
            H = np.array(H)
        if type(R) != type(type_check):
            R = np.array(R)
        if type(Z) != type(type_check):
            Z = np.array(Z)
        if type(prior_X) != type(type_check):
            prior_X = np.array(prior_X)
        if type(prior_P) != type(type_check):
            prior_P = np.array(prior_P)
        
        HPH = np.matmul(np.matmul(H, prior_P), np.transpose(H))
        PH = np.matmul(prior_P, np. transpose(H))
        
        K = np.matmul(PH, np.linalg.inv(HPH + R))
        poster_X = prior_X + np.matmul(K, (Z - np.matmul(H, prior_X)))
        
        KH = np.matmul(K, H)

        I = np.eye(KH.shape[0])
        poster_P = np.matmul((I - KH), prior_P)
        
        return poster_X, poster_P
    
    
    
    def EKF(self):
        # measurement
        self.m_v = math.sqrt(self.linear_velocity_x ** 2 + self.linear_velocity_y ** 2)
        self.m_yawrate = self.angular_velocity_z
        self.m_a = self.acceleration_x
        self.m_sas = self.steering


        # state prior
        Vx = self.Vx # m/s
        w = self.w # deg/s
        Ax = self.Ax # m/s2
        angle = self.angle # sas angle


        car_e = self.e
        car_L =  self.L
        dt = self.dt
        tau = self.tau
        Kus = self.Kus
        
        EH, EF, EQ, ER = self.get_EKF_matrix(Vx, w, car_e, car_L, dt, tau, Kus, angle)
        
        X = np.zeros((self.X_dim, 1))   
        X[0, 0] = Vx #Vx
        X[1, 0] = w  #w
        X[2, 0] = Ax #acc 
        X[3, 0] = angle #sas
        
        P = deepcopy(self.P)
        Z = np.zeros((self.Z_dim,1))
        # Measurement 
        # Z[0,0] = (self.chassis_msg.whl_spd_fl + self.chassis_msg.whl_spd_fr + self.chassis_msg.whl_spd_rl + self.chassis_msg.whl_spd_rr)/4/3.6
        # Z[1,0] = self.chassis_msg.yaw_rate
        # Z[2,0] = self.chassis_msg.long_accel
        # Z[3,0] = (self.chassis_msg.sas_angle) / self.gear_ratio
        Z[0,0] = self.m_v # m/s
        Z[1,0] = self.m_yawrate # rad/s
        Z[2,0] = self.m_a
        Z[3,0] = (self.m_sas) / self.gear_ratio
       
        prior_X, prior_P = self.update(EF, P, EQ, X)
        #rospy.logerr("vx: " + str(prior_X[0,0]))
        
        X, poster_P = self.measurement_update(EH, ER, Z, prior_X, prior_P)
        self.P = deepcopy(poster_P)
        
        # filtered state.
        self.Vx = X[0,0]
        self.w = X[1,0]
        self.Ax = X[2,0]
        self.angle = X[3,0] 
    #################################################################################################################################



    def timer_callback(self):
        self.EKF()
        
        msg = HostVehicleFilter()
        
        msg.vx = self.Vx # self.Vx  # 예제 속도
        print("#####################################################################################")
        print("Filtering result: ", self.Vx)
        print("#####################################################################################")


        msg.yawrate = self.w  # 예제 각속도
        msg.ax = self.Ax  # 예제 가속도
        msg.sas = self.angle # 예제 핸들각

        self.publisher_.publish(msg)
        self.get_logger().info(f'host vehicle filter')
        self.get_logger().info(f'Publishing: {msg}')



def main(args=None):
    rclpy.init(args=args)
    host_vehicle_publisher = HostVehiclePublisher()

    rclpy.spin(host_vehicle_publisher)
    host_vehicle_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
