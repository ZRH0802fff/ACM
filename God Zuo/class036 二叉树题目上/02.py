# 二叉树的锯齿形层序遍历
# 测试链接 : https://leetcode.cn/problems/binary-tree-zigzag-level-order-traversal/

# 不提交这个类
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# 提交以下的方法
# 用每次处理一层的优化bfs就非常容易实现
# 如果测试数据量变大了就修改这个值，但Python动态无需
def zigzagLevelOrder(root):
    ans = []
    if root:
        queue = []
        l = 0
        queue.append(root)
        r = len(queue)
        # false 代表从左往右
        # true 代表从右往左
        reverse = False 
        while l < r:
            size = r - l
            level_list = []
            # reverse == false, 左 -> 右， l....r-1, 收集size个
            # reverse == true,  右 -> 左， r-1....l, 收集size个
            # 左 -> 右, i = i + 1   
            # 右 -> 左, i = i - 1
            start = r - 1 if reverse else l
            step = -1 if reverse else 1
            i = start
            for k in range(size):
                cur = queue[i]
                level_list.append(cur.val)
                i += step
            for i in range(size):
                cur = queue[l]
                l += 1
                if cur.left:
                    queue.append(cur.left)
                if cur.right:
                    queue.append(cur.right)
            r = len(queue)
            ans.append(level_list)
            reverse = not reverse
    return ans