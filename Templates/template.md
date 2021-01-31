
# 알고리즘 정리 
<br/>

# 1) 알고리즘 기초
## DFS
``` cpp
#define MAX 1001;

bool visited[MAX];
vector<int> adj[MAX];

void dfs(int x){
  visited[x] = 1;
  for (int n: adj[x]){
    if (!visited[n]){
      dfs(n);
    }
  }
}

int main(){
  ...
  for (int i = 0; i<n; i++){
    int s,e;
    cin >> s >> e;
    adj[s].push_back(e);
    adj[e].push_back(s);
  }
  ...
}
```



## BFS
``` cpp
#define MAX 1001;

bool visited[MAX];
vector<int> adj[MAX];
 
void bfs(int x){
  queue<int> que;
  visited[x] = 1;
  que.push(x);

  int cur;
  while (!que.empty()){
    int cur = que.front(); que.pop();
    for (int n: adj[cur]){
      if (!visited[n]){
        visited[n] = 1;
        que.push(n);
      }
    }
  }
  
}

int main(){
  ...
  for (int i = 0; i<n; i++){
    int s,e;
    cin >> s >> e;
    adj[s].push_back(e);
    adj[e].push_back(s);
  }
  ...
}
``` 

## 이분탐색(Binary Search)

``` cpp
#define MAX 1001;

// 최솟값 찾기
int BinarySearch(int n){
  int low = 0, high = MAX, mid;
  while (low <= high){
    mid = (low+high)/2;
    if (check(mid)) high = mid-1;
    else low = mid+1;
  }
  return high + 1;
}

// 최댓값 찾기
int BinarySearch(int n){
  int low = 0, high = MAX, mid;
  while (low <= high){
    mid = (low+high)/2;
    if (check(mid)) low = mid+1;
    else high = mid -1;
  }
  return low-1;
}
``` 

## 머지 소트(Merge Sort)
``` cpp
#define MAX 1001

int num[MAX], buf[MAX];

// from부터 to 앞부분까지 정렬
void mergeSort(int from, int to){
  if (from >= to-1) return;
  int mid = (from +to)/2;
  mergeSort(from, mid);
  mergeSort(mid,to);
  merge(from, mid, to);
}

void merge(int from, int mid, int to){
  int i1 = from, i2 = mid, i = from;
  while (i1 < mid && i2 < to){
    if (num[i2] < num[i]){
      buf[i++] = num[i2++];
    }
    else {
      buf[i++] = num[i1++];
    }
  }

  //배열의 남은 숫자들 채워넣기
  while (i1<mid){
    buf[i++] = num[i1++];
  }
  while (i2 <to){
    buf[i++] = num[i2++];
  }
  // 실제 배열로 buf 숫자들 옮기기
  for (i = from; i< to; ++i)
    num[i] = buf[i];
}
``` 

## 백트래킹(Backtracking)
``` cpp
// 예시)
int arr[10], ans[10];
bool visited[10];

void backtracking(int len) {
	if (len == M) {
		// 종료시점에 나와야하는 결과 
		return;
	}

	for (i = 0; i < arr.size(); ++i) {
		if (!check(i)) {
			ans[len] = arr[i];
			visited[i] = 1;
			backtracking(len + 1);
			visited[i] = 0;
		}
	}
}
```
## 다이나믹 프로그래밍 (DP)
``` cpp
// 예시
#define MAX		1000

int num[MAX];
int dp[MAX];

//top down
int DP(int k) {
	//	기저조건
	if (k == 0) return 0;
	//	Memoization
	if (dp[k] != -1) return dp[k];
	//	점화식
	dp[k] = max(DP(k-1), DP(k-2));
	
	return dp[k];
}

//bottom up
int DP(int k) {
  dp[0] = 1;
  dp[1] = 1;
  for (int i = 2; i<=k; ++i){
    dp[k] = max(dp[k-1] + dp[k-2]);
  }
	return dp[k];
}

``` 
<br/>

# 2) 자료구조 
- Stack, Queue, Heap(Priority Queue), Map, Set (c++ stl)

