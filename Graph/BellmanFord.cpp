// 문제 출처 https://www.acmicpc.net/problem/11657
// 난이도: ***

// < 타임머신 >
// 문제 요약: 1번 도시에서 나머지 도시로 가는 가장 빠른 시간을 구하기 (음수 간선 존재)

// 주의점
// 1) 벨만포드 - O(VE) (O(V^3)) 모든 간선을 확인하는 것을 n-1번 반복. 최대 n-1 개의 간선을 거쳐야 최소 거리를 구할 수 있으므로.
// 2) 다익스트라와 달리 음수 간선이 존재해도 된다(다익스트라는 그리디 방식이므로 안됨.). 하지만 비효율적.
// 3) 음의 사이클 존재하는지 알 수 있다. n-1번이 아닌 n번 반복했을 때 거리 달라지면 음의 사이클 존재.
// +) 1번 시작이 아닌 전체 그래프에서 음의 사이클 존재 여부 알고 싶을때 -> dist[x] != inf 지우기 (inf 설정 이유가 단절을 표시하기 위해)
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
  int from;
  int to;
  int cost;
};
long long dist[501];
long long inf = 1000000000;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n,m;
  cin >> n >> m;
  
  vector<Edge> e(m);
  for (int i = 0; i<m; i++){
    cin >> e[i].from >> e[i].to >> e[i].cost;
  }
  for (int i = 1; i<=n; i++){
    dist[i] = inf;
  }
  //1번 노드에서 출발
  dist[1] = 0;
  bool neg_cycle = false;
  for (int i = 1; i<=n; i++){
    for (int j = 0; j< m; j++){
      int x = e[j].from;
      int y = e[j].to;
      int z = e[j].cost;
      if (dist[x] != inf && dist[y] > dist[x] + z){
        dist[y] = dist[x]+ z;
        if (i == n) neg_cycle = true;
      }
    }
  }
  
  if (neg_cycle) cout << "-1" << '\n';
  else{
    for (int i = 2; i<=n; i++){
      if (dist[i] == inf) cout << "-1" << '\n';
      else cout << dist[i] << '\n';
    }
  }
  return 0;
}