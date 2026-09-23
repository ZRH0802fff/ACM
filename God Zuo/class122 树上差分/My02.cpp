// 松鼠的新家(递归版)
// 有n个节点形成一棵树
// 给定一个由点编号组成的数组，表示松鼠依次要去往的地点
// 松鼠每走到一个节点都必须拿一个糖果，否则松鼠就停止前进
// 松鼠来到最后一个地点时不需要吃糖果
// 打印每个节点上至少准备多少糖果才能让松鼠依次走完数组里的节点
// 测试链接 : https://www.luogu.com.cn/problem/P3258

#include<bits/stdc++.h>
using namespace std;

const int maxn = 300010;
const int maxm = 600010;

int n;
int travl[maxn];
int num[maxn];

int headE[maxn];
int nxtE[maxm];
int toE[maxm];
int cntE;

int headQ[maxn];
int nxtQ[maxm];
int toQ[maxm];
int idxQ[maxm];
int cntQ;

bool vis[maxn];
int unoinfound[maxn];
int father[maxn];
int ans[maxn];

void build(){
    memset(num, 0, sizeof(num));
    cntQ = 1;
    cntE = 1;
    memset(headE, 0, sizeof(headE));
    memset(headQ, 0, sizeof(headQ));
}

void addEdge(int u,int v){
    nxtE[cntE] = headE[u];
    toE[cntE] = v;
    headE[u] = cntE++;
}

void addQuary(int u,int v,int i){
    nxtQ[cntQ] = headQ[u];
    toE[cntQ] = v;
    idxQ[cntQ] = i;
    headQ[u] = cntQ++;
}

int find(int i){
    if(i!=unoinfound[i]){
        unoinfound[i] = find(unoinfound[i]);
    }
    return unoinfound[i];
}

void tarjan(int u,int f){
    vis[u] = true;
    for (int e = headE[u], v; e != 0; e=nxtE[e]){
        v = toE[e];
        if(v!=f){
            tarjan(v, u);
            ans[idxQ[e]] = find(v);
        }
    }
    unoinfound[u] = f;
    father[u] = f;
}

void dfs(int u,int f){
    for (int e = headE[u], v; e != 0; e=nxtE[e]){
        v = toE[e];
        if(v!=f){
            dfs(v, u);
            num[u] += num[v];
        }
    }
}

void compute(int n){
    tarjan(1, 0);
    for (int i = 1, u, v, lca, lcaf; i < n; ++i){
        u = travl[i];
        v = travl[i + 1];
        lca = ans[i];
        lcaf = father[lca];
        num[u]++;
        num[v]++;
        num[lca]--;
        num[lcaf]--;
    }
    dfs(1, 0);
    for (int i = 2; i <= n; ++i){
        num[travl[i]]--;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    build();
    for (int i = 1; i <= n; ++i){
        cin >> travl[i];
    }
    for (int i = 1, u, v; i < n; ++i){
        cin >> u >> v;
        addEdge(u, v);
        addEdge(v, u);
    }
    for (int i = 1; i < n; ++i){
        addQuary(travl[i], travl[i + 1], i);
        addQuary(travl[i + 1], travl[i], i);
    }
    compute(n);
    for (int i = 1; i <= n; i++)
    {
        cout << num[i] << "\n";
    }
    return 0;
}