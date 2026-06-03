class Solution:
    def numSubmat(self, mat: list[list[int]]) -> int:
        n = len(mat)
        m = len(mat[0])
        
        # 记录压缩后的直方图高度
        height = [0] * m
        ans = 0
        
        for i in range(n):
            # 1. 数组压缩：更新以当前行为底的直方图高度
            for j in range(m):
                if mat[i][j] == 0:
                    height[j] = 0
                else:
                    height[j] += 1
            
            # 2. 内联单调栈逻辑：计算当前直方图中全 1 子矩形的数量
            stack = []
            for j in range(m):
                while stack and height[stack[-1]] >= height[j]:
                    cur = stack.pop()
                    
                    # 核心去重逻辑：如果出栈的高度和当前高度相等，不结算！
                    # 因为相等的柱子我们把它留到最后一个遇到的时候再统一结算，避免重复计算
                    if height[cur] > height[j]:
                        left = stack[-1] if stack else -1
                        length = j - left - 1
                        
                        # 获取左边界的高度
                        left_h = height[left] if left != -1 else 0
                        # 底部基准线高度，取左右边界高度的较大值 (手写 if 替代 max 进行常数优化)
                        bottom = left_h if left_h > height[j] else height[j]
                        
                        # 结算当前高度片段能组成的所有子矩形数量
                        # 数量 = 高度差 * 底边所有可能的线段组合数
                        ans += (height[cur] - bottom) * length * (length + 1) // 2
                        
                stack.append(j)
                
            # 清理依然在栈中的元素
            while stack:
                cur = stack.pop()
                left = stack[-1] if stack else -1
                length = m - left - 1
                
                # 因为是最后清算，右侧没有限制（相当于右侧高度为 0），所以 bottom 就是左侧的高度
                left_h = height[left] if left != -1 else 0
                
                ans += (height[cur] - left_h) * length * (length + 1) // 2
                
        return ans