# class062 宽度优先遍历及其扩展 笔记

> 视频：算法讲解062【必备】宽度优先遍历及其扩展

---

## 题目1：地图分析

### 题面
n×n 的网格，0 代表海洋，1 代表陆地。找出一个海洋单元格，使其到最近陆地单元格的**曼哈顿距离**最大。若全陆地或全海洋返回 -1。

- LeetCode 1162: https://leetcode.cn/problems/as-far-from-land-as-possible/

### 核心思路
**多源 BFS**：把所有陆地同时入队作为第 0 层，逐层向外扩散。当 BFS 结束时，记录的层数减 1 就是最大距离。
- 陆地入队 visited=true，同时统计海洋数 seas
- 如果 seas==0 或 seas==n*m，直接返回 -1
- 每次处理整层（`size = r-l`），level++ 后扩散四个方向

### 坑点
- 多源 BFS 初始要把所有陆地一起入队，而非只入一个
- 返回 `level - 1`（因为最后一层是只入队但没扩散的）

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 101;
const int MAXM = 101;

int queue_[MAXN * MAXM][2];
int l, r;
bool visited[MAXN][MAXM];

// 0:上，1:右，2:下，3:左
int move_[] = { -1, 0, 1, 0, -1 };

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        l = r = 0;
        int n = grid.size();
        int m = grid[0].size();
        int seas = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    visited[i][j] = true;
                    queue_[r][0] = i;
                    queue_[r++][1] = j;
                } else {
                    visited[i][j] = false;
                    seas++;
                }
            }
        }
        if (seas == 0 || seas == n * m) {
            return -1;
        }
        int level = 0;
        while (l < r) {
            level++;
            int size = r - l;
            for (int k = 0, x, y, nx, ny; k < size; k++) {
                x = queue_[l][0];
                y = queue_[l++][1];
                for (int i = 0; i < 4; i++) {
                    nx = x + move_[i];
                    ny = y + move_[i + 1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny]) {
                        visited[nx][ny] = true;
                        queue_[r][0] = nx;
                        queue_[r++][1] = ny;
                    }
                }
            }
        }
        return level - 1;
    }
};
```

---

## 题目2：贴纸拼词

### 题面
n 种贴纸，每种无限量，每个贴纸有一个小写英文单词。从贴纸中切割字母拼出 target，求最少贴纸数。

- LeetCode 691: https://leetcode.cn/problems/stickers-to-spell-word/

### 核心思路
**BFS + 剪枝**：
- 先将所有贴纸和 target 按字母排序，转成有序形式
- 建图：每种贴纸按首字母分类到 `graph[首字母]`，且去重（同一贴纸只加一次）
- BFS 从头开始：每次取当前字符串的首字母，只尝试对应 `graph` 里的贴纸
- `next(t, s)`：用贴纸 s 去消除 t 中的字符，返回剩余字符串
- 剩余为空→成功返回 level；否则检查 visited，未见过则入队

### 坑点
- 排序是关键优化：让相同前缀的 target 能被哈希去重
- `next()` 中的双指针合并类似归并过程

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 401;
string queue_[MAXN];
int l, r;
vector<vector<string>> graph(26);
unordered_set<string> visited;

string sortStr(const string& str) {
    string s = str;
    sort(s.begin(), s.end());
    return s;
}

string nextStr(const string& t, const string& s) {
    string builder;
    int i = 0, j = 0;
    while (i < (int)t.length()) {
        if (j == (int)s.length()) builder += t[i++];
        else if (t[i] < s[j]) builder += t[i++];
        else if (t[i] > s[j]) j++;
        else { i++; j++; }
    }
    return builder;
}

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        for (int i = 0; i < 26; i++) graph[i].clear();
        visited.clear();
        for (string& str : stickers) {
            str = sortStr(str);
            for (int i = 0; i < (int)str.length(); i++) {
                if (i == 0 || str[i] != str[i - 1]) {
                    graph[str[i] - 'a'].push_back(str);
                }
            }
        }
        target = sortStr(target);
        visited.insert(target);
        l = r = 0;
        queue_[r++] = target;
        int level = 1;
        while (l < r) {
            int size = r - l;
            for (int i = 0; i < size; i++) {
                string cur = queue_[l++];
                for (string& s : graph[cur[0] - 'a']) {
                    string next = nextStr(cur, s);
                    if (next == "") return level;
                    else if (visited.find(next) == visited.end()) {
                        visited.insert(next);
                        queue_[r++] = next;
                    }
                }
            }
            level++;
        }
        return -1;
    }
};
```

---

## 题目3：到达角落需要移除障碍物的最小数目

### 题面
m×n 网格，0 表示空格，1 表示可移除的障碍。从左上走到右下，求最少移除障碍数。

- LeetCode 2290: https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/

### 核心思路
**01-BFS（双端队列）**：每条边权为 0 或 1（走到空格代价 0，走到障碍代价 1），用双端队列求最短路。

### 01-BFS 模板流程（按 PPT 原话整理）

**适用场景**：图中所有边的权重只有 0 和 1 两种值，求源点到目标点的最短距离；时间复杂度 O(节点数 + 边数)。

