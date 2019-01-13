
// ==================================================================================================
//  Program Lab4.cpp
//  Programmer: Johnathan Soto
//  Language: C++
//
//  Description: In this project, take as input a string
//               such as [4, [12, 4, 3], [[5, 3, -1], 8], [12, 8]]
//               and store it in a generalized list, we may use
//               two types of nodes: that has two pointers: next
//               and down. We can now define the depth of a node
//               as follows: nodes that are reachable from the
//               initial (header) node via only next pointers are
//               said to be at depth 0. Nodes that can be reached
//               using k down pointers are said to be at depth k.
//               - Update the list: this operation is specified by
//               (j, k) where j is the position of the key in the
//               original list and k is its new value. Thus, for
//               example, update(5, 10) applied to the list above
//               will change it to:
//               [4, [12, 4, 3], [[5, 10, -1], 8], [12, 8]].
//               print a list in the following format: all the
//               numbers that appear in the list should be printed
//               in the left to right order along its depth.
//               Thus, for example, when printed, the above list
//               will generate the output:
//               (4, 1), (12, 2), (4, 2), (3, 2), (5, 3), (10, 3),
//               (-1, 3), (8, 2), (12, 2), (8, 2)
//
//               Error-handling: suppose the input string is not
//               balanced, for example: “[3, 4, [5]], -4]”. Your
//               program should print a message and point out the
//               first position where an error has occurred. In
//               this case, the output would be “input not valid
//               at position 8” since the 8th token (which is -4)
//               is not a valid token.
//
//               Print: This version of print prints a list in the
//               form of a string in the same format in which the
//               input is entered by the user.
//
//               Delete: The key in specified position is deleted.
//               Thus deletion of 3rd member from the list
//               [4, [12, 4, 3], [[5, 10, -1], 8], [12, 8]] will
//               result in the list [4, [12, 4], [[5, 10, -1], 8], [12, 8]].
//               (You can assume that member being deleted is not
//               the only member of the inner-most list to which it
//               belongs. Thus, for example, if the list is
//               [1, 2, [3], 4, 5], the input for deletion will not be 2.
//
//
// ==================================================================================================

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
//#include "scan.cpp"

using namespace std;

// ==== Classes ========================================================================

class Stack;

class Node
{

public:
    
    Node(int key1)
    {
        key = key1;
        tag = 0;
        down = NULL;
        next = NULL;
    }

    Node(Node* dptr, Node* nptr)
    {
        tag = 1;
        down = dptr;
        next = nptr;
    }

    void setKey(int k)
    {
        key = k;
    }

    void setDown(Node* ptr)
    {
        down = ptr;
    }

    void setNext(Node* ptr)
    {
        next = ptr;
    }
    
    void setTag(int t)
    {
        tag = t;
    }
    
    int getKey()
    {
        return key;
    }
    
    int getTag()
    {
        return tag;
    }
    
    Node* getDown()
    {
        return down;
    }

    Node* getNext()
    {
        return next;
    }

    int size()
    {
        if (this == NULL)
        {
            return 0;
        }
        else if (this->tag == 0)
        {
            return 1;
        }
        else
        {
            return down->size() + next->size();
        }
    }
    void update(int j, int k)
    {
        
        // if the list is empty
        if (isEmpty())
        {
            cout << "\n\nERROR LIST IS EMPTY...\n";
            return;
        }
        else if (tag == 0) // node is a leaf
        {
            
            key = k;
            return;
        }
        // Gets me to the specified location to be 
        else // else you have a list...
        {
            // s = size of the down pointer list
            int S = down->size();
            
            // if the position is less than or equal to
            // size of the down pointer list (check position)
            if (j <= S)
            {
                // down has the position to be updated so call
                // update
                down->update(j,k);
            }
            else // j > S so next has the position
            {
                next->update(j - S, k);
            }
            
        }

    }
    
