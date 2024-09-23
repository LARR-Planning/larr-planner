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




class PathPlotter(Node):
    def __init__(self):
        super().__init__('path_plotter_node')
        self.subscription = self.create_subscription(LocalRefPath, '/local_ref_path', self.ref_local_path_cb, 10)
        self.subscription  # prevent unused variable warning
        
        self.global_path_subscription = self.create_subscription(GlobalPath, '/global_path', self.ref_global_path_cb, 10)
        self.global_path_subscription  # prevent unused variable warning
        


        # rviz_showing
        self.publisher_local_rviz = self.create_publisher(PointCloud2, '/local_path_rviz', 10)
        self.publisher_vehicle_rviz = self.create_publisher(PointCloud2, '/vehicle_pos_rviz', 10)   
        self.publisher_global_rviz = self.create_publisher(PointCloud2, '/global_path_rviz', 10)


        #need to change
        timer_period = 0.05  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.local_ref_xs = []
        self.local_ref_ys = []
        self.ego_x = 0
        self.ego_y = 0

        self.global_xs = []
        self.global_ys = []
    ##########################################################################################################################################


    def ref_local_path_cb(self, msg):
        self.local_ref_xs = msg.local_ref_xs
        self.local_ref_ys = msg.local_ref_ys
        self.ego_x = msg.ego_x
        self.ego_y = msg.ego_y


    def ref_global_path_cb(self, msg):
        self.global_xs = np.array(msg.global_xs)
        self.global_ys = np.array(msg.global_ys)


    ##########################################################################################################################################
    def publish_point_cloud_local_path(self):
        ##############################################
        # local path
        header = Header()
        header.stamp = self.get_clock().now().to_msg()
        header.frame_id = 'map'

        lll = len(self.local_ref_xs)
        points = np.zeros([lll, 3])
        points[:, 0] = np.array(self.local_ref_xs)
        points[:, 1] = np.array(self.local_ref_ys)

        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
        ]

        point_cloud = pc2.create_cloud(header, fields, points)
        self.publisher_local_rviz.publish(point_cloud)

        ##############################################
        # vehicle_position
        header = Header()
        header.stamp = self.get_clock().now().to_msg()
        header.frame_id = 'map'

        vehicle_position_xs = [self.ego_x]
        vehicle_position_ys = [self.ego_y]

        points = np.zeros([1, 3])
        points[:, 0] = np.array(vehicle_position_xs)
        points[:, 1] = np.array(vehicle_position_ys)

        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
        ]

        point_cloud = pc2.create_cloud(header, fields, points)
        self.publisher_vehicle_rviz.publish(point_cloud)
        print("publish local ref path")





    def publish_point_cloud_global_path(self):
        header = Header()
        header.stamp = self.get_clock().now().to_msg()
        header.frame_id = 'map'

        lll = len(self.global_xs)
        points = np.zeros([lll, 3])
        points[:, 0] = np.array(self.global_xs)
        points[:, 1] = np.array(self.global_ys)

        fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1)
        ]

        point_cloud = pc2.create_cloud(header, fields, points)
        self.publisher_global_rviz.publish(point_cloud)
        print("publish global path")

    ##########################################################################################################################################


    def timer_callback(self):
        self.publish_point_cloud_local_path()
        self.publish_point_cloud_global_path()




def main(args=None):
    rclpy.init(args=args)
    pathplotter = PathPlotter()
    #algorithm publish
    #motionplan.publish_local_ref_path()
    rclpy.spin(pathplotter)
    pathplotter.destroy_node()
    rclpy.shutdown()



if __name__ == '__main__':
    main()
