#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.h"
#include <ctime>
using namespace cv;
using namespace std;

tuple<unsigned char*, int, int > StoveCam::get(){
    cv::Mat img = takeImage();
    cv::Mat cropped_img = cropImage(img);
    std::tuple<unsigned char*, int> image_as_png = getImageAsPng(cropped_img);
    int brightPixels = countBrightPixels(cropped_img);
    return std::make_tuple (std::get<0>(image_as_png),std::get<1>(image_as_png), brightPixels);
}



cv::Mat StoveCam::takeImage(){
    cv::VideoCapture cap(0);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 2592);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1944);
    assert(cap.isOpened());

    Mat frame;
    bool success = cap.read(frame);
    assert(success);
    assert( !frame.empty() );

    return frame;
}

cv::Mat StoveCam::cropImage( cv::Mat & image){
    // Setup a rectangle to define your region of interest
    cv::Rect myROI(500, 500, 500, 500);
    //cv::Rect myROI(187, 693, 15, 15);
    cv::Mat croppedRef(image, myROI);
    cv::Mat cropped;
    croppedRef.copyTo(cropped);
    return cropped;
}

cv::Mat StoveCam::takeCroppedImage(){
    auto original_image = takeImage();
    auto image = cropImage(original_image);
    original_image.release();
    return image;
}

int StoveCam::countBrightPixels(cv::Mat & image){
    cv::Mat bright_pixels;
    //auto LightOff = cv::Scalar(180, 30, 30);
    auto LightOff = cv::Scalar(180, 30, 30);
    auto LightOn = cv::Scalar(255, 255, 255);
    cv::inRange(image, LightOff, LightOn, bright_pixels);
    auto amount = cv::countNonZero(bright_pixels);
    bright_pixels.release();
    return amount;
}

cv::Mat StoveCam::imageBrightPixels(cv::Mat & image){
    cv::Mat bright_pixels;
    //auto LightOff = cv::Scalar(180, 30, 30);
    auto LightOff = cv::Scalar(180, 30, 30);
    auto LightOn = cv::Scalar(255, 255, 255);
    cv::inRange(image, LightOff, LightOn, bright_pixels);
    return bright_pixels;
}

std::tuple<unsigned char*, int> StoveCam::getImageAsPng(cv::Mat & image){
    std::vector<uchar> buf;
    cv::imencode(".png", image, buf, std::vector<int>() );
    // encoded image is now in buf (a vector)
    int bufsize = buf.size();
    auto imageBuf = (unsigned char *) malloc( bufsize );
    //auto imageBuf = (unsigned char *) realloc(imageBuf, buf.size());
    memcpy(imageBuf, &buf[0], bufsize);
    return std::make_tuple(imageBuf, bufsize);
}

tuple<unsigned char*, int> StoveCam::getCutout(){

    auto image = takeCroppedImage();
    return getImageAsPng(image);
}

/*int StoveCam::getImageSize(){
  return imagesize;
  }*/



/*int main( int argc, char** argv )
  {
  auto image = takeCroppedImage();
  auto bright_pixels = imageBrightPixels(image);

//auto image = takeCroppedImage();
auto amount = countBrightPixels(bright_pixels);
cout<<"Amount of bright pixels" << amount << endl;

namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
imshow( "Display window", image );                   // Show our image inside it.

waitKey(0);                                          // Wait for a keystroke in the window
return 0;
}
*/
#endif
