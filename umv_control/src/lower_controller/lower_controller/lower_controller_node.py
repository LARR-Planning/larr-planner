import rclpy
from rclpy.node import Node
from umv_msgs.msg import AcuCmd
from airsim_interfaces.msg import CarControls

class AcuCmdSubscriber(Node):

    def __init__(self):
        super().__init__('lower_controller_node')
        self.subscription = self.create_subscription(AcuCmd,'/acu_cmd',self.acu_cmd_callback,10)
        self.subscription  # prevent unused variable warning

        self.publisher_ = self.create_publisher(CarControls, '/airsim_node/PhysXCar/car_cmd', 10)

    def acu_cmd_callback(self, msg):
        self.get_logger().info(f'Subscribed AcuCmd data: ax={msg.ax}, sas={msg.sas}')
        
        # Create CarControls message need to change
        car_controls_msg = CarControls()
        car_controls_msg.throttle = 1.0#msg.ax*10  
        car_controls_msg.brake = 0.0        
        car_controls_msg.steering = 1.0#msg.sas*10  

        # Publish CarControls message
        self.publisher_.publish(car_controls_msg)
        self.get_logger().info(f'Published CarControls data: throttle={car_controls_msg.throttle}, brake={car_controls_msg.brake}, steering={car_controls_msg.steering}')

def main(args=None):
    rclpy.init(args=args)
    acu_cmd_subscriber = AcuCmdSubscriber()
    rclpy.spin(acu_cmd_subscriber)
    acu_cmd_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
