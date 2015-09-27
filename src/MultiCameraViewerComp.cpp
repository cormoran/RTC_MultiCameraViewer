// -*- C++ -*-
/*!
 * @file MultiCameraViewerComp.cpp
 * @brief Standalone component
 * @date $Date$
 *
 * $Id$
 */

#include <rtm/Manager.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include<vector>
#include "MultiCameraViewer.h"
#include "MultiCameraWindow.hpp"

MultiCameraBase* CreateComponent(RTC::Manager* manager){
    RTC::RtcBase* cmp = manager->createComponent("MultiCameraViewer");
    if (cmp == NULL) {
        std::cerr << "Component create failed." << std::endl;
        abort();
    }
    MultiCameraBase* ret = dynamic_cast<MultiCameraBase*>(cmp);
    if (ret == NULL) {
        std::cerr << "Component dynamic cast failed." << std::endl;
        abort();
    }
    return ret;
}


int main (int argc, char** argv)
{
    RTC::Manager* manager;
    manager = RTC::Manager::init(argc, argv);
    manager->init(argc, argv);
    manager->activateManager();
    MultiCameraViewerInit(manager);
    
    manager->runManager(true);
    
    std::cout
    << "Quit : press 'q' on window\n"
    << "AddPort : press 'A' on window" << std::endl;

    std::vector<MultiCameraBase*> components;
    components.push_back(CreateComponent(manager));
    
    MultiCameraWindow window("MultiView",640,480);
    window.ResizeImageArray(components.size());
    while (true) {
        for (int i=0; i<components.size(); i++) {
            if (components[i]->isActive() and components[i]->isNew()) {
                window.UpdateImage(i, components[i]->getImage());
            }
        }
        int key = cv::waitKey(33);
        if (key == 'q') {
            break;
        }
        else if (key == 'A'){
            components.push_back(CreateComponent(manager));
            window.ResizeImageArray(components.size());
        }
    }
    manager->terminate();

  return 0;
}
