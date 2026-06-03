text = "人工智能 机器学习 深度学习 人工智能 算法 机器学习 数据 人工智能"
words = text.split()
freq = {}
for word in words:
    freq[word] = freq.get(word, 0) + 1
print("原始词频:", freq)
filtered = {word: count for word, count in freq.items() if count >= 2}
print("频率≥2的词:", filtered)
sorted_freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)
print("按频率降序:")
for word, count in sorted_freq:
    print(f"{word}: {count}")