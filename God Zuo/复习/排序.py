arr=[[1,2,3] , [2,3,4] , [0,2,2]]
arr.sort(key= lambda x :(x[1],-x[0]))
print(arr)