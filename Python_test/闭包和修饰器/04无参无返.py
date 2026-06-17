def zsq(fn_nm):
    def fn_inner():
        print("额外功能")
        fn_nm()
    return fn_inner

@zsq
def my_sum():
    a=10
    b=20
    sum = a + b
    print(f'sum求和结果: {sum}')

my_sum()