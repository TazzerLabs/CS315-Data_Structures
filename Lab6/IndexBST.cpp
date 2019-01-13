// =================================================================================
//  Programmer: Johnathan Soto
//  Program:    IndexBST.cpp
//  Language:   C++
//  Description:    Creating a list of all the words that appear in a given document.
//                  For each word, our index contains a list of all the line numbers
//                  in which the word occurs. In this project, we will create an
//                  index for a given text document. A Binary Search Tree (BST) will
//                  be used to efficiently implement a solution to this problem.
//
//                  Program will support the following operations:
//                  • Read an input file specified by the user, and build the
//                    index table, and reports the following: the number of
//                    distinct words (the number of nodes in the tree), the height
//                    of the tree, and the total CPU time to complete index building.
//                  • Display the index in a format specified below.
//                  • Search for a word. (Display the line numbers containing the
//                    word and the frequency.)
//                  • Save the index (as a specified text file).
//
//                  NOTE: Program will not exclude " or - from words, need fix
//
//
// =================================================================================

// Included Libraries with Header Files
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include "BinarySearchTree.h"
#include <string>
#include <time.h>

using namespace std;

// Prototypes
bool Punct(char s);
void BuildTree(char file[], BinarySearchTree<string>& BST);

// ==== Main ===================================================================
// Input:            argc - The number of inline arguments
//
//                   argv - The array of variables/files that user put
//                     in with their executable
//
// Output -         return 0 for success...
//
// Description:     code is executed with a text file name specified as
//                  argv[1], it builds an index for the specified text
//                  and prints the CPU time to build the index. It also
//                  prints the total number of words as well as the number
//                  of distinct words in the document which is the number of
//                  nodes in the binary search tree. It also displays the
//                  depth of the tree. It then provides the user the following
//                  options: (1) display index, (2) search, (3) save index and
//                  (4) quit.  When the user enters (1), the entire index is
//                  displayed in alphabetical order. If the tree is printed
//                  using inorder traversal, the index will be alphabetically
//                  printed. For each word, the line numbers in which it
//                  appears is also displayed – see the example below.
//                  If the user chooses option (2), it asks for a word from
//                  the user and it searches the tree and prints all the line
//                  numbers in which it appears. If the user chooses option (3),
//                  it asks the user to enter a file name and stores the index
//                  exactly in the same format in which it is displayed on the
//                  console.
//
//
// ===============================================================================

int main(int argc, char* argv[])
{
    
    // Variables
    char files;
    string words;
    int CountLines;
    BinarySearchTree<string> BST;
    int choice;
    bool looper = true;
    
    // Call BuildTree and BST will be pointing to the tree
    BuildTree(argv[1], BST);
    
    // Main Menu initial
    cout << "\nOptions: (1) Display Index, (2) Search, (3) Save Index, (4) Quit\n";
    
    // Loop till they want to end the program and if EOF doesn't occur...
    while (looper && cin >> choice)
    {
        
        switch (choice)
        {
            // Display the index
            case 1:
            {
                cout << "\nPrinting BST Tree: \n";
                cout << "==============================================================\n";
                
                BST.printTree();
                break;
            }
            // Search the Index
            case 2:
            {
                // Search
                cout << "Search Word? ";
                cin >> words;
                cout << endl;
                // call search
                // search returns a pointer to a node and
                // printsearch is void and prints the line numbers of the word if it is found
                BST.printsearch(BST.search(words, BST.GetRoot()));
                break;
            }
            // Save the Index
            case 3:
            {
                string filename;
                
                cout << "Enter the filename with a .txt extension at the end (file.txt): ";
                cin >> filename;
                
                cout << "\nSaving Index...\n\n";
                
                ofstream redirect_file(filename);
                // back up cout buffer
                // rdbuff redirect buffer
                streambuf* strm_buffer = cout.rdbuf();
                
                //redirect output into file
                cout.rdbuf(redirect_file.rdbuf());
                
                //call print funciton
                cout << "===================== Binary Search TREE INDEX =====================================\n\n";
                BST.printTree();
                
                //restore old stuff from before the call (the original buffer)
                cout.rdbuf(strm_buffer);
                cout <<"Saved Index to " << filename <<endl;
                
                break;
            }
            // Quit the program...
            case 4:
            {
                cout << endl;
                looper = false;
                break;
            }
            // Incorrect Entry
            default:
            {
                cout << "Incorrect entry please try again...\n";
                break;
            }
                
        } // end of switch
        
        // Show menu if user still wants to loop
        if (looper)
        {
            cout << "\nOptions: (1) Display Index, (2) Search, (3) Save Index, (4) Quit\n";
        }
        
    } // end of while
    
    return 0;
    
} // end of main

