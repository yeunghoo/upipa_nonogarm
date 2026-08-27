//
//  ATBaseInitAdapter.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/3/21.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATSafeModuleObject.h>
#import <AnyThinkSDK/ATAdInitArgument.h>
#import <AnyThinkSDK/ATAdMediationArgument.h>
#import <AnyThinkSDK/ATLoadAdapterResult.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ATNetworkInitStatus) {
    ATNetworkInitStatusUnknown,
    ATNetworkInitStatusIniting,
    ATNetworkInitStatusSuccess,
    ATNetworkInitStatusFail,
};

@interface ATBaseInitAdapter : ATSafeModuleObject

@property (atomic, assign) ATNetworkInitStatus networkInitStatus;

#pragma mark - 子类重写

- (void)initWithInitArgument:(ATAdInitArgument *)adInitArgument;

+ (nullable NSString *)sdkVersion;

+ (nullable NSString *)adapterVersion;

+ (nullable NSString *)adapterProtocolVersion;

#pragma mark - 子类调用
/// 三方 network初始化结果,回传
- (void)notificationNetworkInitSuccess;

- (void)notificationNetworkInitFail:(NSError *)error;

/// 是否需要每次请求前都 再次初始化一次 三方 SDK
- (BOOL)loadAdRequireInitialize;

/// S2S 是否需要初始化在获取 token
- (BOOL)s2s_initializeThenHB;

#pragma mark - S2S
- (void)headerBiddingParametersWithArgument:(ATAdMediationArgument *)argument completion:(ATLoadAdapterResultBlock)completion;


#pragma mark - Tool
+ (NSMutableDictionary *)getLoadNetworkObjc:(id)networkObjc;

+ (instancetype)getNetworkInitAdapter:(NSString *)networkFirmString;

+ (instancetype)preNetworkSDkInitAdapter:(NSString *)networkFirmString classNameString:(NSString *)classNameString;

@end

NS_ASSUME_NONNULL_END
