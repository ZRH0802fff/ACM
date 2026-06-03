# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def is_complete_tree(root: TreeNode) -> bool:
    """
    判断一棵二叉树是否是完全二叉树
    LeetCode: https://leetcode.cn/problems/check-completeness-of-a-binary-tree/
    """
    if not root:
        return True

    # 使用列表作为队列（Python 中 list 做队列效率可接受，小规模数据无问题）
    queue = []
    queue.append(root)

    # 是否已经遇到过“不再双全”的节点（即进入了最后一层或接近最后一层的阶段）
    leaf = False

    while queue:
        node = queue.pop(0)  # 出队（队头）

        # 情况1：有右孩子但没有左孩子 → 非法
        # 情况2：已经进入“叶节点阶段”，但当前节点还有孩子 → 非法
        if (node.left is None and node.right is not None) or \
           (leaf and (node.left is not None or node.right is not None)):
            return False

        # 入队左右孩子（如果存在）
        if node.left:
            queue.append(node.left)
        if node.right:
            queue.append(node.right)

        # 一旦发现当前节点不是“左右孩子都存在”，后面就不能再有任何孩子了
        if node.left is None or node.right is None:
            leaf = True

    return True
