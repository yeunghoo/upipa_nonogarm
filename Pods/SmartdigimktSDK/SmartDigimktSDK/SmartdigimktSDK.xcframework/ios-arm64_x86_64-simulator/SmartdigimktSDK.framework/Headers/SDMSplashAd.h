//
//  SDMSplashAd.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/5/27.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMBaseAd.h>
#import <SmartdigimktSDK/SDMAdFormatDefine.h>
#import <SmartdigimktSDK/SDMPubSplashDelegate.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMSplashAd : SDMBaseAd

@property (nonatomic, weak, nullable) id<SDMPubSplashLoadingDelegate> loadDelegate;
@property (nonatomic, weak, nullable) id<SDMPubSplashDelegate> showDelegate;
@property (nonatomic, weak, nullable) UIView *containerView;
@property (nonatomic, weak) UIWindow *window;
@property (nonatomic, assign) double fetchAdTimeout;

- (void)showAd;

@end

NS_ASSUME_NONNULL_END
