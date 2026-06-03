# 二叉树的最大特殊宽度
# 测试链接 : https://leetcode.cn/problems/maximum-width-of-binary-tree/

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    # 提交以下的方法
    # 用每次处理一层的优化bfs就非常容易实现
    # 如果测试数据量变大了就修改这个值
    MAXN = 3001

    def widthOfBinaryTree(self, root: TreeNode) -> int:
        if not root:
            return 0
        nq = [None] * self.MAXN
        iq = [0] * self.MAXN
        l = 0
        r = 0
        nq[r] = root
        iq[r] = 1
        r += 1
        ans = 1
        while l < r:
            size = r - l
            ans = max(ans, iq[r - 1] - iq[l] + 1)
            for i in range(size):
                node = nq[l]
                cur_id = iq[l]
                l += 1
                if node.left:
                    nq[r] = node.left
                    iq[r] = cur_id * 2
                    r += 1
                if node.right:
                    nq[r] = node.right
                    iq[r] = cur_id * 2 + 1
                    r += 1
        return ans