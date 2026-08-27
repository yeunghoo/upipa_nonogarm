//
//  ATAdSourceRequestParams.h
//  AnyThinkSDK
//
//  Created on 2024.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AnyThinkSDK/ATAdEnums.h>

@class ATUnitGroupModel;
@class ATBidInfo;
@class ATLoadParams;
@class ATSafeThreadDictionary;
@class ATAdSourceTrackModel;
@class ATAdAdapterManager;

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ATAdSourceParamsLoadStatus) {
    ATAdSourceParamsLoadAwaitSendStatus = 0,
    ATAdSourceParamsLoadBiddingStatus = 1,
    ATAdSourceParamsLoadBidSucceedStatus = 2,
    ATAdSourceParamsLoadBidFailureStatus = 3,
    
    ATAdSourceParamsLoadBidShortTimeoutStatus,// 废弃
    ATAdSourceParamsLoadBidLongTimeoutStatus,// 废弃
    
    ATAdSourceParamsLoadRequestingStatus = 6,
    
    ATAdSourceParamsLoadRequestSucceedStatus = 7,
    ATAdSourceParamsLoadRequestFailureStatus = 8,
    ATAdSourceParamsLoadRequestTimeoutStatus,// 废弃
};

/**
 * ATAdSourceRequestParams - 广告源请求参数模型
 *
 * 核心设计理念：
 * 1. 统一上下文封装：将广告源相关的所有上下文信息（unitGroupModel、bidInfo、关联关系等）封装在一个对象中
 * 2. 解耦设计：消除 ATUnitGroupModel 与 ATBidInfo 之间的直接引用，避免循环依赖
 * 3. 线程安全：竞价信息（bidInfo）和关联关系（next/win）的读写操作使用互斥锁保护
 * 4. 生命周期管理：通过 weak 引用管理广告源之间的关联关系，避免循环引用
 *
 * 使用场景：
 * - 广告加载流程：从 ATLoadFilterService 创建后，在整个加载链路中传递
 * - 瀑布流管理：ATWaterfallModel 使用 ATAdSourceRequestParams 数组管理广告源列表
 * - 缓存保存：ATAdOfferCacheModel 持有 ATAdSourceRequestParams，用于后续广告展示和 win/loss 通知
 * - Header Bidding：通过 bidInfo 属性管理竞价信息，通过 nextAdSourceRequestParams 和 winAdSourceRequestParams 管理关联关系
 *
 * 架构优势：
 * - 单一数据源：所有广告源相关信息都通过 ATAdSourceRequestParams 访问，避免数据不一致
 * - 易于扩展：新增广告源相关属性只需在 ATAdSourceRequestParams 中添加，无需修改多个模型类
 * - 清晰的数据流：从创建到缓存保存，整个流程中传递的都是 ATAdSourceRequestParams，代码更清晰
 */
@interface ATAdSourceRequestParams : NSObject

#pragma mark - 基础信息（只读）

/**
 * 请求ID
 * 标识本次广告加载请求的唯一ID，从 ATLoadParams 中获取
 */
@property (nonatomic, copy, readonly) NSString *requestId;

/**
 * 广告位ID
 * 标识广告位的唯一ID，从 ATLoadParams 中获取
 */
@property (nonatomic, copy, readonly) NSString *placementID;

/**
 * 广告源单元ID
 * 标识广告源的唯一ID，从 ATUnitGroupModel 中获取
 */
@property (nonatomic, copy, readonly) NSString *unitID;

#pragma mark - 核心模型

/**
 * 广告源单元组模型
 * 包含广告源的基础配置信息（网络ID、价格、适配器类等）
 * 只读属性，在初始化时设置，后续不可修改
 */
@property (nonatomic, strong, readonly) ATUnitGroupModel *unitGroupModel;

/**
 * 竞价信息（线程安全）
 * 仅 Header Bidding 类型的广告源会有此信息
 * 线程安全：通过 bidInfo 和 markBidInfo: 方法访问，内部使用互斥锁保护
 * 可能为 nil（非 HB 广告源或尚未完成竞价）
 * @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 bidInfo 和 markBidInfo: 方法访问
 */
@property (nonatomic, strong, readonly, nullable) ATBidInfo *bidInfo;

/**
 * 适配器管理对象（线程安全）
 * 加载/展示阶段持有该广告源对应的三方适配器（ATAdAdapterManager）。
 * 生命周期与本次请求的广告源一致，加载结束/失败/竞败时通过 clearAdapterManager 释放，避免被
 * placement 配置缓存（ATUnitGroupModel）长期持有而泄露。
 * 注意：winloss 上报使用的 adapter 仍由 bidInfo.adapterModel 快照持有，与此属性各司其职。
 * @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 adapterManager 和 markAdapterManager:/clearAdapterManager 方法访问
 */
