from typing import List

class NumMatrix:

    def __init__(self, matrix: List[List[int]]):
        n=len(matrix)+1
        m=len(matrix[0])+1
        self.sum=[[0]*m for _ in range(n) ]
        for i in range(1,n):
            for j in range(1,n):
                self.sum[i][j]=matrix[i-1][j-1]
        for i in range(1,n):
            for j in range(1,m):
                self.sum[i][j]+=self.sum[i-1][j]-self.sum[i][j-1]-self.sum[i-1][j-1]

                    

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return (self.sum[row2+1][col2+1]-self.sum[row2+1][col1]-self.sum[row1][col2+1]+self.sum[row1][col1])