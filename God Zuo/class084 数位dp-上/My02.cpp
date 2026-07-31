// 最大为N的数字组合
// 给定一个按 非递减顺序 排列的数字数组 digits
// 已知digits一定不包含'0'，可能包含'1' ~ '9'，且无重复字符
// 你可以用任意次数 digits[i] 来写的数字
// 例如，如果 digits = ['1','3','5']
// 我们可以写数字，如 '13', '551', 和 '1351315'
// 返回 可以生成的小于或等于给定整数 n 的正整数的个数
// 测试链接 : https://leetcode.cn/problems/numbers-at-most-n-given-digit-set/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int m;
    int dig[11];

    // len     ->  还有len位没有确定
    // offset  ->  辅助变量 完全由len确定，方便提取num中第len位
    // free    ->  之前位和num一样，需要限制当前位不能选大于num中当前位的数字时为0
    // fix     ->  之前一直没有使用过数字为0
    int f(int num,int offset,int len,int free,int fix){
        if(len==0) return (fix==1)?1:0;
        int ans = 0;
        int cur = (num / offset) % 10;
        if(fix==0){
            ans += f(num, offset / 10, len - 1, 1, 0);
        }
        if(free==0){
            for (int idx = 0; idx < m; ++idx){
                int i = dig[idx];
                if(i<cur){
                    ans += f(num, offset / 10, len - 1, 1, 1);
                }else if(i==cur){
                    ans += f(num, offset / 10, len - 1, 0, 1);
                }else{
                    break;
                }
            }
        }else{
            ans += m * f(num, offset / 10, len - 1, 1, 1);
        }
        return ans;
    }

    int atMostNGivenDigitSet(vector<string>& strs, int num) {
        int tmp = num / 10;
        int len = 1;
        int offset = 1;
        while(tmp>0){
            tmp /= 10;
            ++len;
            offset *= 10;
        }
        m = strs.size();
        for (int i = 0; i < m; ++i){
            dig[i] = stoi(strs[i]);
        }
        return f(num, offset, len, 0, 0);
    }
};


class Solution {
public:
    int m;
    int dig[12];
    int cnt[12];

    int f(int num, int offset,int len){
        if(len==0) return 1;
        int cur = (num / offset) % 10;
        int ans = 0;
        for (int idx = 0; idx < m; ++idx){
            int i = dig[idx];
            if(i<cur){
                ans += cnt[len - 1];
            }else if(i==cur){
                ans += f(num, offset / 10, len - 1);
            }else{
                break;
            }
        }
        return ans;
    }

    int atMostNGivenDigitSet(vector<string>& strs, int num) {
        m = strs.size();
        for (int i = 0; i < m; ++i){
            dig[i] = stoi(strs[i]);
        }
        int len = 1, offset = 1, tmp = num / 10;
        while(tmp>0){
            tmp /= 10;
            len++;
            offset *= 10;
        }
        cnt[0] = 1;
        int ans = 0;
        for (int i = m, k = 1; k < len; ++k, i*=m){
            cnt[k] = i;
            ans += i;
        }
        return ans + f(num, offset, len);
    }
};