## 인덱스 트리
- 구간 조회, 단일 업데이트
``` cpp
#define MAX         1000000
#define SZ_TR       2097152

int OFFSET, tree[SZ_TR];
int num[MAX+1];

// tree[0] 사용하지 않음, 리프 인덱스는 0 부터 시작, 왼쪽 노드(짝수) 오른쪽 노드(홀수)
void init(int N){
  int i;
  //OFFSET 계산 - 리프 노드 시작 위치
  for (OFFSET = 1; OFFSET < N; OFFSET *= 2);
  // 리프 노드에 수 채우기
  for (i = 0; i<N; ++i) tree[OFFSET + i] = num[i];
  // 남은 노드는 디폴트 값으로 채우기
  for (i = N; i<OFFSET; ++i) tree[OFFSET + i] = 0;
  // 구간합 계산
  for (i = OFFSET -1; i > 0; --i) tree[i] = tree[i*2] + tree[i*2+1];
}

int query(int from, int to){
  int res = 0;
  from += OFFSET, to += OFFSET;
  
  while (from <= to){
    if (from %2 == 1) res += tree[from++];
    if (to %2 == 0)  res += tree[to--];
    from /= 2; to /=2;
  }
  return res;
}

void update(int idx, int val){
  // idx 노드 업데이트(리프 인덱스는 0부터 시작!)
  idx += OFFSET;
  tree[idx] = val;

  idx /= 2;

  // 부모 노드들 업데이트
  while (idx >0){
    tree[idx] = tree[idx*2] + tree[idx*2+1];
    idx /= 2;
  }
}

int findKth(int kth){
  int idx = 1, left, right;

  while (idx < OFFSET){
    left = idx*2, right = left + 1;
    if (tree[left] >= kth) idx = left;
    else kth -= tree[left], idx = right;
  }
  return idx - OFFSET;
}
``` 

## 트라이(Trie)
- 문자열 검색
``` cpp
struct Trie {
  // 포함하는 문자 종류 개수만큼 배열 생성(다음으로 가리키는 문자) 
  Trie* Node[26];
  // 이 노드에서 끝나는 문자열이 있는가
  bool fin;

  Trie()
  {
    fin = false;
    for (int i = 0; i < 26; i++)
      Node[i] = NULL;
  }

  void Insert(string s){
    Trie* pNode = this;
    for (int i = 0; i<s.length(); ++i){
      int idx = s[i] - 'A';
      if (!pNode -> Node[idx])
        pNode -> Node[idx] = new Trie();
      pNode = pNode->Node[idx];
    }
    pNode -> fin = true;
  }

  void Search(string s){
    Trie* pNode = this;
    for (int i = 0; i<s.length(); ++i){
      int idx = s[i] - 'A';
      if (!pNode -> Node[idx])
        return false;
      pNode = pNode->Node[idx];
    }
    return (!pNode && pNode->fin);
	}
};

  int main(){
    Trie* root = new Trie();
    for (int i = 0; i<N; i++){
      root->Insert(words[i]);
    }
  }
``` 

<br/>

# 3) 정수론
## 유클리드 호제법(최대공약수 구하기)
``` cpp
typedef long long ll;

ll gcd(ll a, ll b){
  if (b == 0) return a;
  else return gcd(b,a%b);
}

ll gcd2(ll a, ll b) {
	ll t;

	while (b) {
		t = a % b;
		a = b;
		b = t;
	}

	return a;
}
``` 

## 확장 유클리드 호제법
- 정수 m,n 이 있을 때, am + bn = gcd(m,n)의 해가 되는 정수 a, b 짝 찾아내기
- 밑의 코드에서 a,b가 1일 때 주의
``` cpp
typedef long long ll;

ll ee(int a, int b, int K) {
	ll s, s0 = 1, s1 = 0, t, t0 = 0, t1 = 1, q, r;

	while (b != 0)
  {
    q = a / b;
    r = a % b;
    s = s0 - s1 * q;
    t = t0 - t1 * q;

    // 다음 계산
    a = b;
    b = r;
    s0 = s1, s1 = s;
    t0 = t1, t1 = t;
  }

	//음수라면 가능한 양수로 바꾸어줌
  t0 = (t0 % K + K) % K;
  return t0;
}
``` 

## 에라스토테네스의 체 (소수 구하기)
``` cpp
#define MAX    	1001

bool flag[MAX+1];
vector<int> primes;

int main(){
  for (int i = 2; i<= MAX; ++i){
    if (!flag[i]){
      primes.push_back(i);
      for (ll j = (ll) i*i; j <= MAX; j += i){
        flag[j] = 1;
      }
    }
  }
}
```  

<br/>

# 4) 조합론 
## 조합 (Combination)
- 파스칼 삼각형 성질 이용하여 계산
``` cpp
#define MAX    	1001
#define DIV			10007

int combi[MAX + 1][MAX + 1];

int main() {
  ... 
	for (int n = 0; n <= N; ++n) {
		combi[n][0] = combi[n][n] = 1;
		for (int k = 1; k < n; ++k) 
      combi[n][k] = (combi[n - 1][k - 1] + combi[n - 1][k]) % DIV;
	}
  ...
}

``` 
