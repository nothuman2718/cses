#include <bits/stdc++.h>
using namespace std;

/* clang-format on */
int kmp(string n, string m){

    vector<int> lps(m.size(),0);
    int count = 0;

    int prevLPS=0;
    int i=1;
    
    while(i< m.size()){
        if(m[prevLPS]==m[i]){
            lps[i]=prevLPS+1;
            i+=1;
            prevLPS+=1;
        }else if(prevLPS==0){
            lps[i]=0;
            i+=1;
        }else{
            prevLPS=lps[prevLPS-1];
        }
    }

    i=0;
    int j=0;

    while(i<n.size()){
        if(n[i]==m[j]){
            i++;
            j++;
        }else{
            if(j==0){
                i++;
            }else{
                j=lps[j-1];
            }
        }
        if(j==m.size()){
            count++;
            j=lps[j-1];
        }
    }

    return count;
}
