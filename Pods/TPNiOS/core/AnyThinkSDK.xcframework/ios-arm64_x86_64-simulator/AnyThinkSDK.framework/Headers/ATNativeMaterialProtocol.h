//
//  ATNativeMaterialProtocol.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/4/12.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATAdEnums.h>

NS_ASSUME_NONNULL_BEGIN
@class ATNativeAdNetworkViewConfig;
@protocol ATNativeMaterialProtocol <NSObject>

/// network template ad view
@property (nonatomic, strong) UIView *templateView;
/// Only for template AdView
@property(nonatomic, assign) CGFloat nativeExpressAdViewWidth;

@property(nonatomic, assign) CGFloat nativeExpressAdViewHeight;

/// Advertiser, advertiser's name or link
@property(nonatomic, strong, nullable) NSString *advertiser;

/// ad title
@property(nonatomic, strong, nullable) NSString *title;

/// Ad details
@property(nonatomic, strong, nullable) NSString *mainText;

/// CTA Button text such as 'download/install'
@property(nonatomic, strong, nullable) NSString *ctaText;

/// app  icon
@property(nonatomic, strong, nullable) UIImage *icon;

/// main image
@property(nonatomic, strong, nullable) UIImage *mainImage;

/// ad logo
@property(nonatomic, strong, nullable) UIImage *logo;

@property(nonatomic, strong, nullable) NSDictionary *logoSet;

@property(nonatomic, strong, nullable) UIView *logoView;

/// ad logo url
@property(nonatomic, strong, nullable) NSString *logoUrl;

/// video url
@property(nonatomic, strong, nullable) NSString *videoUrl;

/// app icon url
@property(nonatomic, strong, nullable) NSString *iconUrl;

/// main image url
@property(nonatomic, strong, nullable) NSString *imageUrl;

/// main image width
@property(nonatomic, assign) CGFloat mainImageWidth;

/// main image height
@property(nonatomic, assign) CGFloat mainImageHeight;

/// mediaView
@property(nonatomic, strong, nullable) UIView *mediaView;

/// image url list
@property(nonatomic, strong, nullable) NSArray<NSString *> *imageList;

/// video duration, in second, if there is no value, return 0
@property(nonatomic, assign) CGFloat videoDuration;

/// video aspect ratio (width/height), if no value or exception returns 0
@property (nonatomic, assign) CGFloat videoAspectRatio;


/// Ad-supported jump types
@property(nonatomic, assign) ATNativeAdInteractionType interactionType;

/// media extension data
@property(nonatomic, copy, nullable) NSDictionary *mediaExt;

/// app source, marketplace, such as 'App Store'
@property(nonatomic, copy, nullable) NSString *source;

/// app rating
@property(nonatomic, strong, nullable) NSNumber *rating;

/// the number of comments, or -1 if there is no value
@property(nonatomic, assign) NSInteger commentNum;

/// the size of the ad installation package, in KB, if there is no value, return -1
@property(nonatomic, strong) NSString *appSize;

/// app purchase price, such as 'free', nil if none
@property(nonatomic, strong, nullable) NSString *appPrice;

/// The domain. only for Yandex native
@property(nonatomic, strong, nullable) NSString *domain;

/// The warning. only for Yandex native
@property(nonatomic, strong, nullable) NSString *warning;

/// is it template ad
@property(nonatomic, assign) BOOL isExpressAd; // affirm by scy 删除 替换成 ATNativeAdRenderType

/// is video muted init status
@property (nonatomic, assign) BOOL isVideoMuted;
/**
 * For some ads, this property does not always determines whether the ad is a video ad or not; however, to do this, you can always use the corresponding ad view's isVideoContents method instead.
 */
@property(nonatomic, assign) BOOL isVideoContents;

/// 模版渲染还是手动渲染
@property(nonatomic, assign) ATNativeAdRenderType nativeAdRenderType;
/// 物料格式
@property(nonatomic, assign) ATAdMaterialFormat nativeMaterialFormat;

@property(nonatomic, assign) ATNativeAdType nativeAdType;

/// 获取三方network slider View
- (nullable UIView *)getSliderViewWithConfig:(ATNativeAdNetworkViewConfig *)config;
/// 获取三方network 摇一摇 View
- (nullable UIView *)getShakeViewWithConfig:(ATNativeAdNetworkViewConfig *)config;
/// 销毁三方network 摇一摇
- (void)destoryShakeView;
/// 开启三方network 摇一摇
- (void)startShakeView;

@end

NS_ASSUME_NONNULL_END
