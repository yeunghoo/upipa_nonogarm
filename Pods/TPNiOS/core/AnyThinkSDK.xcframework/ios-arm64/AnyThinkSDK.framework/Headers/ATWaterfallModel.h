//
//  ATTempWaterfall.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2022/10/20.
//  Copyright © 2022 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>
#import <AnyThinkSDK/ATPlacementModel.h>
#import <AnyThinkSDK/ATMgPreloadModel.h>
#import <AnyThinkSDK/ATAdSourceRequestParams.h>
#import <AnyThinkSDK/ATSafeThreadArray.h>

typedef NS_ENUM(NSInteger, ATWaterfallType) {
    ATWaterfallTypeWaterfall = 0,
    ATWaterfallTypeFinal = 2
};

typedef NS_ENUM(NSInteger, ATUnitGroupFinishType) {
    ATUnitGroupFinishTypeFinished = 0,
    ATUnitGroupFinishTypeTimeout = 1,
    ATUnitGroupFinishTypeFailed = 2
};

NS_ASSUME_NONNULL_BEGIN

/**
 * ATWaterfallModel - 瀑布流模型
 * 管理广告源请求参数数组的排序、发送、状态更新等操作
 * 所有数组使用 ATAdSourceRequestParams 而非 ATUnitGroupModel
 */
@interface ATWaterfallModel : NSObject

@property (nonatomic, copy) NSString *requestID;
@property (nonatomic, copy) NSString *placementID;

/// 待发送的广告源请求参数数组
@property (nonatomic, strong) ATSafeThreadArray<ATAdSourceRequestParams *> *adSourceRequestParamsArray;

/// HB提前请求广告源数组
@property (nonatomic, strong) ATSafeThreadArray<ATAdSourceRequestParams *> *advanceAdSourceRequestParamsArray;

/// 动态出价广告源数组
@property (nonatomic, strong) ATSafeThreadArray<ATAdSourceRequestParams *> *dynamicAdSourceRequestParamsArray;

/// 已发送请求的广告源数组
@property (nonatomic, strong) ATSafeThreadArray<ATAdSourceRequestParams *> *requestSentAdSourceRequestParamsArray;

/// 已发送请求的HB提前请求广告源数组
@property (nonatomic, strong) ATSafeThreadArray<ATAdSourceRequestParams *> *advanceSentAdSourceRequestParamsArray;

/// 已发送请求的动态出价广告源数组
@property (nonatomic, strong) ATSafeThreadArray<ATAdSourceRequestParams *> *dynamicSentAdSourceRequestParamsArray;

/// 请求超时数量
@property (nonatomic, assign) NSUInteger numberOfTimeoutRequests;

/// 瀑布流类型
@property (nonatomic, assign) ATWaterfallType type;

/// 瀑布流是否正在加载
@property (nonatomic, assign, getter=isLoading) BOOL loading;

/// 加载API类型
@property (nonatomic, assign) ATLoadingAdApiType loadingApiType;

/// 广告位模型
@property (nonatomic, weak) ATPlacementModel *placement;

#pragma mark - 初始化

/// 初始化方法
/// @param adSourceRequestParamsArray 广告源请求参数数组
/// @param placementID 广告位ID
/// @param requestID 请求ID
- (instancetype)initWithAdSourceRequestParamsArray:(nullable NSArray<ATAdSourceRequestParams *> *)adSourceRequestParamsArray
                                       placementID:(NSString *)placementID
                                         requestID:(NSString *)requestID;

/// 初始化方法
- (instancetype)initWithPlacementID:(NSString *)placementID requestID:(NSString *)requestID;

#pragma mark - 广告源管理

/// 添加排序后的广告源请求参数数组
- (void)addRankedAndShuffledAdSourceRequestParams:(NSArray<ATAdSourceRequestParams *> *)params;

/// 标记广告源为已发起请求
- (void)requestAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 标记广告源为发送请求完成
- (void)finishAdSourceRequestParams:(ATAdSourceRequestParams *)params withType:(ATUnitGroupFinishType)type;

/// 添加待发送的广告源
- (void)addAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 插入待发送的广告源（内部会排序）
- (void)insertAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 插入待发送的广告源数组
- (void)insertAdSourceRequestParamsArray:(NSArray<ATAdSourceRequestParams *> *)paramsArray;

