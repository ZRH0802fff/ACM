class Solution:
    def corpFlightBookings(self, bookings, n) :
        cnt=[0]*(n+2)
        for sta ,ed , k in bookings:
            cnt[sta]+=k
            cnt[ed+1]-=k
        for i in range(1,n+2):
            cnt[i]+=cnt[i-1]
        ans=[0]*n
        for i in range(n):
            ans[i]=cnt[i+1]
        return ans