@property (nonatomic, strong, readonly, nullable) ATAdAdapterManager *adapterManager;

/// 广告源展示的次数（线程安全）
/// @discussion 记录广告源被展示的次数
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 showTimes 和 markShowTimes: 方法访问
@property (nonatomic, assign, readonly) NSInteger showTimes;

/// 广告源是否触发过点击（线程安全）
/// @discussion 标识广告源是否已经触发过点击事件
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 adReportClicked 和 markAdReportClicked: 方法访问
@property (nonatomic, assign, readonly) BOOL adReportClicked;

#pragma mark - 广告源追踪信息

/// 广告源追踪信息模型
/// 记录广告源在加载和展示过程中的各种时间戳和状态（线程安全由 ATAdSourceTrackModel 内部保证）
/// 在 ATAdSourceRequestParams 初始化时创建，生命周期与 ATAdSourceRequestParams 一致
@property (nonatomic, strong, readonly) ATAdSourceTrackModel *adSourceTrackModel;

#pragma mark - 关联广告源（weak 引用，用于 win/loss 通知）

/**
 * 下一个广告源请求参数（线程安全）
 * 用于 Header Bidding 的 win/loss 通知，标识当前广告源的下一个广告源
 * weak 引用，避免循环引用
 * 仅在 Header Bidding 场景下使用
 * @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 nextAdSourceRequestParams 和 markNextAdSourceRequestParams: 方法访问
 */
@property (nonatomic, weak, readonly, nullable) ATAdSourceRequestParams *nextAdSourceRequestParams;

/**
 * 竞胜广告源请求参数（线程安全）
 * 用于 Header Bidding 的 win/loss 通知，标识竞胜的广告源
 * weak 引用，避免循环引用
 * 仅在 Header Bidding 场景下使用
 * @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 winAdSourceRequestParams 和 markWinAdSourceRequestParams: 方法访问
 */
@property (nonatomic, weak, readonly, nullable) ATAdSourceRequestParams *winAdSourceRequestParams;

#pragma mark - 加载状态管理（线程安全）

/**
 * 加载状态
 * 标识广告源在加载流程中的当前状态（待发送、竞价中、请求中等）
 * 线程安全：通过 markLoadStatus: 方法设置，内部使用互斥锁保护
 * 默认值为 ATAdSourceParamsLoadAwaitSendStatus（待发送）
 */
@property (nonatomic, assign, readonly) ATAdSourceParamsLoadStatus loadStatus;

/// 询价开始时间戳，毫秒（线程安全）
/// @discussion 记录广告源发起询价请求的时间，对应 tk11:bid_req_start_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 bidReqStartT 和 markBidReqStartT: 方法访问
@property (nonatomic, assign, readonly) NSInteger bidReqStartT;

/// 广告源发起请求时间戳，毫秒（线程安全）
/// @discussion 记录广告源发起加载请求的时间，对应 tk1:req_start_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 reqStartT 和 markReqStartT: 方法访问
@property (nonatomic, assign, readonly) NSInteger reqStartT;

/// 数据填充时间戳，毫秒（线程安全）
/// @discussion 记录广告数据填充的时间，对应 tk11/tk2:ft_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 ftT 和 markFtT: 方法访问
@property (nonatomic, assign, readonly) NSInteger ftT;

/// 素材加载成功/询价成功时间戳，毫秒（线程安全）
/// @discussion 记录素材加载成功或询价成功的时间，对应 tk11/tk2:filled_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 filledT 和 markFilledT: 方法访问
@property (nonatomic, assign, readonly) NSInteger filledT;

/// bid token 获取成功间隔，毫秒（线程安全）
/// @discussion 记录 Header Bidding token 获取成功的时间，对应 tk11 bidresponselist:bid_token_succ_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 bidTokenSuccTs 和 markBidTokenSuccTs: 方法访问
@property (nonatomic, assign, readonly) NSInteger bidTokenSuccTs;

/// bid token 获取成功时间戳，毫秒（线程安全）
/// @discussion 记录 Header Bidding token 获取成功的时间，对应 tk11 bidresponselist:bid_token_succ_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 bidTokenSuccT 和 markBidTokenSuccT: 方法访问
@property (nonatomic, assign, readonly) NSInteger bidTokenSuccT;

/// 发起 bid 接口时间戳，毫秒（线程安全）
/// @discussion 记录发起 bid 接口请求的时间，对应 tk11 bidresponselist:bid_start_t
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 bidStartT 和 markBidStartT: 方法访问
@property (nonatomic, assign, readonly) NSInteger bidStartT;

