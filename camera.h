#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <tuple>
#include <vector>

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class StoveCam {
public:
  StoveCam(){};

  std::tuple<unsigned char *, int> getCutout();
  cv::Mat takeCroppedImage();
  std::tuple<unsigned char *, int> getImageAsPng(cv::Mat &);
  std::tuple<unsigned char *, int, int> get();

private:
  int imagesize = 0;
  cv::Mat takeImage();

  cv::Mat cropImage(cv::Mat &image);

  int countBrightPixels(cv::Mat &image);

  cv::Mat imageBrightPixels(cv::Mat &image);

  // unsigned char* getImageAsPng(cv::Mat & image);
};

#endif
