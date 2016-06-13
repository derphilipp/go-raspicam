#ifndef SIMPLECLASS_H
#define SIMPLECLASS_H
// File name: main_capture_class.h
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "camera.h"
#include <tuple>

class Simpleclass {
    public:
        Simpleclass();
        unsigned char *getImage();
        int getImageLength();
        int getBrightPixels();
    private:
        StoveCam stovecam;
        unsigned char * image_data;
        int image_data_length;
        int bright_pixels;

};

#endif
