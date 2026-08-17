# class026 哈希表、有序表和比较器的用法

> 本节是【必备】阶段的「工具课」，不讲底层原理（哈希函数/红黑树/平衡树后面专课展开），只展示三样高频工具在 C++ 里的用法和关键特性。
> 核心结论：**哈希表 O(1) 大常数、内置类型按值/自定义类型按地址去重；有序表 O(log n)、带 first/last/floor/ceiling/有序遍历；比较器统一「怎么比大小」，可复用到排序、有序表、堆**。

---

## 一、哈希表（HashSet / HashMap）

### 用法对照表

| Java | C++ |
|---|---|
| `HashSet<X>` | `unordered_set<X>` |
| `HashMap<K, V>` | `unordered_map<K, V>` |
| `add(x)` | `insert(x)` |
| `contains(x)` | `count(x) == 1` 或 `find(x) != end()` |
| `get(k)` | `find(k)->second`（**别用 `operator[]`**，见坑点） |
| `remove(k)` | `erase(k)` |
| `size()` / `isEmpty()` | `size()` / `empty()` |
| `clear()` | `clear()` |

### 核心概念

1. **复杂度 O(1) 但是「大常数」**：增删改查都与数据量无关，但常数比数组大得多，因为要算哈希、处理冲突。
2. **内置类型按值去重**：Java 里 `Integer/Long/Double/Float/Byte/Short/Character/Boolean/String` 这八种类型作 key 时按「值」去重——两个 `String` 哪怕内存地址不同、只要字面值都是 `"Hello"`，就是同一条记录。C++ 中 `string`、`int` 等内置类型天然按值，没有 Java `==` vs `equals` 那一层坑（`std::string` 的 `==` 直接比值）。
3. **自定义类型按内存地址去重**：Java 里自定义类型（如 `Student`）作 key 默认按「内存地址」去重——两个 age/name 都相同的对象仍是两条记录（链表的节点、二叉树节点同理）。
   - C++ 等价：用**指针**作 key（`unordered_map<Student*, string>`）。
   - 想改成按值：自定义 `hash` + `operator==`（等价 Java 重写 `hashCode`/`equals`），如 `unordered_map<Student, string, StudentHash>`。
4. **数组替代哈希表**：当 key 范围固定且可控（比如 key ∈ [0, 100)）时，直接用数组下标替代哈希表，常数更小、还可做成全局静态结构。

### 坑点

- `unordered_map` 的 `operator[]` 在 key **不存在时会插入默认值**；只想「查询」要用 `find`。
- 自定义类型作 `unordered_map` 的 key，必须提供 `hash` 和 `operator==`，否则编译不过。
- `find(k) == end()` 才是「不存在」的判断，`count(k)` 对 `unordered_map` 只会是 0 或 1。

### 代码（核心片段）

```cpp
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

```

---

## 二、有序表（TreeSet / TreeMap）

### 用法对照表

| Java | C++ |
|---|---|
| `TreeMap<K, V>` | `map<K, V>`（key 默认升序） |
| `TreeSet<K>` | `set<K>` |
| `firstKey()` | `*begin()` |
| `lastKey()` | `*rbegin()` |
| `floorKey(k)`（≤k 最近） | `*prev(upper_bound(k))` |
| `ceilingKey(k)`（≥k 最近） | `*lower_bound(k)` |
| `pollFirst()` / `pollLast()` | `erase(begin())` / `erase(prev(end()))` |
| 从小到大遍历 | `for (auto& x : s)` 或 `begin() → end()` |
| 从大到小遍历 | `rbegin() → rend()` |

### 核心概念

1. **复杂度 O(log n)**：有序表底层是红黑树，增删改查都要 O(log n) 调整；指标上不如哈希表的 O(1)，但哈希表是「大常数」，实际小数据量下两者差不多。
2. **有序相关操作是哈希表没有的**：`firstKey`、`lastKey`、`floorKey`、`ceilingKey`、有序遍历——因为哈希表不把 key 按序组织，有序表会。
3. **自动去重**：比较相等的 key 只留一份（`TreeSet` 里加 3,3,4,4 大小是 2）。想不去重要在比较器里加更多比较策略（见第三部分）。
4. **堆（PriorityQueue）不去重**：默认小根堆，加 3,3,4,4 大小是 4。C++ 的 `priority_queue` 默认是**大根堆**，要小根堆传 `greater<int>`。

### 坑点

- `map` 的 `operator[]` 同样会「查询时插入默认值」，只想查询用 `find`。
- `floorKey(k)` 的写法 `prev(upper_bound(k))` 在 `upper_bound(k) == begin()` 时要判空（没有 ≤k 的 key）。
- C++ `priority_queue` 默认大根堆，与 Java `PriorityQueue` 默认小根堆相反，别搞反。

### 代码（核心片段）

