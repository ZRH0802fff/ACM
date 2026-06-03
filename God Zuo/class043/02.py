import math


def is_palindrome(num: int) -> bool:
    """
    判断一个整数是否为回文数（字符串方式更直观且不易溢出）
    """
    s = str(num)
    return s == s[::-1]


def even_enlarge(seed: int) -> int:
    """
    种子生成偶数长度回文数
    例：seed = 123 → 123321
    """
    s = str(seed)  
    return int(s + s[::-1])


def odd_enlarge(seed: int) -> int:
    """
    种子生成奇数长度回文数（中间用最后一个数字作为中心）
    例：seed = 123 → 12321   （取 123 的前缀 12 + 3 + 21）
    """
    s = str(seed)
    # 去掉最后一个字符作为“镜像部分”的起点
    return int(s + s[-2::-1])  # s[:-1][::-1] 其实就是 s[-2::-1]


def superpalindromes_in_range1(left: str, right: str) -> int:
    """
    方法1：枚举种子生成回文根，然后平方后判断是否在 [left, right] 且本身是回文
    """
    l = int(left)
    r = int(right)
    
    # 上界开根号
    limit = int(math.sqrt(r)) + 1
    
    ans = 0
    seed = 1
    
    while True:
        # 偶数长度回文根
        num_even = even_enlarge(seed)
        sq_even = num_even * num_even
        if sq_even > r:
            break
        if sq_even >= l and is_palindrome(sq_even):
            ans += 1
        
        # 奇数长度回文根
        num_odd = odd_enlarge(seed)
        sq_odd = num_odd * num_odd
        if sq_odd > r:
            break
        if sq_odd >= l and is_palindrome(sq_odd):
            ans += 1
        
        seed += 1
    
    return ans


# 打表结果（题目范围 10^18 内所有超级回文数）
RECORD = [
    1, 4, 9, 121, 484, 10201, 12321, 14641, 40804, 44944,
    1002001, 1234321, 4008004, 100020001, 102030201, 104060401,
    121242121, 123454321, 125686521, 400080004, 404090404,
    10000200001, 10221412201, 12102420121, 12345654321,
    40000800004, 1000002000001, 1002003002001, 1004006004001,
    1020304030201, 1022325232201, 1024348434201, 1210024200121,
    1212225222121, 1214428244121, 1232346432321, 1234567654321,
    4000008000004, 4004009004004, 100000020000001,
    100220141022001, 102012040210201, 102234363432201,
    121000242000121, 121242363242121, 123212464212321,
    123456787654321, 400000080000004, 10000000200000001,
    10002000300020001, 10004000600040001, 10020210401202001,
    10022212521222001, 10024214841242001, 10201020402010201,
    10203040504030201, 10205060806050201, 10221432623412201,
    10223454745432201, 12100002420000121, 12102202520220121,
    12104402820440121, 12122232623222121, 12124434743442121,
    12321024642012321, 12323244744232321, 12343456865434321,
    12345678987654321, 40000000800000004, 40004000900040004,
    1000000002000000001, 1000220014100220001, 1002003004003002001,
    1002223236323222001, 1020100204020010201, 1020322416142230201,
    1022123226223212201, 1022345658565432201, 1210000024200000121,
    1210242036302420121, 1212203226223022121, 1212445458545442121,
    1232100246420012321, 1232344458544432321, 1234323468643234321,
    4000000008000000004
]


def superpalindromes_in_range2(left: str, right: str) -> int:
    """
    方法2：打表 + 二分（或线性扫描）找范围内的个数
    最快、最稳，实际 oj 比赛推荐写法
    """
    l = int(left)
    r = int(right)
    
    # 找到第一个 >= l 的位置
    i = 0
    while i < len(RECORD) and RECORD[i] < l:
        i += 1
    
    # 找到最后一个 <= r 的位置
    j = len(RECORD) - 1
    while j >= 0 and RECORD[j] > r:
        j -= 1
    
    if i > j:
        return 0
    return j - i + 1


# 用于验证打表是否正确（可运行一次生成所有超级回文数）
def collect_all_super_palindromes():
    import sys
    limit = int(math.sqrt(sys.maxsize)) + 10
    seed = 1
    res = []
    
    while True:
        # 偶数长度
        num = even_enlarge(seed)
        sq = num * num
        if sq > 10**18 * 10:  # 稍微多一点防止边界
            break
        if is_palindrome(sq):
            res.append(sq)
        
        # 奇数长度
        num = odd_enlarge(seed)
        sq = num * num
        if sq > 10**18 * 10:
            break
        if is_palindrome(sq):
            res.append(sq)
        
        seed += 1
    
    res.sort()
    return res


if __name__ == "__main__":
    # 测试用例
    tests = [
        ("1", "100"),
        ("1", "1000"),
        ("40000000000000000", "100000000000000000"),
        ("1", "10"*9 + "0"),
    ]
    
    for left, right in tests:
        ans1 = superpalindromes_in_range1(left, right)
        ans2 = superpalindromes_in_range2(left, right)
        print(f"[{left}, {right}] → {ans1}  (打表法: {ans2})")