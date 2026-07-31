# class060 拓扑排序的扩展技巧 笔记

> 视频：算法讲解060【必备】拓扑排序的扩展技巧

---

## 题目1：最大食物链计数

### 题面
给定有向无环图，a→b 表示 a 被 b 捕食。求从最初级动物到最顶级捕食者的食物链条数，答案对 80112002 取模。

- 洛谷 P4017: https://www.luogu.com.cn/problem/P4017

### 核心思路
**拓扑排序 + DP 推送**：
- `lines[i]`：到达节点 i 的食物链条数
- 入度为 0 的点 `lines[i]=1`（每条初级动物自身是一条链的起点）
- 拓扑排序遍历中，每条边 u→v：`lines[v] = (lines[v] + lines[u]) % MOD`
- `head[u]==0`（无出边）的节点是顶级捕食者，将其 lines 累加到答案

### 坑点
- MOD = 80112002（不是常见的 1e9+7）
- 答案只累加没有出边的节点（顶级捕食者）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5001;
const int MAXM = 500001;
const int MOD = 80112002;

// 链式前向星建图
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int cnt;

// 拓扑排序需要的队列
int queue_[MAXN];

// 拓扑排序需要的入度表
int indegree[MAXN];

// 拓扑排序需要的推送信息
int lines[MAXN];

int n, m;

void build(int n) {
    cnt = 1;
    for (int i = 0; i <= n; i++) {
        indegree[i] = 0;
        lines[i] = 0;
        head[i] = 0;
    }
}

void addEdge(int u, int v) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

int ways() {
    int l = 0;
    int r = 0;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            queue_[r++] = i;
            lines[i] = 1;
        }
    }
    int ans = 0;
    while (l < r) {
        int u = queue_[l++];
        if (head[u] == 0) {
            // 当前的u节点不再有后续邻居了
            ans = (ans + lines[u]) % MOD;
        } else {
            for (int ei = head[u], v; ei > 0; ei = nxt[ei]) {
                // u -> v
                v = to[ei];
                lines[v] = (lines[v] + lines[u]) % MOD;
                if (--indegree[v] == 0) {
                    queue_[r++] = v;
                }
            }
        }
    }
    return ans;
}
```

---

## 题目2：喧闹和富有

### 题面
richer[i]=[ai,bi] 表示 ai 比 bi 更有钱。求对每个人 x，在所有钱≥x 的人中，最安静的人是谁。

- LeetCode 851: https://leetcode.cn/problems/loud-and-rich/

### 核心思路
**拓扑排序 + 推送安静值**：
- 建图：更有钱→更没钱（ai→bi），因为信息从富流向穷更自然
- 初始 `ans[i]=i`（自己最安静）
- 拓扑遍历：cur→next 时，若 `quiet[ans[cur]] < quiet[ans[next]]`，更新 `ans[next] = ans[cur]`
- 这样穷的人会"继承"富人中更安静的选择

### 坑点
- 边方向：ai→bi（有钱指向没钱），入度为 0 的是最有钱的
- 比较安静值用 `<`（更小=更安静）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 501;

// 拓扑排序，入度表
int indegree[MAXN];

// 拓扑排序，队列
int queue_[MAXN];
int l, r;

class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) {
        int n = quiet.size();
        // 邻接表建图（和Java一样用动态方式）
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            indegree[i] = 0;
        }
        for (auto& r : richer) {
            graph[r[0]].push_back(r[1]);
            indegree[r[1]]++;
        }
        l = 0;
        r = 0;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = i;
        }
        while (l < r) {
            int cur = queue_[l++];
            for (int next : graph[cur]) {
                if (quiet[ans[cur]] < quiet[ans[next]]) {
                    ans[next] = ans[cur];
                }
                if (--indegree[next] == 0) {
                    queue_[r++] = next;
                }
            }
        }
        return ans;
    }
};
```

---

## 题目3：并行课程III

### 题面
n 门课，relations 表示先修关系，time[i] 表示第 i+1 门课耗时。可同时修任意多门课（只要先修课已完成）。求完成所有课的最少月份数。

- LeetCode 2050: https://leetcode.cn/problems/parallel-courses-iii/

