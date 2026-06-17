#有参有返

def zsq(fn_nm):
    def fn_inner(a,b):
        print("额外功能")
        return fn_nm(a,b)
    return fn_inner

@zsq
def my_sum(a,b):
    return a+b

print(my_sum(10,20))