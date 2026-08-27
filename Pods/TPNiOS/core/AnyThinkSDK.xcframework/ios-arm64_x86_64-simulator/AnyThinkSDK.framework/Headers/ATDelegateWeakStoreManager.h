//
//  ATShowDelegateStoreManager.h
//  AnyThinkSDK
//
//  Created by mac on 2022/1/12.
//  Copyright © 2022 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATDelegateWeakStoreManager : NSObject

+ (instancetype)share;

- (void)saveLoadDelegate:(id)delegate placementID:(NSString *)placementID;
- (void)removeLoadDelegateWithPlacementID:(NSString *)placementID;
- (id)getLoadDelegateWithPlacementID:(NSString *)placementID;


#pragma mark - load show delegate
- (void)saveLoadDelegateArray:(id)delegate placementID:(NSString *)placementID;

- (void)removeLoadDelegateArrayWithPlacementID:(NSString *)placementID;

- (NSHashTable *)getLoadDelegateArrayWithPlacementID:(NSString *)placementID;

- (void)saveShowDelegateArray:(id)delegate placementID:(NSString *)placementID;

- (void)removeShowDelegateArrayWithPlacementID:(NSString *)placementID;

- (NSHashTable *)getShowDelegateArrayWithPlacementID:(NSString *)placementID;




@end

NS_ASSUME_NONNULL_END