    void Delete(int j)
    {
        // Will delete the leaf node only...
        // Doing this in order to have an
        // option later to insert at node's bot if desired

        Node* curr = this;
        // if the list is empty
        if (isEmpty())
        {
            cout << "\n\nNODE IS EMPTY...\n";
            return;
        }
        else if (tag == 0) // node is a leaf
        {
            
            delete(curr);
            return;
        }
        // Gets me to the specified location to be
        else // else you have a list...
        {
            // s = size of the down pointer list
            int S = down->size();
            
            // if the position is less than or equal to
            // size of the down pointer list (check position)
            if (j <= S)
            {
                // down has the position to be updated so call
                // update
                if (down != NULL)
                {
                    if (down->tag == 0)
                    {
                        down->Delete(j);
                        curr->down = NULL;
                    }
                }
                down->Delete(j);
                
            }
            else // j > S so next has the position
            {
                if (next != NULL)
                {
                    if (next->tag == 0)
                    {
                        next->Delete(j);
                        curr->next = NULL;
                    }
                }
                next->Delete(j - S);
            }
            
        }
    }

    bool isEmpty()
    {
	  return this == NULL;
    }

    void print(int depth)
    {
        if (this == NULL) return;
        if (tag == 0)
        {
            cout << "<" << key << ":" << depth << ">  " ;
        }
        else
        {
            
	     down->print(depth+1);
	     next->print(depth);
            
	    } // end else
        
	 } // end print
    
    void printList(Node* header, Node* prev)
    {
        // if list is null then no list to print
        // print first integer then '[', integer and ',' if there is a next else ']'
        // else print integer then ',' if there is a next or depth
        // else print ']'
        
        Node* curr = header;
        
        while (curr) // loop till null
        {
            
            if (curr == header && curr->tag == 1)
            {
                cout << "[";
            }
            if (curr->tag == 0)
            {
                
                cout << curr->key;
                if (curr->next && curr->next->down != NULL) // only executes if next has an address
                {
                    
                    cout << ",";
                    
                }
                else
                {
                    return;
                }
                
            }
            else
            {
                
                curr->down->printList(curr->down, prev);
                if (curr->next && curr->next->down != NULL)
                {
                    cout << ",";
                }
                
            }
            prev = curr;
            curr = curr->next;
            
        } // end of while
        
        if (prev->next == NULL)
        {
            cout << "]";
        }
        
    } // end of PrintList

private:
    
    int tag;
    int key;
    Node* down;
    Node* next;
    
};

//==== End of Node Class================================================================================================

// ==== Start of Stack Class ===========================================================================================

class Stack
{

private:
    
    int maxTop;// max stack size = size - 1
    int top;// current top of stack
    Node* values[1000];// element array

public:

  bool IsEmpty() { return top == -1; }
  bool IsFull() { return top == maxTop; }

  Stack()
    {
        
        top=-1;
        maxTop= 999;
    
    }

  void Push(Node* x)
    {
        if (IsFull())  // if stack is full, print error
            cout << "Error: the stack is full." << endl;
        else
        {
            values[++top]= x;
        }
    }

  Node*  Pop()
    {
        if (IsEmpty())
        { //if stack is empty, print error
            cout << "Error: the stack is empty." << endl;
            return NULL;
        }
        else
        {
            return values[top--];
        }
    }

  Node* Top()
    {
        if (IsEmpty())
        {
            cout << "Error: the stack is empty." << endl;
            return NULL;
        }
        else
            return values[top];
    }
};// end of stack class

// ==== End of Classes ========================================================================

// ==== Functions ========================================================================


// Converts string integers to ints
int convert(string x)
{
    // converts a string rep of decimal integer to an int
    return atoi(x.c_str());
}

// =====================================================================
//
//  Input:          A vector string called T that houses tokenized
//                  characters of the list
//
//  Output:         An address to the complete build of the list
//
//  Description:    Loops through the tokenized list, if "[" then
//                  create a new node with tag set to -1,down
//                  pointer and next pointer to NULL, push new node
//                  to the stack. Else if token is a number or
//                  negative sign, then convert string to integer
//                  and store in local variable "key".  Create new
//                  node with new key and push to the stack.
//                  Else if the token is "]", then pop the stack
//                  into a node leafer and create a new node "K"
//                  that houses the address of the leafer in its down
//                  pointer.  Now loop till the Top's Tag is -1 or
//                  the down pointer is NULL.  Inside the loop, pop
//                  another item off the stack and store inside a
//                  node, and set a new node with its down pointer
//                  to the recent popped item address stored in
//                  node.  Also the new node's next will house the
//                  address of K node from before the loop.  After the
//                  loop pop the "[" and push the altered node with the
//                  address to the list to the stack.  Return the
//                  address to the list.
//
// =====================================================================

