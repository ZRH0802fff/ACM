class Solution:
    def generatePermutation(self , s: str):
        rs=set()
        def f(i,path):
            if i==len(s):
                rs.add(''.join(path))
                return
            path.append(s[i])
            i+=1
            f(i,path)
            path.pop()
            f(i,path)
        path=[]
        f(0,path)
        return list(rs)
    
class Solution:
    def generatePermutation(self , s: str)  :
        rs=set()
        path=['']*len(s)
        def f(i,size):
            if i==len(s):
                rs.add(''.join(path[:size]))
                return
            path[size]=s[i]
            f(i+1,size+1)
            f(i+1,size)
        f(0,0)
        return list(rs)