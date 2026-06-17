def zsq(fn_nm):
    def fn_inner(*arges,**kwargs):
        print("额外功能")
        return fn_nm(*arges,**kwargs)
    return fn_inner

@zsq
def my_sum(*arges,**kwarges):
    return sum(arges)+sum(kwarges.values())

sum = my_sum(1, 2, 3, a=4, b=5, c=6)
print(sum)