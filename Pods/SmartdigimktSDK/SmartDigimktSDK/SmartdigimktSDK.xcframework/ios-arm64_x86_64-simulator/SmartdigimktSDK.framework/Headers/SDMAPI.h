//
//  SDMAPI.h
//  SmartdigimktSDK
//
//  Created by Plutus on 09/04/2018.
//  Copyright © 2018 Plutus. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <SmartdigimktSDK/SDMDebuggerConfig.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kSDMADDelegateExtraNetworkFirmIdKey;
extern NSString *const kSDMADDelegateExtraAdSourceIdKey;
extern NSString *const kSDMADDelegateExtraIsHeaderBiddingKey;
extern NSString *const kSDMADDelegateExtraBidModeKey;
extern NSString *const kSDMADDelegateExtraAdSourcePriceKey;
extern NSString *const kSDMADDelegateExtraPriorityKey;
extern NSString *const kSDMADDelegateExtraBidFloorKey;
extern NSString *const kSDMADDelegateExtraRequestIDKey;
extern NSString *const kSDMADDelegateExtraCustomExtKey;
extern NSString *const kSDMADDelegateExtraECPMLevelKey; // the eCPM level of the ad source
extern NSString *const kSDMADDelegateExtraSegmentIDKey; //segment ID
extern NSString *const kSDMADDelegateExtraCustomRuleKey; // Json string of the Placement + App dimension custom rule
extern NSString *const kSDMADDelegateExtraIDKey; // a unique ID generated for each impression
extern NSString *const kSDMADDelegateExtraAdunitIDKey; // smartdigimkt placement ID
extern NSString *const kSDMADDelegateExtraPublisherRevenueKey; // impression revenue
extern NSString *const kSDMADDelegateExtraCurrencyKey; // currency unit, for example: "USD"
extern NSString *const kSDMADDelegateExtraCountryKey; // country code, for example: "CN"
extern NSString *const kSDMADDelegateExtraFormatKey; // ad source types
extern NSString *const kSDMADDelegateExtraPrecisionKey; // eCPM precision
extern NSString *const kSDMADDelegateExtraNetworkTypeKey; // Network Type
extern NSString *const kSDMADDelegateExtraNetworkPlacementIDKey; // the ad placement ID of a third-party Ads Network
extern NSString *const kSDMADDelegateExtraPlacementRewardNameKey;
extern NSString *const kSDMADDelegateExtraPlacementRewardNumberKey;
extern NSString *const kSDMADDelegateExtraExtInfoKey; // additional information of Smartdigimkt Adx & OnlineAPI Offer,output as Json string
extern NSString *const kSDMADDelegateExtraOfferIDKey;
extern NSString *const kSDMADDelegateExtraCreativeIDKey;
extern NSString *const kSDMADDelegateExtraIsDeeplinkKey;
extern NSString *const kSDMADDelegateExtraUserCustomData;
extern NSString *const kSDMADDelegateExtraPlacementTypeKey;
extern NSString *const kSDMADDelegateExtraNetworkNameKey;
extern NSString *const kSDMADDelegateExtraTpBidIDKey;
extern NSString *const kSDMADDelegateExtraABTestIDKey;
extern NSString *const kSDMADDelegateExtraDismissTypeKey;
extern NSString *const kSDMADDebuggerKey;
extern NSString *const kSDMADDelegateExtraServerKeyIdKey;
extern NSString *const kSDMADDelegateExtraClientSideEcpmKey;
extern NSString *const kSDMADDelegateExtraUsdExchangeRmbRateKey;
extern NSString *const kSDMADDelegateExtraRmbExchangeUsdRateKey;
extern NSString *const kSDMADDelegateExtraADSourceTypeKey;

extern NSString *const kSDMCustomDataUserIDKey;//string
extern NSString *const kSDMCustomDataAgeKey;//Integer
extern NSString *const kSDMCustomDataGenderKey;//Integer
extern NSString *const kSDMCustomDataNumberOfIAPKey;//Integer
extern NSString *const kSDMCustomDataIAPAmountKey;//Double
extern NSString *const kSDMCustomDataIAPCurrencyKey;//string
extern NSString *const kSDMCustomDataChannelKey;//string
extern NSString *const kSDMCustomDataSubchannelKey;//string
extern NSString *const kSDMCustomDataSegmentIDKey;//int

typedef NS_ENUM(NSInteger, SDMUserLocation) {
    SDMUserLocationUnknown = 0,
    SDMUserLocationInEU = 1,
    SDMUserLocationOutOfEU = 2
};

typedef NS_ENUM(NSInteger, SDMDataConsentSet) {
    //Let it default to forbidden if not set
    SDMDataConsentSetUnknown = 0,
    SDMDataConsentSetPersonalized = 1,
    SDMDataConsentSetNonpersonalized = 2
};

typedef NS_ENUM(NSInteger, SDMBUAdLoadType) {
    SDMBUAdLoadTypeUnknown = -1, // Unknown
    SDMBUAdLoadTypePreload = 1, // Preload resources
    SDMBUAdLoadTypeLoad = 3, // Load resources in real time
};

typedef NS_ENUM(NSInteger, SDMPersonalizedAdState) {
    SDMPersonalizedAdStateType = 1,
    SDMNonpersonalizedAdStateType = 2
};

typedef NS_OPTIONS(NSInteger, SDMLogType) {
    SDMLogTypeNone = 0,
    SDMLogTypeInternal = 1 << 0,
    SDMLogTypeExternal = 1 << 1,
    SDMLogTypeTemporary = 1 << 2,
    SDMLogTypeProcess = 1 << 3,
    SDMLogTypeSave = 1 << 4
};

// Position of the logo icon in the containing ad.
typedef NS_ENUM(NSInteger, SDMAdLogoPosition) {
    SDMAdLogoPositionBottomRightCorner = 0,  ///< Bottom right corner.
    SDMAdLogoPositionBottomLeftCorner,   ///< Bottom Left Corner.
    SDMAdLogoPositionTopRightCorner,     ///< Top right corner.
    SDMAdLogoPositionTopLeftCorner,      ///< Top left corner.
};

@interface SDMAPI : NSObject

@property (nonatomic, readonly) SDMDataConsentSet dataConsentSet;
@property (nonatomic, readonly) NSString *appID;
@property (nonatomic, readonly) NSString *appKey;

/// singleton object
+ (instancetype)sharedInstance;

/// Log enabled
/// @param logEnabled - log status
+ (void)setLogEnabled:(BOOL)logEnabled;

/// Log enabled
/// @param cacheEnabled log localCache status
+ (void)logLocalCacheEnabled:(BOOL)cacheEnabled;

/// print test info log
/// include idfa,idfv
+ (void)testModeInfo;

/// get SDK version
+ (NSString *)version;

+ (void)preStartWithExtra:(nullable NSDictionary *)extra;

/// Initialize SDK
/// @param appID - appid string
/// @param appKey appkey string
/// @param error - see what's the matter.
- (BOOL)startWithAppID:(NSString *)appID
                appKey:(NSString *)appKey
                 error:(NSError **)error;

/// get ps id
- (nullable NSString *)psID;

- (void)setAdDataConsentSet:(SDMDataConsentSet)dataConsentSet;

/// set personalized recommendation state
/// @param state - 1 is to close personalized recommendation, other values or not set to open
- (void)setPersonalizedAdState:(SDMPersonalizedAdState)state;

/// get personalized recommendation state
- (SDMPersonalizedAdState)getPersonalizedAdState;

NS_ASSUME_NONNULL_END
@end


