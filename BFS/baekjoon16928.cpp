// 문제 출처 https://www.acmicpc.net/problem/16928
// 난이도: **

// < 뱀과 사다리 게임 >
// 문제 요약: 1번부터 100번까지 도착하는 최소 횟수를 구하는 문제. 
// 사다리와 뱀을 통해 위와 아래 번호로 이동할 수 있고 주사위를 굴려 1~6까지 이동할 수 있다.

// 주의점
// 1) 구현할 때 뱀과 사다리를 구분할 필요가 없다.
// 2) queue에 한 단계 끝날때마다 -1를 넣어주고 총 단계를 계산해도되고 dist배열을 만들어 -1로 초기화하고 dist[y] = dist[x]+1처럼 계산해도된다.
// 3) visited 배열을 꼭 만들어야 메모리 초과가 안난다.

//풀이 1)
#include <iostream>
#include <queue>
using namespace std;

int go[101];
int visited[101];
int ans = 0;

void bfs(int n){
  queue<int> q;
  q.push(n);
  visited[n] = 1;
  q.push(-1);
  while (!q.empty()){
    int x = q.front();
    q.pop();
    if (x == -1) {
      q.push(-1);
      ans++;
    }
    else if (x == 100)
      break;
    else{
      visited[x] = 1;
      for (int i = 1; i<=6; i++){
        if (x+i <=100 && !visited[x+i]){
          int nxt = go[x+i];
          if (nxt != 0)
            q.push(nxt);
          else
            q.push(x+i);
        }
      }
    }
  }
}

int main(){
  int n,m;
  cin >> n >> m; 

  for (int i = 0; i<n+m; i++){
    int x,y;
    cin >> x >> y;
    go[x] = y;
  }

  bfs(1);
  cout << ans << endl;
  return 0;
}

//풀이 2)
//출처: 백준 강의
#include <queue>
#define next _next
using namespace std;

int dist[101];
int next[101];
int main(){
  int n,m;
  cin >> n >> m;
  for (int i = 1; i<=100; i++){
    next[i] = i;
    dist[i] = -1;
  }
  while (n--){
    int x,y;
    cin >> x >> y;
    next[x] = y;
  }
  while (m--){
    int x,y;
    cin >> x >> y;
    next[x] = y;
  }
  dist[1] = 0;
  queue<int> q;
  q.push(1);
  while (!q.empty()){
    int x = q.front(); q.pop();
    for (int i = 1; i<= 6; i++){
      int y = x+i;
      if (y > 100) continue;
      y = next[y];
      if (dist[y] == -1){
        dist[y] = dist[x]+1;
        q.push(y);
      }
    }
  }
  cout << dist[100] << '\n';
  return 0;
}