// ======================================================================
//  Programmer:     Johnathan Soto
//  Program:        Lab7.cpp
//  Language:       C++
//  Description:    Peg solitaire is a board game played on a board
//                  that contains a collection of peg-holders (holes).
//                  Some of them have a peg on them. The goal is to
//                  remove all except one peg from the board. The rule
//                  for removing a peg is as follows: let A, B and C
//                  be three consecutive holes in the vertical or the
//                  horizontal direction. If A and B have a peg and C
//                  is empty, then the pegs can be removed from
//                  positions A and B, and a peg placed at C. Each move,
//                  thus, removes exactly one peg. It is clear that there
//                  can be many choices for a move from a given position.
//                  The goal is to find a sequence of moves that reduces
//                  to the board to a single peg. (We call such positions
//                  winning positions.) But if the moves are not correctly
//                  chosen, we may end with a board with several pegs left
//                  and no valid moves. It is also clear that there are
//                  some starting positions from which it is impossible
//                  to find a winning position.
//
//                  Program will include:
//                  ------------------------------------------------------
//
//                  • Implement a recursive backtracking
//                    algorithm based on Depth First Search (DFS) which
//                    is a powerful general purpose technique for search
//                    problems.
//
//                  • Use a hash table that enables fast search
//                    over a large container of board positions. The idea
//                    of caching the results of previous search to speed
//                    up is central to many applications such as web search.
//
//                  • Experimentally compare the performance of the costs
//                    of search and insert for various size of hash tables.
//
//                  • Use supporting data structures like arrays,
//                    lists and stacks to represent the board, to maintain
//                    move sequences, to generate all possible next moves
//                    from a given board position etc.
//
//                  Program has open hashing and closed hashing
//
//
// ======================================================================

// Includes
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<stdlib.h>
#include<sstream>
#include "SeparateChaining.cpp"
#include "QuadraticProbing.h"

using namespace std;

// Move Structure
struct Move
{
    long long board;
    int start;
    int mid;
    int end;
    
};


// Prototypes
bool isPeg(long long x, int index);
void setPeg(long long& x, int index);
void clearPeg(long long& x, int index);
bool validPos(int index);
void makeMove(long long x, vector<Move>& moves, int start, int mid, int end);
void nextMoves(long long x, vector<Move>& moves);
bool Solved(long long x);
bool Solve(long long x, vector<Move>& solution);
long long buildBoard(string FileName);
bool hSolve(long long board, vector<Move>& solution, HashTable<long long>& H);
bool CHSolve(long long board, vector<Move>& solution, DoubleHashTable<long long>& H);


// ==== Main ========================================================
//
//  Input:              void
//
//  Output:             int return 0 if program was successful
//
//  Description:        Initial start of the program that will
//                      ask for the user's text file of the peg
//                      locations and also display a main menu for
//                      the user.  When getting the text file from
//                      it will call a function that will build the
//                      board.  From there the user has four choices
//                      either:
//                      1) Solve the puzzle with no hashing
//                      2) Solce the puzzle with open hashing
//                      3) Solve the puzzle with closed hashing
//                      4) Quit the program
//
//                      Within 1-3 options, the program will be
//                      timing the time to take to solve the puzzle
//                      also within each option, they will call their
//                      respective solvers if chosen.  When the
//                      function finishes and shows the solution to
//                      the puzzle with the time is displayed, the
//                      loop will reignite asking what the user wants
//                      to do next, until they hit 4, for quit, or
//                      ctrl-d.
//
//
// ==================================================================

