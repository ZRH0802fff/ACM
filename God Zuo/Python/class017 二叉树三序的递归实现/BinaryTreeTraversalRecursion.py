# 递归序的解释
# 用递归实现二叉树的三序遍历

class TreeNode:
    def __init__(self, val=0):
        self.val = val
        self.left = None
        self.right = None


# 递归基本样子，用来理解递归序
def f(head):
    if not head:
        return
    # 1
    f(head.left)
    # 2
    f(head.right)
    # 3


# 先序打印所有节点，递归版
def pre_order(head):
    if not head:
        return
    print(head.val, end=" ")
    pre_order(head.left)
    pre_order(head.right)


# 中序打印所有节点，递归版
def in_order(head):
    if not head:
        return
    in_order(head.left)
    print(head.val, end=" ")
    in_order(head.right)


# 后序打印所有节点，递归版
def pos_order(head):
    if not head:
        return
    pos_order(head.left)
    pos_order(head.right)
    print(head.val, end=" ")


# 测试代码
if __name__ == "__main__":
    # 构建与 Java 版本相同的测试树
    #       1
    #     /   \
    #    2     3
    #   / \   / \
    #  4   5 6   7
    
    head = TreeNode(1)
    head.left = TreeNode(2)
    head.right = TreeNode(3)
    head.left.left = TreeNode(4)
    head.left.right = TreeNode(5)
    head.right.left = TreeNode(6)
    head.right.right = TreeNode(7)

    print("先序遍历（递归版）: ", end="")
    pre_order(head)
    print("\n")

    print("中序遍历（递归版）: ", end="")
    in_order(head)
    print("\n")

    print("后序遍历（递归版）: ", end="")
    pos_order(head)
    print("\n")