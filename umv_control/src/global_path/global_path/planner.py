import numpy as np
import pickle
import os
import matplotlib.pyplot as plt
import networkx as nx
from dijkstras import Graph
from scipy.interpolate import BSpline, make_interp_spline, interp1d

class GlobalWrapper:
    def __init__(self, pawn_dict_filname="pawn_dict.pkl"):
        self.pawn_dict = self.load_pawn_dict(pawn_dict_filname)
        self.graph = None
        # in_lists와 out_lists를 정의해야 합니다.
        self.in_lists = [
        [1, 4, 12], # 0
        [3,6,10], # 1
        [5,8], # 2
        [9,19,24], # 3
        [22,30,16,15], # 4
        [11,13], # 5
        [18,32], # 6
        [31,36,55], # 7
        [40,29,33,53], # 8
        [27,51, 37], # 9
        [23,26,28], # 10 
        [7,25,69], # 11
        [50,64,71], # 12
        [67,52,60], # 13
        [63,49,56], # 14
        [54,59,47], # 15
        [48,45], # 16
        [46,0,43], # 17
        [44,70,41], # 18
        [42,68] # 19
        ]

        self.out_lists = [
            [2,3,11], # 0
            [4,5,9], # 1 
            [6,7], # 2
            [10,23,22], # 3
            [19,29,18], # 4
            [16,15,12], # 5
            [31,13], # 6
            [54,33,32], # 7
            [52,30,36,37], # 8
            [28,50,40], # 9
            [24,25,27], # 10
            [8,26,68], # 11
            [51,67,70], # 12
            [64,53,63], # 13
            [60,0,59], # 14
            [55,56,48], # 15
            [47,46], # 16
            [45,49,44], # 17
            [43,71,42], # 18
            [41,69] # 19
        ]
        # self.in_lists = [
        # [1, 4, 12], # 0
        # [3,6,10], # 1
        # [5,8], # 2
        # [9,19,20,24], # 3
        # [21,22,30,16,15], # 4
        # [11,13,14], # 5
        # [17,18,32], # 6
        # [31,35,36,55], # 7
        # [39,40,29,33,34,53], # 8
        # [27,51,38, 37], # 9
        # [23,26,28], # 10 
        # [7,25,69], # 11
        # [50,64,65,71], # 12
        # [67,66,52,60,61], # 13
        # [62,63,49,57,56], # 14
        # [54,58,59,47], # 15
        # [48,45], # 16
        # [46,0,43], # 17
        # [44,70,41], # 18
        # [42,68] # 19
        # ]

        # self.out_lists = [
        #     [2,3,11], # 0
        #     [4,5,9], # 1 
        #     [6,7], # 2
        #     [10,23,21,22], # 3
        #     [19,20,29,17,18], # 4
        #     [16,15,12], # 5
        #     [31,13,14], # 6
        #     [54,33,34,32], # 7
        #     [52,30,35,36,38,37], # 8
        #     [28,50,40,39], # 9
        #     [24,25,27], # 10
        #     [8,26,68], # 11
        #     [51, 66,67,70], # 12
        #     [65,64,53,62,63], # 13
        #     [60,61,0,59,58], # 14
        #     [55,56,57,48], # 15
        #     [47,46], # 16
        #     [45,49,44], # 17
        #     [43,71,42], # 18
        #     [41,69] # 19
        # ]
        self.create_graph_from_pawns(self.in_lists, self.out_lists)
        self.g = Graph()
        for node in self.graph.nodes:
            edges = {neighbor: self.graph[node][neighbor]['weight'] for neighbor in self.graph.neighbors(node)}
            self.g.add_vertex(node, edges)




    # pawn_dict.pkl 파일에서 데이터를 불러오는 함수
    def load_pawn_dict(self, filename="pawn_dict.pkl"):
        filename = os.path.join(os.path.dirname(__file__), 'pawn_dict.pkl')
        with open(filename, "rb") as f:
            pawn_dict = pickle.load(f)
        return pawn_dict

    # s -> e 방향의 노드 및 간선을 생성하는 함수
    def create_graph_from_pawns(self, in_lists, out_lists):
        graph = nx.DiGraph()  # 방향 그래프 생성

        for idx in range(72):  # 72개의 Pawn 객체 처리
            key = str(idx)
            s_node = f"{key}_s"
            e_node = f"{key}_e"

            # s 노드 좌표
            s_x = self.pawn_dict[f"Pawn{idx}s"].x_val
            s_y = self.pawn_dict[f"Pawn{idx}s"].y_val

            # e 노드 좌표
            e_x = self.pawn_dict[f"Pawn{idx}e"].x_val
            e_y = self.pawn_dict[f"Pawn{idx}e"].y_val

            # s 노드와 e 노드 간의 연결 (가중치는 거리로 설정)
            distance = np.sqrt((e_x - s_x) ** 2 + (e_y - s_y) ** 2)
            
            # 노드 및 간선 추가
            graph.add_node(s_node, pos=(s_x, s_y))
            graph.add_node(e_node, pos=(e_x, e_y))
            graph.add_edge(s_node, e_node, weight=distance)

        # Intersection 안의 노드들끼리 연결 (우회전/좌회전 제한)
        for idx, (in_nodes, out_nodes) in enumerate(zip(in_lists, out_lists)):
            for in_node in in_nodes:
                in_e_node = f"{in_node}_e"
                in_x = self.pawn_dict[f"Pawn{in_node}e"].x_val
                in_y = self.pawn_dict[f"Pawn{in_node}e"].y_val

                for out_node in out_nodes:
                    out_s_node = f"{out_node}_s"
                    out_x = self.pawn_dict[f"Pawn{out_node}s"].x_val
                    out_y = self.pawn_dict[f"Pawn{out_node}s"].y_val
                        
                    # 직진 가능 조건
                    if out_x == in_x or out_y == in_y or abs(out_y - in_y) < 2:
                        distance = np.sqrt((out_x - in_x) ** 2 + (out_y - in_y) ** 2)
                        if distance > 7 and not 13.9 < distance < 14.1 and not 9 < distance < 9.5:
                            graph.add_edge(in_e_node, out_s_node, weight=distance)

                    # 우회전 가능 조건 (오른쪽으로만)
                    elif (out_x > in_x) or (out_y < in_y):
                        distance = np.sqrt((out_x - in_x) ** 2 + (out_y - in_y) ** 2)
                        if not 4.6 < distance < 4.8:
                            graph.add_edge(in_e_node, out_s_node, weight=distance)

                    # 좌회전 가능 조건 (왼쪽으로만)
                    elif (out_x < in_x) or (out_y > in_y):
                        distance = np.sqrt((out_x - in_x) ** 2 + (out_y - in_y) ** 2)
                        if not 4.6 < distance < 4.8:
                            graph.add_edge(in_e_node, out_s_node, weight=distance)

        self.graph = graph

    # 그래프 시각화 함수
    def visualize_graph(self):
        pos = nx.get_node_attributes(self.graph, 'pos')
        edge_labels = nx.get_edge_attributes(self.graph, 'weight')

        plt.figure(figsize=(8, 8))
        nx.draw(self.graph, pos, with_labels=True, node_size=500, node_color='lightblue', font_size=8, font_weight='bold', edge_color='gray', arrowsize=20)
        nx.draw_networkx_edge_labels(self.graph, pos, edge_labels=edge_labels)
        plt.gca().invert_yaxis()  # Unreal 좌표계와 일치하도록 y축 반전
        plt.show()



    # 현재 노드와 다음 노드의 중점을 구하고, 그 중점에 수직인 선 위에 점을 추가하는 함수
    def calculate_perpendicular_control_point(self, x1, y1, x2, y2, factor=0.3, turn_direction='left'):
        """현재 노드와 다음 노드 사이의 중점에서 수직 방향으로 제어점을 생성하고,
        좌회전/우회전에 따라 케이스별로 제어점의 위치를 조정하는 함수"""
        
        # 현재 노드와 다음 노드의 중간점 계산
        cx = (x1 + x2) / 2
        cy = (y1 + y2) / 2

        # 두 점 사이의 벡터 계산
        dx = x1 - x2
        dy = y1 - y2

        # 기본 수직 벡터 계산
        perp_dx = -dy
        perp_dy = dx

        # 좌회전/우회전 방향과 x1, x2, y1, y2의 관계에 따라 4가지 케이스로 분류
        if turn_direction == 'left':
            if x1 > x2 and y1 > y2:  # Case 1: x1 > x2, y1 > y2
                control_x = cx - perp_dx * factor
                control_y = cy - perp_dy * factor
            elif x1 < x2 and y1 < y2:  # Case 2: x1 < x2, y1 < y2
                control_x = cx - perp_dx * factor
                control_y = cy - perp_dy * factor
            elif x1 > x2 and y1 < y2:  # Case 3: x1 > x2, y1 < y2
                control_x = cx - perp_dx * factor
                control_y = cy - perp_dy * factor
            elif x1 < x2 and y1 > y2:  # Case 4: x1 < x2, y1 > y2
                control_x = cx - perp_dx * factor
                control_y = cy - perp_dy * factor
        else:  # 우회전일 때
            if x1 > x2 and y1 > y2:  # Case 1: x1 > x2, y1 > y2
                control_x = cx + perp_dx * factor
                control_y = cy + perp_dy * factor
            elif x1 < x2 and y1 < y2:  # Case 2: x1 < x2, y1 < y2
                control_x = cx + perp_dx * factor
                control_y = cy + perp_dy * factor
            elif x1 > x2 and y1 < y2:  # Case 3: x1 > x2, y1 < y2
                control_x = cx + perp_dx * factor
                control_y = cy + perp_dy * factor
            elif x1 < x2 and y1 > y2:  # Case 4: x1 < x2, y1 > y2
                control_x = cx + perp_dx * factor
                control_y = cy + perp_dy * factor

        return control_x, control_y


    # 외적을 이용하여 좌회전과 우회전을 구분하는 함수
    def cross_product_direction(self, p1, p2, p3):
        """
        세 점의 좌표를 이용하여 외적을 계산하고,
        양수면 좌회전, 음수면 우회전으로 결정.
        """
        vector1 = [p2[0] - p1[0], p2[1] - p1[1]]  # p1 -> p2 벡터
        vector2 = [p3[0] - p1[0], p3[1] - p1[1]]  # p1 -> p3 벡터

        # 외적 계산 (2D에서 외적은 스칼라 값)
        cross_product = vector1[0] * vector2[1] - vector1[1] * vector2[0]
        
        return cross_product

    def bspline_interpolation(self, path, num_points=100):
        """각 연속된 두 점 사이에 B-spline을 적용하되, 좌회전/우회전을 고려하는 함수."""
        x_new = []
        y_new = []
        self.x_coords = []
        self.y_coords = []

        for node in path:
            if '_s' in node:
                key = node.replace('_s', '')
                self.x_coords.append(self.pawn_dict[f"Pawn{key}s"].x_val)
                self.y_coords.append(self.pawn_dict[f"Pawn{key}s"].y_val)
            elif '_e' in node:
                key = node.replace('_e', '')
                self.x_coords.append(self.pawn_dict[f"Pawn{key}e"].x_val)
                self.y_coords.append(self.pawn_dict[f"Pawn{key}e"].y_val)

        for i in range(len(self.x_coords) - 1):
            x_pair = self.x_coords[i:i+2]
            y_pair = self.y_coords[i:i+2]

            # 현재와 다음 노드 추출
            current_node = path[i]
            next_node = path[i + 1]

            # 현재 노드와 다음 노드의 좌표 설정
            if '_s' in current_node:
                current_x = self.pawn_dict[f"Pawn{current_node.replace('_s', '')}s"].x_val
                current_y = self.pawn_dict[f"Pawn{current_node.replace('_s', '')}s"].y_val
            else:
                current_x = self.pawn_dict[f"Pawn{current_node.replace('_e', '')}e"].x_val
                current_y = self.pawn_dict[f"Pawn{current_node.replace('_e', '')}e"].y_val

            if '_s' in next_node:
                next_x = self.pawn_dict[f"Pawn{next_node.replace('_s', '')}s"].x_val
                next_y = self.pawn_dict[f"Pawn{next_node.replace('_s', '')}s"].y_val
            else:
                next_x = self.pawn_dict[f"Pawn{next_node.replace('_e', '')}e"].x_val
                next_y = self.pawn_dict[f"Pawn{next_node.replace('_e', '')}e"].y_val

            if next_x-current_x==0:
                slope=999999
            else:
                slope = (next_y - current_y) / (next_x - current_x)  # 기울기 계산

            # 곡선 구간 확인: 좌회전/우회전 결정
            if next_x != current_x and next_y != current_y and (slope < -3 or slope > 3 or -1.5 <= slope <= 1.5):
                    # current_node의 e 좌표와 s 좌표, next_node 좌표를 사용해 외적 계산
                    p1 = [current_x, current_y]  # current_node 좌표
                    p2 = [self.pawn_dict[f"Pawn{current_node.replace('_s', '').replace('_e', '')}s"].x_val,
                        self.pawn_dict[f"Pawn{current_node.replace('_s', '').replace('_e', '')}s"].y_val]  # e 좌표
                    p3 = [next_x, next_y]  # next_node 좌표

                    cross_product = self.cross_product_direction(p1, p2, p3)
                    # breakpoint()

                    # 좌회전(양수) 또는 우회전(음수)에 따라 제어점 설정
                    if cross_product > 0:  # 좌회전
                        cx, cy = self.calculate_perpendicular_control_point(x_pair[0], y_pair[0], x_pair[1], y_pair[1], factor=0.25, turn_direction='left')
                        # breakpoint()
                    else:  # 우회전
                        cx, cy = self.calculate_perpendicular_control_point(x_pair[0], y_pair[0], x_pair[1], y_pair[1], factor=0.25, turn_direction='right')
                        # breakpoint()
            else:
                if x_pair[0] == x_pair[1]:
                    # x 값이 같을 때 y 값을 직접 처리
                    x_interpolated = np.linspace(x_pair[0], x_pair[1], num_points)
                    y_interpolated = np.linspace(y_pair[0], y_pair[1], num_points)
                    x_new.extend(x_interpolated)
                    y_new.extend(y_interpolated)
                else:
                    interp_func = interp1d(x_pair, y_pair, kind='linear')
                    x_interpolated = np.linspace(x_pair[0], x_pair[1], num_points)
                    y_interpolated = interp_func(x_interpolated)

                    x_new.extend(x_interpolated)
                    y_new.extend(y_interpolated)
                continue

            # B-spline 적용
            x_spline = np.array([x_pair[0], cx, x_pair[1]])
            y_spline = np.array([y_pair[0], cy, y_pair[1]])
            
            t = np.linspace(0, 1, len(x_spline))
            spline_x = make_interp_spline(t, x_spline, k=2)
            spline_y = make_interp_spline(t, y_spline, k=2)
            
            t_new = np.linspace(0, 1, num_points)
            x_interpolated = spline_x(t_new)
            y_interpolated = spline_y(t_new)
            x_new.extend(x_interpolated)
            y_new.extend(y_interpolated)

        return x_new, y_new


    def resample_by_distance(self, x_new, y_new, desired_distance=1.0):
        """주어진 x_new, y_new 좌표들을 1m 간격으로 보간하는 함수."""
        
        # 결과를 담을 새로운 리스트
        x_resampled = [x_new[0]]
        y_resampled = [y_new[0]]
        
        # 이전 좌표 초기화
        prev_x, prev_y = x_new[0], y_new[0]
        cumulative_distance = 0.0

        for i in range(1, len(x_new)):
            # 두 점 사이의 거리 계산
            dx = x_new[i] - prev_x
            dy = y_new[i] - prev_y
            distance = np.sqrt(dx ** 2 + dy ** 2)
            
            # 현재 거리에 누적
            cumulative_distance += distance
            
            # 누적 거리가 desired_distance 이상이면 점을 추가
            if cumulative_distance >= desired_distance:
                # 새로운 점 추가 (이 간격이 딱 맞도록 보간 가능)
                x_resampled.append(x_new[i])
                y_resampled.append(y_new[i])
                
                # 누적 거리 초기화
                cumulative_distance = 0.0
            
            # 다음 비교를 위해 이전 좌표 업데이트
            prev_x, prev_y = x_new[i], y_new[i]

        return np.array(x_resampled), np.array(y_resampled)
    
    def visualize_path(self, x_new, y_new):
        # 스플라인 그래프 시각화
        plt.figure(figsize=(10, 10))
        plt.plot(self.x_coords, self.y_coords, 'o', label="Original Points")
        plt.plot(x_new, y_new, '-', label="Interpolated Curve")
        plt.xlabel('X Coordinates')
        plt.ylabel('Y Coordinates')
        plt.legend()
        plt.gca().invert_yaxis()  # Unreal 좌표계와 일치하도록 y축 반전
        plt.show()

if __name__ == "__main__":
    # 그래프 생성
    planner = GlobalWrapper()
    start_node = '26_s'
    end_node = '15_s'
    # start_node = '49_s'
    # end_node = '8_e'
    # start_node = '68_s'
    # end_node = '66_e'
    # start_node = '22_s'
    # end_node = '14_s'
    path = planner.g.shortest_path(start_node, end_node) 
    # 두 지점마다 보간 수행
    x_new, y_new = planner.bspline_interpolation(path, num_points=1000)
    x_new, y_new = planner.resample_by_distance(x_new, y_new, desired_distance=1.0)
    planner.visualize_path(x_new, y_new)
