// 순열(연산 순서 정하기) + 시뮬레이션(회전 구현)

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;

int n, m, k;
int arr[50][50];
vector<vector<int>> op;
vector<vector<int>> order(6, vector<int>(3, 0));
bool chk[6];
int ans = 100000;

void calculate()
{
  int copy_arr[50][50];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      copy_arr[i][j] = arr[i][j];
    }
  }

  for (int i = 0; i < k; i++)
  {
    int r = order[i][0], c = order[i][1], s = order[i][2];
    // r,c 에서 j만큼 떨어진 정사각형을 돌림
    for (int j = 1; j <= s; j++)
    {
      int x = r - j + 1, y = c - j;
      int last = copy_arr[x][y];

      //* 끝에서부터 하나씩 반대로 옮겨옴 (서남동북 순서)! *
      //서
      while (r + j > x)
      {
        copy_arr[x][y] = copy_arr[x + 1][y];
        x++;
      }
      //남
      while (c + j > y)
      {
        copy_arr[x][y] = copy_arr[x][y + 1];
        y++;
      }
      //동
      while (r - j < x)
      {
        copy_arr[x][y] = copy_arr[x - 1][y];
        x--;
      }
      //북
      while (c - j < y)
      {
        copy_arr[x][y] = copy_arr[x][y - 1];
        y--;
      }
      copy_arr[x][y] = last;
    }
  }

    for (int i = 0; i < n; i++)
    {
      int sum = 0;
      for (int j = 0; j < m; j++)
      {
        sum += copy_arr[i][j];
      }
      ans = min(ans, sum);
    }
}

void combination(int idx)
{
  if (idx == k)
  {
    calculate();
    return;
  }

  for (int i = 0; i < k; i++)
  {
    if (chk[i] == 0)
    {
      order[idx] = op[i];
      chk[i] = 1;
      combination(idx + 1);
      chk[i] = 0;
    }
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);

  cin >> n >> m >> k;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> arr[i][j];
    }
  }

  for (int i = 0; i < k; i++)
  {
    int r, c, s;
    cin >> r >> c >> s;
    op.push_back({r - 1, c - 1, s});
  }

  combination(0);

  cout << ans << '\n';
}

