# class059 建图、链式前向星、拓扑排序 笔记

> 视频：算法讲解059【必备】建图、链式前向星、拓扑排序

---

## 题目1：三种建图方式

### 题面
演示三种图的存储方式：邻接矩阵、邻接表、链式前向星。分别用于有向图和无向图带权图的建立和遍历。

### 核心思路

**邻接矩阵**：`graph[u][v] = w`。O(1)查询边，O(V²)空间。适合稠密图。

**邻接表**：每个节点维护一个邻居列表。动态灵活，但遍历缓存不友好。

**链式前向星（重点）**：静态数组模拟链表，竞赛首选。
```cpp
int head[MAXN], nxt[MAXM], to[MAXM], weight[MAXM], cnt;
void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}
// 遍历u的所有邻居:
for (int ei = head[u]; ei > 0; ei = nxt[ei]) {
    int v = to[ei], w = weight[ei];
}
```
- 无向图加两次边，MAXM 需设为边数×2
- cnt 从 1 开始（0 作为空的标记）

### 坑点
- 无向图时 MAXM 要准备 m*2
- 链式前向星 cnt 初始化为 1，head 初始化为 0



---

## 题目2：课程表II（拓扑排序模版）

### 题面
numCourses 门课，prerequisites[i]=[ai,bi] 表示修 ai 前必须先修 bi。返回一个合法的学习顺序，若不可能则返回空。

- LeetCode 210: https://leetcode.cn/problems/course-schedule-ii/

### 核心思路
**Kahn算法（BFS拓扑排序）**：
1. 建图 + 入度表：b→a（先修课指向后修课），`indegree[a]++`
2. 入度为 0 的点入队
3. 每次出队一个点，将其邻居入度-1，减到 0 则入队
4. 出队顺序即拓扑序。若出队数 ≠ n，说明有环

### 坑点
- 边的方向：bi→ai（bi 是 ai 的先修课）
- 队列用数组模拟（不用 STL queue）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

// 拓扑排序，入度表
int indegree[MAXN];

// 拓扑排序，用到队列
int queue_[MAXN];
int l, r;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // 邻接表建图（和Java一样用动态方式）
        vector<vector<int>> graph(numCourses);
        // 入度表初始化
        for (int i = 0; i < numCourses; i++) {
            indegree[i] = 0;
        }
        for (auto& edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
            indegree[edge[0]]++;
        }
        l = 0;
        r = 0;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        int cnt = 0;
        while (l < r) {
            int cur = queue_[l++];
            cnt++;
            for (int next : graph[cur]) {
                if (--indegree[next] == 0) {
                    queue_[r++] = next;
                }
            }
        }
        if (cnt == numCourses) {
            return vector<int>(queue_, queue_ + numCourses);
        }
        return vector<int>();
    }
};
```

---

## 题目2：拓扑排序（牛客）

### 题面
给 n 个点 m 条边的有向图，输出拓扑排序结果。若无合法拓扑序输出 -1。

- 牛客：https://www.nowcoder.com/practice/88f7e156ca7d43a1a535f619cd3f495c

### 核心思路
同题目2的 Kahn 算法。提供两个版本：
- **动态版**：每次建图用邻接表
- **静态版**：用链式前向星建图，全局数组复用，更快

### 坑点
- 点多边多（n,m≤200000），必须用链式前向星防卡空间
- 入度表、队列等全部用全局静态数组

### 代码（动态版）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

// 拓扑排序，用到队列
int queue_[MAXN];
int l, r;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

// 邻接表建图（动态方式）
// graph[i] 存 i 指向的所有节点
vector<vector<int>> graph;

int n, m;

void build(int n) {
    graph.clear();
    graph.resize(n + 1);
    for (int i = 0; i <= n; i++) {
        indegree[i] = 0;
    }
}

// 有拓扑排序返回true
// 没有拓扑排序返回false
bool topoSort() {
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue_[r++] = i;
        }
    }
    int fill = 0;
    while (l < r) {
        int cur = queue_[l++];
        ans[fill++] = cur;
        // 邻接表方式遍历 cur 的相邻节点
        for (int next : graph[cur]) {
            if (--indegree[next] == 0) {
                queue_[r++] = next;
            }
        }
    }
    return fill == n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        build(n);
        for (int i = 0, from, to; i < m; i++) {
            cin >> from >> to;
            graph[from].push_back(to);
            indegree[to]++;
        }
        if (!topoSort()) {
            cout << -1 << '\n';
        } else {
            for (int i = 0; i < n - 1; i++) {
                cout << ans[i] << ' ';
            }
            cout << ans[n - 1] << '\n';
        }
    }
    return 0;
}
```

