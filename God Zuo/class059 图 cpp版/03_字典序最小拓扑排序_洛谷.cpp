// 字典序最小的拓扑排序
// 要求返回所有正确的拓扑排序中 字典序最小 的结果
// 建图请使用链式前向星方式，因为比赛平台用其他建图方式会卡空间
// 测试链接 : https://www.luogu.com.cn/problem/U107394
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下所有代码，把主类名改成Main，可以直接通过

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    while (cin >> n >> m) {
        build(n);
        for (int i = 0, from, to; i < m; i++) {
            cin >> from >> to;
            addEdge(from, to);
            indegree[to]++;
        }
        topoSort();
        for (int i = 0; i < n - 1; i++) {
            cout << ans[i] << ' ';
        }
        cout << ans[n - 1] << '\n';
    }
    return 0;
}
