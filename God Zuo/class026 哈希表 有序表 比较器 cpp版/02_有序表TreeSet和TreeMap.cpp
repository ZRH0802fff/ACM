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
