//
//  ATAdNativeObject.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/10/17.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATAdEnums.h>
#import <AnyThinkSDK/ATNativeMaterialProtocol.h>

@class ATNativeAdNetworkViewConfig;
@class ATNativeAdRenderConfig;
@class ATAdMediationArgument;
NS_ASSUME_NONNULL_BEGIN

@protocol ATAdLoadedNativeDataSource

@optional

/// 广告物料格式
//- (ATAdMaterialFormat)nativeMaterialFormat;
//
//- (ATNativeAdType)nativeAdType;


/// CSJ recordCustomPlayerStatus
//- (void)recordCustomPlayerStatus:(ATPwlayerStatus)status currentTime:(NSTimeInterval)time;


#pragma mark - Video
/**
 * The duration of the video ad playing, unit ms
 */
- (CGFloat)videoPlayTime;
/**
 * Video ad duration, unit ms
 */
- (CGFloat)videoDuration;
/**
 Play mute switch
 @param flag whether to mute
 */
- (void)muteEnable:(BOOL)flag;
/**
 * The video ad play
 */
- (void)videoPlay;
/**
 * set voice button hidden, only suport TopOn Adx ad
 */
- (void)updateVoiceBtnHidden:(BOOL)hidden;
/**
 * The video ad pause
 */
- (void)videoPause;

- (void)setVideoAutoPlay:(NSInteger)autoPlayType;

/// The destroy  network native ad
- (void)destroyNative;

/**
 * Returns remaining duration for behavior-based incentive, in seconds. Only for Baidu native feed.
 */
- (int)getActReawrdRemainTime;

@end


@interface ATNativeRegisterArgument : NSObject
@property (nonatomic, strong, nullable) UIViewController *viewController;
@property (nonatomic, strong, nullable) UILabel *sponsorLabel;
@property (nonatomic, strong, nullable) UILabel *advertiserLabel;
@property (nonatomic, strong, nullable) UILabel *priceLabel;
@property (nonatomic, strong, nullable) UILabel *textLabel;
@property (nonatomic, strong, nullable) UILabel *titleLabel;
@property (nonatomic, strong, nullable) UILabel *ctaLabel;
@property (nonatomic, strong, nullable) UILabel *ratingLabel;
@property (nonatomic, strong, nullable) UIImageView *iconImageView;
@property (nonatomic, strong, nullable) UIImageView *mainImageView;
@property (nonatomic, strong, nullable) UIImageView *logoImageView;
@property (nonatomic, strong, nullable) UIButton *dislikeButton;
@property (nonatomic, strong, nullable) UILabel *domainLabel;
@property (nonatomic, strong, nullable) UILabel *warningLabel;
@property (nonatomic, strong, nullable) UIView *containerView;

@end




@interface ATCustomNetworkNativeAd : NSObject<ATAdLoadedNativeDataSource>//,ATNativeMaterialProtocol>

#pragma mark - 素材
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
//穿山甲 .adLabel
@property (nonatomic, assign)UILabel *adLabel;
/// Ad-supported jump types
///
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

/// Incentive copy text for behavior-based reward, only for Baidu native feed
@property(nonatomic, strong, nullable) NSString *actText;

/// Total required interaction duration for behavior-based incentive, only for Baidu native feed
@property(nonatomic, strong, nullable) NSString *actTime;

/// Whether the ad supports behavior-based incentive, only for Baidu native feed
@property (nonatomic, assign) BOOL isSupportActReward;

/// is it template ad
@property(nonatomic, assign) BOOL isExpressAd; // affirm by scy 删除 替换成 ATNativeAdRenderType

/// is video muted init status
@property (nonatomic, assign) BOOL isVideoMuted;
@property (nonatomic, assign) BOOL didSetVideoMuted;
/**
 * For some ads, this property does not always determines whether the ad is a video ad or not; however, to do this, you can always use the corresponding ad view's isVideoContents method instead.
 */
@property(nonatomic, assign) BOOL isVideoContents;

// ADX模版类型
@property (nonatomic, assign) NSInteger expressType;

/// 模版渲染还是手动渲染
@property(nonatomic, assign) ATNativeAdRenderType nativeAdRenderType;
///// 物料格式
@property(nonatomic, assign) ATAdMaterialFormat nativeMaterialFormat;
//
@property(nonatomic, assign) ATNativeAdType nativeAdType;

@property(nonatomic, strong, nullable) id networkNativeAdProduct;

- (nullable UIView *)getSliderViewWithConfig:(ATNativeAdNetworkViewConfig *)config;

- (nullable UIView *)getShakeViewWithConfig:(ATNativeAdNetworkViewConfig *)config;

- (void)destoryShakeView;

- (void)startShakeView;


#pragma mark - 注册
- (void)registerClickableViews:(NSArray<UIView *> *)clickableViews withContainer:(UIView *)container registerArgument:(nullable ATNativeRegisterArgument *)registerArgument;


- (void)setNativeADConfiguration:(ATNativeAdRenderConfig *)configuration;

- (void)destoryView;


@end

NS_ASSUME_NONNULL_END
