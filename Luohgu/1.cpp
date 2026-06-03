#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// 全局变量，方便函数访问
int n, m;
vector<long long> arr;

bool ok(long long msum)
{
    long long op = 0;
    long long tsum = 0;
    int idx = 0;

    while (idx < n && op < m)
    {
        if (idx + 1 == n)
        {
            tsum += arr[idx];
            if (tsum <= msum)
            {
                op += 1;
            }
            else
            {
                op += 2;
            }
            return op <= m;
        }

        tsum += arr[idx];
        if (tsum > msum)
        {
            op += 1;
            tsum = arr[idx];
        }
        idx += 1;
    }
    return false;
}

int main()
{
    // 优化输入输出速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 读取 n 和 m
    if (!(cin >> n >> m))
        return 0;

    arr.resize(n);
    long long max_val = 0;
    long long sum_val = 0;

    // 读取数组并同时计算 max(arr) 和 sum(arr)
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
        sum_val += arr[i];
    }

    // 二分查找初始化
    long long l = max_val;
    long long r = sum_val;
    long long ans = r;

    while (l <= r)
    {
        long long mid = l + (r - l) / 2; // 等同于 (l + r) / 2，这样写可以防止 l+r 溢出
        if (ok(mid))
        {
            r = mid - 1;
            ans = (mid < ans) ? mid : ans;
        }
        else
        {
            l = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}