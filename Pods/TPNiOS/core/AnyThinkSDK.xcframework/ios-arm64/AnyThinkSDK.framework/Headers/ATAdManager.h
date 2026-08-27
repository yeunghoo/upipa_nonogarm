//
//  ATAdManager.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 04/05/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>
#import <AnyThinkSDK/ATADXFloorPrice.h>
#import <AnyThinkSDK/ATAdLoadingDelegate.h>
#import <AnyThinkSDK/ATMgPreloadModel.h>


NS_ASSUME_NONNULL_BEGIN

//TODO ZSR 这个类是否存在一些无用的代码？？

extern NSString *const kATAdAssetsNativeCustomEventKey;
extern NSString *const kATAdAssetsCustomEventKey;
extern NSString *const kATAdAssetsCustomObjectKey;
extern NSString *const kATAdAssetsCustomNativeObjectKey;
extern NSString *const kATExtraInfoRootViewControllerKey;
extern NSString *const kATAdAssetsDelegateObjKey;
extern NSString *const kATAdAssetsCustomNativeAdKey;
extern NSString *const kATAdAssetsCustomShowVcKey;

extern NSString *const kATAdLoadingExtraMediaExtraKey;
extern NSString *const kATAdLoadingExtraNetworkPlacementIDKey;
extern NSString *const kATAdLoadingExtraAdmobContentURLStringsKey;
extern NSString *const kATAdLoadingExtraAdmobKeywordsKey;
extern NSString *const kATAdLoadingExtraShowViewControllerKey;
extern NSString *const kATAdLoadingExtraGDTEnableDefaultAudioSessionKey;
extern NSString *const kATAdLoadingAdChannelSourceKey;
extern NSString *const kATAdLoadingAdMCPreloadModelKey;

/*
 * Banner's ad size, the value is a NSValue wrapped CGSize; for banner ad loading,
 * we only support (320.0f, 50.0f) now, so the value you pass via this key will be ignored.
 */
extern NSString *const kATExtraInfoAdSizeKey;

typedef BOOL(^AdSourceCustomizeFillterBlock)(NSDictionary *extra);

@protocol ATAdLoadingDelegate;

@interface ATAdManager : NSObject

@property (nonatomic, strong) NSDictionary *extra;
@property (nonatomic, strong) NSMutableDictionary *showingObjcDic;
@property (nonatomic, copy) AdSourceCustomizeFillterBlock adSourceCustomizeFillter;

/// singleton object
+ (instancetype)sharedManager;

/// Called when load ad
/// @param placementID - TopOn's ad placement id
/// @param extra - Local configuration parameter
/// @param delegate - delegate object
- (void)loadADWithPlacementID:(NSString *)placementID
                        extra:(NSDictionary *)extra
                     delegate:(id<ATAdLoadingDelegate>)delegate;

- (void)loadADWithPlacementID:(NSString *)placementID
                        extra:(NSDictionary *)extra
               viewController:(UIViewController *)viewController
                     delegate:(id<ATAdLoadingDelegate>)delegate;

- (void)loadADWithPlacementID:(NSString *)placementID
                        extra:(NSDictionary *)extra
                      tkExtra:(nullable NSDictionary *)tkExtra
                adxFloorPrice:(nullable ATADXFloorPrice *)adxFloorPrice
                     delegate:(id<ATAdLoadingDelegate>)delegate;

- (void)setMultipleLoadingDelegate:(id<ATAdMultipleLoadingDelegate>)delegate
                       placementId:(NSString *)placementId;

- (NSDictionary *)extraInfoForPlacementID:(NSString *)placementID
                                requestID:(NSString *)requestID;

- (void)setExludePlacementid:(NSString *)placementid
                 unitIDArray:(NSArray <NSString *> *)unitIDArray DEPRECATED_MSG_ATTRIBUTE("Deprecated. Use [ATSDKGlobalSetting sharedManager] setExludePlacementid:unitIDArray: instead");

/// Set the network that needs to be excluded when loading an placement, will take effect on the next load
/// @param placementid  - TopOn's ad placement id
/// @param networkFirmIDArray - need to be excluded networkFirmIds
///
- (void)setExludePlacementid:(NSString *)placementid
          networkFirmIDArray:(NSArray <NSNumber *> *)networkFirmIDArray DEPRECATED_MSG_ATTRIBUTE("Deprecated. Use [ATSDKGlobalSetting sharedManager] setExludePlacementid:networkFirmIDArray: instead");

- (void)setAdSourceCustomizeFillterPlacementIDArray:(NSArray <NSString *> *)placementIDArray DEPRECATED_MSG_ATTRIBUTE("Deprecated. Use [ATSDKGlobalSetting sharedManager] setAdSourceCustomizeFillterPlacementIDArray: instead");

- (void)entryAdScenarioWithPlacementID:(NSString *)placementID
                            scenarioID:(NSString *)scenarioID;

- (NSArray<NSDictionary *> *)getAdValidAdsForPlacementID:(NSString *)placementID;
 
/// Notify us after custom close ad only
/// @param placementID  - TopOn's ad placement id
- (void)customCloseADEventWithPlacementID:(NSString *)placementID;

// 比价工具, 竞胜竞败接口 TODO ZSR 待优化
+ (void)trackWinWithPlacementID:(nonnull NSString *)placementID extra:(nullable NSDictionary *)extra;
+ (void)trackLossWithPlacementID:(nonnull NSString *)placementID extra:(nullable NSDictionary *)extra;

@end

NS_ASSUME_NONNULL_END
