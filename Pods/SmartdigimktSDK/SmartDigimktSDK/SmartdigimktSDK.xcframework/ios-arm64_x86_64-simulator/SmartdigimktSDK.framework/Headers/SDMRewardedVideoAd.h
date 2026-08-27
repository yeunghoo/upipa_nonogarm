//
//  SDMRewardedVideoAd.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/5/27.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMBaseAd.h>
#import <SmartdigimktSDK/SDMPublicLoadingDelegate.h>
#import <SmartdigimktSDK/SDMPubRewardedVideoDelegate.h>
#import <SmartdigimktSDK/SDMPubRewardedEventDelegate.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMRewardedVideoAd : SDMBaseAd
@property (nonatomic, weak, nullable) id<SDMPubRewardedVideoDelegate> showDelegate;
@property (nonatomic, weak, nullable) id<SDMPubRewardedEventDelegate> deepRewardDelegate;

- (void)showAd;

@end

NS_ASSUME_NONNULL_END
