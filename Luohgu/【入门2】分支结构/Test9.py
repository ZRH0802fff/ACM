def ifrun(year):
    return (year%400==0)or(year%4==0 and year%100!=0)

def rtday(year,mouth):
    arr= [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    if(mouth==2):
        return 29 if ifrun(year) else 28
    else:
        return arr[mouth]

def main():
    y,m=map(int ,input().split())
    print(rtday(y,m))

if __name__ == "__main__":
    main()