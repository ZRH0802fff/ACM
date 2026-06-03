from typing import List
class Solution:
    def canCompleteCircuit(self, gas: List[int], cost: List[int]) -> int:
        n=len(gas)
        l=0
        while l<n:
            r=l
            cur_sum=0
            while cur_sum+gas[r%n]-cost[r%n]>=0:
                if r-l+1==n:
                    return l
                cur_sum+=gas[r%n]-cost[r%n]
                r+=1
            l=r+1
        return -1