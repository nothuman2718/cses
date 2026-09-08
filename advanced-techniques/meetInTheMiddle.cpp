#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll x;
    cin >> n >> x;

    vector<ll> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int l = n / 2;
    int r = n - l;

    vector<ll> leftSums(1LL << l);
    vector<ll> rightSums(1LL << r);

    // Generate left subset sums
    for (int mask = 1; mask < (1 << l); mask++) {
        int bit = __builtin_ctz(mask);
        int prev = mask & (mask - 1);

        leftSums[mask] = leftSums[prev] + a[bit];
    }

    // Generate right subset sums
    for (int mask = 1; mask < (1 << r); mask++) {
        int bit = __builtin_ctz(mask);
        int prev = mask & (mask - 1);

        rightSums[mask] = rightSums[prev] + a[l + bit];
    }

    sort(leftSums.begin(), leftSums.end());
    sort(rightSums.begin(), rightSums.end());

    ll ans = 0;

    // For every left sum, find how many right sums
    // equal x - leftSum.
    for (ll sum : leftSums) {
        ll need = x - sum;

        auto low = lower_bound(rightSums.begin(), rightSums.end(), need);
        auto high = upper_bound(rightSums.begin(), rightSums.end(), need);

        ans += high - low;
    }

    cout << ans << '\n';

    return 0;
}