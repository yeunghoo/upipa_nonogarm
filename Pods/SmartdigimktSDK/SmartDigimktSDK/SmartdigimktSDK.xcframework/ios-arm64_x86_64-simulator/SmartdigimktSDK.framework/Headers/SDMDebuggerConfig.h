//
//  SDMDebuggerConfig.h
//  SmartdigimktSDK
//
//  Created by GUO PENG on 2022/8/2.
//  Copyright © 2022 Smartdigimkt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMDebuggerConfigDefine.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMDebuggerConfig : NSObject

@property(nonatomic, assign,readonly) BOOL isDebugger;

@property(nonatomic, strong) NSString *deviceIdfaStr;
@property(nonatomic, assign) SDMAdNetWorkType netWorkType;

#pragma mark - ADX

@property(nonatomic, assign) SDMADXSplashAdType adx_splashAdType;

@property(nonatomic, assign) SDMADXInterstitialAdType adx_interstitialAdType;

@property(nonatomic, assign) SDMADXRewardVideoAdType adx_rewardVideoAdType;

@property(nonatomic, assign) SDMADXBannerAdType adx_bannerAdType;

@property(nonatomic, assign) SDMADXNativeAdType adx_nativeAdType;


#pragma mark - api
- (NSDictionary *)getCurrentNetWorkConfig;




@end

NS_ASSUME_NONNULL_END
