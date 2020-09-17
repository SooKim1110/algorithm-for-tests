// 문제 출처 https://www.acmicpc.net/problem/11779
// 난이도: ***

// < 최소비용 구하기 2 >
// 문제 요약: A에서 B 도시까지 가는데 드는 버스 비용 최소화, 경로 출력

// 주의점
// 1) 다익스트라 - O(E log E) dist 값이 가장 작은 정점을 선택하는 시간을 줄임 -> 우선순위 큐 사용
// +) 최소 최대를 구해야할 때 우선순위 큐를 써보자 (구간의 최소 최대는 세그먼트 트리)
// dist 바뀔 때 (dist, 정점) 힙에 넣어주기. 삭제가 불가능하므로 중복된 노드라도 넣기. 간선 개수만큼 힙에 넣고 힙은 log 시간이므로 E log E.
// +) E log V 로 구현하려면 BST 사용. 

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
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
  priority_queue <pair<int, int> > q;
  q.push(make_pair(0, start));
  hist[start] = -1;
  
  //노드 전부 탐색
  while (!q.empty()){
    auto p = q.top();
    q.pop();
    int x = p.second;
    if (check[x]) continue;
    check[x] = true;
    
    // x노드에 연결된 모든 정점 방문
    for (int i = 0; i<adj[x].size(); i++){
      int y = adj[x][i].to;
      if (adj[x][i].cost+ dist[x] < dist[y]){
        dist[y] = adj[x][i].cost + dist[x];
        hist[y] = x;
        q.push(make_pair(-dist[y],y));
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


//+) E log V 구현
// #include <cstdio>
// #include <vector>
// #include <set>
// using namespace std;
// struct Edge {
//     int to;
//     int cost;
//     Edge(int to, int cost) : to(to), cost(cost) {
//     }
// };
// vector<Edge> a[20001];
// int dist[20001];
// int inf = 1000000000;
// int main() {
//     int n,m;
//     scanf("%d %d",&n,&m);
//     int start;
//     scanf("%d",&start);
//     for (int i=0; i<m; i++) {
//         int x,y,z;
//         scanf("%d %d %d",&x,&y,&z);
//         a[x].push_back(Edge(y,z));
//     }
//     for (int i=1; i<=n; i++) {
//         dist[i] = inf;
//     }
//     dist[start] = 0;
//     set<pair<int,int>> s;
//     s.insert(make_pair(0, start));
//     while (!s.empty()) {
//         auto p = *s.begin();
//         s.erase(s.begin());
//         int x = p.second;
//         for (int i=0; i<a[x].size(); i++) {
//             int y = a[x][i].to;
//             if (dist[y] > dist[x] + a[x][i].cost) {
//                 if (dist[y] != inf) {
//                     s.erase(s.find(make_pair(dist[y],y)));
//                 }
//                 dist[y] = dist[x] + a[x][i].cost;
//                 s.insert(make_pair(dist[y],y));
//             }
//         }
//     }
//     for (int i=1; i<=n; i++) {
//         if (dist[i] >= inf) {
//             printf("INF\n");
//         } else {
//             printf("%d\n",dist[i]);
//         }
//     }
//     return 0;
// }