**为什么不能用传统 BFS**：传统 BFS 靠"扩散了几层，最短路就是多少"——这要求任意两个节点间距离相同；但边权 0/1 时，走 0 权边距离不变、走 1 权边才 +1，"层数"不再等于距离，必须改用"松弛"来判断。

1. `distance[i]` 表示从源点到 i 点的最短距离，初始时所有点的 distance 设为无穷大。
2. 源点进入双端队列，`distance[源点] = 0`。
3. 双端队列**头部弹出** x：
   - **A**：如果 x 是目标点，返回 `distance[x]`，即源点到目标点的最短距离。
   - **B**：考察从 x 出发的每一条边，设某边去 y 点、边权为 w：
     1. 如果 `distance[y] > distance[x] + w`，才处理这条边；否则忽略这条边。
     2. 处理时更新 `distance[y] = distance[x] + w`：
        - `w == 0` → y 从**头部**进入双端队列；
        - `w == 1` → y 从**尾部**进入双端队列。
     3. 考察完 x 出发的所有边后，重复步骤 3。
4. 双端队列为空，停止。

**为什么 0 进队头、1 进队尾**：双端队列始终"按 distance 递增"排列——0 权边 distance 不变，和当前点一样近，要放队头优先扩展；1 权边 distance +1，比当前点远，放队尾。这样每次队头弹出的都是当前 distance 最小的点。

**为什么不需要 visited 标记**：visited 是为了防止"同一个节点重复进出队列"；这里用松弛条件 `distance[y] > distance[x] + w` 天然去重——只有距离真正变小才入队，不会无限重复。

**映射到本题**：`grid[nx][ny]` 就是边权（空格 0、障碍 1），松弛条件即 `distance[x][y] + grid[nx][ny] < distance[nx][ny]`；第一次从队头弹出右下角即可返回（01-BFS 保证第一次遇到即最短路）。

### 坑点
- 双端队列用数组模拟（全局静态数组 + h/t 指针）
- distance 初始化为 `INT_MAX`

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;
int deque_[MAXN][2];
int h, t;
int move_[] = { -1, 0, 1, 0, -1 };

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // distance 是 new int[m][n]：m、n 单维最大 1e5 但 m*n <= 1e5，得到具体 m、n 再开二维数组
        int distance[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) distance[i][j] = INT_MAX;
        h = t = MAXN / 2;
        deque_[h][0] = 0; deque_[h][1] = 0;
        distance[0][0] = 0;
        while (h <= t) {
            int x = deque_[h][0], y = deque_[h++][1];
            if (x == m - 1 && y == n - 1) return distance[x][y];
            for (int i = 0; i < 4; i++) {
                int nx = x + move_[i], ny = y + move_[i + 1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n
                    && distance[x][y] + grid[nx][ny] < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + grid[nx][ny];
                    if (grid[nx][ny] == 0) {
                        deque_[--h][0] = nx; deque_[h][1] = ny;
                    } else {
                        deque_[++t][0] = nx; deque_[t][1] = ny;
                    }
                }
            }
        }
        return -1;
    }
};
```

---

## 题目4：使网格图至少有一条有效路径的最小代价

### 题面
m×n 网格，每格数字表示方向（1→右, 2→左, 3→下, 4→上）。花费 1 可修改一格方向（仅一次）。求从 (0,0) 到右下角的最小修改代价。

- LeetCode 1368: https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/

### 核心思路
**01-BFS**：顺着原方向走代价 0（队首），改方向走代价 1（队尾）。
- `weight = grid[x][y] != i ? 1 : 0`
- 每个格子的 4 个方向都尝试，weight 为 0 或 1

### 坑点
- `move_` 数组下标从 1 开始（1=右, 2=左, 3=下, 4=上），与 grid 值对应
- 和题目 3 一样用双端队列模拟

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10001;
int deque_[MAXN][2];
int h, t;
int move_[5][2] = { {}, { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };

class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // distance 是 new int[m][n]，得到具体 m、n 再开二维数组
        int distance[m][n];
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) distance[i][j] = INT_MAX;
        h = t = MAXN / 2;
        deque_[h][0] = 0; deque_[h][1] = 0;
        distance[0][0] = 0;
        while (h <= t) {
            int x = deque_[h][0], y = deque_[h++][1];
            if (x == m - 1 && y == n - 1) return distance[x][y];
            for (int i = 1; i <= 4; i++) {
                int nx = x + move_[i][0], ny = y + move_[i][1];
                int weight = grid[x][y] != i ? 1 : 0;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n
                    && distance[x][y] + weight < distance[nx][ny]) {
                    distance[nx][ny] = distance[x][y] + weight;
                    if (weight == 0) {
                        deque_[--h][0] = nx; deque_[h][1] = ny;
                    } else {
                        deque_[++t][0] = nx; deque_[t][1] = ny;
                    }
                }
            }
        }
        return -1;
    }
};
```

---

## 题目5：二维接雨水

### 题面
m×n 非负高度矩阵，计算能接多少体积雨水。类似一维接雨水但扩展到二维。

- LeetCode 407: https://leetcode.cn/problems/trapping-rain-water-ii/

