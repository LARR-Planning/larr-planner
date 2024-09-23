import rclpy
from rclpy.node import Node
from airsim_interfaces.msg import CarState
from airsim_interfaces.msg import CarControls
from umv_msgs.msg import GlobalPath
from umv_msgs.msg import LocalRefPath
import numpy as np
import math

from scipy import io
from scipy import signal
from sensor_msgs.msg import PointCloud2, PointField
import sensor_msgs_py.point_cloud2 as pc2
from std_msgs.msg import Header



def quaternion_to_euler_angle(w, x, y, z):
    ysqr = y * y

    t0 = +2.0 * (w * x + y * z)
    t1 = +1.0 - 2.0 * (x * x + ysqr)
    X = (math.atan2(t0, t1))

    t2 = +2.0 * (w * y - z * x)
    t2 = +1.0 if t2 > +1.0 else t2
    t2 = -1.0 if t2 < -1.0 else t2
    Y = (math.asin(t2))

    t3 = +2.0 * (w * z + x * y)
    t4 = +1.0 - 2.0 * (ysqr + z * z)
    Z = (math.atan2(t3, t4))

    return X, Y, Z


def transfer_to_local(T, arr):
    new = np.concatenate((arr, [arr[0] * 0], [arr[0] * 0 + 1]), axis=0)
    new1 = np.dot(T, new)
    return new1


def get_min_dist_index(end_len, arr, x, y):
    # print("arr: ", arr)
    # print(type(arr))
    # print(arr.shape)
    new1 = np.sqrt(np.power((arr[0][:end_len] - x), 2) + np.power((arr[1][:end_len] - y), 2))
    val = np.amin(new1)
    ind = np.argmin(new1)


    pos_xs = []
    pos_ys = []
    if ind != 0 and ind < len(arr[0])-1:
        pos_xs = arr[0][(ind-1):(ind+1)]
        pos_ys = arr[1][(ind-1):(ind+1)]
    elif ind == 0:
        pos_xs = arr[0][ind:(ind+2)]
        pos_ys = arr[1][ind:(ind+2)]
    else:
        pos_xs = arr[0][(ind-2):ind]
        pos_ys = arr[1][(ind-2):ind]
        

    dis_xs = np.linspace(pos_xs[0],pos_xs[1],1000)
    dis_ys = np.linspace(pos_ys[0],pos_ys[1],1000)

    # print("?????: ", dis_xs)
    # print("?????: ", dis_ys)

    new1 = np.sqrt(np.power((dis_xs[:] - x), 2) + np.power((dis_ys[:] - y), 2))
    val1 = np.amin(new1)

    pos_xs = arr[0][ind:(ind+2)]
    pos_ys = arr[1][ind:(ind+2)]

    if len(pos_xs) == 1:
        return [val1, ind]

    dis_xs_ = np.linspace(pos_xs[0],pos_xs[1],1000)
    dis_ys_ = np.linspace(pos_ys[0],pos_ys[1],1000)
    
    new1 = np.sqrt(np.power((dis_xs[:] - x), 2) + np.power((dis_ys[:] - y), 2))
    val2 = np.amin(new1)

    val = min(val1, val2)

    return [val, ind]




