#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct dot{
  int x, y;
};

bool operator==(dot d1, dot d2) {
  return d1.x == d2.x && d1.y == d2.y;
}

ll ccw(dot d1, dot d2, dot d3) {
  return (ll)(d2.x - d1.x) * (d3.y - d1.y) - (ll)(d2.y - d1.y) * (d3.x - d1.x);
}

// 기준점: 가장 아래 있는 점들 중 가장 왼쪽에 있는 점
dot standard_point = {INT_MAX, INT_MAX};

// 정렬 함수
// 기준점을 맨 앞에 유지하고, 나머지 점들을 기준점 기준으로 반시계 방향으로 정렬
bool compare(dot a, dot b) {
  // 기준점인 경우
  if (a == standard_point) return true;
  if (b == standard_point) return false;

  // double gradient_a = (a.y - standard_point.y) / (a.x - standard_point.x);
  // double gradient_b = (b.y - standard_point.y) / (b.x - standard_point.x);
  ll gradient_a = (ll)(a.y - standard_point.y) * (b.x - standard_point.x);
  ll gradient_b = (ll)(b.y - standard_point.y) * (a.x - standard_point.x);

  if (gradient_a != gradient_b) {
    return gradient_a < gradient_b;
  }

  // 두 점까지의 기울기가 같은 경우에도 반드시 이렇게 정렬해 주어야 함
  if (a.y != b.y) {
    return a.y < b.y;
  }
  return a.x < b.x;
}

int main() {
  // 점 개수
  int n;
  cin>>n;

  // 점 좌표
  dot dots[n];
  for ( int i = 0 ; i < n ; ++i ) {
    cin>>dots[i].x>>dots[i].y;
    // 기준점 정하기
    if (dots[i].y < standard_point.y || (dots[i].y == standard_point.y && dots[i].x < standard_point.x)) {
      standard_point = dots[i];
    }
  }

  sort(dots, dots + n, compare);

  stack<dot> stk;
  stk.push(dots[0]);
  stk.push(dots[1]);
  for ( int i = 2 ; i < n ; ++i ) {
    dot next = dots[i];

    // 첫 점들이 일직선일 경우 이 조건이 없으면 segmentation fault남
    if (stk.size() < 2) {
      stk.push(next);
      continue;
    }

    dot second = stk.top();
    stk.pop();
    dot first = stk.top();

    ll ccw_result = ccw(first, second, next);
    if (ccw_result > 0 ) {
      // 반시계 방향으로 돌아가면 스택에 넣고 진행
      stk.push(second);
      stk.push(next);
    } else {
      // 시계 방향으로 돌아가면 일단 second 점은 다각형에 포함되지 않음
      --i;
    }
  }

  // stk 안에 다각형들의 점이 순서대로 들어가 있음
  cout<<stk.size();
}