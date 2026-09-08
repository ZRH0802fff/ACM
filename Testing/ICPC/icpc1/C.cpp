#include <bits/stdc++.h>
using namespace std;

int T;
int n, m;
int ans[1000010];

int pl, pr;

struct Query{
    int l;
    int r;
    vector<int> arr;
    bool operator()(const Query& a,const Query& b) const{
        if(a.l==b.l)  return a.r<b.r;
        return a.l < b.l;
    }
} query[1000010];

struct Node{
    int val;
    Node *nxt,*pre;
};
Node *head, *tail;

void initialize(int val){
    head = new Node();
    tail = new Node();
    head->nxt = tail;
    tail->pre = head;
    head->val = val;
}

void insert(Node *p,int val,Node *q){
    q = new Node();
    q->val = val;
    p->nxt->pre = q;
    q->nxt = p->nxt;
    p->nxt = q;
    q->pre = p;
}

void remove(Node *p){
    p->pre->nxt = p->nxt;
    p->nxt->pre = p->pre;
    delete p;
}


void build(){
    memset(ans, 0, sizeof(ans));
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while(T--){
        cin >> n >> m;
        build();
        for (int i = 0, l, r; i < m; ++i){
            cin >> query[i].l >> query[i].r;
            for (int j = l; j <= r;++j){
                int num;
                cin >> num;
                query[i].arr.push_back(num);
            }
        }
        sort(query, query+m);
        pl = pr = -1;
        for (int i = 0; i < m; ++i){
            if(query[i].l>pr){
                initialize(query[i].arr[0]);
                Node *p = head;
                // for (int idx = 1; idx < query[i].arr.size(); ++idx){
                //     //*p=insert(p, query[i].arr[idx], new Node());
                // }

            }
        }
    }
}