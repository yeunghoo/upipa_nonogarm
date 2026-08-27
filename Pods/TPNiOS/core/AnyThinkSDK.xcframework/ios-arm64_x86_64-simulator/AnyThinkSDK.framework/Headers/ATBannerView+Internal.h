//
//  ATBanner+Internal.h
//  AnyThinkBanner
//
//  Created by Martin Lau on 28/09/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <AnyThinkSDK/ATAdManager+Banner.h>
#import <AnyThinkSDK/ATBannerView.h>
#import <AnyThinkSDK/ATTrackerInfo.h>

#ifndef ATBanner_Internal_h
#define ATBanner_Internal_h


NS_ASSUME_NONNULL_BEGIN

@class ATBanner;
@interface ATBannerView(Internal)
-(instancetype) initWithFrame:(CGRect)frame banner:(ATAdOfferCacheModel*)banner placementID:(NSString *)placementID;
-(void) loadNextWithoutRefresh;
@property(nonatomic) ATAdOfferCacheModel *banner;
@property (nonatomic, strong,nullable) ATNativeBannerView *selfRenderingMixBannerlView;

@property(nonatomic,copy) NativeMixBannerViewBlock nativeMixBannerViewBlock;

- (void)evaluationPanGesture:(nullable UIPanGestureRecognizer *)panGesture;
- (UIPanGestureRecognizer *)getPanGesture;
- (void)evaluationSlideClickStatus:(BOOL)clickStatus;
- (BOOL)getSlideClickStatus;
- (ATAdOfferCacheModel *)getPrivateBanner;
- (void)updateTrackClickAreaType:(ATClickAreaType)clickAreaType;
- (UIView *)getTrackView;

@end
#endif /* ATBanner_Internal_h */
NS_ASSUME_NONNULL_END
