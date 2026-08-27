//
//  SDMPubNativeDelegate.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/6/20.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMPublicLoadingDelegate.h>

@class UIView, SDMNativeAd;
NS_ASSUME_NONNULL_BEGIN

@protocol SDMPubNativeMediaViewDelegate <NSObject>

- (void)onVideoAdStartPlay:(SDMNativeAd *)item duration:(double)duration;

- (void)onVideoAdComplete:(SDMNativeAd *)item;

- (void)onVideoError:(SDMNativeAd *)item error:(NSError *)error;

- (void)onProgressUpdate:(SDMNativeAd *)item current:(double)current duration:(double)duration;

@end

@protocol SDMPubNativeDelegate <NSObject>

/// Native ads displayed successfully
- (void)onAdShow:(SDMNativeAd *)item;

/// Native ad click
- (void)onAdClick:(SDMNativeAd *)item extra:(nullable NSDictionary *)extra;

@optional

/// Native ad close button cliecked
- (void)onAdClosed:(SDMNativeAd *)item extra:(nullable NSDictionary *)extra;

/// Whether the click jump of Native ads is in the form of Deeplink
- (void)onDeeplinkCallback:(SDMNativeAd *)item
                    result:(BOOL)success;

@end

NS_ASSUME_NONNULL_END
