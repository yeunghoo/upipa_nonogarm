//
//  ATBaseTrackProtocol.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/7.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define ATOfferClickAdTypeKey @"ATOfferClickAdTypeKey"
NS_ASSUME_NONNULL_BEGIN
@class ATCustomNetworkNativeAd;
@protocol ATBaseTrackProtocol <NSObject>

/// 广告数据加载完成
- (void)atOnAdMetaLoadFinish:(NSDictionary * _Nullable)adExtra;
/// 广告加载失败
- (void)atOnAdLoadFailed:(NSError *)error adExtra:(NSDictionary * _Nullable)adExtra;

/// 广告展示成功
- (void)atOnAdShow:(NSDictionary *_Nullable)adExtra;
/// 广告展示失败
- (void)atOnAdShowFailed:(NSError *)error extra:(NSDictionary *_Nullable)extraDic;
/// 广告点击
- (void)atOnAdClick:(NSDictionary *_Nullable)adExtra;
/// 广告即将关闭
- (void)atOnAdWillClosed:(NSDictionary *_Nullable)extra;
/// 广告关闭
- (void)atOnAdClosed:(NSDictionary *_Nullable)extra;
/// 广告详情页即将展现
- (void)atOnAdDetailWillShow:(NSDictionary *_Nullable)extra;
/// 广告详情页关闭
- (void)atOnAdDetailClosed:(NSDictionary *_Nullable)extra;
/// 广告Deeplink跳转
- (void)atOnAdDeeplinkOrJumpResult:(BOOL)success;
/// 广告视频开始播放
- (void)atOnAdVideoStart:(NSDictionary *_Nullable)extra;
/// 广告视频播放结束
- (void)atOnAdVideoEnd:(NSDictionary *_Nullable)extra;
/// 广告播放失败
- (void)atOnAdDidFailToPlayVideo:(NSError*)error extra:(NSDictionary *_Nullable)extraDic;
/// didRevenue
- (void)atOnAdDidRevenue:(NSDictionary *_Nullable)extraDic;

///腾讯原生拼接插屏 显示倒计时时使用
- (void)atVideoStatusChanged:(NSInteger)videoStatus;
@end

@protocol ATSplashTrackProtocol <ATBaseTrackProtocol>

- (void)atOnSplashAdLoadedExtra:(NSDictionary * _Nullable)adExtra;

/// 开屏倒计时
- (void)atOnSplashAdCountdownTime:(NSInteger)countdown;

- (void)atOnSplashAdStartCountdown:(NSDictionary *)localInfo countdownBlock:(void(^)(NSInteger time))block;

- (void)atOnSplashAdZoomOutViewClick;

- (void)atOnSplashAdZoomOutViewClosed;

/// 开屏场景激励回调，仅 GDT 支持
- (void)atOnSplashAdRewarded:(NSDictionary * _Nullable)extra;

@end

@protocol ATRewardedTrackProtocol <ATBaseTrackProtocol>

- (void)atOnRewardedAdLoadedExtra:(NSDictionary * _Nullable)adExtra;
/// 激励发放激励成功
- (void)atOnRewardedVideoAdRewarded;
/// 获取是否发放激励成功
- (BOOL)getRewardGranted;
/// 激励发放激励失败
- (void)atOnRewardedVideoAdRewardedFailWithExtra:(NSDictionary * _Nullable)adExtra;
/// 二次激励回调taskInfo
- (void)onRewardedSuccess:(NSDictionary *)taskInfo;

@end

@protocol ATNativeTrackProtocol <ATBaseTrackProtocol>

- (void)atOnNativeAdLoadedArray:(NSArray <ATCustomNetworkNativeAd *>*)nativeObjectArray adExtra:(NSDictionary *_Nullable)adExtra;

/// Native enters full screen video ads, only for Nend
- (void)atOnNativeAdDidEnterFullScreenVideoInAdViewWithAdExtra:(NSDictionary *_Nullable)adExtra;

/// Native exit full screen video ad, only for Nend
- (void)atOnNativeAdDidExitFullScreenVideoInAdViewWithAdExtra:(NSDictionary *_Nullable)adExtra;

/// 行为激励奖励完成回调，仅百度信息流支持
- (void)atOnNativeAdActRewardDidComplete:(NSDictionary *_Nullable)extra;

/// 行为激励计时更新回调，仅百度信息流支持
- (void)atOnNativeAdActRewardTimerUpdate:(NSDictionary *_Nullable)extra;

@end

@protocol ATBannerTrackProtocol <ATBaseTrackProtocol>

- (void)atOnBannerAdLoadedWithView:(UIView * _Nullable)bannerView  adExtra:(NSDictionary * _Nullable)adExtra;

@end

@protocol ATInterstitialTrackProtocol <ATBaseTrackProtocol>

- (void)atOnInterstitialAdLoadedExtra:(NSDictionary * _Nullable)adExtra;

/// 插屏场景激励回调，仅 GDT 支持
- (void)atOnInterstitialAdRewarded:(NSDictionary * _Nullable)extra;

@end

@protocol ATMediaVideoTrackProtocol <ATBaseTrackProtocol>

- (void)atOnMediaVideoAdLoadedAdObject:(id)adObject extra:(NSDictionary * _Nullable)adExtra;
- (void)atOnMediaVideoAdDidReceiveAdEvent:(id)event;
- (void)atOnMediaVideoAdDidRequestContentPause;
- (void)atOnMediaVideoAdBreakReady;
- (void)atOnMediaVideoAdDidRequestContentResume;
- (void)atOnMediaVideoAdDidProgressToTime:(NSTimeInterval)mediaTime totalTime:(NSTimeInterval)totalTime;
- (void)atOnMediaVideoAdPlaybackReady;
- (void)atOnMediaVideoAdDidStartBuffering;
- (void)atOnMediaVideoAdDidBufferToMediaTime:(NSTimeInterval)mediaTime;
- (void)atOnMediaVideoAdDidAllAdsComplete;
- (void)atOnMediaVideoAdDidSkip;
- (void)atOnMediaVideoAdDidTap;

@end

NS_ASSUME_NONNULL_END