### 核心思路
**最小堆 + BFS**：类似 Dijkstra 的思想，从边界开始"注水"。
- 初始将四条边界全部入小根堆（`{行, 列, 水线高度}`）
- 每次弹出堆顶（水线最低的格子），水量 += 水线 - 当前高度
- 向四个方向扩展：入堆的"水线"为 `max(邻居高度, 当前水线)`——水不能低于自身高度
- 手写小根堆加速

### 坑点
- 手写堆需要维护 `heapInsert` 和 `heapify`
- 水线 = `max(height[nr][nc], w)`：水不能低于当前格子高度

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 201;
const int MAXM = 201;
int move_[] = { -1, 0, 1, 0, -1 };

int heapSize;
int heap[MAXN * MAXM][3];

void push(int r, int c, int w) {
    int i = heapSize++;
    heap[i][0] = r; heap[i][1] = c; heap[i][2] = w;
    while (heap[i][2] < heap[(i - 1) / 2][2]) {
        swap(heap[i][0], heap[(i - 1) / 2][0]);
        swap(heap[i][1], heap[(i - 1) / 2][1]);
        swap(heap[i][2], heap[(i - 1) / 2][2]);
        i = (i - 1) / 2;
    }
}

void pop(int& r, int& c, int& w) {
    r = heap[0][0]; c = heap[0][1]; w = heap[0][2];
    heap[0][0] = heap[--heapSize][0];
    heap[0][1] = heap[heapSize][1];
    heap[0][2] = heap[heapSize][2];
    int i = 0, l = 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1][2] < heap[l][2] ? l + 1 : l;
        best = heap[best][2] < heap[i][2] ? best : i;
        if (best == i) break;
        swap(heap[best][0], heap[i][0]);
        swap(heap[best][1], heap[i][1]);
        swap(heap[best][2], heap[i][2]);
        i = best; l = i * 2 + 1;
    }
}

class Solution {
public:
    int trapRainWater(vector<vector<int>>& height) {
        int n = height.size(), m = height[0].size();
        heapSize = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    push(i, j, height[i][j]);
                    visited[i][j] = true;
                }
        int ans = 0;
        while (heapSize) {
            int r, c, w;
            pop(r, c, w);
            ans += w - height[r][c];
            for (int i = 0, nr, nc; i < 4; i++) {
                nr = r + move_[i]; nc = c + move_[i + 1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc]) {
                    push(nr, nc, max(height[nr][nc], w));
                    visited[nr][nc] = true;
                }
            }
        }
        return ans;
    }
};
```

---

## 题目6：单词接龙 II

### 题面
从 beginWord 变到 endWord，每次变一个字母，中间词必须在 wordList 中。返回所有**最短**转换序列。

- LeetCode 126: https://leetcode.cn/problems/word-ladder-ii/

### 核心思路
**BFS 建反向图 + DFS 收集路径**：
1. BFS 从 begin 开始逐层扩散：每层把词从 dict 中删掉（去重），每个位置 a~z 替换看是否在 dict 中
2. 在 BFS 过程中**建反向图**：`graph[新词].push_back(当前词)`，记录"从哪来的"
3. BFS 遇到 end 时立即停止整层处理（因为要所有最短路径）
4. DFS 从 end 反向走回 begin，用 `list` 收集路径并翻转

### 坑点
- BFS 必须整层处理完才检查是否找到 end（因为同一层可能有多个路径到达 end）
- 每层开始前 `dict.removeAll(curLevel)` 而非边扩边删（保证同层不同词可互为邻居）
- `path.push_front` + `pop_front` 实现路径回溯

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

unordered_set<string> dict;
unordered_set<string> curLevel, nextLevel;
unordered_map<string, vector<string>> graph_;
list<string> path_;
vector<vector<string>> ans_;

void build_(vector<string>& wordList) {
    dict = unordered_set<string>(wordList.begin(), wordList.end());
    graph_.clear(); ans_.clear();
    curLevel.clear(); nextLevel.clear();
}

bool bfs_(const string& begin, const string& end) {
    bool find = false;
    curLevel.insert(begin);
    while (!curLevel.empty()) {
        for (const string& word : curLevel) dict.erase(word);
        for (const string& word : curLevel) {
            string w = word;
            for (int i = 0; i < (int)w.length(); i++) {
                char old = w[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    w[i] = ch;
                    if (dict.count(w) && w != word) {
                        if (w == end) find = true;
                        graph_[w].push_back(word);
                        nextLevel.insert(w);
                    }
                }
                w[i] = old;
            }
        }
        if (find) return true;
        curLevel.clear(); swap(curLevel, nextLevel);
    }
    return false;
}

void dfs_(const string& word, const string& aim) {
    path_.push_front(word);
    if (word == aim) ans_.push_back(vector<string>(path_.begin(), path_.end()));
    else if (graph_.count(word))
        for (const string& next : graph_[word]) dfs_(next, aim);
    path_.pop_front();
}

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        build_(wordList);
        if (!dict.count(endWord)) return ans_;
        if (bfs_(beginWord, endWord)) dfs_(endWord, beginWord);
        return ans_;
    }
};
```
