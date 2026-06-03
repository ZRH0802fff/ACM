class ListNode:
    def __init__(self,val=0,next=None):
        self.val=val
        self.next=next

class Solution:
    def mergeTwoLists(self, head1: ListNode, head2: ListNode) -> ListNode:
        if not head1 or not head2:
            return head2 if not head1 else head1
        if head1.val<=head2.val:
            head=head1
            cur1=head1.next
            cur2=head2
        else:
            head=head2
            cur1=head1
            cur2=head2.next
        
        pre =head
        while cur1 and cur2:
            if cur1.val<=cur2.val:
                pre.next=cur1
                cur1=cur1.next
            else:
                pre.next=cur2
                cur2=cur2.next
            pre = pre .next
        pre.next=cur1 if cur1 else cur2
        return head
        