def calc_curvature(x, y, num_window, is_smooth, Hz): # recommend Hz => 0.1, num_window => 20~30
    if num_window < 2:
        num_window = 2
    n_window = num_window
    map_centerline = np.array([x,y]) # 2 X N array
    # theta = np.radians(90)
    # c,s = np.cos(theta), np.sin(theta)
    # Rot_Mat_theta = np.array([[c,-s],[s,c]])
    Rot_Mat_90deg = np.array([[0.0,-1.0],[1.0,0.0]])

    num_pts = len(map_centerline[0])
    # ds = np.sqrt(np.diff(x)**2 + np.diff(y)**2)
    Sc = np.cumsum(np.sqrt(np.diff(x)**2 + np.diff(y)**2))
    Sc = np.insert(Sc, 0, 0)  # 1 X N array
    T_Centerline = np.diff(map_centerline)/np.array((np.diff(Sc), np.diff(Sc))) # 2 X (N-1) array
    N_Centerline = np.dot(Rot_Mat_90deg,T_Centerline) # 2 X (N-1) array

    Yaw_o = np.arctan2(T_Centerline[1,0], T_Centerline[0,0])
    dYaw = np.zeros((num_pts,1))

    for idx in range(1,num_pts):
        if idx == num_pts-1:
            dYaw[idx] = dYaw[idx-1]
        else:
            R = np.array([T_Centerline[:,idx-1], N_Centerline[:,idx-1]])
            P_rel = np.dot(np.transpose(R),T_Centerline[:,idx])
            P_rel = np.dot(R,T_Centerline[:,idx])
            dYaw[idx] = np.arctan2(P_rel[1], P_rel[0])

    Yaw_noisy = Yaw_o + np.cumsum(dYaw)
    curvature_yawrate = np.diff(Yaw_noisy)/np.diff(Sc)

    test_cumsum = np.cumsum(np.insert(curvature_yawrate,0,0))
    
    test_curvature_smooth = (test_cumsum[n_window:] - test_cumsum[:-n_window]) / float(n_window)
    
    test_curvature_smooth = np.insert(test_curvature_smooth, 0, np.ones(int(n_window/2))*test_curvature_smooth[0])
    test_curvature_smooth = np.insert(test_curvature_smooth, -1, np.ones(int(n_window/2))*test_curvature_smooth[-1])

    if is_smooth == True:
        Hz_new = max(min(Hz, 0.999), 0.001) # recommend => 0.1
        b,a = signal.butter(1,Hz_new)
        test_curvature_smooth = signal.filtfilt(b,a,test_curvature_smooth)

    idx = np.where(Yaw_noisy < -3.141517)
    Yaw_noisy[idx] = Yaw_noisy[idx] + 2 * 3.141517
    idx = np.where(Yaw_noisy > 3.141517)
    Yaw_noisy[idx] = Yaw_noisy[idx] - 2 * 3.141517
    
    return Sc, test_curvature_smooth, Yaw_noisy



