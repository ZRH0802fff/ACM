// 单词接龙
// 字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
// 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk ：
// 每一对相邻的单词只差一个字母。
// 对于 1 <= i <= k 时，每个 si 都在 wordList 中
// 注意， beginWord 不需要在 wordList 中。sk == endWord
// 给你两个单词 beginWord 和 endWord 和一个字典 wordList
// 返回 从 beginWord 到 endWord 的 最短转换序列 中的 单词数目
// 如果不存在这样的转换序列，返回 0 。
// 测试链接 : https://leetcode.cn/problems/word-ladder/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string begin, string end, vector<string>& wordList) {
        // 总词表
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(end)) {
            return 0;
        }
        // 数量小的一侧
        unordered_set<string> smallLevel;
        // 数量大的一侧
        unordered_set<string> bigLevel;
        // 由数量小的一侧，所扩展出的下一层列表
        unordered_set<string> nextLevel;
        smallLevel.insert(begin);
        bigLevel.insert(end);
        for (int len = 2; !smallLevel.empty(); len++) {
            for (const string& w : smallLevel) {
                // 从小侧扩展
                string word = w;
                for (int j = 0; j < (int)word.length(); j++) {
                    // 每一位字符都试
                    char old = word[j];
                    for (char change = 'a'; change <= 'z'; change++) {
                        // // 每一位字符都从a到z换一遍
                        if (change != old) {
                            word[j] = change;
                            if (bigLevel.count(word)) {
                                return len;
                            }
                            if (dict.count(word)) {
                                dict.erase(word);
                                nextLevel.insert(word);
                            }
                        }
                    }
                    word[j] = old;
                }
            }
            if (nextLevel.size() <= bigLevel.size()) {
                swap(smallLevel, nextLevel);
            } else {
                smallLevel.clear();
                swap(smallLevel, bigLevel);
                swap(bigLevel, nextLevel);
            }
            nextLevel.clear();
        }
        return 0;
    }
};

int main() {
    Solution sol;
    vector<string> wordList1 = {"hot","dot","dog","lot","log","cog"};
    cout << sol.ladderLength("hit", "cog", wordList1) << " (expected: 5)" << endl;
    vector<string> wordList2 = {"hot","dot","dog","lot","log"};
    cout << sol.ladderLength("hit", "cog", wordList2) << " (expected: 0)" << endl;
    return 0;
}
