import bisect

class OrderedSet:
    def __init__(self):
        self.data = []                     # 始终保持升序 + 去重

    def add(self, val):
        if not self.contains(val):         # 去重（和 TreeSet 一样）
            bisect.insort(self.data, val)

    def remove(self, val):
        idx = bisect.bisect_left(self.data, val)
        if idx < len(self.data) and self.data[idx] == val:
            self.data.pop(idx)

    def contains(self, val):
        idx = bisect.bisect_left(self.data, val)
        return idx < len(self.data) and self.data[idx] == val

    def size(self):
        return len(self.data)

    def poll_first(self):                  # 弹出最小值（类似 pollFirst）
        return self.data.pop(0) if self.data else None

    def first(self):
        return self.data[0] if self.data else None

    def last(self):
        return self.data[-1] if self.data else None

    def floor(self, val):                  # <= val 的最大值
        idx = bisect.bisect_right(self.data, val)
        return self.data[idx-1] if idx > 0 else None

    def ceiling(self, val):                # >= val 的最小值
        idx = bisect.bisect_left(self.data, val)
        return self.data[idx] if idx < len(self.data) else None

    def __iter__(self):                    # 支持 for x in s:
        return iter(self.data)


# ====================== 有序映射（TreeMap） ======================
class OrderedMap:
    def __init__(self):
        self.data = {}                     # key -> value
        self.keys = []                     # 维护有序 key 列表

    def put(self, key, value):
        if key not in self.data:
            bisect.insort(self.keys, key)
        self.data[key] = value

    def get(self, key):
        return self.data.get(key)

    def remove(self, key):
        if key in self.data:
            del self.data[key]
            idx = bisect.bisect_left(self.keys, key)
            self.keys.pop(idx)

    def floor_key(self, key):
        idx = bisect.bisect_right(self.keys, key)
        return self.keys[idx-1] if idx > 0 else None

    def ceiling_key(self, key):
        idx = bisect.bisect_left(self.keys, key)
        return self.keys[idx] if idx < len(self.keys) else None