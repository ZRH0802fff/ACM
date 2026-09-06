// 出现次数最多的数有几个
// 给定一个长度为n的数组arr，该数组一定是有序的
// 一共有m次查询，每次查询arr[l~r]上出现次数最多的数有几个
// 对数器验证

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

void randomArray(int n, int v);
int checkQuery(int l, int r);

// 对数器
// 为了验证
int main() {
	srand(time(0));
	cout << "测试开始\n";
	int n = 10000;
	int v = 100;
	int m = 5000;
	randomArray(n, v);
	build(n);
	for (int i = 1, l, r; i <= m; i++) {
		l = rand() % n + 1;
		r = rand() % n + 1;
		if (query(l, r) != checkQuery(l, r)) {
			cout << "出错了!\n";
		}
	}
	cout << "测试结束\n";
	return 0;
}

// 得到随机数组
// 为了验证
void randomArray(int n, int v) {
	for (int i = 1; i <= n; i++) {
		arr[i] = rand() % (2 * v) - v;
	}
	sort(arr + 1, arr + n + 1);
}

// 暴力方法
// 直接遍历统计词频
// 为了验证
int checkQuery(int l, int r) {
	if (l > r) {
		int tmp = l;
		l = r;
		r = tmp;
	}
	unordered_map<int, int> freq;
	for (int i = l; i <= r; i++) {
		freq[arr[i]]++;
	}
	int ans = 0;
	for (auto& kv : freq) {
		ans = max(ans, kv.second);
	}
	return ans;
}
