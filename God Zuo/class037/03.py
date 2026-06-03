class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def pathSum(self, root, targetSum):
        """
        题目：找出所有从根到叶子节点的路径，使得路径上节点值之和等于 targetSum
        返回：所有满足条件的路径（每条路径用列表表示）
        
        思路：DFS + 回溯
        1. 用一个 path 列表记录当前从根到当前节点的路径
        2. 用 current_sum 记录当前路径的和（优化：不用每次 sum(path)）
        3. 到达叶子节点时检查 current_sum 是否等于 targetSum
        4. 找到有效路径时，把 path 复制一份加入答案（因为 path 会回溯修改）
        5. 递归结束后回溯：弹出当前节点
        
        时间复杂度：O(N)，每个节点访问一次
        空间复杂度：O(H) 递归栈 + 路径长度，最坏 O(N)
        """
        # 存放所有满足条件的路径
        result = []
        
        def dfs(node, current_sum, path):
            # 边界：空节点直接返回
            if not node:
                return
            
            # --------------------
            # 1. 选择：把当前节点加入路径
            # --------------------
            path.append(node.val)
            current_sum += node.val   # 更新当前路径和
            
            # --------------------
            # 2. 判断是否到达叶子节点且满足条件
            # --------------------
            if not node.left and not node.right:  # 是叶子节点
                if current_sum == targetSum:
                    # 找到一条有效路径，复制当前 path 加入结果
                    # 注意：必须用 path[:] 复制，不能直接 append(path)
                    result.append(path[:])
            
            # --------------------
            # 3. 递归：向左右子树继续探索
            # --------------------
            if node.left:
                dfs(node.left, current_sum, path)
            if node.right:
                dfs(node.right, current_sum, path)
            
            # --------------------
            # 4. 回溯：撤销选择，恢复现场
            # --------------------
            path.pop()
            # 注意：这里不需要减 current_sum，因为它是值传递，下层不会影响上层
        
        # 从根节点开始 DFS
        if root:
            dfs(root, 0, [])
        
        return result