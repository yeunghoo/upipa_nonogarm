//
//  ATBidResult.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/8/13.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATBidInfoCacheManager.h>
#import <AnyThinkSDK/ATAdAdapter.h>


NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger,ATBidWinLossResultType) {
    ATBidWinLossResultTypeWin = 0,
    ATBidWinLossResultTypeLoss = 1
};

@interface ATBidWinLossResult : NSObject
/// Win/Loss 类型
@property (nonatomic, assign) ATBidWinLossResultType bidResultType;
/// lossReasonType
@property (nonatomic, assign) ATBiddingLossType lossReasonType;
/// winPrice
@property (nonatomic, strong) NSString *winPrice;
/// secondPrice
@property (nonatomic, strong) NSString *secondPrice;
/// userInfoDic
@property (nonatomic, strong) NSDictionary  *userInfoDic;


@end

NS_ASSUME_NONNULL_END
