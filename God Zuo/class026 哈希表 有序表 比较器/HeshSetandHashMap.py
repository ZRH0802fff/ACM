# Integer、Long、Double、Float
# Byte、Short、Character、Boolean
# String等都有这个特征（hashCode和equals基于值）

str1 = "Hello"
str2 = "".join("Hello")          # 强制创建新的字符串对象（模拟new String("Hello")）

# false，因为不同的内存地址（身份不同）
print(str1 is str2)
# true，因为它们的值是相同的
print(str1 == str2)

s = set()
s.add(str1)
print("Hello" in s)
print(str2 in s)
s.add(str2)
print(len(s))
s.remove(str1)
s.clear()
print(len(s) == 0)

print("===========")

map1 = {}
map1[str1] = "World"
print("Hello" in map1)
print(str2 in map1)
print(map1.get(str2))
print(map1.get("你好") is None)
if "Hello" in map1:
    del map1["Hello"]
print(len(map1))
map1.clear()
print(len(map1) == 0)

print("===========")

# 一般在笔试中，未必需要申请哈希表
map2 = {}
map2[56] = 7285
map2[34] = 3671263
map2[17] = 716311
map2[24] = 1263161
# 上面的map2行为，可以被如下数组的行为替代
arr = [0] * 100
arr[56] = 7285
arr[34] = 3671263
arr[17] = 716311
arr[24] = 1263161
# 哈希表的增、删、改、查，都可以被数组替代，前提是key的范围是固定的、可控的
print("在笔试场合中哈希表往往会被数组替代")

print("===========")


class Student:
    def __init__(self, a, b):
        self.age = a
        self.name = b


s1 = Student(17, "张三")
s2 = Student(17, "张三")
map3 = {}
map3[s1] = "这是张三"
print(s1 in map3)
print(s2 in map3)
map3[s2] = "这是另一个张三"
print(len(map3))
print(map3.get(s1))
print(map3.get(s2))