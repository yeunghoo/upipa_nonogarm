//
//  ATAdsLgStModel.h
//  AnyThinkSDK
//
//  Created by Captain on 2025/1/6.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <AnyThinkSDK/ATModel.h>
#import <AnyThinkSDK/ATAdsLgStRuleModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATAdsLgStModel : ATModel

/// 广告源防作弊规则字典，Key 为广告源 ID，Value 为对应的防作弊规则模型
@property (atomic, copy) NSDictionary<NSString *, ATAdsLgStRuleModel *> *adsLgStRules;

@end

NS_ASSUME_NONNULL_END