/// 移除已完成的请求广告源
- (void)removeFinishedRequestObject:(ATAdSourceRequestParams *)params;

/// 获取已填充的广告源数组
- (NSArray<ATAdSourceRequestParams *> *)getRequestFilledAdSourceRequestParams;

/// 根据 unitID 获取广告源
- (ATAdSourceRequestParams *)adSourceRequestParamsWithUnitID:(NSString *)unitID;

/// 获取价格最大的广告源
- (ATAdSourceRequestParams *)adSourceRequestParamsWithMaximumPrice;

/// 获取价格最小的广告源
- (ATAdSourceRequestParams *)adSourceRequestParamsWithMinimumPrice;

/// 获取瀑布流中所有广告源
- (NSMutableArray<ATAdSourceRequestParams *> *)getWaterfallAllAdSourceRequestParams;

/// 获取瀑布流中未发送请求的广告源
- (NSMutableArray<ATAdSourceRequestParams *> *)getWaterfallAllNotRequestAdSourceRequestParams;

/// 获取获取瀑布流中已发送请求的 adSourceRequestParams
- (NSMutableArray<ATAdSourceRequestParams *> *)getWaterfallAllSentRequestAdSourceRequestParams;

/// 获取广告源在 final waterfall 中的优先级
- (NSInteger)getPriorityInFinalWaterfallWithAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 请求中最大价格（过滤指定的unitID）
- (ATAdSourceRequestParams *)requestingAdSourceRequestParamsMaxPriceWithFilteredUnitID:(NSString *)unitID;

#pragma mark - 提前请求

/// 获取HB提前请求发送数量
- (NSInteger)getAdvanceSendCount;

/// 获取HB提前请求最大价格广告源
- (ATAdSourceRequestParams *)advanceAdSourceRequestParamsWithMaximumPrice;

/// HB提前请求插入待发送数组
- (void)insertAdvanceAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 标记广告源为已发送
- (void)markAdvanceRequestSendAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 标记广告源为已填充
- (void)markAdvanceRequestFillAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 获取提前请求已填充的广告源数组
- (NSArray<ATAdSourceRequestParams *> *)getAdvanceRequestFillAdSourceRequestParams;

#pragma mark - 动态出价

/// 获取动态出价提前请求发送数量
- (NSInteger)getDynamicSendCount;

/// 获取动态出价已填充的广告源数组
- (NSArray<ATAdSourceRequestParams *> *)getDynamicRequestFillAdSourceRequestParams;

/// 获取动态出价最大价格广告源
- (ATAdSourceRequestParams *)dynamicAdSourceRequestParamsWithMaximumPrice;

/// 标记广告源为已发送
- (void)markDynamicRequestSendAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 动态出价插入待发送数组
- (void)insertDynamicAdSourceRequestParams:(ATAdSourceRequestParams *)params;

/// 标记广告源为已填充
- (void)markDynamicRequestFillAdSourceRequestParams:(ATAdSourceRequestParams *)params;

#pragma mark - 其他

/// 获取第一个非HB的待处理广告源
- (ATAdSourceRequestParams *)firstPendingNonHBAdSourceRequestParamsWithNetworkFirmID:(NSInteger)nwFirmID;

/// 获取下一个价格
- (NSString *)getNextPrice:(NSString *)price array:(NSArray *)priceArray;

/// 获取同价格广告源数量
- (NSInteger)getEqualPriceRequestsQueuedWithSpacing:(NSInteger)divisionSpacing;

/// 判断瀑布流是否继续请求
- (BOOL)canContinueLoading:(BOOL)waitForSentRequests;

/// 遍历请求超时的广告源
- (void)enumerateTimeoutAdSourceRequestParamsWithBlock:(void(^)(ATAdSourceRequestParams *params))block;

#pragma mark - 状态

/// 更新广告源状态
- (void)updateAdSourceRequestParamsStatus:(ATAdSourceRequestParams *)params loadStatus:(ATAdSourceParamsLoadStatus)loadStatus;

@end

NS_ASSUME_NONNULL_END
