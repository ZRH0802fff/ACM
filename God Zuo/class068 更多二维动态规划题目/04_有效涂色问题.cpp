// 有效涂色问题
// 给定n、m两个参数
// 一共有n个格子，每个格子可以涂上一种颜色，颜色在m种里选
// 当涂满n个格子，并且m种颜色都使用了，叫一种有效方法
// 求一共有多少种有效的涂色方法
// 1 <= n, m <= 5000
// 结果比较大请 % 1000000007 之后返回
// 对数器验证

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 5001;

int path[MAXN];
bool sett[MAXN];

// 暴力方法
// 为了验证
// 把所有填色的方法暴力枚举
// 然后一个一个验证是否有效
// 这是一个带路径的递归
// 无法改成动态规划
int f(int i, int n, int m) {
	if (i == n) {
		memset(sett, false, (m + 1) * sizeof(bool));
		int colors = 0;
		for (int c = 0; c < n; c++) {
			if (!sett[path[c]]) {
				sett[path[c]] = true;
				colors++;
			}
		}
		return colors == m ? 1 : 0;
	} else {
		int ans = 0;
		for (int j = 1; j <= m; j++) {
			path[i] = j;
			ans += f(i + 1, n, m);
		}
		return ans;
	}
}

int ways1(int n, int m) {
	return f(0, n, m);
}

// 正式方法
// 时间复杂度O(n * m)
// 已经展示太多次从递归到动态规划了
// 直接写动态规划吧
// 也不做空间压缩了，因为千篇一律
// 有兴趣的同学自己试试
int dp[MAXN][MAXN];

int ways2(int n, int m) {
	// dp[i][j]:
	// 一共有m种颜色
	// 前i个格子涂满j种颜色的方法数
	for (int i = 1; i <= n; i++) {
		dp[i][1] = m;
	}
	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= m; j++) {
			dp[i][j] = (int)(((long long)dp[i - 1][j] * j) % MOD);
			dp[i][j] = (int)((((long long)dp[i - 1][j - 1] * (m - j + 1)) + dp[i][j]) % MOD);
		}
	}
	return dp[n][m];
}

int main() {
	// 测试的数据量比较小
	// 那是因为数据量大了，暴力方法过不了
	// 但是这个数据量足够说明正式方法是正确的
	int N = 9;
	int M = 9;
	cout << "功能测试开始" << endl;
	for (int n = 1; n <= N; n++) {
		for (int m = 1; m <= M; m++) {
			int ans1 = ways1(n, m);
			int ans2 = ways2(n, m);
			if (ans1 != ans2) {
				cout << "出错了!" << endl;
			}
		}
	}
	cout << "功能测试结束" << endl;

	cout << "性能测试开始" << endl;
	int n = 5000;
	int m = 4877;
	cout << "n : " << n << endl;
	cout << "m : " << m << endl;
	auto start = chrono::steady_clock::now();
	int ans = ways2(n, m);
	auto end = chrono::steady_clock::now();
	cout << "取模之后的结果 : " << ans << endl;
	cout << "运行时间 : " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " 毫秒" << endl;
	cout << "性能测试结束" << endl;
	return 0;
}
