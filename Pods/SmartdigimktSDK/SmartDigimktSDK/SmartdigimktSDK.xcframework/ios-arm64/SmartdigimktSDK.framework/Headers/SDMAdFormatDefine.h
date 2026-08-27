//
//  SDMAdFormatDefine.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/11/4.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kSDMSplashExtraCustomSkipButtonKey; // only supported UIButton

typedef NS_ENUM(NSInteger, SDMBaseAdInitType) {
    SDMBaseAdInitTypeMyOffer = 1,
    SDMBaseAdInitTypeADX,
    SDMBaseAdInitTypeDirect,
};

typedef NS_ENUM(NSInteger, SDMAdFormat) {
    SDMAdFormatNative = 0,
    SDMAdFormatRewardedVideo = 1,
    SDMAdFormatBanner = 2,
    SDMAdFormatInterstitial = 3,
    SDMAdFormatSplash = 4,
};

typedef NS_ENUM(NSInteger, SDMNativeAdRenderType) {
    SDMNativeAdRenderSelfRender = 1,
    SDMNativeAdRenderExpress = 2,
};

NS_ASSUME_NONNULL_END
