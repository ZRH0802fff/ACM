def distinctSubseqII(s: str) -> int:
    MOD = 10**9 + 7
    # cnt 记录以某个字符结尾的子序列数量
    # 也可以理解为：由于该字符的加入，上一次产生的增量
    cnt = [0] * 26
    
    # all 代表当前所有子序列的总数（包含空集，所以初始为 1）
    all_count = 1
    
    for char in s:
        idx = ord(char) - ord('a')
        
        # 新增的子序列数量 = 当前总数 - 之前由该字符贡献过的重复部分
        # 这里的 new_add 实际上是把当前所有子序列末尾都加上 char 形成的
        new_add = (all_count - cnt[idx] + MOD) % MOD
        
        # 更新该字符的贡献记录
        cnt[idx] = (cnt[idx] + new_add) % MOD
        
        # 更新总数
        all_count = (all_count + new_add) % MOD
        
    # 题目要求非空子序列，所以减去初始的空集 1
    return (all_count - 1 + MOD) % MOD