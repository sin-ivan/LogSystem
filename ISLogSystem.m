//
//  ISLogSystem.m
//
//
//  Created by Ivan Sinitsa on 11/13/13.
//  Copyright (c) 2013 Home. All rights reserved.
//

#import "ISLogSystem.h"

#import "DDTTYLogger.h"
#import "DDASLLogger.h"
#import "DDFileLogger.h"

//Default file maximum size, initially set to 2MB.
static const int kISDefaultLogFileMaxSize = 2 * 1024 * 1024;

//Default roll frequency, initiallly set to 86400 in seconds (once per day)
static const int kISDefaultLogFileRollFrequency = 24 * 60 * 60;

//Defailt maximum number of log files, initially set to 5
static const int kISDefaultLogFileMaxFileNumber = 5;


@implementation ISLogSystem

//Setup loggers objects
+ (void)setupLogSystem:(int)aLogParamsMask logLevel:(int)aLogLevel
{
    if (aLogParamsMask & kLogToConsole) {
        //Initialize log output to Terminal or XCode
        [DDLog addLogger:[DDTTYLogger sharedInstance] withLogLevel:aLogLevel];
        //Initialize log output to Apple System Log
        [DDLog addLogger:[DDASLLogger sharedInstance] withLogLevel:aLogLevel];
    }
    
    if (aLogParamsMask & kLogToFile) {
        //Initialize log output to file
        DDFileLogger *fileLogger = [DDFileLogger new]; //Prints log to files
        [fileLogger setMaximumFileSize:kISDefaultLogFileMaxSize];
        [fileLogger setRollingFrequency:kISDefaultLogFileRollFrequency];
        [fileLogger.logFileManager setMaximumNumberOfLogFiles:kISDefaultLogFileMaxFileNumber];
        [DDLog addLogger:fileLogger withLogLevel:aLogLevel]; //Always write log to file
    }
    
    DLog(@"***************************************************");
    DLog(@"**** Started logging session at: %@ ****", [NSDate date]);
    DLog(@"***************************************************");
}

@end
