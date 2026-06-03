class Solution:
    def totalSteps(self, nums: list[int]) -> int:
        # stack 存放元组 (鱼的体重, 彻底消除右侧较小元素所需的轮数)
        stack = []
        ans = 0
        
        # 倒序遍历数组：从右向左处理
        for i in range(len(nums) - 1, -1, -1):
            cur_turns = 0
            
            # 当栈不为空，且当前鱼的体重 > 栈顶鱼的体重时，说明可以吃掉栈顶
            while stack and stack[-1][0] < nums[i]:
                popped_weight, popped_turns = stack.pop()
                
                # 核心状态转移公式：
                # 当前鱼每吃一条小鱼，基础轮数 + 1 (cur_turns += 1)
                # 但如果被吃的小鱼自身也花了很多轮去吃别人 (popped_turns)，
                # 当前大鱼就必须等小鱼消化完，也就是取两者的最大值。
                cur_turns += 1
                if popped_turns > cur_turns:
                    cur_turns = popped_turns
            
            # 当前鱼和它的轮数入栈
            stack.append((nums[i], cur_turns))
            
            # 记录全局最大轮数
            if cur_turns > ans:
                ans = cur_turns
                
        return ans