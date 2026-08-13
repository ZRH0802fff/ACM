// 单词接龙 II
// 按字典 wordList 完成从单词 beginWord 到单词 endWord 转化
// 一个表示此过程的 转换序列 是形式上像
// beginWord -> s1 -> s2 -> ... -> sk 这样的单词序列，并满足：
// 每对相邻的单词之间仅有单个字母不同
// 转换过程中的每个单词 si（1 <= i <= k）必须是字典 wordList 中的单词
// 注意，beginWord 不必是字典 wordList 中的单词
// sk == endWord
// 给你两个单词 beginWord 和 endWord ，以及一个字典 wordList
// 请你找出并返回所有从 beginWord 到 endWord 的 最短转换序列
// 如果不存在这样的转换序列，返回一个空列表
// 每个序列都应该以单词列表 [beginWord, s1, s2, ..., sk] 的形式返回
// 测试链接 : https://leetcode.cn/problems/word-ladder-ii/

#include <bits/stdc++.h>
using namespace std;

// 单词表 ： list -> hashSet
unordered_set<string> dict;

unordered_set<string> curLevel;
unordered_set<string> nextLevel;

// 反向图
unordered_map<string, vector<string>> graph_;

// 记录路径，当生成一条有效路的时候，拷贝进ans！
list<string> path_;

vector<vector<string>> ans_;

void build_(vector<string>& wordList) {
    dict = unordered_set<string>(wordList.begin(), wordList.end());
    graph_.clear();
    ans_.clear();
    curLevel.clear();
    nextLevel.clear();
}

// begin -> end ，一层层bfs去，建图
// 返回值：真的能找到end，返回true；false
bool bfs_(const string& begin, const string& end) {
    bool find = false;
    curLevel.insert(begin);
    while (!curLevel.empty()) {
        for (const string& word : curLevel) {
            dict.erase(word);
        }
        for (const string& word : curLevel) {
            // word : 去扩
            // 每个位置，字符a~z，换一遍！检查在词表中是否存在
            // 避免，加工出自己
            string w = word;
            for (int i = 0; i < (int)w.length(); i++) {
                char old = w[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    w[i] = ch;
                    if (dict.count(w) && w != word) {
                        if (w == end) {
                            find = true;
                        }
                        graph_[w].push_back(word);
                        nextLevel.insert(w);
                    }
                }
                w[i] = old;
            }
        }
        if (find) {
            return true;
        } else {
            curLevel.clear();
            swap(curLevel, nextLevel);
        }
    }
    return false;
}

void dfs_(const string& word, const string& aim) {
    path_.push_front(word);
    if (word == aim) {
        ans_.push_back(vector<string>(path_.begin(), path_.end()));
    } else if (graph_.count(word)) {
        for (const string& next : graph_[word]) {
            dfs_(next, aim);
        }
    }
    path_.pop_front();
}

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        build_(wordList);
        if (!dict.count(endWord)) {
            return ans_;
        }
        if (bfs_(beginWord, endWord)) {
            dfs_(endWord, beginWord);
        }
        return ans_;
    }
};

int main() {
    Solution sol;
    // 示例: beginWord="hit", endWord="cog", wordList=["hot","dot","dog","lot","log","cog"]
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    auto res = sol.findLadders("hit", "cog", wordList);
    cout << "Results: " << res.size() << " paths" << endl;
    for (auto& path : res) {
        for (auto& w : path) cout << w << " ";
        cout << endl;
    }
    return 0;
}
