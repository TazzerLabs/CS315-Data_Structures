//
//  lab3.cpp
//  
//
//  Created by Johnathan Soto on 2/6/18.
//

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int Acounter = 0;
int Icounter = 0;
int Lcounter = 0;

void insertionSort (vector<int> A)
{
    for (int j = 1; j < A.size(); ++j)
    {
        int temp = A[j];
        Lcounter++;
        
        int k;
        
        for (k = j-1; k >= 0 && A[k] > temp; k--, Icounter++)
            A[k+1] = A[k];
        A[k+1] = temp;
        
    }
}


double calcPower(double x, double n)
{
    if ( n == 0 )
    {
        return 1;
    }
    else if (n == 1)
    {
        return x;
    }
    else if ((int)n % 2 == 0)
    {
        Acounter++;
        return calcPower(x * x, n/2);
    }
    else
    {
        Acounter = Acounter + 2;
        return calcPower(x * x, ((n-1)/2)) * x;
    }


    
}

int quiz2(int n)
{
    
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;
    else if (n % 2 == 0)
        return quiz2(n/2);
    else
        return quiz2((n-1)/2) + 1;
    
}

int main()
{
    /*
    double base, power;
    
    cout << "Enter base number: ";
    cin >> base;
    
    cout << "Enter power number(positive integer): ";
    cin >> power;
    
    cout << base << "^" << power << " = " << calcPower(base, power) << endl;
    
    cout << "Multi: " << (Acounter) << endl;
    
     
    
    cout << quiz2(1000) << endl;
     
     */
    
    vector<int> A;
    
    A.push_back(0);
    A.push_back(1);
    A.push_back(2);
    A.push_back(3);
    A.push_back(4);
    A.push_back(5);
    A.push_back(6);
    A.push_back(7);
    A.push_back(8);
    A.push_back(9);
    
    insertionSort(A);
    
    cout << "1st loop: " << Lcounter<< "\n2nd loop: " << Icounter << endl;
    
    return 0;
}

