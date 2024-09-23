import rclpy
from rclpy.node import Node
from umv_msgs.msg import AcuCmd
from airsim_interfaces.msg import CarControls
from umv_msgs.msg import HostVehicleFilter
import math
import copy
# import longiController



EPSILON_GENERAL = 0.0000001


class DiscreteDerivative:
    def __init__(self):
        self.data_pre = 0.0
        self.input_pre = 0.0
        self.time_pre = 0.0

    def getResult(self, input, currtime):
        if  abs(currtime - self.time_pre_) < EPSILON_GENERAL or currtime < 0:
            result = self.data_pre_
        else:
            self.data_pre_ = (input - self.input_pre_) / (currtime - self.time_pre_)
            self.input_pre_ = input
            self.time_pre_ = currtime
            result = self.data_pre_

        return result

class DiscreteIntegrator:
    def __init__(self, _initial = 0.0):
        self.initial_condition_ = _initial
        self.data_pre_ = 0.0
        self.time_pre_ = 0.0

    def getResult(self, input, currtime, isReset):
        if isReset == True :
            if self.data_pre_ != None: 
                self.data_pre_ = self.initial_condition_
            if self.time_pre_ != None: 
                self.time_pre_ = currtime
                
            result = self.data_pre_
        
        else:
            if abs(currtime - self.time_pre_) < EPSILON_GENERAL or currtime < 0:
                result = self.data_pre_
            else:
                self.data_pre_ = self.data_pre_ + input * (currtime - self.time_pre_)
                self.time_pre_ = currtime
                result = self.data_pre_
            
        return result


class LookupTable:
    def __init__(self, i_tarr=None, i_xarr=None, n=0):
        self.num_ = n
        self.t_arr_ = None
        self.x_arr_ = None
        
        try:
            if i_tarr != None:
                self.t_arr_ = copy.deepcopy(i_tarr)
            if i_xarr != None:
                self.x_arr_ = copy.deepcopy(i_xarr)
        except:
            self.t_arr = None
            self.x_arr = None


    def getTableData(self, time):
        if self.t_arr_ != None and self.x_arr_ != None:
                if self.num_ > 0:
                    result = 0.0

                    if time <= self.t_arr_[0]:
                        result = self.x_arr_[0]
                    elif time >= self.t_arr_[self.num_ - 1]:
                        result = self.x_arr_[self.num_ - 1]
                    else:
                        for i in range(1, self.num_):
                            if time > self.t_arr_[i - 1] and time <= self.t_arr_[i]:
                                result = self.x_arr_[i - 1] + (self.x_arr_[i] - self.x_arr_[i - 1]) / (self.t_arr_[i] - self.t_arr_[i - 1]) * (time - self.t_arr_[i - 1]);
                            
                    return result
                
                else: 
                    return 0.0
            
        else:
                return 0.0 


