// ST表查询最大公约数
// 给定一个长度为n的数组arr，一共有m次查询
// 每次查询arr[l~r]上所有数的最大公约数
// 测试链接 : https://www.luogu.com.cn/problem/P1890
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1001;

const int LIMIT = 10;

int arr[MAXN];

int lg[MAXN];

int stgcd[MAXN][LIMIT];

int gcd(int a, int b);

void build(int n) {
	lg[0] = -1;
	for (int i = 1; i <= n; i++) {
		lg[i] = lg[i >> 1] + 1;
		stgcd[i][0] = arr[i];
	}
	for (int p = 1; p <= lg[n]; p++) {
		for (int i = 1; i + (1 << p) - 1 <= n; i++) {
			stgcd[i][p] = gcd(stgcd[i][p - 1], stgcd[i + (1 << (p - 1))][p - 1]);
		}
	}
}

// 算法讲解041 - 辗转相除法求最大公约数
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int query(int l, int r) {
	int p = lg[r - l + 1];
	return gcd(stgcd[l][p], stgcd[r - (1 << p) + 1][p]);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	build(n);
	for (int i = 1, l, r; i <= m; i++) {
		cin >> l >> r;
		cout << query(l, r) << "\n";
	}
	return 0;
}
