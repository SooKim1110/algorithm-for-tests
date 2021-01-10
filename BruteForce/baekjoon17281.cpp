// 문제 출처 https://www.acmicpc.net/problem/17281
// 난이도: **

// < ⚾ >
// 문제 요약: 야구의 각 이닝에서의 결과를 알고있을 때 가장 많은 득점을 하는 타순을 구하는 문제

// 주의점
// 1) 1번 선수가 4번 타자로 정해져있다. 타순은 이닝이 넘어가도 유지된다!
// 2) 8! * 50 이 최대이므로 브루트포스로 풀 수 있는 문제이다.

//풀이 1) c++ next_permutation 사용.
//타순을 나타내는 배열 cur_order에 계속 1번 선수를 insert해주고, 현재 선수들의 위치인 position을 매번 초기화해주는 등 비효율적인 부분이 많다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  int score = 0;
  vector<int> result;

  // 입력 받기
  cin >> n;
  for (int i = 0; i < n*9; i++)
  {
      int t;
      cin >> t;
      result.push_back(t);
  }

  // 시뮬레이션
  vector<int> order = {2, 3, 4, 5, 6, 7, 8, 9};

  do
  {
    int temp_score = 0;
    int out = 0;
    vector<int> cur_order = order;
    cur_order.insert(cur_order.begin()+3, 1);
    int count = 0;
    vector<int> position(9, -1);

    // 각 이닝별 시뮬레이션
    for (int i = 0; i < n; i++)
    {
      while (out <3){
        int cur_num = cur_order[count]-1;
        int cur_result = result[i*9+cur_num];
        if (cur_result == 0)
        {
          out++;
        }
        else
        {
          if (cur_result == 4)
            temp_score++;
          else
            position[cur_num] = cur_result;
          for (int k = 0; k < 9; k++)
          {
            if (position[k] != -1 && k != cur_num)
            {
              if (position[k] + cur_result >= 4)
              {
                temp_score++;
                position[k] = -1;
              }
              else{
                position[k] = position[k] + cur_result;
              }
            }
          }
        }
        count = (count+1) % 9;
      }
      //초기화
      out = 0;
      position = vector<int>(9, -1);
    }
    score = max(score, temp_score);
  } while (next_permutation(order.begin(), order.end()));

  // 출력
  cout << score;
}

//풀이 2) kmg8280님의 풀이 참고
// 선수별로 위치(position)을 기록하지 않고 base 위치별로 선수의 수를 계산하면 시간을 줄일 수 있다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  int score = 0;
  vector<int> result;

  // 입력 받기
  cin >> n;
  for (int i = 0; i < n * 9; i++)
  {
    int t;
    cin >> t;
    result.push_back(t);
  }

  // 시뮬레이션
  vector<int> order = {2, 3, 4, 5, 6, 7, 8, 9};

  do
  {
    int temp_score = 0;
    int out = 0;
    vector<int> cur_order = order;
    cur_order.insert(cur_order.begin() + 3, 1);
    int count = 0;
    int base[4];
    base[1] = base[2] = base[3] = 0;

    // 각 이닝별 시뮬레이션
    for (int i = 0; i < n; i++)
    {
      while (out < 3)
      {
        int cur_num = cur_order[count] - 1;
        int cur_result = result[i * 9 + cur_num];

        if (cur_result == 4)
        {
          temp_score += base[1] + base[2] + base[3] + 1;
          base[1] = base[2] = base[3] = 0;
        }
        else if (cur_result == 1)
        {
          temp_score += base[3];
          base[3] = base[2];
          base[2] = base[1];
          base[1] = 1;
        }
        else if (cur_result == 2)
        {
          temp_score += base[3] + base[2];
          base[3] = base[1];
          base[2] = 1;
          base[1] = 0;
        }
        else if (cur_result == 3)
        {
          temp_score += base[1] + base[2] + base[3];
          base[1] = base[2] = base[3] = 0;
          base[3] = 1;
        }
        else
        {
          out++;
        }

        count = (count + 1) % 9;
      }

      //초기화
      out = 0;
      base[1] = base[2] = base[3] = 0;
    }
    score = max(score, temp_score);
  } while (next_permutation(order.begin(), order.end()));

  // 출력
  cout << score;
}

//*참고* 순열 구현 (dfs)
int order[10], chk[10];

void dfs(int cnt) {
  //base 케이스 (순서를 모두 정했을 때)
	if (cnt == 9) {
		calculate_score(); // 이 타순대로 했을 때 점수 구하기 
		return;
	}
  // 4번 위치는 1번 선수로 정해져있으므로 다음 번호 구하기 (order 배열의 4번째 타자는 1로 초기화 되어있음)
	if (cnt == 3) {
		dfs(cnt + 1);
		return;
	}
  //순서를 정해야하는 8명 만큼 반복
	for (int i = 1; i < 9; i++) {
    //체크 안된 선수들 사용
		if (chk[i] == 1) continue;
		order[cnt] = i;
		chk[i] = 1;
		dfs(cnt + 1);
		chk[i] = 0;
	}
	return;
}