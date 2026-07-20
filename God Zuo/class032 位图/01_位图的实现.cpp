// 位图的实现
// Bitset(int size)
// void add(int num)
// void remove(int num)
// void reverse(int num)
// bool contains(int num)

#include <bits/stdc++.h>
using namespace std;

// 位图的实现
// 使用时num不要超过初始化的大小
class Bitset {
public:
    vector<int> set;

    // n个数字 : 0~n-1
    Bitset(int n) {
        // a/b如果结果想向上取整，可以写成 : (a+b-1)/b
        // 前提是a和b都是非负数
        set.resize((n + 31) / 32);
    }

    void add(int num) {
        set[num / 32] |= 1 << (num % 32);
    }

    void remove(int num) {
        set[num / 32] &= ~(1 << (num % 32));
    }

    void reverse(int num) {
        set[num / 32] ^= 1 << (num % 32);
    }

    bool contains(int num) {
        return ((set[num / 32] >> (num % 32)) & 1) == 1;
    }
};

// 对数器测试
int main() {
    int n = 1000;
    int testTimes = 10000;
    cout << "测试开始" << endl;
    // 实现的位图结构
    Bitset bitSet(n);
    // 直接用unordered_set做对比测试
    unordered_set<int> hashSet;
    cout << "调用阶段开始" << endl;
    srand(time(0));
    for (int i = 0; i < testTimes; i++) {
        double decide = (double)rand() / RAND_MAX;
        // number -> 0 ~ n-1，等概率得到
        int number = rand() % n;
        if (decide < 0.333) {
            bitSet.add(number);
            hashSet.insert(number);
        } else if (decide < 0.666) {
            bitSet.remove(number);
            hashSet.erase(number);
        } else {
            bitSet.reverse(number);
            if (hashSet.count(number)) {
                hashSet.erase(number);
            } else {
                hashSet.insert(number);
            }
        }
    }
    cout << "调用阶段结束" << endl;
    cout << "验证阶段开始" << endl;
    for (int i = 0; i < n; i++) {
        if (bitSet.contains(i) != (hashSet.count(i) > 0)) {
            cout << "出错了!" << endl;
        }
    }
    cout << "验证阶段结束" << endl;
    cout << "测试结束" << endl;
    return 0;
}
