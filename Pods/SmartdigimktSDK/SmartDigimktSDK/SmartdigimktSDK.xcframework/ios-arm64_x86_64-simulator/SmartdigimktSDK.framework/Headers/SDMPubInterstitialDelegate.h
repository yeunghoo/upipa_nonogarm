//
//  SDMPubInterstitialDelegate.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/6/17.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN
@class SDMInterstitialAd;

@protocol SDMPubInterstitialDelegate <NSObject>

#pragma mark - InterstitialAd
/// Interstitial ad displayed successfully
- (void)onAdShow:(SDMInterstitialAd *)item;

/// Interstitial ad clicked
- (void)onAdClick:(SDMInterstitialAd *)item extra:(nullable NSDictionary *)extra;

/// Interstitial ad closed
- (void)onAdClose:(SDMInterstitialAd *)item extra:(nullable NSDictionary *)extra;

@optional

/// Interstitial ad display failed
- (void)onAdShowFail:(SDMInterstitialAd *)item
               error:(NSError *)error;

/// Interstitial video ad playback start
- (void)onAdVideoStart:(SDMInterstitialAd *)item;

/// Interstitial playback end
- (void)onAdVideoEnd:(SDMInterstitialAd *)item;

/// Whether the click jump on the interstitial advertisement is in the form of Deeplink
- (void)onDeeplinkCallback:(SDMInterstitialAd *)item
                    result:(BOOL)success;

@end

NS_ASSUME_NONNULL_END
