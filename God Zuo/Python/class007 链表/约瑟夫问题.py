class CircularLiseNode:
    def __init__(self,x):
        self.val=x
        self.next=None

def appand_node(head,val):
    if head is None:
        return
    cur=head
    while cur.next is not head:
        cur=cur.next
    new_node=CircularLiseNode(val)
    cur.next=new_node
    new_node.next=head

def print_node(head):
    if head is None:
        return
    cur=head.next
    if cur is head:
        print(cur.val)
        return
    print(head.val,end="\t")
    while cur is not head:
        print(cur.val,end="\t")
        cur=cur.next
    print()

#删除操作，删除第K个节点，并返回删除节点的val
def remove_node(head,k):
    if head is None or head.next is head:
        return head
    if k==0:
        cur = head
        while cur.next is not head:
            cur=cur.next 
        cur.next=head.next
        return head
    cur=head
    for i in range(k-1):
        cur= cur.next
    tmp=cur.next
    cur.next=cur.next.next
    return tmp

if __name__=='__main__':
    n,m=41,3
    head=CircularLiseNode(1)
    head.next=head
    for i in range(1,n):
        appand_node(head,i+1)
    print_node(head)
    f=''
    for j in range(n):
        node=remove_node(head,m-1)
        f+=str(node.val)+' '
        head=node.next
    print(f)