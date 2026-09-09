#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, k;
    cin >> n >> k;
    ll x, a, b, c;
    cin >> x >> a >> b >> c;

    ll cap = k + 1;
    vector<ll> dqIdx(cap), dqVal(cap);
    ll head = 0, cnt = 0;

    auto pushBack = [&](ll idx, ll val){
        ll pos = head + cnt;
        if (pos >= cap) pos -= cap;
        dqIdx[pos] = idx;
        dqVal[pos] = val;
        cnt++;
    };
    auto backVal = [&]() -> ll {
        ll pos = head + cnt - 1;
        if (pos >= cap) pos -= cap;
        return dqVal[pos];
    };
    auto popFront = [&](){ head++; if (head == cap) head = 0; cnt--; };

    ll last = x; // value for the "current" index, advanced each step

    for (ll i = 0; i < k; i++){
        ll val = last;
        while (cnt > 0 && backVal() >= val) cnt--;
        pushBack(i, val);
        last = (a * last + b) % c;
    }

    ll res = dqVal[head];

    for (ll i = k; i < n; i++){
        if (cnt > 0 && dqIdx[head] <= i - k) popFront();

        ll val = last;
        while (cnt > 0 && backVal() >= val) cnt--;
        pushBack(i, val);
        last = (a * last + b) % c;

        res ^= dqVal[head];
    }

    cout << res << '\n';
}
