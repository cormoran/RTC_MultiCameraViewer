// -*- C++ -*-
/*!
 * @file  MultiCameraViewer.cpp
 * @brief MultiCameraViewer
 * @date $Date$
 *
 * $Id$
 */

#include "MultiCameraViewer.h"

// Module specification
// <rtc-template block="module_spec">
static const char* multicameraviewer_spec[] =
  {
    "implementation_id", "MultiCameraViewer",
    "type_name",         "MultiCameraViewer",
    "description",       "MultiCameraViewer",
    "version",           "1.0.0",
    "vendor",            "Kenya Ukai",
    "category",          "basic tool",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.port_num", "1",
    // Widget
    "conf.__widget__.port_num", "text",
    // Constraints
    ""
  };

MultiCameraViewer::MultiCameraViewer(RTC::Manager* manager)
  : RTC::DataFlowComponentBase(manager),
    m_imageIn("camera", m_image)
{
}

MultiCameraViewer::~MultiCameraViewer()
{
}



RTC::ReturnCode_t MultiCameraViewer::onInitialize()
{
    
    static InPort<RTC::CameraImage> m_imageIn2("camera2",m_image);

    addInPort("camera", m_imageIn);
    addInPort("camera2", m_imageIn2);
    
    bindParameter("port_num", m_port_num, "1");

  return RTC::RTC_OK;
}


RTC::ReturnCode_t MultiCameraViewer::onFinalize()
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t MultiCameraViewer::onActivated(RTC::UniqueId ec_id)
{
    is_active_ = true;
    is_new_ = false;
    return RTC::RTC_OK;
}


RTC::ReturnCode_t MultiCameraViewer::onDeactivated(RTC::UniqueId ec_id)
{
    is_active_ = false;
    return RTC::RTC_OK;
}


RTC::ReturnCode_t MultiCameraViewer::onExecute(RTC::UniqueId ec_id)
{
    if (m_imageIn.isNew()) {
        m_imageIn.read();
        
        image_mutex_.lock();
        if (image_.rows != m_image.height or image_.cols != m_image.width) {
            image_ = cv::Mat::zeros(m_image.height, m_image.width, CV_8UC3);
            
        }
        memcpy((void*)image_.data, (void*)&m_image.pixels[0], m_image.pixels.length());
        
        is_new_ = true;
        image_mutex_.unlock();
    }
    
    return RTC::RTC_OK;
}

cv::Mat MultiCameraViewer::getImage()
{
    //cv::Mat image(height_,width_,CV_8UC3);
    image_mutex_.lock();
    cv:: Mat image = image_.clone();
    //cv::resize(image_, image, image.size());
    image_mutex_.unlock();
    return image;
}

extern "C"
{
 
  void MultiCameraViewerInit(RTC::Manager* manager)
  {
    coil::Properties profile(multicameraviewer_spec);
    manager->registerFactory(profile,
                             RTC::Create<MultiCameraViewer>,
                             RTC::Delete<MultiCameraViewer>);
  }
  
};


