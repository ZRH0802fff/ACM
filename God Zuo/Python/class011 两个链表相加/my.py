class ListNode:
    def __init__(self,val=0,next=None):
        self.val=val
        self.next=next

class Solution     :
    def addTwoNumbers(self, h1: ListNode, h2: ListNode) -> ListNode:
        ans=None
        cur=None
        cy=0
        while h1 or h2:
            sum=(h1.val if h1 else 0)+(h2.val if h2 else 0)+cy
            val=sum%10
            cy=sum/10
            if ans is None:
                ans=ListNode(val)
                cur=ans
            else:
                cur.next=ListNode(val)
                cur=cur.next
            if h1:
                h1=h1.next
            if h2:
                h2=h2.next
        
        if cy!=0:
            cur.next=ListNode(cy)
        return ans