/// bid 接口请求时间戳，毫秒（线程安全）
/// @discussion 记录 bid 接口请求的时间戳，对应 tk11:bid_req_api_ts
/// @note 线程安全由 pthread_mutex_t _lock 锁保证，通过 bidReqApiTs 和 markBidReqApiTs: 方法访问
@property (nonatomic, assign, readonly) NSInteger bidReqApiTs;

/**
 * 设置加载状态
 * 线程安全方法，用于更新广告源的加载状态
 *
 * @param loadStatus 新的加载状态
 *
 * 线程安全说明：
 * - 使用互斥锁保护，可在多线程环境下安全调用
 * - 如果新状态与当前状态相同（且不是 AwaitSendStatus），则跳过更新
 *
 * 使用场景：
 * - 初始化时设置初始状态
 * - 竞价流程中更新状态（开始竞价、竞价成功、竞价失败等）
 * - 请求流程中更新状态（开始请求、请求成功、请求失败等）
 */
- (void)markLoadStatus:(ATAdSourceParamsLoadStatus)loadStatus;

/**
 * 设置询价开始时间戳
 * @param bidReqStartT 询价开始时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markBidReqStartT:(NSInteger)bidReqStartT;

/**
 * 设置广告源发起请求时间戳
 * @param reqStartT 广告源发起请求时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markReqStartT:(NSInteger)reqStartT;

/**
 * 设置数据填充时间戳
 * @param ftT 数据填充时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markFtT:(NSInteger)ftT;

/**
 * 设置素材加载成功/询价成功时间戳
 * @param filledT 素材加载成功或询价成功时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markFilledT:(NSInteger)filledT;

/**
 * 设置 bid token 获取成功间隔
 * @param bidTokenSuccTs token 获取成功时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markBidTokenSuccTs:(NSInteger)bidTokenSuccTs;

/**
 * 设置 bid token 获取成功时间戳
 * @param bidTokenSuccT token 获取成功时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markBidTokenSuccT:(NSInteger)bidTokenSuccT;

/**
 * 设置发起 bid 接口时间戳
 * @param bidStartT 发起 bid 接口时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markBidStartT:(NSInteger)bidStartT;

/**
 * 设置 bid 接口请求时间戳
 * @param bidReqApiTs bid 接口请求时间戳，毫秒
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markBidReqApiTs:(NSInteger)bidReqApiTs;

#pragma mark - 初始化方法

/**
 * 初始化方法
 * 创建广告源请求参数对象
 *
 * @param unitGroupModel 广告源单元组模型，不能为 nil
 * @param loadParams 加载参数模型，用于获取 requestId 和 placementID，不能为 nil
 * @return 初始化后的实例
 *
 * 使用示例：
 *   ATAdSourceRequestParams *params = [[ATAdSourceRequestParams alloc] 
 *       initWithUnitGroupModel:unitGroup loadParams:loadParams];
 */
- (instancetype)initWithUnitGroupModel:(ATUnitGroupModel *)unitGroupModel
                            loadParams:(ATLoadParams *)loadParams;

/**
 * 禁用默认初始化方法
 * 必须使用 initWithUnitGroupModel:loadParams: 方法初始化
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * 禁用 new 方法
 * 必须使用 initWithUnitGroupModel:loadParams: 方法初始化
 */
+ (instancetype)new NS_UNAVAILABLE;

#pragma mark - 竞价信息管理（线程安全）

/**
 * 设置竞价信息
 * 线程安全方法，用于设置或更新 Header Bidding 的竞价信息
 *
 * @param bidInfo 竞价信息对象，可以为 nil（清除竞价信息）
 *
 * 使用场景：
 * - Header Bidding 竞价成功后，设置竞价信息
 * - 竞价失败或过期时，设置为 nil
 *
 * 注意：此方法内部使用互斥锁保护，可在多线程环境下安全调用
 */
- (void)markBidInfo:(nullable ATBidInfo *)bidInfo;

/**
 * 设置适配器管理对象
 * 线程安全方法，加载阶段为广告源绑定其对应的三方适配器（ATAdAdapterManager）。
 *
 * @param adapterManager 适配器管理对象，可以为 nil
 *
 * 注意：此方法内部使用互斥锁保护，可在多线程环境下安全调用
 */
- (void)markAdapterManager:(nullable ATAdAdapterManager *)adapterManager;

/**
 * 清理适配器管理对象
 * 线程安全方法，加载结束/失败/竞败、不再需要 adapter 去 load/show 时调用，
 * 切断广告源对 adapter 的强引用，打破并避免 retain cycle。
 * 内部统一异步切换到主线程释放，与三方 SDK 的释放约定保持一致。
 */
- (void)clearAdapterManager;

