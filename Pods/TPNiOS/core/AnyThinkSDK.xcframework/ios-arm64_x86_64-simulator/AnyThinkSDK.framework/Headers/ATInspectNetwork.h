//
//  ATInspectNetwork.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2023/6/25.
//  Copyright © 2023 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATInspectNetworkModel.h>

NS_ASSUME_NONNULL_BEGIN
#define ATDefaultVersion @"9999.99999999"

@interface ATInspectNetwork : NSObject

- (NSArray <ATInspectNetworkModel *>*)integrationCheckingAPI;

- (void)checkNetworkVersions;

- (void)transmissionCheckSDKInfo:(NSDictionary *)infoDic;

+ (instancetype)sharedManager;

@end

NS_ASSUME_NONNULL_END
