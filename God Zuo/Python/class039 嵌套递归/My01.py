class Solution:
    def solve(self, s: str) -> int:
        self.where=0
        chars = list(s.replace(" ", ""))
        return self.f(chars,0)
    
    def f(self,s,i):
        cur=0
        nums=[]
        ops=[]
        
        while  i<len(s) and s[i]!=")" :
            ch=s[i]
            if ch.isdigit():
                cur=cur*10+int(ch)
                i+=1 
            elif ch=='(':
                cur=self.f(s,i+1)
                i=self.where+1
            else:
                self.push(nums,ops,cur,ch)
                cur=0
                i+=1
        self.push(nums,ops,cur,'+')
        self.where=i
        return self.compute(nums,ops)
    
    def push(self,nums,ops,cur,ch):
        if not nums or ops[-1] in '+-':
            nums.append(cur)
            ops.append(ch)
        else:
            tn=nums.pop()
            tc=ops.pop()
            if tc=='*':
                nums.append(cur*tn)
            else:
                nums.append(tn//cur)
            ops.append(ch)
    
    def compute(self,nums,ops):
        if not nums:
            return 0
        ans=nums[0]
        for i in range(1,len(nums)):
            if ops[i-1]=='+':
                ans+=nums[i]
            else:
                ans-=nums[i]
        return ans