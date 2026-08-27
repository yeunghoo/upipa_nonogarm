//
//  SDMSDKGlobalSetting.h
//  SmartdigimktSDK
//
//  Created by Smartdigimkt on 8/23/23.
//  Copyright © 2023 Smartdigimkt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <SmartdigimktSDK/SDMAdFormatDefine.h>
#import <SmartdigimktSDK/SDMDebuggerConfig.h>

NS_ASSUME_NONNULL_BEGIN
@class SDMAntiBrushConfig, SDMRiskControlModel, SDMAdCustomFilter;
extern NSString *const kSDMDeviceDataInfoOSVersionNameKey; //System version name
extern NSString *const kSDMDeviceDataInfoOSVersionCodeKey; //System version code
extern NSString *const kSDMDeviceDataInfoPackageNameKey; //Application package name
extern NSString *const kSDMDeviceDataInfoAppVersionNameKey; //Application version name
extern NSString *const kSDMDeviceDataInfoAppVersionCodeKey; //Application version code
extern NSString *const kSDMDeviceDataInfoBrandKey; //Phone brands
extern NSString *const kSDMDeviceDataInfoCPUKey; //Phone cpu
extern NSString *const kSDMDeviceDataInfoModelKey; //Phone model
extern NSString *const kSDMDeviceDataInfoScreenKey; //Screen Resolution
extern NSString *const kSDMDeviceDataInfoNetworkTypeKey; //Network Type
extern NSString *const kSDMDeviceDataInfoMNCKey; //Mobile Network Code
extern NSString *const kSDMDeviceDataInfoMCCKey; //Mobile Country Code
extern NSString *const kSDMDeviceDataInfoLanguageKey; //Language
extern NSString *const kSDMDeviceDataInfoTimeZoneKey; //Time zone
extern NSString *const kSDMDeviceDataInfoUserAgentKey; //User Agent
extern NSString *const kSDMDeviceDataInfoOrientKey; //Screen orientation
extern NSString *const kSDMDeviceDataInfoIDFAKey; //idfa
extern NSString *const kSDMDeviceDataInfoIDFVKey; //idfv
extern NSString *const kSDMDeviceDataInfoSIMCardStateKey; //sim card status
extern NSString *const kSDMDeviceDataInfoBatteryKey; //sim card status
extern NSString *const kSDMDeviceDataInfoSensorDeny; // shake event
extern NSString *const kSDMDeviceDataInfoGyroscopeDeny; // twist event


typedef NS_ENUM(NSUInteger, SDMSplashAdClickResultType) {
    SDMSplashAdClickResultTypeDidCloseAd         = 1,  // After clicking on the jump button, close the splash ad
    SDMSplashAdClickResultTypePauseCountdown     = 2,  // Pause the countdown after clicking the jump button, and continue the countdown when the splash ad is visible
};

typedef NS_ENUM(NSInteger, SDMSystemPlatformType) {
    SDMSystemPlatformTypeUnknown = 0,
    SDMSystemPlatformTypeIOS = 1,
    SDMSystemPlatformTypeUnity = 2,
    SDMSystemPlatformTypeCocos2dx = 3,
    SDMSystemPlatformTypeCocosCreator = 4,
    SDMSystemPlatformTypeReactNative = 5,
    SDMSystemPlatformTypeFlutter = 6,
    SDMSystemPlatformTypeAdobeAir = 7
};

typedef NS_ENUM(NSUInteger, SDMDomainServiceType) {
    SDMDomainServiceTypeDefault = 0,
    SDMDomainServiceTypeKuying = 1,
    SDMDomainServiceTypeOnPro = 2,
};

@interface SDMSDKGlobalSetting : NSObject

+ (instancetype)sharedManager;

@property (nonatomic, strong) NSDictionary *customData;
/// Splash Shake Text String, Only for DirectlyAd
@property (nonatomic, strong) NSString *directlySplashAdShakeTextString;
/// Splash CTA Button BackgroundColor, Only for DirectlyAd
@property (nonatomic, strong) UIColor *directlySplashAdCTAButtonBackgroundColor;
/// Splash Shake Custom View, Only for DirectlyAd
@property (nonatomic, strong) UIView *directlySplashAdCustomShakeView;
/// Splash CTA Custom View, Only for DirectlyAd
@property (nonatomic, strong) UIView *directlySplashAdCustomCTAView;
/// Splash Video Mute Icon hidden, Not hidden by default,  Only for DirectlyAd
@property (nonatomic, assign) BOOL directlySplashAdVideoMuteIconHidden;
/// Whether to pause the countdown after clicking on the  Splash ad to jump, the default is NO, Only for smartdigimkt ADX、DirectlyAd and Cross Promotion
@property (nonatomic, assign) SDMSplashAdClickResultType splashAdClickResultType;
/// Whether deep reward is enabled (new templates such as task card); default is YES. If set to NO, task card template is disabled and falls back to legacy rendering.
@property (nonatomic, assign) BOOL deepRewardEnabled;

/// set header bidding test mode,only support incoming device idfa.
/// setLogEnabled must be turned on before use
@property (nonatomic, strong) NSString *headerBiddingTestModeDeviceID;
/// system platform Information
@property (nonatomic, assign) SDMSystemPlatformType systemPlatformType;
/// Optional domain service; set before SDK init. Used by SmartdigimktDomainSwitchAdapter when linked.
@property (nonatomic, assign) SDMDomainServiceType domainServiceType;
/// set whether WX is installed
@property (nonatomic, assign) BOOL isInstallWX;
/// for setLocationLongitude:dimension:
@property (nonatomic, readonly) NSDictionary *locationDictionary;

/// set custom data for the ad placement
/// @param customData - custom data
/// @param placementID - placement id
- (void)setCustomData:(NSDictionary *)customData forPlacementID:(NSString *)placementID;

/// get custom data
- (nullable NSDictionary *)customDataForPlacementID:(NSString *)placementID;

/// set Wechat appID and universalLink, for register WechatOpenSDK
/// @param appID - Wechat appID
/// @param universalLink - Wechat universalLink
- (void)setWeChatAppID:(NSString *)appID universalLink:(NSString *)universalLink;

/// set exlude appleid list for sdk to filter offers
- (void)setExludeAppleIdArray:(NSArray *)appleIdArray;

/// get exlude appleid list
- (NSArray *)exludeAppleIdArray;

/// set denied Upload Info list for sdk to Control report
- (void)setDeniedUploadInfoArray:(NSArray *)uploadInfoArray;

/// get denied Upload Info list
- (NSArray *)deniedUploadInfoArray;

/// Determine whether the Denied key is included
/// @param key - key string
- (BOOL)isContainsForDeniedUploadInfoArray:(NSString *)key;

/// - Parameter isPermit: default YES
- (void)setAbnormalCollect:(BOOL)isPermit;

#pragma mark - Sensor
- (BOOL)isDenySensor;
- (BOOL)isDenySensorWithExtra:(NSDictionary *)extra;
- (void)setDenySensor:(BOOL)isShakeEnabled;
- (void)setDenySensor:(BOOL)isShakeEnabled extra:(NSDictionary *)extra;

#pragma mark - DeviceInfo
/// set location longitude
- (void)setLocationLongitude:(double)longitude dimension:(double)dimension;
- (void)setDebuggerConfig:(void(^_Nullable)(SDMDebuggerConfig * _Nullable debuggerConfig))debuggerConfigBlock;

@end

NS_ASSUME_NONNULL_END