class MotionPlanner(Node):
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

        # print("x_position: ", self.position_x)
        # print("y_position: ", self.position_y)
        
        self.orientation_x = msg.pose.pose.orientation.x
        self.orientation_y = msg.pose.pose.orientation.y
        self.orientation_z = msg.pose.pose.orientation.z
        self.orientation_w = msg.pose.pose.orientation.w
        
        q_x = self.orientation_x
        q_y = self.orientation_y
        q_z = self.orientation_z
        q_w = self.orientation_w

        roll, pitch, yaw = quaternion_to_euler_angle(q_w, q_x, q_y, q_z)
        self.yaw = yaw
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



    def global_path_callback(self, msg):
        self.brake_flag = 0

        self.global_xs = np.array(msg.global_xs)
        self.global_ys = np.array(msg.global_ys)
        self.end_len = len(self.global_xs)
        print("self.end_len: ", self.end_len)

        self.distance_interval = msg.distance_interval
        ##############################################################################################################
        # attach straight line for preventing out of bound
        self.idx_interval = int(self.ds/self.distance_interval)

        self.final_dx = self.global_xs[-1] - self.global_xs[-2]
        self.final_dy = self.global_ys[-1] - self.global_ys[-2]
        self.final_yaw = math.atan2(self.final_dy, self.final_dx)

        self.add_path_len = self.idx_interval * (self.horizon_len + 2)

        self.final_x = self.global_xs[-1] + self.add_path_len * math.cos(self.final_yaw)
        self.final_y = self.global_ys[-1] + self.add_path_len * math.sin(self.final_yaw)

        self.add_xs = np.linspace(self.global_xs[-1], self.final_x, self.horizon_len + 3)
        self.add_ys = np.linspace(self.global_ys[-1], self.final_y, self.horizon_len + 3)

        dx = self.add_xs[-1] - self.add_xs[-2]
        dy = self.add_ys[-1] - self.add_ys[-2]
        dddd = math.sqrt(dx**2 + dy ** 2)

        self.global_xs = np.concatenate([self.global_xs, self.add_xs[1:]])
        self.global_ys = np.concatenate([self.global_ys, self.add_ys[1:]])
        ##############################################################################################################
        self.map_path_s = np.cumsum(self.distance_interval * np.ones_like(self.global_xs))

        # make curvature:
        np_msg_global_ys = np.array(self.global_ys)
        np_msg_global_xs = np.array(self.global_xs)
        yaw = np.arctan2(np_msg_global_ys[1:] - np_msg_global_ys[0:-1], np_msg_global_xs[1:] - np_msg_global_xs[0:-1])

        dyaw = (yaw[1:] - yaw[0:-1])
        
        idx = np.where(dyaw > 5)
        dyaw[idx] = dyaw[idx] - math.pi * 2
        idx = np.where(dyaw < -5)
        dyaw[idx] = dyaw[idx] + math.pi * 2 

        curvature = dyaw / self.distance_interval
        curvature = curvature.tolist()
        curvature.append(curvature[-1])
        curvature.append(curvature[-1])

        self.map_curvature = np.array(curvature) ##################################################### can get curvature??????
        

        self.map_path = np.array([self.global_xs, self.global_ys])
        self.global_flag = 1

        # print
        # self.get_logger().info(f'Global Path X coordinates: {self.global_xs}')
        # self.get_logger().info(f'Global Path Y coordinates: {self.global_ys}')
        # self.get_logger().info(f'Distance Interval: {self.distance_interval}')



    def __init__(self):
        super().__init__('motion_planner_node')
        self.subscription = self.create_subscription(CarState, '/airsim_node/PhysXCar/car_state', self.state_cb, 10)
        self.subscription  # prevent unused variable warning

        self.subscription = self.create_subscription(CarControls, '/airsim_node/PhysXCar/car_cmd', self.steering_cb, 10)
        self.subscription 
        # Topic name can be changed
        self.global_path_subscription = self.create_subscription(GlobalPath, '/global_path', self.global_path_callback, 10)
        self.global_path_subscription  # prevent unused variable warning
        
        #publishing
        self.local_ref_path_publisher = self.create_publisher(LocalRefPath, '/local_ref_path', 10)  # LocalRefPath publisher
        
        # # rviz_showing
        # self.publisher_rviz = self.create_publisher(PointCloud2, '/local_path_rviz', 10)
        # self.publisher_vehicle_rviz = self.create_publisher(PointCloud2, '/vehicle_pos_rviz', 10)

        #need to change
        timer_period = 0.05  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.prev_linear_velocity_x = None  # before linear velocity
        self.prev_time = self.get_clock().now()  # before step time

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

        self.yaw = 0
        self.end_len = 0
        self.brake_flag = 0

        # steerig cb
        self.steering = 0
        

        # global path cb
        self.global_xs = [0 for i in range(100)]
        self.global_ys = [0 for i in range(100)]
        self.map_path = np.array([self.global_xs, self.global_ys])
        self.distance_interval = 2
        self.global_flag = 0


        # eyaw, ey
        self.eyaw = 0
        self.ey = 0
        self.ds = 1
        self.horizon_len = 30


    ##########################################################################################################################################



    # def publish_point_cloud(self):
    #     # local path
    #     header = Header()
    #     header.stamp = self.get_clock().now().to_msg()
    #     header.frame_id = 'map'

    #     lll = len(self.local_ref_path_msg.local_ref_xs)
    #     points = np.zeros([lll, 3])
    #     points[:, 0] = np.array(self.local_ref_path_msg.local_ref_xs)
    #     points[:, 1] = np.array(self.local_ref_path_msg.local_ref_ys)

    #     fields = [
    #         PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
    #         PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
    #         PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
    #     ]

    #     point_cloud = pc2.create_cloud(header, fields, points)
    #     self.publisher_rviz.publish(point_cloud)


    #     # vehicle_position
    #     header = Header()
    #     header.stamp = self.get_clock().now().to_msg()
    #     header.frame_id = 'map'

    #     vehicle_position_xs = [self.position_x]
    #     vehicle_position_ys = [self.position_y]

    #     points = np.zeros([1, 3])
    #     points[:, 0] = np.array(vehicle_position_xs)
    #     points[:, 1] = np.array(vehicle_position_ys)

    #     fields = [
    #         PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
    #         PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
    #         PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
    #     ]

    #     point_cloud = pc2.create_cloud(header, fields, points)
    #     self.publisher_vehicle_rviz.publish(point_cloud)


    ##########################################################################################################################################


    def timer_callback(self):
        # get ey, eyaw
        if self.global_flag == 1:
            print("self.position_x: ", self.position_x)
            print("self.position_y: ", self.position_y)
            [dist, closest_ind_in] = get_min_dist_index(self.end_len, self.map_path, self.position_x, self.position_y)
            self.closet_idx = closest_ind_in
            

            front_idx = 0
            idx_interval = int(self.ds/self.distance_interval)
            station_idxs = list(range(closest_ind_in-front_idx, min(closest_ind_in + idx_interval * (self.horizon_len) - front_idx, len(self.map_path[0])), idx_interval))# 2m?
            # print("station_idxs: ", station_idxs)
            next_station_idxs = [min(x+1, len(self.map_path[0])-1) for x in station_idxs] # error out of range #######################################################################


            if closest_ind_in >= (self.end_len - 12):
                # near end of the global path
                self.brake_flag = 1


            self.ref_path_xs = self.global_xs[station_idxs]
            self.ref_path_ys = self.global_ys[station_idxs]
            self.ref_path_ss = self.map_path_s[station_idxs]
            
            self.ego_s = self.ref_path_ss[0]
            
            self.ref_next_path_xs = self.global_xs[next_station_idxs]
            self.ref_next_path_ys = self.global_ys[next_station_idxs]
            
            self.ref_path_curvs = self.map_curvature[station_idxs]
            
            self.ref_path_yaws = np.arctan2(self.ref_next_path_ys- self.ref_path_ys, self.ref_next_path_xs- self.ref_path_xs) # -pi ~ pi
            self.ref_path_yaws = np.trunc((self.ref_path_yaws) * 1000000)
            self.ref_path_yaws = self.ref_path_yaws/1000000
            
            for i in range(1, self.horizon_len):
                a = self.ref_path_yaws[i] - self.ref_path_yaws[0]
                
                if a <= -3.141592 * 2:
                    self.ref_path_yaws[i] = self.ref_path_yaws[i] + 3.141592 * 2
                elif a >= 3.141592 * 2:
                    self.ref_path_yaws[i] = self.ref_path_yaws[i] - 3.141592 * 2
            

            self.ey = dist
            # isleftside
            px1 = self.ref_path_xs[0]
            py1 = self.ref_path_ys[0]
            px2 = self.ref_path_xs[1]
            py2 = self.ref_path_ys[1]
            px3 = self.position_x
            py3 = self.position_y 
            ret = (px2 - px1) * (py3 - py1) - (px3 - px1) * (py2 - py1)
            if ret < 0:
                self.ey = -1 * self.ey
                
            
            self.eyaw = self.yaw - self.ref_path_yaws[0]
            if self.eyaw > 3.141592:
                self.eyaw = self.eyaw - 2 * 3.141592
            elif self.eyaw < -3.141592:
                self.eyaw = self.eyaw + 2 * 3.141592



            # LocalRefPath msg
            self.local_ref_path_msg = LocalRefPath()
            self.local_ref_path_msg.local_ref_xs = self.ref_path_xs.tolist() #ex
            self.local_ref_path_msg.local_ref_ys = self.ref_path_ys.tolist()  #ex
            self.local_ref_path_msg.local_ref_ss = self.ref_path_ss.tolist()  #ex
            self.local_ref_path_msg.local_ref_yaws = self.ref_path_yaws.tolist()  #ex
            self.local_ref_path_msg.local_ref_curvs = self.ref_path_curvs.tolist()  #ex
            self.local_ref_path_msg.ey = self.ey.tolist()  #ex
            self.local_ref_path_msg.eyaw = self.eyaw.tolist()  #ex
            self.local_ref_path_msg.ego_s = self.ego_s.tolist()  #ex
            self.local_ref_path_msg.ego_x = self.position_x
            self.local_ref_path_msg.ego_y = self.position_y


            self.local_ref_path_msg.ego_yaw = self.yaw
            self.local_ref_path_msg.brake_flag = int(self.brake_flag)


            self.local_ref_path_publisher.publish(self.local_ref_path_msg)
            self.get_logger().info(f'Published LocalRefPath: {self.local_ref_path_msg}')

            # self.publish_point_cloud()
        else:
            self.get_logger().info(f'No global path')


    #algorithm spot
    #def publish_local_ref_path(self):




def main(args=None):
    rclpy.init(args=args)
    motionplan = MotionPlanner()
    #algorithm publish
    #motionplan.publish_local_ref_path()
    rclpy.spin(motionplan)
    motionplan.destroy_node()
    rclpy.shutdown()






if __name__ == '__main__':
    main()