class LongiController:
    def __init__(self):
        self.ax_des_ = 0.0
        self.vx_current_ = 0.0

        self.throttle_out_ = 0.0
        self.brake_out_ = 0.0

        self.ax_current_ = 0.0
        self.u_min_ = 0.00001 # control input limit for unnecessary small input rejection

        self.u_zero_throttle_ = 0.0

        self.delta_t_ = 0.0
        self.curr_time_ = -1.0
        self.runCount_ = 0

        self.ctrl_mode_ = 0 # 0 : idle, 1 : throttle, -1 : brake

        self.lookup_table_zero_throttle_ = LookupTable()

        self.error_integrator_ = DiscreteIntegrator(0.0)
        #error_derivative_ = new DiscreteDerivative();

        self.Kff_gain_ = 0.1*2.2
        self.KP_gain_ = 0.3*self.Kff_gain_
        self.KI_gain_ = 1.0*0.65*self.Kff_gain_


    def initialize(self, _delta_t):
        if abs(_delta_t) > EPSILON_GENERAL:
            self.delta_t_ = _delta_t
            self.runCount_ = 0
            self.curr_time_ = -1.0
        
        else:
        # add exception catch code here
        # set zero-throttle table
        # double table_x[5] = { 0/3.6, 25.35/3.6, 48/3.6, 66.1/3.6, 74.8/3.6};
        # double table_y[5] = { 0.0, 0.025, 0.05, 0.075, 0.1};
            table_x = [0, 0.04913, 1.0633, 2.4654, 3.6424, 4.9136, 5.0585, 6.0321, 8.7852, 11.3513, 13.9345, 16.7328, 20.0745]
            table_y = [0.0, 0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60]
            self.lookup_table_zero_throttle_.setTableData(table_x, table_y, 13)


    def calcSaturation(self, _input, _upperlimit, _lowerlimit):
        if _input >= _upperlimit:
            return _upperlimit
        elif _input <= _lowerlimit:
            return _lowerlimit
        else:
            return _input


    def calcEquivalentControlInput(self):
        self.u_zero_throttle_ = self.lookup_table_zero_throttle_.getTableData(self.vx_current_)
    
    
    def calcThrottleBrakeValue(self):
        error = self.ax_des_ - self.ax_current_
        u_feedforward = self.u_zero_throttle_


        # double u_feedback = KI_gain_ * error_integrator_->getResult(error, curr_time_, false) + KP_gain_ * error_derivative_->getResult(error, curr_time_);
        u_feedback = self.KI_gain_ * self.error_integrator_.getResult(error, self.curr_time_, False) + self.KP_gain_ * error + self.Kff_gain_ * self.ax_des_
        u_total = u_feedforward + u_feedback

        # printf("u feedforward : [%f], u feedback : [%f]\n", u_feedforward, u_feedback);
        # printf("u total : [%f], ctrl_mode : [%d]\n", u_total, ctrl_mode_);

        #  switching algorithm
        throttle = 0.0
        brake = 0.0

        if self.ctrl_mode_ == 1:
            if u_total > self.u_min_:
                throttle = u_total
                brake = 0
            elif u_total < -1*self.u_min_:
                self.ctrl_mode_ = -1
                throttle = 0
                brake = 0
            else:
                self.ctrl_mode_ = 0; 
                throttle = 0
                brake = 0
        
        elif self.ctrl_mode_ == -1:
            if u_total > self.u_min_:
                self.ctrl_mode_ = 1
                throttle = 0
                brake = 0
            elif u_total < -1 * self.u_min_:
                throttle = 0
                brake = -1 * u_total
            else:
                self.ctrl_mode_ = 0	
                throttle = 0
                brake = 0
        
        elif self.ctrl_mode_ == 0:
            if u_total > self.u_min_:
                self.ctrl_mode_ = 1
            elif u_total < -1 * self.u_min_:
                self.ctrl_mode_ = -1
            throttle = 0
            brake = 0
        else:
            self.ctrl_mode_ = 1 # default mode -> throttle
            throttle = 0
            brake = 0

        self.throttle_out_ = self.calcSaturation(throttle, 1.0, 0.0)
        thr_brk_ratio = 0.2
        self.brake_out_ = self.calcSaturation( thr_brk_ratio * brake, 1.0, 0.0)


    def setInput(self, _ax_des, _ax_current, _vx_current):
        self.ax_des_ = self.calcSaturation(_ax_des, 1.5, -5.0)
        self.ax_current_ = self.calcSaturation(_ax_current, 10.0, -10.0)
        self.vx_current_ = self.calcSaturation(_vx_current, 100 / 3.6, 0 / 3.6)

        if self.curr_time_ < 0.0:
            self.curr_time_ = 0.0
        else:
        # time advance
            self.curr_time_ = self.curr_time_ + self.delta_t_
            # calc equivalent control input
            self.calcEquivalentControlInput()
            self.calcThrottleBrakeValue()


        if self.vx_current_ < 0.05 and self.ax_des_ > 0.1: #  stop and go situation
            self.error_integrator_.getResult(0, self.curr_time_, True) # reset integrator

        if self.vx_current_ < 0.05 and self.ax_des_ > 0.1 and self.runCount_ < 1: # stop and go situation
            self.runCount_ = self.runCount_ + 1
        elif self.vx_current_ < 0.05 and self.ax_des_ > 0.1 and self.runCount_ >= 1:
            self.error_integrator_.getResult(0, self.curr_time_, True) # reset integrator
            self.runCount_ = 0
        else:
            self.runCount_ = 0
        


    def getThrottle(self):
        return self.calcSaturation(self.throttle_out_, 1.0, 0.0)
    
    def getBrake(self):
        # double brake_gain = 1.5; // 0~1 normalized value -> set control input gain
        brake_gain = 1.0 # 0~1 normalized value -> set control input gain
        return brake_gain * self.calcSaturation(self.brake_out_, 1.0, 0.0)



