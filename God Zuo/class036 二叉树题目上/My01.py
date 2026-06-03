class TreeNode:
    def __init__(self,val=0,left=0,right=0):
        self.val=val
        self.left=left
        self.right=right

def levelOrder1(root):
    ans=[]
    if root:
        quque=[]
        levels={}
        quque.append(root)
        levels[root]=0
        while quque:
            cur=quque.pop(0)
            level=levels[cur]
            if len(ans)==level:
                ans.append([])
            ans[level].append(cur.val)
            if cur.left:
                quque.append(cur.left)
                levels[cur.left]=level+1
            if cur.right:
                quque.append(cur.right)
                level[cur.right]=level+1
    return ans
def levelotder2(root):
    ans=[]
    if root:
        quque=[root]
        while quque :
            size=len(quque)
            leve_list=[]
            for _ in range(size):
                cur=quque.pop(0)
                leve_list.append(cur.val)
                if cur.left:
                    quque.append(cur.left)
                if cur.right:
                    quque.append(cur.right)
            ans.append(leve_list)
    return ans