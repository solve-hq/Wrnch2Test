//
//  Wrnch2Wrapper.m
//  Test Wrnch 2
//
//  Created by Matthew Aitken on 22/01/2021.
//

#import <Foundation/Foundation.h>
#import "Wrnch2Wrapper.h"
#import "Wrnch2.hpp"

@implementation Wrnch2Wrapper

+ (void) start:(NSString *) licenseKey {
    Wrnch2 wrnch2;
    wrnch2.start([licenseKey cStringUsingEncoding:NSUTF8StringEncoding]);
}

@end
