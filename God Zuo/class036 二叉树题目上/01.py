# 二叉树的层序遍历
# Binary tree level order traversal
# 测试链接 : https://leetcode.cn/problems/binary-tree-level-order-traversal/
# Test link: https://leetcode.cn/problems/binary-tree-level-order-traversal/

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 提交时把方法名改为levelOrder，此方法为普通bfs，此题不推荐
# Ordinary BFS, not recommended for this problem
def levelOrder1(root):
    ans = []
    if root:
        queue = []
        levels = {}
        queue.append(root)
        levels[root] = 0
        while queue:
            cur = queue.pop(0)
            level = levels[cur]
            if len(ans) == level:
                ans.append([])
            ans[level].append(cur.val)
            if cur.left:
                queue.append(cur.left)
                levels[cur.left] = level + 1
            if cur.right:
                queue.append(cur.right)
                levels[cur.right] = level + 1
    return ans

# 提交时把方法名改为levelOrder，此方法为每次处理一层的优化bfs，此题推荐
# Optimized BFS processing one level at a time, recommended for this problem
def levelOrder2(root):
    ans = []
    if root:
        queue = [root]
        while queue:
            size = len(queue)
            level_list = []
            for _ in range(size):
                cur = queue.pop(0)
                level_list.append(cur.val)
                if cur.left:
                    queue.append(cur.left)
                if cur.right:
                    queue.append(cur.right)
            ans.append(level_list)
    return ans