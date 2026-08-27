//
//  SDMAdEcpmInfo.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/21.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, SDMAdCurrencyType) {
    SDMAdCurrencyTypeUSD,
    SDMAdCurrencyTypeCNY,
    SDMAdCurrencyTypeCNYCents,
};

NS_ASSUME_NONNULL_BEGIN

@interface SDMAdEcpmInfo : NSObject
/// get ecpm with currency type
- (double)currentEcpm:(SDMAdCurrencyType)type;
- (NSDecimalNumber *)currentDecimalEcpm:(SDMAdCurrencyType)type;
/// get revenue with currency type
- (double)currentRevenueEcpm:(SDMAdCurrencyType)type;
- (NSDecimalNumber *)currentDecimalRevenueEcpm:(SDMAdCurrencyType)type;

@end

NS_ASSUME_NONNULL_END
