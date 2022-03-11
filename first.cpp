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

void parse_string(string &s,unordered_map<char,vector<string>>& m,vector<char>& order) {
    int i = 0;
    // string temp = "";
    
    // // removing all the spaces.
    // for(int j = 0 ; j < s.size() ; j++) {
    //     if(s[j] != ' ')
    //         temp += s[j];
    // }
    // s = temp;
    // skip all charcters before ->
    
    order.push_back(s[0]);
    
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



int main()
{
    int n;
    cout << "ENTER NUMBER OF PRODUCTIONS : ";
    cin >> n;
    cout << "\nEnter the production in following manner : A->Aa|ba (no spaces)\n";
    
    vector<char> order;
    
    unordered_map<char, vector<string>> m;
    while (n--) {
        string s;
        cin >> s;
    
        for(int i : s) {
            if(i >= 'A' and i <= 'Z')
                mx_char = max(mx_char,i);
        }
        
        parse_string(s,m,order);
    }
    /*
    example : 

A->aBC|Dd
B->eF|CD
C->gh|#
D->i|#
F->h
    
    */
    
    
    // print_map(m);
    unordered_map<char,set<char>> ans;
    
    for(int i = order.size()-1 ; i >= 0 ; i--) {
        
        char cur = order[i];
        queue<string> q;
        for(string& j : m[cur]) {
            
            q.push(j);
            
            while(!q.empty()) {
                
                string s = q.front(); q.pop();
                
                if(s.size() == 0) continue;
                
                if(s.size() > 1 and s[0] == '#') {
                    s = s.substr(1);
                }
                
                // terminal
                if( (s[0] >= 'a' and s[0] <= 'z') || (s.size() == 1 and s[0] == '#') ) {
                    ans[cur].insert(s[0]);
                }
                
                // non-terminal
                else if(s[0] >= 'A' and s[0] <= 'Z') {
                    for(char c : ans[s[0]]) {
                        q.push(c + s.substr(1));
                    }
                }
            }
        }
        
    }
    cout << "\n__________________________________________\n";
    cout << "FIRST : \n\n";
    for(char c : order) {
        cout << c << "->";
        for(auto& j : ans[c]) {
            cout << j << ",";
        }
        cout << endl;
    }
    // print_map(ans);


    return 0;
}

