# 给定两个非空链表，表示两个非负的整数
# 每位数字按逆序存储
# 请将两个数相加，并以相同形式返回一个表示和的链表

# 定义链表节点
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def addTwoNumbers(self, h1: ListNode, h2: ListNode) -> ListNode:
        ans = None  # 初始化结果链表
        cur = None  # 当前节点
        carry = 0    # 进位
        
        # 遍历两个链表
        while h1 or h2:
            # 如果链表不为空，取当前节点的值，否则默认为0
            sum_ = (h1.val if h1 else 0) + (h2.val if h2 else 0) + carry
            
            # 计算当前位的值和进位
            val = sum_ % 10
            carry = sum_ // 10
            
            # 构建新的节点并连接到结果链表
            if ans is None:
                ans = ListNode(val)
                cur = ans
            else:
                cur.next = ListNode(val)
                cur = cur.next

            # 移动h1和h2指针
            if h1:
                h1 = h1.next
            if h2:
                h2 = h2.next

        # 如果最后有进位，添加一个新的节点
        if carry == 1:
            cur.next = ListNode(1)
        
        return ans
