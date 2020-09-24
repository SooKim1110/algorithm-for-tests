// 문제 출처 https://www.acmicpc.net/problem/1790
// 난이도: ***

// < 수 이어 쓰기 2 >
// 문제 요약:  1부터 N까지 숫자를 이어썼을 때 앞에서 k번째 자리 숫자 구하기

// 풀이 1)
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

long long check(int n){
  long long ans = 0;
  int len = to_string(n).length();   
  long long div = pow(10,len-1);
  ans += len * ((n-div)+1);
  len--;
  while (len >=1){
    ans += len * 9 * pow(10,len-1); 
    len--;
  }
  return ans;
}
int main(){
  int n,k;
  cin >> n >> k;

  int l = 0, r = n, mid;
  bool impossible = false;
  
  if (check(n) < k) impossible = true;
  else{
    while (true){
      mid = (l+r)/2;
      long long len = check(mid);
      if ( k <= len && k> len - to_string(mid).length()){
        break;
      }
      else if (k < len){
        r = mid-1; 
      }
      else{
        l = mid+1;
      }
    }
  }
  if (impossible)
    cout << "-1" << endl;
  else{
    cout << to_string(mid)[to_string(mid).length()-1-(check(mid)-k)] << endl;
  }
}


// 풀이 2)
#include <iostream>
using namespace std;
long long calc(int n) {
    long long ans = 0;
    for (int start=1, len=1; start<=n; start*=10, len++) {
        int end = start*10-1;
        if (end > n) {
            end = n;
        }
        ans += (long long)(end - start + 1) * len;
    }
    return ans;
}
int main() {
    int n;
    long long k;
    cin >> n >> k;
    if (calc(n) < k) {
        cout << -1 << '\n';
        return 0;
    }
    int left = 1;
    int right = n;
    int ans = 0;
    while (left <= right) {
        int mid = (left+right)/2;
        long long len = calc(mid);
        if (len < k) {
            left = mid+1;
        } else {
            ans = mid;
            right = mid-1;
        }
    }
    string s = to_string(ans);
    long long l = calc(ans);
    cout << s[s.length()-(l-k)-1] << '\n';
    return 0;
}