int main()
{
    // Variables
    string file;
    int choice;
    char cont;
    bool looper = true;
    vector<Move> moves;
    double finish_time;
    double start_time;
    double time;
    long long board = 0;
    
    cout << "Please insert a filename: ";
    cin >> file;
    
    board = buildBoard(file);
    cout << "\n---- Main Menu ------------------------------------------------------\n"
         << "\nPlease Select an option:\n"
    << "1) No Hashing\n2) Open Hasing\n3) Closed Hashing\n4) Quit\nOption: ";
    
    // While the user inserts something
    while (looper && cin >> choice)
    {
        
        cout << "-----------------------------------------------------------------\n";
        
        switch (choice)
        {
                
                cout << "No Hashing:\n";
            
            // No Hashing
            case 1:
            {
                start_time = clock();
                // if board was solved continue...
                if (Solve(board, moves))
                {
                    
                    cout << "Solution: ";
                    
                    // iterate through moves
                    // auto can only be used in C++ 11
                    for (auto m: moves)
                    {
                        cout << "( " << m.start << " "
                             << m.mid << " "
                             << m.end << ") ";
                    }
                    cout << "\nSolved the board!\n";
                }
                // the board was not solved...
                else
                {
                    cout << "Board is not solvable...\n\n";
                }
                
                // stop clock
                finish_time = clock();
                // calculate the time
                time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
                
                cout << "Time to solve board with No Hashing: " << time << "secs\n";
                
                break;
            }
            // Open Hashing
            case 2:
            {
                
                cout << "Open Hashing:\n";
                
                // with resize at 101
                
                HashTable<long long> hashTable;
                
                cout << "\nBoard with Resize: \n";
                
                start_time = clock();
                
                // if board was solved by hSolve
                if (hSolve(board, moves, hashTable))
                {
                    
                    // for every moves in vector
                    // print the moves
                    for( auto m: moves)
                    {
                        
                        cout << "( " << m.start << " "
                             << m.mid << " "
                             << m.end << ") ";
                        
                    } // end of for
                    cout << "\nSolved!\n";
                    
                } // end of if
                else
                {
                    cout << "Program cannot solve the board given...\n\n";
                }
                
                // Stop the Clock...
                finish_time = clock();
                
                // Generate the total time
                time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
                
                // Display total time to user
                cout << "Time to solve board with No Hashing: " << time << " secs\n\n";
                
                
                
                // ** with resize at 10000 ******************************************************
                
                cout << "\nBoard with Size 10000: \n";
                
                // make the board empty
                hashTable.makeEmpty();
                
                hashTable.ReSize(10000);
                
                start_time = clock();
                
                // if board was solved by hSolve
                if (hSolve(board, moves, hashTable))
                {
                    
                    // for every moves in vector
                    // print the moves
                    for( auto m: moves)
                    {
                        
                        cout << "( " << m.start << " "
                        << m.mid << " "
                        << m.end << ") ";
                        
                    } // end of for
                    cout << "\nSolved!\n";
                    
                } // end of if
                else
                {
                    cout << "Program cannot solve the board given...\n\n";
                }
                
                // Stop the Clock...
                finish_time = clock();
                
                // Generate the total time
                time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
                
                // Display total time to user
                cout << "Time to solve board with No Hashing: " << time << "secs\n\n";
                
                
                
                // ** with resize at 50000 ******************************************************
                
                cout << "\nBoard with Size 50000: \n";

                
                // make the board empty
                hashTable.makeEmpty();
                
                hashTable.ReSize(50000);
                
                start_time = clock();
                
                // if board was solved by hSolve
                if (hSolve(board, moves, hashTable))
                {
                    
                    // for every moves in vector
                    // print the moves
                    for( auto m: moves)
                    {
                        
                        cout << "( " << m.start << " "
                        << m.mid << " "
                        << m.end << ") ";
                        
                    } // end of for
                    cout << "\nSolved!\n";
                    
                } // end of if
                else
                {
                    cout << "Program cannot solve the board given...\n\n";
                }
                
                // Stop the Clock...
                finish_time = clock();
                
                // Generate the total time
                time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
                
                // Display total time to user
                cout << "Time to solve board with No Hashing: " << time << "secs\n\n";

                // ** with resize at 100000 ******************************************************

                cout << "\nBoard with Size 100000: \n";

                // make the board empty
                hashTable.makeEmpty();
                
                hashTable.ReSize(100000);
                
                start_time = clock();
                
                // if board was solved by hSolve
                if (hSolve(board, moves, hashTable))
                {
                    
                    // for every moves in vector
                    // print the moves
                    for( auto m: moves)
                    {
                        
                        cout << "( " << m.start << " "
                        << m.mid << " "
                        << m.end << ") ";
                        
                    } // end of for
                    cout << "\nSolved!\n";
                    
                } // end of if
                else
                {
                    cout << "Program cannot solve the board given...\n\n";
                }
                
                // Stop the Clock...
                finish_time = clock();
                
                // Generate the total time
                time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
                
                // Display total time to user
                cout << "Time to solve board with No Hashing: " << time << "secs\n\n";
                
                
                break;
            }
            case 3:
            {
                
                cout << "Closed Hashing:\n";
                
                DoubleHashTable<long long> DhashTable;
                start_time = clock();
                
                // if board was solved by hSolve
                if (CHSolve(board, moves, DhashTable))
                {
                    
                    // for every moves in vector
                    // print the moves
                    for( auto m: moves)
                    {
                        
                        cout << "( " << m.start << " "
                        << m.mid << " "
                        << m.end << ") ";
                        
                    } // end of for
                    cout << "\nSolved!\n";
                    
                } // end of if
                else
                {
                    cout << "Program cannot solve the board given...\n\n";
                }
                
                // Stop the Clock...
                finish_time = clock();
                
                // Generate the total time
                time = (double)(finish_time - start_time) / CLOCKS_PER_SEC;
                
                // Display total time to user
                cout << "Time to solve board with No Hashing: " << time << "secs\n";
                
                break;
            }
            // Quit
            case 4:
            {
                cout << "Quitting Program...\n\n";
                looper = false;
                break;
            }
            // User inserted incorrect entry
            default:
            {
                cout << "Incorrect Entry...Please Try again...\n ";
                break;
            }
                
        } // end of switch
        
        if (looper)
        {
            
            cout << "-----------------------------------------------------------------\n";
            
            cout << "Solve another board? (Y/N) ";
            cin >> cont;
            
            if (toupper(cont) == 'N')
            {
                cout << "Quitting Program...\n\n";
                return 0;
            }
            
            // Get a new Peg board to solve
            cout << "\nPlease insert a filename: ";
            cin >> file;
            
            board = buildBoard(file);
            
            cout << "\n---- Main Menu ------------------------------------------------------\n"
                 << "\nPlease Select an option:\n"
                 << "1) No Hashing\n2) Open Hasing\n3) Closed Hashing\n4) Quit\nOption: ";
            
        } // end of if
        
    } // end of while loop
    
    return 0;
    
} // end of main

