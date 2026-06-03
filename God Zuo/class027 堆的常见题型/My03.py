import heapq

def halveArray1(self, nums: list[int]) -> int:
    heap=[]
    tal=0
    for num in nums:
        heapq.heappush(heap,-num)
        tal+=num
    target=tal/2
    n=0
    rt=0

    while rt<target:
        cur=-heapq.heappop(heap)
        half=cur/2
        rt+=half
        n+=1
        heapq.heappush(heapq,-half)
    
    return n

def halveArray2(self, nums: list[int]) -> int:
    heap=[]
    tal=0