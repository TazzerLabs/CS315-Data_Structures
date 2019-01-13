// ===================================================
// Programmer: Johnathan Soto
// Program: tiled.cpp
// Language: C++
// Description: Create tiled image of input file and
//              output to the output file.
//
// ===================================================

#include <cstdlib>
#include "EasyBMP.h"
using namespace std;

// Prototypes
BMP tile (BMP & input, BMP & output);

int main (int argc, char* argv [])
{
    // Create BMP var to store input image
    BMP myPhoto;
    myPhoto.ReadFromFile(argv[1]);
    
    // Create BMP var to take in copy of original image
    BMP myOutput = myPhoto;
    
    // Should generate tiled image of original inside of myOutput
    tile (myPhoto, myOutput);
    
    // Write to output file
    myOutput.WriteToFile(argv[2]);
    
    
    return 0;
} // end of main

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
    
    //Rescale(sub, 'p', 50);
    
    for(int i = 0; i < x; i+=2)
    {
        for(int j = 0; j < y; j+=2)
        {
            RGBApixel color1 = input.GetPixel(i,j);
            RGBApixel color2 = input.GetPixel(i+1,j);
            RGBApixel color3 = input.GetPixel(i,j+1);
            RGBApixel color4 = input.GetPixel(i+1,j+1);
            Output2(i/2, j/2)->Red = (color1.Red + color2.Red + color3.Red + color4.Red) / 4;
            Output2(i/2, j/2)->Green = (color1.Green + color2.Green + color3.Green + color4.Green) / 4;
            Output2(i/2, j/2)->Blue = (color1.Blue + color2.Blue + color3.Blue + color4.Blue) / 4;
        }
    
    
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
