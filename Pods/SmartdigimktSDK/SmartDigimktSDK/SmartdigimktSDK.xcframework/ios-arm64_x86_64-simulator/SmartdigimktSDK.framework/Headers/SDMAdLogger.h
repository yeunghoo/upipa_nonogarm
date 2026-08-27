//
//  SDMAdLogger.h
//  SmartdigimktSDK
//
//  Created by Plutus on 28/04/2018.
//  Copyright © 2018 Plutus. All rights reserved.
//  Logger Tool

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMAPI.h>

#define SDMADPublicLogKEY @"publicLog"
#define SDM_SmartdigimktAdTrack @"SmartdigimktAdTrack"
#define SDMNETLog(format, ...) printf("%s\n\n",[[NSString stringWithFormat:(format), ##__VA_ARGS__] UTF8String])

@interface SDMAdLogger : NSObject
NS_ASSUME_NONNULL_BEGIN

@property (atomic) BOOL logEnabled;
@property (atomic) BOOL logCacheEnabled;

+ (instancetype)sharedManager;

+ (BOOL)shouldLogType:(SDMLogType)type;
+ (void)logMessage:(NSString *)message type:(SDMLogType)type;
+ (void)logWarning:(NSString *)warning type:(SDMLogType)type;
+ (void)logError:(NSString *)error type:(SDMLogType)type;
+ (void)logNetworkString:(NSString *)networkString typeString:(NSString *)typeString;
+ (void)logDeviceInfo;

/// for External message
/// @param message pStr
/// @param prefixStr prefix string
+ (void)showExternalLogMessage:(nullable NSString *)message
                     prefixStr:(nullable NSString *)prefixStr;

/// for External warning
/// @param warning pStr
/// @param prefixStr prefix string
+ (void)showExternalLogWarning:(nullable NSString *)warning
                     prefixStr:(nullable NSString *)prefixStr;
NS_ASSUME_NONNULL_END
@end
