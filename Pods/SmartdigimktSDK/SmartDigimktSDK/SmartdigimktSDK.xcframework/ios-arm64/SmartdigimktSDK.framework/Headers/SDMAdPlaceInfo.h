//
//  SDMAdPlaceInfo.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/21.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMAdFormatDefine.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMAdPlaceInfo : NSObject

@property (nonatomic, copy, readonly) NSString *placementId;
@property (nonatomic, copy, readonly) NSString *requestId;
@property (nonatomic, assign, readonly) SDMAdFormat format;

@end

NS_ASSUME_NONNULL_END
