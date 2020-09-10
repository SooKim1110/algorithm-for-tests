// 문제 출처 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff43
// 난이도: ****

// < Perfect Subarray >
// 문제 요약: 수열의 부분수열 중 합이 양의 정수의 제곱(0,1,4,9...)이 되는 부분수열의 개수를 찾는 문제.
// 주의점
// 1) O(N^2) 보다 빠른 풀이를 찾아내는 것이 관건.
// 2) prefix_sum(0부터 i번째 인덱스까지의 합)을 구하면 모든 부분수열의 합을 나타낼 수 있다.
// 3) 각 prefix_sum이 나온 개수를 저장하고 참조할때는 배열을 써도 되고 unordered_map을 써도 된다. 다만 unordered_map 참조 시간도 걸림을 고려해야한다.
// 4) prefix_sum이 음수가 될 수 있기 때문에 offset을 더해줘야한다.
// 5) 처음에 prefix_sum이 0으로 시작하는 것을 넣어줘야한다! 
// 참고 영상: https://www.youtube.com/watch?v=Lyay4WJwXyI 

//풀이 1) O(N^2) 풀이
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

int cases[100001];
int sums [100001];

int main(){
    int T;
    cin >> T;
    for(int t = 1; t<=T; t++){
      int n, ans = 0;
      cin >> n;
       
      cin >> cases[0];
      sums[0] = cases[0];
      for (int i = 1; i<n; i++){
        cin >> cases[i];
        sums[i] = sums[i-1] + cases[i];
      }
      
      int sum;
      for (int i = 0; i<n; i++){
        for (int j = 0; i+j<n; j++){
          sum = sums[i+j];
          int root = sqrt(sum);
          if (root*root == sum){
            ans++;
          }
          sums[i+j] -= cases[i];
        }
      }
  
      cout << "Case #" << t<<": " << ans << endl;
    }
    return 0;
} 

//풀이 2) 
//출처: icecuber
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
    int n;
    cin >> n;

    vector<int> prefix_sum = {0};
    for (int i = 0; i < n; i++) {
      int num;
      cin >> num;
      prefix_sum.push_back(prefix_sum.back() + num);
    }

    const int offset = n*100+1000;
    vector<int> P(offset*2);

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
      for (int x = 0; x*x <= n*100; x++) {
	      int idx = prefix_sum[i] + offset - x*x;
	      if (idx >= 0 && idx < offset*2)
	        ans += P[idx];
      }
      P[prefix_sum[i] + offset]++;
    }
    cout << ans << endl;
  }
}

//풀이 3)구글 풀이 O(N * sqrt(N*MAX_A)) 구현
#include <algorithm>
#include <iostream>
#include <vector>
#include <math.h>
#include <string.h> 
using namespace std;

int cases[100001];
int S [100001];
int P [20000010];

int main(){
    int T;
    cin >> T;
    for(int t = 1; t<=T; t++){
      memset(cases,0,sizeof(cases));
      memset(S,0,sizeof(S));
      memset(P,0,sizeof(P));
      int n;
      long long ans = 0;
      cin >> n;
      
      int max_num = -101;
      for (int i = 1; i<=n; i++){
        cin >> cases[i];
        max_num = max(cases[i], max_num);
      }

      int offset = n*100;

      //compute S
      int idx = 0;
      while (idx <= sqrt(n*max_num)){
        S[idx] = idx * idx;
        idx++;
      }

      int prefix_sum = 0;
      for (int i = 0; i<=n; i++){
        prefix_sum += cases[i];
  
        //compute Res(ans)
        for (int j = 0; j<idx; j++){
          if (prefix_sum - S[j] + offset < 0) break;
          ans += P[prefix_sum - S[j] + offset];
        }
        //compute P
        P[prefix_sum+offset]++;
      }

      cout << "Case #" << t<<": " << ans << endl;
    }
    return 0;
} 