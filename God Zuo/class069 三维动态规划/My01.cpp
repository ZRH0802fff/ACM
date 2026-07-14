#include<bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int dp[610][110][110];

    int f(vector<string>& strs,int i,int z,int o){
        if(i==(int)strs.size()){
            return 0;
        }
        if(dp[i][z][o]!=-1){
            return dp[i][z][o];
        }

    }

    int findMaxForm(vector<string> &strs, int m, int n)
    {
        int len = strs.size();
        
        for (int i = 0; i < len;++i){
            for (int j = 0; j <= m;++j){
                for (int k = 0; k <= n;++k)
                    dp[i][j][k] = -1;
            }
        }
        return f(strs, 0, m, n);
    }
    
};