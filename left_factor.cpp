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
    sort(m[s[0]].begin(),m[s[0]].end());
} 

int compare_string(string &a,string&b) {
    int i = 0;

    for(; i < min(a.size(),b.size()); i++)
        if(a[i] != b[i])
            break;
    
    return i;
}

int main()
{
    int n;
    cout << "ENTER NUMBER OF PRODUCTIONS : ";
    cin >> n;
    cout << "\nEnter the production in following manner : A->Aa|Ab (no spaces)\n";

    /*
    example 1:
        S->iEtS / iEtSeS / a
        E->b

     answer
       S->iEtST|a
       T->$|eS
       E->b

     example 2:
        S->aa|aaAB|aaAd|bA|bca|db
   
    answer
        V->B|d
        U->A|ca
        T->$|AV
        S->aaT|bU|db
        
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

    // print_map(m);

    queue<char> q;
    for(auto& i : m)
        q.push(i.first);


  
    while(!q.empty()) {
        char c = q.front(); q.pop();
        int prefix = INT_MAX;
        int last = 0;
        vector<string> ov;
        for(int i = 1 ; i <= m[c].size() ; i++) {
            int common=0;
            if(i < m[c].size())
                common=compare_string(m[c][i],m[c][i-1]);

            if(common == 0 || i == m[c].size()) {
                
                if(last+1 == i) {
                    ov.push_back(m[c][last]);
                    last = i;
                }
                else {
                    char next = next_char();
                    vector<string> nv;
                    for(int j = last ; j < i ; j++) {
                        nv.push_back(m[c][j].substr(prefix) == "" ? "$" : m[c][j].substr(prefix));
                    }
                    // m[c].push_back(m[c][last].substr(0,prefix));

                    ov.push_back(m[c][last].substr(0,prefix)+next);

                    sort(nv.begin(),nv.end());
                    m[next] = nv;
                    q.push(next);
                    last = i;
                    prefix = INT_MAX;
                }
            } else {
                prefix = min(prefix,common);
            }
        }
        sort(ov.begin(),ov.end());
        m[c] = ov;
    }

    
    cout << "__________________________________________________";
    cout << "\nProductions after removing left factoring - \n";
    print_map(m);

    return 0;
}