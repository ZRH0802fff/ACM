a = "实体识别结果： \n人名： 张三\n地点： 北京\n组织： 清华大学\n时间： 2023年"

b = a.split("\n")
c = {}

for d in b[1:]:
    e = d.split("：")
    c[e[0]] = e[1].strip()

print(c)