// ==== isPeg ================================================================
//
//  Input:          x -     long long data type that holds the board
//
//                  index - integer data type that houses the index at which
//                          to check if there is a peg in that specific index
//
//  Output:         bool - returns true if there is a peg in the specified
//                          location and false if there isn't a peg in index
//
//  Description:    Function gets a board and index value that may be set
//                  inside the board.  However since the program is using a
//                  64 bit to store the board, bitwise operators are necessary
//                  to see the pegs.  To do this x is bitwise & to a long long
//                  conversion of integer 1, that is also being left shifted
//                  by the index.  If the there is a peg from this conversion,
//                  then the value will be not 0.  However if there is a 0
//                  after operations, then there is no peg in the location.
//
// ===========================================================================

bool isPeg(long long x, int index)
{
    
    //  Bitwise & x with left shift of long long 1
    // if it isn't 0 then it is a peg else false
    return ((x & ((long long)1 << index)) != 0);
    
} // end of isPeg

// ==== SetPeg ===============================================================
//
//  Input:          x -     long long data type that holds a reference of the
//                          board to be manipulated.
//
//                  index - integer data type that house the index at which to
//                          set the peg at...
//
//  Output:         Void
//
//  Description:    Function gets a referenced board and index value to be set
//                  be inside the board.  However since the program is using a
//                  64 bit to store the board, bitwise operators are necessary
//                  to set the pegs.  To do this x is bitwise | to a long long
//                  conversion of integer 1, that is also being left shifted
//                  by the index. Doing this sets the value at the location
//                  within the board to be 1, thus marking the location as a
//                  set peg within the board.
//
//
// ===========================================================================

