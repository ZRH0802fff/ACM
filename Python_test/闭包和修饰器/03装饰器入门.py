"""
作用：
    本质是闭包函数
    在不改变原有函数的基础上,对其进行功能增强
前提条件：
    1.有嵌套
    2.有引用
    3.有返回
    4.有额外功能
写法：
    传统写法：
        装饰后的函数名 = 装饰器名（被装饰的原函数名）
        装饰后的函数名（）
    语法糖：
        在要被装饰的原函数上，直接写@装饰器名，之后直接调用原函数即可。
"""

#在发表评论区需要先登录

def check_login(fn_name):                  #fn_name:被装饰的函数名
    def fn_inner():                        #有嵌套
        print('校验登陆... 登陆成功!')      #有额外功能
        fn_name()                          #有引用
    return fn_inner                        #有返回

def comment():
    print("发表评论")
comment=check_login(comment)
comment()

@check_login
def payment():
    print('充值中...')
payment()