// ==== Punct ========================================================
//  Input:          s -     a character that is being
//                          determined as a punctuation or not.
//
//  Output:         bool - If variable is a punctuation
//                         return true if not false.
//
//  Description:    Function takes in a parameter of type
//                  char to see if it is a punctuation or not.
//                  If it is return true and if not return
//                  false.  Using the library function:
//                  ispunct to narrow down field as well as
//                  using my own function for specific points
//                  the library function may have missed.
//
//
// ===================================================================

bool Punct(char s)
{
    
    // if the function return true for punctuation enter...
    if ( (ispunct(s) ))
    {
        // if the char is ' \' ' (i.e. the library missed this \n)
        if (s == '\'' || s == '"' || s == '-')
        {
            return false;
        }
        
        return true;
    }
    // The library function says it isn't a punctuation...
    else
    {
        return false;
    }
    
} // end of Punct

// ==== BuildTree ========================================================
//  Input:          file[] - A character array of the specified text file
//                           with the words that need to be index into a
//                           tree.
//
//                  BST - A reference of the BST from the caller of type
//                        BinarySearchTree that houses the tree of the
//                        index of words.
//
//  Output:         NONE
//
//  Description:    The function takes as input the file array of chars
//                  and also a referenced variable of BST from caller
//                  that will house the tree of index words from a user
//                  inputed file.  The function then breaks up the file
//                  into strings to be stored into the tree in a specific
//                  order.  When finished building the tree, output the:
//                  Total number of words in the index, Total number of
//                  distinct words, Total time to build the BST, and the
//                  height of the tree.  Then return to caller.
//
// =======================================================================


void BuildTree(char file[], BinarySearchTree<string>& BST)
{
    
    // Variables
    int WordCounter = 0;
    int LineCounter = 0;
    int Dwords = 0;     // DWORD from assembly lol
    int height = 0;
    ifstream TxtFile;
    string word;
    string lines;
    double finish_time;
    double start_time = clock();
    double time;
    
    // Open the text file user provided
    TxtFile.open(file);
    
    // building the BST here
    // While the file does not hit EOF
    while (getline(TxtFile, lines)) // lines stores the whole line
    {
        // Increment the line counter
        LineCounter++;
        
        // Get the lines into ss
        istringstream ss(lines);
        
        // While stringstream can still input into word i.e. there
        // is still stuff to be inserted
        while (ss >> word)
        {
            
            // Increment the Words read in
            WordCounter++;
            
            // if the BST doesn't have this word enter...
            if (!(BST.contains(word)))
            {
                Dwords++; // Increment the Distinct words read in
            }
            
            // Give the length of the word to length
            int length = word.size();
            
            // Need t get all the punctuatons out of the word
            for (int i = 0; i < length; i++)
            {
                
                // if the character is a Punctuation enter...
                if (Punct(word[i]))
                {
                    // erase the char
                    word.erase(i--, 1);
                    length = word.size();
                    
                }
                
            } // end of for loop
            
            // Insert the string word into the tree
            BST.insert(word, LineCounter);
            
        } // end of 2nd while loop
        
    } // end of 1st while loop
    
    // Stop the Clock...
    finish_time = clock();
    
    // Time in seconds
    time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
    
    // Close the user inputed file...
    TxtFile.close();
    
    // Output the Total number of words in the index
    cout << "The total number of words: " << WordCounter << endl;
    
    // Output the number of distinct words
    cout << "The total number of distinct words: " << Dwords << endl;
    
    // Output the total time taken to build the index using BST
    cout << "Time taken to build index using BST is: " << time << " sec\n";
    
    // Height of BST
    height = BST.height(BST.GetRoot());
    cout << "The height of the BST is: " << height << endl;
    
    
    
} // end of BuildTree


