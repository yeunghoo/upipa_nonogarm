//
//  ATAdCacheTool.h
//  AnyThinkSDK
//
//  Created by shuai on 2025/12/31.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAdManager+Internal.h>

@class ATPlacementAdCache, ATAdObject;

NS_ASSUME_NONNULL_BEGIN

@interface ATAdCacheManager : NSObject

+ (instancetype)sharedManager;

#pragma mark - 存储

/// 存储缓存广告包装对象
- (void)cacheAd:(ATAdObject *)cacheAdModel;

#pragma mark - 请求检查

/// 检查广告源是否可以开始请求
/// @param placementId 广告位id
/// @param params 请求参数
/// @param requestId 请求id
/// @return 如果可以开始请求返回YES，否则返回NO
- (BOOL)checkCanStartAdSourceRequestWithPlacementId:(NSString *)placementId
                       loadingAdSourceRequestParams:(ATAdSourceRequestParams *)loadingAdSourceRequestParams
                lowPriceFilledAdSourceRequestParams:(ATAdSourceRequestParams *)lowPriceFilledAdSourceRequestParams;

#pragma mark - 读取

/// 获取价格最高的可用缓存(仅判断有效性 !self.expired && self.showTimes <= 0 && self.ready;）
/// - Parameters:
///   - placementId: 广告位ID
///   - unitId: 广告源ID
- (ATAdObject *)firstValidAdCacheWithPlacementId:(NSString *)placementId
                                          unitId:(nullable NSString *)unitId;

/// 获取ready的可展示的广告(过滤频次之类的6层过滤筛选，不会进行广告位维度的过滤)
/// - Parameters:
///   - placementId: 广告位ID
///   - unitId: 广告源ID
- (ATAdObject *)readiedAdCacheWithPlacementId:(NSString *)placementId
                                       unitId:(nullable NSString *)unitId
                                unreadyModels:(NSArray <ATAdObject *>*__autoreleasing *)adModels;

/// 获取即将展示或者ready的广告（会首选从广告位维度进行过滤）
/// - Parameters:
///   - placementID: 广告位ID
///   - unitId: 广告源ID
///   - requestId: 请求ID
///   - show: 是否即将展示
///   - error: 广告位维度的过滤信息以及最终没获取到广告的错误信息
///   - adModels: 没有ready的数据列表
- (ATAdObject *)readiedAdCacheWithPlacementId:(NSString*)placementID
                                       unitId:(nullable NSString *)unitId
                                    requestId:(nullable NSString *)requestId
                                       isShow:(BOOL)show
                         placementFilterError:(NSError **)error
                                unreadyModels:(NSArray <ATAdObject *>*__autoreleasing *)adModels;

/// 获取即将展示或者ready的广告（会首选从广告位维度进行过滤）
/// - Parameters:
///   - placementID: 广告位ID
///   - unitId: 广告源ID
///   - requestId: 请求ID
///   - show: 是否即将展示
///   - error: 广告位维度的过滤信息以及最终没获取到广告的错误信息
///   - trackData: 查询中生产的埋点数据
- (ATAdObject *)readiedAdCacheWithPlacementId:(NSString*)placementID
                                       unitId:(nullable NSString *)unitId
                                    requestId:(nullable NSString *)requestId
                                       isShow:(BOOL)show
                         placementFilterError:(NSError **)error
                                    trackData:(NSDictionary*__autoreleasing*)trackData;

/// 读取缓存广告数据数据列表(默认adx兜底，不会进行广告位维度的过滤)
/// - Parameters:
///   - placementId: 广告位id
///   - unitId: 广告源id
///   - filter: 是否需要过滤()
///   - inclued: 是否包含共享广告位的缓存
- (NSArray<ATAdObject *> *)readCacheWithPlacementId:(NSString *)placementId
                                             unitId:(nullable NSString *)unitId
                                          requestId:(nullable NSString *)requestId
                                           isFilter:(BOOL)filter
                            isIncluedSharePlacement:(BOOL)inclued;

#pragma mark - 删除

/// 删除对应的广告对象
/// @param ad 广告对象
- (void)removeWithAdModel:(ATAdObject *)ad;

/// 根据广告位id移除所有缓存
/// @param placementId 广告位id
- (void)removePlacementAdCacheWithPlacementId:(NSString *)placementId;

/// 根据条件移除缓存
/// @param placementId 广告位id
/// @param unitId 广告源id（可选，为空时根据placementId删除所有）
/// @param requestId 请求id（可选，为空时根据placementId删除所有）
- (void)removePlacementAdCacheWithPlacementId:(NSString *)placementId
                                       unitId:(nullable NSString *)unitId
                                    requestId:(nullable NSString *)requestId;

#pragma mark - Loss通知

/// 发送过期广告的loss通知
/// @param placementId 广告位id
/// @param requestId 请求id
- (void)sendLossForExpiredAdWithPlacementId:(NSString *)placementId
                                  requestId:(NSString *)requestId;

/// 发送过期广告的loss通知（带预加载模型）
/// @param placementId 广告位id
/// @param unitId 广告源id
/// @param requestId 请求id
/// @param preloadModel 预加载模型（可选）
- (void)sendLossForExpiredAdWithPlacementId:(NSString *)placementId
                                     unitId:(NSString *)unitId
                                  requestId:(NSString *)requestId
                               preloadModel:(nullable ATMgPreloadModel *)preloadModel;

#pragma mark - 辅助方法

/// 构建ADX缓存广告的额外信息字典
/// @param cache 缓存广告模型
/// @param placementID 广告位id
/// @param cacheInfoes 缓存信息数组
/// @return 额外信息字典
- (NSDictionary *)extraInfoWithAdxOfferCached:(ATAdObject *)cache
                                  placementID:(NSString *)placementID
                                  cacheInfoes:(NSArray<ATAdObject *> *)cacheInfoes;

@end

NS_ASSUME_NONNULL_END
