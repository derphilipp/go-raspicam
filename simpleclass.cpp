#ifndef SIMPLECLASS_CPP
#define SIMPLECLASS_CPP

#include "simpleclass.h" // Include the main C/C++ program

using namespace std;
using namespace cv;

Simpleclass::Simpleclass(){
     tuple<unsigned char*, int, int> result = stovecam.get();
     image_data = get<0> (result);
     image_data_length = get<1> (result);
     bright_pixels = get<2> (result);
}

unsigned char * Simpleclass::getImage(){
    return image_data;
}

int Simpleclass::getImageLength(){
    return image_data_length;
}

int Simpleclass::getBrightPixels(){
    return bright_pixels;
}


#endif
