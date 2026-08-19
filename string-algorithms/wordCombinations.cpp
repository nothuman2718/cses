#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct Node {
    bool isEnd;
    int child[26];

    Node() {
        isEnd = false;

        for (int i = 0; i < 26; i++) {
            child[i] = -1;
        }
    }
};

vector<Node> trie(1);

void insertWord(string str) {
    int cur = 0;

    for (char c : str) {
        int idx = c - 'a';

        if (trie[cur].child[idx] == -1) {
            trie[cur].child[idx] = trie.size();
            trie.push_back(Node());
        }

        cur = trie[cur].child[idx];
    }

    trie[cur].isEnd = true;
}

int main() {

    string main;
    cin >> main;

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
        string str;
        cin >> str;

        insertWord(str);
    }

    int n = main.size();

    // dp[i] = number of ways to construct main[0 ... i-1]
    vector<int> dp(n + 1, 0);

    dp[0] = 1;

    for (int i = 0; i < n; i++) {

        if (dp[i] == 0)
            continue;

        int node = 0;

        for (int j = i; j < n; j++) {

            int x = main[j] - 'a';

            // No dictionary word can continue from here
            if (trie[node].child[x] == -1)
                break;

            // Move to the node representing main[i ... j]
            node = trie[node].child[x];

            // main[i ... j] is a dictionary word
            if (trie[node].isEnd) {
                dp[j + 1] += dp[i];

                if (dp[j + 1] >= MOD)
                    dp[j + 1] -= MOD;
            }
        }
    }

    cout << dp[n] << '\n';

    return 0;
}