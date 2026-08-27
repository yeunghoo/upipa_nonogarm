//
//  ATInteriorTrackProtocol.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/11/27.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ATInteriorTrackProtocol <NSObject>
#pragma mark - Splash
/// 广告数据加载成功,回调成功
- (void)atOnSplashAdDataLoadSuccessExtra:(NSDictionary *_Nullable)adExtra;
/// 广告渲染成功,回调成功
- (void)atOnSplashAdRenderSuccessExtra:(NSDictionary *_Nullable)adExtra;

#pragma mark - Rewarded

/// 广告数据加载成功,回调成功
- (void)atOnRewardedAdDataLoadSuccessExtra:(NSDictionary *_Nullable)adExtra;
/// 广告渲染成功,回调成功
- (void)atOnRewardedAdRenderSuccessExtra:(NSDictionary *_Nullable)adExtra;

#pragma mark - Banner

/// 广告数据加载成功,回调成功
- (void)atOnBannerAdDataLoadWithView:(UIView *)bannerView  adExtra:(NSDictionary * _Nullable)adExtra;

/// 广告渲染成功,回调成功
- (void)atOnBannerAdRenderSuccessWithView:(UIView *)bannerView  adExtra:(NSDictionary * _Nullable)adExtra;

#pragma mark - Interstitial
/// 广告数据加载成功,回调成功
- (void)atOnInterstitialAdDataLoadSuccessExtra:(NSDictionary *_Nullable)adExtra;
/// 广告渲染成功,回调成功
- (void)atOnInterstitialAdRenderSuccessExtra:(NSDictionary *_Nullable)adExtra;

@end

NS_ASSUME_NONNULL_END
