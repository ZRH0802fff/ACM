class CircularListLind:
    def __init__(self,x):
        self.val=x
        self.next=None

def appand_node(head,val):
    if head is None:
        return 
    cur = head
    while cur.next is not head:
        cur =cur.next
    new_node=CircularListLind(val)
    cur.next=new_node
    new_node.next=head

def print_node(head):
    if head is None:
        return
    cur = head.next
    if head is cur :
        print(cur.val)
        return
    print(head.val,end="\t")
    while cur is not head:
        print(cur.val,end="\t")
        cur=cur.next
    print()

def delete_node(head):
    if head is None or head is head.next:
        return head
    cur =head
    while cur.next.next is not head:
        cur=cur.next
    cur.next=head


if __name__=="__main__":
    root=CircularListLind(10)
    root.next=root
    appand_node(root,11)
    appand_node(root,12)
    appand_node(root,13)
    appand_node(root,14)

    print_node(root)

    delete_node(root)
    print_node(root)
