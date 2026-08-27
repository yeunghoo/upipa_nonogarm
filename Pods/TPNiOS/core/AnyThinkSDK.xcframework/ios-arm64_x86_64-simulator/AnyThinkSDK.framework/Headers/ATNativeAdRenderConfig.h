//
//  ATNativeAdRenderConfig.h
//  AnyThinkNative
//
//  Created by Captain on 2025/4/8.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
NS_ASSUME_NONNULL_BEGIN

@interface ATNativeAdRenderConfig : NSObject

@property (nonatomic, assign) BOOL sizeToFit;

@property (nonatomic, weak) UIViewController *rootViewController;

@property (nonatomic, assign) CGPoint adChoicesViewOrigin;

@property (nonatomic, assign) CGRect logoViewFrame;

@property (nonatomic, copy) NSString *scene;
@property (nonatomic, copy) NSString *showCustomExt;


@end

NS_ASSUME_NONNULL_END
