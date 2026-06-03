# 数组中交换i和j位置的数
def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]

# 选择排序
def selection_sort(arr):
    if arr is None or len(arr)<2:
        return
    for i in range(len(arr)-1):
        min_idx=i
        for j in range(i,len(arr)-1):
            if arr[j]<arr[min_idx]:
                min_idx=j
    swap(arr,i,min_idx)        

# 冒泡排序
def bubble_sort(arr):
    if arr is None or len(arr)<2:
        return
    for end in range(len(arr)-1,0,-1):
        for i in range(end):
            if arr[i]<arr[i+1]:
                swap(arr,i,i+1)
    
    

# 插入排序
def insertion_sort(arr):
    if arr is None or len(arr)<2:
        return
    for i in range(1,len(arr)):
        j=i-1
        while j>=0 and arr[j]>arr[j+1]:
            swap(arr,j,j+1)
            j-=1