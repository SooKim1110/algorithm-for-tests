// 문제 출처 https://www.acmicpc.net/problem/1654
// 난이도: ***

// < 랜선 자르기 >
// 문제 요약: 랜선 K개 길이가 주어졌을때 랜선을 같은 길이로 잘라 N개 이상을 만들어야한다. 이 때 가장 길게 자를 수 있는 길이 구하기.

//주의
// 1) 종료 조건 꼼꼼하게 보기 l < r인지, l <= r 인지
// 2) l+r 했을 때 int 범위 초과하므로 long long 으로 선언해야한다

// 풀이 1)
#include <iostream>
#include <vector>
using namespace std;

int check(vector<int> lines, long long x){
  int num = 0;
  for (int line: lines){
    num += line/x;
  }
  return num;
}
int main(){
  int k,n, ans = 0;
  cin >> k >> n;
  vector<int>  lines(k);

  for (int i = 0; i<k; i++){
    cin >> lines[i];
  }

  long long l = 0, r = 2147483647, mid;
  while (l<=r){
     mid = (l+r)/2;
    int num = check(lines, mid);
    if (num >= n){
      ans = mid;
      l = mid+1;
    }
    else{
      r = mid-1;
    }
  }
  cout << ans << '\n';
}

//풀이 2) a 최대를 max로 설정해준다.
#include <cstdio>
long long a[10000];
int n,m;
bool check(long long x) {
    int cnt = 0;
    for (int i=0; i<n; i++) {
        cnt += a[i]/x;
    }
    return cnt >= m;
}
int main() {
    scanf("%d %d",&n,&m);
    long long max = 0;
    for (int i=0; i<n; i++) {
        scanf("%lld",&a[i]);
        if (max < a[i]) {
            max = a[i];
        }
    }
    long long ans = 0;
    long long l = 1;
    long long r = max;
    while (l <= r) {
        long long mid = (l+r)/2;
        if (check(mid)) {
            if (ans < mid) {
                ans = mid;
            }
            l = mid+1;
        } else {
            r = mid-1;
        }
    }
    printf("%lld\n",ans);
    return 0;
}