#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll recursive(ll n){
    if(n==0 || n==1) return n;
    ll bits = 64 - __builtin_clzll((unsigned long long)n); // 3 // bit-length of n
    ll pw = 1LL << (bits-1);                           // 4     // largest power of two <= n
    ll cnt = n - pw;                                   // 4  // count of numbers with this bit-length
    return recursive(cnt) + cnt + 1 + (pw)*(bits-1)/2; // 
}

int main(){
    ll n;
    cin >> n;
    cout << recursive(n) << "\n";
}