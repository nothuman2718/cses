#include <bits/stdc++.h>
using namespace std;

long long orient(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3) {
    return (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
}

bool onSegment(long long x1,long long y1,long long x2,long long y2,long long x3,long long y3) {
    return min(x1,x2) <= x3 && x3 <= max(x1,x2) &&
           min(y1,y2) <= y3 && y3 <= max(y1,y2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long x1,y1,x2,y2,x3,y3,x4,y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

        long long o1 = orient(x1,y1,x2,y2,x3,y3);
        long long o2 = orient(x1,y1,x2,y2,x4,y4);
        long long o3 = orient(x3,y3,x4,y4,x1,y1);
        long long o4 = orient(x3,y3,x4,y4,x2,y2);

        bool intersect = false;

        // General case
        if ((o1 > 0 && o2 < 0 || o1 < 0 && o2 > 0) &&
            (o3 > 0 && o4 < 0 || o3 < 0 && o4 > 0)) {
            intersect = true;
        }
        // Collinear cases
        else if (o1 == 0 && onSegment(x1,y1,x2,y2,x3,y3)) intersect = true;
        else if (o2 == 0 && onSegment(x1,y1,x2,y2,x4,y4)) intersect = true;
        else if (o3 == 0 && onSegment(x3,y3,x4,y4,x1,y1)) intersect = true;
        else if (o4 == 0 && onSegment(x3,y3,x4,y4,x2,y2)) intersect = true;

        cout << (intersect ? "YES\n" : "NO\n");
    }
}
