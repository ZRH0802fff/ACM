// 最小的必要团队
// 作为项目经理，你规划了一份需求的技能清单req_skills
// 并打算从备选人员名单people中选出些人组成必要团队
// 编号为i的备选人员people[i]含有一份该备选人员掌握的技能列表
// 所谓必要团队，就是在这个团队中
// 对于所需求的技能列表req_skills中列出的每项技能，团队中至少有一名成员已经掌握
// 请你返回规模最小的必要团队，团队成员用人员编号表示
// 你可以按 任意顺序 返回答案，题目数据保证答案存在
// 测试链接 : https://leetcode.cn/problems/smallest-sufficient-team/

#include<bits/stdc++.h>
using namespace std;

int arr[63];
int dp[63][(1<<16)];
int m,n;

int f(int i,int s){
    if(s==(1<<n)-1) return 0;
    if(i==m) return INT_MAX;
    if(dp[i][s]!=-1) return dp[i][s];
    int p1=f(i+1,s);
    int p2=INT_MAX;
    int next2=f(i+1,(s|arr[i]));
    if(next2!=INT_MAX){
        p2=1+next2;
    }
    int ans=min(p1,p2);
    dp[i][s]=ans;
    return ans;
}

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        n=req_skills.size();
        m=people.size();

        unordered_map<string,int> book;
        int cnt=0;
        for(string s:req_skills){
            book[s]=cnt++;
        }
        for(int i=0;i<m; ++i){
            int status=0;
            for(string sk:people[i]){
                if(book.find(sk)!=book.end()){
                    status |= (1<<book[sk]);
                }
            }
            arr[i]=status;
        }

        for(int i=0;i<m; ++i){
            for(int j=0;j<(1<<n); ++j){
                dp[i][j]=-1;
            }
        }

        int size=f(0,0);
        vector<int> ans(size);
        for(int j=0,i=0,s=0;s!=(1<<n)-1; ++i){
            if(i==m-1 || dp[i][s]!=dp[i+1][s]){
                ans[j++]=i;
                s |= arr[i];
            }
        }
        return ans;
    }
};