#include <bits/stdc++.h>
#include <string>
using namespace std;
class Solution
{
public:
    static bool dfs(vector<vector<char>> &b, int i, int j, const string &w, int k)
    {
        if (k == w.length())
            return true;
        if (i < 0 || j < 0 || i >= (int)b.size() || j >= (int)b[0].size() || b[i][j] != w[k])
            return false;
        char tmp = b[i][j];
        b[i][j] = '0';
        bool ans = dfs(b, i - 1, j, w, k + 1) || dfs(b, i + 1, j, w, k + 1) || dfs(b, i, j - 1, w, k + 1) || dfs(b, i, j + 1, w, k + 1);
        b[i][j] = tmp;
        return ans;
    }
    static bool exist(vector<vector<char>> &board, string word)
    {
        int n = board.size();
        int m = board[0].size();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (dfs(board, i, j, word, 0))
                {
                    return true;
                }
            }
        }
        return false;
    }
};