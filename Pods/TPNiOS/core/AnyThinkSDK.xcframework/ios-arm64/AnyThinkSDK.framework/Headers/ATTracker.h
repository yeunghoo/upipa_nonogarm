//
//  ATTracker.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 19/04/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAdObject.h>
#import <AnyThinkSDK/ATTrackerInfo.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ATADTrackType) {
    ATADTrackTypeADRequest = 1, // 广告源请求
    ATADTrackTypeADRecalledSuccessfully = 2, // 广告源填充
    ATADTrackTypeADRecallFailed = 3,
    ATADTrackTypeADImpression = 4, // 广告展示
    ATADTrackTypeADRefreshShow = 5,
    ATADTrackTypeADClicked = 6, // 广告点击
    ATADTrackTypeVideoPlayed = 7,
    ATADTrackTypeVideoStart = 8,
    ATADTrackTypeVideoEnd = 9,
    ATADTrackTypeLoad = 10,
    ATADTrackTypeBidSort = 11, // bid结果上报
    ATADTrackTypeLoadResult = 12,// 加载成功
    ATADTrackTypeShowAPICall = 13, // 广告show API
    ATADTrackTypeEntryScenario = 16,// 上报场景
    ATADTrackTypeEntryLaunch = 21,
    ATADTrackTypeWin = 22,     // 比价SDK竞胜
    ATADTrackTypeLoss = 23,    // 比价SDK竞败
    ATADTrackTypeWinLoss = 24,    // win loss
    ATADTrackTypeRewarded = 25,    // 触发激励
    ATADTrackTypeComparePrice = 26, // 多聚合比价
    ATADTrackTypeUploadBrush = 27, // 刷子上报
    ATADTrackTypeXADClick = 28, // 扣点击上报
};

@class ATSafeThreadDictionary, ATTrackingSettingsModel;
/**
 * 类职责概述（TK 埋点中心）
 *
 * - 负责广告相关 TK 事件的采集、缓冲、与按策略上传（HTTP/TCP 由底层统一处理）。
 * - 提供点击、展示、比价胜负、冷启动、外部 API 触发等多类事件的对外接口。
 * - 内部统一将事件先写入数据库，按“实时/非实时”策略选择立即上传或等待轮询定时器。
 * - 关键并发策略：使用 TK 专用串行队列与信号量保证“查询→标记发送中→网络上传”过程的原子性。
 * - 过滤策略：受远端下发的 `trackingSetting` 控制，按网络、广告格式、事件类型决定是否跳过或实时上传。
 * - 重要边界：Debugger 模式下不采集；当 TK 总开关关闭或事件数据不合法时直接忽略。
 */
@interface ATTracker : NSObject

// TODO: 使用统一单例宏声明，目前因为tk类对外暴露，没有调整
+ (instancetype)sharedTracker;

/// 更新策略
/// @param trackingSetting 新的追踪与上报策略快照
- (void)updateTrackingSetting:(ATTrackingSettingsModel *)trackingSetting;

/// 轮询定时器触发：发送缓存数据
- (void)sendCachedTrackers;

/// 通用发送tk数据入口
- (void)appendTKDataElement:(NSDictionary *)dataElement
                  trackType:(ATADTrackType)trackType
             placementModel:(ATPlacementModel *)placementModel
              networkFirmID:(NSInteger)networkFirmID;

@end

NS_ASSUME_NONNULL_END
