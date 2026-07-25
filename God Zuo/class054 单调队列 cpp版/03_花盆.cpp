// 花盆 — 洛谷 P2698
// 给定 n 个水滴的 (x, y)，找最短的连续区间使得区间内 maxY - minY >= d

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
int maxQ[MAXN], minQ[MAXN];
int maxH, maxT, minH, minT;
int n, d;

struct Point { int x, y; } arr[MAXN];

bool ok() {
    int mx = maxH < maxT ? arr[maxQ[maxH]].y : 0;
    int mn = minH < minT ? arr[minQ[minH]].y : 0;
    return mx - mn >= d;
}

void push(int r) {
    while (maxH < maxT && arr[maxQ[maxT - 1]].y <= arr[r].y) maxT--;
    maxQ[maxT++] = r;
    while (minH < minT && arr[minQ[minT - 1]].y >= arr[r].y) minT--;
    minQ[minT++] = r;
}

void pop(int l) {
    if (maxH < maxT && maxQ[maxH] == l) maxH++;
    if (minH < minT && minQ[minH] == l) minH++;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> d;
    for (int i = 0; i < n; i++) cin >> arr[i].x >> arr[i].y;
    sort(arr, arr + n, [](const Point& a, const Point& b) { return a.x < b.x; });

    maxH = maxT = minH = minT = 0;
    int ans = INT_MAX;
    for (int l = 0, r = 0; l < n; l++) {
        while (!ok() && r < n) { push(r); r++; }
        if (ok()) ans = min(ans, arr[r - 1].x - arr[l].x);
        pop(l);
    }
    cout << (ans == INT_MAX ? -1 : ans) << "\n";
    return 0;
}