class lgsvl_output_node(Node):
    def acu_cmd_callback(self, msg):
        self.get_logger().info(f'Subscribed AcuCmd data: ax={msg.ax}, sas={msg.sas}')
        self.D_Ax = msg.ax
        self.D_FSA = -1 * msg.sas * self.deg2rad / 3.5


    def hvf_cmd(self, msg):
        self.vx_curr = msg.vx 
        self.ax_curr = msg.ax   


    def __init__(self):
        super().__init__('lower_controller_node')
        self.subscription = self.create_subscription(AcuCmd,'/acu_cmd',self.acu_cmd_callback,10)
        self.subscription  # prevent unused variable warning

        self.subscription = self.create_subscription(HostVehicleFilter,'/host_vehicle_filter_msg',self.hvf_cmd,10)
        self.subscription  # prevent unused variable warning

        self.publisher_ = self.create_publisher(CarControls, '/airsim_node/PhysXCar/car_cmd', 10)

        #need to change
        timer_period = 0.025  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)

        self.myController = None

        self.rad2deg = 180/math.pi
        self.deg2rad = math.pi / 180.0
        self.vx_curr = 0.0
        self.ax_curr = 0.0
        self.u_final = 0.0
        self.throttle_out = 0.0
        self.brake_out = 0.0
        self.D_Ax = 0.0
        self.D_FSA = 0.0
        self.Ax = 0.0
        self.FSA = 0.0
        self.p_Ax = 0.0
        self.p_FSA = 0.0
        self.ax_IMU_current = 0.0
        self.ax_IMU_pre = 0.0
        self.vx_pre = 0.0
        self.TC_lat = 0.02
        self.TC_long = 0.2
        self.T_period = 0.04
        self.M_FSA = 34.9
        
        self.auto_on = True ################################################################################################
        self.lkas_on = True
        self.acc_on = True
        self.initflag = False
        self.stop_signal = False

        self.msg = CarControls()



    def calc(self):
        #ax(1-order) & FSA(2-order) command with Delay model
        self.Ax = self.p_Ax * self.TC_long/(self.T_period + self.TC_long) + self.D_Ax * self.T_period/(self.T_period + self.TC_long)
        self.FSA = self.p_FSA * self.TC_lat/(self.T_period + self.TC_lat) + self.D_FSA * self.T_period/(self.T_period + self.TC_lat)

        #FSA = ((1-TC_lat*T_period)*p_FSA + (1-T_period*T_period)*D_FSA)/(2 - TC_lat*T_period - T_period*T_period);

        # without Delay
        # Ax = D_Ax;
        # FSA = D_FSA[0];

        # Set imu sensor result with low pass filter
        # ax_IMU_current = ax_IMU_pre*TC_long/(T_period+TC_long) + ax_curr*T_period/(T_period+TC_long);
        # ax_IMU_pre = ax_curr;

        # ax estimation : 230404 Dabin
        self.ax_IMU_current = 0.8 * self.ax_IMU_pre + 0.2 * (self.vx_curr - self.vx_pre)/0.04
        self.ax_IMU_pre = self.ax_IMU_current
        self.vx_pre = self.vx_curr


    
    def setset(self, throttle_out, brake_out):
        # final vehicle control command
        # msg.gear = 64;
        # msg.ctrl_cmd.linear_acceleration = u_final;
        # msg.ctrl_cmd.steering_angle = -FSA*rad2deg/M_FSA;
        if self.stop_signal == True:
            self.msg.throttle = 0.0
            self.msg.brake = 0.7
        
        elif self.auto_on == True and self.acc_on == True:
            self.msg.throttle = throttle_out
            self.msg.brake = brake_out
        else:
            self.msg.throttle = 0.0
            self.msg.brake = 0.3
        
        if self.auto_on == True and self.lkas_on == True:
            # msg.steer = -FSA*rad2deg/M_FSA;
            self.msg.steering = -self.FSA * self.rad2deg / self.M_FSA # * 15/12;
        else:
            self.msg.steering = 0.0
        
        #store previous step data
        self.p_Ax = self.Ax
        self.p_FSA = self.FSA



    def timer_callback(self):
        deltaT = 0.025

        if self.initflag == True:
            # Ax = 0;
            # ax_IMU_current = 0;
            # vx_curr = 0;
            print("###########################################################################")
            del self.myController
            self.myController = LongiController()
            self.myController.initialize(deltaT)
            
        else:
            print("----------------------------------------------------------------------------")
            self.calc()
            print("self.Ax: ", self.Ax)
            print("self.ax_IMU_current: ", self.ax_IMU_current)
            print("self.vx_curr: ", self.vx_curr)

            #longitudinal control(calculate pedal input)
            self.myController.setInput(self.Ax, self.ax_IMU_current, self.vx_curr)
            throttle_out = self.myController.getThrottle()
            brake_out = self.myController.getBrake()
            print("throttle_out: ", throttle_out)
            print("brake_out: ", brake_out)

            #printf("throttle : [%f], brake : [%f]\n\n", throttle_out, brake_out);
            # u_final = throttle_out - brake_out
            self.setset((throttle_out), (brake_out))
            # Create CarControls message need to change

            self.publisher_.publish(self.msg)
            # Publish CarControls message
            self.get_logger().info(f'Published CarControls data: throttle={self.msg.throttle}, brake={self.msg.brake}, steering={self.msg.steering}')




def main(args=None):
    rclpy.init(args=args)

    acu_cmd_subscriber = lgsvl_output_node()
    acu_cmd_subscriber.myController = LongiController()
    deltaT = 0.025
    acu_cmd_subscriber.myController.initialize(deltaT)
    rclpy.spin(acu_cmd_subscriber)
    acu_cmd_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
