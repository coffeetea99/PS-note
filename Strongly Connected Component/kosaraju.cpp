#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
using namespace std;
#define pii pair<int, int>
#define MAX_NODE 10005

/*
(순)방향 그래프와, 그 그래프의 모든 간선들의 방향을 뒤집은 역방향 그래프를 만든다.
순방향 그래프에서 점을 잡아 DFS로 탐색하면서, 탐색이 끝나는 순서대로 stack에 집어넣는다.
stack에서 가장 윗 점을 빼고, 그 점을 기점으로 역방향 그래프를 DFS한다. 한 번 수행에 탐색되는 모든 정점들이 하나의 SCC로 묶인다.
*/

// 순방향 그래프와 역방향 그래프
vector<int> forward_road[MAX_NODE], backward_road[MAX_NODE];
// 각 그래프를 탐색했는지
bool forward_visited[MAX_NODE], backward_visited[MAX_NODE];

// DFS 탐색 종료 순으로 넣을 스택
stack<int> stk;
// SCC 목록
vector<int> scc[MAX_NODE];

// 순방향 DFS
void forward_dfs(int node) {
  forward_visited[node] = true;
  for ( int next: forward_road[node] ) {
    if (!forward_visited[next]) {
      forward_dfs(next);
    }
  }
  stk.push(node);
}

// 역방향 DFS
void backward_dfs(int node, int scc_index) {
  backward_visited[node] = true;
  scc[scc_index].push_back(node);
  for ( int next: backward_road[node] ) {
    if (!backward_visited[next]) {
      backward_dfs(next, scc_index);
    }
  }
}

int main() {
  // 정점, 간선 개수
  int v, e;
  cin>>v>>e;
  while(e--) {
    int a, b;
    cin>>a>>b;
    forward_road[a].push_back(b);
    backward_road[b].push_back(a);
  }

  // 순방향 DFS
  for ( int i = 1 ; i <= v ; ++i ) {
    if (!forward_visited[i]) {
      forward_dfs(i);
    }
  }

  // 역방향 DFS
  int scc_index = 0;
  while(!stk.empty()) {
    int top = stk.top();
    stk.pop();
    if (!backward_visited[top]) {
      backward_dfs(top, scc_index);
      ++scc_index;
    }
  }

  // scc에 이제 다 들어가 있음
}