void setPeg(long long& x, int index)
{
    
    // bitwise or x with long long 1 that is shifted by index
    // used to set a peg with a number that is 64 bit long
    x |= (long long)1 << index;
    
} // end of SetPeg

// ==== clearPeg =============================================================
//
//  Input:          x -     long long data type that holds a referenced of the
//                          board to be manipulated
//
//                  index - integere data type that houses the index at which
//                          the peg needs to be cleared
//
//  Output:         Void
//
//  Description:    Function gets a referenced board and index value to be
//                  cleared inside the board.  However since the program is
//                  using a 64 bit to store the board, bitwise operators are
//                  necessary to set the pegs.  To do this x is bitwise & and
//                  ~ to a long long conversion of integer 1, that is also
//                  being left shifted by the index. Doing this sets the value
//                  at the location within the board to be 0, thus marking the
//                  location as a cleared peg within the board.
//
//
// ===========================================================================

void clearPeg(long long& x, int index)
{
    
    // bitwise & to x with tilde (~, switches up the bits) of long long 1
    // shifted by the index
    //set x to this value
    x &= ~((long long)1 << index);
    
} // end of clearPeg

// ==== ValidPos =============================================================
//
//  Input:          index - integer data type that houses the index at which
//                          the user wishes to move to (or in this case the
//                          program...)
//
//  Output:         bool -  returns true if the position is valid and
//                          false if the position is invalid
//
//  Description:    Function gets an index position from the caller as to
//                  verify that the current position they want to access is
//                  a valid one.  If the index is below zer or above 48
//                  (0-48 bound) then the index is not in bounds.  However
//                  the index can also be in bounds when the values
//                  equate to being false (returned as true due to !) if they
//                  are valid positions.  Else if they aren't then the
//                  variables equate to true before ! has been applied
//
// ===========================================================================

bool validPos(int index)
{
    
    // if the peg isn't within bounds of the board its not valid
    if (index < 0 || index > 48)
    {
        return false;
    }
    
    // Mod 7 for the columns and divide for rows for a 7x7 board
    int col = index % 7;
    int row = index / 7;
    
    // These two variables get the corners for a 7x7 board
    // only if the index is valid for a 7x7.
    // values should be false if they are valid positions
    // else if they aren't then the variables equate to true
    bool columnCorners = (col < 2 || col >= 5);
    bool rowCorners = (row < 2 || row >= 5);
    
    return !(columnCorners && rowCorners);
        
} // end of ValidPos

// ==== makeMove =========================================================
//
//  Inout:          x -     long long datat type that holds the board
//
//                  moves - a vector of type Moves structure that houses all
//                          the moves
//
//                  start - integer data type that has the starting position
//
//                  mid -   integer dat type that has the mid position
//
//                  end -   integer data type that has the end position
//
//  Output:         void
//
//  Description:    This function makes a move within the board based off the
//                  DFS solving algorithm.  If the positions at start, mid
//                  , or end equate to false for being valid, then the
//                  program cannot make a move so return to caller.  However
//                  if there is a peg on the board at start and mid but not
//                  at end then a move can be made.  Since a move can be
//                  made a new board should be made in order not to damage
//                  original.  The new board will be a copy of the original
//                  and next the program will clear the peg at start and mid
//                  and place a peg at end to make a move.  Next a new
//                  Moves object should be made in order to set the new board
//                  to the new object along with the start, mid, and end.
//                  Next push the new Moves object onto the old moves vector
//                  object in order to keep track of it for the caller.
//                  End function call and return to caller.
//
// ==========================================================================

void makeMove(long long x, vector<Move>& moves, int start, int mid, int end)
{
    
    // if the postion is not valid for the pegs in start, mid, or end
    // return
    if ( !(validPos(start)) || !(validPos(mid)) || !(validPos(end))  )
        {
            return;
        }
    // if there is a peg in the start and mid then the program
    // can move the peg from start to the end overtaking the mid
    if (isPeg(x, start) && isPeg(x, mid) && !(isPeg(x, end)) )
    {
        
        // create a copy of the board to manipulate from x
        long long FreshBoard = x;
        
        // Clear the pegs at position start and mid
        clearPeg(FreshBoard, start);
        clearPeg(FreshBoard, mid);
        
        // Set the peg at the end
        setPeg(FreshBoard, end);
        
        // create a new Move struct object
        Move g;
        
        // Set the object's variables to the new board and start to end
        g.board = FreshBoard;
        g.start = start;
        g.mid = mid;
        g.end = end;
        
        // push this new object onto the moves vector of struct Moves
        moves.push_back(g);
        
    }
    
} // end of makeMove

