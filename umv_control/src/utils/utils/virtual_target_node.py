import rclpy
from rclpy.node import Node
from airsim_interfaces.msg import CarState
from airsim_interfaces.msg import CarControls
from umv_msgs.msg import GlobalPath
from umv_msgs.msg import LocalRefPath, Obstacles
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




class VirtualTarget(Node):
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




    def global_path_callback(self, msg):
        self.global_flag = 1

        self.global_xs = np.array(msg.global_xs)
        self.global_ys = np.array(msg.global_ys)

        self.distance_interval = msg.distance_interval
        self.map_path_s = np.cumsum(self.distance_interval * np.ones_like(self.global_xs))

        ##############################################################################################################
        # make curvature:
        np_msg_global_ys = np.array(msg.global_ys)
        np_msg_global_xs = np.array(msg.global_xs)
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

        # Topic name can be changed
        self.global_path_subscription = self.create_subscription(GlobalPath, '/global_path', self.global_path_callback, 10)
        self.global_path_subscription  # prevent unused variable warning
        

        # rviz_showingse
        self.publisher_ = self.create_publisher(Obstacles, '/virtual_target', 10)
        self.publisher_obs_rviz = self.create_publisher(PointCloud2, '/obs_pos_rviz', 10)




        #need to change
        timer_period = 0.025  # seconds
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

        # steerig cb
        self.steering = 0
        

        # global path cb
        self.global_xs = [0 for i in range(100)]
        self.global_ys = [0 for i in range(100)]
        self.map_path = np.array([self.global_xs, self.global_ys])
        self.distance_interval = 2
        self.global_flag = 0
        self.map_path_s = []
        self.msg = Obstacles()

    ##########################################################################################################################################



    def publish_point_cloud(self):
        # vehicle_position
        header = Header()
        header.stamp = self.get_clock().now().to_msg()
        header.frame_id = 'map'


        vehicle_position_xs = self.msg.obs_xs
        vehicle_position_ys = self.msg.obs_ys



        points = np.zeros([self.msg.obs_cnt, 3])
        points[:, 0] = np.array(vehicle_position_xs)
        points[:, 1] = np.array(vehicle_position_ys)

        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
        ]

        point_cloud = pc2.create_cloud(header, fields, points)
        self.publisher_obs_rviz.publish(point_cloud)


    ##########################################################################################################################################



    def timer_callback(self):
        if self.global_flag == 1:
            obs_cnt = 6 # 6
            virtual_target_idx = [31,36,41, 135, 140, 145, 194, 197] # [31,36,41, 135, 140, 145]

            obs_xs = []
            obs_ys = []
            obs_ss = []
            obs_eys = []
            obs_eyaws = []
            

            for i in range(obs_cnt):
                obs_idx = virtual_target_idx[i]

                obs_x = self.global_xs[obs_idx]
                obs_y = self.global_ys[obs_idx]
                obs_s = self.map_path_s[obs_idx]
                obs_ey = 0.0
                obs_eyaw = 0.0

                obs_xs.append(obs_x)
                obs_ys.append(obs_y)
                obs_ss.append(obs_s)
                obs_eys.append(obs_ey)
                obs_eyaws.append(obs_eyaw)


                obs_xs.append(obs_x)
                obs_ys.append(obs_y)
                obs_ss.append(obs_s)
                obs_eys.append(obs_ey + 0.5)
                obs_eyaws.append(obs_eyaw)


            self.msg.obs_cnt = obs_cnt * 2
            self.msg.obs_xs = obs_xs
            self.msg.obs_ys = obs_ys
            self.msg.obs_ss = obs_ss
            self.msg.obs_eys = obs_eys
            self.msg.obs_eyaws = obs_eyaws

            self.publisher_.publish(self.msg)
            self.publish_point_cloud()
            print("publish obstacles")



def main(args=None):
    rclpy.init(args=args)
    virtualtarget = VirtualTarget()
    #algorithm publish
    #motionplan.publish_local_ref_path()
    rclpy.spin(virtualtarget)
    virtualtarget.destroy_node()
    rclpy.shutdown()






if __name__ == '__main__':
    main()
