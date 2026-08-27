//
//  ATAdObject.h
//  AnyThinkSDK
//
//  Created by li zhixuan on 2024/1/11.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATPlacementModel.h>
@class ATAdCustomEvent;
#import <AnyThinkSDK/ATAdSourceRequestParams.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>


NS_ASSUME_NONNULL_BEGIN

@class ATAdInterstitialEventPrams, ATLoadParams;
@class ATWaterfallModel,ATCustomContentResult,ATLoadParams;

@interface ATAdObject : NSObject
/// 是否触发过误点击
@property (nonatomic, assign) BOOL isTriggerAccidentalClick;
/// 原生混广告 本次点击是否为误点击
@property (nonatomic, assign) BOOL isCurrentAccidentalClick;

@property(nonatomic, assign)NSInteger priorityIndex;

@property(nonatomic, strong) __kindof UIView *bannerView;

@property (nonatomic, assign) NSInteger clickTag;

@property(nonatomic, copy) NSDictionary *assets;

@property(nonatomic, assign) BOOL adViewHasShowToWindow;

/// TODO: 检查多余的参数，从loadparams能读取的就删除，从loadparams读
@property (nonatomic, strong) ATPlacementModel *placementModel;

@property (nonatomic, strong) ATAdSourceRequestParams *adSourceRequestParams;

@property (nonatomic, strong) NSMutableArray<NSDictionary*> *unitGroupInfos;
// Priority is calculate by the index of the unit group in the placement's unit group list; zero is the highest
@property (nonatomic, assign) NSInteger priority;
@property (nonatomic, assign) NSInteger priorityLevel;//the order in witch this ad has been requested
@property (nonatomic, copy) NSString *requestID;

@property (nonatomic, copy) NSString *originalRequestID;
@property (nonatomic, assign) NSInteger showTimes;
@property (nonatomic, strong) NSDate *expireDate;
@property (nonatomic, strong) NSDate *cacheDate;
@property (nonatomic, assign, readonly)BOOL expired;
/// tk13时生成，用于返回show_id拼接
@property (nonatomic, strong) NSNumber *sdkTime;
// Third-party network native ad object.
@property (nonatomic, strong, nullable) id customObject;
/// 三方广告平台的广告位id
@property (nonatomic, copy) NSString *networkPlacementId;
/// 广告源id
@property (nonatomic, copy) NSString *unitID;
@property (nonatomic, copy) NSString *appID;

@property (nonatomic, assign) BOOL filledByReady;
@property (nonatomic, assign) BOOL filledByAutoloadOnClose;
@property (nonatomic, assign) NSInteger fillByfreshType;
@property (nonatomic, assign) BOOL defaultPlayIfRequired;
@property (nonatomic, assign) BOOL defaultAdxOfferCached;
@property (nonatomic, assign) BOOL renewed;
@property (nonatomic, copy) NSString *price;
@property (nonatomic, copy) NSString *sortPriorityLevel;
@property (nonatomic, copy) NSString *bidId;
@property (nonatomic, copy) NSString *tpBidId;
@property (nonatomic, weak) ATWaterfallModel *finalWaterfall;
@property (nonatomic, assign) NSInteger autoReqType;
@property (nonatomic, assign) BOOL isSharePlacementOffer;
/// placementMode maybe is share placement, so this save true placment id,
@property (nonatomic, copy) NSString *placementId;
@property (nonatomic, strong) ATAdCustomEvent *customEvent;
@property (nonatomic, copy) NSString *scene;
@property (nonatomic, copy) NSString *showCustomExt;
@property (nonatomic, strong) ATCustomContentResult *customContentResult;
@property (nonatomic, assign) BOOL isUserSetAd;
@property (nonatomic, copy) NSDictionary *developer_extraDic;
@property(nonatomic, assign) BOOL adHasReportImpression;
@property (nonatomic, strong) ATAdInterstitialEventPrams *showPrams;
@property (nonatomic, weak) UIViewController *currentInterstitialAdVc;
/// 关联的加载参数上下文
@property (nonatomic, strong) ATLoadParams *loadParams;

/// 初始化方法
- (instancetype)initWithPriority:(NSInteger)priority
                  placementModel:(ATPlacementModel *)placementModel
                       requestID:(NSString *)requestID
                          assets:(NSDictionary *)assets
           adSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams
                  finalWaterFall:(ATWaterfallModel *)finalWaterFall;

- (void)setupPriority:(NSInteger) priority
       placementModel:(ATPlacementModel*)placementModel
            requestID:(NSString*)requestID
               assets:(NSDictionary*)assets
adSourceRequestParams:(ATAdSourceRequestParams*)adSourceRequestParams
       finalWaterFall:(ATWaterfallModel *)finalWaterFall;

- (void)renewAdWithPlacementModel:(ATPlacementModel*)placementModel
                        requestID:(NSString*)requestID;

- (void)releasCustomObject;

- (NSString *)ecpm;

- (NSString *)bidFloor;

- (BOOL)ready;

- (void)destroyBanner;


#pragma mark - cache
/// 获取唯一标识符
@property (atomic, copy, readonly) NSString *identifier;

/// 广告源加载间隔时间状态
//@property (atomic, assign, readonly) BOOL upStatus;

/// 是否有效（showTimes <= 0, is ready, !expired, upStatus）
@property (atomic, assign, readonly) BOOL isValid;

/// 是否有效（不检查upStatus）
@property (atomic, assign, readonly) BOOL isValidWithoutUpstatus;

/// !self.expired && self.showTimes <= 0 && self.ready;
@property (atomic, assign, readonly) BOOL isValidInCache;

/// 有效状态标记 ???
//@property (atomic, assign) BOOL isValidStatus;

/// 是否为ADX兜底
@property (atomic, assign) BOOL isAdxFallBack;

@end

NS_ASSUME_NONNULL_END
