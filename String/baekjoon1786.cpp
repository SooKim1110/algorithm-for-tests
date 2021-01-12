// 문제 출처 https://www.acmicpc.net/problem/1786
// 난이도: ****

// < 찾기 >
// 문제 요약: KMP 알고리즘을 이용한 검색 기능 구현

// https://bowbowbow.tistory.com/6 참고

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int k[1000001];

//KMP랑 유사한 원리 (P의 suffix(인덱스 i) 가 prefix(인덱스 j)와 일치하는지 확인)
void calculate_k(string P)
{
  int len = P.length();
  int j = 0;
  for (int i = 1; i < len; i++)
  {
    // 일치하지 않을 경우 중간 단계 최대한 건너뛰기 (겹치는 만큼 j 인덱스 앞당기기)
    while (j > 0 && P[i] != P[j])
    {
      j = k[j - 1];
    }
    // 일치할 경우 일치하는 길이 (j까지 확인했으므로 j) 저장
    if (P[i] == P[j])
      k[i] = ++j;
  }
}

int main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  string T, P;
  int cnt = 0;
  vector<int> ans_idx;

  getline(cin, T);
  getline(cin, P);

  calculate_k(P);

  // i는 계속 1씩 올리고 상황에 따라 j만 조정해주면 됨. 
  int j = 0;
  for (int i = 0; i<T.length(); i++){
    while (j > 0 && T[i] != P[j]){
      // 일치했던 곳까지
      j = k[j-1];
    }
    if (T[i] == P[j]){
      if (j == P.length()-1){
        ans_idx.push_back(i-j);
        j = k[j];
        cnt++;
      }
      else{
        j++;
      }
    }
  }

  cout << cnt << '\n';
  for (int idx: ans_idx){
    cout << idx+1 << '\n';
  }
}