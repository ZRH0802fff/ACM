class Solution:
    def countOfAtoms(self, formula: str) -> str: 
        self.where=0
        book=self.f(0,list(formula))
        tm=[]
        for t in book :
            tm.append(t)
        tm.sort()

        ans=[]
        for t in tm:
            ans.append(tm)
            cnt=book[t]
            if cnt>1:
                ans.append(str[cnt])
        return ''.join(ans)

    def f(self,i,s):
        #解析字符串，返回字典
        ans={} 
        name=[]          #历史1
        pre=None         #历史2
        cnt=0            #倍数
        while i<len(s) and s[i]!=')':
            ch=s[i]
            if 'A'<=ch<='Z' or ch=='(':
                #遇到清算条件，先清算前面的
                self._fill(ans,name,pre,cnt)
                #清算之后，将历史清空
                name=[]
                pre=None
                cnt=0

                if ch=='(':
                    pre=self.f(s,i+1)
                    i=self.where+1
                else:
                    name.append(ch)
                    i+=1
            elif 'a'<=ch<='z':
                name.append(ch)
                i+=1
            else:
                cnt=cnt*10+int(ch)
                i+=1
        self._fill(ans,name,pre,cnt)
        self.where=i
        return ans
    
    def _fill(self,ans,name,pre,cnt):
        if name or pre:
            cnt=1 if cnt==0 else cnt

            if name:
                t=''.join(name)
                ans[t]=ans.get(t,0)+cnt
            else:
                for t in pre :
                    ans[t]=ans.get[t,0]+pre[t]*cnt
