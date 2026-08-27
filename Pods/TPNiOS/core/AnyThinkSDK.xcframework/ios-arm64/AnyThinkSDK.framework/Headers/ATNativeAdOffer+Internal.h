//
//  ATNativeAdOffer+Internal.h
//  AnyThinkNative
//
//  Created by Topon on 10/27/21.
//  Copyright © 2021 AnyThink. All rights reserved.
//

#import <AnyThinkSDK/ATNativeAdOffer.h>
#import <AnyThinkSDK/ATAdOfferCacheModel.h>
#import <AnyThinkSDK/ATAPI.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATNativeAdOffer (Internal)

- (ATAdOfferCacheModel *)offerCacheModel;

- (instancetype)initWithPlacementID:(NSString *)placementID
                             config:(ATShowConfig *)config
                        nativeOffer:(ATAdOfferCacheModel *)nativeOffer;

@end

NS_ASSUME_NONNULL_END
