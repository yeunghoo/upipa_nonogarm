//
//  SDMPubSplashDelegate.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/6/17.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMPublicLoadingDelegate.h>
NS_ASSUME_NONNULL_BEGIN

#pragma mark - Splash
@class SDMSplashAd;

@protocol SDMPubSplashDelegate <NSObject>
/// Splash ad displayed successfully
- (void)onAdShow:(SDMSplashAd *)item;

/// Splash ad click
- (void)onAdClick:(SDMSplashAd *)item extra:(nullable NSDictionary *)extra;

/// Splash ad closed
- (void)onAdClose:(SDMSplashAd *)item extra:(nullable NSDictionary *)extra;

@optional
///  Whether the click jump of Splash ad is in the form of Deeplink
- (void)onDeeplinkCallback:(SDMSplashAd *)item
                    result:(BOOL)success;
/// Splash ad show fail with error
- (void)onAdShowFail:(SDMSplashAd *)item
               error:(NSError *)error;

@end

@protocol SDMPubSplashLoadingDelegate <SDMPublicLoadingDelegate>

/// Callback when the splash ad is loaded successfully
/// @param isTimeout whether timeout
- (void)onAdLoaded:(SDMSplashAd *)item isTimeout:(BOOL)isTimeout;

/// Splash ad loading timeout callback
- (void)onAdLoadTimeout:(SDMSplashAd *)item;

@end

NS_ASSUME_NONNULL_END
