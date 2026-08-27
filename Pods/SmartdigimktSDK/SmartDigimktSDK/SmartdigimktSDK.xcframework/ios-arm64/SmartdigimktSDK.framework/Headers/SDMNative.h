//
//  SDMNative.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/24.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMNativeAd.h>
#import <SmartdigimktSDK/SDMAdRequest.h>
NS_ASSUME_NONNULL_BEGIN

@protocol SDMNativeLoadDelegate <NSObject>

- (void)onAdLoaded:(SDMNativeAd *)nativeAd;
- (void)onAdLoadFail:(NSError *)error;

@end

@interface SDMNative : NSObject

@property (nonatomic, weak) id<SDMNativeLoadDelegate> delegate;
@property (nonatomic, copy) NSString *placementId;
@property (nonatomic, strong) SDMAdRequest *adRequest;

- (instancetype)initAdWithPlacementId:(NSString *)placementId;
- (void)load;

@end

NS_ASSUME_NONNULL_END
