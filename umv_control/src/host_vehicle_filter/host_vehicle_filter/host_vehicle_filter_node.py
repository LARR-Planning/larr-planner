import rclpy
from rclpy.node import Node
from airsim_interfaces.msg import CarState
from airsim_interfaces.msg import CarControls
from umv_msgs.msg import HostVehicleFilter

class HostVehiclePublisher(Node):

    def __init__(self):
        super().__init__('host_vehicle_publisher_node')
        self.subscription = self.create_subscription(CarState, '/airsim_node/PhysXCar/car_state', self.state_cb, 10)
        self.subscription  # prevent unused variable warning

        self.subscription = self.create_subscription(CarControls, '/airsim_node/PhysXCar/car_cmd', self.steering_cb, 10)
        self.subscription 

        self.publisher_ = self.create_publisher(HostVehicleFilter, '/host_vehicle_filter_msg', 10)

        #need to change
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        
        self.prev_linear_velocity_x = None  # 초기 선형 속도 저장 변수
        self.prev_time = self.get_clock().now()  # 초기 시간 저장 변수


    def state_cb(self, msg):
        # current time
        current_time = self.get_clock().now()
        time_diff = (current_time - self.prev_time).nanoseconds / 1e9  # time interval(s)

        # linear velocity
        linear_velocity_x = msg.twist.twist.linear.x
        linear_velocity_y = msg.twist.twist.linear.y
        linear_velocity_z = msg.twist.twist.linear.z
        
        # angular velocity
        angular_velocity_x = msg.twist.twist.angular.x
        angular_velocity_y = msg.twist.twist.angular.y
        angular_velocity_z = msg.twist.twist.angular.z
        
        # acceleration
        if self.prev_linear_velocity_x is not None:
            acceleration_x = (linear_velocity_x - self.prev_linear_velocity_x) / time_diff
        else:
            acceleration_x = 0.0
        
        # PoseTwist
        position_x = msg.pose.pose.position.x
        position_y = msg.pose.pose.position.y
        position_z = msg.pose.pose.position.z
        
        orientation_x = msg.pose.pose.orientation.x
        orientation_y = msg.pose.pose.orientation.y
        orientation_z = msg.pose.pose.orientation.z
        orientation_w = msg.pose.pose.orientation.w
        
        
        self.prev_linear_velocity_x = linear_velocity_x
        self.prev_time = current_time
        
        # print
        self.get_logger().info(f'Linear Velocity - x: {linear_velocity_x}, y: {linear_velocity_y}, z: {linear_velocity_z}')
        self.get_logger().info(f'Angular Velocity - x: {angular_velocity_x}, y: {angular_velocity_y}, z: {angular_velocity_z}')
        self.get_logger().info(f'Acceleration - x: {acceleration_x} m/s^2')
        self.get_logger().info(f'Position - x: {position_x}, y: {position_y}, z: {position_z}')
        self.get_logger().info(f'Orientation - x: {orientation_x}, y: {orientation_y}, z: {orientation_z}, w: {orientation_w}')

    def steering_cb(self, msg):
        steering = msg.steering

        # print
        self.get_logger().info(f'steering: {steering}')

    def timer_callback(self):
        msg = HostVehicleFilter()
        msg.vx = 10.0  # 예제 속도
        msg.yawrate = 0.1  # 예제 각속도
        msg.ax = 0.2  # 예제 가속도
        msg.sas = 0.3  # 예제 핸들각

        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: {msg}')

def main(args=None):
    rclpy.init(args=args)
    host_vehicle_publisher = HostVehiclePublisher()
    rclpy.spin(host_vehicle_publisher)
    host_vehicle_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
