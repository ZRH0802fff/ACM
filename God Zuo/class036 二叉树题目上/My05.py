class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Codec:

    def serialize(self, root: TreeNode) -> str:
        s=[]
        self._serialize(root , s)
        return ','.join(s)
        
    def _serialize(self, root: TreeNode, s: list):
        if root is None:
            s.append('#')
        else:
            s.append(str(root.val))
            self._serialize(root.left,s)
            self._serialize(root.right , s)
    def deserialize(self, data: str) -> TreeNode:
        if not data:
            return None
        vals=data.split(',')
        self.index=0
        return self._deserialize(vals)
    
    def _deserialize(self, vals: list) -> TreeNode:
        val=vals[self.index]
        self.index+=1
        if val=='#':
            return None
        
        node=TreeNode(int(val))
        node.left=self._deserialize(vals)
        node.right=self._deserialize(vals)
        return node