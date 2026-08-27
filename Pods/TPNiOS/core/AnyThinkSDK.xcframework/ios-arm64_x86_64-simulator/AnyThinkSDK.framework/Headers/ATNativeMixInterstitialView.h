//
//  ATNativeMixInterstitialView.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/12/26.
//  Copyright © 2024 AnyThink. All rights reserved.
//
#import <AnyThinkSDK/ATBaseNativeMixView.h>
#import <AnyThinkSDK/ATAdOfferCacheModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATNativeMixInterstitialView : ATBaseNativeMixView

/// 是否半屏广告
@property (nonatomic, assign) BOOL isHalfAd;

/// 是否1:1比例
@property (nonatomic, assign) BOOL isSameRadio;

/// 主图是否为竖图
@property (nonatomic,assign) BOOL isMaterialPortrait;

/// 屏幕方向
@property (nonatomic, assign) BOOL isPortrait;

@end

NS_ASSUME_NONNULL_END
