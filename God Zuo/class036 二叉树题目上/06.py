# 二叉树按层序列化和反序列化
# 对应 LeetCode 297. Serialize and Deserialize Binary Treequ

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Codec:
    def __init__(self):
        # 最大节点数限制（可以根据需要调整）
        self.MAXN = 10001
        self.queue = [None] * self.MAXN

    def serialize(self, root: TreeNode) -> str:
        """Encodes a tree to a single string."""
        if not root:
            return ""

        builder = []
        l, r = 0, 0
        
        builder.append(str(root.val) + ",")
        self.queue[r] = root
        r += 1

        while l < r:
            cur = self.queue[l]
            l += 1

            # 左孩子
            if cur.left:
                builder.append(str(cur.left.val) + ",")
                self.queue[r] = cur.left
                r += 1
            else:
                builder.append("#,")

            # 右孩子
            if cur.right:
                builder.append(str(cur.right.val) + ",")
                self.queue[r] = cur.right
                r += 1
            else:
                builder.append("#,")

        return "".join(builder)

    def deserialize(self, data: str) -> TreeNode:
        """Decodes your encoded data to tree."""
        if not data:
            return None

        nodes = data.split(",")
        # 去掉最后一个空字符串（因为最后会多一个 ,）
        if nodes[-1] == "":
            nodes.pop()

        idx = 0
        root = self._generate(nodes[idx])
        idx += 1

        if not root:
            return None

        l, r = 0, 0
        self.queue[r] = root
        r += 1

        while l < r:
            cur = self.queue[l]
            l += 1

            # 左孩子
            cur.left = self._generate(nodes[idx])
            idx += 1
            if cur.left:
                self.queue[r] = cur.left
                r += 1

            # 右孩子
            cur.right = self._generate(nodes[idx])
            idx += 1
            if cur.right:
                self.queue[r] = cur.right
                r += 1

        return root

    def _generate(self, val: str) -> TreeNode | None:
        return None if val == "#" else TreeNode(int(val))


# 测试用例（可选）
if __name__ == "__main__":
    # 构造一棵树
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.right.left = TreeNode(4)
    root.right.right = TreeNode(5)

    codec = Codec()
    serialized = codec.serialize(root)
    print("序列化结果:", serialized)

    deserialized = codec.deserialize(serialized)
    print("反序列化后根节点值:", deserialized.val if deserialized else None)