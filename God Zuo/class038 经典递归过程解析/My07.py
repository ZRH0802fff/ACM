def f(i,fr,t,o):
    if i==1:
        print(f"1从{fr}移动到{t}")
        return
    f(i-1,fr,o,t)
    print(f"{i}从{fr}移动到{t}")
    f(i-1,o,t,fr)
f(3,"左",'中','右')