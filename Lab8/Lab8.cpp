
// ======================================================================
//
//  Program: Lab8.cpp
//  Programmer: Johnathan Soto
//  Language: C++
//  Description: agojaofnop[a;
//
//
//
// ======================================================================

// include files
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <tgmath.h>
#include "BinarySearchTree.h"


using namespace std;

// prototypes
bool TraversalCheck(vector<int> Checker);

// ==== Main ============================================================
//
//  Input:          void
//
//  Output:         integer 0 if program succeeded and anything else
//                  means something went wrong
//
//  Description:    • ask the user to enter an integer n; it generates n
//                    random integers and stores them in a vector A.
//                  • insert each key of A into a binary search tree T.
//                  • Display the height and size of the tree T. Also
//                    display the value [log2 n]. (You can expect the
//                    height to be within a factor 2 of [log2 n].)
//                  • Perform inorder traversal and store the keys in
//                    vector B.
//                  • Check that B is in sorted order by calling a
//                    function check that checks that B[j] < B[j+1] for
//                    all j = 0, 1, ..., size(B)-2. Display a message
//                    (‘order check - successful’) if the condition
//                    above holds. If not, display (‘order check
//                    – unsuccessful’).
//                  • Call KeyOfRank(n/2) and check that the returned
//                    key is the same as B[n/2-1]. Display message
//                    (‘key of rank successful’) or ‘key of rank
//                    unsuccessful’ accordingly.
//                  • Next call RankOfKey with input A[n/2]. If the
//                    call returned k, check that A[n/2] == B[k-1]. If
//                    this is true, then display the message (‘rank of
//                    key successful’) else display (‘rank of key
//                    unsuccessful’).
//                  • Iteratively delete the keys stored in positions
//                    A[n/2+1], A[n/2+2], ..., A[n-1], i.e., delete
//                    the last half of the keys in vector A from the
//                    binary search tree T.
//                  • Print the height and the size of the tree T
//                    after the deletions.
//                  • Perform inorder traversal of T and write the
//                    outputs to a vector C and again test that C is
//                    sorted.
//                  • Call KeyOfRank(n/4) and check that the returned
//                    key is the same as C[n/4-1]. Display message
//                    ‘key of rank successful’ or ‘key of rank
//                    unsuccessful’ accordingly.
//                  • Next call RankOfKey with input A[n/4]. If the
//                    call returned k, check that A[n/4] == C[k-1]. If
//                    this is true, then display the message(‘rank of
//                    key successful’) else display (‘rank of key
//                    unsuccessful’).
//
//
// ======================================================================

