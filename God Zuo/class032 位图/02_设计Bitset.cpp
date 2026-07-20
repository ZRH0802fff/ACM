// 位图的实现
// Bitset是一种能以紧凑形式存储位的数据结构
// Bitset(int n) : 初始化n个位，所有位都是0
// void fix(int i) : 将下标i的位上的值更新为1
// void unfix(int i) : 将下标i的位上的值更新为0
// void flip() : 翻转所有位的值
// bool all() : 是否所有位都是1
// bool one() : 是否至少有一位是1
// int count() : 返回所有位中1的数量
// String toString() : 返回所有位的状态
// 测试链接 : https://leetcode-cn.com/problems/design-bitset/

#include <bits/stdc++.h>
using namespace std;

class Bitset {
private:
    vector<int> set;
    int size;
    int zeros;
    int ones;
    bool rev;

public:
    Bitset(int n) {
        set.resize((n + 31) / 32);
        size = n;
        zeros = n;
        ones = 0;
        rev = false;
    }

    // 把i这个数字加入到位图
    void fix(int i) {
        int index = i / 32;
        int bit = i % 32;
        if (!rev) {
            // 位图所有位的状态，维持原始含义
            // 0 : 不存在
            // 1 : 存在
            if ((set[index] & (1 << bit)) == 0) {
                zeros--;
                ones++;
                set[index] |= (1 << bit);
            }
        } else {
            // 位图所有位的状态，翻转了
            // 0 : 存在
            // 1 : 不存在
            if ((set[index] & (1 << bit)) != 0) {
                zeros--;
                ones++;
                set[index] ^= (1 << bit);
            }
        }
    }

    // 把i这个数字从位图中移除
    void unfix(int i) {
        int index = i / 32;
        int bit = i % 32;
        if (!rev) {
            if ((set[index] & (1 << bit)) != 0) {
                ones--;
                zeros++;
                set[index] ^= (1 << bit);
            }
        } else {
            if ((set[index] & (1 << bit)) == 0) {
                ones--;
                zeros++;
                set[index] |= (1 << bit);
            }
        }
    }

    void flip() {
        rev = !rev;
        int tmp = zeros;
        zeros = ones;
        ones = tmp;
    }

    bool all() {
        return ones == size;
    }

    bool one() {
        return ones > 0;
    }

    int count() {
        return ones;
    }

    string toString() {
        string builder;
        for (int i = 0, k = 0, number, status; i < size; k++) {
            number = set[k];
            for (int j = 0; j < 32 && i < size; j++, i++) {
                status = (number >> j) & 1;
                status ^= rev ? 1 : 0;
                builder += (char)('0' + status);
            }
        }
        return builder;
    }
};
