//
//  ATMCPreloadModel.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/3/17.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATModel.h>


NS_ASSUME_NONNULL_BEGIN

@interface ATMgPreloadModel : NSObject
/// 多聚合request_id
@property (nonatomic, copy) NSString *requestID;
/// 多聚合psid
@property (nonatomic, copy) NSString *psID;
/// 多聚合 mgPlacementID
@property (nonatomic, copy) NSString *mgPlacementID;

/// 是否开启向Topon回调价格
@property (nonatomic, assign) BOOL isPriceCallbackEnabled;
/// 多聚合回调价格最长等待时间: 毫秒,默认为:1000
@property (nonatomic, assign) NSInteger maxPriceCallbackWaitTime;

/// 多聚合透传给SDK的最高价  币种:currencyType
- (void)mgCallBackPrice:(NSString *)mgprice currencyType:(ATBiddingCurrencyType)currencyType;




@end

NS_ASSUME_NONNULL_END
