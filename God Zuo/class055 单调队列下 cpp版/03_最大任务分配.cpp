// 最大任务分配 — LeetCode 2071
// 有 tasks 和 workers，pills 片药（每片药让工人力量+strength）
// 求最多能完成多少个任务
// 二分答案 + 贪心 + 双端队列

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
int q[MAXN];
int h, t;

class Solution {
public:
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int tsize = tasks.size(), wsize = workers.size();

        auto check = [&](int m) -> bool {
            if (m == 0) return true;
            h = t = 0;
            int cnt = 0; // 用药数
            // 用最强的 m 个工人，从最弱的开始派活
            for (int i = wsize - m, j = 0; i < wsize; i++) {
                int worker = workers[i];
                // 不吃药能做的任务入队
                while (j < m && tasks[j] <= worker) q[t++] = j++;
                if (h < t && tasks[q[h]] <= worker) {
                    h++; // 不吃药，做最简单的任务
                } else {
                    // 吃药！能做的任务入队
                    while (j < m && tasks[j] <= worker + strength) q[t++] = j++;
                    if (h < t) {
                        cnt++; // 吃药了，做最难的（队尾出队）
                        t--;
                    } else {
                        return false; // 吃了药都做不了，失败
                    }
                }
            }
            return cnt <= pills;
        };

        int ans = 0, l = 0, r = min(tsize, wsize);
        while (l <= r) {
            int mid = (l + r) / 2;
            if (check(mid)) { ans = mid; l = mid + 1; }
            else r = mid - 1;
        }
        return ans;
    }
};
