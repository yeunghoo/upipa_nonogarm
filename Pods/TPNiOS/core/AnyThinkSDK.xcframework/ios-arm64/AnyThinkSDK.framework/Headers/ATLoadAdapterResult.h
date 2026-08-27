//
//  ATLoadAdapterResult.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/3/24.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATBidInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class ATLoadAdapterResult;

typedef void(^ATLoadAdapterResultBlock)(ATLoadAdapterResult *adapterResult);

@interface ATLoadAdapterResult : NSObject

/// adapter 返回的 素材 数组
@property (nonatomic, strong) NSArray<NSDictionary *> *_Nullable completionArray;

@property (nonatomic, strong) NSError *error;

/// S2S bid 请求参数
@property (nonatomic, strong) NSDictionary *headerBiddingParamDic;

/// C2S bid info
@property (nonatomic, strong) ATBidInfo *bidInfo;

@end

NS_ASSUME_NONNULL_END
