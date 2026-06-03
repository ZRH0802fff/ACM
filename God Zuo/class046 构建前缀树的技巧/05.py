from typing import List

def longestWPI(hours: List[int]) -> int:
    # 某个前缀和，最早出现的位置
    prefix_map = {0: -1}   # sum -> 最早出现的下标
    ans = 0
    total = 0
    
    for i in range(len(hours)):
        # 劳累一天记 +1，不劳累记 -1
        total += 1 if hours[i] > 8 else -1
        
        if total > 0:
            # 当前整个前缀就是表现良好的（劳累天数 > 不劳累天数）
            ans = i + 1
        else:
            # 寻找是否存在前缀和为 total - 1 的最早位置
            if total - 1 in prefix_map:
                ans = max(ans, i - prefix_map[total - 1])
        
        # 只记录每个前缀和第一次出现的位置
        if total not in prefix_map:
            prefix_map[total] = i
    
    return ans


# ==================== 测试示例 ====================
if __name__ == "__main__":
    # 示例 1
    hours1 = [9, 9, 6, 0, 6, 6, 9]
    print(longestWPI(hours1))   # 输出: 3
    
    # 示例 2
    hours2 = [6, 6, 6]
    print(longestWPI(hours2))   # 输出: 0