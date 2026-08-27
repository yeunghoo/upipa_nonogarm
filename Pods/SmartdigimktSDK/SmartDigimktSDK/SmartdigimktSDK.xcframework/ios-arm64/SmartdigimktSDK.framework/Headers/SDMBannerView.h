//
//  SDMBannerView.h
//  AnyThinkSDK
//
//  Created by xuejingwei on 2025/6/18.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <SmartdigimktSDK/SDMAdRequest.h>
#import <SmartdigimktSDK/SDMWinInfo.h>
#import <SmartdigimktSDK/SDMLossInfo.h>
#import <SmartdigimktSDK/SDMAd.h>

NS_ASSUME_NONNULL_BEGIN

@class SDMBannerView;

@protocol SDMBannerViewDelegate <NSObject>

- (void)onAdLoaded:(SDMBannerView *)bannerView;

- (void)onAdLoadFail:(SDMBannerView *)bannerView error:(NSError *)error;

- (void)onAdShow:(SDMBannerView *)bannerView;

- (void)onAdClick:(SDMBannerView *)bannerView extra:(nullable NSDictionary *)extra;

- (void)onAdClose:(SDMBannerView *)bannerView extra:(nullable NSDictionary *)extra;

- (void)onDeeplinkCallback:(SDMBannerView *)bannerView result:(BOOL)success;

@end

/// creating && using in the main thread
@interface SDMBannerView : UIView

@property (nonatomic, copy) NSString *placementId;
@property (nonatomic, weak, nullable) id<SDMBannerViewDelegate> delegate;

- (void)load;
- (void)loadWithAdRequest:(nullable SDMAdRequest *)adRequest;
- (BOOL)isAdReady;
- (void)sendImpressionTracking;
- (void)destroy;
/// send win
- (void)notifyWin:(SDMWinInfo *)winInfo;
/// send loss
- (void)notifyLoss:(SDMLossInfo *)lossInfo;

- (nullable SDMAd *)getSDMAd;


- (instancetype)initAdWithPlacementId:(nonnull NSString *)placementId extra:(nullable NSDictionary *)extra;
- (void)loadAdWithExtraDic:(nonnull NSDictionary *)ExtraDic;
- (BOOL)readyFilledWithExtraDic:(NSDictionary *)extraDic;
@end

NS_ASSUME_NONNULL_END
