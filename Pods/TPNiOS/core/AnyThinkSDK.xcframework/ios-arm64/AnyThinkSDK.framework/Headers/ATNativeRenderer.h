//
//  ATNativeRenderer.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 25/04/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/AnyThinkSDK.h>

@class ATAdOfferCacheModel;

NS_ASSUME_NONNULL_BEGIN

@protocol ATNativeADRenderer;
@interface ATNativeRenderer : NSObject<ATNativeADRenderer>

-(UIView*)retriveADView;
- (void)recordCustomPlayerStatus:(ATPlayerStatus)status currentTime:(NSTimeInterval)time;
-(instancetype) initWithConfiguraton:(ATNativeADConfiguration*)configuration adView:(ATNativeADView*)adView;
-(__kindof UIView*)createMediaView;
@property(nonatomic, weak) ATNativeADView *ADView;
@property(nonatomic, readonly) ATNativeADConfiguration *configuration;

- (UIView *)getNetWorkMediaView;

- (UIView *)getNetWorkShakeView:(ATAdOfferCacheModel *)offer frame:(CGRect)frame;

- (UIView *)getNetworkSlideViewWithOffer:(ATAdOfferCacheModel *)offer frame:(CGRect)frame repeat:(int)repeat animationWidth:(CGFloat)animationWidth animationHeight:(CGFloat)animationHeight;

// for override
- (void)closeAct;

- (void)setVideoAutoPlay:(NSInteger)autoPlayType;

- (void)shakeViewDestroy:(UIView *)shakeView;

@end

NS_ASSUME_NONNULL_END
