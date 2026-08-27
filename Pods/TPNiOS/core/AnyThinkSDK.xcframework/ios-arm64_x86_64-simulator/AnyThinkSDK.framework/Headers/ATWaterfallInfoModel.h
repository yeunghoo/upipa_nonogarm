//
//  ATTempWaterfallWrapper.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2022/10/20.
//  Copyright © 2022 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATPlacementModel.h>
#import <AnyThinkSDK/ATAdSourceRequestParams.h>
@class ATAdObject;

NS_ASSUME_NONNULL_BEGIN

@class ATUnitGroupModel;
@class ATPlacementModel;
@class ATWaterfallModel;

typedef enum : NSUInteger {
    ATwaterfallModuleTypeStart = 1,
    ATWaterfallModuleTypeNext,
    ATWaterfallModuleTypeAdvance,
    ATWaterfallModuleTypeDynamic,
} ATWaterfallModuleType;

typedef enum : NSUInteger {
    ATLoadedCallbackTypeAdSourceStatusCached,
    ATLoadedCallbackTypeNormalRequest
} ATLoadedCallbackType;

@interface ATWaterfallInfoModel : NSObject

/// 共享广告位是否成功
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markIsSharePlacementSucceeded: 设置
@property (nonatomic, assign, readonly) BOOL isSharePlacementSucceeded;

/// 请求ID（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markRequestID: 设置
@property (nonatomic, copy, readonly) NSString *requestID;

/// 瀑布流模块类型（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markWaterfallModuleType: 设置
@property (nonatomic, assign, readonly) ATWaterfallModuleType waterfallModuleType;

/// 瀑布流是否结束
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markWaterFallfinished: 设置
@property (nonatomic, assign, readonly) BOOL waterFallfinished;

/// 整体流程是否结束
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markFinished: 设置
@property (nonatomic, assign, readonly) BOOL finished;

/// 加载开始时间（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markLoadStartDate: 设置
@property (nonatomic, strong, readonly) NSDate *loadStartDate;

/// 是否已填充
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markFilled: 设置
@property (nonatomic, assign, readonly, getter=isFilled) BOOL filled;

/// 当前瀑布流模型（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markWaterfall: 设置
@property (nonatomic, strong, readonly) ATWaterfallModel *waterfall;

/// 最终瀑布流模型（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markFinalWaterfall: 设置
@property (nonatomic, strong, readonly) ATWaterfallModel *finalWaterfall;

/// 默认瀑布流模型（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markDefaultWaterfall: 设置
@property (nonatomic, strong, readonly) ATWaterfallModel *defaultWaterfall;

/// 默认为waterfall,当为兜底模式时,为defaultWaterfall（线程安全，只读计算属性）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 getter 方法访问
@property (nonatomic, strong, readonly) ATWaterfallModel *currentUwaterfall;

/// Header Bidding 是否已触发
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHeaderBiddingFired: 设置
@property (nonatomic, assign, readonly) BOOL headerBiddingFired;

/// Header Bidding 是否失败
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHeaderBiddingFailed: 设置
@property (nonatomic, assign, readonly) BOOL headerBiddingFailed;

/// 是否在瀑布流中展示过
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHasBeenShowInWaterfall: 设置
@property (nonatomic, assign, readonly) BOOL hasBeenShowInWaterfall;

/// 是否在请求过动态出价广告源
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHasBeenLoadDynamicHBUnitGroup: 设置
@property (nonatomic, assign, readonly) BOOL hasBeenLoadDynamicHBUnitGroup;

/// 缓存的 Offer 数量（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markNumberOfCachedOffers: 设置
@property (nonatomic, assign, readonly) NSInteger numberOfCachedOffers;

/// 是否填充超时
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markIsFillTimeout: 设置
@property (nonatomic, assign, readonly) BOOL isFillTimeout;

// TODO: ADX 位置??
/// 缓存的 ADX Offer（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markAdxOfferCached: 设置
@property (nonatomic, strong, readonly, nullable) ATAdObject *adxOfferCached;

/// 加载回调类型（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markLoadedCallbackType: 设置
@property (nonatomic, assign, readonly) ATLoadedCallbackType loadedCallbackType;

