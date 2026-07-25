# class075 背包DP — 多重背包、混合背包

> B站视频：[算法讲解075](https://www.bilibili.com/video/BV1Nz4y1c71M/)
> 前置知识：class054 单调队列、class073 01背包、class074 完全背包

---

## 01 多重背包 — 朴素枚举（会超时）

**题面：** n种物品，每种有体积w、价值v、数量cnt。背包容量t，求最大价值。

**核心思路：** `dp[i][j]=max over k=0..cnt(dp[i-1][j-k*w]+k*v)`。朴素枚举会超时（O(n·t·avgCnt)）。

**坑点：** 需同时限制k≤cnt且k*w≤j。

**代码：**
```cpp
// 朴素版，大cnt会超时
for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= t; j++) {
        dp[i][j] = dp[i-1][j];
        for (int k = 1; k <= cnt[i] && k * w[i] <= j; k++) {
            dp[i][j] = max(dp[i][j], dp[i-1][j - k*w[i]] + k*v[i]);
        }
    }
}
```

---

## 02 多重背包 — 二进制分组优化（最常用）

**题面：** 同01，但必须优化。

**核心思路：** 把cnt个物品拆成log(cnt)个"包裹"，1,2,4,8,...倍捆绑+最后小尾巴。每个包裹是要么全拿、要么全不拿的01背包物品。原理：二进制组合能覆盖[0,cnt]所有数字。最后对包裹跑01背包(O(包裹数·t))。

**坑点：** 最后剩的小尾巴不能漏；有些数量可能被重复表示，但不影响正确性。

**代码：**

```cpp
#include<bits/stdc++.h>
using namespace std;

const int maxn = 1005;
const int maxm = 40005;

int n,t,idx;
int val[maxn];
int wei[maxn];
int dp[maxm];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    while(cin>>n>>t){
        idx = 0;
        for (int i = 1, v, w, c; i <= n; ++i){
            cin >> v >> w >> c;
            for (int k = 1; k <= c;k<<=1){
                val[++idx] = k * v;
                wei[idx] = k * w;
                c -= k;
            }
            if(c>0){
                val[++idx] = c * v;
                wei[idx] = c * w;
            }
        }
        for (int i = 1; i <= idx;++i){
            for (int j = t; j >= wei[i]; --j){
                dp[j] = max(dp[j], dp[j - wei[i]] + val[i]);
            }
        }
        cout << dp[t] << '\n';
    }
    return 0;
}
```

---

## 03 观赏樱花

**题面：** 给定开始/结束时间，求欣赏时长。n种樱花，每种消耗分钟数、获得美学价值、可看次数（0=无限）。求最大美学价值。

**核心思路：** 无限次→补次数为1001（总容量上限），然后统一二进制分组+01背包。时间解析：小时差×60+分钟差，若开始分钟>结束分钟则借位。

**坑点：** 输入格式含冒号，需跳过。

**代码：**
```cpp
// 关键转化
int cnt;
cin >> cost >> val >> cnt;
if (cnt == 0) cnt = 1001; // 无限次补足
// 然后二进制分组
```

---

## 04 多重背包 — 单调队列优化（最优复杂度）

**题面：** 同01，求O(n·t)解。

**核心思路：** ①**按余数分组**：重量w，按`j%w`分成w组，同组内格子只依赖同组(j, j-w, j-2w...)；②**指标改写**：把`dp[i-1][j]+k*v`改写为`(j/w)*v + max over窗口(dp[i-1][G]-G/w*v)`，式中`G`是窗口内各位置。指标只与G有关，不随j变化，可进单调队列；③**滑动窗口**：每次进一个新指标（G变小方向），出一个过期指标（超cnt个）。

空间压缩版从右往左+提前建窗口。

**坑点：** 理解关键是指标改写让值固定下来；窗口长度=`cnt+1`（含0个的情况）。

**代码：**
```cpp
// 单调队列优化（空间压缩版核心逻辑）
for (int i = 1; i <= n; i++) {
    int w = cost[i], v = val[i], cnt = num[i];
    for (int mod = 0; mod < min(t + 1, w); mod++) {
        int l = 0, r = 0;
        // 提前建窗口（先放cnt个，少放1个）
        for (int j = t - mod, enter = 0; j >= 0 && enter < cnt; j -= w, enter++) {
            while (l < r && value1(dp, j) >= value1(dp, window[r - 1])) r--;
            window[r++] = j;
        }
        // 逐格求解
        for (int j = t - mod, enter = 0; j >= 0; j -= w) {
            // 新指标进入
            int nextJ = j - (cnt + 1) * w;
            if (nextJ >= 0) {
                while (l < r && value1(dp, nextJ) >= value1(dp, window[r - 1])) r--;
                window[r++] = nextJ;
            }
            // 求dp[j]
            if (l < r) dp[j] = value1(dp, window[l]) + (j / w) * v;
            // 当前j过期
            if (l < r && window[l] == j) l++;
        }
    }
}
// value1: 指标值 = dp[g] - (g/w)*v
```

---

## 05 混合背包找零钱 — POJ 1742

**题面：** n种货币，面值a[i]和数量c[i]。求[1..m]中有多少金额能被凑出（不限制凑法，只要能凑出）。

**核心思路：** 对每种货币分三种情况处理：①`cnt==1`→01背包，从右往左；②`面值×cnt≥M`→完全背包（根本用不完），从左往右；③其他→多重背包窗口优化。由于是布尔类型，不需要单调队列pk指标，只需统计窗口内true的个数>0即可。每个余数组维护一个true计数，进窗口+1/出窗口-1。

**坑点：** 空间卡得严，必须空间压缩；右左左方向取决于类型。

**代码：**
```cpp
// 三种类型核心逻辑
for (int i = 1; i <= n; i++) {
    if (cnt[i] == 1) {
        // 01背包，从右往左
        for (int j = m; j >= a[i]; j--)
            if (dp[j - a[i]]) dp[j] = true;
    } else if (a[i] * cnt[i] >= m) {
        // 完全背包，从左往右
        for (int j = a[i]; j <= m; j++)
            if (dp[j - a[i]]) dp[j] = true;
    } else {
        // 多重背包窗口优化（布尔版）
        for (int mod = 0; mod < a[i]; mod++) {
            int trueCnt = 0;
            // 初始窗口
            for (int j = m - mod, k = 0; j >= 0 && k <= cnt[i]; j -= a[i], k++)
                if (dp[j]) trueCnt++;
            // 滑动窗口
            for (int j = m - mod, enter; j >= 0; j -= a[i]) {
                enter = j - (cnt[i] + 1) * a[i];
                if (enter >= 0 && dp[enter]) trueCnt++;
                if (trueCnt > 0) dp[j] = true;
                if (dp[j]) trueCnt--;
            }
        }
    }
}
int ans = 0;
for (int j = 1; j <= m; j++) if (dp[j]) ans++;
return ans;
```