// ==== nextMoves ============================================================
//
//  Input:          x -     long long datat type that holds the board
//
//                  moves - vector of Moves struct, passed by referenced
//
//  Output:         void
//
//  Description:            Function gets the next moves and stores inside the
//                          moves variable.  It does this by first instancing
//                          through a loop to get to all the points within a
//                          7x7 board.  While in this loop it will calculate
//                          col and row at which it is located at based off
//                          the integer it is working on (0-48).  Once it has
//                          the col and row instance, it will check to see if
//                          the col is below 5, and if it is then the
//                          move needs to be made from k to k+1 and k+2.  If
//                          the col is above 1 then the move needs to be made
//                          from k to k-1 and k-2.  If the row is less than 5
//                          the move needs to be made from k to k+7 and k+14.
//                          If the row falls above 1 then the move needs to be
//                          made from k to k-7 and k-14.
//
//                          Col:    (k%7),  Row: (k/7)
//
//                          Col is horizontal and row is vertical, so col
//                          needs to move from horizontal points of + or - 1
//                          or 2.
//                          Since row is a vertical needs to move from
//                          vertical points of + or - 7 or 14, based off board
//                          size.
//
// ===========================================================================

void nextMoves(long long x, vector<Move>& moves)
{
    
    // loop through whole board of 7x7; 0-48
    for (int k = 0; k < 49; k++)
    {
        
        // get the column location and row location
        int col = k % 7;
        int row = k / 7;
        
        // if the col location is under 5 then
        // the move to be made will be at k value
        // k + 1, and k + 2
        if (col < 5)
        {
            makeMove(x, moves, k, k+1, k+2);
        }
        // if the col location is over 1 then
        // the move to be made will be at k,
        // k - 1, and k - 2
        if (col > 1)
        {
            makeMove(x, moves, k, k-1, k-2);
        }
        // if the row location is under 5 then
        // the move to be made will be at k value
        // k + 7, and k + 14
        if (row < 5)
        {
            makeMove(x, moves, k, k+7, k+14);
        }
        // if the row location is under 5 then
        // the move to be made will be at k value
        // k - 7, and k - 14
        if (row > 1)
        {
            makeMove(x, moves, k, k-7, k-14 );
        }
    }
    
} // end of nextMoves

// ==== Solved ===============================================================
//
//  Input:          x -    long long data type, that houses the whole board
//                         inside one integer...
//
//  Output:         bool - true if the board is solvable,
//                         false if it wasn't
//
//  Description:           Function takes as input a board and sees if the
//                         board has been solved.  It does this by seeing if
//                         the board only has one peg left in a valid postion
//                         and if so return true.  However if it is not any
//                         of the conditions then return false, indicating that
//                         the board hasn't been solved yet to the caller.
//
//
// ===========================================================================

bool Solved(long long x)
{
    
    int counter = 0;
    
    // loop through 7x7 board 0-48
    for (int j = 0; j < 49; j++)
    {
        // if there is a peg in this location then
        // add to the counter and check if the postion
        // is valid just in case
        if (isPeg(x, j))
        {
            // this is valid as bool equates to 1 or 0
            // so if valid and 1 then coutner += 1
            counter += ((validPos(j)) && 1);
        }
        // There isn't a peg in this location of the board
        // so check also if this is a valid spot just in case and
        // statement should always return false so 0.
        // counter += 0
        else
        {
            counter += ((validPos(j)) && 0);
        }
    }
    
    // if the counter is 1 then the board board is already solved due to one Peg
    return counter == 1;
    
} // end of Solved

