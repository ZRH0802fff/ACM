class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        # 将词表转化为集合，O(1) 极速查找
        word_set = set(wordList)
        
        # 如果终点都不在词表里，直接宣告失败
        if endWord not in word_set:
            return 0
            
        # 初始化双向 BFS 的两端
        small_level = {beginWord}
        big_level = {endWord}
        
        # 记录转换序列的长度 (beginWord 到 endWord 算 2 个单词)
        length = 2
        
        while small_level:
            next_level = set()
            
            # 遍历较小一端的所有单词
            for word in small_level:
                # 每一位字符都替换成 a-z 试一遍
                for i in range(len(word)):
                    for char in 'abcdefghijklmnopqrstuvwxyz':
                        if char == word[i]:
                            continue
                            
                        # Python 绝技：利用切片直接拼接新字符串，速度远超 list 修改
                        next_word = word[:i] + char + word[i+1:]
                        
                        # 如果新单词存在于对面的集合中，说明两端接头了！直接返回长度
                        if next_word in big_level:
                            return length
                            
                        # 如果新单词在未访问的词表中，将其加入下一层的扩展集合
                        if next_word in word_set:
                            word_set.remove(next_word) # 移出词表，防止走回头路
                            next_level.add(next_word)
                            
            # 核心优化：永远优先扩展元素较少的那一端
            if len(next_level) <= len(big_level):
                small_level = next_level
            else:
                # Python 的多变量赋值特性，直接完成交换
                small_level, big_level = big_level, next_level
                
            length += 1
            
        return 0