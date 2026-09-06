// 在传球游戏中最大化函数值
// 给定一个长度为n的数组receiver和一个整数k
// 总共有n名玩家，编号0 ~ n-1，这些玩家在玩一个传球游戏
// receiver[i]表示编号为i的玩家会传球给下一个人的编号
// 玩家可以传球给自己，也就是说receiver[i]可能等于i
// 你需要选择一名开始玩家，然后开始传球，球会被传恰好k次
// 如果选择编号为x的玩家作为开始玩家
// 函数f(x)表示从x玩家开始，k次传球内所有接触过球的玩家编号之和
// 如果某位玩家多次触球，则累加多次
// f(x) = x + receiver[x] + receiver[receiver[x]] + ...
// 你的任务时选择开始玩家x，目的是最大化f(x)，返回函数的最大值
// 测试链接 : https://leetcode.cn/problems/maximize-value-of-function-in-a-ball-passing-game/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100001;

const int LIMIT = 34;

int power;

// 给定k的二进制位上有几个1
int m;

// 收集k的二进制上哪些位有1
int kbits[LIMIT];

int stjump[MAXN][LIMIT];

long long stsum[MAXN][LIMIT];

void build(long long k) {
	power = 0;
	while ((1LL << power) <= (k >> 1)) {
		power++;
	}
	m = 0;
	for (int p = power; p >= 0; p--) {
		if ((1LL << p) <= k) {
			kbits[m++] = p;
			k -= 1LL << p;
		}
	}
}

class Solution {
public:
	// 该方法是树上倍增的解法
	// 打败比例很一般但是非常好想
	// 这个题最优解来自对基环树的分析
	// 后面的课会安排基环树的内容
	long long getMaxFunctionValue(vector<int>& receiver, long long k) {
		build(k);
		int n = receiver.size();
		for (int i = 0; i < n; i++) {
			stjump[i][0] = receiver[i];
			stsum[i][0] = receiver[i];
		}
		for (int p = 1; p <= power; p++) {
			for (int i = 0; i < n; i++) {
				stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
				stsum[i][p] = stsum[i][p - 1] + stsum[stjump[i][p - 1]][p - 1];
			}
		}
		long long sum, ans = 0;
		for (int i = 0, cur; i < n; i++) {
			cur = i;
			sum = i;
			for (int j = 0; j < m; j++) {
				sum += stsum[cur][kbits[j]];
				cur = stjump[cur][kbits[j]];
			}
			ans = max(ans, sum);
		}
		return ans;
	}
};

int main() {
	Solution sol;
	vector<int> receiver = { 2, 0, 1 };
	long long k = 4;
	cout << sol.getMaxFunctionValue(receiver, k) << "\n"; // 6
	return 0;
}
