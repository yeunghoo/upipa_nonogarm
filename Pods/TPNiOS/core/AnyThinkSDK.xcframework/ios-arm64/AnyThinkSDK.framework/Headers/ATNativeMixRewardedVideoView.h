//
//  ATNativeMixRewardedVideoView.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/9/3.
//

#import <AnyThinkSDK/ATBaseNativeMixView.h>
#import <AnyThinkSDK/ATAdOfferCacheModel.h>


NS_ASSUME_NONNULL_BEGIN

@interface ATNativeMixRewardedVideoView : ATBaseNativeMixView

/// 是否半屏广告
@property (nonatomic, assign) BOOL isHalfAd;

/// 主图是否为竖图
@property (nonatomic,assign) BOOL isMaterialPortrait;

@end

NS_ASSUME_NONNULL_END
