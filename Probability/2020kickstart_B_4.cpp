// 문제 출처 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc8
// 난이도: ****

// < Wandering Robot >
// 문제 요약: 로봇이 구멍에 빠지지 않고 도착할 확률을 구하는 문제.
// 1) 

// 풀이1) 
// 구멍의 바로 위, 바로 왼쪽을 갈 확률을 구해서 더함
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

//풀이 2)
//출처 scottwu
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int MAXN = 1000100;

int W, H, L, U, R, D;
double lfac[MAXN];
double p2[MAXN];

double choose (int N, int K)
{
    if (K < 0 || K > N) return 0;
    return exp (lfac[N] - lfac[K] - lfac[N-K] - p2[N]);
}

void gogo()
{
    cin >> W >> H >> L >> U >> R >> D;
    W--, H--, L--, U--, R--, D--;

    double ans = 0.0;

    int ly = U, lx = R;
    if (R < W)
    {
        double mult = 1.0;
        while (ly > 0)
        {
            ly--;
            lx++;

            if (lx >= W)
            {
                lx = W - 1;
                mult = 0.5;
            }
            //cout << mult << lx << ly << "\n";
            ans += mult * choose (lx + ly, lx);
        }
    }

    swap (U, L);
    swap (D, R);
    swap (H, W);
    ly = U, lx = R;
    if (R < W)
    {
        double mult = 1.0;
        while (ly > 0)
        {
            ly--;
            lx++;

            if (lx >= W)
            {
                lx = W - 1;
                mult = 0.5;
            }
            ans += mult * choose (lx + ly, lx);
        }
    }
    cout << fixed << setprecision(9);
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(0);

    lfac[0] = 0.0;
    for (int i = 1; i < MAXN; i++)
        lfac[i] = lfac[i-1] + log(i);
    p2[1] = log(2);
    for (int i = 2; i < MAXN; i++)
        p2[i] = p2[i-1] + p2[1];

    //cout << choose (1, 0) << "\n";

    int T; cin >> T;
    for (int i = 0; i < T; i++)
    {
        cout << "Case #" << i + 1 << ": ";
        gogo();
    }
}