/// 展示广告的最高优先级（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHighestPriorityOfShownAd: 设置
@property (nonatomic, assign, readonly) NSInteger highestPriorityOfShownAd;

/// bid 是否短超时（用于区分短超时完成和真正bid完成）
/// @note 线程安全：使用 _lock 锁保护，保证跨队列访问安全（loadQueue_t 和 headerBiddingLoad_Queue_t）
@property (nonatomic, assign, readonly) BOOL isBidingShortTimeout;

/// 所有HB广告源竞价完成状态（在headerBidingFinish回调时记录）
/// @note 线程安全：使用 _lock 锁保护，保证跨队列访问安全（loadQueue_t 和 headerBiddingLoad_Queue_t）
@property (nonatomic, assign, readonly) BOOL isAllAdSourceBiddingFinish;

/// 检查是否已发送过 HB win 通知
/// @discussion 用于判断是否需要发送 win 通知
/// @return YES 表示已发送，NO 表示未发送
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHBWinNotificationSent 设置
@property (nonatomic, assign, readonly) BOOL hasHBWinNotificationSent;

/// 策略解析成功开始竞价流程时间，毫秒（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markStartBidTime: 设置
@property (nonatomic, assign, readonly) NSInteger startBidTime;

/// 竞价请求时间，毫秒（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markBidRequestTime: 设置
@property (nonatomic, assign, readonly) NSInteger bidRequestTime;

/// WaterFall_HB 最大启动时间，bid 短超时，毫秒（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markHeaderBiddingRequestShortTimeout: 设置
@property (nonatomic, assign, readonly) NSInteger headerBiddingRequestShortTimeout;

/// Waterfall 填充等待时间，毫秒（线程安全）
/// @note 线程安全：使用 pthread_mutex_t 锁保护，通过 markWaterfallFilledWaitingTime: 设置
@property (nonatomic, assign, readonly) NSInteger waterfallFilledWaitingTime;

/// 销毁
- (void)destroy;

/// 移除缓存的 ADX Offer
- (void)removeAdxOfferCached;

/// 获取所有瀑布流 已填充最低价格
- (ATAdSourceRequestParams *)filledAdSourceRequestParamsWithMaximumPrice;

/// 获取填充的广告源价格，用于下一次加载期望的索引
- (ATAdSourceRequestParams *)filledAdSourceRequestParamsPriceNextLoadWithExpectedIndex:(NSInteger)expectedIndex isNeedBeyondEmpty:(BOOL)isNeedBeyondEmpty;

/// 获取所有已填充的广告源请求参数数组
- (NSArray<ATAdSourceRequestParams *> *)getAllAdSourceRequestParamsArray;

/// 初始化方法
+ (instancetype)waterfallInfoWithWaterfallModel:(ATWaterfallModel *)waterfallModel;

#pragma mark - status
/// 初始化 普通广告源状态 ATWaterFallLoader
- (void)initializeNormalAdSourceStatusAdSourceRequestParamsArray:(NSArray<ATAdSourceRequestParams *> *)adSourceRequestParamsArray;

/// 初始化 竞价广告源状态
- (void)initializeHBAdSourceStatusAdSourceRequestParamsArray:(NSArray<ATAdSourceRequestParams *> *)adSourceRequestParamsArray;

/// 更新 未返回结果的广告源 为失败 ATWaterFallLoader
- (void)updateAllAdSourceFailure;

/// 获取所有 请求ing 请求成功 竞价广告源  
- (NSArray<ATAdSourceRequestParams *> *)bidFilledAndRequestingStateModeAdSourceRequestParams;

/// 获取所有 请求ing 广告源请求参数
- (NSArray<ATAdSourceRequestParams *> *)getRequestingAllAdSourceRequestParams;

/// 获取bid成功,但未发起请求的广告源
- (NSArray<ATAdSourceRequestParams *> *)unUsedbidinfoAdSourceRequestParams;

/// 判断请求ing中的竞价广告源价格  是否比指定价格大
- (BOOL)existHigherPriceBiddingAdSourceRequestingWithCurrentAdSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams;

/// 判断请求ing中的 广告源价格是否比指定价格大
- (BOOL)existHigherPriceAdSourceRequestingWithCurrentAdSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams;

