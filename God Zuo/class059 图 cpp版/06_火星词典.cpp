// 火星词典
// 现有一种使用英语字母的火星语言
// 这门语言的字母顺序对你来说是未知的。
// 给你一个来自这种外星语言字典的字符串列表 words
// words 中的字符串已经 按这门新语言的字母顺序进行了排序 。
// 如果这种说法是错误的，并且给出的 words 不能对应任何字母的顺序，则返回 ""
// 否则，返回一个按新语言规则的 字典递增顺序 排序的独特字符串
// 如果有多个解决方案，则返回其中任意一个
// words中的单词一定都是小写英文字母组成的
// 测试链接 : https://leetcode.cn/problems/alien-dictionary/
// 测试链接(不需要会员) : https://leetcode.cn/problems/Jf1JuT/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string alienOrder(vector<string>& words) {
        // 入度表，26种字符
        int indegree[26];
        for (int i = 0; i < 26; i++) {
            indegree[i] = -1;
        }
        for (string& w : words) {
            for (char c : w) {
                indegree[c - 'a'] = 0;
            }
        }
        // 'a' -> 0
        // 'b' -> 1
        // 'z' -> 25
        // x -> x - 'a'
        // 邻接表，最多26个节点，每个节点最多26条边
        int graph[26][26];
        int graphCnt[26];
        for (int i = 0; i < 26; i++) {
            graphCnt[i] = 0;
        }
        for (int i = 0, j, len; i < (int)words.size() - 1; i++) {
            string& cur = words[i];
            string& next = words[i + 1];
            j = 0;
            len = min((int)cur.length(), (int)next.length());
            for (; j < len; j++) {
                if (cur[j] != next[j]) {
                    int from = cur[j] - 'a';
                    int to = next[j] - 'a';
                    graph[from][graphCnt[from]++] = to;
                    indegree[to]++;
                    break;
                }
            }
            if (j < (int)cur.length() && j == (int)next.length()) {
                return "";
            }
        }
        int queue[26];
        int l = 0, r = 0;
        int kinds = 0;
        for (int i = 0; i < 26; i++) {
            if (indegree[i] != -1) {
                kinds++;
            }
            if (indegree[i] == 0) {
                queue[r++] = i;
            }
        }
        string ans;
        while (l < r) {
            int cur = queue[l++];
            ans += (char)(cur + 'a');
            for (int j = 0; j < graphCnt[cur]; j++) {
                int next = graph[cur][j];
                if (--indegree[next] == 0) {
                    queue[r++] = next;
                }
            }
        }
        return (int)ans.length() == kinds ? ans : "";
    }
};

int main() {
    Solution sol;
    vector<string> words1 = {"wrt","wrf","er","ett","rftt"};
    cout << "words1: " << sol.alienOrder(words1) << " (expected: wertf)" << endl;
    vector<string> words2 = {"z","x"};
    cout << "words2: " << sol.alienOrder(words2) << " (expected: zx)" << endl;
    vector<string> words3 = {"z","x","z"};
    cout << "words3: " << sol.alienOrder(words3) << " (expected: empty)" << endl;
    return 0;
}
