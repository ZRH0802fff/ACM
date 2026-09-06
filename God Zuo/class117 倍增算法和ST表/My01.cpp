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

#include<bits/stdc++.h>
using namespace std;

int n, m;
struct Line{int id,l,r;} line[400010];

// st[i][p] -> 从i号线段出发，跳2的p次方，能到达的最右端线段
int st[400010][20];
int power;
int ans[200010];

void build(){
    for (int i = 1; i <= n; ++i){
        if(line[i].l>line[i].r){
            line[i].r += m;
        }
    }

    sort(line + 1, line + 1 + n, [](const Line &a, const Line &b)
         { return a.l < b.l; });
    for (int i = 1; i <= n; ++i){
        line[i + n].id = line[i].id;
        line[i + n].l = line[i].l+m;
        line[i + n].r = line[i].r+m;
    }
    int e = n << 1;

    for (int i = 1, j = 1; i <= e; ++i){
        while(j+1<=e && line[j+1].l<=line[i].r){
            j++;
        }
        st[i][0] = j;
    }
    for (int p = 1; p <= power; ++p){
        for (int i = 1; i <= e; ++i){
            st[i][p] = st[st[i][p - 1]][p - 1];
        }
    }
}

int jump(int i){
    int aim = line[i].l + m, cur = i, nxt, ans = 0;
    for (int p = power; p >= 0; --p){
        nxt = st[cur][p];
        if (nxt != 0 &&line[nxt].r < aim){
            ans += 1 << p;
            cur = nxt;
        }
    }
    return ans + 2;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i){
        line[i].id = i;
        cin >> line[i].l >> line[i].r;
    }

    power = log2(n);
    build();
    for (int i = 1; i <= n; ++i){
        ans[line[i].id] = jump(i);
    }
    for (int i = 1; i <= n; ++i){
        cout << ans[i] << ' ';
    }
    cout << '\n';
    return 0;
}