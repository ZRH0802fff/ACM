#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s;
    int k;
    cin >> s >> k;

    while (k > 0){
        int i = 0;
        while (i < s.size() - 1 && s[i] <= s[i + 1]){
            i++;
        }
        s.erase(i, 1);
        k--;
    }
    while (s.size() > 1 && s[0] == '0'){
        s.erase(0, 1);
    }
    if (s.empty()){
        cout << 0 << endl;
    }else{
        cout << s << endl;
    }
    return 0;
}