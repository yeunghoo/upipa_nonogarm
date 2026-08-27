//
//  ATAdStatusTraceCenter.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/14.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATBaseTrackProtocol.h>
#import <AnyThinkSDK/ATAdEnums.h>
#import <AnyThinkSDK/ATAdCustomEvent.h>

#define ATAdLoadedCallBackTypeKey @"ATAdLoadedCallBackTypeKey"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ATAdapterLoadType) {
    ATAdapterLoadTypeNormal = 0,
    ATAdapterLoadTypeS2S,
    ATAdapterLoadTypeC2S,
};

@protocol ATAdStatusEventProtocol <NSObject>
@optional
- (void)adStatusCleanUpAd;
@end

typedef void(^ATADMetaDataDidLoadedBlock)(void);

@interface ATAdStatusBridge : NSObject<ATBaseTrackProtocol>

/// 广告类型
@property (nonatomic, assign) ATAdapterLoadType adapterLoadType;

/// 设置回调代理
@property (nonatomic, weak) id adapterDelegate;

@property (nonatomic, assign) ATAdCloseType closeType;

@property (nonatomic, copy) NSString *scene;
 
@property (nonatomic, weak) id<ATAdStatusEventProtocol>eventDelegate;

@property (atomic, strong) ATAdCustomEvent *targetAdCustomEvent;

/// 设置三方 networkCustomInfo
- (void)setNetworkCustomInfo:(NSDictionary *)networkCustomInfo;

/// 设置三方 networkUnitId
- (void)setNetworkUnitId:(NSString *)networkUnitId;

/// 设置是否 由core层发送 TK 4
- (void)setSendImpressionTrackingIfNeed:(BOOL)isCoreSend;

- (void)setTrackerExtraInfo:(ATTrackerInfo *)trackerExtraInfo;

- (void)updateTriggerCloseClickType:(ATTriggerCloseClickType)closeType;
@end


@interface ATSplashAdStatusBridge : ATAdStatusBridge<ATSplashTrackProtocol>

@end

@interface ATInterstitialAdStatusBridge : ATAdStatusBridge<ATInterstitialTrackProtocol>

@end

@interface ATRewardedAdStatusBridge : ATAdStatusBridge<ATRewardedTrackProtocol>

@end

@interface ATBannerAdStatusBridge : ATAdStatusBridge<ATBannerTrackProtocol>

- (void)loadNextWithoutRefresh;

@end

@interface ATNativeAdStatusBridge : ATAdStatusBridge<ATNativeTrackProtocol>

@end

@interface ATMediaVideoAdStatusBridge : ATAdStatusBridge<ATMediaVideoTrackProtocol>

@end

NS_ASSUME_NONNULL_END
