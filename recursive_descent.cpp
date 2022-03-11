#include <bits/stdc++.h>
using namespace std;

string s;
int l;

bool A();
bool B();
bool C();


bool A() {
    if( l < s.size() and s[l] == 'a') {
        l++;
        return B();
    }
    return false;
}


bool B() {
    if(l < s.size() and s[l] == '+') {
        l++;
        if( C() and B() ) return true;
    }
    else if(l < s.size() and s[l] == 'e') {
        l++;
        return true;
    }
    return false;
}


bool C() {
    bool one = A();
    if(s[l] == '/') {
        l++;
        bool two = A();
        if(one and two) return true;
    }
    return false;
}



int main()
{   
    // look ahead
    l = 0;
    
    cout << "Enter the string : (without putting '$' at the end of the string)\n";
    cin >> s; 
    
    // if(s.back() != '$')
    //     s.push_back('$');
    
    bool ans = A();
    
    if(ans)
        cout <<"\nit is Recursive descent parsable";
    else 
        cout <<"\nit is not Recursive descent parsable";
        
    
    return 0;
}