//
//  ATSafeModuleObject.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/3/5.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATSafeModuleObject : NSObject

- (void)at_lock;

- (void)at_unlock;

@end

NS_ASSUME_NONNULL_END
