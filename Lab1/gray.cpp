#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> gray(int n);

int main(void)
{
    
    int k;
    vector<string> B;
    
    cout << "n = ";
    cin >> k;
    
    B = gray(k);
    int counter = 0;
    
    for (int i = 0; i < B.size(); i++)
    {
        cout << B[i] << endl;
        counter++;
    }
    
    cout << "\ncounter: " << counter << endl;
    
    return 0;
    
}

vector<string> gray(int n)
{
    
    vector<string> test;
    vector<string> reverseG;
    vector<string> forward;
    vector<string> arr;
    
    if (n == 0)
    {
        test.push_back("0");
        return test;
    }
    if (n == 1)
    {
        test.push_back("0");
        test.push_back("1");
        return test;
    }
    
    // Recursive call
    forward = gray(n - 1);
    
    // Reverse vector takes in the reverse order of forward vector
    reverseG.resize(forward.size());
    reverse_copy(forward.begin(), forward.end(), reverseG.begin());
    
    //prefix elements of forward with 0
    for (int i = 0; i < forward.size(); i++)
    {
        forward[i] = "0" + forward[i];
        arr.push_back(forward[i]);
    }
    
    //prefix elements of reverse with 1
    for (int i = 0; i < reverseG.size(); i++)
    {
        reverseG[i] = "1" + reverseG[i];
        arr.push_back(reverseG[i]);
    }
    
    
    //arr = (concat of forward and reverseG)
    forward.insert(forward.end(), reverseG.begin(), reverseG.end());
    arr = forward;
    
    return arr;
    
}

