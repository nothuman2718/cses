#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<long long> tree, lazy;

    SegmentTree(int n) {
        this->n = n;
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    // Build from array
    void build(vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l+r)/2;
        build(arr, node*2, l, mid);
        build(arr, node*2+1, mid+1, r);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    // Push pending updates
    void pushDown(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = (l+r)/2;
            tree[node*2]     += (mid-l+1) * lazy[node];
            tree[node*2+1]   += (r-mid)   * lazy[node];
            lazy[node*2]     += lazy[node];
            lazy[node*2+1]   += lazy[node];
            lazy[node] = 0;
        }
    }

    // Range update: add val to [ql, qr]
    void updateRange(int node, int l, int r, int ql, int qr, int val) {
        if (qr < l || ql > r) return; // no overlap
        if (ql <= l && r <= qr) { // full overlap
            tree[node] += (r-l+1) * val;
            lazy[node] += val;
            return;
        }
        pushDown(node, l, r);
        int mid = (l+r)/2;
        updateRange(node*2, l, mid, ql, qr, val);
        updateRange(node*2+1, mid+1, r, ql, qr, val);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    // Point update: set arr[idx] = val
    void updatePoint(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        pushDown(node, l, r);
        int mid = (l+r)/2;
        if (idx <= mid) updatePoint(node*2, l, mid, idx, val);
        else updatePoint(node*2+1, mid+1, r, idx, val);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    // Range query: sum in [ql, qr]
    long long queryRange(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return 0; // no overlap
        if (ql <= l && r <= qr) return tree[node]; // full overlap
        pushDown(node, l, r);
        int mid = (l+r)/2;
        return queryRange(node*2, l, mid, ql, qr) +
               queryRange(node*2+1, mid+1, r, ql, qr);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 8;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};

    SegmentTree st(n);
    st.build(arr, 1, 0, n-1);

    cout << "Sum [0,7] = " << st.queryRange(1, 0, n-1, 0, 7) << "\n"; // 36

    st.updateRange(1, 0, n-1, 2, 5, 10); // add +10 to [2..5]
    cout << "Sum [0,7] after range update = "
         << st.queryRange(1, 0, n-1, 0, 7) << "\n"; // 76

    st.updatePoint(1, 0, n-1, 4, 100); // set arr[4] = 100
    cout << "Sum [0,7] after point update = "
         << st.queryRange(1, 0, n-1, 0, 7) << "\n";

    cout << "Sum [3,6] = " << st.queryRange(1, 0, n-1, 3, 6) << "\n";

    return 0;
}
