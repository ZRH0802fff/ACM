from collections import defaultdict, deque

class Solution:
    def alienOrder(self, words: list[str]) -> str:
        # 1. 初始化入度表
        # 利用字典推导式，一键提取所有出现的独特字符并将其入度初始化为 0
        # 这替代了 Java 中使用长度为 26 的数组并统计 kinds 的步骤
        indegree = {c: 0 for word in words for c in word}
        
        # 2. 建图相关：邻接表
        # 使用 defaultdict(list) 避免处理空列表的边界判断
        graph = defaultdict(list)
        
        # 3. 遍历相邻单词建图
        for i in range(len(words) - 1):
            cur_word = words[i]
            next_word = words[i + 1]
            min_len = min(len(cur_word), len(next_word))
            
            j = 0
            while j < min_len:
                # 找到第一个不相同的字符，建立有向边
                if cur_word[j] != next_word[j]:
                    graph[cur_word[j]].append(next_word[j])
                    indegree[next_word[j]] += 1
                    break
                j += 1
            
            # 特判：如果遍历完最短长度都没有不同，但前一个单词更长
            # 例如 words = ["abc", "ab"]，这绝对不符合字典序，直接返回空
            if j == min_len and len(cur_word) > len(next_word):
                return ""
                
        # 4. 拓扑排序准备：将所有入度为 0 的节点放入双端队列 deque
        queue = deque([c for c in indegree if indegree[c] == 0])
        ans = []
        
        # 5. 开始拓扑排序
        while queue:
            cur = queue.popleft()
            ans.append(cur)
            
            # 遍历相邻节点并解除入度
            for nxt in graph[cur]:
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    queue.append(nxt)
                    
        # 6. 如果收集的字符数量等于总字符数量，说明没有环，返回正确顺序
        # 否则存在环，产生逻辑冲突，返回 ""
        return "".join(ans) if len(ans) == len(indegree) else ""