class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Codec:
    def __init__(self):
        # 最大节点数限制（可以根据需要调整）
        self.MAXN = 10001
        self.queue = [None] * self.MAXN

    def serialize(self, root: TreeNode) -> str:
        if not root:
            return ''
        builder=[]
        l,r=0,0
        builder.append(str(root.val) + ',')
        self.quque[r]=root
        r+=1
        while l<r :
            cur=self.queue[l]
            l+=1
            if cur.left:
                builder.append(str(cur.left.val)+',')
                self.queue[r]=cur.left
                r+=1
            else:
                builder.append("#,")
            if cur.right:
                builder.append(str(cur.right.val) + ",")
                self.queue[r] = cur.right
                r += 1
            else:
                builder.append("#,")   
        return ''.join(builder)

    def deserialize(self, data: str) -> TreeNode:
        if not data:
            return None
        nodes=data.split(',')
        if nodes[-1]=='':
            nodes.pop()
        idx=0
        root=self._generate(nodes[idx])
        idx+=1
        if not root :
            return None
        l,r=0,0
        self.queue[r]=root
        r+=1
        while l<r:
            cur=self.queue[l]
            l+=1
            cur.left=self._generate(nodes[idx])
            idx+=1
            if cur.left:
                self.queue[r]=cur.left
                r+=1
            cur .right=self._generate(nodes[idx])
            idf+=1
            if cur.right :
                self.queue[r]=cur.right
                r+=1
        return root
                
    
    def _generate(self, val: str) -> TreeNode | None:
        return None if val=='#' else TreeNode(int(val))