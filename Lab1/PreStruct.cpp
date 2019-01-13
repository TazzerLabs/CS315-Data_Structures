#include <iostream>
using namespace std;

double calcPower(double x, double n);

int main(void)
{
    double base, power;
    
    cout << "Enter base number: ";
    cin >> base;
    
    cout << "Enter power number(positive integer): ";
    cin >> power;
    
    cout << base << "^" << power << " = " << calcPower(base, power) << endl;
    
    return 0;
}

double calcPower(double x, double n)
{
    if ( n <= 0 )
    {
        return 1;
    }
    
    return x * calcPower( x, n - 1 );
}
