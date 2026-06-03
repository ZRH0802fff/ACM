# 二叉树先序序列化和反序列化
# 测试链接 : https://leetcode.cn/problems/serialize-and-deserialize-binary-tree/

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Codec:

    def serialize(self, root: TreeNode) -> str:
        """Encodes a tree to a single string.
        先序遍历：根 -> 左 -> 右，空节点用 "#" 表示
        """
        builder = []
        self._serialize(root, builder)
        return ','.join(builder)

    def _serialize(self, root: TreeNode, builder: list):
        if root is None:
            builder.append("#")
        else:
            builder.append(str(root.val))
            self._serialize(root.left, builder)
            self._serialize(root.right, builder)

    def deserialize(self, data: str) -> TreeNode:
        """Decodes your encoded data to tree.
        使用先序遍历的顺序重建树
        """
        if not data:
            return None
        
        vals = data.split(',')
        self.index = 0  # 用于记录当前消费到数组的哪个位置
        return self._deserialize(vals)

    def _deserialize(self, vals: list) -> TreeNode:
        val = vals[self.index]
        self.index += 1
        
        if val == "#":
            return None
        
        # 创建当前节点
        node = TreeNode(int(val))
        
        # 先序：先重建左子树，再重建右子树
        node.left = self._deserialize(vals)
        node.right = self._deserialize(vals)
        
        return node


# 测试用例（可选，非提交部分）
if __name__ == "__main__":
    # 示例树：
    #       1
    #      / \
    #     2   3
    #        / \
    #       4   5
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.right.left = TreeNode(4)
    root.right.right = TreeNode(5)

    codec = Codec()
    serialized = codec.serialize(root)
    print("序列化结果:", serialized)          # 应输出: 1,2,#,#,3,4,#,#,5,#,#

    deserialized = codec.deserialize(serialized)
    # 可以再序列化验证是否一致
    print("反序列化后再序列化:", codec.serialize(deserialized))