import heapq
import random
from typing import List

class WaitingTime:
    
    # =========================================================
    # 方法一：堆模拟 (非最优解，仅供验证和小数据量使用)
    # 时间复杂度 O(m * log(n))，额外空间复杂度 O(n)
    # =========================================================
    @staticmethod
    def waitingTime1(arr: List[int], m: int) -> int:
        # 堆里存的是元组：(服务员下一次可用时间, 该服务员接待客人的耗时)
        # 一开始时间为 0，所有服务员都处于可用状态
        heap = [(0, time) for time in arr]
        heapq.heapify(heap)
        
        # 模拟前面 m 个客人的等位分配
        for _ in range(m):
            available_time, service_time = heapq.heappop(heap)
            # 安排一个客人给当前最快空闲的服务员，更新他的下一次可用时间并重新入堆
            heapq.heappush(heap, (available_time + service_time, service_time))
            
        # 前面 m 个人都安排妥当了，下一个就是你（第 m+1 个人）
        # 此时堆顶服务员的可用时间，就是你需要等待的时间
        return heap[0][0]

    # =========================================================
    # 方法二：二分答案法 (最优解，应对 10^9 级别的 m)
    # 时间复杂度 O(n * log(min * m))，额外空间复杂度 O(1)
    # =========================================================
    @staticmethod
    def waitingTime2(arr: List[int], m: int) -> int:
        # 最快服务员的耗时
        min_time = min(arr)
        
        # 内部辅助函数：如果经过了 time 时间，所有服务员一共能接待多少位客人？
        def count_served(time: int) -> int:
            # time // num 表示服务员在这段时间内后续能接待的客人数
            # +1 是因为在第 0 时刻（刚开门），每个服务员都能立刻接客 1 人
            return sum((time // num) + 1 for num in arr)
            
        l = 0
        # 右边界（最差情况）：全场最快的那个服务员，一个人把前面的 m 个人全包了
        r = min_time * m
        ans = 0
        
        while l <= r:
            mid = (l + r) // 2
            
            # 有 m 个人在等位，你是第 m + 1 个人
            # 如果在 mid 时间内，能接待的人数 >= m + 1，说明 mid 时间或者更早，你就能吃上饭
            if count_served(mid) >= m + 1:
                ans = mid
                r = mid - 1  # 尝试寻找更短的等待时间
            else:
                l = mid + 1  # 接待人数不够，只能继续等
                
        return ans

# =========================================================
# 对数器测试 (用于验证两个算法结果是否严格一致)
# =========================================================
def main():
    print("测试开始")
    N = 50
    V = 30
    M = 3000
    test_time = 20000
    
    for _ in range(test_time):
        n = random.randint(1, N)
        # 随机生成服务员耗时数组
        arr = [random.randint(1, V) for _ in range(n)]
        m = random.randint(0, M)
        
        ans1 = WaitingTime.waitingTime1(arr, m)
        ans2 = WaitingTime.waitingTime2(arr, m)
        
        if ans1 != ans2:
            print(f"出错了! m={m}, arr={arr}")
            print(f"ans1={ans1}, ans2={ans2}")
            break
    else:
        # 如果 for 循环正常结束，没有触发 break
        print("测试结束，结果完全正确！")

if __name__ == '__main__':
    main()