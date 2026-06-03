# 用类描述实现前缀树。不推荐！
# 测试链接 : https://leetcode.cn/problems/implement-trie-ii-prefix-tree/
class Code01_TrieTree:

    # 路是数组实现的
    # 提交时把类名、构造方法改为Trie
    class Trie1:

        class TrieNode:
            def __init__(self):
                self.pass_ = 0
                self.end = 0
                self.nexts = [None] * 26

        def __init__(self):
            self.root = self.TrieNode()

        def insert(self, word: str) -> None:
            node = self.root
            node.pass_ += 1
            for i in range(len(word)):  # 从左往右遍历字符
                path = ord(word[i]) - ord('a')  # 由字符，对应成走向哪条路
                if node.nexts[path] is None:
                    node.nexts[path] = self.TrieNode()
                node = node.nexts[path]
                node.pass_ += 1
            node.end += 1

        # 如果之前word插入过前缀树，那么此时删掉一次
        # 如果之前word没有插入过前缀树，那么什么也不做
        def erase(self, word: str) -> None:
            if self.countWordsEqualTo(word) > 0:
                node = self.root
                node.pass_ -= 1
                for i in range(len(word)):
                    path = ord(word[i]) - ord('a')
                    if node.nexts[path] is None:  # 理论上不会发生，但保持原逻辑安全
                        return
                    if (node.nexts[path].pass_ - 1) == 0:
                        node.nexts[path].pass_ -= 1
                        node.nexts[path] = None
                        return
                    node.nexts[path].pass_ -= 1
                    node = node.nexts[path]
                node.end -= 1

        # 查询前缀树里，word单词出现了几次
        def countWordsEqualTo(self, word: str) -> int:
            node = self.root
            for i in range(len(word)):
                path = ord(word[i]) - ord('a')
                if node.nexts[path] is None:
                    return 0
                node = node.nexts[path]
            return node.end

        # 查询前缀树里，有多少单词以pre做前缀
        def countWordsStartingWith(self, pre: str) -> int:
            node = self.root
            for i in range(len(pre)):
                path = ord(pre[i]) - ord('a')
                if node.nexts[path] is None:
                    return 0
                node = node.nexts[path]
            return node.pass_ 

    # 路是哈希表实现的
    # 提交时把类名、构造方法改为Trie
    class Trie2:

        class TrieNode:
            def __init__(self):
                self.pass_ = 0
                self.end = 0
                self.nexts = {}

        def __init__(self):
            self.root = self.TrieNode()

        def insert(self, word: str) -> None:
            node = self.root
            node.pass_ += 1
            for i in range(len(word)):  # 从左往右遍历字符
                path = ord(word[i])  # 与Java完全一致：使用字符的整数值作为key
                if path not in node.nexts:
                    node.nexts[path] = self.TrieNode()
                node = node.nexts[path]
                node.pass_ += 1
            node.end += 1

        def erase(self, word: str) -> None:
            if self.countWordsEqualTo(word) > 0:
                node = self.root
                node.pass_ -= 1
                for i in range(len(word)):
                    path = ord(word[i])
                    if path not in node.nexts:
                        return
                    next_node = node.nexts[path]
                    if next_node.pass_ - 1 == 0:
                        next_node.pass_ -= 1
                        node.nexts.pop(path)
                        return
                    next_node.pass_ -= 1
                    node = next_node
                node.end -= 1

        def countWordsEqualTo(self, word: str) -> int:
            node = self.root
            for i in range(len(word)):
                path = ord(word[i])
                if path not in node.nexts:
                    return 0
                node = node.nexts[path]
            return node.end

        def countWordsStartingWith(self, pre: str) -> int:
            node = self.root
            for i in range(len(pre)):
                path = ord(pre[i])
                if path not in node.nexts:
                    return 0
                node = node.nexts[path]
            return node.pass_