#include<iostream>
#include<vector>
using namespace std;

/*
구간의 합을 구하는 세그먼트 트리
물론 단순히 구간의 합을 구할 때 & 하나씩만 바꿀 땐 펜윅 트리가 더 간단하다.
[min]이라고 적힌 주석은, 구간 합이 아니라 구간의 최솟값을 반환하는 트리일 경우의 코드이다
*/

#define MAX_SIZE 100005 // 1-based 이므로 딱 100000이면 에러가 날 수 있음

int num[MAX_SIZE];  // 초기 숫자
vector<int> rangeSum(MAX_SIZE * 4); // 세그먼트 트리. 적어도 [(숫자 개수보다 큰 2의 거듭제곱 중 가장 작은 수) * 2]만큼의 크기여야 한다. 따라서 크기가 [(숫자 개수) * 4]이면 항상 가능하다.

// 세그먼트 트리 초기화
int init(int left, int right, int node) {
    if ( left == right) {
        return rangeSum[node] = num[left];
    } else {
        int mid = (left + right) / 2;
        return rangeSum[node] = init(left, mid, node * 2) + init(mid+1, right, node * 2 + 1);
        // [min] rangeSum[node] = min(init(left, mid, node * 2), init(mid+1, right, node * 2 + 1));
    }
}

// queryLeft ~ queryRight번(1-based) 구간의 합 구하기
int query(int queryLeft, int queryRight, int node, int nodeLeft, int nodeRight) {
    if ( queryRight < nodeLeft || nodeRight < queryLeft) {
        return 0;
        // [min] return INT_MAX;
    } else if ( queryLeft <= nodeLeft && nodeRight <= queryRight ) {
        return rangeSum[node];
    } else {
        int nodeMid = (nodeLeft + nodeRight) / 2;
        return query(queryLeft, queryRight, node*2, nodeLeft, nodeMid) + query(queryLeft, queryRight, node*2+1, nodeMid+1, nodeRight);
        // [min] min(query(queryLeft, queryRight, node*2, nodeLeft, nodeMid), query(queryLeft, queryRight, node*2+1, nodeMid+1, nodeRight));
    }
}

// position번(1-based) 자리에 addition만큼 더하기
void add(int position, int node, int nodeLeft, int nodeRight, int addition) {
    if ( nodeLeft <= position && position <= nodeRight ) {
        rangeSum[node] += addition;
        if ( nodeLeft != nodeRight ) {
            int nodeMid = (nodeLeft + nodeRight) / 2;
            add(position, node*2, nodeLeft, nodeMid, addition);
            add(position, node*2+1, nodeMid+1, nodeRight, addition);
            // [min] rangeSum[node] = min(rangeSum[node*2], rangeSum[node*2+1],);
        }
        // [min] else { rangeSum[node] = addition) };
    }
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

    // 쿼리 처리, 1 -> pos번 숫자를 val만큼 더하기, 2 -> left ~ right 구간 합 출력
    while(q--) {
        int type;
        cin>>type;
        if (type == 1) {
            int pos, val;
            cin>>pos>>val;
            add(pos, 1, 1, n, val);
            // num[pos] += val; (필요 없음)
        } else {
            int left, right;
            cin>>left>>right;
            cout<<query(left, right, 1, 1, n)<<'\n';
        }
    }
}