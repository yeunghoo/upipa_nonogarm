//
//  ATAdInitArgument.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/3/22.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAPI.h>

NS_ASSUME_NONNULL_BEGIN


@interface ATAdInitArgument : NSObject

/// 广告平台配置信息
@property (nonatomic, strong) NSDictionary *serverContentDic;

/// 开发者透传配置
@property (nonatomic, strong) NSDictionary *localInfoDic;

@property (nonatomic,copy)NSString *placementID;

/// 是否限制GDPR,包含个性化 默认为NO
@property (nonatomic, assign)  BOOL limitGdprConsent;

/// 是否限制GDPR, 默认为NO
@property (nonatomic, assign)  BOOL limitGdpr;

/// 是否限制CCPA,默认为NO
@property (nonatomic, assign) BOOL complyWithCCPA;

/// 是否限制COPPA,默认为NO
@property (nonatomic, assign) BOOL complyWithCOPPA;
/// 是否为debug模式
@property (nonatomic, assign) BOOL isDebugger;
/// 是否限制获取idfa, 默认为NO(部分adn支持)
@property (nonatomic, assign) BOOL limitIdfa;


/// 个性化广告
@property (nonatomic, assign) ATPersonalizedAdState personalizedAdState;
/// extraDic
@property (nonatomic, strong) NSDictionary *extraDic;

@end



NS_ASSUME_NONNULL_END
