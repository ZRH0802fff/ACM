# 测试链接(不需要会员) : https://leetcode.cn/problems/Jf1JuT/
from collections import defaultdict, deque

class Solution:
    def alienOrder(self, words: list[str]) -> str:
        indegree = {c: 0 for word in words for c in word}
        graph=defaultdict(list)

        for i in range(len(words) - 1):
            cur_word = words[i]
            next_word = words[i + 1]
            min_len = min(len(cur_word), len(next_word))
            j=0
            while j<min_len:
                if cur_word[j]!=next_word[j]:
                    graph[cur_word[j]].append(next_word[j])
                    indegree[next_word[j]]+=1
                    break
                j+=1
            
            if j ==min_len and len(cur_word)>len(next_word):
                return ''
        queue=deque([c for c in indegree if indegree[c] ==0] )
        ans=[]

        while queue:
            cur=queue.popleft()
            ans.append(cur)
            for nxt in graph[cur]:
                indegree[nxt]-=1
                if indegree[nxt]==0:
                    queue.append(nxt)
        return ''.join(ans) if len(ans)==len(indegree) else ''