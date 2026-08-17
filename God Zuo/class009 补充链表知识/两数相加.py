class ListNode:
    def __init__(self,value):
        self.val=value
        self.next=None

def two_num_and(head1,head2):
    f1,f2='',''
    cur1=head1
    cur2=head2
    
    while cur1 is not None:
        f1+=str(cur1.val)
        cur1=cur1.next
    while cur2 is not None:
        f2+=str(cur2.val)
        cur2=cur2.next
    f=int(f1[::-1])+int(f2[::-1])
    return f

if __name__=='__main__':
    head1=ListNode(2)
    head1.next=ListNode(3)
    head2=ListNode(1)
    head2.next=ListNode(2)
    f=two_num_and(head1,head2)
    ff=list(map(int,str(f)))
    print(ff)