/// 返回值: 1:正在请求ing,2:正在bidding中 判断请求ing中的广告源价格是否比指定价格大 ATGeneralTool
- (NSArray<ATAdSourceRequestParams *> *)existHigherPriceRequestingAdWithCurrentAdSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams;

/// 获取bid成功,未发起请求的最高价 ATGeneralTool
- (ATAdSourceRequestParams *)higherPriceAdSourceBidSuccessAdSourceRequestParams;

/// 获取请求成功最高价
- (ATAdSourceRequestParams *)higherPriceAdSourceRequestSuccessfulAdSourceRequestParams;

/// 获取请求成功最高价,不包括指定ad
- (ATAdSourceRequestParams *)higherPriceAdSourceRequestSuccessfulExcludeUnitID:(nullable NSString *)unitID;

/// 判断是否所有的广告,请求完成 广告源加载超时算请求 ing ATWaterFallLoader ATWaterfallInfoModel
- (BOOL)isAllAdSourceFinish;

/// 判断是否所有的广告,请求完成 广告源加载超时算完成
- (BOOL)isAllAdSourceFinishExclusionTimeout;

/// 判断是否所有的HB广告源,竞价完成,用于成功失败回调
//- (BOOL)isAllAdSourceBiddingFinish;

/// 获取bid完成,但是没发请求的广告源
- (NSArray<ATAdSourceRequestParams *> *)getBidFinishNORequestAdSourceRequestParams;

/// 获取价格最大的 待发送广告源,(价格优先: 不包含超时的广告源)
- (ATAdSourceRequestParams *)getPrepareRequestingMaxhuaPriceStateModeWithCallSuccessfulType:(ATCallSuccessType)callSuccessfulType;

- (void)updateAdSourceRequestParamsStatus:(ATAdSourceRequestParams *)params loadStatus:(ATAdSourceParamsLoadStatus)loadStatus;

/// 获取S2S 请求失败的广告源,用于发起重试
- (NSArray<ATAdSourceRequestParams *> *)getAdSourceBiddingFailureAdSourceRequestParams;

- (void)recordsRequestTimeoutAdSourceRequestParams:(ATAdSourceRequestParams *)params;

#pragma mark - Bid 请求状态（线程安全）

/// 从 keyStr 中提取 bidType
/// @discussion 从完整的 keyStr（格式：placementID_requestID_S2S 或 placementID_requestID_BKS）中提取 bidType
/// @param keyStr 完整的 key 字符串
/// @return bidType，@"S2S"、@"BKS" 或 @""（空字符串表示普通类型）
+ (NSString *)bidTypeFromKeyStr:(NSString *)keyStr;

/// 检查指定 bid 类型是否正在请求中
/// @discussion 用于避免重复发起 bid 请求，支持 S2S、BKS 等不同类型
/// @param bidType bid 类型，@"S2S"、@"BKS" 或 @""（空字符串表示普通类型）
/// @return YES 表示正在请求中，NO 表示未请求
/// @note 使用 ATSafeThreadDictionary 保证线程安全
- (BOOL)isBidRequestingForBidType:(NSString *)bidType;

/// 标记指定 bid 类型开始请求
/// @discussion 在发起 bid 请求前调用，标记该类型正在请求中
/// @param bidType bid 类型，@"S2S"、@"BKS" 或 @""（空字符串表示普通类型）
/// @note 使用 ATSafeThreadDictionary 保证线程安全
- (void)markBidRequestStartForBidType:(NSString *)bidType;

/// 标记指定 bid 类型请求结束
/// @discussion 在 bid 请求完成后调用，清除请求中标记
/// @param bidType bid 类型，@"S2S"、@"BKS" 或 @""（空字符串表示普通类型）
/// @note 使用 ATSafeThreadDictionary 保证线程安全
- (void)markBidRequestEndForBidType:(NSString *)bidType;

#pragma mark - Advance Request 状态（线程安全）

/// 检查指定 bid 类型是否已发起过 advance request
/// @discussion 用于标记是否已经发起过提前请求
/// @param bidType bid 类型，@"S2S"、@"BKS" 或 @""（空字符串表示普通类型）
/// @return YES 表示已发起过，NO 表示未发起
/// @note 使用 ATSafeThreadDictionary 保证线程安全
- (BOOL)hasAdvanceRequestForBidType:(NSString *)bidType;

