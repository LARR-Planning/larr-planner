#!/usr/bin/env python
import rospy
import copy

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