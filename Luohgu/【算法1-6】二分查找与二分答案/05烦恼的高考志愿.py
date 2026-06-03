import sys
data=list(map(int,sys.stdin.read().split()))
m,n=data[0],data[1]
line=data[2:2+m]
sc=data[2+m:]
line.sort()
sc.sort()
idx_l,idx_sc=0,0
ans=0
#print(line)
#print(sc)
while idx_sc<n:
    cur_sc=sc[idx_sc]
    #print(cur_sc)
    while idx_l<m and cur_sc>line[idx_l]:
        idx_l+=1
    if idx_l==m: idx_l-=1   ###重要DeBug点，分数线数组已经被卡到最后一个但是仍有很多分时，指针会在第二次
                            ###+1然后越界，但只会加一次，每次只需特判-1即可
     #print(1,cur_sc,idx_l)
    ans+=min(abs(line[idx_l-1]-cur_sc),abs(line[idx_l]-cur_sc))
    #print(cur_sc,ans)
    idx_sc+=1
print(ans)