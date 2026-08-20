// A*算法模版（对数器验证）
// A*算法 vs Dijkstra算法
// 采用对数器验证

#include <bits/stdc++.h>
using namespace std;

// grid 最大 4000 * 4000（性能测试用）
const int MAXN = 4001;

// 0:上，1:右，2:下，3:左
int move_[] = { -1, 0, 1, 0, -1 };

int grid[MAXN][MAXN];
int distance_[MAXN][MAXN];
bool visited[MAXN][MAXN];

// 小根堆的记录
// 0 : 行
// 1 : 列
// 2 : 排序依据的距离（Dijkstra 是真实距离，A* 是真实距离 + 预估距离）
struct Record {
    int x, y, c;
};
struct Cmp {
    bool operator()(const Record& a, const Record& b) const {
        return a.c > b.c;
    }
};
priority_queue<Record, vector<Record>, Cmp> heap;

// 预估函数的前置声明（C++ 需先声明后使用）
int f1(int x, int y, int targetX, int targetY);
int f2(int x, int y, int targetX, int targetY);
double f3(int x, int y, int targetX, int targetY);

// Dijkstra算法
// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离
int minDistance1(int n, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distance_[i][j] = INT_MAX;
        }
    }
    distance_[startX][startY] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }
    heap = priority_queue<Record, vector<Record>, Cmp>();
    // 0 : 行
    // 1 : 列
    // 2 : 从源点出发到达当前点的距离
    heap.push({ startX, startY, 1 });
    while (!heap.empty()) {
        Record cur = heap.top();
        heap.pop();
        int x = cur.x;
        int y = cur.y;
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance_[x][y];
        }
        for (int i = 0, nx, ny; i < 4; i++) {
            nx = x + move_[i];
            ny = y + move_[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1 && !visited[nx][ny]
                    && distance_[x][y] + 1 < distance_[nx][ny]) {
                distance_[nx][ny] = distance_[x][y] + 1;
                heap.push({ nx, ny, distance_[x][y] + 1 });
            }
        }
    }
    return -1;
}

// A*算法
// grid[i][j] == 0 代表障碍
// grid[i][j] == 1 代表道路
// 只能走上、下、左、右，不包括斜线方向
// 返回从(startX, startY)到(targetX, targetY)的最短距离
int minDistance2(int n, int startX, int startY, int targetX, int targetY) {
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distance_[i][j] = INT_MAX;
        }
    }
    distance_[startX][startY] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }
    heap = priority_queue<Record, vector<Record>, Cmp>();
    // 0 : 行
    // 1 : 列
    // 2 : 从源点出发到达当前点的距离 + 当前点到终点的预估距离
    heap.push({ startX, startY, 1 + f1(startX, startY, targetX, targetY) });
    while (!heap.empty()) {
        Record cur = heap.top();
        heap.pop();
        int x = cur.x;
        int y = cur.y;
        if (visited[x][y]) {
            continue;
        }
        visited[x][y] = true;
        if (x == targetX && y == targetY) {
            return distance_[x][y];
        }
        for (int i = 0, nx, ny; i < 4; i++) {
            nx = x + move_[i];
            ny = y + move_[i + 1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 1 && !visited[nx][ny]
                    && distance_[x][y] + 1 < distance_[nx][ny]) {
                distance_[nx][ny] = distance_[x][y] + 1;
                heap.push({ nx, ny, distance_[x][y] + 1 + f1(nx, ny, targetX, targetY) });
            }
        }
    }
    return -1;
}

// 曼哈顿距离
int f1(int x, int y, int targetX, int targetY) {
    return (abs(targetX - x) + abs(targetY - y));
}

// 对角线距离
int f2(int x, int y, int targetX, int targetY) {
    return max(abs(targetX - x), abs(targetY - y));
}

// 欧式距离
double f3(int x, int y, int targetX, int targetY) {
    return sqrt(pow(targetX - x, 2) + pow(targetY - y, 2));
}

// 为了测试
void randomGrid(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (rand() % 10 < 3) {
                // 每个格子有30%概率是0
                grid[i][j] = 0;
            } else {
                // 每个格子有70%概率是1
                grid[i][j] = 1;
            }
        }
    }
}

// 为了测试
int main() {
    srand(time(0));
    int len = 100;
    int testTime = 10000;
    cout << "功能测试开始" << endl;
    for (int i = 0; i < testTime; i++) {
        int n = rand() % len + 2;
        randomGrid(n);
        int startX = rand() % n;
        int startY = rand() % n;
        int targetX = rand() % n;
        int targetY = rand() % n;
        int ans1 = minDistance1(n, startX, startY, targetX, targetY);
        int ans2 = minDistance2(n, startX, startY, targetX, targetY);
        if (ans1 != ans2) {
            cout << "出错了!" << endl;
        }
    }
    cout << "功能测试结束" << endl;

    cout << "性能测试开始" << endl;
    randomGrid(4000);
    int startX = 0;
    int startY = 0;
    int targetX = 3900;
    int targetY = 3900;
    auto start = chrono::steady_clock::now();
    int ans1 = minDistance1(4000, startX, startY, targetX, targetY);
    auto end = chrono::steady_clock::now();
    cout << "运行dijskra算法结果: " << ans1 << ", 运行时间(毫秒) : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    start = chrono::steady_clock::now();
    int ans2 = minDistance2(4000, startX, startY, targetX, targetY);
    end = chrono::steady_clock::now();
    cout << "运行A*算法结果: " << ans2 << ", 运行时间(毫秒) : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    cout << "性能测试结束" << endl;
    return 0;
}
