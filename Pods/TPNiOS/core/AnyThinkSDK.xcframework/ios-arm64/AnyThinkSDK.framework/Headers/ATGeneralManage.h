//
//  ATGeneralManage.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2025/4/22.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATDAParameter.h>
@class ATNativeAdNetworkViewConfig;
NS_ASSUME_NONNULL_BEGIN

@interface ATGeneralManage : NSObject

+ (BOOL)isEmpty:(id)object;
+ (NSString *)advertisingIdentifier;
+ (NSDictionary *)at_getLoadedSuccessfulExtra:(id)networkObject;
+ (UIViewController *)getCurrentViewControllerWithWindow:(nullable UIWindow *)window;

+ (NSDictionary *)ttPrimeRitUnitIDForPlacementID:(NSString *)placementID;

+ (NSInteger)capShowByDayWithPlacementID:(NSString *)placementID;

+ (NSString *)getExchRateC2UWithRMBPrice:(NSString *)price placementID:(NSString *)placementID;

+ (void)sendAgentEvent:(NSString *)dakeyString daParameter:(void(^_Nullable)(ATDAParameter* _Nullable parameter))parameterBlock;

+ (void)recordShowEcpmDic:(NSDictionary *)dic priceValue:(double)priceValue;

+ (NSString *)at_transformString:(id)stringOrNumber;

+ (int)getU2CPointIntForPrice:(NSString *)price bidInfoCurRate:(NSString *)curRate;

+ (NSString *)at_dateToUTCStr:(NSDate *)date;


+ (BOOL)screenOrientationIsLandscape;

+ (NSString*)skipSubString;

+ (UIEdgeInsets)AT_safeAreaInsets;

+ (BOOL)isBackground;

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)interval target:(id)target repeats:(BOOL)repeats block:(void (^)(NSTimer *timer))block;

+ (NSString *)getSecondPrice:(NSString *)placementID requestID:(NSString *)requestID originPrice:(NSString *)originPrice  gspRates:(CGFloat)rates priceArray:(nullable NSArray *)priceArray;

+ (BOOL)hasSetMute;

+ (CGSize)getTemplateAdSize:(NSDictionary *)serverInfo;

+ (BOOL)isDebuggerPreInit;
+ (BOOL)isDebuggerPreLoad;

+ (NSString *)wxAppID;
+ (NSString *)wxUniversalLink;

+ (id)modelToJSONObject:(id)model;

@end

NS_ASSUME_NONNULL_END
