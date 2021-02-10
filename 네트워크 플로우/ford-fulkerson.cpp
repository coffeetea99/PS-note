#include<bits/stdc++.h>
using namespace std;
#define NODE_COUNT 1005

/*
a -> b 로 가는 간선의 capacity(= 최대 flow)가 7이고, 현재 flow가 4이면 이 간선의 잔여 용량은 3
그런데 이 간선을 b -> a 로 가는 간선으로 보면 capacity는 0이고, 현재 flow가 (-4)이므로 잔여 용량이 4인 것으로 간주할 수 있다

최대 유량을 F라고 했을 때 기본적인 시간복잡도는 O(E * F)
하지만 증가 경로를 BFS로 찾으면 V * E번 이상 찾지 않는다는 것이 증명되어 있으므로 시간복잡도는 O(V * E^2)
*/

// a -> b로 가는 간선의 용량, 현재 유량
int capacity[NODE_COUNT][NODE_COUNT], flow[NODE_COUNT][NODE_COUNT];

int main() {
    // 시작점, 끝점
    int start, finish;
    cin>>start>>finish;

    /* capacity를 입력받는다 */

    int maxFlow = 0;

    // start -> finish로 가는 증가 경로가 더 이상 존재하지 않을 때까지 찾는다
    while(true) {

        // 증가 경로에서 각 노드의 이전 노드
        vector<int> parent(NODE_COUNT, -1);
        parent[start] = start;

        // 증가 경로를 찾는 BFS로 찾음
        queue<int> q;
        q.push(start);
        while(!q.empty() && parent[finish] == -1) {

            // here: 현재 노드
            int here = q.front();
            q.pop();

            // 어떤 노드 next에 대해 here에서 next로 가는 쪽에 용량이 남고, next가 미방문일 때 next를 방문
            for ( int next = 0 ; next < NODE_COUNT ; ++next ) {
                if ( capacity[here][next] - flow[here][next] > 0 && parent[next] == -1 ) {
                    parent[next] = here;
                    q.push(next);
                }
            }
        }

        // 계속 찾아 보았지만 증가 경로가 없다
        if ( parent[finish] == -1 ) {
            break;
        }

        // 증가 경로가 존재한다
        // 이 경로를 통해 증가시킬 유량을 찾는다
        int amount = INT_MAX;
        for ( int p = finish ; p != start ; p = parent[p] ) {
            amount = min(capacity[parent[p]][p] - flow[parent[p]][p], amount);
        }

        // 증가시킬 유량을 정했으니 증가시키자
        for ( int p = finish ; p != start ; p = parent[p] ) {
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }

        // 전체 유량에 더해 주자
        maxFlow += amount;
    }
    cout<<maxFlow;
}