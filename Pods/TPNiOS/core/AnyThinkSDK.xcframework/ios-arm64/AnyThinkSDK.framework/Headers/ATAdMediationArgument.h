//
//  ATAdMediationArgument.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/15.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATPlacementModel.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATAdMediationArgument : NSObject

/// 广告类型
@property (nonatomic, assign) NSInteger format;
/// unitId
@property (nonatomic, copy) NSString *unitID;

/// 广告位ID
@property (nonatomic, copy) NSString *placementID;

/// 广告源配置信息
@property (nonatomic, copy) NSDictionary *serverContentDic;

/// 开发者透传配置
@property (nonatomic, copy) NSDictionary *localInfoDic;

/// 三方广告平台 广告请求数量
@property(nonatomic, assign) NSInteger networkRequestNum;

/// 三方平台 networkFirmID
@property(nonatomic, assign) NSInteger networkFirmID;

/// 加载广告传入的控制器
@property (nonatomic, weak) UIViewController *viewController;

/// requestID
@property (nonatomic, copy) NSString *requestID;

/// BannerSize
@property (nonatomic, assign) CGSize bannerSize;
/// NativeSize
@property (nonatomic, assign) CGSize nativeSize;

/// S2S bid id
@property (nonatomic, copy) NSString *bidId;
/// network币种
@property (nonatomic, assign) NSInteger networkCurrencyType;

@property (nonatomic, assign)CGFloat gspRates;
@property (nonatomic, assign)BOOL hasAdmobHB;
@property (nonatomic, assign)ATPlacementModelAutoLoadType placementModelAutoLoadType;
@property (nonatomic, assign)BOOL autoRefresh;

@property (nonatomic, assign) BOOL isDisplayPriceSwitch;
@end

NS_ASSUME_NONNULL_END
