# =============================================
# 【算法竞赛超干净模板】HashSet + HashMap
# 直接复制到你的代码最前面，每次竞赛都用这个风格！
# =============================================

print("=== 字符串 HashSet / HashMap 演示 ===")

# 1. 字符串（值相同但对象不同）
s1 = "Hello"
s2 = "Hello"          # Python 字符串常量会自动复用，但为了演示我们强制不同对象也没必要
# s2 = "".join("Hello")  # 如果想严格模拟 new String() 可以这样

print(s1 is s2)       # False（身份不同）或 True（Python 优化）
print(s1 == s2)       # True（值相同）

# ------------------- HashSet -------------------
st = set()
st.add(s1)
print("Hello" in st)   # True
print(s2 in st)        # True（自动按值判断）
st.add(s2)             # 重复添加无效
print("HashSet 大小:", len(st))   # 1
st.remove(s1)
st.clear()
print("清空后是否为空:", len(st) == 0)

print("=" * 40)

# ------------------- HashMap -------------------
mp = {}
mp[s1] = "World"
print("Hello" in mp)               # containsKey
print(s2 in mp)                    # True
print(mp.get(s2))                  # World
print(mp.get("你好") is None)      # True（不存在返回 None）

mp.pop("Hello", None)              # remove（安全写法）
print("大小:", len(mp))
mp.clear()
print("清空后大小:", len(mp))

print("=" * 40)

# ------------------- 小范围 key 用数组更快（竞赛最优技巧）-------------------
print("小范围 key 用数组替代 HashMap（更快！）")
arr = [0] * 100                    # key 在 0~99 就够
arr[56] = 7285
arr[34] = 3671263
arr[17] = 716311
arr[24] = 1263161
print("arr[17] =", arr[17])        # 直接 O(1) 访问

print("=" * 40)

# ------------------- 自定义类放入 Hash（竞赛最容易错的地方）-------------------
class Student:
    def __init__(self, age, name):
        self.age = age
        self.name = name

    # 竞赛中一定要同时重写 __hash__ 和 __eq__，否则默认按内存地址！
    def __hash__(self):
        return hash((self.age, self.name))   # 关键！按值哈希

    def __eq__(self, other):
        if not isinstance(other, Student):
            return False
        return self.age == other.age and self.name == other.name


s1 = Student(17, "张三")
s2 = Student(17, "张三")

mp3 = {}
mp3[s1] = "这是张三"
print(s1 in mp3)          # True
print(s2 in mp3)          # True（重写后生效！）
mp3[s2] = "这是另一个张三"
print("大小:", len(mp3))   # 1（因为 s1 和 s2 相等）
print(mp3[s1])            # 这是另一个张三（被覆盖）