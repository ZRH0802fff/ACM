MOD = 10**9 + 7

class Solution:
    def numDecodings(self, s: str) -> int:
        n = len(s)
        dp = [-1] * (n + 1)
        
        def f(i):
            if i == n:
                return 1
            if dp[i] != -1:
                return dp[i]
            if s[i] == '0':
                return 0
                
            ans = f(i + 1) * (9 if s[i] == '*' else 1)
            
            if i + 1 < n:
                if s[i] != '*':
                    if s[i + 1] != '*':
                        if int(s[i:i+2]) <= 26:
                            ans += f(i + 2)
                    else:
                        if s[i] == '1':
                            ans += f(i + 2) * 9
                        elif s[i] == '2':
                            ans += f(i + 2) * 6
                else:
                    if s[i + 1] != '*':
                        if s[i + 1] <= '6':
                            ans += f(i + 2) * 2
                        else:
                            ans += f(i + 2)
                    else:
                        ans += f(i + 2) * 15
                        
            ans %= MOD
            dp[i] = ans
            return ans
            
        return f(0)
    def numDecodings2(self, s: str) -> int:
        n = len(s)
        dp = [0] * (n + 1)
        dp[n] = 1
        
        for i in range(n - 1, -1, -1):
            if s[i] == '0':
                dp[i] = 0
            else:
                ans = dp[i + 1] * (9 if s[i] == '*' else 1)
                
                if i + 1 < n:
                    if s[i] != '*':
                        if s[i + 1] != '*':
                            if int(s[i:i+2]) <= 26:
                                ans += dp[i+2]
                        else:
                            if s[i] == '1':
                                ans += dp[i+2] * 9
                            elif s[i] == '2':
                                ans += dp[i+2] * 6
                    else:
                        if s[i + 1] != '*':
                            if s[i + 1] <= '6':
                                ans += dp[i+2] * 2
                            else:
                                ans += dp[i+2]
                        else:
                            ans += dp[i+2] * 15
                            
                dp[i] = ans % MOD
        return dp[0]