//
//  SDMWinInfo.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/26.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMAdEcpmInfo.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMWinInfo : NSObject

@property (nonatomic, assign) double secondPrice;
@property (nonatomic, copy) NSString *networkName;
@property (nonatomic, copy) NSDictionary *extraInfo;
@property (nonatomic, assign) SDMAdCurrencyType currencyType;

@end

NS_ASSUME_NONNULL_END
