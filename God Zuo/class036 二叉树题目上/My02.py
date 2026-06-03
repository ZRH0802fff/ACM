class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def zigzagLevelOrder(root):
        ans = []
        if root:
            queue = [root]
            # false 代表从左往右
            # true 代表从右往左
            reverse = False 
            while queue:
                size = len(queue)
                level_list = []
                # reverse == false, 左 -> 右， 0....size-1, 收集size个
                # reverse == true,  右 -> 左， size-1....0, 收集size个
                if not reverse:
                    for i in range(size):
                        level_list.append(queue[i].val)
                else:
                    for i in range(size - 1, -1, -1):
                        level_list.append(queue[i].val)
                for _ in range(size):
                    cur = queue.pop(0)
                    if cur.left:
                        queue.append(cur.left)
                    if cur.right:
                        queue.append(cur.right)
                ans.append(level_list)
                reverse = not reverse
        return ans