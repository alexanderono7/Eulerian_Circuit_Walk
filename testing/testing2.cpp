#include <iostream>

using namespace std;

/* 
Input to dynamically allocate memory (DAM) for a 1-dimensional array, size based on user input.
Then, dynamically delete memory for array.
*/
int main()
{
    int x;
    cin >> x;
    int *foo;
    foo = new int[x];
    for (int i = 0; i < x; i++)
    {
        foo[i] = i;
    }
    for (int i = 0; i < x; i++)
    {
        cout << foo[i];
    }
    delete[] foo;
    return 0;
}