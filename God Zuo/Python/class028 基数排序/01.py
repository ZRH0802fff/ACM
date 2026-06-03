import sys

# 可以设置进制，不一定10进制，随你设置
BASE = 10

MAXN = 100001

arr = [0] * MAXN
help_arr = [0] * MAXN
cnts = [0] * BASE

n = 0

def main():
    global n
    input = sys.stdin.read
    data = input().split()
    index = 0
    n = int(data[index])
    index += 1
    for i in range(n):
        arr[i] = int(data[index])
        index += 1
    sort_arr()
    output = ' '.join(str(arr[i]) for i in range(n))
    print(output)

def sort_arr():
    # 如果会溢出，那么要改用long类型数组来排序
    # 找到数组中的最小值
    min_val = arr[0]
    for i in range(1, n):
        min_val = min(min_val, arr[i])
    max_val = 0
    for i in range(n):
        # 数组中的每个数字，减去数组中的最小值，就把arr转成了非负数组
        arr[i] -= min_val
        # 记录数组中的最大值
        max_val = max(max_val, arr[i])
    # 根据最大值在BASE进制下的位数，决定基数排序做多少轮
    radix_sort(bits(max_val))
    # 数组中所有数都减去了最小值，所以最后不要忘了还原
    for i in range(n):
        arr[i] += min_val

# 返回number在BASE进制下有几位
def bits(number):
    ans = 0
    while number > 0:
        ans += 1
        number //= BASE
    return ans

# 基数排序核心代码
# arr内要保证没有负数
# m是arr中最大值在BASE进制下有几位
def radix_sort(bits_count):
    # 理解的时候可以假设BASE = 10
    offset = 1
    while bits_count > 0:
        cnts[:] = [0] * BASE
        for i in range(n):
            # 数字提取某一位的技巧
            cnts[(arr[i] // offset) % BASE] += 1
        for i in range(1, BASE):
            cnts[i] += cnts[i - 1]
        for i in range(n - 1, -1, -1):
            # 前缀数量分区的技巧
            # 数字提取某一位的技巧
            digit = (arr[i] // offset) % BASE
            cnts[digit] -= 1
            help_arr[cnts[digit]] = arr[i]
        arr[:] = help_arr[:n]
        offset *= BASE
        bits_count -= 1

if __name__ == "__main__":
    main()