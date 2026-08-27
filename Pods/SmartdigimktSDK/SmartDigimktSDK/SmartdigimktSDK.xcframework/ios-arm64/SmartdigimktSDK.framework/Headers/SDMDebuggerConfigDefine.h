//
//  SDMDebuggerConfigDefine.h
//  SmartdigimktSDK
//
//  Created by GUO PENG on 2022/8/10.
//  Copyright © 2022 Smartdigimkt. All rights reserved.
//


#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
#pragma mark - NetWorkType
typedef NS_ENUM(NSUInteger, SDMAdNetWorkType) {
    SDMAdNetWorkAdxType = 66,
};

#pragma mark - ADX
typedef NS_ENUM(NSUInteger, SDMADXSplashAdType) {
    SDMADXSplashAdDefaultType = 0
};

typedef NS_ENUM(NSUInteger, SDMADXInterstitialAdType) {
    SDMADXInterstitialAdFullScreenType = 1,
    SDMADXInterstitialAdHalfScreenType = 2,
};

typedef NS_ENUM(NSUInteger, SDMADXRewardVideoAdType) {
    SDMADXRewardVideoAdDefaultType = 0,
};

typedef NS_ENUM(NSUInteger, SDMADXBannerAdType) {
    SDMADXBannerAdType_320_50 = 1,
    SDMADXBannerAdType_320_90 = 2,
    SDMADXBannerAdType_300_250 = 3,
    SDMADXBannerAdType_728_90 = 4,
};

typedef NS_ENUM(NSUInteger, SDMADXNativeAdType) {
    SDMADXNativeAdTypeExpressLeftPicRightText = 1,
    SDMADXNativeAdTypeExpressLeftTextRightPic = 2,
    SDMADXNativeAdTypeExpressTopPicBottomText = 3,
    SDMADXNativeAdTypeExpressTopTextBottomPic = 4,
    SDMADXNativeAdTypeExpressTextSuperposedLayer = 5,
    SDMADXNativeAdTypeSelfRender = 6,
};

NS_ASSUME_NONNULL_END
