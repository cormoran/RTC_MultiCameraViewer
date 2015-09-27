// -*- C++ -*-
/*!
 * @file  MultiCameraViewer.h
 * @brief MultiCameraViewer
 * @date  $Date$
 *
 * $Id$
 */

#ifndef MULTICAMERAVIEWER_H
#define MULTICAMERAVIEWER_H

#include <rtm/idl/BasicDataTypeSkel.h>
#include <rtm/idl/ExtendedDataTypesSkel.h>
#include <rtm/idl/InterfaceDataTypesSkel.h>

// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="port_stub_h">
// </rtc-template>

using namespace RTC;

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>

#include<mutex>
#include<opencv2/opencv.hpp>

class MultiCameraBase{
public:
    bool isActive(){return is_active_;}
    bool isNew(){
        bool ret=is_new_;
        is_new_=false;
        return ret;
    }
    //void setHeight(int height){height_=height;}
    //void setWidth(int width){width_=width;}
    
    virtual cv::Mat getImage()=0;
protected:
    bool is_active_;
    bool is_new_;
    //int height_=480;
    //int width_=640;
};


class MultiCameraViewer
  : public RTC::DataFlowComponentBase,public MultiCameraBase
{
 public:
    MultiCameraViewer(RTC::Manager* manager);
    ~MultiCameraViewer();
    virtual RTC::ReturnCode_t onInitialize();
    virtual RTC::ReturnCode_t onFinalize();
    virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);
    virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);
    virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);
    
    virtual cv::Mat getImage();
protected:
    int m_port_num;
    RTC::CameraImage m_image;
    InPort<RTC::CameraImage> m_imageIn;
    
    
    std::mutex image_mutex_;
    cv::Mat image_;
private:
};


extern "C"
{
  DLL_EXPORT void MultiCameraViewerInit(RTC::Manager* manager);
};

#endif // MULTICAMERAVIEWER_H