```cpp
// 哈希表、有序表和比较器的用法 —— 第2部分：有序表（TreeSet / TreeMap）
// 有序表底层是红黑树，key 有序组织；复杂度 O(log n)（哈希表 O(1) 但大常数）
// 有序表比哈希表多出的功能：firstKey / lastKey / floorKey / ceilingKey / 有序遍历
// key 相同会自动去重（比较相等的 key 只留一份）
//
// Java -> C++ 对照：
//   Java TreeMap<K, V>    ->  C++ map<K, V>（默认升序）
//   Java TreeSet<K>       ->  C++ set<K>
//   firstKey              ->  *begin()
//   lastKey               ->  *rbegin()
//   floorKey(k)  (<=k 最近) ->  *prev(upper_bound(k))
//   ceilingKey(k)(>=k 最近) ->  *lower_bound(k)

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // ============ 1. TreeMap（有序映射）============
    map<int, string> m;
    m[1] = "这是1";
    m[3] = "这是3";
    m[4] = "这是4";
    m[5] = "这是5";
    m[7] = "这是7";
    m[8] = "这是8";

    cout << (m.count(1) == 1) << endl;   // containsKey(1) -> 1
    cout << (m.count(10) == 1) << endl;  // containsKey(10) -> 0

    // get(4) —— 注意：C++ 的 operator[] 在 key 不存在时会插入默认值
    // 只想查询而不插入，用 find：
    auto it4 = m.find(4);
    if (it4 != m.end()) cout << it4->second << endl;  // 这是4

    // 更新 value（put 覆盖）
    m[4] = "张三是4";
    cout << m[4] << endl;                // 张三是4

    // firstKey / lastKey
    cout << m.begin()->first << endl;    // firstKey -> 1
    cout << m.rbegin()->first << endl;   // lastKey -> 8

    // 删除 key
    m.erase(4);

    // 删掉 4 之后：get(4) 应不存在
    cout << (m.find(4) == m.end()) << endl;  // 1（true）

    // floorKey(4)：<=4 且最近的 key（此时 4 已删，应为 3）
    auto it = m.upper_bound(4);          // 第一个 >4 的元素
    if (it == m.begin()) {
        cout << "floor 不存在" << endl;
    } else {
        cout << (--it)->first << endl;   // 3
    }

    // ceilingKey(4)：>=4 且最近的 key（应为 5）
    cout << m.lower_bound(4)->first << endl;  // 5

    // ============ 2. TreeSet（有序集合，自动去重）============
    set<int> st;
    st.insert(3);
    st.insert(3);
    st.insert(4);
    st.insert(4);
    cout << st.size() << endl;           // 2（自动去重）

    // 从小到大遍历
    for (int x : st) cout << x << ' ';   // 3 4
    cout << endl;
    // 从大到小遍历
    for (auto rit = st.rbegin(); rit != st.rend(); ++rit) cout << *rit << ' ';  // 4 3
    cout << endl;

    // ============ 3. 堆（PriorityQueue）============
    // Java PriorityQueue 默认小根堆，不去重
    // C++ priority_queue 默认大根堆，要小根堆需传 greater<int>
    priority_queue<int, vector<int>, greater<int>> pq;  // 小根堆
    pq.push(3);
    pq.push(3);
    pq.push(4);
    pq.push(4);
    cout << pq.size() << endl;           // 4（不去重）
    while (!pq.empty()) {
        cout << pq.top() << ' ';         // 3 3 4 4
        pq.pop();
    }
    cout << endl;

    return 0;
}

```

---

## 三、比较器（Comparator）

### 核心概念

1. **约定**：Java `compare(o1, o2)` 返回负数 → o1 优先级高，正数 → o2 优先级高，0 → 一样。C++ 的 `sort` lambda 返回 `true` 表示 `a` 排在 `b` 前（等价 a 优先级高）。
2. **三种写法的化简**：`谁年龄小谁优先` 从 if/else 版化简为一句 `return a.age < b.age;`。
3. **多指标排序**：先 company 升序、company 相同时 age 升序，用 `if (a.company != b.company) return a.company < b.company; return a.age < b.age;`。
4. **自定义类型放进 set 必须给比较器**，否则编译报错（有序表不知道怎么比大小）。
5. **去重 vs 不去重**：比较器只比较了 age 时，age 相同的两个对象会被 set 去重；想不去重就在比较器末尾加「内存地址」兜底（`return &a < &b;`），保证任意两个对象都能分出大小。
6. **字典序**：字符串比大小 = 字典序（短串补「最小字符」到等长再比，相当于一个「进制数」）。C++ 的 `string` 的 `<`、`==`、`>` 本身就是字典序，`s.compare(t)` 返回负数表示 `s` 字典序更小。

### 坑点

- `sort` 的比较器必须满足**严格弱序**：不能 `a < b` 和 `b < a` 同时为真，相等时必须返回 false。
- set 里「用地址兜底不去重」是粗略技巧：`&a` 是 set 内部存储元素的地址（稳定），可用于保证互不相同。
- 排序后的数组顺序会覆盖原顺序；需要保留原顺序先拷贝一份。

### 代码（核心片段）

```cpp
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

```

---

## 本节小结

1. **哈希表**（`unordered_set`/`unordered_map`）：O(1) 大常数，增删改查一把梭；内置类型按值、自定义类型默认按地址（指针作 key 模拟）；key 范围小时用数组替代更快。
2. **有序表**（`set`/`map`）：O(log n)，比哈希表多了 first/last/floor/ceiling/有序遍历，key 自动去重；堆（`priority_queue`）不去重且默认大根堆。
3. **比较器**：统一「怎么比大小」，复用到 `sort`、`set`、`priority_queue`；多指标排序、去重与否都能用比较策略精细控制；字符串默认字典序。
4. 三者覆盖了刷题里「需要快速查重」「需要按序访问」「需要自定义排序」的绝大多数场景，后续课程会大量用到。