Node* buildList (vector<string> T) // Builds the list
{
    
    // Variables
    Stack S;
    
    for (int i = 0; i < T.size(); i++)
    {
        
        if (T[i] == "[")
        {
            
            Node* pointer = new Node(NULL,NULL);
            pointer->setTag(-1); // -1 indicates "["
            S.Push(pointer);
            
        }
        // put [0] so that I can get the '-' sign as it didn't work with a single [i]...
        else if ((T[i] >= "0" && T[i] <= "9") || T[i][0] == '-') // if integer or neg sign
        {
            
            int key;
            key = convert(T[i]); // convert integer or
            
            Node* leafNode = new Node(key); // create new node with key from token list
            S.Push(leafNode); // Push node to stack
            
        }
        else // T[k] == "]"
        {
            
            // pops top of stack into leafer node
            Node* leafer = S.Pop();
            
            // New node with down pointer to leafer and next pointer to NULL
            Node* NewPointerNode = new Node(leafer, NULL);
            
            // loop until "[" has appeared
            while ((S.Top()->getTag() != -1) || S.Top()->getDown() != NULL)
            {
                
                leafer = S.Pop(); // overwrite leafer with new address to node
                
                // Create a new node stored in NewPointerNode that has
                // the down pointer to leafer and the old
                // NewPointerNode addresses
                NewPointerNode = new Node(leafer, NewPointerNode);
                
            }
            
            S.Pop(); // Pop the "["
            S.Push(NewPointerNode); // push onto the stack a new
        }
        
    }
    
    return S.Pop();

} // end of create

// ================================================================
//  Input:      A string input that needs to be tokenized
//
//  Output:     A vector that stores the tokenized input that is
//              housed as a string
//
//  Description Uses a switch to tokenize the input in order to
//              properly allocate each part of the input into the
//              vector.  However do not insert into the vector ','
//              or ' '.
//
// ================================================================
vector<string> Tokenization (string input)
{
    // Variables
    vector<string> Token;
    int Lcounter = 0;
    int Rcounter = 0;
    int Ncounter = 0;
    
    // Loop for the length of the input
    for (int i = 0; i < input.length(); i++)
    {
        // Tokenize the whole string
        switch (input[i])
        {
                
            case '[':
                Lcounter++;
                Token.push_back("[");
                break;
                
            case ']':
                Rcounter++;
                Token.push_back("]");
                break;
                
            case ' ':
                break;
                
            case ',':
                break;
                
            case '-':
                Ncounter++;
                Token.push_back("-");
                while(input[i+1] >= '0' && input[i+1] <= '9')
                {
                    
                    Token.back() += input[i+1];
                    i++;
                    
                }// end of while
                
                break;
                
            default: // if number...
                Ncounter++;
                string number;
                
                number += input[i];
                
                while(input[i+1] >= '0' && input[i+1] <= '9')
                {
                    
                    i++;
                    number += input[i];
                    
                }//end of while
                
                Token.push_back(number);
                break;
                
        }//switch
        
        // Error checking for correct number of [, ]
        if ((Lcounter == Rcounter && i != input.length()-1))
        {
            
            cout << "input not valid at position " << Lcounter + Rcounter + Ncounter + 1
            << "\nPlease Try again...\n";
            Token.clear();
            Token.push_back("F");
            return Token;
            
        }
        
    }// end of for loop
    
    // Error checking outside here do to reoccurring number counter being 0 at start
    // so need it outside the loop after it is finished to see if any numbers are in
    // it, if not then send out an error it isn't proper...
    if (Ncounter == 0 || Lcounter == 0 || Rcounter == 0)
    {
        
        cout << "input not valid at position " << Lcounter + Rcounter - 1
        << "\nPlease Try again...\n";
        Token.clear();
        Token.push_back("F");
        return Token;
        
    }
    
    return Token;
    
}// end of tokenization