### 代码（静态版）
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;
const int MAXM = 200001;

// 建图相关，链式前向星
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序，用到队列
int queue_[MAXN];
int l, r;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

void build(int n) {
    cnt = 1;
    for (int i = 0; i <= n; i++) {
        head[i] = 0;
        indegree[i] = 0;
    }
}

// 用链式前向星建图
void addEdge(int f, int t) {
    nxt[cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt++;
}

bool topoSort() {
    l = r = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue_[r++] = i;
        }
    }
    int fill = 0;
    while (l < r) {
        int cur = queue_[l++];
        ans[fill++] = cur;
        // 用链式前向星的方式，遍历cur的相邻节点
        for (int ei = head[cur]; ei != 0; ei = nxt[ei]) {
            if (--indegree[to[ei]] == 0) {
                queue_[r++] = to[ei];
            }
        }
    }
    return fill == n;
}
```

---

## 题目3：字典序最小的拓扑排序（洛谷）

### 题面
在合法的拓扑排序中输出字典序最小的那个。

### 核心思路
将队列换成**小根堆**：每次从入度为 0 的点中取编号最小的。其他同 Kahn 算法。

- 手写堆：`heapInsert` + `heapify`
- `push(x)`, `pop()`, `isEmpty()`

### 坑点
- 不能用优先队列（STL），手写小根堆保持静态风格
- 堆操作注意维护 heapSize

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
const int MAXM = 100001;

// 建图相关，链式前向星
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序，不用队列，用小根堆，为了得到字典序最小的拓扑排序
int heap[MAXN];
int heapSize;

// 拓扑排序，入度表
int indegree[MAXN];

// 收集拓扑排序的结果
int ans[MAXN];

int n, m;

// 清理之前的脏数据
void build(int n) {
    cnt = 1;
    heapSize = 0;
    for (int i = 0; i <= n; i++) {
        head[i] = 0;
        indegree[i] = 0;
    }
}

// 用链式前向星建图
void addEdge(int f, int t) {
    nxt[cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt++;
}

// 小根堆里加入数字
void push(int num) {
    int i = heapSize++;
    heap[i] = num;
    // heapInsert的过程
    while (heap[i] < heap[(i - 1) / 2]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// 小根堆里弹出最小值
int pop() {
    int ans = heap[0];
    heap[0] = heap[--heapSize];
    // heapify的过程
    int i = 0;
    int l = 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1] < heap[l] ? l + 1 : l;
        best = heap[best] < heap[i] ? best : i;
        if (best == i) {
            break;
        }
        swap(heap[best], heap[i]);
        i = best;
        l = i * 2 + 1;
    }
    return ans;
}

// 判断小根堆是否为空
bool isEmpty() {
    return heapSize == 0;
}

void topoSort() {
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            push(i);
        }
    }
    int fill = 0;
    while (!isEmpty()) {
        int cur = pop();
        ans[fill++] = cur;
        // 用链式前向星的方式，遍历cur的相邻节点
        for (int ei = head[cur]; ei != 0; ei = nxt[ei]) {
            if (--indegree[to[ei]] == 0) {
                push(to[ei]);
            }
        }
    }
}
```

---

## 题目4：火星词典

### 题面
给定已按外星语言字典序排好的单词列表，推导字母顺序。若矛盾返回 ""。

- LeetCode 269: https://leetcode.cn/problems/alien-dictionary/

### 核心思路
1. 出现过的字符 indegree 初始为 0，未出现为 -1
2. 比较相邻单词：找到第一个不同字符 `cur[j] != next[j]`，建立 cur[j]→next[j] 的边
3. **特殊情况**：若 `cur` 是 `next` 的前缀且更长（如 "abc" "ab"），矛盾返回 ""
4. 拓扑排序，看是否所有出现过的字符都被输出

### 坑点
- indegree 初始化为 -1 标记未出现，出现过的字符才设为 0
- 前缀矛盾检查：`j < cur.length() && j == next.length()`

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

// 入度表，26种字符
int indegree[26];

// 拓扑排序，队列
int queue_[26];
int l, r;

