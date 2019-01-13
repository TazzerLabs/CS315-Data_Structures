// ===================================================
// Programmer: Johnathan Soto
// Program: checkerBoard.cpp
// Language: C++
// Description: Create a checkerboard that is 256x256
//              and have 8 rows and cols.
//
// ===================================================

#include "EasyBMP.h"
using namespace std;

void checkerBoard(BMP& output);

int main( int argc, char* argv[])
{
    
    BMP myImage;
    myImage.SetSize(256,256);
    myImage.SetBitDepth(32);
    
    checkerBoard(myImage);
    myImage.WriteToFile("board.bmp");
    return 0;
    
} // end of main


// ======================================================
//  Input - BMP variable that will house the checkerboard
//  Output - none
//
//  Description Create a checkerboard that is 256x256
//              and have 8 rows and cols.
//
// ======================================================

void checkerBoard(BMP& output)
{
    
    int picWidth = output.TellWidth();
    int picHeight = output.TellHeight();
    
    for (int i = 0; i < picWidth-1; i++)
    {
        
        for (int j = 0; j < picHeight-1; j++)
        {
            
            int row = i/32;
            int col = j/32;
        
            // if even for row and col = even
            if (row % 2 == 0  && col % 2 == 0) // red
            {
                
                output(i,j)->Red = 255;
                output(i,j)->Green = 0;
                output(i,j)->Blue = 0;
                output(i,j)->Alpha = 0;
                
            }
            // if odd on row and col = even
            else if (row % 2 != 0 && col % 2 != 0) // red
            {
                output(i,j)->Red = 255;
                output(i,j)->Green = 0;
                output(i,j)->Blue = 0;
                output(i,j)->Alpha = 0;
            }
            // else it's odd
            else // black
            {
                
                output(i,j)->Red = 0;
                output(i,j)->Green = 0;
                output(i,j)->Blue = 0;
                output(i,j)->Alpha = 0;
                
                 
            }
            
        } // end of 2nd for loop
        
    } // end of 1st for loop
    
} // end of checkerBoard(BMP& output);
