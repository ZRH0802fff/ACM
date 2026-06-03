class Solution:
    def nthMagicalNumber(self, n: int, a: int, b: int) -> int:
        MOD = 10**9 + 7
        ans=0
        lcm=self.lcm(a,b)
        l=min(a,b)
        r=n*min(a,b)
        while l<=r:
            mid=(l+r)//2
            count=mid//a+mid//b-mid//lcm
            if count>=n:
                ans=mid
                r=mid-1
            else:
                l=mid+1
        return ans%MOD




    def gcd(self,a,b):
        return a if b==0 else self.gcd(b,a%b)
    def lcm(self,a,b):
        return a//self.gcd(a,b)*b