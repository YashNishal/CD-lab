#include <bits/stdc++.h>
using namespace std;
int mx_char;

char next_char() {
    mx_char++;
    return mx_char;
}

void print_map(unordered_map<char,vector<string>>& m) {
    for(auto &i : m){
            cout << i.first << "->";
            for(int j = 0 ; j < i.second.size() ; j++) {
                cout << i.second[j];
                if(j != i.second.size() -1)
                    cout << "|";
            }
            cout << "\n";
        }
}

void parse_string(string &s,unordered_map<char,vector<string>>& m) {
    int i = 0;
    // string temp = "";
    
    // // removing all the spaces.
    // for(int j = 0 ; j < s.size() ; j++) {
    //     if(s[j] != ' ')
    //         temp += s[j];
    // }
    // s = temp;
    // skip all charcters before ->
    while(s[i] != '>') i++;
    i++;

    string str;
    for(;i < s.size();i++) {
        if(s[i] == '|') {
            m[s[0]].push_back(str);
            str = "";
        }
        else 
            str.push_back(s[i]);
    }
    m[s[0]].push_back(str);
} 

void remove_lr(char c,vector<string>& arr,unordered_map<char,vector<string>>& ans) {
    
    int idx = 0;
    for(; idx < arr.size() ; idx++)
        if(arr[idx][0] == c) 
            break;

    if(idx == arr.size()) {
        ans[c] = arr;
        return;
    }

    vector<string> nv,nv2;
    char next = next_char();

    for(int i = 0 ; i < arr.size() ; i++) {
        if(idx == i) continue;
        nv.push_back(arr[i]+next);
    }

    ans[c] = nv;
    ans[next].push_back(arr[idx].substr(1) + next);
    ans[next].push_back("epsilon");
}

int main()
{
    int n;
    cout << "ENTER NUMBER OF PRODUCTIONS : ";
    cin >> n;
    cout << "\nEnter the production in following manner : A->Aa|ba (no spaces)\nmake sure that the production is deterministic\n\n";

    /*
    example 1:
        S->SB|c|d
        B->a|b

     answer
        S->cT|dT
        T->BT|epsilon 
        B->a|b

     example 2:
        E->E+T|T
        T->TxF|F 
        F->id
   
    answer
        V->+TV|epsilon
        F->id
        U->xFU|epsilon
        T->FU
        E->TV
    */ 

    unordered_map<char, vector<string>> m;
    while (n--) {
        string s;
        cin >> s;

        for(int i : s) {
            if(i >= 'A' and i <= 'Z')
                mx_char = max(mx_char,i);
        }
        
        parse_string(s,m);
    }

    // print_map(m);
    unordered_map<char,vector<string>> ans;



    // assuming grammar is deterministic
    for(auto& i : m) {
        remove_lr(i.first,i.second,ans);        
    }
    cout << "__________________________________________________";
    cout << "\nProductions after removing left recursion - \n";
    print_map(ans);


    return 0;
}