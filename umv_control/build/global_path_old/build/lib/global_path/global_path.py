import rclpy
from rclpy.node import Node
from std_msgs.msg import Header
from umv_msgs.msg import GlobalPath  # 패키지와 메시지 이름을 맞게 변경해야 합니다
import math
import numpy as np
import time
from sensor_msgs.msg import PointCloud2, PointField
import sensor_msgs_py.point_cloud2 as pc2


class GlobalPathPublisher(Node):

    def __init__(self):
        super().__init__('global_path_publisher')
        self.publisher_ = self.create_publisher(GlobalPath, '/global_path', 10)
        timer_period = 1.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)




    def timer_callback(self):
        self.msg = GlobalPath()
        self.msg.header = Header()
        self.msg.header.stamp = self.get_clock().now().to_msg()
        self.msg.header.frame_id = 'map'

        # 직선 경로 생성
        x1 = np.array(list(range(0, 100, 1)))
        y1 = np.zeros_like(x1)

        # curve
        angle_start_rad = np.deg2rad(-90)
        angle_end_rad = np.deg2rad(90)
        radius = 50
        arc_length = radius * (angle_end_rad - angle_start_rad)
        num_points = int(np.ceil(arc_length))
        angles = np.linspace(angle_start_rad, angle_end_rad, num_points)
        x2 = 100 + radius * np.cos(angles)
        y2 = 50 + radius * np.sin(angles)
    
        # straight
        x3 = np.array(list(range(100, 0, -1)))
        y3 = 100 * np.ones_like(x1)

        # curve
        angle_start_rad = np.deg2rad(90)
        angle_end_rad = np.deg2rad(270)
        radius = 50
        arc_length = radius * (angle_end_rad - angle_start_rad)
        num_points = int(np.ceil(arc_length))
        angles = np.linspace(angle_start_rad, angle_end_rad, num_points)
        x4 = 0 + radius * np.cos(angles)
        y4 = 50 + radius * np.sin(angles)

        xs = np.concatenate((x1, x2, x3, x4))
        ys = np.concatenate((y1, y2, y3, y4))

        print("xs length: ", xs.shape)
        print("ys length: ", ys.shape)

        xs = xs - 50
        ys = ys + 0


        self.msg.global_xs = xs.tolist()
        self.msg.global_ys = ys.tolist()
        print("global_xs: ", self.msg.global_xs)
        print("global_ys: ", self.msg.global_ys)
        self.msg.distance_interval = 1.0  # 예시 데이터
        self.get_logger().info('Publishing straight line path')
        # else:
        # 랜덤 곡선 경로 생성
        # x = np.linspace(0, 70, 100)
        # y = 70 * np.sin(x * np.pi / 140) + 70  # 임의의 곡선 경로
        # msg.global_xs = x.tolist()
        # msg.global_ys = y.tolist()
        # msg.distance_interval = 1.0  # 예시 데이터
        self.get_logger().info('Publishing random curve path')

        self.publisher_.publish(self.msg)



def main(args=None):
    rclpy.init(args=args)
    global_path_publisher = GlobalPathPublisher()
    rclpy.spin(global_path_publisher)
    global_path_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
