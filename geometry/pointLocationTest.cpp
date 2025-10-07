#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        long long x1,y1,x2,y2,x3,y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        long long dx21 = x2 - x1;
        long long dy21 = y2 - y1;
        long long dx31 = x3 - x1;
        long long dy31 = y3 - y1;
        long long cross = dx21 * dy31 - dy21 * dx31;
        if (cross > 0) cout << "LEFT\n";
        else if (cross < 0) cout << "RIGHT\n";
        else cout << "TOUCH\n";
    }
    return 0;
}