/// 标记指定 bid 类型已发起 advance request
/// @discussion 在发起 advance request 后调用，标记该类型已发起过
/// @param bidType bid 类型，@"S2S"、@"BKS" 或 @""（空字符串表示普通类型）
/// @note 使用 ATSafeThreadDictionary 保证线程安全
- (void)markAdvanceRequestForBidType:(NSString *)bidType;

#pragma mark - Dynamic HB UnitGroup（线程安全）

/// 获取动态 HB 广告源列表
/// @discussion 从保存的动态 HB 广告源列表中，筛选出与传入的 UnitModeArray 匹配的广告源
/// @param unitModeArray 需要匹配的广告源数组
/// @return 匹配的动态 HB 广告源数组
/// @note 使用 ATSafeThreadArray 保证线程安全，无需额外加锁
- (NSArray<ATAdSourceRequestParams *> *)getDynamicHBAdSourceWithAdSourceRequestParamsArray:(NSArray<ATAdSourceRequestParams *> *)adSourceRequestParamsArray;

/// 保存动态 HB 广告源列表
/// @discussion 保存动态出价的 HB 广告源列表，用于后续动态底价计算
/// @param adSourceRequestParamsArray 动态 HB 广告源请求参数数组
/// @note 使用 _lock 保证 removeAllObjects + addObjectsFromArray 的原子性
- (void)saveDynamicHBAdSourceRequestParamsArray:(NSArray<ATAdSourceRequestParams *> *)adSourceRequestParamsArray;

/// 清除动态 HB 广告源列表
/// @discussion 在动态底价计算完成后清除，避免内存泄漏
/// @note 使用 ATSafeThreadArray 保证线程安全，无需额外加锁
- (void)clearDynamicHBUnitGroup;

/// 检查是否存在动态 HB 广告源
/// @discussion 用于判断是否需要启动动态出价流程
/// @return YES 表示存在，NO 表示不存在
/// @note 使用 ATSafeThreadArray 保证线程安全，无需额外加锁
- (BOOL)hasDynamicHBUnitGroup;

#pragma mark - Bid Success UnitGroup（线程安全）

/// 保存 bid 成功的广告源
/// @discussion 在 bid 请求成功后保存，用于后续 S2S 重试等场景
/// @param adSourceRequestParams bid 成功的广告源请求参数
/// @note 使用 _lock 保证 containsObject + addObject 的原子性，避免重复添加
- (void)saveBidSuccessAdSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams;

/// 获取 bid 成功的广告源数组
/// @discussion 获取本次请求中所有 bid 成功的广告源列表
/// @return bid 成功的广告源请求参数数组
/// @note 使用 ATSafeThreadArray 保证线程安全，无需额外加锁
- (NSArray<ATAdSourceRequestParams *> *)getBidSuccessAdSourceRequestParamsArray;

/// 清除 bid 成功的广告源数组
/// @discussion 在 Header Bidding 流程完成后清除，避免内存泄漏
/// @note 使用 ATSafeThreadArray 保证线程安全，无需额外加锁
- (void)clearBidSuccessAdSourceRequestParamsArray;

#pragma mark - HB Win Notification Status（线程安全）

/// 保存 HB win 通知发送状态
/// @discussion 标记已发送过 win 通知，避免重复发送
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHBWinNotificationSent;

/// 设置 bid 短超时状态（线程安全）
/// @param isBidingShortTimeout YES 表示短超时，NO 表示正常
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markIsBidingShortTimeout:(BOOL)isBidingShortTimeout;

/// 设置所有广告源 bid 是否完成（线程安全）
/// @param isAllAdSourceBiddingFinish YES 表示完成，NO 表示未完成
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markIsAllAdSourceBiddingFinish:(BOOL)isAllAdSourceBiddingFinish;

/// 设置是否请求过动态出价广告源（线程安全）
/// @param hasBeenLoadDynamicHBUnitGroup YES 表示已请求，NO 表示未请求
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHasBeenLoadDynamicHBUnitGroup:(BOOL)hasBeenLoadDynamicHBUnitGroup;

/// 设置共享广告位是否成功（线程安全）
/// @param isSharePlacementSucceeded YES 表示成功，NO 表示失败
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markIsSharePlacementSucceeded:(BOOL)isSharePlacementSucceeded;

