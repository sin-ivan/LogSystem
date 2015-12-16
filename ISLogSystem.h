//
//  ISLogSystem.h
//
//
//  Created by Ivan Sinitsa on 11/13/13.
//  Copyright (c) 2013 Home. All rights reserved.
//
//  Small wrapper for CocoaLumberjack
//

#import <Foundation/Foundation.h>

#import "DDLog.h"
static const int ddLogLevel = LOG_LEVEL_VERBOSE; //Setup constant for the\
                                                    CocoaLumberJack framework

#pragma mark -
//Usage example LOG_CONFIGURE(kLogToFile | kLogToConsole, LOG_LEVEL_VERBOSE);
//Macros for shortening setup procedure
#define LOG_CONFIGURE(aParamsMask, aLogLevel) [ISLogSystem \
                setupLogSystem:(aParamsMask) logLevel:(aLogLevel)]

//Log macros

//! Prints specified params.
#define DLog(x, ...) DDLogInfo(@""x, ##__VA_ARGS__)

//! Prints call point. Params will be printed after log output.
#define DLogTrace(x, ...) DDLogInfo(@"-[%@ %@%d] "x, self, \
        NSStringFromSelector(_cmd), __LINE__, ##__VA_ARGS__)

/*! 
 Prints call point. Params will be printed after log output.
 Works both in C/C++ and Objective-C methods.
 */
#define DLogSafeTrace(x, ...) DDLogInfo(@"%s, line:%d "x, __func__, \
                                             __LINE__, ##__VA_ARGS__)

//! Prints stack trace. Params will be printed after log output.
#define DLogStackTrace(x, ...) DDLogVerbose(@"-[%@ %@%d] %@ "x, self, \
                                NSStringFromSelector(_cmd), __LINE__, \
                            [NSThread callStackSymbols], ##__VA_ARGS__)

//! Print call point with additional error info. Params will be
//printed after log output.
#define DLogError(x, ...) DDLogError(@"ERROR: -[%@ %@%d] "x, self, \
                NSStringFromSelector(_cmd), __LINE__, ##__VA_ARGS__)

//! Print call point with additional error info. Params will be
//printed after log output.
#define DLogNotImplemented(x, ...) DDLogError(@"NOT IMPLEMENTED: -[%@ %@%d] "x, self, \
    NSStringFromSelector(_cmd), __LINE__, ##__VA_ARGS__)

/*!
 Print call point with additional error info and current stack trace.
 Params will be printed after log output.
*/
#define DLogErrorStack(x, ...) DDLogError(@"ERROR: -[%@ %@%d] %@ "x, \
                         self, NSStringFromSelector(_cmd), __LINE__, \
                           [NSThread callStackSymbols], ##__VA_ARGS__)

//Available log sources
typedef NS_ENUM(int, ISLogParams)
{
    kLogToConsole = 0x1,
    kLogToFile = 0x2
};

#pragma mark -

/*! 
 Class wrapper for CocoaLumberJack logging framework. Class defines it's
 own macros to simplify interaction interface with CocoaLumberJack framework.
*/
@interface ISLogSystem : NSObject

//! Main logging system setup method.
//! @param aLogParamsMask - binary mask, see ISLogParams for possible values
//! @param aLogLevel -
+ (void)setupLogSystem:(int)aLogParamsMask logLevel:(int)aLogLevel;

@end
