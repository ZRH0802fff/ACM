# 合并K个有序链表
# 测试链接：https://www.nowcoder.com/practice/65cfde9e5b9b4cf2b6bafa5f3ef33fa6

# Python 中链表节点定义
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


# 使用小根堆（优先队列）合并 k 个有序链表
def mergeKLists(lists: list[ListNode]) -> ListNode:
    if not lists:
        return None
    
    # Python 的 heapq 是小根堆，但它只能比较基本类型或实现了 __lt__ 的对象
    # 我们使用 (值, 节点) 元组来比较，因为 ListNode 本身没有定义 __lt__
    import heapq
    
    heap = []
    
    # 把所有非空链表的头节点放入堆中
    for node in lists:
        if node:
            heapq.heappush(heap, (node.val, node))
    
    if not heap:
        return None
    
    # 弹出第一个节点作为结果链表的头
    val, head = heapq.heappop(heap)
    pre = head
    
    # 如果这个链表还有后续节点，加入堆
    if pre.next:
        heapq.heappush(heap, (pre.next.val, pre.next))
    
    # 开始合并
    while heap:
        val, cur = heapq.heappop(heap)
        pre.next = cur
        pre = cur
        
        if cur.next:
            heapq.heappush(heap, (cur.next.val, cur.next))
    
    return head


# 如果你想写一个更简洁的版本（推荐在面试中使用）
def merge_k_lists(lists: list[ListNode]) -> ListNode:
    import heapq
    
    heap = []
    for i, node in enumerate(lists):
        if node:
            heapq.heappush(heap, (node.val, i, node))  # 加个 i 防止节点值相同时比较失败
    
    if not heap:
        return None
    
    dummy = ListNode(0)
    tail = dummy
    
    while heap:
        val, i, node = heapq.heappop(heap)
        tail.next = node
        tail = tail.next
        
        if node.next:
            heapq.heappush(heap, (node.next.val, i, node.next))
    
    return dummy.next