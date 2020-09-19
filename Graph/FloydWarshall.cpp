// 문제 출처 https://www.acmicpc.net/problem/11780
// 난이도: ***

// < 플로이드2 >
// 문제 요약: 모든 도시의 쌍에 대해 A에서 B 도시까지 가는데 드는 버스 비용 최소화

// 주의점
// 1) 다익스트라는 시작점이 1개일때. 플로이드는 모든 다익스트라를 v번 반복하여 모든 쌍의 최단경로.
// +) 만약 시작 도시와 도착 도시 사이의 노선이 여러개이면 최솟값을 저장한다.
// 2) 다익스트라 역추적과 달리 i->k, k->j 간선을 i->j로 바꿨기 때문에 i->j가 어떤 정점을 가리키고 있었는지 저장
// x -> go[x][y] -> y (다른 알고리즘들은 그냥 하나의 배열이 왜 바뀌었는지 저장하면 됨)
#include <iostream>
#include <queue>
using namespace std;

int d[101][101];
int go[101][101];
const int inf = 1000000000;

void print_route(int i, int j){
  if (go[i][j] == -1){
    cout << "0\n";
    return;
  }

  queue<int> q;
  q.push(i);
  while (i != j){
    i = go[i][j];
    q.push(i);
  }

  cout << q.size() << ' ';
  while (!q.empty()){
    cout << q.front() << ' ';
    q.pop();
  }
  cout << '\n';
}

int main(){
  int n,m;
  cin >> n >> m;

  for (int i = 1; i<=n; i++){
    for (int j = 1; j<=n; j++){
      if (i == j) d[i][j] = 0;
      else d[i][j] = inf;
      go[i][j] = -1;
    }
  }

  for (int i = 0; i<m; i++){
    int from, to, cost;
    cin >> from >> to >> cost;
    if (d[from][to] > cost)
      d[from][to] = cost;
    go[from][to] = to;
  }

  for (int k = 1; k<=n; k++){
    for (int i = 1; i<=n; i++){
      for (int j = 1; j<=n; j++){
        if (d[i][j] > d[i][k] + d[k][j]){
          d[i][j] = d[i][k] + d[k][j];
          go[i][j] = go[i][k];
        }
      }
    }
  }

  for (int i = 1; i<=n; i++){
    for (int j = 1; j<=n; j++){
      if (d[i][j] == inf) cout << 0 << ' ';
      else cout << d[i][j] << ' ';
    }
    cout << '\n';
  }

  for (int i = 1; i<=n; i++){
    for (int j = 1; j<=n; j++){
      print_route(i,j);
    }
  }
  return 0;
}