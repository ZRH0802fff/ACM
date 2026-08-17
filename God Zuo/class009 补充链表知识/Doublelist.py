class DoublelistNode:
    def __init__(self,x):
        self.val=x
        self.prev=None
        self.next=None

class  DoubleList:
    def __init__(self):
        self.head=None
        self.tail=None
    
    #尾部添加
    def insert1(self,val):
        new_node=DoublelistNode(val)
        #特殊————无节点
        if self.head is None and self.tail is None:
            self.head=new_node
            self.tail=new_node
            return
        self.tail.next=new_node
        new_node.prev=self.tail
        self.tail=new_node

    #头部添加
    def insert2(self ,val):
        new_node=DoublelistNode(val)
        if self.head is None and self.tail is None:
            self.head=new_node
            self.tail=new_node
            return
        new_node.next=self.head
        self.head.prev=new_node
        self.head=new_node
    
    #从前遍历
    def print1(self):
        cur=self.head
        while cur is not None:
            print(cur.val,end='\t')
            cur=cur.next
        print()
    
    #从后遍历
    def print2(self):
        cur=self.tail
        while cur is not None:
            print(cur.val,end='\t')
            cur=cur.prev
        print()

    #删除节点
    def delete (self,val):
        cur =self.head
        while cur is not None:
            if cur.val==val:
                if cur.prev is None:
                    self.head=cur.next
                    cur.next=None
                    self.head.prev=None
                    return
                if cur.next is None:
                    self.tail=cur.prev
                    cur.prev=None
                    self.tail.next=None
                    return
                cur.prev.next=cur.next
                cur.next.prev=cur.prev
                return
            cur=cur.next
    
if __name__=='__main__':
    root=DoubleList()

    root.insert1(0)
    root.insert1(1)
    root.insert2(-1)
    root.insert1(2)
    root.insert2(-2)

    root.print1()
    root.print2()

    root.delete(0)
    root.print1()