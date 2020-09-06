// 문제 출처 https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff43
// 난이도: ****

// < Perfect Subarray >
// 문제 요약: 수열의 부분수열 중 합이 양의 정수의 제곱(0,1,4,9...)이 되는 부분수열의 개수를 찾는 문제.
// 주의점
// 1) O(N^2) 보다 빠른 풀이를 찾아내는 것이 관건.

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