import sys

def solve():
    # 1. 极速快读：一次性读入所有数据并分割
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    n = int(input_data[0])
    w = int(input_data[1])
    arr = [int(x) for x in input_data[2 : n+2]]
    
    # 2. 折半拆分
    mid = n >> 1
    left_arr = arr[:mid]
    right_arr = arr[mid:]
    
    # 3. 迭代生成左半部分的所有合法子集和 (完美替代原 Java 的 DFS)
    # 利用列表推导式，不仅省去了递归开销，还能在每一步直接过滤掉 > w 的废弃状态
    lsum = [0]
    for val in left_arr:
        lsum.extend([s + val for s in lsum if s + val <= w])
        
    # 4. 迭代生成右半部分的所有合法子集和
    rsum = [0]
    for val in right_arr:
        rsum.extend([s + val for s in rsum if s + val <= w])
        
    # 5. 排序（Python 的 Timsort 对一百万级别的数据排序仅需约 0.1 秒）
    lsum.sort()
    rsum.sort()
    
    ans = 0
    j = 0
    r_len = len(rsum)
    
    # 6. 双指针合并统计
    # lsum 从大到小遍历 (利用 reversed 得到反向迭代器，O(1) 空间)
    # rsum 从小到大遍历 (指针 j 不断向右推进)
    for val in reversed(lsum):
        # 如果左边挑了 val，右边最多能挑多大？
        while j < r_len and val + rsum[j] <= w:
            j += 1
        # 如果右边前 j 个元素（索引 0 到 j-1）跟 val 加起来都不超过 w
        # 说明对于当前的 val，右边有 j 种搭配方式
        ans += j
        
    print(ans)

if __name__ == '__main__':
    solve()