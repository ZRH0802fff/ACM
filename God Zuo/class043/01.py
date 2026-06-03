import sys

# 为了方便阅读，这里直接使用列表，不用固定大小数组
# 但逻辑和Java版本完全一致

def f(i, r, kill, blood, n):
    """
    参数说明：
    i : 当前要决定使用第几个技能的位置（从0开始）
    r : 怪物当前剩余血量
    kill : 伤害数组
    blood : 触发双倍的血量阈值数组
    n : 技能总数
    返回：从当前位置开始，最少需要几个技能能打死怪物
          如果不可能，返回一个极大值
    """
    if r <= 0:
        return i  # 已经打死了，返回用了几个技能

    if i == n:
        return float('inf')  # 用完了所有技能还没死，无解

    ans = float('inf')

    # 枚举当前第i位置放哪个技能（i到n-1都尝试交换到i位置）
    for j in range(i, n):
        # 交换 i 和 j
        kill[i], kill[j] = kill[j], kill[i]
        blood[i], blood[j] = blood[j], blood[i]

        # 计算这次技能造成的伤害
        damage = kill[i] * 2 if r <= blood[i] else kill[i]

        # 递归
        ans = min(ans, f(i + 1, r - damage, kill, blood, n))

        # 恢复现场（回溯）
        kill[i], kill[j] = kill[j], kill[i]
        blood[i], blood[j] = blood[j], blood[i]

    return ans


def main():
    input = sys.stdin.read
    data = input().split()

    index = 0
    t = int(data[index])
    index += 1

    for _ in range(t):
        n = int(data[index])
        index += 1
        m = int(data[index])
        index += 1

        kill = []
        blood = []

        for j in range(n):
            k = int(data[index])
            index += 1
            b = int(data[index])
            index += 1
            kill.append(k)
            blood.append(b)

        # 开始递归
        result = f(0, m, kill, blood, n)

        if result == float('inf'):
            print(-1)
        else:
            print(result)


if __name__ == "__main__":
    main()