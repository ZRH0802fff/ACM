"""
概念：
    内部函数使用了外部函数的变量
格式：
    def 外部函数名（形参列表）：
        外部函数变量
        def 内部函数名（形参列表）：
            使用外部函数变量
        return 内部函数名
前提条件：
    1.有嵌套
    2.有引用
    3.有返回
"""

def fn_outer(num1):
    def fn_inner(num2):
        sum=num1+num2
        print(f'求和结果: {sum}')
    return fn_inner

fn_inner=fn_outer(10)
fn_inner(1)
fn_inner(1)
fn_inner(1)
fn_inner(1)
fn_inner(1)
fn_inner(1)