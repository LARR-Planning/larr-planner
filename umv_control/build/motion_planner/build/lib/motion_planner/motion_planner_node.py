import rclpy
from rclpy.node import Node
from airsim_interfaces.msg import CarState
from airsim_interfaces.msg import CarControls
from umv_msgs.msg import GlobalPath
from umv_msgs.msg import LocalRefPath
import math

class MotionPlanner(Node):

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
        
        #no need after algorithm
        timer_period = 0.1  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.prev_linear_velocity_x = None  # before linear velocity
        self.prev_time = self.get_clock().now()  # before step time

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

    def global_path_callback(self, msg):
        global_xs = msg.global_xs
        global_ys = msg.global_ys
        distance_interval = msg.distance_interval

        # print
        self.get_logger().info(f'Global Path X coordinates: {global_xs}')
        self.get_logger().info(f'Global Path Y coordinates: {global_ys}')
        self.get_logger().info(f'Distance Interval: {distance_interval}')


    def timer_callback(self):
        # LocalRefPath msg
        local_ref_path_msg = LocalRefPath()
        local_ref_path_msg.local_ref_xs = [0.0]  #ex
        local_ref_path_msg.local_ref_ys = [0.0]  #ex
        local_ref_path_msg.local_ref_ss = [0.0]  #ex
        local_ref_path_msg.local_ref_yaws = [0.0]  #ex
        local_ref_path_msg.local_ref_curvs = [0.0]  #ex
        local_ref_path_msg.ey = 0.0  #ex
        local_ref_path_msg.eyaw = 0.0  #ex
        local_ref_path_msg.ego_s = 0.0  #ex

        self.local_ref_path_publisher.publish(local_ref_path_msg)
        self.get_logger().info(f'Published LocalRefPath: {local_ref_path_msg}')

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