// ==== Solve =================================================================
//
//  Input:          x -         long long data type, The board itself in one
//                              variable
//
//                  solution -  a vector of type Moves structure that stores
//                              all the moves to be made for the board
//
//  Output:         bool -      true if the board was solved, false if it wasn't
//
//  Descrption:                 Function tries to solve the board with the
//                              moves that are determined based of peg
//                              locations.  However first it must check to see
//                              if the board is solved already by calling the
//                              Solved function, if it returns true then the
//                              board is already solved but if false then the
//                              board needs to be solved.  Since it needs to be
//                              solved then get the nextMoves that it can make
//                              and loop through them putting them into the
//                              board.  While also checking to see if it has
//                              been solved, if so then return true for being
//                              solved if not continue until it gets through
//                              all the moves.  If the moves were not enough
//                              to solve the board then the board is unsolvable
//                              so return false, indicating that it could not
//                              be solved to the caller.
//
// ============================================================================

bool Solve(long long x, vector<Move>& solution)
{
    
    // if the board is already solved
    if (Solved(x))
    {
        
        // the board is already solved so return true
        return true;
    }
    
    // Call nextMoves to get the next moves to do if any...
    vector<Move> currMoves;
    nextMoves(x, currMoves);
    
    // NOTE: DID NOT PUT A MAKEMOVES CALL IN THIS FUNCTION
    //       DUE TO CALL BEING MADE WHEN NEXTMOVES IS
    //       GENERATED.
    
    // for every moves obj available put in m
    for (auto m: currMoves)
    {
        
        if (Solve(m.board, solution))
        {
            
            // insert the m with the updated moves and such into solution
            solution.insert(solution.begin(), m);
            
            // function was able to solve the board
            return true;
            
        }
        
    } // end of for
    
    // function was unable to find a solution so return false
    return false;
    
} // end of Solve

// ==== buildBoard =============================================================
//
//  Input:          FileName - string data type that houses the name of the file
//                             that houses the peg locations for the board
//
//  Output:         long long - The board that has all the peg locations on it
//                              to be used by the program to solve...
//
//  Description:    Function will build a board from the specified peg locations
//                  given by the user.  In using this it will only work if the
//                  file was able to properly open.  While the file still has
//                  input to feed it will then check through the file to see
//                  if there is any punctuation marks, and if so delete those
//                  marks from the file and get the new size of the file for
//                  the loop.  next it will see all that is within those lines
//                  in order to see which positions the pegs need to be placed
//                  into.  When finished it will return the board with all the
//                  pegs placed properly into the board.
//
//
// =============================================================================

long long buildBoard(string FileName)
{
    
    // Variables
    
    ifstream input;
    int postion;
    int length;
    long long board = 0; // long long for 64
    string line;
    
    input.open(FileName);
    
    // If the file was able to be opened without errors
    if (input.is_open())
    {
        
        cout << "\nBoard: ( ";
        
        // While input file still has stuff to give...
        while (getline(input, line))
        {
            
            length = line.size();
            
            // loops through whole line
            for (int i = 0; i < length; i++)
            {
                // if you have found a punctuation...',','{', etc.
                if (ispunct(line[i]))
                {
                    // erase the mark
                    line.erase(i--, 1);
                    length = line.size();
                }
                
            } // end of for loop
            
            // initialize stream with line
            istringstream ss(line);
            
            // While the inards of ss ca still output
            while (ss >> postion)
            {
                
                setPeg(board, postion);
                
                cout << postion << " ";
                
            } // end of while
            
        } // end of while
        
    } // end of if
    
    cout << ")\n";
    
    // Close the file
    input.close();
    
    // Return edited board
    return board;
    
} // end of buildBoard


