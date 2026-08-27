//
//  SDMAd.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/21.
//  Ads Info

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMAdEcpmInfo.h>
#import <SmartdigimktSDK/SDMAdPlaceInfo.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMAd : NSObject

@property (nonatomic, strong, readonly) SDMAdEcpmInfo *ecpmInfo;
@property (nonatomic, strong, readonly) SDMAdPlaceInfo *placementInfo;
@property (nonatomic, copy, readonly) NSDictionary *extraInfo;

@end

NS_ASSUME_NONNULL_END
