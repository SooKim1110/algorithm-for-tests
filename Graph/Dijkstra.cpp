// 문제 출처 https://www.acmicpc.net/problem/11779
// 난이도: ***

// < 최소비용 구하기 2 >
// 문제 요약: A에서 B 도시까지 가는데 드는 버스 비용 최소화, 경로 출력

// 주의점
// 1) 다익스트라 - O(V^2) 검사하지 않은 정점 중 dist 값 가장 작은 정점 V 선택. V와 연결된 모든 정점 검사 dist 업데이트
// 2) 경로 구하기 - 방문 기록 저장(hist 배열), 스택이용해서 역추적

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Edge{
  int to;
  int cost;
  Edge(int to, int cost) : to(to), cost(cost){}
};

vector <Edge> adj[1001];
int dist[1001];
bool check[1001];
int inf = 1000000000;
int hist[1001];

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n,m;
  cin >> n >> m;

  for (int i = 0; i<m; i++){
    int from, to, cost;
    cin >> from >> to >> cost;
    adj[from].push_back(Edge(to,cost));
  }

  int start, end;
  cin >> start >> end;
  for (int i = 1; i<=n; i++){
    dist[i] = inf;
  }
  //시작 0으로 설정
  dist[start] = 0;
  hist[start] = -1;
  
  //노드 전부 탐색
  for (int k = 0; k<n-1; k++){
    int m = inf+1;
    int x = -1;
    //아직 안 방문했으면서 최소인 노드 찾기
    for (int i = 1; i<=n; i++){
      if (check[i] == false && m > dist[i]){
        m = dist[i];
        x = i;
      }
    }
    check[x] = true;
    // x노드에 연결된 모든 정점 방문
    for (int i = 0; i<adj[x].size(); i++){
      int y = adj[x][i].to;
      if (adj[x][i].cost+ dist[x] < dist[y]){
        dist[y] = adj[x][i].cost + dist[x];
        hist[y] = x;
      }
    }
  }

  stack<int> s;
  int t = end;
  while (t != -1){
    s.push(t);
    t = hist[t];
  }

  cout << dist[end] << '\n' << s.size() << '\n';
  while (!s.empty()){
    cout << s.top() << ' ';
    s.pop();
  }
  return 0;
}