/**
 * 设置下一个广告源请求参数
 * 线程安全方法，用于设置 Header Bidding 中的下一个广告源
 *
 * @param nextAdSourceRequestParams 下一个广告源请求参数，可以为 nil
 *
 * 使用场景：
 * - 在 Header Bidding 流程中，建立广告源之间的关联关系
 * - 用于 win/loss 通知时确定下一个广告源
 *
 * 注意：使用 weak 引用，避免循环引用
 */
- (void)markNextAdSourceRequestParams:(nullable ATAdSourceRequestParams *)nextAdSourceRequestParams;

/**
 * 设置竞胜广告源请求参数
 * 线程安全方法，用于设置 Header Bidding 中的竞胜广告源
 *
 * @param winAdSourceRequestParams 竞胜广告源请求参数，可以为 nil
 *
 * 使用场景：
 * - 在 Header Bidding 流程中，记录竞胜的广告源
 * - 用于 win/loss 通知时确定竞胜广告源
 *
 * 注意：使用 weak 引用，避免循环引用
 */
- (void)markWinAdSourceRequestParams:(nullable ATAdSourceRequestParams *)winAdSourceRequestParams;

#pragma mark - 运行时状态管理（线程安全）

/**
 * 设置广告源展示次数
 * 线程安全方法，用于更新广告源的展示次数
 *
 * @param showTimes 新的展示次数
 *
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markShowTimes:(NSInteger)showTimes;

/**
 * 设置广告源点击状态
 * 线程安全方法，用于标记广告源是否已触发点击
 *
 * @param adReportClicked YES 表示已触发点击，NO 表示未触发
 *
 * @note 线程安全由 pthread_mutex_t _lock 锁保证
 */
- (void)markAdReportClicked:(BOOL)adReportClicked;

#pragma mark - 便捷访问方法

/**
 * 判断是否为 Header Bidding 广告源
 * 通过 unitGroupModel.headerBidding 属性判断
 *
 * @return YES 表示是 Header Bidding 广告源，NO 表示普通广告源
 */
- (BOOL)isHeaderBidding;

/**
 * 判断是否有竞价信息
 * 线程安全方法，检查 bidInfo 是否为 nil
 *
 * @return YES 表示有竞价信息，NO 表示没有
 */
- (BOOL)hasBidInfo;

/**
 * 获取竞价价格
 * 线程安全方法，从 bidInfo 中获取价格字符串
 *
 * @return 竞价价格字符串，如果没有竞价信息则返回 nil
 */
- (nullable NSString *)getBidPrice;

/**
 * 获取竞价排序优先级
 * 线程安全方法，从 bidInfo 中获取排序优先级
 *
 * @return 竞价排序优先级（NSDecimalNumber），如果没有竞价信息则返回 nil
 */
- (nullable NSDecimalNumber *)getBidSortPriorityLevel;

/**
 * 获取联合广告类型
 * 根据广告源类型和竞价信息（如果是 ADX）确定联合广告类型
 *
 * @return 联合广告类型枚举值
 *
 * 特殊处理：
 * - 对于 ADX 类型的广告源，如果存在 bidInfo，会根据 bidInfo.adxMixType 确定类型
 * - 其他情况直接返回 unitGroupModel.jointAdType
 */
- (ATUnitGroupJointAdType)jointAdType;

/**
 * 判断是否为 PMP 类型
 * 线程安全方法，检查 bidInfo 是否为 PMP 类型
 *
 * @return YES 表示是 PMP 类型，NO 表示不是
 *
 * PMP 类型判断：
 * - 如果 bidInfo 存在且 bidInfo.isPMPType 返回 YES，则返回 YES
 * - 否则返回 NO
 *
 * 使用场景：
 * - 判断广告源是否为 PMP 类型，用于不同的处理逻辑
 * - 在缓存检查、过滤等场景中使用
 */
- (BOOL)isPMPType;

/**
 * 判断 bidInfo 是否为无价格类型
 * 线程安全方法，检查 bidInfo 是否为无价格类型
 *
 * @return YES 表示 bidInfo 存在且为无价格类型，NO 表示不是
 *
 * 无价格类型判断：
 * - 如果 bidInfo 存在且 bidInfo.isNoPrice 返回 YES，则返回 YES
 * - 否则返回 NO
 *
 * 线程安全说明：
 * - 读取 bidInfo 时使用互斥锁保护
 * - 确保在多线程环境下读取的一致性
 *
 * 使用场景：
 * - 判断竞价信息是否为无价格类型，用于价格处理逻辑
 * - 在价格计算、上报等场景中使用
 */
- (BOOL)isBidInfoNoPrice;

@end

NS_ASSUME_NONNULL_END
