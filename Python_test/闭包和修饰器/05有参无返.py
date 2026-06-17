#有参无返
def zsq(fn_nm):
    def fn_inner(x,y):
        print("额外功能")
        fn_nm(x,y)     #原函数有参，装饰器内部函数有参
    return fn_inner

@zsq
def my_sum(x,y):
    print(f"sum:{x+y}")

my_sum(1,2)