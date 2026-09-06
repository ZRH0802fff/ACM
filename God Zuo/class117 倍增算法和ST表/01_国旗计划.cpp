// 国旗计划
// 给定点的数量m，点的编号1~m，所有点围成一个环
// i号点一定顺时针到达i+1号点，最终m号点顺指针回到1号点
// 给定n条线段，每条线段(a, b)，表示线段从点a顺时针到点b
// 输入数据保证所有线段可以把整个环覆盖
// 输入数据保证每条线段不会完全在另一条线段的内部
// 也就是线段之间可能有重合但一定互不包含
// 返回一个长度为n的结果数组ans，ans[x]表示一定选x号线段的情况下
// 至少选几条线段能覆盖整个环
// 测试链接 : https://www.luogu.com.cn/problem/P4155
// 请同学们务必参考如下代码中关于输入、输出的处理
// 这是输入输出处理效率很高的写法
// 提交以下的code，提交时请把类名改成"Main"，可以直接通过

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200001;

const int LIMIT = 18;

int power;

// 每条线段3个信息 : 线段编号、线段左边界、线段右边界
struct Line {
	int id;   // 线段编号
	int l;    // 线段左边界
	int r;    // 线段右边界
};

Line line[MAXN << 1];

// stjump[i][p] : 从i号线段出发，跳的次数是2的p次方，能到达的最右线段的编号
int stjump[MAXN << 1][LIMIT];

int ans[MAXN];

int n, m;

// <=n最接近的2的幂，是2的几次方
int log2(int n) {
	int ans = 0;
	while ((1 << ans) <= (n >> 1)) {
		ans++;
	}
	return ans;
}

void build() {
	for (int i = 1; i <= n; i++) {
		if (line[i].l > line[i].r) {
			line[i].r += m;
		}
	}
	sort(line + 1, line + n + 1, [](const Line& a, const Line& b) {
		return a.l < b.l;
	}); 
	for (int i = 1; i <= n; i++) {
		line[i + n].id = line[i].id;
		line[i + n].l = line[i].l + m;
		line[i + n].r = line[i].r + m;
	}
	int e = n << 1;

	// i跳2的0次方能到的线段
	for (int i = 1, arrive = 1; i <= e; i++) {
		while (arrive + 1 <= e && line[arrive + 1].l <= line[i].r) {
			arrive++;
		}
		stjump[i][0] = arrive;
	}

	// i跳2的p次方能到的线段
	for (int p = 1; p <= power; p++) {
		for (int i = 1; i <= e; i++) {
			stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
		}
	}
}

int jump(int i) {
	int aim = line[i].l + m, cur = i, next, ans = 0;
	for (int p = power; p >= 0; p--) {
		next = stjump[cur][p];
		if (next != 0 && line[next].r < aim) {
			ans += 1 << p;
			cur = next;
		}
	}
	return ans + 1 + 1;
}  

void compute() {
	power = log2(n);
	build();
	for (int i = 1; i <= n; i++) {
		ans[line[i].id] = jump(i);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		line[i].id = i;
		cin >> line[i].l >> line[i].r;
	}
	compute();
	cout << ans[1];
	for (int i = 2; i <= n; i++) {
		cout << " " << ans[i];
	}
	cout << "\n";
	return 0;
}
