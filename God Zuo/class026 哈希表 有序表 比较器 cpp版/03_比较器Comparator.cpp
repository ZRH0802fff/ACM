// 哈希表、有序表和比较器的用法 —— 第3部分：比较器（Comparator）
// 比较器 = 自己定制"怎么比大小"，用于排序、有序表、堆等需要"序"的结构
//
// Java 约定：compare(o1, o2) 返回负数 => o1 优先级更高；正数 => o2 更高；0 => 一样
// C++ 对照：
//   sort 第3个参数 lambda：返回 true 表示 a 排在 b 前面（等价于 a 优先级高）
//   set/map 自定义类型：传比较器（仿函数）或重载 operator<
//   priority_queue：第3个模板参数传仿函数
//
// 字符串比大小 = 字典序：短串补"最小字符"到等长再比，C++ 中 string 的 < 本身就是字典序

#include <bits/stdc++.h>
using namespace std;

struct Employee {
    int company;
    int age;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    Employee arr[6] = {
        {2, 27}, {1, 60}, {4, 19}, {3, 23}, {1, 35}, {3, 55}
    };
    int n = 6;

    auto print = [&]() {
        for (int i = 0; i < n; i++)
            cout << arr[i].company << "," << arr[i].age << "  ";
        cout << endl;
    };

    cout << "原顺序：" << endl;
    print();

    // 1. 按年龄升序（谁年龄小谁在前）
    sort(arr, arr + n, [](const Employee& a, const Employee& b) {
        return a.age < b.age;
    });
    cout << "按年龄升序：" << endl;
    print();

    // 2. 按年龄降序（谁年龄大谁在前）
    sort(arr, arr + n, [](const Employee& a, const Employee& b) {
        return a.age > b.age;
    });
    cout << "按年龄降序：" << endl;
    print();

    // 3. 先按公司编号升序，公司相同时按年龄升序（多指标排序）
    sort(arr, arr + n, [](const Employee& a, const Employee& b) {
        if (a.company != b.company) return a.company < b.company;
        return a.age < b.age;
    });
    cout << "先公司升序、再年龄升序：" << endl;
    print();

    // ============ 有序表（set）中使用比较器 ============
    // 自定义类型放进 set 必须告诉它怎么比大小，否则编译报错
    struct CmpByAge {
        bool operator()(const Employee& a, const Employee& b) const {
            return a.age < b.age;   // 谁年龄小谁在前
        }
    };
    set<Employee, CmpByAge> st;
    // 若两个对象比较相等（年龄相同），set 会去重

    // 不去重的比较器：最后用"内存地址"兜底，保证任意两个对象都能分出大小
    struct CmpNoDedup {
        bool operator()(const Employee& a, const Employee& b) const {
            if (a.company != b.company) return a.company < b.company;
            if (a.age != b.age) return a.age < b.age;
            return &a < &b;   // 用地址兜底 -> 任何两个对象都不相等 -> 不去重
        }
    };

    // ============ 字典序 ============
    // 两个字符串比大小 = 字典序：短串补"最小字符"到等长再比
    // C++ 中 string 的 <、==、> 本身就是字典序
    string s1 = "abcde";
    string s2 = "ks";
    cout << (s1 < s2) << endl;           // 1（abcde 字典序更小）
    cout << s1.compare(s2) << endl;      // 负数（s1 字典序更小）
    cout << s2.compare(s1) << endl;      // 正数（s2 字典序更大）

    return 0;
}
