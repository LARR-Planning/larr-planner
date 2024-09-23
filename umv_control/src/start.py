import airsim
import numpy as np

# connect to the AirSim simulator
client = airsim.VehicleClient()
client.confirmConnection()

# set vehicle pose with Unreal Engine coordinates
# TODO : type the Unreal Engine coordinates
unreal_x = 38 #-95 #38 
unreal_y = -158  #27 #-158 
unreal_yaw = 90 #0 #90 # clockwise from the north, left-handed coordinate system

# set the pose
x = unreal_x #/100
y = unreal_y #/100
yaw = unreal_yaw/180.0*np.pi
client.simSetVehiclePose(airsim.Pose(airsim.Vector3r(x, y, 0), airsim.to_quaternion(0, 0, yaw)), True)
