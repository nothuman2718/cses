#include <bits/stdc++.h>
using namespace std;

/* TYPES */
#define ll long long
#define vi vector<int>
#define f(i,s,e) for(int i=s;i<e;i++)

/* DFS function */
int dfs(int node, vi &subordinates, vi adjList[]) {
    int size = 1;
    for (int child : adjList[node]) {
        size += dfs(child, subordinates, adjList);
    }
    subordinates[node] = size;
    return size;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vi adjList[n];
    vi subordinates(n, 0);

    for (int i = 1; i < n; i++) {
        int boss;
        cin >> boss;
        adjList[boss - 1].push_back(i); // child of boss
    }

    dfs(0, subordinates, adjList);

    for (int i = 0; i < n; i++) {
        cout << subordinates[i] - 1 << " ";
    }
    cout << "\n";
}
