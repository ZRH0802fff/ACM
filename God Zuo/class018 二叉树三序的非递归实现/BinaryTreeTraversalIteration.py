from typing import List, Optional


class TreeNode:
    def __init__(self, val=0):
        self.val = val
        self.left = None
        self.right = None


# 先序遍历（迭代版） - 打印
def pre_order(head: Optional[TreeNode]) -> None:
    if not head:
        return
    
    stack = []
    stack.append(head)
    
    while stack:
        node = stack.pop()
        print(node.val, end=" ")
        if node.right:
            stack.append(node.right)
        if node.left:
            stack.append(node.left)
    print()


# 中序遍历（迭代版） - 打印
def in_order(head: Optional[TreeNode]) -> None:
    if not head:
        return
    
    stack = []
    cur = head
    
    while stack or cur:
        if cur:
            stack.append(cur)
            cur = cur.left
        else:
            cur = stack.pop()
            print(cur.val, end=" ")
            cur = cur.right
    print()


# 后序遍历 - 双栈法（打印）
def pos_order_two_stacks(head: Optional[TreeNode]) -> None:
    if not head:
        return
    
    stack = []
    collect = []
    stack.append(head)
    
    while stack:
        node = stack.pop()
        collect.append(node)
        if node.left:
            stack.append(node.left)
        if node.right:
            stack.append(node.right)
    
    while collect:
        print(collect.pop().val, end=" ")
    print()


# 后序遍历 - 单栈法（较复杂但只用一个栈）（打印）
def pos_order_one_stack(h: Optional[TreeNode]) -> None:
    if not h:
        return
    
    stack = []
    stack.append(h)
    last_printed = None   # 记录上一次打印的节点
    
    while stack:
        cur = stack[-1]  # peek
        
        # 左孩子存在 且 左孩子和右孩子都没处理过
        if cur.left and last_printed != cur.left and last_printed != cur.right:
            stack.append(cur.left)
        # 右孩子存在 且 右孩子没处理过
        elif cur.right and last_printed != cur.right: 
            stack.append(cur.right)
        else:
            # 左右都处理完了（或都没有）
            print(cur.val, end=" ")
            last_printed = stack.pop()
    
    print()


# ─────────────── LeetCode 风格 返回列表的版本 ───────────────

def preorder_traversal(root: Optional[TreeNode]) -> List[int]:
    ans = []
    if not root:
        return ans
    
    stack = [root]
    while stack:
        node = stack.pop()
        ans.append(node.val)
        if node.right:
            stack.append(node.right)
        if node.left:
            stack.append(node.left)
    return ans


def inorder_traversal(root: Optional[TreeNode]) -> List[int]:
    ans = []
    stack = []
    cur = root
    
    while stack or cur:
        if cur:
            stack.append(cur)
            cur = cur.left
        else:
            cur = stack.pop()
            ans.append(cur.val)
            cur = cur.right
    return ans


def postorder_traversal_two_stacks(root: Optional[TreeNode]) -> List[int]:
    ans = []
    if not root:
        return ans
    
    stack = [root]
    collect = []
    
    while stack:
        node = stack.pop()
        collect.append(node)
        if node.left:
            stack.append(node.left)
        if node.right:
            stack.append(node.right)
    
    while collect:
        ans.append(collect.pop().val)
    
    return ans


def postorder_traversal_one_stack(root: Optional[TreeNode]) -> List[int]:
    ans = []
    if not root:
        return ans
    
    stack = [root]
    last = None
    
    while stack:
        cur = stack[-1]
        if cur.left and last != cur.left and last != cur.right:
            stack.append(cur.left)
        elif cur.right and last != cur.right:
            stack.append(cur.right)
        else:
            ans.append(cur.val)
            last = stack.pop()
    
    return ans


# 测试代码
if __name__ == "__main__":
    # 构造测试树
    #       1
    #     /   \
    #    2     3
    #   / \   / \
    #  4   5 6   7
    
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.left = TreeNode(6)
    root.right.right = TreeNode(7)

    print("先序（迭代）   :", end=" ")
    pre_order(root)

    print("中序（迭代）   :", end=" ")
    in_order(root)

    print("后序（双栈）   :", end=" ")
    pos_order_two_stacks(root)

    print("后序（单栈）   :", end=" ")
    pos_order_one_stack(root)

    print("\nLeetCode 风格返回列表：")
    print("前序:", preorder_traversal(root))
    print("中序:", inorder_traversal(root))
    print("后序(双栈):", postorder_traversal_two_stacks(root))
    print("后序(单栈):", postorder_traversal_one_stack(root))