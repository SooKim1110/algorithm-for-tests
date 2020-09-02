// 문제 출처 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc8
// 난이도: **

// < Robot Path Decoding >
// 문제 요약: 입력 스트링을 받았을 때 로봇의 최종 위치를 출력. N,S,E,W의 입력으로 동서남북 방향으로 움직이고 특별한 입력인 X(Y)이 있어서 Y방향으로 X번 이동할 수 있음.
// 주의점
// 1) 스택에 현재까지 계산된 값을 넣어주는 것도 방법이다.
// 2) %연산자를 사용해서 오버플로우를 막아준다.

// 풀이1) 
// 제출한 풀이. 반복되는 코드가 많고 효율적이지 않다.
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <stack>

#define WIDTH 1000000000

using namespace std;

long long ways[4];
int main(){
    int T;
    cin >> T;
    for(int t = 1; t<=T; t++){
        for (int i = 0; i<4; i++){
            ways[i] = 0;
        }
        string s;
        cin >> s;
        vector<int> st;
        long long mul = 1;
        for (int i = 0; i<s.size(); i++){
            if (s[i] == 'N'){
                ways[0] = (ways[0] + mul) % WIDTH;
            }
            else if (s[i] == 'S'){
                ways[1] = (ways[1] + mul) % WIDTH;
            }
            else if (s[i] == 'E'){
                ways[2] = (ways[2] + mul) % WIDTH;
            }
            else if (s[i] == 'W'){
                ways[3] = (ways[3] + mul) % WIDTH;
            }
            else if (s[i] == ')'){
                st.pop_back();
                mul = 1;
                for (int k = 0; k<st.size(); k++){
                    mul *= st[k];
                    mul %= WIDTH;
                }
            }
            else if ('0'<= s[i] && s[i] <='9'){
                st.push_back(s[i]-'0');
                mul *= (s[i]-'0');
                mul = mul %WIDTH;
            }
        }
        long long row = 1, col = 1;
        row += ways[1] -ways[0];
        if (row<1)
            row += WIDTH;
        col += ways[2] -ways[3];
        if (col<1)
            col += WIDTH;
        cout << "Case #" << t<<": " << col << ' ' << row << endl;
    }
    return 0;
}

// 풀이2)
// 참고할만한 풀이(출처: icecuber)
// x,y 변수를 사용해 위치를 바로 계산하였고, 하나의 배열 mul에 결과를 누적하여 저장했다. 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  int cc = 1;
  while (t--) {
    cout << "Case #" << cc++ << ": ";
    string s;
    cin >> s;
    ll mod = 1e9;
    ll x = 0, y = 0;
    vector<ll> mul = {1};
    for (char c : s) {
      if (c >= '2' && c <= '9')
	mul.push_back(mul.back()*(c-'0')%mod);
      else if (c == 'E') x = (x+mul.back())%mod;
      else if (c == 'W') x = ((x-mul.back())+mod)%mod;
      else if (c == 'S') y = (y+mul.back())%mod;
      else if (c == 'N') y = ((y-mul.back())+mod)%mod;
      else if (c == '(') continue;
      else if (c == ')') mul.pop_back();
      else assert(0);
    }
    cout << x+1 << ' ' << y+1 << endl;
  }
}