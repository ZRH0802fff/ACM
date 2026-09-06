// 树节点的第K个祖先
// 树上有n个节点，编号0 ~ n-1，树的结构用parent数组代表
// 其中parent[i]是节点i的父节点，树的根节点是编号为0
// 树节点i的第k个祖先节点，是从节点i开始往上跳k步所来到的节点
// 实现TreeAncestor类
// TreeAncestor(int n, int[] parent) : 初始化
// getKthAncestor(int i, int k) : 返回节点i的第k个祖先节点，不存在返回-1
// 测试链接 : https://leetcode.cn/problems/kth-ancestor-of-a-tree-node/

#include<bits/stdc++.h>
using namespace std;

const int maxn=500010;
const int limit = 16;
int power;

int head[maxn];
int nxt[maxn];
int to[maxn];
int cnt;

int deep[maxn];
int st[maxn][limit];

int log2(int n){
    int ans = 0;
    while((1<<ans)<=(n>>1)) ans++;
    return ans;
}

void addEdge(int u, int v){
    nxt[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
}

void dfs(int i, int f){
    if(i==0){
        deep[i] = 1;
    } else {
        deep[i] = deep[f] + 1;
    }

    st[i][0] = f;
    for (int p = 1; p <= power; ++p){
        st[i][p] = st[st[i][p - 1]][p - 1];
    }
    for (int e = head[i]; e != 0; e=nxt[e]){
        dfs(to[e], i);
    }
}

class TreeAncestor {
public:
    TreeAncestor(int n, vector<int>& parent) {
        power = log2(n);
        cnt = 1;
        memset(head, 0, sizeof(head));
        for (int i = 1; i < parent.size(); ++i){
            addEdge(parent[i], i);
        }
        dfs(0, 0);
    }
    
    int getKthAncestor(int i, int k) {
        if(deep[i]<=k){
            return -1;
        }

        int s = deep[i] - k;
        for (int p = power; p >= 0; --p){
            if(deep[st[i][p]]>=s){
                i = st[i][p];
            }
        }
        return i;
    }
};