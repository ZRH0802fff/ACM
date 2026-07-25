// 单调栈模板：数组中每个元素左右两侧最近的比自己小的元素位置
// 输入：数组长度 n，然后 n 个数
// 输出：每行两个数，左侧最近小的位置 和 右侧最近小的位置（没有则为 -1）
// 注意：如果两侧有相等的值，只记录严格小于的位置（等于不算）

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int arr[MAXN];
int ansL[MAXN];
int ansR[MAXN];
int stk[MAXN];
int n, r;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n) {
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            ansL[i] = -1;
            ansR[i] = -1;
        }

        r = 0;
        // 遍历阶段
        for (int i = 0; i < n; i++) {
            while (r > 0 && arr[stk[r - 1]] >= arr[i]) {
                int cur = stk[--r];
                ansL[cur] = r > 0 ? stk[r - 1] : -1;
                ansR[cur] = i;
            }
            stk[r++] = i;
        }

        // 清算阶段
        while (r > 0) {
            int cur = stk[--r];
            ansL[cur] = r > 0 ? stk[r - 1] : -1;
            ansR[cur] = -1;
        }

        // 修正阶段：相等元素修正右侧答案
        for (int i = n - 2; i >= 0; i--) {
            if (ansR[i] != -1 && arr[ansR[i]] == arr[i]) {
                ansR[i] = ansR[ansR[i]];
            }
        }

        for (int i = 0; i < n; i++) {
            cout << ansL[i] << " " << ansR[i] << "\n";
        }
    }
    return 0;
}
