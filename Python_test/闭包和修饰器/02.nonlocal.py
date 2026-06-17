# nonlocal: 在内部函数中修改外部函数的值

def fn_outer():
    a=100
    def fn_inner():
        nonlocal a
        a+=1
        print(f'a: {a}')
    return fn_inner

fn_inner=fn_outer()
fn_inner()
fn_inner()
fn_inner()
