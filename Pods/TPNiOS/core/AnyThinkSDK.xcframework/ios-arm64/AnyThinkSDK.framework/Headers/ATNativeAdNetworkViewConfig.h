//
//  ATNativeAdNetworkViewConfig.h
//  AnyThinkNative
//
//  Created by Captain on 2024/10/24.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATNativeAdNetworkViewConfig : NSObject
@property (nonatomic, assign) CGRect frame;

// for baidu slider
@property (nonatomic, assign) NSInteger repeat;
@property (nonatomic, assign) CGFloat animationWidth;
@property (nonatomic, assign) CGFloat animationHeight;

@end

NS_ASSUME_NONNULL_END
