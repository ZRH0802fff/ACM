#include<bits/stdc++.h>
using namespace std;

const int maxn = 27;
const int maxm = 1010;
int n = 26, m;
string str[maxm];
int a[maxm];
int b[maxm];
int eidarr[maxm];

int head[maxn];
int nxt[maxm];
int to[maxm];
string weight[maxm];
int cntg;

int cur[maxn];
int outDeg[maxn];
int inDeg[maxn];

string path[maxm];
int cntp;

bool EdgeCmp(int i,int j){
    if(a[i]!=a[j])  return a[i] < a[j];
    return str[i] < str[j];
}

void addEdge(int u,int v,string w){
    nxt[++cntg] = head[u];
    to[cntg] = v;
    weight[cntg]=w;
    head[u] = cntg;
}

int char_sta(const string& str){
    return (int)(str[0] - 'a' + 1);
}

int char_ed(const string& str){
    return (int)(str[(int)str.size() - 1] - 'a' + 1);
}

int directedstart(){
    int sta=-1,ed=-1;
    for (int i = 1; i <= n; ++i){
        int v = outDeg[i] - inDeg[i];
        if(v<-1 || v>1 ||(v==1 && sta!=-1) || (v==-1 && ed!=-1)) return -1;
        if(v==1) sta=i;
        if(v==-1) ed=i;
    }
    if((sta==-1)^(ed==-1)) return -1;
    if(sta!=-1) return sta;
    for (int i = 1; i <= n;++i){
        if(outDeg[i]>0){
            return i;
        }
    }
    return -1;
}

void euler(int u,string w){
    for (int e = cur[u]; e > 0;e=cur[u]){
        cur[u] = nxt[e];
        euler(to[e], weight[e]);
    }
    path[++cntp] = w;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m;
    for (int i = 1; i <= m; ++i){
        cin >> str[i];
        a[i] = char_sta(str[i]);
        b[i] = char_ed(str[i]);
        eidarr[i] = i;
    }

    sort(eidarr + 1, eidarr + m + 1, EdgeCmp);
    for (int l = 1, r = 1; l <= m;l=++r){
        while(r+1<=m && a[eidarr[l]]==a[eidarr[r+1]]) r++;
        for (int i = r, u, v; i >= l;--i){
            u = a[eidarr[i]];
            v = b[eidarr[i]];
            outDeg[u]++;
            inDeg[v]++;
            addEdge(u, v, str[eidarr[i]]);
        }
        for (int i = 1; i <= n;++i){
            cur[i] = head[i];
        }
    }

    int sta = directedstart();
    if(sta==-1){
        cout << "***\n";
    }else{
        euler(sta, "");
        if(cntp!=m+1){
            cout << "***\n";
        }else{
            cout << path[cntp - 1];
            for (int i = cntp - 2; i >= 1; --i){
                cout << '.' << path[i];
            }
            cout << '\n';
        }
    }
    return 0;
}
