// 문제 출처 https://www.acmicpc.net/problem/11779
// 난이도: ***

// < 최소비용 구하기 2 >
// 문제 요약: A에서 B 도시까지 가는데 드는 버스 비용 최소화, 경로 출력

// 주의점
// 1) 다익스트라는 시작점이 1개일때. 플로이드는 모든 다익스트라를 v번 반복하여 모든 쌍의 최단경로.
// 2) 경로 구하기 - 방문 기록 저장(hist 배열), 스택이용해서 역추적


#include <vector>
#include <iostream>

using namespace std;

int d[101][101];

int main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int n, m;
  cin >> n >> m;

  for (int i = 1; i<=n; i++){
    for (int j = 1; j<=n; j++){
      d[i][j] = 100000000;
    }
  }

   for (int i = 1; i<=n; i++){
     d[i][i] = 0;
   }

  for (int i = 0; i<m; i++){
    int from, to, cost;
    cin >> from >> to >> cost;
    d[from][to] = cost;
  }

  for (int k = 1; k<=n; k++){
    for (int i = 1; i<=n; i++){
      for (int j = 1; j<=n; j++){
        if (d[i][k] + d[k][j] < d[i][j]){
          d[i][j] = d[i][k] + d[k][j];
        }
      }
    }
  }

  for (int i = 1; i<=n; i++){
    for (int j = 1; j<=n; j++){
      if (d[i][j] >= 100000000) cout << 0 << ' ';
      else cout << d[i][j] << ' ';
    }
    cout << '\n';
  }
  return 0;
}