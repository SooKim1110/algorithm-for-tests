// 문제 출처 https://www.acmicpc.net/problem/9019
// 난이도: ***

// < DSLR >
// 문제 요약: 4자리 숫자 A에서 B로 변환하기 위해 필요한 최소한의 명령어 나열을 출력한다. 명령어는 4가지로 2배, 1 빼기, 자릿수 왼편으로 회전, 자릿수 오른편으로 회전이 있다.
// 주의점
// 1) 자릿수를 왼쪽, 오른쪽으로 돌릴 때 문자열로 변환해 돌리는 것보다 수식으로 계산하는 것이 빠르다.
// 2) 전 명령어 나열에 현재 명령어를 더하는 방식으로는 명령어가 얼마나 길어질지 모르고, 이것을 계속 저장해야하기 때문에 시간초과가 난다. 
//    대신 from 배열을 통해 현재 숫자가 어느 숫자에서 온건지를 기록하여서 이를 통해 b에서 a를 추적하는 방식으로 문제를 풀어야한다.


//풀이)
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

pair<int, char> visited[10000];
int from[10000];
char letter[4] = {'D','S','L','R'};

void bfs(int a, int b){
  queue <int> q;
  q.push(a);
  visited[a].first = 1;

  while (!q.empty()){
    int x = q.front();
    q.pop();

    if (x == b)
      break;
    else{
      for (int i = 0; i<4; i++){
        int n;
        if (i == 0){
          n = (2 * x) % 10000;
        }
        else if (i == 1){
          if (x == 0) n = 9999;
          else n = x-1;
        }
        else if (i == 2){
          n = (x%1000) * 10 + x/1000;
        }
        else{
          n = (x/10) + (x%10) * 1000;
        }
        if (visited[n].first == -1){
            visited[n].first = 1;
            visited[n].second = letter[i];
            from[n] = x;
            q.push(n);
          }
      }
    }
  }
}

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--){
    //visited 초기화
    for (int i = 0; i<10000; i++){
      visited[i] = make_pair(-1, '0');
      from[i] = -1;
    }
    
    int a,b;
    cin >> a >> b;
    bfs(a,b);
    string ans = "";
    while (b != a){
      ans += visited[b].second;
      b = from[b];
    }
    reverse(ans.begin(), ans.end());
    cout << ans << '\n';
  }
  return 0;
}