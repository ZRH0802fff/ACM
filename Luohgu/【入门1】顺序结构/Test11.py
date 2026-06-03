s,v=map(int ,input().split())
t=(s+v-1)//v+10
start=(8*60-t)%1440
h=start//60
m=start%60
print(f"{h:02d}:{m:02d}")