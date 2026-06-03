def generate_permutation1(s: str) -> list[str]:
    """
    方法1：使用列表模拟 StringBuilder，回溯生成所有子序列并用 set 去重
    """
    result = set()
    
    def f1(i: int, path: list[str]):
        if i == len(s):
            result.add(''.join(path))
            return
        
        # 选择当前字符（要）
        path.append(s[i])
        f1(i + 1, path)
        path.pop()           # 回溯
        
        # 不选当前字符
        f1(i + 1, path)
    
    f1(0, [])
    return list(result)
def generate_permutation2(s: str) -> list[str]:
    """    
    方法2：使用固定长度列表 + size 控制有效长度，回溯生成子序列并去重
    """
    result = set()
    path = [''] * len(s)   # 预分配空间
    
    def f2(i: int, size: int):
        if i == len(s):
            result.add(''.join(path[:size]))
            return
        
        # 选择当前字符（要）
        path[size] = s[i]
        f2(i + 1, size + 1)
        
        # 不选当前字符
        f2(i + 1, size)
    
    f2(0, 0)
    return list(result)