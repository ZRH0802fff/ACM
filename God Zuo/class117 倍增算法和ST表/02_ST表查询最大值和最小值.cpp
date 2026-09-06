// ST表查询最大值和最小值
// 给定一个长度为n的数组arr，一共有m次查询
// 每次查询arr[l~r]上的最大值和最小值
// 每次查询只需要打印最大值-最小值的结果
// 测试链接 : https://www.luogu.com.cn/problem/P2880
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50001;

// 2的15次方是<=50001且最接近的
// 所以次方可能是0~15
// 于是准备16长度够用了
const int LIMIT = 16;

int arr[MAXN];

// lg[i] : 查询<=i情况下，最大的2的幂，是2的几次方
int lg[MAXN];

int stmax[MAXN][LIMIT];

int stmin[MAXN][LIMIT];

void build(int n) {
	lg[0] = -1;
	for (int i = 1; i <= n; i++) {
		lg[i] = lg[i >> 1] + 1;
		stmax[i][0] = arr[i];
		stmin[i][0] = arr[i];
	}
	for (int p = 1; p <= lg[n]; p++) {
		for (int i = 1; i + (1 << p) - 1 <= n; i++) {
			stmax[i][p] = max(stmax[i][p - 1], stmax[i + (1 << (p - 1))][p - 1]);
			stmin[i][p] = min(stmin[i][p - 1], stmin[i + (1 << (p - 1))][p - 1]);
		}
	}
}

int query(int l, int r) {
	int p = lg[r - l + 1];
	int a = max(stmax[l][p], stmax[r - (1 << p) + 1][p]);
	int b = min(stmin[l][p], stmin[r - (1 << p) + 1][p]);
	return a - b;
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
