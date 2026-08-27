//
//  ATAdLogger.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 28/04/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAPI.h>

#define ATADPublicLogKEY @"publicLog"
#define AT_AnyThinkAdTrack @"AnyThinkAdTrack"
#define ATNETLog(format, ...) printf("%s\n\n",[[NSString stringWithFormat:(format), ##__VA_ARGS__] UTF8String])

NS_ASSUME_NONNULL_BEGIN

/**
 * 广告日志管理器，负责SDK的日志记录和输出
 * 提供不同级别的日志记录功能，包括普通消息、警告和错误日志
 * 支持日志缓存、外部日志显示等功能，便于调试和问题排查
 */
@interface ATAdLogger : NSObject

/**
 * 是否启用日志记录
 * 控制整个SDK的日志输出开关
 */
@property (atomic) BOOL logEnabled;

/**
 * 是否启用日志缓存
 * 控制日志是否缓存到本地存储
 */
@property (atomic) BOOL logCacheEnabled;

/**
 * 是否禁止ADX加载提示
 * 控制ADX相关的Toast提示是否显示
 */
@property (atomic) BOOL adxLoadToastForbid;

/**
 * 获取日志管理器的单例实例
 * @return ATAdLogger的共享实例
 */
+ (instancetype)sharedManager;

/**
 * 判断是否应该记录指定类型的日志
 * @param type 日志类型
 * @return YES表示应该记录，NO表示不记录
 */
+ (BOOL)shouldLogType:(ATLogType)type;

/**
 * 记录普通消息日志
 * @param message 要记录的消息内容
 * @param type 日志类型
 */
+ (void)logMessage:(NSString *)message type:(ATLogType)type;

/**
 * 记录警告日志
 * @param warning 警告信息内容
 * @param type 日志类型
 */
+ (void)logWarning:(NSString *)warning type:(ATLogType)type;

/**
 * 记录错误日志
 * @param error 错误信息内容
 * @param type 日志类型
 */
+ (void)logError:(NSString *)error type:(ATLogType)type;

/**
 * 记录网络相关日志
 * @param networkString 网络信息字符串
 * @param typeString 类型描述字符串
 */
+ (void)logNetworkString:(NSString *)networkString typeString:(NSString *)typeString;

/**
 * 记录设备信息日志
 * 输出当前设备的相关信息用于调试
 */
+ (void)logDeviceInfo;

/**
 * 显示外部消息日志
 * 用于显示来自外部的日志消息
 * @param message 消息内容，可以为nil
 * @param prefixStr 前缀字符串，可以为nil
 */
+ (void)showExternalLogMessage:(nullable NSString *)message
                     prefixStr:(nullable NSString *)prefixStr;

/**
 * 显示外部警告日志
 * 用于显示来自外部的警告信息
 * @param warning 警告内容，可以为nil
 * @param prefixStr 前缀字符串，可以为nil
 */
+ (void)showExternalLogWarning:(nullable NSString *)warning
                     prefixStr:(nullable NSString *)prefixStr;

+ (void)logDebugMessage:(NSString *)message withPrefix:(NSString *)prefix;

@end

NS_ASSUME_NONNULL_END
