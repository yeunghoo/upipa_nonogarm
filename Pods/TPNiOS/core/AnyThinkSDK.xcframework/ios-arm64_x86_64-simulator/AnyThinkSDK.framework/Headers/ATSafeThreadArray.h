//  ATSafeThreadArray.h
//  ATSDK
//
//  Created by topon on 2020/9/21.
//  Copyright © 2020 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 for...in非线程安全,使用数组 enumerateObjectsUsingBlock遍历
 遍历回调中,不能修改数组
 */
@interface ATSafeThreadArray<ObjectType> : NSMutableArray

@end
