//
//  SDMInterstitialAd.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/5/27.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMBaseAd.h>
#import <SmartdigimktSDK/SDMPubInterstitialDelegate.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMInterstitialAd : SDMBaseAd

@property (nonatomic, weak, nullable) id<SDMPubInterstitialDelegate> showDelegate;

- (void)showAd;

@end

NS_ASSUME_NONNULL_END
