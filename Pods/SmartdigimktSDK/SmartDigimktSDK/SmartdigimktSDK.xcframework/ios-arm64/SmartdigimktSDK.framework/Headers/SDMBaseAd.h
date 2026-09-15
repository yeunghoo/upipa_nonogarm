//
//  SDMBaseAd.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/5.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMPublicLoadingDelegate.h>
#import <SmartdigimktSDK/SDMAdFormatDefine.h>
#import <SmartdigimktSDK/SDMAdRequest.h>
#import <SmartdigimktSDK/SDMAd.h>
#import <SmartdigimktSDK/SDMWinInfo.h>
#import <SmartdigimktSDK/SDMLossInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class UIViewController;

FOUNDATION_EXPORT NSString * const kSDMS2SAdmPayloadKey;

@interface SDMBaseAd : NSObject

@property (nonatomic, copy, nullable) NSString *placementId;
@property (nonatomic, strong, nullable) NSDictionary *extra;
@property (nonatomic, weak, nullable) id<SDMPublicLoadingDelegate> loadDelegate;
@property (nonatomic, weak, nullable) UIViewController *showViewController;
@property (nonatomic, strong, nullable) NSDictionary *adSourceExtra;

@property (nonatomic, strong, nullable) SDMAdRequest *adRequest;

/// generate params for adx
+ (void)generateHBParamWithExtraDic:(nullable NSDictionary *)extraDic
                             format:(SDMAdFormat)format
                           complete:(nonnull void(^)(NSDictionary *headerBiddingParams))complete;

//+ (void)requestS2SBuyerUidWithPlacementId:(nonnull NSString *)placementId
//                                     extra:(nullable NSDictionary *)extra
//                                completion:(nonnull void (^)(NSString *_Nullable buyerUid, NSError *_Nullable error))completion;

+ (void)forceCloseAdIfNeeded;

- (instancetype)initAdWithPlacementId:(nonnull NSString *)placementId;

- (instancetype)initAdWithPlacementId:(nonnull NSString *)placementId extra:(nullable NSDictionary *)extra;

- (void)load;

- (void)loadAdWithExtraDic:(nonnull NSDictionary *)ExtraDic;

/// check ads is ready
- (BOOL)isReady;
/// send win
- (void)notifyWin:(SDMWinInfo *)winInfo;
/// send loss
- (void)notifyLoss:(SDMLossInfo *)lossInfo;
/// destroy show info
- (void)destroy;
/// ads expired time
- (nullable NSDate *)getExpirationTimestamp;

- (nullable SDMAd *)getSDMAd;

- (BOOL)readyFilledWithExtraDic:(NSDictionary *)extraDic;

@end

NS_ASSUME_NONNULL_END
