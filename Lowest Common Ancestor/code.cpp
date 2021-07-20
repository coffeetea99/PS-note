#include<bits/stdc++.h>
using namespace std;
#define MAX_NODE 100005
#define MAX_POWER 20    // 2^(MAX_POWER - 1)이 MAX_NODE 이상이어야 함

vector<int> edge[MAX_NODE];

// parent[i][j]: i번 노드의 2^j번 위의 부모
int parent[MAX_NODE][MAX_POWER];

int depth[MAX_NODE];

// parent[i][0]만 세팅하는 DFS
void dfs(int cur_node, int cur_depth, int cur_parent) {
    depth[cur_node] = cur_depth;
    for ( int adj: edge[cur_node] ) {
        if (adj != cur_parent) {
            // adj는 자기 자식 노드
            parent[adj][0] = cur_node;
            dfs(adj, cur_depth + 1, cur_node);
        }
    }
}

int main() {
    // root가 1번이라고 가정
    int root = 1;

    // 점의 개수
    int n;
    cin>>n;

    // 간선 n-1개 입력받음
    for ( int i = 1 ; i < n ; ++i ) {
        int a, b;
        cin>>a>>b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }

    // parent[i][0] 세팅
    parent[root][0] = root;
    dfs(root, 0, -1);

    // 나머지 parent 세팅
    for ( int j = 1 ; j < MAX_POWER ; ++j ) {
        int power = pow(2, j);
        for ( int i = 1 ; i <= n ; ++i ) {
            if ( depth[i] < power ) {
                parent[i][j] = root;
            } else {
                // 2^j번 위 == 2^(j-1)번 위의 2^(j-1)번 위
                parent[i][j] = parent[ parent[i][j-1] ][ j-1 ];
            }
        }
    }

    // 쿼리의 개수
    int m;
    cin>>m;
    while(m--) {
        int a, b;
        cin>>a>>b;

        int depth_a = depth[a], depth_b = depth[b];
        // WLOG b가 더 깊은 쪽
        if ( depth_a > depth_b ) {
            swap(a, b);
            swap(depth_a, depth_b);
        }

        // b를 a와 depth가 같을 때까지 끌어올리기
        for ( int depth_diff = depth_b - depth_a, exponent = MAX_POWER - 1, power = pow(2, exponent) ; depth_diff ; --exponent, power >>= 1 ) {
            if ( power <= depth_diff ) {
                depth_diff -= power;
                b = parent[b][exponent];
            }
        }

        if ( a == b ) {
            // a가 b의 조상이었음
            cout<<a<<'\n';
        } else {
            // a와 b를 같은 조상 바로 아래까지 끌어올리기
            for ( int exponent = MAX_POWER - 1, power = pow(2, exponent) ; power ; --exponent, power >>= 1 ) {
                if ( parent[a][exponent] != parent[b][exponent] ) {
                    a = parent[a][exponent];
                    b = parent[b][exponent];
                }
            }
            cout<<parent[a][0]<<'\n';
        }
    }
}