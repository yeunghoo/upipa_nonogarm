//
//  ATNetworkInitManager.h
//  AnyThinkSDK
//
//  Created by Ben on 2022/6/9.
//  Copyright © 2022 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kATNetworkSDKInitAppId;
extern NSString *const kATNetworkSDKInitAppkey;
extern NSString *const kATNetworkSDKInitGDPR;
extern NSString *const kATNetworkSDKInitZoons;

@interface ATNetworkInitManager : NSObject

+ (instancetype)sharedManager;

- (void)storageInitNetworkName:(NSString *)networkName
                      appID:(NSString *)appID
                     appkey:(NSString *_Nullable)appkey;
- (BOOL)isSameWithStorageForNetworkName:(NSString *)networkName appId:(NSString *)appId appkey:(NSString *)appkey;

- (void)handleInitDataForNetwork:(NSString *)networkName
                       cacheData:(NSDictionary *)cacheDic
                      serverInfo:(NSDictionary *)serverInfo
                     placementID:(NSString *)placementID;

- (NSDictionary *)getCacheInitDataForNetwork:(NSString *)networkName;

@end

NS_ASSUME_NONNULL_END
