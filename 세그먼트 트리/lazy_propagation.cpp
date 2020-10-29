#include<bits/stdc++.h>
using namespace std;
#define MAX_SIZE 100005

/*
구간의 합을 구하는 세그먼트 트리 & 특정 구간 전체에 더해지는 값이 있을 때의 lazy propagation
물론 단순히 구간의 합을 구할 때 & 하나씩만 바꿀 땐 펜윅 트리가 더 간단하다.
[lazy] 라고 적힌 부분은 일반적인 세그먼트 트리에는 없고 lazy propagation일 때만 있는 코드
*/

int num[MAX_SIZE];
vector<int> rangeSum(MAX_SIZE * 4);

// [lazy] lazy하게 더할 값을 저장하는 공간
vector<int> lazy(MAX_SIZE * 4);

// 세그먼트 트리 초기화
int init(int left, int right, int node) {
    if ( left == right) {
        return rangeSum[node] = num[left];
    } else {
        int mid = (left + right) / 2;
        return rangeSum[node] = init(left, mid, node * 2) + init(mid+1, right, node * 2 + 1);
    }
}

// queryLeft ~ queryRight번(1-based) 구간의 합 구하기
int query(int queryLeft, int queryRight, int node, int nodeLeft, int nodeRight) {

    // [lazy] lazy 값이 있는 node에 도달할 때마다 lazy값을 반영한다.
    if ( lazy[node] != 0) {
        rangeSum[node] += (nodeRight - nodeLeft + 1) * lazy[node];
        if ( nodeLeft != nodeRight) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }

    if ( queryRight < nodeLeft || nodeRight < queryLeft) {
        return 0;
    } else if ( queryLeft <= nodeLeft && nodeRight <= queryRight ) {
        return rangeSum[node];
    } else {
        int nodeMid = (nodeLeft + nodeRight) / 2;
        return query(queryLeft, queryRight, node*2, nodeLeft, nodeMid) + query(queryLeft, queryRight, node*2+1, nodeMid+1, nodeRight);
    }
}

// [lazy] queryLeft ~ queryRight번(1-based) 자리의 모든 값에 addition만큼 더하기
void add(int queryLeft, int queryRight, int node, int nodeLeft, int nodeRight, int addition) {

    // lazy 값이 있는 node에 도달할 때마다 lazy값을 반영한다. query() 부분에 있는 코드와 동일하다.
    if ( lazy[node] != 0) {
        rangeSum[node] += (nodeRight - nodeLeft + 1) * lazy[node];
        if ( nodeLeft != nodeRight) {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }

    // node 구간과 query 구간이 겹치지 않는 경우
    if ( queryRight < nodeLeft || nodeRight < queryLeft) return;

    // node 구간이 query 구간에 완전히 포함되면 값을 갱신하고 더 내려가지 않는다.(아래 node들의 값은 나중에 방문하게 되면 그때 갱신할 거다. 이것이 lazy의 의미)
    if ( queryLeft <= nodeLeft && nodeRight <= queryRight) {
        rangeSum[node] += (nodeRight - nodeLeft + 1) * addition;

        if ( nodeLeft != nodeRight) {
            lazy[node*2] += addition;
            lazy[node*2+1] += addition;
        }
        return;
    }

    // nodeLeft == nodeRight이면 바로 위의 조건문에 걸리므로 걸리므로 확인해 줄 필요는 없다
    int nodeMid = (nodeLeft + nodeRight) / 2;
    add(queryLeft, queryRight, node*2, nodeLeft, nodeMid, addition);
    add(queryLeft, queryRight, node*2+1, nodeMid+1, nodeRight, addition);

    // 중요!
    rangeSum[node] = rangeSum[node*2] + rangeSum[node*2+1];
}

int main() {
    int n, q;
    cin>>n>>q;

    // 초기 값 입력
    for ( int i = 1 ; i <= n ; ++i ) {
        cin>>num[i];
    }

    // 세그먼트 트리 초기화
    init(1, n, 1);

    // 쿼리 처리, 1 -> left ~ right 구간의 모든 숫자에 val만큼 더하기, 2 -> left ~ right 구간 합 출력
    while(q--) {
        int type;
        cin>>type;
        if (type == 1) {
            int left, right, val;
            cin>>left>>right>>val;
            add(left, right, 1, 1, n, val);
        } else {
            int left, right;
            cin>>left>>right;
            cout<<query(left, right, 1, 1, n)<<'\n';
        }
    }
}