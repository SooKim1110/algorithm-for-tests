// 경우의 수, DFS
// direction 배열을 만들어주어서 (eg. Dir moveDir[3] = { {0, 1}, {1, 0}, {1, 1} } 반복문을 사용하면 더 간결한 코드로 작성할 수 있다.
// 위와 같이 짜면 범위를 벗어나거나 벽일 경우 + 대각선일때 추가적으로 확인해야하는 벽일 경우를 확인해주면 된다. 
// 파이프의 시작점을 사용하는 방식으로 풀었지만 끝점을 기록하면 종료조건이 x == N && y == N 으로 간단해지기 때문에 끝점을 사용하는 것이 나을 것 같다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

bool board[17][17];
int ans = 0, N;

// dir -> 가로: 0, 세로: 1, 대각선: 2
void dfs(pair<int, int> p, int dir){
  int x = p.first, y = p.second;
  if ((x == N-1 && y == N-1 && dir == 2) || (x == N-1 && y == N && dir == 1) || (x == N && y == N-1 && dir == 0)){
    ans++;
    return;
  }
  
  // 가로 방향
  if (dir == 0){
    if (y+2 <= N && board[x][y+2] != 1)
      dfs(make_pair(x,y+1), 0);
    if (x+1 <= N && y+2 <= N && board[x][y+2] != 1 && board[x+1][y+1] != 1 && board[x+1][y+2] != 1)
      dfs(make_pair(x,y+1),2);
  }

  // 세로 방향
  if (dir == 1){
    if (x+2 <= N && board[x+2][y] != 1)
      dfs(make_pair(x+1,y), 1);
    if (x+2 <= N && y+1 <= N && board[x+1][y+1] != 1 && board[x+2][y] != 1 && board[x+2][y+1] != 1)
      dfs(make_pair(x+1,y), 2);
  }

  // 대각선 방향 
  if (dir == 2){
    if (x+1 <= N && y+2 <= N && board[x+1][y+2] != 1)
      dfs(make_pair(x+1,y+1), 0);
    if (x+2 <= N && y+1 <= N && board[x+2][y+1] != 1)
      dfs(make_pair(x+1,y+1), 1);
    if (x+2 <= N && y+2 <= N && board[x+2][y+1] != 1 && board[x+1][y+2] != 1 && board[x+2][y+2] != 1)
      dfs(make_pair(x+1,y+1), 2);
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  int n;
  cin >> n;
  N = n;
  for (int i = 1; i<=n; i++){
    for (int j = 1; j<=n; j++){
      cin >> board[i][j];
    }
  }

  dfs(make_pair(1,1), 0);
  
  cout << ans << '\n';
}