class Solution {
public:
    string alienOrder(vector<string>& words) {
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
        // 邻接表建图（和Java一样用动态方式）
        vector<vector<int>> graph(26);
        for (int i = 0, j, len; i < (int)words.size() - 1; i++) {
            string& cur = words[i];
            string& next = words[i + 1];
            j = 0;
            len = min((int)cur.length(), (int)next.length());
            for (; j < len; j++) {
                if (cur[j] != next[j]) {
                    graph[cur[j] - 'a'].push_back(next[j] - 'a');
                    indegree[next[j] - 'a']++;
                    break;
                }
            }
            if (j < (int)cur.length() && j == (int)next.length()) {
                return "";
            }
        }
        l = 0, r = 0;
        int kinds = 0;
        for (int i = 0; i < 26; i++) {
            if (indegree[i] != -1) {
                kinds++;
            }
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        string ans;
        while (l < r) {
            int cur = queue_[l++];
            ans += (char)(cur + 'a');
            for (int next : graph[cur]) {
                if (--indegree[next] == 0) {
                    queue_[r++] = next;
                }
            }
        }
        return (int)ans.length() == kinds ? ans : "";
    }
};
```

---

## 题目5：戳印序列

### 题面
给定印章 stamp 和目标 target，初始 ???。每次盖章必须完全盖在序列内（可覆盖已盖章部分）。返回盖章的最左索引顺序，使得最终得到 target。使用次数 ≤ 10*n。

- LeetCode 936: https://leetcode.cn/problems/stamping-the-sequence/

### 核心思路
**反向拓扑排序**：从最终状态反推。

1. 枚举每个可能的盖章位置 i（0 ≤ i ≤ n-m），indegree[i]=m 表示还需匹配 m 个字符
2. 比较 target[i+j] 和 stamp[j]：匹配则 indegree[i]--；不匹配则建立"错误位置→i"的依赖边
3. indegree[i]=0 的位置入队（表示可直接盖章）
4. 队列弹出过程：每次盖章消除一些"错误"，解除依赖，最终得到盖章顺序
5. 结果逆序（因为是反向推导）

### 课上例子

`stamp = "ABC"`（M=3），`target = "AABCBC"`（N=6，6 个目标字符）。可盖章的开头位置 i = 0..3，共 N−M+1 = 4 个。

**第 1 步：算每个开头位置的「错误点」（= 入度 indegree）**

把印章平移到 target[i..i+2]，数有几个字符对不上：

| 开头 i | 覆盖位置 | target 片段 | 与 "ABC" 比对 | 错误点(入度) |
|---|---|---|---|---|
| 0 | 0,1,2 | A A B | 对 错 错 | 2 |
| 1 | 1,2,3 | A B C | 对 对 对 | 0 |
| 2 | 2,3,4 | B C B | 错 错 错 | 3 |
| 3 | 3,4,5 | C B C | 错 对 对 | 1 |

**第 2 步：建图（错误位置 → 开头位置）**

开头 i 在位置 j 对不上，就建边 j→i（"位置 j 错了 → 导致开头 i 错点 +1"）：

- 位置 1 → 开头 0（开头 0 在位置 1 错）
- 位置 2 → 开头 0、开头 2
- 位置 3 → 开头 2、开头 3
- 位置 4 → 开头 2

**第 3 步：反向拓扑排序（倒着推盖章顺序）**

错误点 = 0 的开头 = 「最后盖」的（最后盖的没人覆盖它），所以开头 1 先进队列。

1. **弹出开头 1**（盖住位置 1、2、3，取消这三处错误）：
   - 位置 1 → 开头 0 入度 2→1
   - 位置 2 → 开头 0 入度 1→0（进队）、开头 2 入度 3→2
   - 位置 3 → 开头 2 入度 2→1、开头 3 入度 1→0（进队）
2. **弹出开头 0**（盖住 0、1、2）：位置 1、2 已被取消（visited 跳过），位置 0 没有任何开头在这里出错，帮不到别人。
3. **弹出开头 3**（盖住 3、4、5）：位置 3 已被取消；位置 4 → 开头 2 入度 1→0（进队）；位置 5 无对应边。
4. **弹出开头 2**（盖住 2、3、4）：都已取消过，结束。

反向顺序（晚盖 → 早盖）= **[1, 0, 3, 2]**。

**第 4 步：逆序得到答案**

`[1,0,3,2]` 逆序 → 真实盖章顺序 **[2, 3, 0, 1]**。

验证：按 2→3→0→1 依次盖章（每次盖 3 个位置、后盖覆盖前盖），最终得到 "AABCBC" ✓。题目只要求 ≤ 10N 次内盖出、不要求最少次数，所以像 [0,3,1] 这类顺序同样合法。

### 坑点
- 依赖方向：错误位置 j → 依赖它的盖章起始位置 i
- 最终结果需要逆序
- visited 数组防重复统计同位置错误

### 代码
```cpp
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
        char* s = &stamp[0];
        char* t = &target[0];
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
                if (t[i + j] == s[j]) {
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
```
