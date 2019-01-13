// ===================================================================
// Programmer: Johnathan Soto
// Program: Lab5.cpp
// Language: C++
// Description: The goal of this project is to find the shortest
//              path through a maze. The maze is represented by a
//              black and white image in which the path is not
//              allowed to go through any black pixel. We can view
//              the maze as a graph in which each white pixel is a
//              vertex and the white pixels among its 4 neighbors
//              to N, S, E and W are connected by an edge. Given a
//              starting vertex (pixel) s and a destination vertex t,
//              the goal is to find the shortest path from s to t.
//              The output will be an image in which the pixels on
//              the shortest path from s to t will be changed to red.
//              Your program will take as input a file name containing
//              the image, and the x and y coordinates of s and t, and
//              will create an image in which the shortest path is
//              drawn. It will also output two more quantities on the
//              console: the length of the shortest path from the
//              starting pixel to the goal pixel and the total number
//              of pixels that entered the queue.
//
//
//
//
// ===================================================================

#include <iostream>
#include <limits>
#include "EasyBMP.h"
using namespace std;

// Global Variable
const int MSIZE = 100000;

// Classes
class point
{
private:
    int x;
    int y;
    
public:
    
    point()
    {
        x = 0;
        y = 0;
    }
    
    point(int p, int q)
    {
        x = p;
        y = q;
    }
    
    int getx()
    {
        return x;
    }
    
    int gety()
    {
        return y;
    }
    void setx(int i)
    {
        x = i;
    }
    void sety(int j)
    {
        y = j;
    }
}; //  end of point class

class queue
{
    
private:
    point* Q[MSIZE];
    
    int front, rear, size;
    
public:
    queue()
    {
        // initialize an empty queue
        front = 0; rear = 0; size = 0;
        for (int j=0; j < MSIZE; ++j)
            Q[j] = 0;
    }
    
    void insert(point * x)
    {
        if (size != MSIZE)
        {
            size++;
            if (rear == MSIZE)
                rear = 0;
            Q[rear] = x;
            rear++;
        }
    }
    
    point del()
    {
        point temp;
        
        // if the queue has something to give take it...
        if (size != 0)
        {
            
            if (front == MSIZE)
                front = 0;
            temp.setx(Q[front]->getx());
            temp.sety(Q[front]->gety());
            
            size--;
            front++;
            return temp;
        }
        //else it has nothing left to give
        // return NULL should never execute unless
        // trying to delete an empty queue so give them NULL!
        return temp;
    }
    
    bool isEmpty()
    {
        return (size == 0);
    }
}; // end of queue class

// ==== End of Classes ===================================================

// Prototypes
void colorToGray(BMP& Output);
void BFS(BMP& input, BMP& output, int s[], int t[], int counter);

// Main ==================================================================
int main(int argc, char* argv[])
{
    
    // Variables
    BMP myImage;
    BMP myOutput;
    int Entry[2];
    int Exit[2];
    int count;
    
    myImage.ReadFromFile(argv[1]); // gets the input file
    // Alter image
    colorToGray(myImage); // Image is now black and white
    
    // Ask user for starting point vertice and exit vertice
    cout << "What is the entry/starting X-coordinate? ";
    cin >> Entry[0];
    cout << "\nWhat is the entry/starting Y-coordinate? ";
    cin >> Entry[1];
    cout << "\nWhat is the exit X-coordinate? ";
    cin >> Exit[0];
    cout << "\nWhat is the exit Y-coordinate? ";
    cin >> Exit[1];
    
    // User input is acceptable to the program for coords...
    if ((Entry[0] >= 0 && Entry[0] < myImage.TellWidth()) &&
        (Entry[1] >= 0 && Entry[1] < myImage.TellHeight()) &&
        (Exit[0] >= 0 && Exit[0] < myImage.TellWidth()) &&
        (Exit[1] >= 0 && Exit[1] < myImage.TellHeight()))
    {
        
        RGBApixel temp = myImage.GetPixel(Entry[0], Entry[1]);
        RGBApixel temp2 = myImage.GetPixel(Exit[0], Exit[1]);
        // If the starting and exit pixel is white then continue
        if (((temp.Red == 255 ) && ( temp.Blue == 255) && ( temp.Green == 255)) &&
            (( temp2.Red == 255 ) && ( temp2.Blue == 255) && (temp2.Green == 255)))
        {
            // Call BFS if it was successful then True is passed along else False for failure
            BFS(myImage, myOutput, Entry, Exit, count);
            
        } // end of 2nd if
        
        else
        {
            cout << "The coordinates you have inputed are black and not white...\nEnding Program...\n";
        }
        
    } // end of 1st if
    
    return 0;
    
} // end of main ========================================================================

// ==============================================================================
//  Input:          BMP Referenced image (output) - Image to be converted to a
//                                                  black and white image
//
//  Output:         None
//
//  Description:    Converts the BMP image to black and white
//
// ==============================================================================

