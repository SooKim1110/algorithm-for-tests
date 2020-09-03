// 문제 출처 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc8
// 난이도: ****

// <  >
// 문제 요약: 
// 1) 

// 풀이1) 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

double calculate_probability(int X, int Y){
    // (W+H!) / (W!*H!)
    X--; Y--;
    ll num = 1;
    int K = X + Y;
    // X smaller than Y
    if (X < Y){
        int t = Y;
        Y = X;
        X = t;
    }
    for (int i = 0; i<Y; i++){
        num = num*(K-i)/(Y-i);
    }
    double prob = num * powf(0.5,X+Y);
    return prob;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  int cc = 1;
  while (t--) {
    cout << "Case #" << cc++ << ": ";

    int W,H,L,U,R,D;
    cin >> W >> H >> L >> U >> R >> D;
    
    // 구멍의 가로 또는 세로가 전체 크기의 가로, 세로랑 같다면 구멍에 항상 빠짐 
    if (L == 1 && R == W){
        cout << 0.0 << endl;
        continue;
    }
    if (U == 1 && D == H){
        cout << 0.0 << endl;
        continue;
    }
    
    //구멍 위
    double prob = 0.0;
    if (U != 1){
        for (int i = L; i<=R && i< W; i++){
            prob += calculate_probability(i, U-1);
        }
    }
    //구멍 왼쪽
    if (L != 1){
        for (int i = U; i<=D && i< H; i++){
            prob += calculate_probability(L-1, i);
        }
    }
    
    prob /= 2;
    if (R == W){
        for (int i = 0; i<U; i++)
            prob += calculate_probability(R,i);
    }
    if (D == H){
        for (int i = 0; i<L; i++)
            prob += calculate_probability(i,H);
    }
    
    double ans = 1.0- prob;
    cout << ans << endl;
  }
}