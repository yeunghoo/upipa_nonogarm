//
//  SDMPubRewardedVideoDelegate.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/6/17.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SDMRewardedVideoAd;

@protocol SDMPubRewardedVideoDelegate <NSObject>

#pragma mark - RewardVideo
/// Rewarded video ad play starts
- (void)onAdPlayStart:(SDMRewardedVideoAd *)item;


/// Rewarded video ad play ends
- (void)onAdPlayEnd:(SDMRewardedVideoAd *)item;

/// Rewarded video ad clicks
- (void)onAdClick:(SDMRewardedVideoAd *)item extra:(nullable NSDictionary *)extra;

/// Rewarded video ad closed
- (void)onAdClose:(SDMRewardedVideoAd *)item
         rewarded:(BOOL)rewarded;

@optional

/// Rewarded video ad reward distribution
- (void)onAdReward:(SDMRewardedVideoAd *)item __attribute__((deprecated("Use onAdReward:trackDict: instead")));

/// Rewarded video ad reward distribution
- (void)onAdReward:(SDMRewardedVideoAd *)item trackDict:(nullable NSDictionary *)trackDict;

/// Rewarded video ad play failed
- (void)onAdPlayFailed:(SDMRewardedVideoAd *)item
                 error:(NSError *)error;

/// Whether the click jump of rewarded video ad is in the form of Deeplink
- (void)onDeeplinkCallback:(SDMRewardedVideoAd *)item
                    result:(BOOL)success;

@end

NS_ASSUME_NONNULL_END
