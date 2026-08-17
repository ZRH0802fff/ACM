// 哈希表、有序表和比较器的用法 —— 第1部分：哈希表
// 本节目的是展示哈希表（HashSet / HashMap）的用法与关键特性，
// 不涉及底层原理（哈希函数、一致性哈希、布隆过滤器等后面专课讲）。
//
// Java -> C++ 对照：
//   Java HashSet<X>      ->  C++ unordered_set<X>
//   Java HashMap<K, V>   ->  C++ unordered_map<K, V>
//   增删改查都是 O(1)，但常数较大（哈希表是"大常数"时间，与数据量无关）
//
// 两个核心概念：
//   1. Java 中 Integer/Long/Double/Float/Byte/Short/Character/Boolean/String
//      这八种类型作 key 时"按值"去重；自定义类型作 key 时默认"按内存地址"去重。
//   2. 当 key 范围固定且可控时，可以用数组代替哈希表（更快、可静态）。

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ============ 1. 字符串相等：按值比较 ============
    // Java 里 new String("Hello") 两次得到两个不同内存地址，== 比地址、equals 比值。
    // C++ 中 std::string 的 == 直接按值比较，没有"比地址"这一层坑。
    string str1 = "Hello";
    string str2 = "Hello";
    cout << (str1 == str2) << endl;   // 1（true），按值相等

    // ============ 2. HashSet（哈希集合）============
    unordered_set<string> s;
    s.insert(str1);                            // add
    cout << (s.count("Hello") == 1) << endl;   // contains，按值判断 -> 1
    cout << (s.count(str2) == 1) << endl;      // str2 字面值也是 Hello，仍命中 -> 1
    s.insert(str2);                            // 重复插入，不会多一条
    cout << s.size() << endl;                  // size -> 1（按值去重）
    s.erase(str1);                             // remove
    s.clear();                                 // clear
    cout << s.empty() << endl;                 // isEmpty -> 1（true）

    // ============ 3. HashMap（哈希映射）============
    unordered_map<string, string> map1;
    map1[str1] = "World";                      // put
    cout << (map1.count("Hello") == 1) << endl;   // containsKey -> 1
    cout << (map1.count(str2) == 1) << endl;      // 按值 -> 1
    cout << map1[str2] << endl;                // get -> World
    // 查询不存在的 key：用 find 判断，别用 operator[]（它会插入默认值）
    cout << (map1.find("你好") == map1.end()) << endl;  // 不存在 -> 1
    map1.erase("Hello");                       // remove
    cout << map1.size() << endl;               // size
    map1.clear();                              // clear
    cout << map1.empty() << endl;              // isEmpty -> 1

    // ============ 4. 小范围 key 用数组替代哈希表 ============
    // key 范围固定可控时，数组比哈希表更快（常数更小、可做成静态结构）
    unordered_map<int, int> map2;
    map2[56] = 7285;
    map2[34] = 3671263;
    map2[17] = 716311;
    map2[24] = 1263161;
    // 上面的行为可以用一个长度 100 的数组替代：
    int arr[100];
    fill(arr, arr + 100, 0);
    arr[56] = 7285;
    arr[34] = 3671263;
    arr[17] = 716311;
    arr[24] = 1263161;
    // 增删改查都可用数组替代，前提是 key 范围小

    // ============ 5. 自定义类型作 key ============
    // Java 中自定义类型作 key 默认"按内存地址"去重
    // （两个 age/name 都相同的对象，仍是两条记录）。
    struct Student {
        int age;
        string name;
        bool operator==(const Student& o) const {
            return age == o.age && name == o.name;
        }
    };
    struct StudentHash {
        size_t operator()(const Student& s) const {
            return hash<int>()(s.age) ^ (hash<string>()(s.name) << 1);
        }
    };

    Student s1{17, "张三"};
    Student s2{17, "张三"};

    // (a) 用指针作 key -> 等价于 Java"按内存地址"去重
    unordered_map<Student*, string> map3;
    map3[&s1] = "这是张三";
    cout << (map3.count(&s1) == 1) << endl;   // 有 s1 -> 1
    cout << (map3.count(&s2) == 1) << endl;   // 没有 s2（不同地址）-> 0
    map3[&s2] = "这是另一个张三";
    cout << map3.size() << endl;              // 2（按地址，两条记录）
    cout << map3[&s1] << endl;                // 这是张三
    cout << map3[&s2] << endl;                // 这是另一个张三

    // (b) 自定义 hash + == -> 等价于 Java"按值"去重（重写 hashCode/equals）
    unordered_map<Student, string, StudentHash> map4;
    map4[s1] = "这是张三";
    cout << (map4.count(s1) == 1) << endl;    // 1
    cout << (map4.count(s2) == 1) << endl;    // s2 与 s1 值相同，命中 -> 1
    map4[s2] = "这是另一个张三";
    cout << map4.size() << endl;              // 1（按值去重）
    cout << map4[s1] << endl;                 // 这是另一个张三（被覆盖）

    return 0;
}
