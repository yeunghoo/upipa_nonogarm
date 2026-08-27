//
//  ATBaseMediationAdapter.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/7.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATBaseAdapterProtocol.h>
#import <AnyThinkSDK/ATAdStatusBridge.h>
#import <AnyThinkSDK/ATAdOfferCacheModel.h>
#import <AnyThinkSDK/ATCustomNetworkNativeAd.h>
#import <AnyThinkSDK/ATBaseInitAdapter.h>

NS_ASSUME_NONNULL_BEGIN
@interface ATBaseMediationAdapter : NSObject<ATBaseAdapterProtocol>

/// load 加载参数
@property (nonatomic,readonly)ATAdMediationArgument *argument;

@property (nonatomic,assign)BOOL didLoaded;
@property (nonatomic,assign)BOOL didShow;
@property (nonatomic,assign)BOOL didClose;

#pragma mark - Option

- (Class)initializeClassName;

#pragma mark - Over Writing
/// 广告加载(子类重写)
- (void)loadADWithArgument:(ATAdMediationArgument *)argument;
/// 强制关闭广告
- (void)forceCloseAd;

@end

NS_ASSUME_NONNULL_END
