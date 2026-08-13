// 选择k个数字使得两集合累加和相差不超过1
// 给定一个正数n，表示1~n这些数字都可以选择
// 给定一个正数k，表示要从1~n中选择k个数字组成集合A，剩下数字组成集合B
// 希望做到集合A和集合B的累加和相差不超过1
// 如果能做到，返回集合A选择了哪些数字，任何一种方案都可以
// 如果不能做到，返回长度为0的数组
// 2 <= n <= 10^6
// 1 <= k <= n
// 来自真实大厂笔试，没有测试链接，用对数器验证

#include <bits/stdc++.h>
using namespace std;

// 结果数组最多装 k <= n <= 10^6 个数字
const int MAXN = 1000001;
// 对数器里 n = rand()%60 + 2，范围 [2, 61]；三维dp只用于验证
const int MAXV = 62;  // n + 1，n 最大 61
const int MAXK = 62;  // k + 1，k 最大 61
const int MAXS = 947; // wantSum + 1，wantSum 最大 946（61*62/2 = 1891，1891/2 + 1）

int ansArr[MAXN];
int ansLen;
int dp3D[MAXV][MAXK][MAXS];

bool canSplit(int n, int k);
bool f(int n, int i, int k, int s);
void build(long long sum, int n, int k);

// 正式方法
// 最优解
void pick(int n, int k) {
    long long sum = (long long)(n + 1) * n / 2;
    build(sum / 2, n, k);
    if (ansLen == 0 && (sum & 1) == 1) {
        build(sum / 2 + 1, n, k);
    }
}

// 1 ~ n这些数字挑选k个
// 能不能凑够累加和sum
// 能的话，返回挑选了哪些数字（写入 ansArr / ansLen）
// 不能的话，ansLen = 0
void build(long long sum, int n, int k) {
    long long minKSum = (long long)(k + 1) * k / 2;
    int range = n - k;
    if (sum < minKSum || sum > minKSum + (long long)range * k) {
        ansLen = 0;
        return;
    }
    // 100 15 -> 85
    long long need = sum - minKSum;
    int rightSize = (int)(need / range);
    int midIndex = (k - rightSize) + (int)(need % range);
    int leftSize = k - rightSize - (need % range == 0 ? 0 : 1);
    ansLen = k;
    for (int i = 0; i < leftSize; i++) {
        ansArr[i] = i + 1;
    }
    if (need % range != 0) {
        ansArr[leftSize] = midIndex;
    }
    for (int i = k - 1, j = 0; j < rightSize; i--, j++) {
        ansArr[i] = n - j;
    }
}

// 为了验证
// 检验得到的结果是否正确
bool pass(int n, int k) {
    if (ansLen == 0) {
        if (canSplit(n, k)) {
            return false;
        } else {
            return true;
        }
    } else {
        if (ansLen != k) {
            return false;
        }
        int sum = (n + 1) * n / 2;
        int pickSum = 0;
        for (int i = 0; i < ansLen; i++) {
            pickSum += ansArr[i];
        }
        return abs(pickSum - (sum - pickSum)) <= 1;
    }
}

// 记忆化搜索
// 不是最优解，只是为了验证
// 返回能不能做到
bool canSplit(int n, int k) {
    int sum = (n + 1) * n / 2;
    int wantSum = (sum / 2) + ((sum & 1) == 0 ? 0 : 1);
    memset(dp3D, 0, sizeof(dp3D));
    return f(n, 1, k, wantSum);
}

bool f(int n, int i, int k, int s) {
    if (k < 0 || s < 0) {
        return false;
    }
    if (i == n + 1) {
        return k == 0 && s == 0;
    }
    if (dp3D[i][k][s] != 0) {
        return dp3D[i][k][s] == 1;
    }
    bool ans = f(n, i + 1, k, s) || f(n, i + 1, k - 1, s - i);
    dp3D[i][k][s] = ans ? 1 : -1;
    return ans;
}

// 为了验证
// 对数器
int main() {
    srand((unsigned)time(0));
    int N = 60;
    int testTime = 5000;
    cout << "测试开始" << "\n";
    for (int i = 0; i < testTime; i++) {
        int n = rand() % N + 2;
        int k = rand() % n + 1;
        pick(n, k);
        if (!pass(n, k)) {
            cout << "出错了!" << "\n";
        }
    }
    cout << "测试结束" << "\n";
    return 0;
}
