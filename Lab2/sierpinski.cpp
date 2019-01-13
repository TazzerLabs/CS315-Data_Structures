// =================================================
// Programmer: Johnathan Soto
// Program: sierpinski.cpp
//
// Description: Generate the sierpinski triangle
//              and output to file
//
// =================================================


#include "EasyBMP.h"
#include <stdlib.h>
using namespace std;

void sierpinski(BMP& output);

int main( int argc, char* argv[])
{
    
    // Create a blank 256X256 white image with 32 Bit depth
    BMP Image;
    Image.SetSize(256,256);
    Image.SetBitDepth(32);
    
    sierpinski(Image);
    Image.WriteToFile("sierpinski.bmp");
    return 0;
    
} // end of main


// =====================================================================
//  Input - BMP referenced variable that will house the
//          sierpinski triangle generated
//
//  Output - none
//
//  Description: Start with an image containing white
//               background of size 256 by 256. The vertices of the
//               outermost triangle (labeled X, Y and Z in the figure
//               below) are chosen as inputs to the program. The
//               values of X, Y and Z are specified later. In addition,
//               one point (P0) inside the triangle will be specified.
//               The following algorithm generates the successive points
//               P1, P2, ... etc: Select one of the vertices X, Y or Z
//               randomly; the mid-point of the line segment connecting
//               this selected vertex and Pi gives the next point Pi+1.
//               Repeat this process a large number of times (10000 to be
//               specific), change the color of the points P(0), P(1),
//               ..., P(10000) to red, and save the resulting image as
//               ‘sierpinski.bmp’
//
//
// ======================================================================

void sierpinski(BMP& output)
{

    int picWidth = output.TellWidth();
    int picHeight = output.TellHeight();
    
    int X[] = {128, 5};
    int Y[] = {5, 251};
    int Z[] = {251, 251};
    int P[] = {171, 34};
    
    for (int i = 0; i < 10000; i++)
    {
        int random = rand() % 3; // 0-2
        
        if (random == 0) // X
        {
            int x = (P[0] + X[0]) / 2;
            int y = (P[1] + X[1]) / 2;
            
            output(x, y)->Red = 255;
            output(x, y)->Green = 0;
            output(x, y)->Blue = 0;
            output(x, y)->Alpha = 0;
            
            P[0] = x;
            P[1] = y;
            
        }
        else if (random == 1) // Y
        {
            int x = (P[0] + Y[0]) / 2;
            int y = (P[1] + Y[1]) / 2;
            
            output(x, y)->Red = 255;
            output(x, y)->Green = 0;
            output(x, y)->Blue = 0;
            output(x, y)->Alpha = 0;
            
            P[0] = x;
            P[1] = y;
            
        }
        else // Z
        {
            int x = (P[0] + Z[0]) / 2;
            int y = (P[1] + Z[1]) / 2;
            
            output(x, y)->Red = 255;
            output(x, y)->Green = 0;
            output(x, y)->Blue = 0;
            output(x, y)->Alpha = 0;
            
            P[0] = x;
            P[1] = y;
            
        }
        
    } // end of for loop
    
} // end of sierpenski(BMP& output;)

