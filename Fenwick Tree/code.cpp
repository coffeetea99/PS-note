#include<iostream>
#include<vector>
using namespace std;

#define MAX_LENGTH 100005   // 1-based 이므로 딱 100000이면 에러가 날 수 있음

vector<int> tree(MAX_LENGTH);

// 1 ~ pos번(1-based)까지의 합을 구함
int sum(int pos) {
    int ret = 0;
    while(pos > 0) {
        ret += tree[pos];
        pos &= (pos-1);
    }
    return ret;
}

// pos번(1-based) 자리에 val만큼 더하기
void add(int pos, int val) {
    while(pos < tree.size() ) {
        tree[pos] += val;
        pos += (pos & -pos);
    }
}

int main() {
    int n, q;
    cin>>n>>q;

    // 초기 값 입력
    for ( int i = 1 ; i <= n ; ++i ) {
        int temp;
        cin>>temp;
        add(i, temp);
    }

    // 쿼리 처리, 1->숫자 하나 갱신, 2->구간 합 출력
    while(q--) {
        int query;
        cin>>query;
        if ( query == 1 ) {
            int pos, val;
            cin>>pos>>val;
            add(pos, val);
        } else {
            int left, right;
            cin>>left>>right;
            cout<<sum(right) - sum(left-1)<<'\n';
        }
    }
}