def f(set1, set2):
    if not set1 and not set2:
        return 1.0  
    return  len(set1 & set2)/ len(set1 | set2) if len(set1 | set2) != 0 else 0.0
item1_tags = {"动作", "冒险", "科幻"}
item2_tags = {"动作", "科幻", "惊悚"}
item3_tags = {"爱情", "剧情", "文艺"}

sim12 = f(item1_tags, item2_tags)
sim13 = f(item1_tags, item3_tags)

print(f"item1与item2的Jaccard相似度: {sim12:.4f}")  
print(f"item1与item3的Jaccard相似度: {sim13:.4f}")  