int main (int argc, char* argv[])
{
    
    // variables
    vector<int> RandList;
    vector<int> InOrderTraversal;
    vector<int> TraversalAfter;
    int input;
    int BSTkey;
    int BSTrank;
    int n;
    int random;
    double log;
    BinarySearchTree<int> BST;
    

    // Clearing screen for user
    cout << string(50, '\n');
    
    
    cout << "How many random integers do you want generated? ";
    cin >> n;

    
    
    // generate n number of random ints
    for (int i = 0; i < n; i++)
    {
        
        random = rand() % RAND_MAX;
        // put 0 - n random ints into the vector of ints
        RandList.push_back(random);
        
    } // end of for
    
    
    
    // Builds BST from the randomized list
    for (int i = 0; i < RandList.size(); i++)
    {
        
        BST.insert(RandList[i]);
        
    } // end of for
    
    log = log2(n);
    
    // Display height and size of the tree
    cout << "\nThe height of the BST is: " << BST.height()
         << "\nThe size of the BST is: " << BST.size()
         << "\nThe log base 2 of " << n << "is: " << log << endl;
    
    // inorder traversal of the BST
    //  store inside vector InOrderTraversal
    BST.InOrder(InOrderTraversal);
    
    // Check that the vector is in sorted order
    // if so say it is, else say it is not
    if (TraversalCheck(InOrderTraversal))
    {
        cout << "Order Check - Successful\n";
    }
    else
    {
        cout << "Order Check - Unsuccessful\n";
    }
    
    // Call KeyOfRank(n/2) and check that
    // the returned key is the same as B[n/2-1].
    // Display message (‘key of rank successful’)
    // or ‘key of rank unsuccessful’ accordingly.
    BSTkey = BST.KeyOfRank(n/2);
    if (BSTkey == InOrderTraversal[(n/2)-1])
    {
        cout << "Key of rank Successful\n";
    }
    else
    {
        cout << "Key of rank Unsuccessful\n";
    }
    
    // call RankOfKey with input RandList[n/2]. If the
    // call returned k, check that RandList[n/2] ==
    // InOrderTraversal[k-1]. If
    // this is true, then display the message (‘rank of
    // key successful’) else display (‘rank of key unsuccessful’).
    BSTrank = BST.RankOfKey(RandList[n/2]);
    
    if (RandList[n/2] == InOrderTraversal[BSTrank-1])
    {
        cout << "Rank of key Successful\n";
    }
    else
    {
        cout << "Rank of key Unsuccessful\n";
    }
    
    // Iteratively delete the keys stored in positions
    // RandList[n/2+1], RandList[n/2+2], ..., RandList[n-1],
    // i.e., delete the last half of the keys in vector
    // RandList from the binary search tree BST.
    for (int i = 0; i < RandList.size()-1; i++)
    {
        
        BST.remove(RandList[(n/2)+i]);
        
    } // end of for
    
    log = log2(n);
    
    // Print the height and the size of the tree
    // BST after the deletions
    cout << "The height of the BST is: " << BST.height()
         << "\nThe size of the BST is: " << BST.size()
         << "\nThe log base 2 of " << n << "is: " << log << endl;
    
    // Perform inorder traversal of BST and write the
    // outputs to a vector TraversalAfter and
    // again test that TraversalAfter is sorted
    BST.InOrder(TraversalAfter);
    
    if (TraversalCheck(TraversalAfter))
    {
        cout << "Order Check - Successful\n";
    }
    else
    {
        cout << "Order Check - Unsuccessful\n";
    }
    
    // Call KeyOfRank(n/4) and check that the returned
    // key is the same as TraversalAfter[n/4-1].
    // Display message ‘key of rank successful’
    // or ‘key of rank unsuccessful’ accordingly.
    BSTkey = BST.KeyOfRank(n/4);
    if (BSTkey == TraversalAfter[(n/4)-1])
    {
        cout << "Key of rank Successful\n";
    }
    else
    {
        cout << "Key of rank Unsuccessful\n";
    }
    
    // call RankOfKey with input RandList[n/4]. If the call
    // returned k, check that RandList[n/4] ==
    // TraversalAfter[k-1]. If this is true, then display
    // the message(‘rank of key successful’)
    // else display (‘rank of key unsuccessful’).
    BSTrank = BST.RankOfKey(RandList[n/4]);
    
    if (RandList[n/4] == TraversalAfter[BSTrank-1])
    {
        cout << "Rank of key Successful\n";
    }
    else
    {
        cout << "Rank of key Unsuccessful\n";
    }
    
    cout << endl;
    
    return 0;
    
} // end of main


// ==== TraversalCheck =================================================
//
// Input:               Checker - a vector of integers that need to
//                                be checked whether if the inorder
//                                traversal was done correctly.
//
//  Output:             if true then the vector was put in proper
//                      inorder traversal. Else false then the vector
//                      was not put in proper inorder traversal
//
//  Description:        Function gets a vector that needs to be checked
//                      if it has been put in proper inorder traversal.
//                      For every integer in the vector check whether
//                      the value in the vector is less than the integer
//                      in the next slot.  If it is then continue on in
//                      the loop, else return false.  If the loop
//                      finishes without any problems, then return true
//                      for the vector is in inorder traversal.
//
//
// ======================================================================

bool TraversalCheck(vector<int> Checker)
{
    
    for (int i = 0; i < Checker.size()-2; i++)
    {
        
        if (Checker[i] < Checker[i+1])
        {
            continue;
        }
        else
        {
            return false;
        }
        
    } // end of for
    
    // vector was traversed fully without hiccups
    return true;
    
} // end of TraversalCheck







