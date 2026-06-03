student = {
    "name": "张三",
    "age": 20,
    "major": "计算机科学",
    "grades": [85, 90, 78]  # grades 是一个列表
}
student["graduated"] = False
student["age"] = student["age"] + 1
scholarship = student.get("scholarship", "无")
print("scholarship:", scholarship)
print("字典所有键值对:")
for key, value in student.items():
    print(f"{key}: {value}")

del student["grades"]
print("\n删除 grades 后的字典:")
print(student)