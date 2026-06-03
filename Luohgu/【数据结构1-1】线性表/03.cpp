#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    int n = s.size();
    int stack[n];
    int r = 0;
    int idx = 0;
    int sum = 0;
    string tnum="";
    while(idx<n){
        if(s[idx]=='.'){
            stack[r++] = stoi(tnum);
            tnum.clear();
        }else if(s[idx]=='+' || s[idx]=='-' || s[idx]=='*' || s[idx]=='/'){
            int num2 = stack[--r];
            int num1 = stack[--r];
            if(s[idx]=='+')
                sum = num1 + num2;
            else if(s[idx]=='-')
                sum = num1 - num2;
            else if(s[idx]=='*')
                sum = num1 * num2;
            else if(s[idx]=='/')
                sum = num1 / num2;
            stack[r++] = sum;
            //cout << sum << "\n";//
        }else if(s[idx]=='@') break;
        else{
            tnum += s[idx];
        }
        idx++;
    }
    cout << sum << "\n";
    return 0;
}