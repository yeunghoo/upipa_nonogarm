//
//  ATAdOfferModel.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/7.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <AnyThinkSDK/ATAdObject.h>
#import <AnyThinkSDK/ATModel.h>
#import <AnyThinkSDK/ATCustomNetworkNativeAd.h>

@class ATInterstitialCustomEvent,ATRewardedVideoCustomEvent,ATNativeADCustomEvent,ATBannerCustomEvent,ATSplashCustomEvent;



NS_ASSUME_NONNULL_BEGIN

@interface ATAdOfferCacheModel : ATAdObject

@property (nonatomic, strong) ATCustomNetworkNativeAd *customNetworkNativeAd;

@property(nonatomic, assign) ATAdFormat format;

@property(nonatomic, strong) ATSplashCustomEvent *splashCustomEvent;

@property(nonatomic, strong) ATBannerCustomEvent *bannerCustomEvent;

@property(nonatomic, strong) ATNativeADCustomEvent *nativeCustomEvent;

@property(nonatomic, strong) ATInterstitialCustomEvent *interstitialCustomEvent;

@property(nonatomic, strong) ATRewardedVideoCustomEvent *rewardedCustomEvent;

@property (nonatomic, strong) ATAdAdapterManager *adapterModel;

- (instancetype)initWithPriority:(NSInteger) priority placementModel:(ATPlacementModel *)placementModel requestID:(NSString *)requestID assets:(NSDictionary*)assets adSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams finalWaterFall:(nullable ATWaterfallModel *)finalWaterFall;
@end

NS_ASSUME_NONNULL_END
