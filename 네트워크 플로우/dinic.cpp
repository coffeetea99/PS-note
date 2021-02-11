#include<bits/stdc++.h>
using namespace std;
#define NODE_COUNT 1005

/*
레벨 그래프: 모든 노드에 대해 시작점으로부터의 최단 거리(거쳐야 하는 간선의 수)를 레벨 값으로 부여한 그래프
이때 용량이 꽉 차서 거쳐갈 수 없는 간선은 고려하지 않는다

차단 유량: 레벨 그래프에서, 항상 자신보다 레벨이 1 높은 노드로만 흘러갈 수 있을 때의 최대 유량
레벨의 정의상, 유량은 최단 거리로만 흘러가게 된다

1. BFS로 레벨 그래프를 만든다
2. DFS로 한 줄짜리 최단 거리 증가 경로를 찾고, 그 경로로 최대한 많은 유량을 보낸다. 이때 그 경로에 속한 최소한 1개의 간선은 포화된다.
3. (2)를 반복한다.
4. (3)에서 더 흘려보낼 수 없으면 차단 유량에 도달한 것이다. 다시 (1)로 돌아간다.
5. 레벨 그래프를 만들었을 때 도착점까지 레벨이 도달하지 못하면 종료한다.

하나의 레벨 그래프에서 최단 거리 증가 경로 하나를 처리할 때마다 간선이 1개씩 포화되어 삭제되므로 O(E)번 경로를 찾을 수 있다.
하나의 증가 경로의 길이는 노드의 개수보다 클 수 없으므로 증가 경로 하나를 처리하는 데 O(V)의 시간이 걸린다
따라서 하나의 레벨 그래프에서 시간복잡도는 O(V * E)

이렇게 레벨 그래프를 만드는 것을 O(V)번 할 수 있다.
하나의 레벨 그래프에서 최단 거리가 k라면, 그 다음 레벨 그래프에서는 최단 거리가 k+1이 된다.
그런데 최단 거리는 V를 넘을 수 없기 때문이다.

따라서 전체 시간복잡도는  O(V^2 * E)
*/

// 코드 전체에 걸쳐 사용하는 값

// 시작 노드, 끝 노드
int start, finish;
// a -> b로 가는 간선의 용량, 현재 유량
int capacity[NODE_COUNT][NODE_COUNT], flow[NODE_COUNT][NODE_COUNT];
// 각 노드와 인접한 노드의 벡터
vector<int> adjacent[NODE_COUNT];

// 한 차례 레벨 그래프를 생성할 때마다 초기화되는 값

// 각 노드의 레벨
int level[NODE_COUNT];
// 어떤 노드에 대해, 몇 번째 인접 노드까지 탐색했는가를 기록한 값
// 여기서 '몇 번째'라는 것은 위의 adjacent 벡터 기준이다
int record[NODE_COUNT];

bool bfs();
int dfs(int current, int start_flow);

int main() {
    cin>>start>>finish;

    /* TODO: capacity를 입력받는다 */

    /* TODO: adjacent를 세팅한다 */

    int max_flow = 0;

    // 레벨 그래프를 만든다
    while(bfs()) {
        memset(record, 0, sizeof(record));

        while(true) {
            // start -> finish로 가는 한 줄짜리 최단 거리 증가 경로를 아무거나 찾고, 그 증가 경로에서 흘려보낼 수 있는 최대 유량을 구한다
            int add_flow = dfs(start, INT_MAX);

            // 더 흘려보낼 수 없으면 종료
            if (add_flow == 0) break;

            max_flow += add_flow;
        }
    }

    cout<<max_flow;
}

// 레벨 그래프를 만든다
bool bfs() {
    queue<int> q;
    memset(level, -1, sizeof(level));

    level[start] = 0;
    q.push(start);

    while(!q.empty()) {
        int current = q.front();
        q.pop();

        for ( int next : adjacent[current] ) {
            if ( level[next] == -1 && capacity[current][next] - flow[current][next] > 0 ) {
                level[next] = level[current] + 1;
                q.push(next);
            }
        }
    }

    return level[finish] != -1;
}

// start -> current까지 한 줄로 start_flow만큼 흘러왔다면, current -> finish까지 한 줄의 최단 경로로 얼마나 보낼 수 있는지를 계산한다.
int dfs(int current, int start_flow) {
    // 마지막 노드에 도달했다
    if ( current == finish ) {
        return start_flow;
    }

    for ( int& index = record[current] ; index < adjacent[current].size() ; ++index ) {
        int next = adjacent[current][index];

        int left_capacity = capacity[current][next] - flow[current][next];
        if ( level[next] - level[current] == 1 && left_capacity > 0 ) {
            int end_flow = dfs(next, min(start_flow, left_capacity));

            // finish까지의 경로를 찾았다. 이 경로로는 최대 end_flow만큼 보낼 수 있는 모양이다.
            if ( end_flow > 0 ) {
                flow[current][next] += end_flow;
                flow[next][current] -= end_flow;

                return end_flow;
            }
        }
    }
    return 0;
}