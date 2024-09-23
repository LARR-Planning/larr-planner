import matplotlib.pyplot as plt

if __name__ == "__main__":
    with open('fuckfuck.txt', 'r') as file:
        # 파일의 각 라인 읽기
        lines = file.readlines()
        traj_cnt = 0
        
        # 라인 단위로 출력
        for line in lines:
            traj_cnt = int(line.strip())
            break
        
        print(traj_cnt)
        # 1 // x
        # 2 // y
        print(lines[1].strip())
        print(lines[2].strip())
        print(type(lines[1].strip()))
        
        plt.plot([0, 1e10], [10, 10], 'k-', linewidth=2)
        plt.plot([0, 1e10], [-3, -3], 'k-', linewidth=2)
        # traj_cnt = 10000
        for i in range(0, traj_cnt, 250):
            xs = (lines[i * 3 + 1].strip()).split()
            ys = (lines[i * 3 + 2].strip()).split()
            
            for j in range(30):
                xs[j] = float(xs[j])
                ys[j] = float(ys[j])
            
            # print(xs)
            # print(ys)
            # break
            plt.plot(xs, ys, linewidth=0.7)


        plt.xlim([0, 40])      # X축의 범위: [xmin, xmax]
        plt.ylim([-1, 8])     # Y축의 범위: [ymin, ymax]
        plt.show()
