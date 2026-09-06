// 出现次数最多的数有几个
// 给定一个长度为n的数组arr，该数组一定是有序的
// 一共有m次查询，每次查询arr[l~r]上出现次数最多的数有几个
// 题目查看 : https://www.luogu.com.cn/problem/UVA11235
// 题目提交 : https://vjudge.net/problem/UVA-11235
// 洛谷上提交会发生远程连接错误，需要绑定一个UVA账号再提交
// 也可以注册一个vjudge账号来提交，不过如果UVA链接不上就需要等
// 其实用对数器验证即可，我肯定是提交通过测试了的
// 提交以下的code，提交时请把类名改成"Main"

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

const int LIMIT = 17;

int arr[MAXN];

int lg[MAXN];

int bucket[MAXN];

int lft[MAXN];

int rgt[MAXN];

int stmax[MAXN][LIMIT];

void build(int n) {
	// 题目给定的数值范围-100000 ~ +100000
	// 把arr[0]设置成不会到达的数字即可
	arr[0] = -23333333;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		if (arr[i - 1] != arr[i]) {
			rgt[cnt] = i - 1;
			lft[++cnt] = i;
		}
		bucket[i] = cnt;
	}
	rgt[cnt] = n;
	lg[0] = -1;
	for (int i = 1; i <= cnt; i++) {
		lg[i] = lg[i >> 1] + 1;
		stmax[i][0] = rgt[i] - lft[i] + 1;
	}
	for (int p = 1; p <= lg[cnt]; p++) {
		for (int i = 1; i + (1 << p) - 1 <= cnt; i++) {
			stmax[i][p] = max(stmax[i][p - 1], stmax[i + (1 << (p - 1))][p - 1]);
		}
	}
}

int query(int l, int r) {
	if (l > r) {
		int tmp = l;
		l = r;
		r = tmp;
	}
	int lbucket = bucket[l];
	int rbucket = bucket[r];
	if (lbucket == rbucket) {
		return r - l + 1;
	}
	// a : 最左侧桶在此时l~r范围上的数字有几个
	// b : 最右侧桶在此时l~r范围上的数字有几个
	int a = rgt[lbucket] - l + 1, b = r - lft[rbucket] + 1, c = 0;
	if (lbucket + 1 < rbucket) {
		int from = lbucket + 1, to = rbucket - 1, p = lg[to - from + 1];
		c = max(stmax[from][p], stmax[to - (1 << p) + 1][p]);
	}
	return max(max(a, b), c);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	while (cin >> n) {
		if (n == 0) {
			break;
		}
		cin >> m;
		for (int i = 1; i <= n; i++) {
			cin >> arr[i];
		}
		build(n);
		for (int i = 1, l, r; i <= m; i++) {
			cin >> l >> r;
			cout << query(l, r) << "\n";
		}
	}
	return 0;
}
