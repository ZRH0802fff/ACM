from sys import stdin, stdout

# 返回无序数组中正数和负数个数相等的最长子数组长度
# 给定一个无序数组arr，其中元素可正、可负、可0
# 求arr所有子数组中正数与负数个数相等的最长子数组的长度

MAXN = 100001
arr = [0] * MAXN

def compute(n):
    prefix_map = {0: -1}   # sum -> 最小的下标
    ans = 0
    total = 0
    
    for i in range(n):
        # 将数字转为 1（正数）、-1（负数）、0（零）
        num = arr[i]
        total += num
        
        if total in prefix_map:
            ans = max(ans, i - prefix_map[total])
        else:
            prefix_map[total] = i
    
    return ans


if __name__ == "__main__":
    input = stdin.read
    data = input().split()
    
    index = 0
    while index < len(data):
        n = int(data[index])
        index += 1
        
        for i in range(n):
            num = int(data[index])
            arr[i] = 1 if num > 0 else (-1 if num < 0 else 0)
            index += 1
        
        result = compute(n)
        stdout.write(str(result) + '\n')
    
    stdout.flush()