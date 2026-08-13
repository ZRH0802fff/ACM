#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

string l,r;
const int MOD=1e9+7;
int dp[1010][11][11][2];

void build(int n){
    for(int a=0;a<n;++a){
        for(int b=0;b<11; ++b){
            for(int c=0;c<11; ++c){
                for( int d=0;d<2; ++d){
                    dp[a][b][c][d]=-1;
                }
            }
        }
    }
}

/*
从num高位开始，来到i位
前一位是p，前前一位是pp，如果是10表示还没开始有数字
free表示前一位和num一样，不可以随便选
返回<=num的非萌数有多少个
*/
int f(string& num,int i,int pp,int p,int free){
    if(i==num.length()) return 1;
    if(dp[i][pp][p][free]!=-1) return dp[i][pp][p][free];
    int ans=0;
    if(free==0){
        if(p==10){
            ans=(ans+f(num,i+1,10,10,1))%MOD;
            for(int cur=1;cur<num[i]-'0'; ++cur){
                ans=(ans+f(num,i+1,p,cur,1))%MOD;
            }
            ans=(ans+f(num,i+1,p,num[i]-'0',0))%MOD;
        }else{
            for(int cur=0;cur<num[i]-'0'; ++cur){
                if(pp!=cur && p!=cur){
                    ans=(ans+f(num,i+1,p,cur,1))%MOD;
                }
            }
            if(pp!=num[i]-'0' && p!=num[i]-'0'){
                ans=(ans+f(num,i+1,p,num[i]-'0',0))%MOD;
            }
        }
    }else{
        if(p==10){
            ans=(ans+f(num,i+1,10,10,1))%MOD;
            for(int cur=1; cur<=9; ++cur){
                ans=(ans+f(num,i+1,p,cur,1))%MOD;
            }
        }else{
            for(int cur=0;cur<10; ++cur){
                if(pp!=cur && p!=cur){
                    ans=(ans+f(num,i+1,p,cur,1))%MOD;
                }
            }
        }
    }
    dp[i][pp][p][free]=ans;
    return ans;
}

int cnt(string & num){
    if(num[0]=='0') return 0;
    int n=num.length();
    ll all=0;
    ll base=1;
    for(int i=n-1;i>=0; --i){
        all=(all+base*(num[i]-'0'))%MOD;
        base=(base*10)%MOD;
    }
    build(n);
    return (all-f(num,0,10,10,0)+1+MOD)%MOD;
}

bool check(string& num){
    for(int pp=-2,p=-1,i=0;i<num.length(); ++pp,++p,++i){
        if(pp>=0 && num[pp]==num[i]) return true;
        if(p>=0 && num[p]==num[i]) return true;
    }
    return false;
}

int main(){
    cin>>l>>r;
    int ans=(cnt(r)-cnt(l)+MOD)%MOD;
    if(check(l)){
        ans++;
        ans%=MOD;
    }
    cout<<ans<<endl;
    return 0;
}