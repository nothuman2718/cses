#include <bits/stdc++.h>
using namespace std;

#define pii pair<int, int>
#define vi vector<int>

#define f(i,s,e) for(long long int i=s;i<e;i++)

int main()
{
    int n;
    cin >> n;

    vi pruferCode(n - 2);
    vi degree(n, 1);

    // Calculate degrees
    f(i, 0, n - 2) {
        cin >> pruferCode[i];
        degree[pruferCode[i] - 1]++;
    }

    // Min heap: {degree, vertex}
    priority_queue<
        pii,
        vector<pii>,
        greater<pii>
    > pq;

    // Add all initial leaves
    f(i, 0, n) {
        if (degree[i] == 1)
            pq.push({degree[i], i + 1});
    }

    vector<pii> ans;

    // Reconstruct edges
    for (int x : pruferCode) {

        // Get smallest leaf
        pii top = pq.top();
        pq.pop();

        int leaf = top.second;

        // Add edge leaf -> x
        ans.push_back({leaf, x});

        // Remove leaf
        degree[leaf - 1]--;

        // x loses one occurrence from Prufer code
        degree[x - 1]--;

        // If x becomes a leaf, add it
        if (degree[x - 1] == 1) {
            pq.push({1, x});
        }
    }

    // Two vertices remain
    pii a = pq.top();
    pq.pop();

    pii b = pq.top();
    pq.pop();

    ans.push_back({a.second, b.second});

    // Print edges
    for (auto [u, v] : ans) {
        cout << u << " " << v << "\n";
    }
}