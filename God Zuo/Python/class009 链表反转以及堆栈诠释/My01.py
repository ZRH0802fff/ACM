class ListNode():
    def __init__(self,val=0,next=None):
        self.val=val
        self.next=next

    def reverseList(self,head):
        if not head:
            return
        pre=None
        while head:
            nxt=head.next
            head.next=pre
            pre=head
            head=nxt
        return head
