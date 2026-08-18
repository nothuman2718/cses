#include<bits/stdc++.h>
using namespace std;

struct Node{
    bool isEnd;
    int child[26];

    Node(){
        for(int i=0;i<26;i++){
            child[i]=-1;
        }
        isEnd=false;
    }
};

vector<Node> trie(1);

void insertWord(string str){
    int cur=0;

    for(char c: str){
        int idx = c-'a';
        if(trie[cur].child[idx]==-1){
            trie[cur].child[idx]=strie.size();
            trie.push_back(Node());
        }
        cur = trie[cur].child[idx];
    }
    trie[cur].isEnd=true;
}

bool search(string str){
    int cur=0;

    for(char c: str){
        int idx = c - 'a';
        if(trie[cur].child[idx]==1) return false;
        cur = trie[cur].child[idx];
    }

    return trie[cur].isEnd;
}


int main(){

    insertWord("apple");
    insertWord("app");
    insertWord("bannana");


    cout << search("apple");
    cout << search("appl`");
    cout << search("app");

    return 0;
}