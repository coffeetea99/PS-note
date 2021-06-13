/*
ret > 0: 반시계
ret = 0: 일직선
ret < 0: 시계
*/

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}
