
#include "MultiCameraWindow.hpp"
#include <iostream>
#include <cmath>

/* Public */

MultiCameraWindow::MultiCameraWindow(std::string name,int width,int height)
:name_(name),width_(width),height_(height)
{
    window_image_ = cv::Mat::zeros(height_, width_, CV_8SC3);
    RenderWindow();
}


MultiCameraWindow::~MultiCameraWindow()
{
    cv::destroyAllWindows();
}

void MultiCameraWindow::Rename(std::string name)
{
    cv::destroyWindow(name_);
    name_ = name;
    RenderWindow();
}


void MultiCameraWindow::ResizeWindow(int width, int height)
{
    if (width_ != width or height_ != height){
        width_=width;
        height_=height;
        window_image_ = cv::Mat::zeros(height_, width_, CV_8UC3);
        RenderWindow();
    }
}

void MultiCameraWindow::ResizeImageArray(int size){
    if (size<=0 or MULTI_CAMERA_WINDOW_MAX_IMAGE_NUM < size){
        std::cerr << "Error MultiCameraWIndow::ResizeImageArray : size must be between "
        << 0 << " and " << MULTI_CAMERA_WINDOW_MAX_IMAGE_NUM << std::endl;
        abort();
    }
    //clear window
    window_image_ = cv::Mat::zeros(window_image_.size(), CV_8UC3);
    image_num = size;
}

void MultiCameraWindow::UpdateImage(int index, const cv::Mat &image)
{
    int square_size = ceil(sqrt(image_num));
    int w = window_image_.cols / square_size;
    int h = window_image_.rows / square_size;
    
    int x = index % square_size;
    int y = index / square_size;
    cv::Rect roi_rect(w*x,h*y,w,h);

    //転写
    if (image.rows != h or image.cols != w){
        cv::Mat resized_img = cv::Mat(h,w,CV_8SC3);
        cv::resize(image, resized_img, resized_img.size());
        resized_img.copyTo(cv::Mat(window_image_,roi_rect));
    } else {
        image.copyTo(cv::Mat(window_image_,roi_rect));
    }
    RenderWindow();
}


/* Private */

void MultiCameraWindow::RenderWindow()
{
    cv::imshow(name_, window_image_);
}

