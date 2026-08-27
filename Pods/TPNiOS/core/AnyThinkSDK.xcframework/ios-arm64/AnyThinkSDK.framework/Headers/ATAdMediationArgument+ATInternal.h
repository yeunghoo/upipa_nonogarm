//
//  ATAdMediationArgument+ATInternal.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/15.
//  Copyright © 2024 AnyThink. All rights reserved.
//
#import <AnyThinkSDK/ATAdMediationArgument.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>
#import <AnyThinkSDK/ATBidInfo.h>


NS_ASSUME_NONNULL_BEGIN
typedef NS_ENUM(NSInteger, ATAdapterLoadAdType) {
    ATAdapterLoadTypeRequesting = 0,// S2S || 常规 发起请求
    ATAdapterLoadTypeC2SRequesting,// C2S 发起请求
    ATAdapterLoadTypeC2SBiding,// C2S biding
    ATAdapterLoadTypeS2SBiding,// S2S biding
    ATAdapterLoadTypeReadyFill,// 自填充

};

@interface ATAdMediationArgument (ATInternal)

/// Adapter触发加载类型
@property (nonatomic, assign) ATAdapterLoadAdType adapterLoadAdType;

/// 三方平台需要的广告信息
@property (nonatomic, strong) NSDictionary *statisticsInfoDic;

/// 广告混用类型 1
@property (nonatomic, assign) NSInteger jointAdType;

/// 请求合并开关
@property (nonatomic, assign) BOOL requestMerge;
/// 三方平台 预估价格数量 (admob, GM)
@property (nonatomic, assign) NSInteger networkEstimatePriceNum;
/// 三方平台 预估价格开关 (admob, GM)
@property (nonatomic, assign) BOOL networkEstimatePriceSwitch;
/// 点击区域
@property (nonatomic, strong) NSArray *mixAdClickAreaArray;

/// 回调类型
@property (nonatomic, assign) ATAdLoadedCallBackType requestFiledType;

/// bid 结果
@property (nonatomic, copy) NSDictionary *bidResult;

/// bid 信息
@property (nonatomic, strong) ATBidInfo *bidInfo;
/// admob 请求内容
@property (nonatomic, strong) NSString *admobRequestAgent;
/// 原生摇一摇开关
@property (nonatomic, assign) BOOL isNativeShakeSwitch;

/// 动态出价价格
@property (nonatomic, strong) NSString *dynamicFloorPrice;
/// 排序
@property (nonatomic, assign) NSInteger priority;

/// 展示价格开关(admob和gm)
@property (nonatomic, assign) BOOL isDisplayPriceSwitch;
@end

NS_ASSUME_NONNULL_END