void colorToGray(BMP & Output)
{
    int picWidth = Output.TellWidth();
    int picHeight = Output.TellHeight();
    Output.SetBitDepth(1); //compression happens here
    
    for (int i = 0; i < picWidth-1; ++i)
    {
        for (int j = 0; j < picHeight-1; ++j)
        {
            int col = 0.1* Output(i, j)->Blue +0.6*Output(i,j)->Green +0.3* Output(i,j)->Red;
            if (col > 127)
            {
                Output(i,j)->Red = 255;
                Output(i,j)->Blue = 255;
                Output(i,j)->Green = 255;
                
            }
            else
            {
                Output(i,j)->Red = 0;
                Output(i,j)->Blue = 0;
                Output(i,j)->Green = 0;
            }
        } // end of 2nd for
    } // end of 1st for
    
} // end of colorToGray

//=================================================================================
//  Input -         input:   The input image from user to be solved via BFS
//
//                  output:  A blank image that will house a copy of the input
//                           image and will have the shortest path on the image
//
//                  start[]: The starting coordinate for the maze: start[0] = x,
//                           start[1] = y
//
//                  end[]:   The end coordinate for the maze: end[0] = x, end[1] = y
//
//                  count: integer variable that counts how many items have been
//                           inserted into the queue
//
//  Output -        1:  If function succeeded
//                  0:  If function fails to find exit or queue is full at start
//
//  Description -   Gets a maze BMP image and tries to find the shortest path to
//                  the exit.  User will provide starting coordinates and exit
//                  coordinates.  If no solution is found function will say so
//                  and return false for function not executing shortest path.
//                  Will generate image of the maze with shortest path in red for
//                  the user to see in an output BMP image reserved in output
//                  variable respectivily.
//
//
//=================================================================================


