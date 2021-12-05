#include <iostream>
 
// `M × N` matrix
 
void printArray(int** A, int M, int N);

// Dynamic Memory Allocation in C++ for 2D Array
using namespace std;
int main()
{
    int n,m;
    cout << "input M:";
    cin >> n;
    cout << "input N:";
    cin >> m;
    // dynamically create an array of pointers of size `M`
    int** A = new int*[n];
 
    // dynamically allocate memory of size `N` for each row
    for (int i = 0; i < n; i++) {
        A[i] = new int[m];
    }
 
    // assign values to the allocated memory
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            A[i][j] = rand() % 100;
        }
    }
 
    // print the 2D array
    printArray(A, n, m);
 
    // deallocate memory using the delete operator
    for (int i = 0; i < n; i++) {
        delete[] A[i];
    }
    delete[] A;
 
    return 0;
}

void printArray(int** A, int M, int N){
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return;
}