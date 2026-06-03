class Solution:
    def countOfAtoms(self, formula: str) -> str:
        self.where = 0
        count_map = self.f(list(formula), 0)
        
        # 手动收集所有原子并排序
        atoms = []
        for atom in count_map:
            atoms.append(atom)
        atoms.sort()  # 内置 sort，无需额外库
        
        ans = []
        for atom in atoms:
            ans.append(atom)
            cnt = count_map[atom]
            if cnt > 1:
                ans.append(str(cnt))
        
        return ''.join(ans)

    def f(self, s: list, i: int) -> dict:
        """
        从 s[i] 开始解析，直到遇到 ')' 或结束
        返回：当前段的原子计数 {原子: 数量}
        """
        ans = {}                    # 普通 dict
        name = []                   # 收集原子名
        pre = None                  # 括号内的子 map
        cnt = 0                     # 当前倍数

        while i < len(s) and s[i] != ')':
            ch = s[i]

            # 大写字母开头 或 '('
            if ('A' <= ch <= 'Z') or ch == '(':
                # 把上一个原子/括号内容填入 ans
                self._fill(ans, name, pre, cnt)
                name = []
                pre = None
                cnt = 0

                if 'A' <= ch <= 'Z':
                    name.append(ch)
                    i += 1
                else:
                    # 遇到 '('，递归
                    pre = self.f(s, i + 1)
                    i = self.where + 1

            # 小写字母，继续原子名
            elif 'a' <= ch <= 'z':
                name.append(ch)
                i += 1

            # 数字，累积倍数
            else:
                cnt = cnt * 10 + int(ch)
                i += 1

        # 处理最后一段
        self._fill(ans, name, pre, cnt)
        self.where = i
        return ans

    def _fill(self, ans: dict, name: list, pre: dict, cnt: int):
        """
        将当前原子或括号内容乘 cnt 后加入 ans
        """
        if name or pre:
            cnt = 1 if cnt == 0 else cnt

            if name:
                atom = ''.join(name)
                # 普通 dict 的 getOrDefault 写法
                ans[atom] = ans.get(atom, 0) + cnt
            else:
                for atom in pre:
                    ans[atom] = ans.get(atom, 0) + pre[atom] * cnt