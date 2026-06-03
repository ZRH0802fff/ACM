class Solution:
    def longestSubstring(self, s: str, k: int) -> int:
        ans = 0
        n = len(s)
        
        # 每次要求子串必须含有 require 种字符，且每种字符出现次数都 >= k
        # 因为题目是小写英文字母，最多 26 种，我们枚举限制条件
        for require in range(1, 27):
            # 用 128 长度的数组替代字典，避免哈希开销，直接用 ord() 映射
            cnts = [0] * 128 
            l = 0
            
            collect = 0  # 窗口中一共收集到的字符种类数
            satisfy = 0  # 窗口中达标的字符种类数 (即出现次数 >= k 的种类数)
            
            for r, char in enumerate(s):
                idx = ord(char)
                cnts[idx] += 1
                
                # 新增了一种字符
                if cnts[idx] == 1:
                    collect += 1
                # 某种字符的频率刚刚达到 k，达标种类数 +1
                if cnts[idx] == k:
                    satisfy += 1 
                    
                # 如果当前窗口内的字符种类数超过了 require 限制！
                # 破坏了单调性，必须让 l 位置的字符从窗口中吐出来
                while collect > require:
                    left_idx = ord(s[l])
                    
                    # 如果吐出后该字符在窗口内绝迹了，总种类数 -1
                    if cnts[left_idx] == 1:
                        collect -= 1
                    # 如果吐出后该字符频率不足 k 了，达标种类数 -1
                    if cnts[left_idx] == k:
                        satisfy -= 1
                        
                    cnts[left_idx] -= 1
                    l += 1
                    
                # 当收集的种类数完全等于限定的 require 种类数
                # 并且这些收集到的所有种类，频次全部达标 (>=k)
                if satisfy == require:
                    ans = max(ans, r - l + 1)
                    
        return ans