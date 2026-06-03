import random
import sys
from functools import cache
from typing import List

# 增加递归深度，防止 DP 验证时爆栈
sys.setrecursionlimit(200000)

class CutOrPoison:
    
    # =========================================================
    # 方法一：动态规划验证法 (仅供对数器验证使用)
    # 利用 Python 自带的 @cache 装饰器，实现极简的记忆化搜索
    # =========================================================
    @staticmethod
    def fast1(cuts: List[int], poisons: List[int], hp: int) -> int:
        n = len(cuts)
        
        # @cache 会自动帮我们记录 (i, r, p) 的返回值，相当于省去了 Java 里的 dp[][][] 数组
        @cache
        def dp(i: int, r: int, p: int) -> int:
            # 回合开始，先扣除之前累加的毒药伤害
            r -= p
            if r <= 0:
                return i + 1
                
            # 如果回合已经用完，但怪兽还没死
            if i == n:
                if p == 0:
                    # 没有中毒，怪兽永远死不掉了
                    return float('inf')
                else:
                    # 中毒了，计算还需要几回合毒死它 (向上取整)
                    return n + 1 + (r + p - 1) // p
                    
            # 选择 1：刀砍
            p1 = (i + 1) if r <= cuts[i] else dp(i + 1, r - cuts[i], p)
            # 选择 2：毒杀 (毒药伤害累加到下回合)
            p2 = dp(i + 1, r, p + poisons[i])
            
            return min(p1, p2)
            
        ans = dp(0, hp, 0)
        dp.cache_clear()  # 跑完一次清理缓存，避免多组测试用例串内存
        return ans

    # =========================================================
    # 方法二：二分答案法 + 贪心 (最优解)
    # 时间复杂度 O(n * log(hp))，额外空间复杂度 O(1)
    # =========================================================
    @staticmethod
    def fast2(cuts: List[int], poisons: List[int], hp: int) -> int:
         
        # 内部辅助函数：如果强制要求在 limit 回合内击杀怪兽，能否做到？
        def check(limit: int) -> bool:
            # 最多只能操作 n 次，或者 limit 次（取决于谁更小）
            n = min(len(cuts), limit)
            current_hp = hp
            
            for i in range(n):
                j = i + 1  # 当前是第 j 回合 (从 1 开始)
                # 【核心贪心逻辑】：
                # 如果我们这回合选择刀砍，造成的伤害是 cuts[i]
                # 如果选择毒杀，它会在未来的 (limit - j) 个回合里，每回合造成 poisons[i] 的伤害
                # 既然它们互不干扰，我们贪心地选择两者中伤害更大的那一个即可！
                current_hp -= max(cuts[i], (limit - j) * poisons[i])
                
                if current_hp <= 0:
                    return True
            return False

        # 最少需要 1 回合
        l = 1
        # 最多需要 hp + 1 回合 (假设每回合只能打 1 滴血)
        r = hp + 1
        ans = float('inf')
        
        while l <= r:
            m = (l + r) // 2
            if check(m):
                ans = m
                r = m - 1  # 尝试寻找更短的回合数
            else:
                l = m + 1  # 杀不死，只能增加回合数
                
        return ans

# =========================================================
# 对数器测试 (验证两种方法结果是否一致)
# =========================================================
def main():
    print("测试开始")
    N = 30
    V = 20
    H = 300
    test_times = 10000
    
    for _ in range(test_times):
        n = random.randint(1, N)
        cuts = [random.randint(1, V) for _ in range(n)]
        poisons = [random.randint(1, V) for _ in range(n)]
        hp = random.randint(1, H)
        
        ans1 = CutOrPoison.fast1(cuts, poisons, hp)
        ans2 = CutOrPoison.fast2(cuts, poisons, hp)
        
        if ans1 != ans2:
            print("出错了!")
            print(f"cuts: {cuts}")
            print(f"poisons: {poisons}")
            print(f"hp: {hp}")
            print(f"ans1: {ans1}, ans2: {ans2}")
            break
    else:
        print("测试结束，结果完全正确！")

if __name__ == '__main__':
    main() 