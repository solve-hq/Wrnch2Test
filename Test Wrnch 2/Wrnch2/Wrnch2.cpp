//
//  Wrnch2.cpp
//  Test Wrnch 2
//
//  Created by Matthew Aitken on 22/01/2021.
//

#include "Wrnch2.hpp"
#include <iostream>
#include <wrEngine/wrEngine.h>

int framesReceived;
static wrEngine* engine = nullptr;

void Wrnch2::start(const char* licenseKey) {
    std::cout << "Wrnch2::start method called";
    
    wrCameraConfig* const camConfig = wrCameraConfig_Create();
    unsigned int numCameras = wrEngine_GetNumCameraDevices();
    wrCameraDeviceInfo* deviceInfo = wrCameraDeviceInfo_Create();
    
    for (unsigned int i = 0; i < numCameras; i++) {
        wrEngineCode code = wrEngine_GetCameraDeviceInfo(deviceInfo, i);

        if (code != wrEngineCode_OK)
            continue;

        const char* friendlyName = wrCameraDeviceInfo_GetFriendlyName(deviceInfo);
        const char* deviceId = wrCameraDeviceInfo_GetId(deviceInfo);
        wrCameraDevicePosition position = wrCameraDeviceInfo_GetPosition(deviceInfo);

        // Choose a camera based on some combination of friendly name, ID, and position
        std::cout << friendlyName;
        std::cout << deviceId;
        
        //we want to use the front facing camera
        if (position != wrCameraDevicePosition_FRONT) {
            continue;
        }
        
        std::cout << "Selected camera:" << deviceId;
        
        //configure camera (this is the front facing camera if it reaches here)
        wrCameraConfig_SetIntProperty(camConfig, wrCameraConfigProperty_WIDTH, 1920);
        wrCameraConfig_SetIntProperty(camConfig, wrCameraConfigProperty_HEIGHT, 1080);
        wrCameraConfig_SetFloatProperty(camConfig, wrCameraConfigProperty_FPS, 30);
        wrCameraConfig_SetStringProperty(camConfig, wrCameraConfigProperty_DEVICE_ID, deviceId);
        
        //configure engine
        wrEngineConfig* const config = wrEngineConfig_Create();
        wrEngineConfig_SetIntProperty(config, wrEngineConfigProperty_STREAM_FLAGS, wrStream_POSE_2D | wrStream_POSE_3D);
        wrEngineConfig_SetStringProperty(config, wrEngineConfigProperty_LICENSE_STRING, licenseKey);
        
        std::cout << "Setting detection callback";
        
        wrDetectionCallback callback = &Wrnch2::detectionCallback;
        
        //set callback        
        wrEngineConfig_SetDetectionCallback(config, callback, &framesReceived);
        
        std::cout << "Has set detection callback";
        
        //start engine
        code = wrEngine_Create(&engine, config);
        if (code != wrEngineCode_OK)
        {
            char const* error = wrEngineCode_Describe(code);
            
            std::cout << "wrEngine start error: " << error;
            return;
//            std::cerr << wrEngineCode_Describe(code) << '\n';
//            return EXIT_FAILURE;
        }
        
        std::cout << "Successfully created engine";
        std::cout << "Opening camera";
        
        //start reading from camera
        wrEngineCode cameraCode = wrEngine_OpenCamera(engine, camConfig);
        if(cameraCode != wrEngineCode_OK) {
            char const* error = wrEngineCode_Describe(code);
            std::cout << "wrEngine open camera error: " << error;
        }
        
        return;
    }
}


void Wrnch2::detectionCallback(wrFrame const* const frame, char const* const serializedDetections, size_t const serializedDetectionsLen, void* userData)
{
//    NSLog(@"%@", [NSString stringWithUTF8String:serializedDetections])
    std::cout << "detectionCallback()";
}
