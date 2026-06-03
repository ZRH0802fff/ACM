class ListNode:
    def __init__(self,value):
        self.val=value
        self.next=None

def insert_node(node,value):
    if node is None:
        return
    new_node=ListNode(value)
    cur=node
    while cur.next is not None:
        cur=cur.next
    cur.next=new_node

def print_node(node):
    cur=node
    while cur is not None:
        print(cur.val,end="\t")
        cur=cur.next
    print()

if __name__=='__main__':
    root=ListNode(10)
    insert_node(root,20)
    insert_node(root,30)
    insert_node(root,40)
    print_node(root)