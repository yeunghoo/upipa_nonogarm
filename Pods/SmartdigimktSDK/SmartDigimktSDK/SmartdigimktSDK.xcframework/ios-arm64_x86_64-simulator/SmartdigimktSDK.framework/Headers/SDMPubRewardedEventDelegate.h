//
//  SDMPubRewardedEventDelegate.h
//  SmartdigimktSDK
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class SDMRewardedVideoAd;

@protocol SDMPubRewardedEventDelegate <NSObject>

@optional

- (void)onRewardedSuccess:(SDMRewardedVideoAd *)item trackDict:(nullable NSDictionary *)trackDict;

@end

NS_ASSUME_NONNULL_END
