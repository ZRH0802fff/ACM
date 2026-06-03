class ListNode:
    def __init__(self,val=0,next=None):
        self.val=val
        self.next=next

def f(arr):
    head=ListNode(arr[0])
    cur=head
    for val in arr[1:]:
        cur.next=ListNode(val)
        cur=cur.next
    return head
def findidxval(head,i):
    cur=head
    count=1
    while cur:
        if count==i:
            return cur.val
        cur=cur.next
        count+=1
arr=[1,2,3]
h1=f(arr)
print(h1.val)
print(h1.next.next.val)
print(findidxval(h1,1))
print(findidxval(h1,2))