class Employee:
    def __init__(self, company, age):
        self.company = company
        self.age = age
    
    def __str__(self):
        return f"{self.company} , {self.age}"


arr = [
    Employee(2, 27),
    Employee(1, 60),
    Employee(4, 19),
    Employee(3, 23),
    Employee(1, 35),
    Employee(3, 55),
]

print("原顺序：")
for e in arr: print(e)

# ───────────── 各种排序方式 ─────────────

print("\n1. 按年龄升序（最简单）")
arr.sort(key=lambda x: x.age)
for e in arr: print(e)

print("\n2. 按年龄降序（两种写法等价）")
arr.sort(key=lambda x: -x.age)
# arr.sort(key=lambda x: x.age, reverse=True)
for e in arr: print(e)

print("\n3. 先 company 升序，公司相同再 age 升序（最常用）")
arr.sort(key=lambda x: (x.company, x.age))
for e in arr: print(e)

print("\n4. 先 company 升序，公司相同再 age 降序")
arr.sort(key=lambda x: (x.company, -x.age))
for e in arr: print(e)