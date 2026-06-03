# 测试链接 : https://leetcode.cn/problems/word-ladder/
class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        wordset=set(wordList)
        if endWord not in wordset:
            return 0
        
        small_level={beginWord}
        big_level={endWord}
        length=2
        while small_level:
            nxt_level=set()
            for word in small_level:
                for i in range(len(word)):
                    for char in 'abcdefghijklmnopqrstuvwxyz':
                        if char==word[i]:
                            continue
                        nxt_word=word[:i]+char+word[i+1:]
                        if nxt_word in big_level:
                            return length
                        if nxt_word in wordset:
                            nxt_level.add(nxt_word)
                            wordset.remove(nxt_word)
            if len(nxt_level)<=len(big_level):
                small_level=nxt_level
            else:
                small_level,big_level=big_level,nxt_level
            length+=1

        return 0