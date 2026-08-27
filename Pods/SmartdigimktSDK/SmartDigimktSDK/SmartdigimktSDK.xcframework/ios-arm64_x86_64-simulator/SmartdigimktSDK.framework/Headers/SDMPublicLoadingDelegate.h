//
//  SDMPublicLoadingDelegate.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/6/1.
//  Copyright © 2025 Smartdigimkt. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SDMBaseAd;
NS_ASSUME_NONNULL_BEGIN

@protocol SDMPublicLoadingDelegate <NSObject>

/// Callback when the successful loading of the ad
- (void)onAdLoaded:(SDMBaseAd *)item;

/// Callback of ad loading failure
- (void)onAdLoadFail:(SDMBaseAd *)item
               error:(NSError *)error;

@end

NS_ASSUME_NONNULL_END
