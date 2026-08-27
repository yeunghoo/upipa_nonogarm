//
//  ATAdManager+Internal.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 04/05/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

/**
 * This file contains methods&properties implemented by ATAdManager intented for internal use only.
 */
#ifndef ATAdManager_Internal_h
#define ATAdManager_Internal_h
#import <AnyThinkSDK/ATAdManager.h>
#import <AnyThinkSDK/ATAdSourceRequestParams.h>
#import <AnyThinkSDK/ATAPI.h>

@class ATCheckLoadModel, ATAdOfferCacheModel, ATAdObject;

@interface ATAdReadyResult : NSObject
@property (nonatomic, assign) BOOL isReady;
@property (nonatomic, strong) ATAdObject *ad;
@property (nonatomic, strong) NSDictionary *extraInfo;
@end

//The value is (subclass of) UIViewController
extern NSString *const kATAdLoadingExtraRefreshFlagKey;//Defined in loader
extern NSString *const kATAdLoadingExtraBannerAutoRefreshFlagKey;
extern NSString *const kATAdLoadingExtraAutoloadFlagKey;
extern NSString *const kATAdLoadingTrackingExtraStatusKey;
extern NSString *const kATAdLoadingTrackingExtraFlagKey;
extern NSString *const kATAdLoadingExtraDefaultLoadKey;
extern NSString *const kATReadyToShowNotification;

typedef NS_ENUM(NSInteger, ATAdManagerReadyAPICaller) {
    ATAdManagerReadyAPICallerReady = 0,
    ATAdManagerReadyAPICallerShow = 1,
};

@interface ATAdManager(Internal)

#pragma mark - for inner usage
/**
 nil might be returned on one of the following conditions:
 1) No offer's been successfully loaded for the placement;
 2) Pacing/caps has exceeded the limit.
 when this happens, clients are expected to behave as if ad load request has failed.
 */
//- (ATAdObject *)offerWithPlacementID:(NSString *)placementID
//                               error:(NSError **)error;

- (ATAdReadyResult *)adReadyForPlacementID:(NSString *)placementID
                                showConfig:(ATShowConfig *)showConfig
                                    caller:(ATAdManagerReadyAPICaller)caller
                                    sendTK:(BOOL)send;

/*
 *For internal use only
 */
- (BOOL)adReadyForPlacementID:(NSString *)placementID;

- (NSDictionary*)extraInfoForPlacementID:(NSString *)placementID
                               requestID:(NSString *)requestID;

- (void)setExtraInfo:(NSDictionary *)extraInfo
      forPlacementID:(NSString *)placementID
           requestID:(NSString *)requestID;

- (void)removeExtraInfoForPlacementID:(NSString *)placementID
                            requestID:(NSString *)requestID;

- (NSDictionary *)lastExtraInfoForPlacementID:(NSString *)placementID;

#pragma mark - other
- (BOOL)getInspectAdSourceStatusPlacementModel:(ATPlacementModel *)placementModel
                  loadingAdSourceRequestParams:(ATAdSourceRequestParams *)loadingAdSourceRequestParams
           lowPriceFilledAdSourceRequestParams:(ATAdSourceRequestParams *)lowPriceFilledAdSourceRequestParams
                                finalWaterfall:(ATWaterfallModel *)finalWaterfall
                                     requestID:(NSString *)requestID
                                extraInfoArray:(NSArray<NSDictionary *> *__autoreleasing *)adSourceStatusInpectionExtraInfo;

#pragma mark - Data
- (void)unionEntryAdScenarioWithPlacementID:(NSString *)placementID
                                      scene:(NSString *)scene;

- (ATCheckLoadModel *)unionCheckAdLoadStatusForPlacementID:(NSString *)placementID;

- (NSArray<NSDictionary *> *)unionGetAdValidAdsForPlacementID:(NSString *)placementID;

#pragma mark - Is Ready
- (BOOL)checkFormatWithPlacementId:(NSString *)placementId
                            format:(ATAdFormat)format;

- (BOOL)unionReadyForPlacementID:(NSString *)placementID
                          sendTK:(BOOL)send;

#pragma mark - real time TK
+ (NSArray *)getRealTimeNetworkArray;

#pragma mark - send_tracking
- (void)sendEntryScenarioTrackingWithPlacementID:(NSString *)placementID
                           adSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams
                                           scene:(NSString *)scene
                                       isLoading:(BOOL)isLoading
                                         isReady:(BOOL)isReady
                                       extraInfo:(NSDictionary *)extraInfo;

+ (void)tryInvalidateBidInfoIfNeeded:(ATAdOfferCacheModel *)offerCacheModel;

@end


#endif /* ATAdManager_Internal_h */
