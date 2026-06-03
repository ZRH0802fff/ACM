from collections import Counter

class Solution:
    def balancedString(self, s: str) -> int:
        n = len(s)
        req = n // 4  # 平衡状态下每个字符应该出现的次数
        
        # 统计原字符串中各字符的频次
        counts = Counter(s)
        
        cnts = {}
        debt = 0
        
        # 计算每种字符的“欠债”情况
        for char in "QWER":
            if counts[char] > req:
                # 只有出现次数多于 req 的字符，才是我们需要“替换掉”的
                # 用负数表示还需要被替换的数量（负债）
                cnts[char] = req - counts[char]
                debt -= cnts[char]  # 累加总负债数量
            else:
                # 出现次数 <= req 的字符，不用刻意替换，欠债为 0
                cnts[char] = 0
                
        # 如果一开始就没有负债，说明本身就是平衡的
        if debt == 0:
            return 0
            
        ans = float('inf')
        l = 0
        
        # 滑动窗口开始遍历
        for r, char in enumerate(s):
            # 右边界向右扩，遇到我们需要替换的字符，偿还负债
            if cnts[char] < 0:
                debt -= 1
            cnts[char] += 1
            
            # 当窗口内包含了所有需要替换的溢出字符（总负债清零）
            if debt == 0:
                # 尝试收缩左边界，把盈余的无用字符踢出窗口
                while cnts[s[l]] > 0:
                    cnts[s[l]] -= 1
                    l += 1
                
                # 记录满足条件的最小替换子串长度
                ans = min(ans, r - l + 1)
                
        return ans
    

# ======================================================================
# 🌟 核心知识点复习：collections.Counter (超级计数器)
# ======================================================================
# 1. 它是啥？
#    它是 Python 标准库中专门用来“统计频率/计数”的数据结构，本质是 dict 的子类。
# 
# 2. 它和 defaultdict(int) 的区别？
#    - defaultdict(int) : 只是不报错并默认返回 0，但遍历累加的 for 循环还得你自己写。
#    - Counter          : 不仅不报错，还把底层“遍历 + 累加”的过程全封装好了，一行搞定。
# 
# 3. 算法竞赛 / 刷题四大神技：
#    (1) 一行完成统计：
#        cnt = Counter("aaabbc")  # -> {'a': 3, 'b': 2, 'c': 1}
#    
#    (2) 安全访问（免除 KeyError）：
#        cnt['z']                 # 如果键不存在，直接返回 0，程序绝不会崩溃。
#    
#    (3) 秒杀众数 / Top K 问题：
#        cnt.most_common(2)       # 直接返回频率最高的前 2 个元素：[('a', 3), ('b', 2)]
#    
#    (4) 支持数学运算（差集、并集）：
#        Counter("aab") - Counter("ab")  # -> {'a': 1}，直接做词频抵消！
# ======================================================================