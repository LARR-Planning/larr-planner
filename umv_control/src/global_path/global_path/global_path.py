import rclpy
from rclpy.node import Node
from std_msgs.msg import Header
from umv_msgs.msg import GlobalPath  # 패키지와 메시지 이름을 맞게 변경해야 합니다
import numpy as np
import time

class GlobalPathPublisher(Node):

    def __init__(self):
        super().__init__('global_path_publisher')
        self.publisher_ = self.create_publisher(GlobalPath, '/global_path', 10)
        timer_period = 1.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

    def timer_callback(self):
        msg = GlobalPath()
        msg.header = Header()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = 'map'

        # 직선 경로 생성
        x = np.linspace(0, 70, 100)
        y = np.linspace(0, 70, 100)
        msg.global_xs = x.tolist()
        msg.global_ys = y.tolist()
        msg.distance_interval = 1.0  # 예시 데이터
        self.get_logger().info('Publishing straight line path')
        # else:
        #     # 랜덤 곡선 경로 생성
        #     x = np.linspace(0, 70, 100)
        #     y = 70 * np.sin(x * np.pi / 140) + 70  # 임의의 곡선 경로
        #     msg.global_xs = x.tolist()
        #     msg.global_ys = y.tolist()
        #     msg.distance_interval = 1.0  # 예시 데이터
        #     self.get_logger().info('Publishing random curve path')

        self.publisher_.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    global_path_publisher = GlobalPathPublisher()
    rclpy.spin(global_path_publisher)
    global_path_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
