class ListNode:
    def __init__(self,val=0,next=None):
        self.val=val
        self.next=next

def f (lists: list[ListNode]) -> ListNode:
    import heapq
    heap=[]
    for i , node in enumerate(lists):
        if node :
            heapq.heappush(heap,(node.val,i,node))
    if not heap:
        return None
    dummy=ListNode(0)
    tail=dummy
    while heap:
        val , i , node=heapq.heappop(heap)
        tail.next=node
        tail=tail.next
        if node.next:
            heapq.heappush(heap,(node.next.val,i,node.next))
    return dummy.next