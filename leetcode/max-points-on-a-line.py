import math
from typing import List
from collections import Counter

class Solution:
    def get_ab_raw(p0, p1):
        # y = ax + b
        # a = (y1 - y0) / (x1 - x0)
        # b = y - ax
        if p0[0] > p1[0]:
            p = p0
            p0 = p1
            p1 = p
        if p1[0] != p0[0]:
            dy, dx = p1[1] - p0[1], p1[0] - p0[0]
            a = dy / dx
            b = p0[1] - a * p0[0]
        else:
            a = float("inf")
            b = p0[0]
        print(p0, p1, " => ", a, b)
        return a, b
    def get_ab(p0, p1):
        # y = ax + b
        # a = (y1 - y0) / (x1 - x0)
        # b = y - ax
        if p0[0] > p1[0]:
            p = p0
            p0 = p1
            p1 = p
        if p1[0] != p0[0]:
            dy, dx = p1[1] - p0[1], p1[0] - p0[0]
            gcd = math.gcd(dx, dy)
            a = dx / gcd, dy / gcd
            divisor = dx
            dividende = dx * p0[1] - dy * p0[0]
            gcd = math.gcd(divisor, dividende)
            b = divisor / gcd, dividende / gcd
        else:
            a = float("inf")
            b = p0[0]
        print(p0, p1, " => ", a, b)
        return a, b
    def maxPoints0(self, points: List[List[int]]) -> int:
        if len(points) < 3:
            return len(points)
        ret = 2
        for idx, p0 in enumerate(points[:-1]):
            counter = Counter()
            print(p0)
            for p1 in points[idx+1:]:
                a, b = Solution.get_ab(p0, p1)
                # print("p0 %s - p1 %s => %f, %f" % (p0, p1, a, b))
                # if a != float("inf"):
                # counter[(int(a * 10000), int(b*10000))] += 1
                # else:
                counter[(a, b)] += 1
                # p0 = points[idx]
            ret = max(counter.most_common(1)[0][1] + 1, ret)
            print(ret)
            return ret
            #print(counter)
        #print(ret)
    def get_slope(dx, dy):
        if dx < 0:
            dx = -dx
            dy = -dy
        elif dx == 0:
            dy = dy if dy > 0 else -dy  
        gcd = math.gcd(dx, dy)
        return dy / gcd, dx / gcd

    def maxPoints(self, points: List[List[int]]) -> int:
        if len(points) < 3:
            return len(points)
        ret = 2
        for idx, p0 in enumerate(points[:-1]):
            if ret >= len(points) - idx:
                break
            counter = Counter()
            for p1 in points[idx+1:]:
                slope = Solution.get_slope(p0[0] - p1[0], p0[1] - p1[1])
                # print(p0, p1, " => ", slope)
                counter[slope] += 1
            # print(counter.most_common(1))
            ret = max(counter.most_common(1)[0][1] + 1, ret)
        return ret


def check_solution():
    s = Solution()
    points = [[1,1],[2,2],[3,3]]
    assert(s.maxPoints(points) == 3)

    points = [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
    assert(s.maxPoints(points) == 4)

    points = [[1,1],[3,2],[5,1],[4,1],[2,1],[-1,1]]
    assert(s.maxPoints(points) == 5)

    points = [[6,1],[6,2],[6,3],[6,4],[6,0],[-1,1]]
    assert(s.maxPoints(points) == 5)

    points = [[3,3],[1,4],[1,1],[2,1],[2,2]]
    assert(s.maxPoints(points) == 3)

    points = [[54,153],[1,3],[0,-72],[-3,3],[12,-22],[-60,-322],[0,-5],[-5,1],[5,5],[36,78],[3,-4],[5,0],[0,4],[-30,-197],[-5,0],[60,178],[0,0],[30,53],[24,28],[4,5],[2,-2],[-18,-147],[-24,-172],[-36,-222],[-42,-247],[2,3],[-12,-122],[-54,-297],[6,-47],[-5,3],[-48,-272],[-4,-2],[3,-2],[0,2],[48,128],[4,3],[2,4]]
    # import matplotlib.pyplot as plt
    # import numpy as np
    # xaxis = np.array([x for x, y in points[:10]])
    # yaxis = np.array([y for x, y in points[:10]])
    # plt.scatter(xaxis, yaxis)
    # plt.show()
    assert(s.maxPoints(points) == 18)

check_solution()