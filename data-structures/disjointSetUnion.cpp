#include <bits/stdc++.h>
using namespace std;


// ============================================================
//                    DISJOINT SET UNION (DSU)
// ============================================================


// ------------------------------------------------------------
// Find with Path Compression
// ------------------------------------------------------------

int find(int x, vector<int>& parent) {

    // x is the representative of its set
    if (parent[x] == x)
        return x;

    // Path compression
    return parent[x] = find(parent[x], parent);
}


// ------------------------------------------------------------
// Union By Rank
// ------------------------------------------------------------

void unionByRank(
    int a,
    int b,
    vector<int>& parent,
    vector<int>& rank
) {
    int par_A = find(a, parent);
    int par_B = find(b, parent);

    // Already in the same set
    if (par_A == par_B)
        return;

    // Attach smaller-rank tree below larger-rank tree
    if (rank[par_A] < rank[par_B]) {

        parent[par_A] = par_B;

    }
    else if (rank[par_B] < rank[par_A]) {

        parent[par_B] = par_A;

    }
    else {

        // Same rank → choose one as parent
        parent[par_A] = par_B;

        // Height increases by 1
        rank[par_B]++;
    }
}


// ------------------------------------------------------------
// Union By Size
// ------------------------------------------------------------

void unionBySize(
    int a,
    int b,
    vector<int>& parent,
    vector<int>& size
) {
    int par_A = find(a, parent);
    int par_B = find(b, parent);

    // Already in the same set
    if (par_A == par_B)
        return;

    // Make par_A the larger component
    if (size[par_A] < size[par_B]) {
        swap(par_A, par_B);
    }

    // Attach smaller component to larger component
    parent[par_B] = par_A;

    // Update size
    size[par_A] += size[par_B];
}


// ============================================================
//                         MAIN
// ============================================================

int main() {

    int n;
    cin >> n;

    vector<int> parent(n);
    vector<int> rank(n);
    vector<int> size(n);


    // --------------------------------------------------------
    // Initialization
    // --------------------------------------------------------

    for (int i = 0; i < n; i++) {

        parent[i] = i;
        rank[i] = 1;
        size[i] = 1;
    }


    // --------------------------------------------------------
    // Example
    // --------------------------------------------------------

    unionBySize(0, 1, parent, size);
    unionBySize(1, 2, parent, size);

    cout << find(2, parent) << '\n';


    return 0;
}