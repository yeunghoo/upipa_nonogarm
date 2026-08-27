//
//  SDMNativeAd.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/5/27.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMBaseAd.h>
#import <SmartdigimktSDK/SDMPubNativeDelegate.h>
#import <SmartdigimktSDK/SDMNativeAdOffer.h>
#import <SmartdigimktSDK/SDMAdRequest.h>
#import <SmartdigimktSDK/SDMNativePrepareInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class SDMNativeLayoutParams, SDMAdRequest;

@interface SDMNativeAd : SDMBaseAd

@property (nonatomic, weak, nullable) id<SDMPubNativeDelegate> showDelegate;
@property (nonatomic, strong, readonly, nullable) SDMNativeAdOffer *nativeAdOffer;
@property (nonatomic, strong) SDMAdRequest *adRequest;

- (void)registerAdView:(nullable UIView *)container
            clickViews:(nullable NSArray<UIView *> *)clickableViews
           prepareInfo:(nullable SDMNativePrepareInfo *)prepareInfo
           configParam:(nullable SDMNativeLayoutParams *)configParam
             closeView:(nullable UIView *)closeView;

- (nullable UIView *)getMediaViewWithDelegate:(id<SDMPubNativeMediaViewDelegate>)mediaViewDelegate;
- (void)resumeVideo;
- (void)pauseVideo;
- (void)muteEnable:(BOOL)flag;
- (void)updateVoiceHidden:(BOOL)hidden;

- (nullable UIView *)agenerateShakeViewContainer;


@end

NS_ASSUME_NONNULL_END
