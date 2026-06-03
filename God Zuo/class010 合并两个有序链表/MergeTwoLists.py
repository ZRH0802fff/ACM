# 定义链表节点
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeTwoLists(self, head1: ListNode, head2: ListNode) -> ListNode:
        # 如果其中一个链表为空，直接返回另一个
        if not head1 or not head2:
            return head1 if head1 else head2
        
        # 确定合并后新链表的头节点（选值较小的那个）
        if head1.val <= head2.val:
            head = head1
            cur1 = head1.next
            cur2 = head2
        else:
            head = head2
            cur1 = head1
            cur2 = head2.next
        
        # pre 指向新链表的最后一个节点
        pre = head
        
        # 遍历两个链表，按升序连接
        while cur1 and cur2: 
            if cur1.val <= cur2.val:
                pre.next = cur1
                cur1 = cur1.next
            else:
                pre.next = cur2
                cur2 = cur2.next
            pre = pre.next
        
        # 循环结束后，将剩余的链表部分直接连接在末尾
        pre.next = cur1 if cur1 else cur2
        
        return head

# 测试代码（可选）
if __name__ == "__main__":
    # 构造链表 1: 1 -> 2 -> 4
    l1 = ListNode(1, ListNode(2, ListNode(4)))
    # 构造链表 2: 1 -> 3 -> 4
    l2 = ListNode(1, ListNode(3, ListNode(4)))
    
    sol = Solution()
    res = sol.mergeTwoLists(l1, l2)
    
    # 打印结果
    while res:
        print(res.val, end=" -> " if res.next else "\n")
        res = res.next