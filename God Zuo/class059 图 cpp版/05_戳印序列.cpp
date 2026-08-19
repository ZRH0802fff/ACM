// 戳印序列
// 你想最终得到"abcbc"，认为初始序列为"?????"。印章是"abc"
// 那么可以先用印章盖出"??abc"的状态，
// 然后用印章最左字符和序列的0位置对齐，就盖出了"abcbc"
// 这个过程中，"??abc"中的a字符，被印章中的c字符覆盖了
// 每次盖章的时候，印章必须完全盖在序列内
// 给定一个字符串target是最终的目标，长度为n，认为初始序列为n个'?'
// 给定一个印章字符串stamp，目标是最终盖出target
// 但是印章的使用次数必须在10*n次以内
// 返回一个数组，该数组由每个回合中被印下的最左边字母的索引组成
// 上面的例子返回[2,0]，表示印章最左字符依次和序列2位置、序列0位置对齐盖下去，就得到了target
// 如果不能在10*n次内印出序列，就返回一个空数组
// 测试链接 : https://leetcode.cn/problems/stamping-the-sequence/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;
const int MAXM = 1001;

// 邻接表建图
int head[MAXN];
int nxt[MAXN * MAXM];
int to[MAXN * MAXM];
int graphCnt;

int indegree[MAXN];
int queue_[MAXN];
int l, r;
bool visited[MAXN];
int path[MAXN];
int pathSize;

void build(int n) {
    graphCnt = 1;
    for (int i = 0; i <= n; i++) {
        head[i] = 0;
    }
}

void addEdge(int f, int t) {
    nxt[graphCnt] = head[f];
    to[graphCnt] = t;
    head[f] = graphCnt++;
}

class Solution {
public:
    vector<int> movesToStamp(string stamp, string target) {
        int m = stamp.length();
        int n = target.length();
        // indegree[i]表示以i位置开头盖印章，有多少个字符已经和最终目标一致
        for (int i = 0; i <= n - m; i++) {
            indegree[i] = m;
        }
        build(n);
        l = 0, r = 0;
        // O(n*m)
        for (int i = 0; i <= n - m; i++) {
            // i开头....(m个)
            // i+0 i+1 i+m-1
            for (int j = 0; j < m; j++) {
                if (target[i + j] == stamp[j]) {
                    if (--indegree[i] == 0) {
                        queue_[r++] = i;
                    }
                } else {
                    // i + j
                    // from : 错误的位置
                    // to : i开头的下标
                    addEdge(i + j, i);
                }
            }
        }
        // 同一个位置取消错误不要重复统计
        for (int i = 0; i < n; i++) {
            visited[i] = false;
        }
        pathSize = 0;
        while (l < r) {
            int cur = queue_[l++];
            path[pathSize++] = cur;
            for (int i = 0; i < m; i++) {
                // cur : 开头位置
                // cur + 0 cur + 1 cur + 2 ... cur + m - 1
                if (!visited[cur + i]) {
                    visited[cur + i] = true;
                    for (int ei = head[cur + i]; ei > 0; ei = nxt[ei]) {
                        int next = to[ei];
                        if (--indegree[next] == 0) {
                            queue_[r++] = next;
                        }
                    }
                }
            }
        }
        if (pathSize != n - m + 1) {
            return vector<int>();
        }
        // path逆序调整
        vector<int> result(pathSize);
        for (int i = 0; i < pathSize; i++) {
            result[i] = path[pathSize - 1 - i];
        }
        return result;
    }
};

int main() {
    Solution sol;
    // 示例: stamp="abc", target="abcbc" → [2,0] 或 [0,2]
    vector<int> res1 = sol.movesToStamp("abc", "abcbc");
    cout << "stamp=abc, target=abcbc: ";
    for (int x : res1) cout << x << " ";
    cout << endl;
    // 示例: stamp="abca", target="aabcaca"
    vector<int> res2 = sol.movesToStamp("abca", "aabcaca");
    cout << "stamp=abca, target=aabcaca: ";
    for (int x : res2) cout << x << " ";
    cout << endl;
    return 0;
}
