from collections import defaultdict

class Solution:
    def findLadders(self, beginWord: str, endWord: str, wordList: list[str]) -> list[list[str]]:
        word_set = set(wordList)
        if endWord not in word_set:
            return []
            
        # 反向图：记录每个单词是从哪些父节点（上一层单词）推导过来的
        graph = defaultdict(list)
        cur_level = {beginWord}
        found = False
        
        # 1. BFS 探路并构建反向 DAG (有向无环图)
        while cur_level and not found:
            # 核心细节：在当前层开始扩展前，把当前层所有的单词从字典中删掉
            # 这样既能保证同层内的不同单词可以指向下一个层的同一个单词（保留所有并行路径）
            # 又能防止走回头路产生死循环
            word_set -= cur_level
            next_level = set()
            
            for word in cur_level:
                # 遍历单词的每个字符，尝试替换为 a-z
                for i in range(len(word)):
                    for char in 'abcdefghijklmnopqrstuvwxyz':
                        if char == word[i]:
                            continue
                            
                        # 拼接替换一个字母后的新单词
                        next_word = word[:i] + char + word[i+1:]
                        
                        if next_word in word_set:
                            if next_word == endWord:
                                found = True
                                
                            next_level.add(next_word)
                            # 构建反向边：子节点指向父节点
                            graph[next_word].append(word)
                            
            cur_level = next_level
            
        ans = []
        
        # 2. DFS 顺着反向图回溯收集所有路径
        if found:
            def dfs(current_word: str, path: list[str]):
                # 触底反弹：回溯到了起点，记录答案
                if current_word == beginWord:
                    # 因为是从 endWord 往回找的，所以最终路径需要 [::-1] 翻转一下
                    ans.append(path[::-1])
                    return
                
                # 遍历当前单词的所有父节点
                for parent in graph[current_word]:
                    path.append(parent)
                    dfs(parent, path)
                    path.pop() # 恢复现场（回溯）
            
            # 启动 DFS 回溯
            dfs(endWord, [endWord])
            
        return ans