//
//  ATBaseAdapterProtocol.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/7.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATBidWinLossResult.h>

NS_ASSUME_NONNULL_BEGIN
@class ATBaseMediationAdapter,ATSplashAdStatusBridge,ATInterstitialAdStatusBridge,ATRewardedAdStatusBridge,ATBannerAdStatusBridge,ATNativeAdStatusBridge,ATMediaVideoAdStatusBridge,ATAdMediationArgument;
@class ATMediaVideoAdObject;

typedef void(^ATADLoadCompletionBlock)(NSArray<NSDictionary *> *_Nullable completionArray, NSError *_Nullable error);

typedef void(^ATADNetworkInitBlock)(BOOL isInitSuccess, NSError *_Nullable error);

@protocol ATBaseAdapterProtocol <NSObject>

#pragma mark - init
+ (nullable ATBaseMediationAdapter *)getLoadAdAdapter:(nonnull ATAdMediationArgument *)argument;
#pragma mark - load Ad
- (void)loadADWithArgument:(ATAdMediationArgument *)argument;
#pragma mark - 初始化
- (Class)initializeClassName;

@optional

#pragma mark - C2S Win Loss
- (void)didReceiveBidResult:(ATBidWinLossResult *)result;

- (id)getAdObject;
- (UIView *)getBannerView;

@end

@protocol ATNativeADDelegate,ATSplashDelegate,ATBannerDelegate,ATInterstitialDelegate,ATRewardedVideoDelegate;

@protocol ATBaseNativeAdapterProtocol <ATBaseAdapterProtocol>


@optional
@property (nonatomic,strong) ATNativeAdStatusBridge *adStatusBridge;

@end

@protocol ATBaseBannerAdapterProtocol <ATBaseAdapterProtocol>

@optional
@property (nonatomic, strong) ATBannerAdStatusBridge *adStatusBridge;
/// 是否触发 showBannerView 调用,默认为NO,不触发
- (BOOL)callShowBannerView;
- (void)showBannerView:(UIView *)bannerView inView:(UIView *)view inViewController:(UIViewController *)viewController;

@end

@protocol ATBaseInterstitialAdapterProtocol <ATBaseAdapterProtocol>


- (BOOL)adReadyInterstitialWithInfo:(NSDictionary *)info;
- (void)showInterstitialInViewController:(UIViewController *)viewController;

@optional
@property (nonatomic,strong) ATInterstitialAdStatusBridge *adStatusBridge;



@end

@protocol ATBaseRewardedAdapterProtocol <ATBaseAdapterProtocol>

- (void)showRewardedVideoInViewController:(UIViewController *)viewController;
- (BOOL)adReadyRewardedWithInfo:(NSDictionary *)info;

@optional
@property (nonatomic,strong) ATRewardedAdStatusBridge *adStatusBridge;


@end


@protocol ATBaseSplashAdapterProtocol <ATBaseAdapterProtocol>

- (BOOL)adReadySplashWithInfo:(NSDictionary *)info;

- (void)showSplashAdInWindow:(UIWindow *)window inViewController:(UIViewController *)inViewController parameter:(NSDictionary *)parameter;

@optional
@property (nonatomic,strong) ATSplashAdStatusBridge *adStatusBridge;



@end

@protocol ATBaseMediaVideoAdapterProtocol <ATBaseAdapterProtocol>

- (BOOL)adReadyMediaVideoWithInfo:(NSDictionary *)info;

- (ATMediaVideoAdObject *)getMediaVideoAdObject;

@optional
@property (nonatomic,strong) ATMediaVideoAdStatusBridge *adStatusBridge;

@end

NS_ASSUME_NONNULL_END
