#ifndef MULTICAMERAWINDOW_HPP
#define MULTICAMERAWINDOW_HPP

#include<opencv2/opencv.hpp>
#include<string>
#include<vector>


#define MULTI_CAMERA_WINDOW_MAX_IMAGE_NUM 9

class MultiCameraWindow{
public:
    MultiCameraWindow(std::string name,int width,int height);
    virtual ~MultiCameraWindow();
    
    void Rename(std::string name);
    void ResizeWindow(int width,int height);
    void ResizeImageArray(int size);
    void UpdateImage(int index,const cv::Mat &image);
    
protected:
    
private:
    std:: string name_;
    int width_;
    int height_;
    int image_num;
    cv::Mat window_image_;
    
    void RenderWindow(); //現在のwindow_image_を画面に反映
};


#endif