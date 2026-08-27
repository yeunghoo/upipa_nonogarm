//
//  SDMMyOfferCommonManager.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/9/10.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface SDMMyOfferCommonManager : NSObject

+ (NSMutableArray *)excludeMyOfferID;

+ (BOOL)myOfferExhaustedInMyOfferIDs:(NSArray<NSString *> *)myOfferIDs;

+ (NSInteger)capForOfferID:(NSString *)myOfferID;

+ (BOOL)resourceReadyWithPlacement:(NSDictionary *)placementDic placementId:(NSString *)placementId offerId:(NSString *)offerId;

+ (BOOL)offerReadyWithPlacement:(NSDictionary *)placementDic placementId:(NSString *)placementId offerId:(NSString *)offerId;

+ (void)preLoadMyOfferOffersWithPlacement:(NSDictionary *)placementDic placementId:(NSString *)placementId requestId:(NSString*)requestId;
    
@end

NS_ASSUME_NONNULL_END
