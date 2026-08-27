//
//  ATAdsLgStRuleModel.h
//  AnyThinkSDK
//
//  Created by Captain on 2025/2/12.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <AnyThinkSDK/ATModel.h>

NS_ASSUME_NONNULL_BEGIN

/// 激励视频防作弊节点枚举
typedef NS_ENUM(NSInteger, ATAdRewardAntiCheatingNode) {
    /// 竞价阶段
    ATAdRewardAntiCheatingNode_Bidding = 1,
    /// 竞价响应阶段
    ATAdRewardAntiCheatingNode_BiddingResponse = 2,
    /// 广告源请求阶段
    ATAdRewardAntiCheatingNode_AdSourceRequest = 3,
    /// 广告源填充阶段
    ATAdRewardAntiCheatingNode_AdSourceFilling = 4,
    /// 竞价胜出/失败通知阶段
    ATAdRewardAntiCheatingNode_WinLossNotification = 5,
    /// 展示阶段
    ATAdRewardAntiCheatingNode_Display = 6
};

@interface ATAdsLgStRuleModel : ATModel

/// 验证开关
@property (nonatomic, assign) BOOL vf_switch;
//@property (nonatomic, copy) NSArray *hb_vf_types;
//@property (nonatomic, copy) NSArray *wf_vf_types;
//@property (nonatomic, copy) NSString *vf_sk;

/// 激励视频验证开关
@property (nonatomic, assign) BOOL vf_switch_rv;

/// 头部竞价激励视频验证类型列表，内含 ATAdRewardAntiCheatingNode
@property (nonatomic, copy) NSArray<NSNumber *> *hb_vf_types_rv; // 内含ATAdRewardAntiCheatingNode

/// 瀑布流激励视频验证类型列表，内含 ATAdRewardAntiCheatingNode
@property (nonatomic, copy) NSArray<NSNumber *> *wf_vf_types_rv; // 内含ATAdRewardAntiCheatingNode

/// 广告平台 ID
@property (nonatomic, assign) NSInteger networkFirmID;

@end

NS_ASSUME_NONNULL_END
