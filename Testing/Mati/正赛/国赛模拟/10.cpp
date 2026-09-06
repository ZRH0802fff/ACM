#include<bits/stdc++.h>
using namespace std;

int n;
int ans;
int num2, num5;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    ans = 1;
    for (int i = 0; i < n; ++i){
        int num;
        cin >> num;
        while(num%2==0){
            num2 += 1;
            num /= 2;
        } 
        while(num%5==0){
            num5++;
            num /= 5;
        }
        ans = (ans * (num% 10)) % 10;
    }
    if(num2>num5){
        num2 -= num5;
        while(num2!=0){
            ans = (ans * 2) % 10;
            num2--;
        }
    }else if(num2<num5){
        num5 -= num2;
        while(num5!=0){
            ans = (ans * 5) % 10;
            num5--;
        }
    }
    cout << ans << '\n';
    return 0;
}