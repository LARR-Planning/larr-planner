import numpy as np
import pickle
import os
import matplotlib.pyplot as plt

# define the topology
# intersections' idx : 0 ~ 19
# roads' idx : 0 ~ 71
in_lists = [
    [1, 4, 12], # 0
    [3,6,10], # 1
    [5,8], # 2
    [9,19,20,24], # 3
    [21,22,30,16,15], # 4
    [11,13,14], # 5
    [17,18,32], # 6
    [31,35,36,55], # 7
    [39,40,29,33,34,53], # 8
    [27,51,38, 37], # 9
    [23,26,28], # 10 
    [7,25,69], # 11
    [50,64,65,71], # 12
    [67,66,52,60,61], # 13
    [62,63,49,57,56], # 14
    [54,58,59,47], # 15
    [48,45], # 16
    [46,0,43], # 17
    [44,70,41], # 18
    [42,68] # 19
]

out_lists = [
    [2,3,11], # 0
    [4,5,9], # 1 
    [6,7], # 2
    [10,23,21,22], # 3
    [19,20,29,17,18], # 4
    [16,15,12], # 5
    [31,13,14], # 6
    [54,33,34,32], # 7
    [52,30,35,36,38,37], # 8
    [28,50,40,39], # 9
    [24,25,27], # 10
    [8,26,68], # 11
    [51, 66,67,70], # 12
    [65,64,53,62,63], # 13
    [60,61,0,59,58], # 14
    [55,56,57,48], # 15
    [47,46], # 16
    [45,49,44], # 17
    [43,71,42], # 18
    [41,69] # 19
]

out_all = []
in_all = []
for i in out_lists:
    for j in i:
        out_all.append(j)
        
for i in in_lists:
    for j in i:
        in_all.append(j)

out_all.sort()
in_all.sort()

# print(out_all)
# print(in_all)
if out_all[2:] != in_all[2:]:
    print("Error: the intersection and road indices are not matched")
    print(out_all)
    print(in_all)
else:
    print("The intersection and road indices are matched")

USE_AIRSIM = False # if false, load the dictionary from the file


if USE_AIRSIM:
    ############### BY AIRSIM ###############
    import airsim
    client = airsim.VehicleClient()
    client.confirmConnection()

    # get all Pawn* objects
    objs = client.simListSceneObjects("Pawn.*")
    print("Number of objects: ", len(objs))

    pawn_dict = {}
    for obj in objs:
        pawn_dict[obj] = client.simGetObjectPose(obj).position

    # save the dictionary
    if os.path.exists("pawn_dict.pkl"):
        import time
        time_date = time.strftime("%Y%m%d_%H%M%S")
        print("Save the dictionary in new file: ", time_date)
        with open("pawn_dict_"+time_date+".pkl", "wb") as f:
            pickle.dump(pawn_dict, f)
    else:
        with open("pawn_dict.pkl", "wb") as f:
            pickle.dump(pawn_dict, f)

else:
    ############### Without AirSim ################
    # load the dictionary
    with open("pawn_dict.pkl", "rb") as f:
        pawn_dict = pickle.load(f)

    ############################################

def plot_topology(pawn_dict, in_lists, out_lists):
        # flip the axis
    plt.gca().invert_yaxis() # NOTE : beware of this line!!!! unreal uses left-handed coordinate system
    plt.gca().set_aspect('equal', adjustable='box')

    # draw the topology
    for idx in range(72):
        key = "Pawn" + str(idx)
        xs = pawn_dict[key+"s"].x_val
        ys = pawn_dict[key+"s"].y_val
        plt.plot(xs, ys, 'ro')
        plt.text(xs, ys, key+"s", fontsize=9)
        xe = pawn_dict[key+"e"].x_val
        ye = pawn_dict[key+"e"].y_val
        plt.plot(xe, ye, 'ro')
        plt.text(xe, ye, key+"e", fontsize=9)
        plt.plot([xs, xe], [ys, ye], 'b-')

    for idx_inter in range(len(out_lists)):
        cur_in = in_lists[idx_inter]
        cur_out = out_lists[idx_inter]
        poses = np.zeros((len(cur_in)*2, 2))
        for idx, i in enumerate(cur_in):
            poses[idx] = [pawn_dict["Pawn"+str(i)+"e"].x_val, pawn_dict["Pawn"+str(i)+"e"].y_val]
            
        for idx, i in enumerate(cur_out):
            poses[idx+len(cur_in)] = [pawn_dict["Pawn"+str(i)+"s"].x_val, pawn_dict["Pawn"+str(i)+"s"].y_val]
        
        # draw the intersection with rectangle
        min_x = np.min(poses[:,0])
        max_x = np.max(poses[:,0])
        min_y = np.min(poses[:,1])
        max_y = np.max(poses[:,1])
        plt.plot([min_x, max_x], [min_y, min_y], 'g-')
        plt.plot([min_x, max_x], [max_y, max_y], 'g-')
        plt.plot([min_x, min_x], [min_y, max_y], 'g-')
        plt.plot([max_x, max_x], [min_y, max_y], 'g-')
        plt.text((min_x+max_x)/2, (min_y+max_y)/2, str(idx_inter), fontsize=12, color='b', fontweight='bold')

if __name__ == "__main__":

    plt.figure(figsize=(10,10))
    plot_topology(pawn_dict, in_lists, out_lists)
    plt.show()
        