void BFS(BMP& input, BMP& Output, int start[], int end[], int count)
{
    // Variables
    int w = input.TellWidth();
    int h = input.TellHeight();
    point* p[h][w];
    point* u = new point();
    point* v = new point();
    
    count = 0;
    
    // initialize p's values
    for(int j = 0; j < h; j++)
    {
        for (int k = 0; k < w; k++)
        {
            p[j][k] = new point();
        }
    }
    
    //initialize Q
    queue Q;
    
    //Q->insert(s);
    point* s = new point(start[0],start[1]);
    Q.insert(s);
    count++;
    
    // Output = copy(input);
    Output.SetSize(input.TellWidth(), input.TellHeight());
    RangedPixelToPixelCopy(input, 0, input.TellWidth(), input.TellHeight(), 0, Output, 0, 0);
    Output.SetBitDepth(24);
    
    //set visited [j][k] false for all j, k
    bool visited[h][w];
    for(int j = 0; j < h; j++)
    {
        for (int k = 0; k < w; k++)
        {
            visited[j][k] = false;
        }
    }
    // visited[s] = true;
    visited[start[1]][start[0]] = true;
    
    // set d[s] = 0 and d[u] = MaxInt for all u
    int distance[h][w];
    for(int j = 0; j < h; j++)
    {
        for (int k = 0; k < w; k++)
        {
            distance[j][k] = 0;
        }
    }
    distance[start[1]][start[0]] = 0;
    
    // while the queue isn't empty and the end point hasn't been visited
    while (!(Q.isEmpty()) && !(visited[end[1]][end[0]]))
    {
        // Get the deleted point to u from first of the queue
        *u = Q.del();
        
        // EasyBMP checker to see if coords are within bounds: used for each direction
        /* if( i >= Width )
         { i = Width-1; Warn = true; }
         if( i < 0 )
         { i = 0; Warn = true; }
         if( j >= Height )
         { j = Height-1; Warn = true; }
         if( j < 0 )
         { j = 0; Warn = true; }
         */
        if (u->getx() < 0 || u->getx() >= w || u->gety()-1 >= h || u->gety()-1 < 0)
        {
            // coords are not valid continue on no code needed here
            // just using else if to not get warnings from the EasyBMP file
        }
        // if northern point has yet to be visited and
        // is not a wall (i.e. pixel isn't black)
        else if ( !(visited[u->gety()-1][u->getx()]) &&
                 (Output( u->getx(), u->gety()-1)->Red != 0 &&
                  Output( u->getx(), u->gety()-1)->Green != 0 &&
                  Output( u->getx(), u->gety()-1)->Blue != 0) )
        {
            // Set the North coord
            point* North = new point();
            North->setx(u->getx());
            North->sety(u->gety()-1);
            
            // visted[North] = true;
            visited[North->gety()][North->getx()] = true;

            // d[North] = d[u] + 1;
            distance[North->gety()][North->getx()] = distance[u->gety()][u->getx()] + 1;
            
            //p[North] = u;
            p[North->gety()][North->getx()]->setx(u->getx());
            p[North->gety()][North->getx()]->sety(u->gety());
            
            // Q->inset(North)
            Q.insert(North);
            count++;
            
        }
        if (u->getx()-1 < 0 || u->getx()-1 >= w || u->gety() >= h || u->gety() < 0)
        {
            // coords are not valid continue on no code needed here
            // just using else if to not get warnings from the EasyBMP file
        }
        // if eastern point has yet to be visited and
        // is not a wall (i.e. pixel isn't black)
        else if ( !(visited[u->gety()][u->getx() - 1]) &&
                 (Output( u->getx()-1, u->gety())->Red != 0 &&
                  Output( u->getx()-1, u->gety())->Green != 0 &&
                  Output( u->getx()-1, u->gety())->Blue != 0) )
        {
            
            // Set East coord
            point* East = new point();
            East->setx(u->getx()-1);
            East->sety(u->gety());
            
            // visted[East] = true;
            visited[East->gety()][East->getx()] = true;
            // d[East] = d[u] + 1;
            distance[East->gety()][East->getx()] = distance[u->gety()][u->getx()] + 1;
            
            //p[East] = u;
            p[East->gety()][East->getx()]->setx(u->getx());
            p[East->gety()][East->getx()]->sety(u->gety());
            
            // Q->insert(East)
            Q.insert(East);
            count++;
            
        }
        
        if (u->getx() < 0 || u->getx() >= w || u->gety()+1 >= h || u->gety()+1 < 0)
        {
            // coords are not valid continue on no code needed here
            // just using else if to not get warnings from the EasyBMP file
        }
        // if Southern point has yet to be visited and
        // is not a wall (i.e. pixel isn't black)
        else if ( !(visited[u->gety() + 1][u->getx()]) &&
                 (Output( u->getx(), u->gety()+1)->Red != 0 &&
                  Output( u->getx(), u->gety()+1)->Green != 0 &&
                  Output( u->getx(), u->gety()+1)->Blue != 0) )
        {
            
            // Set South Coord
            point* South = new point();
            South->setx(u->getx());
            South->sety(u->gety()+1);
            
            // visted[South] = true;
            visited[South->gety()][South->getx()] = true;
            // d[South] = d[u] + 1;
            distance[South->gety()][South->getx()] = distance[u->gety()][u->getx()] + 1;
            
            //p[South] = u;
            p[South->gety()][South->getx()]->setx(u->getx());
            p[South->gety()][South->getx()]->sety(u->gety());
            
            // Q->insert(South)
            Q.insert(South);
            count++;
            
        }
        if (u->getx()+1 < 0 || u->getx()+1 >= w || u->gety() >= h || u->gety() < 0)
        {
            // coords are not valid continue on no code needed here
            // just using else if to not get warnings from the EasyBMP file
        }
        // if western point has yet to be visited and
        // is not a wall (i.e. pixel isn't black)
        else if ( !(visited[u->gety()][u->getx() + 1]) &&
                 (Output( u->getx()+1, u->gety())->Red != 0 &&
                  Output( u->getx()+1, u->gety())->Green != 0 &&
                  Output( u->getx()+1, u->gety())->Blue != 0) )
        {
            
            // Set West Coord
            point* West = new point();
            West->setx(u->getx()+1);
            West->sety(u->gety());
            
            // visted[West] = true;
            visited[West->gety()][West->getx()] = true;
            // d[West] = d[u] + 1;
            distance[West->gety()][West->getx()] = distance[u->gety()][u->getx()] + 1;
            
            //p[West] = u;
            p[West->gety()][West->getx()]->setx(u->getx());
            p[West->gety()][West->getx()]->sety(u->gety());
            
            // Q->insert(West)
            Q.insert(West);
            count++;
            
        }
        
    }// end of while
    
    // if the end vertex has been visited continue..
    if(visited[end[1]][end[0]])
    {
        v->setx(end[0]);
        v->sety(end[1]);
        
        // While v's vertex doesn't equal s's vertex
        while (v != s)
        {
            // if x or y is 0 go in...cause you broken...
            if (v->getx() == 0 && v->gety() == 0)
            {
                break;
            }
            
            //set pixel color at v to Red
            Output( v->getx(), v->gety())->Red = 255;
            Output( v->getx(), v->gety())->Green = 0;
            Output( v->getx(), v->gety())->Blue = 0;
            Output( v->getx(), v->gety())->Alpha = 0;
            
            // v = p[v];
            v->setx(p[v->gety()][v->getx()]->getx());
            v->sety(p[v->gety()][v->getx()]->gety());
            
        } // end of while
        
        // write image to output takes place in main due to the destination being stored in argv[2]
        Output.WriteToFile("output.bmp");
        
        // output d[t] and count;
        cout << "\nThe shortest distance is " << distance[end[1]][end[0]]
        << "\nand the number of integers in the Queue is " << count << endl;
        
    } // end of if
    
    else // No path found from starting vertex to the end vertex
    {
        
        cout << "\nNo path from (" << start[0] << ", " << start[1] << ")"
        << "to (" << end[0] << ", " << end[1] << ")\n\n";
        
    } //end if-else
    
} // end of BFS




