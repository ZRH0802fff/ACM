class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution1:
    def isValidBST(self, root):
        if not root:
            return True
        
        stack = []
        pre = None
        
        while stack or root:
            # 一直向左走，把所有左子节点压栈
            while root:
                stack.append(root)
                root = root.left
            
            # 弹出栈顶（当前最左节点）
            root = stack.pop()
            
            # 检查是否递增（BST 中序遍历必须严格递增）
            if pre is not None and pre.val >= root.val:
                return False
            
            pre = root
            # 转向右子树
            root = root.right
        
        return True
    
class Solution2:
    def isValidBST(self, root):
        """
        递归方式：每个节点返回自己子树的最小值和最大值
        同时检查：左子树 max < 当前值 < 右子树 min
        """
        if not root:
            return True
        
        # 用类属性记录子树范围（类似 Java 的 static min/max）
        self.min_val = float('inf')
        self.max_val = float('-inf')
        
        def dfs(node):
            if not node:
                self.min_val = float('inf')
                self.max_val = float('-inf')
                return True
            
            left_ok = dfs(node.left)
            lmin, lmax = self.min_val, self.max_val
            
            right_ok = dfs(node.right)
            rmin, rmax = self.min_val, self.max_val
            
            # 更新当前子树的 min 和 max
            self.min_val = min(lmin, rmin, node.val)
            self.max_val = max(lmax, rmax, node.val)
            
            # 检查当前节点是否满足 BST 性质
            return (left_ok and right_ok and
                    lmax < node.val and node.val < rmin)
        
        return dfs(root)