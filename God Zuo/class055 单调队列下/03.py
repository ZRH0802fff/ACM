class Solution:
    def maxTaskAssign(self, tasks: list[int], workers: list[int], pills: int, strength: int) -> int:
        # 1. 预处理排序：任务从易到难，工人从弱到强
        tasks.sort()
        workers.sort()
        
        tsize = len(tasks)
        wsize = len(workers)
        
        # 预分配定长数组模拟双端队列，存放当前可解锁任务的【索引】
        q = [0] * tsize 
        
        # 检查是否能完成 m 个任务
        def check(m: int) -> bool:
            if m == 0:
                return True
                
            h = t = 0
            cnt = 0
            j = 0  # 任务索引，范围限制在 [0, m-1]
            
            # 贪心原则 1：一定要完成 m 个任务，那必然是挑【最简单的 m 个任务】给【最强的 m 个工人】做
            # 遍历这最强的 m 个工人，从他们之中最弱的开始派活
            for i in range(wsize - m, wsize):
                worker = workers[i]
                
                # 步骤 A：把当前工人【不吃药】就能做的任务全部入队
                while j < m and tasks[j] <= worker:
                    q[t] = j
                    t += 1
                    j += 1
                    
                # 步骤 B：抉择
                # 如果队列中有任务，且当前工人不吃药就能做队头任务（最简单的任务）
                if h < t and tasks[q[h]] <= worker:
                    # 贪心原则 2：能不吃药就不吃药，并且优先消耗掉最简单的任务（队头出队）
                    # 把偏难的任务留给后面更强的工人
                    h += 1
                else:
                    # 必须吃药！把当前工人【吃了药】能做的任务也全部入队
                    while j < m and tasks[j] <= worker + strength:
                        q[t] = j
                        t += 1
                        j += 1
                        
                    if h < t:
                        # 贪心原则 3：既然吃了宝贵的药，就一定要发挥最大价值，去做能做的【最难的任务】（队尾出队）
                        # 这样可以把相对简单的任务省下来，留给后面没有药的工人
                        cnt += 1
                        t -= 1
                    else:
                        # 吃了药都一个任务也做不了，说明 m 达不到，直接剪枝
                        return False
                        
            # 最后检查使用的药丸数量是否超标
            return cnt <= pills

        # 2. 二分答案求最大完成数
        ans = 0
        l = 0
        r = min(tsize, wsize)
        
        while l <= r:
            mid = (l + r) // 2
            if check(mid):
                ans = mid
                l = mid + 1  # 尝试挑战更多的任务
            else:
                r = mid - 1
                
        return ans