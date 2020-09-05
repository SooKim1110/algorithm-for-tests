// 문제 출처 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc8
// 난이도: ****

// < Wandering Robot >
// 문제 요약: 로봇이 구멍에 빠지지 않고 도착할 확률을 구하는 문제.
// 주의점
// 1) 팩토리얼 계산은 로그로 할 수 있다
// 2) 문제에 나온 것처럼 맨 오른쪽, 맨 밑에 있으면 선택지가 1가지밖에 없으므로 이런 예외 상황의 계산은 다르게 처리해줘야한다.

//풀이 1) 구멍에 빠질 확률을 구하고 1에서 빼줌
//참고 https://eliasnodland.wordpress.com/2020/05/09/google-kickstart-round-b-problem-d-wandering-robot/

#include <bits/stdc++.h>
using namespace std;

const int XMAX = 1e5;
const int YMAX = 1e5;

// 로그 누적 합을 저장하는 배열 
std::vector<double> logfac(XMAX + YMAX);

// 특정 칸까지 갈 확률 (x+y)!/(x!*y!) * (1/2)^(x+y)
double probability(int x, int y) {
        return std::exp(logfac[x + y] - logfac[y] - logfac[x] -
                        (x + y) * std::log(2));
}

double solve(int W, int H, int L, int U, int R, int D) {
        // 가로 전체 혹은 세로 전체를 구멍이 차지하면 무조건 빠지게 됨.
        if (U == 1 && D == H) return 0.0;
        if (L == 1 && R == W) return 0.0;
        --W, --H, --L, --U, --R, --D;

        // 구멍에 빠질 확률 구하기 (R == W, D == H 일 때는 제외)
        double p = 0.0;
        if (U != 0)
                for (int x = L; x <= R && x < W; ++x){
                        p += probability(x, U - 1); 
                }

        if (L != 0)
                for (int y = U; y <= D && y < H; ++y){
                        p += probability(L - 1, y); 
                }

        // 예외 처리 - 이 위치에 있으면 100% 구멍에 빠진다
        if (R == W)
                for (int y = 0; y < U; ++y){
                        p += probability(R - 1, y); 
                }
        if (D == H)
                for (int x = 0; x < L; ++x) {
                        p += probability(x, H - 1); 
                }

        // 실제로 구멍에 빠지려면 한 번 더 움직여야하므로 2로 나눠줌
        return 1.0 - p / 2.0;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int t;
  cin >> t;
  int cc = 1;

    //logfac logfac is an array where logfac[n] is the logarithm of n!. 
    logfac[0] = 0.0;
    for (int i = 1; i<XMAX + YMAX; i++){
        logfac[i] = logfac[i-1]+ log(i);
    }

  while (t--) {
    cout << "Case #" << cc++ << ": ";
    int W,H,L,U,R,D;
    cin >> W >> H >> L >> U >> R >> D;
    
    cout << solve(W,H,L,U,R,D) << endl;
  }
}

//풀이 2) 구멍의 위/ 아래로 갈 확률을 구한 후 더해준다. 
//출처 scottwu https://www.youtube.com/watch?v=AP74zQ0ZmRM

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

