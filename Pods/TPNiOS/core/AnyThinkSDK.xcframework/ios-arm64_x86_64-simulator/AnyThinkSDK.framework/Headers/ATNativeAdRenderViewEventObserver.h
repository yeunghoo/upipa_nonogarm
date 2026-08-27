//
//  ATNativeAdRenderViewEventObserver.h
//  AnyThinkNative
//
//  Created by Captain on 2024/10/24.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ATNativeAdRenderViewEventObserver <NSObject>

- (ATAdOfferCacheModel *)adOfferCacheModel;
- (void)notifyNativeAdClick;
- (void)notifyVideoStart;
- (void)notifyVideoEnd;
- (void)notifyVideoEnterFullScreen;
- (void)notifyVideoExitFullScreen;
- (void)notifyCloseButtonTapped;
- (void)notifyDeeplinkOrJumpResult:(BOOL)success;
- (void)notifyAdDetailShow;
- (void)notifyAdDetailClosed;
- (void)notifyNativeAdShow;
- (void)notifyNativeAdDidRevenue;
- (void)notifyNativeAdShowFail:(NSError *)error;
- (void)notifyActRewardComplete:(nullable NSDictionary *)extra;
- (void)notifyActRewardTimerUpdate:(nullable NSDictionary *)extra;
- (NSArray<UIView*>*)clickableViews;
- (BOOL)isVideoContents;
@end

NS_ASSUME_NONNULL_END
