#include<bits/stdc++.h>
using namespace std;

unordered_set<int> isstack;

int n;
int T;
int stk[2000010];
int tail;

void build(){

    tail=0;
    isstack.clear();
}

void prt(){
    for (int i = 0; i < tail; ++i){
        cout << stk[i] << ' ';
    }
    cout << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while(T--){
        cin >> n;
        build();
        for (int i = 0; i < n; ++i){
            char op;
            int num;
            cin >> op >> num;
            if(op=='+'){
                //有
                if(isstack.count(num)){
                    while (tail>0 && stk[tail-1]!=num){
                        isstack.erase(stk[tail--]);
                        cout << '-';
                    }
                    isstack.erase(stk[tail--]);
                    cout << '-';
                }
                //没有 tiaoguo
                cout << '+';
                isstack.insert(num);
                stk[tail++]=num;
            }else if(op=='F'){
                if(isstack.count(num)){
                    while (tail>0 && stk[tail-1]!=num){
                        isstack.erase(stk[tail--]);
                        cout << '-';
                    }
                    isstack.erase(stk[tail--]);
                    cout << '-';
                }
                cout << '?';
            }else if(op=='T'){
                cout << '?';
            }
            //prt();
        }
        for (int i = 0; i < tail; ++i){
            cout << '-';
        }
        cout << '\n';
    }
    return 0;
}
