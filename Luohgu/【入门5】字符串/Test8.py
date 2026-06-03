s = input().strip()
text = input()

low_s = s.lower()
low_text = text.lower()

m = len(low_s)
n = len(low_text)

if m == 0 or low_s not in low_text:
    print(-1)
else:
    count = 0
    first = -1
    pos = 0
    while True:
        pos = low_text.find(low_s, pos)
        if pos == -1:
            break
        # 检查是否整词：前面是空格/开头，后面是空格/结尾
        before = (pos == 0 or low_text[pos - 1] == ' ')
        after = (pos + m == n or low_text[pos + m] == ' ')
        if before and after:
            count += 1
            if first == -1:
                first = pos
        pos += 1  # 防止极端重叠情况，继续往后找

    if count == 0:
        print(-1)
    else:
        print(count, first)