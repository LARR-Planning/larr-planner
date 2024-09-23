import rclpy
from rclpy.node import Node
from std_msgs.msg import Header
from umv_msgs.msg import GlobalPath  # 패키지와 메시지 이름을 맞게 변경해야 합니다
import math
import numpy as np
import time
from sensor_msgs.msg import PointCloud2, PointField
import sensor_msgs_py.point_cloud2 as pc2
import os
from .planner import GlobalWrapper


class GlobalPathPublisher(Node):

    def __init__(self):
        super().__init__('global_path_publisher')
        self.publisher_ = self.create_publisher(GlobalPath, '/global_path', 10)
        timer_period = 1.0  # seconds
        planner = GlobalWrapper()
        start_node = '26_s'
        end_node = '14_s'
        path = planner.g.shortest_path(start_node, end_node) 
        self.x_new, self.y_new = planner.bspline_interpolation(path, num_points=1000)
        self.x_new, self.y_new = planner.resample_by_distance(self.x_new, self.y_new, desired_distance=1.0)
        # planner.visualize_path(x_new, y_new)
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        self.msg = GlobalPath()
        self.msg.header = Header()
        self.msg.header.stamp = self.get_clock().now().to_msg()
        self.msg.header.frame_id = 'map'

        xs=self.x_new
        ys=self.y_new
        print("xs length: ", xs.shape)
        print("ys length: ", ys.shape)

        self.msg.global_xs = xs.tolist()
        self.msg.global_ys = ys.tolist()
        print("global_xs: ", self.msg.global_xs)
        print("global_ys: ", self.msg.global_ys)
        self.msg.distance_interval = 1.0  # 예시 데이터
        self.get_logger().info('Publishing path')
        # else:
        # 랜덤 곡선 경로 생성
        # x = np.linspace(0, 70, 100)
        # y = 70 * np.sin(x * np.pi / 140) + 70  # 임의의 곡선 경로
        # msg.global_xs = x.tolist()
        # msg.global_ys = y.tolist()
        # msg.distance_interval = 1.0  # 예시 데이터
        self.publisher_.publish(self.msg)



def main(args=None):
    # print("Current file path:", os.path.abspath(__file__))
    rclpy.init(args=args)
    global_path_publisher = GlobalPathPublisher()
    rclpy.spin(global_path_publisher)
    global_path_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
