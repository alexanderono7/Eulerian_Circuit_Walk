#include <iostream>
#include <string>

using namespace std;
//string splitting
int main(){
    int a,b;
    string s;

    cout << "\nInput: \n";
    getline(cin, s);

    a = stoi(s.substr(0,s.find_first_of(' ')));
    b = stoi(s.substr(s.find_first_of(' ')+1,s.length()));

    cout << "\n";
    cout << a + b;
    return 0;
}