class Solution:
    def decodeString(self, s: str) -> str:
        s=list(s)
        self.where=0
        return self.f(0,s)
    
    def f(self,i,s):
        ans=[]
        cur=0
        while i<len(s) and s[i]!=']':
            ch=s[i]
            if ch.isdigit():
                cur=cur*10+int(ch)
                i+=1
            elif ch == '[':
                inner=self.f(i+1,s)
                for i in range(cur):
                    ans.append(inner)
                i=self.where+1
                cur=0
            else:
                ans.append(ch)
                i+=1
        self.where=i
        return ''.join(ans)
    