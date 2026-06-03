class Solution:
    def minStickers(self, stickers: list[str], target: str) -> int:
        # graph 的 26 个槽位对应 a-z 
        # graph[i] 存放所有包含了字符 (i + 'a') 的排序后的贴纸
        graph = [[] for _ in range(26)]
        
        # 1. 预处理贴纸：字符内部排序 + 挂载到词频图中
        for string in stickers:
            s = "".join(sorted(string))
            for i in range(len(s)):
                # 如果是该字符第一次出现，把这张贴纸挂在这个字符的名单下
                if i == 0 or s[i] != s[i - 1]:
                    graph[ord(s[i]) - ord('a')].append(s)
                    
        target = "".join(sorted(target))
        visited = set([target])
        
        # 2. 严格保留 l, r 控制队列的思路
        queue = [target]
        l = 0
        r = 1
        level = 1
        
        # 辅助函数：双指针相减 (target 减去 sticker)
        def get_next(t: str, s: str) -> str:
            res = []
            i, j = 0, 0
            while i < len(t):
                if j == len(s):
                    res.append(t[i])
                    i += 1
                elif t[i] < s[j]:
                    res.append(t[i])
                    i += 1
                elif t[i] > s[j]:
                    j += 1
                else:
                    i += 1
                    j += 1
            return "".join(res)
            
        # 3. 宽度优先遍历 (按层推进)
        while l < r:
            size = r - l
            for _ in range(size):
                cur = queue[l]
                l += 1
                
                # 核心剪枝：既然我们迟早要消掉 cur[0] 这个字符
                # 那我们这轮「只试」那些拥有 cur[0] 字符的贴纸即可，极大幅度缩减分支！
                first_char_idx = ord(cur[0]) - ord('a')
                for s in graph[first_char_idx]:
                    nxt = get_next(cur, s)
                    
                    if not nxt:
                        return level  # 减成空串了，直接返回层数
                    elif nxt not in visited:
                        visited.add(nxt)
                        # 加入队尾，推进尾指针
                        queue.append(nxt)
                        r += 1
                        
            level += 1
            
        return -1