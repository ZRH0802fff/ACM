class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def partition(self, head: ListNode, x: int) -> ListNode:
        left_head = left_tail = None  # < x 的区域
        right_head = right_tail = None  # >= x 的区域
        
        while head:
            next_node = head.next
            head.next = None  # 断开当前节点的 next 指针
            
            if head.val < x:
                if left_head is None:
                    left_head = head
                else:
                    left_tail.next = head
                left_tail = head
            else:
                if right_head is None:
                    right_head = head
                else:
                    right_tail.next = head
                right_tail = head
            
            head = next_node
        
        if left_head is None:
            return right_head
        
        # < x 的区域有内容
        left_tail.next = right_head
        return left_head
