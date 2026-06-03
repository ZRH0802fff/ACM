def divide_list(data, divisor):
    if divisor == 0:
        raise ZeroDivisionError

    res = []
    for x in data:
        if type(x) != int and type(x) != float:
            raise TypeError
        res.append(x / divisor)
    return res


a = [10, 20, 30]
b = [10, "a", 30]

try:
    ans1 = divide_list(a, 2)
    print(ans1)

    ans2 = divide_list(a, 0)
    print(ans2)
except ZeroDivisionError:
    print("提示：除数不能为0")
except TypeError:
    print("提示：列表中包含了非数字的元素")

try:
    ans3 = divide_list(b, 2)
    print(ans3)
except ZeroDivisionError:
    print("提示：除数不能为0")
except TypeError:
    print("提示：列表中包含了非数字的元素")