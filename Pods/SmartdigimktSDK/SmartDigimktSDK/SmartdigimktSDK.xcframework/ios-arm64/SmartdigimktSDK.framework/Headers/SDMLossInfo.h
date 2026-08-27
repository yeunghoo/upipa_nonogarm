//
//  SDMLossInfo.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/26.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMAdEcpmInfo.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SDMLossReason) {
    SDMLossToHigherBid = 0,
    SDMLossToNormal,
    SDMLossToAuctionFloor,
    SDMLossToExpire,
};

@interface SDMLossInfo : NSObject

@property (nonatomic, assign) SDMLossReason reason;
@property (nonatomic, assign) double winPrice;
@property (nonatomic, copy) NSString *networkName;
@property (nonatomic, copy) NSDictionary *extraInfo;
@property (nonatomic, assign) SDMAdCurrencyType currencyType;

@end

NS_ASSUME_NONNULL_END
