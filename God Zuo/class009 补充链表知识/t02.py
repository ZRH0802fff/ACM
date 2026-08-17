import random

num = random.randint(1, 100)
count = 0

while True:
    guess = int(input("请输入你猜的数字（1~100）："))
    count += 1
    if guess > num:
        print("你猜的数字比答案大")
    elif guess < num:
        print("你猜的数字比答案小")
    else:
        print(f"正确！你一共猜了{count}次。")
        break