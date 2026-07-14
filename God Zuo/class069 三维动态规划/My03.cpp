// 测试链接 : https://leetcode.cn/problems/knight-probability-in-chessboard/
class Solution{
public:
    double dp[30][30][110];
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    double f(int n,int i,int j,int k){
        if(i<0 || i>=n || j<0 || j>=n)
            return 0;
        if(dp[i][j][k]!=-1.0)
            return dp[i][j][k];
        double ans = 0;
        if(k==0){
            ans = 1;
        }else{
            for (int t = 0; t < 8;++t){
                ans += (f(n, i + dx[t], j + dy[t], k - 1) /8.0);
            }
        }
        dp[i][j][k] = ans;
        return ans;
    }
    double knightProbability(int n, int k, int row, int column){
        for (int i = 0; i < 30;++i){
            for (int j = 0; j < 30;++j){
                for (int l = 0; l < 100;++l)
                    dp[i][j][l] = -1;
            }
        }
        return f(n, row, column, k);
    }
};