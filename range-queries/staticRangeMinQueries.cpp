#include <bits/stdc++.h>
using namespace std;

/* clang-format off */

/* TYPES  */
#define ll long long
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long>
#define mii map<int, int>
#define si set<int>
#define sc set<char>
#define sll set<long long>
#define usi unordered_set<int>
#define usc unordered_set<char>
#define usll unordered_set<long long>

/* FUNCTIONS */
#define f(i,s,e) for(long long int i=s;i<e;i++)
#define cf(i,s,e) for(long long int i=s;i<=e;i++)
#define rf(i,e,s) for(long long int i=e-1;i>=s;i--)
#define pb push_back
#define eb emplace_back

/* PRINTS */
template <class T>
void print_v(vector<T> &v) { cout << "{"; for (auto x : v) cout << x << ","; cout << "\b}"; }

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define read(type) readInt<type>()
ll min(ll a,int b) { if (a<b) return a; return b; }
ll min(int a,ll b) { if (a<b) return a; return b; }
ll max(ll a,int b) { if (a>b) return a; return b; }
ll max(int a,ll b) { if (a>b) return a; return b; }
ll gcd(ll a,ll b) { if (b==0) return a; return gcd(b, a%b); }
ll lcm(ll a,ll b) { return a/gcd(a,b)*b; }
string to_upper(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='a' && a[i]<='z') a[i]-='a'-'A'; return a; }
string to_lower(string a) { for (int i=0;i<(int)a.size();++i) if (a[i]>='A' && a[i]<='Z') a[i]+='a'-'A'; return a; }
bool prime(ll a) { if (a==1) return 0; for (int i=2;i<=round(sqrt(a));++i) if (a%i==0) return 0; return 1; }
void yes() { cout<<"YES\n"; }
void no() { cout<<"NO\n"; }

/*  All Required define Pre-Processors and typedef Constants */
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;

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
        tree[node] = min(tree[node*2], tree[node*2+1]);
    }

    // Push pending updates
    void pushDown(int node, int l, int r) {
        if (lazy[node] != 0) {
            int mid = (l+r)/2;
            // Apply to children
            tree[node*2]   += lazy[node];
            tree[node*2+1] += lazy[node];
            lazy[node*2]   += lazy[node];
            lazy[node*2+1] += lazy[node];
            lazy[node] = 0;
        }
    }

    // Range update: add val to [ql, qr]
    void updateRange(int node, int l, int r, int ql, int qr, int val) {
        if (qr < l || ql > r) return; // no overlap
        if (ql <= l && r <= qr) { // full overlap
            tree[node] += val;
            lazy[node] += val;
            return;
        }
        pushDown(node, l, r);
        int mid = (l+r)/2;
        updateRange(node*2, l, mid, ql, qr, val);
        updateRange(node*2+1, mid+1, r, ql, qr, val);
        tree[node] = min(tree[node*2], tree[node*2+1]);
    }

    // Point update: set arr[idx] = val
    void updatePoint(int node, int l, int r, int idx, int val) {
        if (l == r) {
            tree[node] = val;
            lazy[node] = 0;
            return;
        }
        pushDown(node, l, r);
        int mid = (l+r)/2;
        if (idx <= mid) updatePoint(node*2, l, mid, idx, val);
        else updatePoint(node*2+1, mid+1, r, idx, val);
        tree[node] = min(tree[node*2], tree[node*2+1]);
    }

    // Range query: min in [ql, qr]
    long long queryRange(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return LLONG_MAX; // no overlap
        if (ql <= l && r <= qr) return tree[node]; // full overlap
        pushDown(node, l, r);
        int mid = (l+r)/2;
        return min(queryRange(node*2, l, mid, ql, qr),
                   queryRange(node*2+1, mid+1, r, ql, qr));
    }
};



int main() {

    int n, q;
    cin >> n >> q;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    SegmentTree tree(n);
    tree.build(arr,1,0,n-1);

    while (q--) {
        int a, b;
        cin >> a >> b;
        
        cout << tree.queryRange(1,0,n-1,a-1,b-1)<< '\n';
    }

    return 0;
}