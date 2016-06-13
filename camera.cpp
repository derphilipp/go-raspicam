#ifndef CAMERA_CPP
#define CAMERA_CPP

#include "camera.h"
using namespace cv;
using namespace std;

tuple<unsigned char *, int, int> StoveCam::nextPicture() {
  auto img = takeImage();
  auto cropped_img = cropImage(img);
  auto image_as_png = getImageAsPng(cropped_img);
  int brightPixels = countBrightPixels(cropped_img);
  return {std::get<0>(image_as_png), std::get<1>(image_as_png), brightPixels};
}

Mat StoveCam::takeImage() {
  Mat frame;

  bool success = cap.read(frame);
  assert(success);
  assert(!frame.empty());

  return frame;
}

StoveCam::StoveCam() {
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 2592);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 1944);
  assert(cap.isOpened());
}

Mat StoveCam::cropImage(Mat &image) {
  // Setup a rectangle to define your region of interest
  Rect myROI(1182, 1287, 20, 20); // 0, 0, 2592, 1944);
  Mat croppedRef(image, myROI);
  Mat cropped;
  croppedRef.copyTo(cropped);
  return cropped;
}

Mat StoveCam::takeCroppedImage() {
  auto original_image = takeImage();
  auto image = cropImage(original_image);
  original_image.release();
  return image;
}

int StoveCam::countBrightPixels(Mat &image) {
  Mat bright_pixels;
  // auto LightOff = Scalar(180, 30, 30);
  auto LightOff = Scalar(180, 30, 30);
  auto LightOn = Scalar(255, 255, 255);
  inRange(image, LightOff, LightOn, bright_pixels);
  auto amount = countNonZero(bright_pixels);
  bright_pixels.release();
  return amount;
}

Mat StoveCam::imageBrightPixels(Mat &image) {
  Mat bright_pixels;
  // auto LightOff = Scalar(180, 30, 30);
  auto LightOff = Scalar(180, 30, 30);
  auto LightOn = Scalar(255, 255, 255);
  inRange(image, LightOff, LightOn, bright_pixels);
  return bright_pixels;
}

tuple<unsigned char *, int> StoveCam::getImageAsPng(Mat &image) {
  vector<uchar> buf;
  imencode(".jpg", image, buf, vector<int>());
  // encoded image is now in buf (a vector)
  int bufsize = buf.size();
  auto imageBuf = (unsigned char *)malloc(bufsize);
  // auto imageBuf = (unsigned char *) realloc(imageBuf, buf.size());
  memcpy(imageBuf, &buf[0], bufsize);
  return {imageBuf, bufsize};
}

tuple<unsigned char *, int> StoveCam::getCutout() {

  auto image = takeCroppedImage();
  return getImageAsPng(image);
}

#endif
