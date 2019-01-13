#include <iostream>
using namespace std;

int f(int n);

int main(void)
{
    
    int j;
    
    cout << "f(?): ";
    cin >> j;
    
    cout << "f(" << j << "): " << f(j) << endl;
    
}

int f(int n)
{
    
    if (n == 1) return 0;
    else if (n % 2 == 0) return 1 + f(n/2);
    else return 2 + f((n - 1) / 2);
    
}
