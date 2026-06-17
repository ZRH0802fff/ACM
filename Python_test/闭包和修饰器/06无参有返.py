#无参有返

def zsq(fn_nm):
    def fn_inner():
        print("额外功能")
        return fn_nm()    #原函数有返，装饰器函数内部有返
    return fn_inner

@zsq
def my_sum():
    a=10
    b=20
    return a+b

print(my_sum())