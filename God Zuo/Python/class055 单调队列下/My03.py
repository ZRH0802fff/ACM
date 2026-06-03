# 测试链接 : https://leetcode.cn/problems/maximum-number-of-tasks-you-can-assign/
class Solution:
    def maxTaskAssign(self, tasks: list[int], workers: list[int], pills: int, strength: int) -> int:
        tasks.sort()
        workers.sort()
        tlen=len(tasks)
        wlen=len(workers)
        q=[0]*tlen

        #检查能否完成m个项目
        def f(m):
            if m==0:
                return True
            h=t=0
            cnt=0
            j=0
            for i in range(wlen-m,wlen):
                eg=workers[i]
                while j<m and tasks[j]<=eg:
                    q[t]=j
                    t+=1
                    j+=1
                if h<t and tasks[q[h]]<=eg:
                    h+=1
                else:
                    while j<m and tasks[j]<=eg+strength:
                        q[t]=j
                        t+=1
                        j+=1
                    if h<t:
                        t-=1
                        cnt+=1
                    else:
                        return False
            return cnt<=pills

        ans=0
        l=0
        r=min(tlen,wlen)
        while l<=r:
            mid=(r+l)//2
            if f(mid):
                ans=mid
                l=mid+1
            else:
                r=mid-1
        return ans