from collections import Counter

class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        # 1. 统计每个字符在字符串中的出现频次（C 级别底层优化，极快）
        # 对应 Java 版的 cnts 数组
        cnts = Counter(s)
        
        # 2. 记录当前已经在栈里的字符，用 set 可以做到 O(1) 的极速查重
        # 对应 Java 版的 enter 数组
        enter = set()
        
        # 原生动态列表模拟单调栈
        stack = []
        
        for cur in s:
            # 无论当前字符最终是否进栈，只要我们遍历过了，它在后续的剩余可用频次就得减 1
            cnts[cur] -= 1
            
            # 如果字符已经在这个递增栈里了，直接跳过
            if cur not in enter:
                # 核心单调栈逻辑：
                # a. 栈不为空
                # b. 栈顶元素的字典序 > 当前元素的字典序 (出现了逆序)
                # c. 栈顶元素在后面还会出现 (剩余频次 > 0)，现在弹出去以后还能捡回来
                while stack and stack[-1] > cur and cnts[stack[-1]] > 0:
                    # 把原本的栈顶元素出栈，并从 enter 集合中注销
                    enter.remove(stack.pop())
                    
                # 经过前面的肃清，当前字符可以安全入栈了
                stack.append(cur)
                enter.add(cur)
                
        # 将栈中的字符拼接成最终的字符串
        return "".join(stack)