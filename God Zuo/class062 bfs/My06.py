# 测试链接 : https://leetcode.cn/problems/word-ladder-ii/
from collections import defaultdict
class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: list[str]) -> list[list[str]]:
        wordset=set(wordList)
        if endWord not in wordset:
            return []
        graph=defaultdict(list)
        cur_level={beginWord}
        found=False
        while cur_level and not found:
            wordset-=cur_level
            next_level=set()
            for s in cur_level:
                for i in range(len(s)):
                    for char in 'abcdefghijklmnopqrstuvwxyz':
                        if char ==s[i]:
                            continue
                        nxt_s=s[:i]+char+s[i+1:]
                        if nxt_s in wordset:
                            if nxt_s==endWord:
                                found=True
                            next_level.add(nxt_s)
                            graph[nxt_s].append(s)
            cur_level=next_level
        ans=[]
        if found:
            def dfs(cur_word,path:list):
                if cur_word ==beginWord:
                    ans.append(path[::-1])
                    return
                for pre in graph[cur_word]:
                    path.append(pre)
                    dfs(pre,path)
                    path.pop()
            dfs(endWord,[endWord])
        return ans 