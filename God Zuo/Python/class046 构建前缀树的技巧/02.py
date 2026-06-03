from sys import stdin, stdout

# 全局变量
MAXN = 100001
arr = [0] * MAXN


def compute(n: int, aim: int, arr: list) -> int:
    # key: 前缀和   value: 该前缀和最早出现的位置
    prefix_map = {0: -1}   # 重要：空数组前缀和为0，位置为-1
    
    ans = 0
    sum_val = 0
    
    for i in range(n):
        sum_val += arr[i]
        
        # 寻找 sum - aim 之前出现的位置
        if sum_val - aim in prefix_map:
            ans = max(ans, i - prefix_map[sum_val - aim])
        
        # 只记录最早出现的位置
        if sum_val not in prefix_map:
            prefix_map[sum_val] = i
    
    return ans


def main():
    input = stdin.read
    data = input().split()
    
    index = 0
    while index < len(data):
        n = int(data[index])
        index += 1
        aim = int(data[index])
        index += 1
        
        for i in range(n):
            arr[i] = int(data[index])
            index += 1
        
        result = compute(n, aim, arr)
        stdout.write(str(result) + '\n')


if __name__ == "__main__":
    main()