/// 设置瀑布流是否结束（线程安全）
/// @param waterFallfinished YES 表示结束，NO 表示未结束
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markWaterFallfinished:(BOOL)waterFallfinished;

/// 设置整体流程是否结束（线程安全）
/// @param finished YES 表示结束，NO 表示未结束
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markFinished:(BOOL)finished;

/// 设置是否已填充（线程安全）
/// @param filled YES 表示已填充，NO 表示未填充
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markFilled:(BOOL)filled;

/// 设置 Header Bidding 是否已触发（线程安全）
/// @param headerBiddingFired YES 表示已触发，NO 表示未触发
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHeaderBiddingFired:(BOOL)headerBiddingFired;

/// 设置 Header Bidding 是否失败（线程安全）
/// @param headerBiddingFailed YES 表示失败，NO 表示未失败
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHeaderBiddingFailed:(BOOL)headerBiddingFailed;

/// 设置是否在瀑布流中展示过（线程安全）
/// @param hasBeenShowInWaterfall YES 表示已展示，NO 表示未展示
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHasBeenShowInWaterfall:(BOOL)hasBeenShowInWaterfall;

/// 设置是否填充超时（线程安全）
/// @param isFillTimeout YES 表示超时，NO 表示未超时
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markIsFillTimeout:(BOOL)isFillTimeout;

/// 设置请求ID（线程安全）
/// @param requestID 请求ID
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markRequestID:(NSString *)requestID;

/// 设置瀑布流模块类型（线程安全）
/// @param waterfallModuleType 瀑布流模块类型
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markWaterfallModuleType:(ATWaterfallModuleType)waterfallModuleType;

/// 设置加载开始时间（线程安全）
/// @param loadStartDate 加载开始时间
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markLoadStartDate:(NSDate *)loadStartDate;

/// 设置当前瀑布流模型（线程安全）
/// @param waterfall 当前瀑布流模型
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markWaterfall:(ATWaterfallModel *)waterfall;

/// 设置最终瀑布流模型（线程安全）
/// @param finalWaterfall 最终瀑布流模型
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markFinalWaterfall:(ATWaterfallModel *)finalWaterfall;

/// 设置默认瀑布流模型（线程安全）
/// @param defaultWaterfall 默认瀑布流模型
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markDefaultWaterfall:(ATWaterfallModel *)defaultWaterfall;

/// 设置缓存的 Offer 数量（线程安全）
/// @param numberOfCachedOffers 缓存的 Offer 数量
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markNumberOfCachedOffers:(NSInteger)numberOfCachedOffers;

/// 设置缓存的 ADX Offer（线程安全）
/// @param adxOfferCached 缓存的 ADX Offer，可为 nil
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markAdxOfferCached:(ATAdObject *_Nullable)adxOfferCached;

/// 设置加载回调类型（线程安全）
/// @param loadedCallbackType 加载回调类型
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markLoadedCallbackType:(ATLoadedCallbackType)loadedCallbackType;

/// 设置展示广告的最高优先级（线程安全）
/// @param highestPriorityOfShownAd 展示广告的最高优先级
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHighestPriorityOfShownAd:(NSInteger)highestPriorityOfShownAd;

/// 设置策略解析成功开始竞价流程时间（线程安全）
/// @param startBidTime 开始竞价流程时间，毫秒
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markStartBidTime:(NSInteger)startBidTime;

/// 设置竞价请求时间（线程安全）
/// @param bidRequestTime 竞价请求时间，毫秒
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markBidRequestTime:(NSInteger)bidRequestTime;

/// 设置 WaterFall_HB 最大启动时间（线程安全）
/// @param headerBiddingRequestShortTimeout bid 短超时，毫秒
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markHeaderBiddingRequestShortTimeout:(NSInteger)headerBiddingRequestShortTimeout;

/// 设置 Waterfall 填充等待时间（线程安全）
/// @param waterfallFilledWaitingTime 填充等待时间，毫秒
/// @note 使用 pthread_mutex_t 保证线程安全
- (void)markWaterfallFilledWaitingTime:(NSInteger)waterfallFilledWaitingTime;

@end

NS_ASSUME_NONNULL_END
