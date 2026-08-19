// 飞行路线（自己手撸的堆）
// Alice和Bob现在要乘飞机旅行，他们选择了一家相对便宜的航空公司
// 该航空公司一共在n个城市设有业务，设这些城市分别标记为0 ~ n−1
// 一共有m种航线，每种航线连接两个城市，并且航线有一定的价格
// Alice 和 Bob 现在要从一个城市沿着航线到达另一个城市，途中可以进行转机
// 航空公司对他们这次旅行也推出优惠，他们可以免费在最多k种航线上搭乘飞机
// 那么 Alice 和 Bob 这次出行最少花费多少
// 测试链接 : https://www.luogu.com.cn/problem/P4568
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10001;
const int MAXM = 100001;
const int MAXK = 11;

// 链式前向星建图需要
int head[MAXN];
int nxt[MAXM];
int to[MAXM];
int weight[MAXM];
int cnt;

// Dijkstra需要
int distance_[MAXN][MAXK];
bool visited[MAXN][MAXK];

// 自己写的普通堆，静态结构，推荐
// 注意是自己写的普通堆，不是反向索引堆
// 因为(点编号，使用免费路线的次数)，两个参数的组合才是图中的点
// 两个参数的组合对应一个点(一个堆的下标)，所以反向索引堆不好写
// 其实也能实现，二维点变成一维下标即可
// 但是会造成很多困惑，索性算了，就手写普通堆吧
// 0 : 到达的城市编号
// 1 : 已经使用的免单次数
// 2 : 沿途的花费
struct Node {
    int u, use, cost;
};
Node heap[MAXM * MAXK];
int heapSize;

int n, m, k, s, t;

void build() {
    cnt = 1;
    heapSize = 0;
    for (int i = 0; i < n; i++) {
        head[i] = 0;
        for (int j = 0; j <= k; j++) {
            distance_[i][j] = INT_MAX;
            visited[i][j] = false;
        }
    }
}

void addEdge(int u, int v, int w) {
    nxt[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
}

void push(int u, int t, int c) {
    heap[heapSize] = { u, t, c };
    int i = heapSize++;
    while (heap[i].cost < heap[(i - 1) / 2].cost) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int u, use, cost;

// 先声明，pop 里会用到
void heapify(int i);

void pop() {
    u = heap[0].u;
    use = heap[0].use;
    cost = heap[0].cost;
    swap(heap[0], heap[--heapSize]);
    heapify(0);
}

void heapify(int i) {
    int l = i * 2 + 1;
    while (l < heapSize) {
        int best = l + 1 < heapSize && heap[l + 1].cost < heap[l].cost ? l + 1 : l;
        best = heap[best].cost < heap[i].cost ? best : i;
        if (best == i) {
            break;
        }
        swap(heap[best], heap[i]);
        i = best;
        l = i * 2 + 1;
    }
}

int dijkstra() {
    distance_[s][0] = 0;
    push(s, 0, 0);
    while (heapSize > 0) {
        pop();
        if (visited[u][use]) {
            continue;
        }
        visited[u][use] = true;
        if (u == t) {
            // 常见剪枝
            // 发现终点直接返回
            // 不用等都结束
            return cost;
        }
        for (int ei = head[u], v, w; ei > 0; ei = nxt[ei]) {
            v = to[ei];
            w = weight[ei];
            if (use < k && distance_[v][use + 1] > distance_[u][use]) {
                // 使用免费
                distance_[v][use + 1] = distance_[u][use];
                push(v, use + 1, distance_[v][use + 1]);
            }
            if (distance_[v][use] > distance_[u][use] + w) {
                // 不用免费
                distance_[v][use] = distance_[u][use] + w;
                push(v, use, distance_[v][use]);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m >> k >> s >> t) {
        build();
        for (int i = 0, a, b, c; i < m; i++) {
            cin >> a >> b >> c;
            addEdge(a, b, c);
            addEdge(b, a, c);
        }
        cout << dijkstra() << '\n';
    }
    return 0;
}