/*
// ================================================================
//
//
//  doesn't work
//
//
// ================================================================

vector<string> Reverse (Node* header, Node* prev)
{
 // Retokenizing the list put into function...
 vector<string> temp;
 Node* curr = header;
 
 while (curr) // loop till null
 {
 
    if (curr == header && curr->getTag() == 1) // if empty node without key
    {
        temp.push_back("[");
    }
    if (curr->getTag() == 0) // if node has a key
    {
 
        temp.push_back(to_string(curr->getKey()));
        if (curr->getNext() && curr->getNext()->getDown() != NULL) // only executes if next has an address
        {
            
            temp.push_back(",");
 
        }
        else
        {
            return temp;
        }
 
    }
    else
    {
 
        vector<string> rec = Reverse(curr->getDown(), prev);
        
        temp.insert(temp.end(), rec.begin(), rec.end());
        
        if (curr->getNext() && curr->getNext()->getDown() != NULL)
        {
            temp.push_back(",");
        }
 
    }
     prev = curr;
     curr = curr->getNext();
 
    } // end of while
 
    if (prev->getNext() == NULL)
    {
        cout << "]";
        temp.push_back("]");
    }
 
    return temp;
    
}

*/
 
// ==== End of Functions ========================================================================


int main(int argc, char* argv[]) // void parameters?
{
    // Variables
    char choice;
    int looper = 1;
    int trues = 1;
    int deleter;
    int element;
    int updater;
    string UserInput;
    vector<string> list;
    vector<string> Rlist;
    
    
    while (trues == 1)
    {
    
        // Get the user input
        cout << "=====================================\n"
             << "  Program now has Error Handling!\n"
             << "=====================================\n"
             << "Input a generalized list:\n";
        getline(cin, UserInput);
        cout << endl;
    
        //Tokenize the list
        list = Tokenization(UserInput);
    
        if (list[0] != "F") // list is balanced
        {
            trues = 0;
        }
    }
    
    //buildList
    Node* temp = buildList(list);
    
    // Display list before update with size
    cout << "The list before update: " << endl;
    temp->print(0);
    cout << "\nThe size is " << temp->size() << endl;
    
    // loop till user wants to exit the program
    // else show the menu options
    while (looper == 1)
    {
        
        cout << "\nWhat would you like to do? \n\n"
             << "'U' : Update an element\n"
           //<< "'R' : Deep Reverse the list at all levels\n"
             << "'P' : Print the list in the form of a string in the same format the user entered\n"
             << "'D' : Delete the key in a specified location\n"
             << "'Q' : Quit the program\n\n";
        cin >> choice;
        
        switch (toupper(choice))
        {
        
            case 'U':
                // Update the list
                cout << "\nWhich element would you like to update?  "; // j
                cin >> element;
                cout << "\nWhat would you like to update it to? "; // k
                cin >> updater;
            
                // Call update here
                temp->update(element, updater);
            
                // Print updated list
                cout << "The updated list is:\n";
                temp->print(0);
                cout << endl;
                // Node->print(0);
                
                break;
            /*
            case 'R':
                // Reverse the order and store in a node
                cout << "\nDeep Reverse of user input: \n";
                
                Rlist = Reverse(temp, NULL); // reverse the list and sends output string to Rlist
                reverse(Rlist.begin(), Rlist.end());
                
                for (int i = temp->size(); i > 0; i-- )// Delete all original list
                {
                    temp->Delete(i); // Deletes the whole list
                }
                delete(temp);
                    
                temp = buildList(Rlist);    // Building reversed list
                // print out temp->print(0);
                
                break;
            */
            case 'P':
                // Print list in string format and exactly how user inputed
                cout << "\nUser's Generalized list: \n";
                temp->printList(temp, NULL);
                cout << endl;
                break;
                
            case 'D':
                // Delete the node
                cout << "\nWhat key do you want deleted at specified position? ";
                cin >> deleter;
                
                temp->Delete(deleter);
                // Display the new list
                cout << "\nNew List: \n";
                temp->print(0);
                cout << endl;
                
                break;
                
            case 'Q':
                cout << "\nClosing Program...\n\n";
                looper = 0;
                break;
            
            default:
                cout << "\nERROR, INCORRECT ENTRY, PLEASE TRY AGAIN.\n\n";
                break;
        
        }
    } // end of while loop
    
    return 0;
}






