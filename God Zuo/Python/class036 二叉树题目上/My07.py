class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def build_tree(pre, ino):
    if not pre or not ino or len(pre)!=len(ino):
        return None
    #enumerate() 是 Python 的内置函数，
    # 它接收一个可迭代对象（如列表 inorder），返回一个枚举对象。
    # 这个枚举对象每次迭代时产生一个元组：(索引, 元素)，其中索引从 0 开始。
    # 例如，如果 inorder = [4, 2, 5, 1, 3]，
    # 则 enumerate(inorder) 会产生：
    # (0, 4)
    # (1, 2)
    # (2, 5)
    # (3, 1)
    # (4, 3)
    book={val:idx for idx, val in enumerate(ino)}
    def f (l1,r1,l2,r2):
        if l1>r1:
            return None
        head=TreeNode(pre[l1])
        k=book[pre[l1]]
        head.left=f(l1+1,l1+k-l2,l2,k-1)
        head.right=f(l1+k-l2+1,r1,k+1,r2)
        return head
    return f(0,len(pre)-1,0,len(ino)-1)