// ==== hsolve =================================================================
//
//  Input:          x - a board of type long long that houses all of the board
//
//                  solution - a vectory of type Move that is referenced to
//                             caller and houses the solution moves to the board
//
//                  H - a HashTable vector of type lon long that houses the
//                      hash table
//
//  Output:         bool - true if solved, false if not
//
//  Description:    Function tries to solve the board with the
//                  moves that are determined based of peg
//                  locations.  However first it must check to see
//                  if the board is solved already by calling the
//                  Solved function, if it returns true then the
//                  board is already solved but if false then the
//                  board needs to be solved.  Since it needs to be
//                  solved then get the nextMoves that it can make
//                  and loop through them putting them into the
//                  board.  While also checking to see if it has
//                  been solved, if so then return true for being
//                  solved if not continue until it gets through
//                  all the moves.  If the moves were not enough
//                  to solve the board then the board is unsolvable
//                  so return false, indicating that it could not
//                  be solved to the caller.  This function is different than
//                  the solve function by which:
//
//                  (a) before making a recursive call, search the hash table
//                      to see if the current position y has been searched
//                      before (and has failed) and
//                  (b) insert the board into the hash table when the recursive
//                      call returns false so that future search from that
//                      position can be avoided.
//
//
// =============================================================================

bool hSolve(long long x, vector<Move>& solution, HashTable<long long>& H)
{
    
    // if the board is already solved then return true for solved
    if (Solved(x))
    {
        return true;
    }
    
    // Create a new move vector that will house the
    // next moves to be executed
    vector<Move> currMoves;
    nextMoves(x, currMoves);
    
    // loop for every moves that is in the vector
    for (auto m: currMoves)
    {
        
        // if H doesn't contain the updated board
        if (!H.contains(m.board))
        {
            // if the board was solved in the next call of hsolve then
            // record the solution to solution vector and return true
            if (hSolve(m.board, solution, H))
            {
                
                solution.insert(solution.begin(), m);
                return true;
                
            }
            else
            {
                
                H.insert(m.board);
                
            }
            
        } // end of if
        
    } // end of for
    
    // if the was unable to be solved
    // by the open hashing then return false
    // for being unsolved.
    return false;

} // end of hSolve


// ==== CHSolve ================================================================
//
//  Input:          x - a board of type long long that houses all of the board
//
//                  solution - a vectory of type Move that is referenced to
//                             caller and houses the solution moves to the board
//
//                  H - a DoubleHashTable vector of type long long that
//                      houses the hash table
//
//  Output:         bool - true if solved, false if not
//
//  Description:    Function tries to solve the board with the
//                  moves that are determined based of peg
//                  locations.  However first it must check to see
//                  if the board is solved already by calling the
//                  Solved function, if it returns true then the
//                  board is already solved but if false then the
//                  board needs to be solved.  Since it needs to be
//                  solved then get the nextMoves that it can make
//                  and loop through them putting them into the
//                  board.  While also checking to see if it has
//                  been solved, if so then return true for being
//                  solved if not continue until it gets through
//                  all the moves.  If the moves were not enough
//                  to solve the board then the board is unsolvable
//                  so return false, indicating that it could not
//                  be solved to the caller.  This function is different than
//                  the solve function by which:
//
//                  (a) before making a recursive call, search the hash table
//                      to see if the current position y has been searched
//                      before (and has failed) and
//                  (b) insert the board into the hash table when the recursive
//                      call returns false so that future search from that
//                      position can be avoided.
//
//                  This is also different from hSolve by which this uses
//                  quadratic probing to solve the board.
//
//
// =============================================================================

bool CHSolve(long long x, vector<Move>& solution, DoubleHashTable<long long>& H)
{
    
    // if the board is already solved then return true for solved
    if (Solved(x))
    {
        return true;
    }
    
    // Create a new move vector that will house the
    // next moves to be executed
    vector<Move> currMoves;
    nextMoves(x, currMoves);
    
    // loop for every moves that is in the vector
    for (auto m: currMoves)
    {
        
        // if H doesn't contain the updated board
        // contains is where the Quadratic Probing happens
        if (!H.contains(m.board))
        {
            // if the board was solved in the next call of hsolve then
            // record the solution to solution vector and return true
            if (CHSolve(m.board, solution, H))
            {
                
                solution.insert(solution.begin(), m);
                return true;
                
            }
            else
            {
                
                H.insert(m.board);
                
            }
            
        } // end of if
        
    } // end of for
    
    // if the was unable to be solved
    // by the open hashing then return false
    // for being unsolved.
    return false;

    
} // end of CHSolve






