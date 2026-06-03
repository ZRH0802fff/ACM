from typing import List

class Solution:
    def corpFlightBookings(self, bookings: List[List[int]], n: int) -> List[int]:
        # 使用差分数组（差分技巧），长度为 n+2 防止越界
        cnt = [0] * (n + 2)
        
        # 步骤1：对每个预订记录进行差分标记
        for first, last, seats in bookings:
            cnt[first] += seats
            cnt[last + 1] -= seats
        
        # 步骤2：计算前缀和，得到每个航班的实际预订座位数
        for i in range(1, len(cnt)):
            cnt[i] += cnt[i - 1]
        
        # 步骤3：提取答案（航班编号从1到n，对应cnt[1]到cnt[n]）
        ans = [0] * n
        for i in range(n):
            ans[i] = cnt[i + 1]
        
        return ans


# ==================== 测试示例 ====================
if __name__ == "__main__":
    solution = Solution()
    
    # 示例 1
    bookings1 = [[1, 2, 10], [2, 3, 20], [2, 5, 25]]
    n1 = 5
    print(solution.corpFlightBookings(bookings1, n1))  
    # 输出: [10, 55, 45, 25, 25]
    
    # 示例 2
    bookings2 = [[1, 2, 10], [2, 2, 15]]
    n2 = 2
    print(solution.corpFlightBookings(bookings2, n2))  
    # 输出: [10, 25]