### 核心思路
**拓扑排序 + 最早完成时间**：
- `cost[cur]`：完成 cur 这门课的最早时间
- 初始入度为 0 的课直接入队
- 对于每个 cur：`cost[cur] += time[cur-1]`（加上自己耗时），更新全局 `ans = max(ans, cost[cur])`
- 推送到 next：`cost[next] = max(cost[next], cost[cur])`（next 必须等 cur 完成才能开始）

### 坑点
- 课程编号从 1 开始，time 索引从 0 开始 → `time[cur-1]`
- cost 推送取 max（所有先修课中最晚完成的那个决定开始时间）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;

// 拓扑排序，入度表
int indegree[MAXN];

// 拓扑排序，队列
int queue_[MAXN];
int l, r;

// cost[i] : 完成课程i的最早时间
int cost[MAXN];

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        // 点 : 1....n
        // 邻接表建图（和Java一样用动态方式）
        vector<vector<int>> graph(n + 1);
        for (int i = 0; i <= n; i++) {
            indegree[i] = 0;
            cost[i] = 0;
        }
        for (auto& edge : relations) {
            graph[edge[0]].push_back(edge[1]);
            indegree[edge[1]]++;
        }
        l = 0;
        r = 0;
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        int ans = 0;
        while (l < r) {
            int cur = queue_[l++];
            // 1 : time[0]
            // x : time[x-1]
            cost[cur] += time[cur - 1];
            ans = max(ans, cost[cur]);
            for (int next : graph[cur]) {
                cost[next] = max(cost[next], cost[cur]);
                if (--indegree[next] == 0) {
                    queue_[r++] = next;
                }
            }
        }
        return ans;
    }
};
```

---

## 题目4：参加会议的最多员工数

### 题面
n 个员工坐圆桌，每人有一个喜欢的人。只有坐在喜欢的人旁边才参会。求最多参会人数。

- LeetCode 2127: https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/

### 核心思路
**拓扑排序剥洋葱 + 基环树分析**：

每个点出度为 1（favorite[i]），图由若干基环树组成。

1. **拓扑排序去链**：从入度为 0 的点开始，用 `deep` 数组记录环外最长链长度
2. 遍历剩余环：
   - **大小为 2 的环**（小环）：两个人都可以带上各自的最长链 → `sum += 2 + deep[a] + deep[b]`
   - **大小 > 2 的环**（大环）：只能取环上的人，不能带链 → `bigRing = max(bigRing, ringSize)`
3. 答案 = max(小环总人数, 最大大环人数)

### 坑点
- 环 size=2 可以带上两侧链条（因为两人坐一起，链条可以分别靠在两侧）
- 环 size>2 链条无法插入（会破坏环结构）
- 答案取两种可能性的最大值

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

int indegree[MAXN];
int queue_[MAXN];
int l, r;
int deep[MAXN];

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        // 图 : favorite[a] = b : a -> b
        int n = favorite.size();
        for (int i = 0; i < n; i++) {
            indegree[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            indegree[favorite[i]]++;
        }
        l = 0;
        r = 0;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                queue_[r++] = i;
            }
        }
        // deep[i] : 不包括i在内，i之前的最长链的长度
        for (int i = 0; i < n; i++) {
            deep[i] = 0;
        }
        while (l < r) {
            int cur = queue_[l++];
            int next = favorite[cur];
            deep[next] = max(deep[next], deep[cur] + 1);
            if (--indegree[next] == 0) {
                queue_[r++] = next;
            }
        }
        // 目前图中的点，不在环上的点，都删除了！ indegree[i] == 0
        // 可能性1 : 所有小环(中心个数 == 2)，算上中心点 + 延伸点，总个数
        int sumOfSmallRings = 0;
        // 可能性2 : 所有大环(中心个数 > 2)，只算中心点，最大环的中心点个数
        int bigRings = 0;
        for (int i = 0; i < n; i++) {
            // 只关心的环！
            if (indegree[i] > 0) {
                int ringSize = 1;
                indegree[i] = 0;
                for (int j = favorite[i]; j != i; j = favorite[j]) {
                    ringSize++;
                    indegree[j] = 0;
                }
                if (ringSize == 2) {
                    sumOfSmallRings += 2 + deep[i] + deep[favorite[i]];
                } else {
                    bigRings = max(bigRings, ringSize);
                }
            }
        }
        return max(sumOfSmallRings, bigRings);
    }
};
```
