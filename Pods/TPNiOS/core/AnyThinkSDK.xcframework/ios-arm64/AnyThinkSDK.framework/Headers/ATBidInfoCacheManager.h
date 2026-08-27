//
//  ATBidInfoCacheManager.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 2020/4/28.
//  Copyright © 2020 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import <AnyThinkSDK/ATBidInfo.h>



NS_ASSUME_NONNULL_BEGIN

#pragma mark - 常量定义

/// Header Bidding 列表的字典键
#define ATHeaderBiddingListKey @"headerBiddingList"

/// Header Bidding 参数错误的字典键
#define ATHbParmeterErrorsKey @"hbParmeterErrors"

/// 当前单元组的字典键
#define ATCurrentUnitGroupsKey @"currentUnitGroups"

/// Direct Offer 广告源请求参数的字典键
#define ATDirectOfferAdSourceRequestParamsKey @"directOfferAdSourceRequestParams"

#pragma mark - 前向声明

@class ATUnitGroupModel;
@class ATPlacementModel;
@class ATWaterfallModel;
@class ATBidInfo;
@class ATAdSourceBidResultModel;
@class ATAdSourceRequestParams;
@class ATLoadParams;

#pragma mark - 类型定义

/**
 * @typedef StartBidBlock
 * @brief Header Bidding 开始的回调 Block
 * @param headerBiddingListDic Header Bidding 列表字典
 */
typedef void(^StartBidBlock)(NSDictionary * headerBiddingListDic);

#pragma mark - 类声明

/**
 * @class ATBidInfoCacheManager
 * @brief Header Bidding 竞价信息缓存管理器
 *
 * @discussion
 * 该类负责管理 Header Bidding 的竞价信息缓存，包括：
 * - 内存缓存：使用 ATSafeThreadDictionary 存储 ATAdSourceBidResultModel 对象
 * - 磁盘缓存：通过 ATADXBidInfoCacheManager 管理 ADX 和 Direct Offer 的磁盘缓存
 *
 * 缓存结构：
 * {
 *   placementID: {
 *     unitID: ATAdSourceBidResultModel
 *   }
 * }
 *
 * 核心功能：
 * 1. 保存竞价结果：保存 ATAdSourceBidResultModel（包含 bidInfo 和 adSourceRequestParams）
 * 2. 查询历史竞价：根据 placementID 和 unitID 查询有效的竞价信息
 * 3. 缓存失效管理：移除过期或无效的竞价信息
 * 4. Loss 通知：对过期的竞价信息发送 Loss 通知
 * 5. 磁盘持久化：ADX 和 Direct Offer 类型的竞价信息会持久化到磁盘
 *
 * 使用场景：
 * - Header Bidding 竞价成功后保存竞价信息
 * - 广告加载时查询是否有可用的历史竞价信息
 * - 竞价信息过期时发送 Loss 通知并清理缓存
 *
 * 线程安全：
 * - 使用 ATSafeThreadDictionary 保证线程安全
 * - 所有方法都可以在多线程环境下安全调用
 */
@interface ATBidInfoCacheManager : NSObject

#pragma mark - 单例方法

/**
 * @brief 获取共享实例
 * @return ATBidInfoCacheManager 的单例对象
 * @discussion 使用单例模式，确保全局只有一个缓存管理器实例
 */
+ (instancetype)sharedManager;

#pragma mark - 竞价信息保存

/**
 * @brief 保存竞价结果模型
 * @param resultModel 竞价结果模型，包含 bidInfo 和 adSourceRequestParams
 * @discussion
 * 将竞价结果保存到内存缓存，如果是 ADX 或 Direct Offer 类型，同时保存到磁盘。
 * 保存的 key 为 placementID，value 为字典，字典的 key 为 unitID，value 为 ATAdSourceBidResultModel。
 *
 * @note
 * - resultModel 和 resultModel.bidInfo 不能为 nil，否则不会保存
 * - ADX 和 Direct Offer 类型的竞价信息会自动持久化到磁盘
 */
- (void)saveAdSourceBidResultModel:(ATAdSourceBidResultModel*)resultModel;

#pragma mark - 竞价信息查询

/**
 * @brief 根据广告源请求参数查询缓存的竞价信息
 * @param adSourceRequestParams 广告源请求参数，包含 placementID 和 unitID
 * @param loadParams 加载参数，用于创建 resultModel（从磁盘加载时需要）
 * @return 缓存的 ATBidInfo 对象，如果不存在或已过期则返回 nil
 * @discussion
 * 查询流程：
 * 1. 先从内存缓存中查询（通过 placementID 和 unitID）
 * 2. 如果内存中没有，则从磁盘缓存中查询（ADX 类型）
 * 3. 如果从磁盘加载到有效的 bidInfo，会创建 resultModel 并保存到内存缓存
 *
 * @note
 * - 只返回有效的（isValid = YES）竞价信息
 * - 从磁盘加载的 bidInfo 会自动保存到内存缓存
 */
