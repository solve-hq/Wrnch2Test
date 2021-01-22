//
//  Wrnch2.hpp
//  Test Wrnch 2
//
//  Created by Matthew Aitken on 22/01/2021.
//

#ifndef Wrnch2_hpp
#define Wrnch2_hpp

#include <stdio.h>
#import <wrEngine/wrEngine.h>

class Wrnch2 {
public:
    void start(const char* licenseKey);
private:
    static void detectionCallback(wrFrame const* const frame, char const* const serializedDetections, size_t const serializedDetectionsLen, void* userData);
};

#endif /* Wrnch2_hpp */
