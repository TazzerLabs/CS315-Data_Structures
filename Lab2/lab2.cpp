// ===================================================
// Programmer: Johnathan Soto
// Programs:   main.cpp
// Language: C++
// Description: Lab2 for CS 315 that hold the
//              generation of a 256x256 checkerboard
//              with 8 rows and 8 columns, sierpinski
//              triangle that goes to 10000 iterations
//              , also the tiled image of a bmp file
//              that fills the dimensions of the prior
//              image with tiled scaled versions
//              getting smaller till the image is a
//              2x2
//
// ===================================================

#include "EasyBMP.h"
using namespace std;

// Function Prototypes
void checkerBoard(BMP& output);
void sierpinski(BMP& output);
BMP tile (BMP & input, BMP & output);


int main( int argc, char* argv[])
{
    
    // ---- Checkerboard block ----
    
    BMP myImage;
    myImage.SetSize(256,256);
    myImage.SetBitDepth(32);
    
    checkerBoard(myImage);
    myImage.WriteToFile("board.bmp");
    
    // ---- end of checkerboard block ----
    
    // ---- Sierpinski block ----
    
    // Create a blank 256X256 white image with 32 Bit depth
    BMP Image;
    Image.SetSize(256,256);
    Image.SetBitDepth(32);
    
    sierpinski(Image);
    Image.WriteToFile("sierpinski.bmp");
    
    // ---- end of sierpinski block ----
    
    // ---- tile block ----
    
    // Create BMP var to store input image
    BMP myPhoto;
    myPhoto.ReadFromFile("in.bmp");
    
    // Create BMP var to take in copy of original image
    BMP myOutput = myPhoto;
    
    // Should generate tiled image of original inside of myOutput
    tile (myPhoto, myOutput);
    
    // Write to output file
    myOutput.WriteToFile("tile.bmp");
    
    // ----- end of tile block
    
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


// ============================================================================
//
// Parameters:      BMP& input - Referenced BMP image at start will house
//                               original image, due to recursion,
//                               will be scaled to 50%
//
//                  BMP& output - Referenced BMP image to be written out to
//                                designated output file, due recursion
//                                will be accumulating tiled images of the
//                                original and postioning them accordingly
//
//
// return value:    a tiled image of the original image
//
//
// Description:     A function that scales the input image, copies to
//                  output BMP variable, then recursively calls itself
//                  and to scale input again and copying till the image is
//                  2x2.  When popping back up copy new output to output
//                  and postition iages to the till first call.  Then return
//                  tiled output image to main.  Instead of doing for loop
//                  to copy pixel by pixel to another BMP image, just use the
//                  EasyBMP function RangedPixelToPixelCopy so image can be
//                  copied from right to left and up to down all to another
//                  EMP variable.  This also allows the average of the pixels
//                  [2k,2k], [2k, 2k+1], [2k+1, 2k] and [2k+1, 2k+1] so that
//                  the tiling can be scaled appropriately.
//
//
// ============================================================================

BMP tile (BMP & input, BMP & output)
{
    // Set output to the input size
    output.SetSize( input.TellWidth (), input.TellHeight ());
    
    // Base case:
    if (input.TellWidth() == 1 && input.TellHeight() == 1)
    {
        
        // copy input image from left to right input image: (0 - 1)
        // up to down input image: (1 - 0)
        //to output at output's image: (0, 0)
        RangedPixelToPixelCopy (input, 0, 1, 1, 0, output, 0, 0);
        
        // pop modify output to caller
        return output;
    }
    
    // Dummy variables to be effected by recursion so that
    // the final output will have all recursive tiled images
    // copied into the appropriate postions in the BMG file
    BMP sub;
    BMP subber;
    
    // Set the dummy variable to be the input BMG Dimmensions
    sub.SetSize(input.TellWidth(), input.TellHeight());
    subber.SetSize(input.TellWidth(), input.TellHeight());
    
    // copy input image from left to right (0-width of image), up to down (height of image - 0)
    // to sub BMG variable at (0,0)
    RangedPixelToPixelCopy(input, 0, input.TellWidth(), input.TellHeight(), 0, sub, 0, 0);
    
    // Scale  sub image to be 1/4 of image
    Rescale(sub, 'p', 50);
    
    // copy sub BMG image from left to right (0 - width of image), up to down (height of image - 0)
    // to output BMG variable at (0, output height of image divided by 2)
    RangedPixelToPixelCopy(sub, 0, sub.TellWidth(), sub.TellHeight(), 0, output, 0, output.TellHeight()/2);
    
    // copy the new output BMG image from (0 - width of image), up to down (height of image - 0)
    // to subber BMG variable at (0,0)
    RangedPixelToPixelCopy(output, 0, output.TellWidth(), output.TellHeight(), 0, subber, 0, 0);
    
    // Recursion passing the modified sub and subber, sub being input and subber output
    tile(sub, subber);
    
    // copy after recursion subber from left to right (0 - width of image), up to down (height of image - 0)
    // to output BMG variable at (width of image divided by 2 - 0)
    RangedPixelToPixelCopy(subber, 0, subber.TellWidth(), subber.TellHeight(), 0, output, ((output.TellWidth())/2), 0);
    
    // copy after previous function call - output from left to right (width of image divided by 2 - 3 times width of image divided by 4)
    // up to down (height of image divided by 2 - 0) to output at (0,0) of image
    RangedPixelToPixelCopy(output, ((output.TellWidth())/2), (3*(output.TellWidth())/4), ((output.TellHeight())/2), 0, output, 0, 0);
    
    // copy after previous function call - output from left to right (width of image divided by 2 - 3 times width of image divided by 4)
    // up to down (height of image divided by 2 - 0) to output at (width of image divided by 4, 0) of image
    RangedPixelToPixelCopy(output, ((output.TellWidth())/2), (3*(output.TellWidth())/4), ((output.TellHeight())/2), 0, output, (output.TellWidth())/4, 0);
    
    // copy after previous function call - output from left to right (width of image divided by 2 - width of image)
    // up to down (height of image divided by 2 - height of image divided by 4)
    // to output at (width of image divided by 2, height of image divided by 2)
    RangedPixelToPixelCopy(output, ((output.TellWidth())/2), output.TellWidth(), ((output.TellHeight())/2), ((output.TellHeight())/4),
                           output, (output.TellWidth())/2, (output.TellHeight())/2);
    
    // copy after previous function call - output from left to right (width of image divided by 2 - width of image)
    // up to down (height of image divided by 2 - height of image divided by 4)
    // to output at (width of image divided by 2, 3 times the height of image divided by 4)
    RangedPixelToPixelCopy(output, ((output.TellWidth())/2), output.TellWidth(), ((output.TellHeight())/2), ((output.TellHeight())/4),
                           output, (output.TellWidth())/2, 3*(output.TellHeight())/4);
    
    // return altered image to caller
    return output;
    
} // end of tile