- (ATBidInfo*)getBidInfoCachedAdSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams loadParams:(ATLoadParams *)loadParams;

/**
 * @brief 根据历史竞价信息获取可用的广告源请求参数列表
 * @param placementID 广告位ID
 * @param hbParams Header Bidding 广告源请求参数数组
 * @param inhouseParams 内部广告源请求参数数组
 * @param s2sParams S2S 广告源请求参数数组
 * @param bksParams BKS 广告源请求参数数组
 * @param directParams Direct Offer 广告源请求参数数组
 * @param requestID 请求ID
 * @param placementModel 广告位模型
 * @param loadParams 加载参数，用于创建 resultModel 和发送 Loss 通知
 * @return 包含有效竞价信息的广告源请求参数数组
 * @discussion
 * 该方法会：
 * 1. 从内存缓存和磁盘缓存中查询所有广告源的历史竞价信息
 * 2. 筛选出有效的竞价信息（isValid = YES 且未过期）
 * 3. 将有效的 bidInfo 设置到对应的 adSourceRequestParams 中
 * 4. 对过期但未发送通知的竞价信息发送 Loss 通知
 * 5. 将使用过的竞价信息重新保存到缓存（用于后续使用）
 *
 * @note
 * - PMP 订单（isPMPType = YES）不会发起新的 bid 请求，直接使用缓存
 * - 如果广告源设置了 waterfallTimeOutSW，会跳过该广告源
 * - 过期的竞价信息会发送 ATLossAdExpiteType 类型的 Loss 通知
 */
- (NSMutableArray<ATAdSourceRequestParams *> *)adSourceRequestParamsWithHistoryBidInfoForPlacementID:(NSString *)placementID
                                                                                            hbParams:(NSArray<ATAdSourceRequestParams *> *)hbParams
                                                                                       inhouseParams:(NSArray<ATAdSourceRequestParams *> *)inhouseParams
                                                                                           s2sParams:(NSArray<ATAdSourceRequestParams *> *)s2sParams
                                                                                           bksParams:(NSArray<ATAdSourceRequestParams *> *)bksParams
                                                                                        directParams:(NSArray<ATAdSourceRequestParams *> *)directParams
                                                                                           requestID:(NSString *)requestID
                                                                                      placementModel:(ATPlacementModel *)placementModel
                                                            loadParams:(ATLoadParams *)loadParams;

#pragma mark - 竞价信息移除

/**
 * @brief 使指定广告位的竞价信息失效（仅从内存缓存移除）
 * @param placementID 广告位ID
 * @param unitGroupModel 单元组模型，包含 unitID
 * @discussion
 * 仅从内存缓存中移除指定的竞价信息，不会删除磁盘缓存。
 * 适用于临时失效的场景，如竞价信息被使用后需要标记为已使用。
 *
 * @note
 * - 只移除内存缓存，磁盘缓存不受影响
 * - 如果 placementID 或 unitID 不存在，操作会被忽略
 */
- (void)invalidateBidInfoForPlacementID:(NSString*)placementID unitGroupModel:(ATUnitGroupModel*)unitGroupModel;

/**
 * @brief 移除指定广告位的竞价信息（同时移除内存和磁盘缓存）
 * @param placementID 广告位ID
 * @param bidInfos 要移除的竞价信息数组
 * @discussion
 * 从内存缓存和磁盘缓存中移除指定的竞价信息。
 * 对于 ADX 和 Direct Offer 类型，会同时从磁盘中删除。
 *
 * @note
 * - 会同时移除内存和磁盘缓存
 * - ADX 和 Direct Offer 类型的竞价信息会从磁盘中删除
 * - 其他类型的竞价信息只从内存中删除
 */
- (void)removeBidInfoWithDiskForPlacementID:(NSString*)placementID bidInfos:(NSArray<ATBidInfo*>*)bidInfos;

/**
 * @brief 移除指定广告位的竞价信息（通过广告源请求参数数组）
 * @param placementID 广告位ID
 * @param adSourceRequestParamsArray 广告源请求参数数组
 * @discussion
 * 从 adSourceRequestParamsArray 中提取 bidInfo，然后调用 removeBidInfoWithDiskForPlacementID:bidInfos: 方法。
 * 这是一个便捷方法，避免外部需要手动提取 bidInfo。
 *
 * @note
 * - 只会移除有 bidInfo 的广告源请求参数
 * - 会同时移除内存和磁盘缓存
 */
- (void)removeBidInfoWithDiskForPlacementID:(NSString*)placementID adSourceRequestParamsArray:(NSArray<ATAdSourceRequestParams *>*)adSourceRequestParamsArray;

@end

NS_ASSUME_NONNULL_END
