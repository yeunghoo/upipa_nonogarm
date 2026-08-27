//
//  ATSDKGlobalSetting.h
//  AnyThinkSDK
//
//  Created by Topon on 8/23/23.
//  Copyright © 2023 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAdLoadingDelegate.h>
#import <AnyThinkSDK/ATCustomContentInfo.h>
#import <AnyThinkSDK/ATCustomContentResult.h>
#import <AnyThinkSDK/ATDeviceInfoConfig.h>
#import <AnyThinkSDK/ATDebuggerConfig.h>
#import <AnyThinkSDK/ATCustomNetworkMode.h>
#import <AnyThinkSDK/ATSharePlacementConfig.h>


NS_ASSUME_NONNULL_BEGIN
@class ATAntiBrushConfig, ATRiskControlModel, ATAdCustomFilter;
extern NSString *const kATGeoLongitudeKey;
extern NSString *const kATGeoDimensionKey;
extern NSString *const kATDeviceDataInfoOSVersionNameKey; //System version name
extern NSString *const kATDeviceDataInfoOSVersionCodeKey; //System version code
extern NSString *const kATDeviceDataInfoPackageNameKey; //Application package name
extern NSString *const kATDeviceDataInfoAppVersionNameKey; //Application version name
extern NSString *const kATDeviceDataInfoAppVersionCodeKey; //Application version code
extern NSString *const kATDeviceDataInfoBrandKey; //Phone brands
extern NSString *const kATDeviceDataInfoCPUKey; //Phone cpu
extern NSString *const kATDeviceDataInfoModelKey; //Phone model
extern NSString *const kATDeviceDataInfoScreenKey; //Screen Resolution
extern NSString *const kATDeviceDataInfoNetworkTypeKey; //Network Type
extern NSString *const kATDeviceDataInfoMNCKey; //Mobile Network Code
extern NSString *const kATDeviceDataInfoMCCKey; //Mobile Country Code
extern NSString *const kATDeviceDataInfoLanguageKey; //Language
extern NSString *const kATDeviceDataInfoTimeZoneKey; //Time zone
extern NSString *const kATDeviceDataInfoUserAgentKey; //User Agent
extern NSString *const kATDeviceDataInfoOrientKey; //Screen orientation
extern NSString *const kATDeviceDataInfoIDFAKey; //idfa
extern NSString *const kATDeviceDataInfoIDFVKey; //idfv
extern NSString *const kATDeviceDataInfoSIMCardStateKey; //sim card status
extern NSString *const kATDeviceDataInfoBatteryKey; //sim card status
extern NSString *const kATDeviceDataInfoSensorDeny; // sensor denny status

typedef NS_ENUM(NSUInteger, ATSplashAdClickResultType) {
    ATSplashAdClickResultTypeDidCloseAd         = 1,  // After clicking on the jump button, close the splash ad
    ATSplashAdClickResultTypePauseCountdown     = 2,  // Pause the countdown after clicking the jump button, and continue the countdown when the splash ad is visible
};

/// Debug values for testing geography.
typedef NS_ENUM(NSInteger, ATUMPDebugGeography) {
    ATUMPDebugGeographyDisabled = 0,  ///< Disable geography debugging.
    ATUMPDebugGeographyEEA = 1,       ///< Geography appears as in EEA for debug devices.
    ATUMPDebugGeographyNotEEA = 2,    ///< Geography appears as not in EEA for debug devices.
};

typedef NS_ENUM(NSInteger, ATSystemPlatformType) {
    ATSystemPlatformTypeUnknown = 0,
    ATSystemPlatformTypeIOS = 1,
    ATSystemPlatformTypeUnity = 2,
    ATSystemPlatformTypeCocos2dx = 3,
    ATSystemPlatformTypeCocosCreator = 4,
    ATSystemPlatformTypeReactNative = 5,
    ATSystemPlatformTypeFlutter = 6,
    ATSystemPlatformTypeAdobeAir = 7
};

/**
 * @enum ATDomainServiceType
 * @brief Domain service type for runtime domain switching.
 * @details Set this enum before SDK initialization to control which set of domains the SDK uses.
 *          Requires AnyThinkDomainSwitchAdapter plugin which contains both Taku and TPN domain sets.
 *          If not set (default), the SDK uses its built-in domains, behaving identically to without the plugin.
 */
typedef NS_ENUM(NSUInteger, ATDomainServiceType) {
    /** Default: use SDK built-in domains, plugin not involved */
    ATDomainServiceTypeDefault = 0,
    /** Use Taku domains  */
    ATDomainServiceTypeTaku,
    /** Use TPN domains  */
    ATDomainServiceTypeTPN,
};

typedef NS_ENUM(NSInteger, ATNetworkSensorType) {
    ATNetworkSensorTypeDefaultNetwork   = 0,   /// Default, Follow the network default shake configuration
    ATNetworkSensorTypeForbidAll        = 1,   /// Forbid all networks to open shake
    ATNetworkSensorTypeAllowAll         = 2,   /// Allow all networks to open shake
    ATNetworkSensorTypeAllowNetwork     = 3    /// Allows to open shake function on specified network
};

@interface ATSDKGlobalSetting : NSObject

+ (instancetype)sharedManager;

/*
 channel & customData has to be set before init
 */
@property (nonatomic, strong) NSString *channel;
@property (nonatomic, strong) NSString *subchannel;
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
/// Whether to pause the countdown after clicking on the  Splash ad to jump, the default is NO, Only for TopOn ADX、DirectlyAd and Cross Promotion
@property (nonatomic, assign) ATSplashAdClickResultType splashAdClickResultType;

// ump test ids
@property (nonatomic, nullable,strong) NSArray<NSString *> *umpTestDeviceIdentifiers;
/// Debug geography.
@property (nonatomic, assign) ATUMPDebugGeography umpGeography;
/// set header bidding test mode,only support incoming device idfa.
/// setLogEnabled must be turned on before use
@property (nonatomic, strong) NSString *headerBiddingTestModeDeviceID;
/// system platform Information
@property (atomic, assign) ATSystemPlatformType systemPlatformType;

/// Background color of open screen advertisement
/// Currently only supports MeiShu platform
@property (nonatomic, strong) UIColor *splashBgColor;

@property (nonatomic, strong) ATSharePlacementConfig *sharePlacementConfig;
/// set whether WX is installed
@property (atomic, assign) BOOL isInstallWX;
/// for setLocationLongitude:dimension:
@property (nonatomic, copy, readonly) NSDictionary *locationDictionary;

/// set ad video voice is mute
///  Currently only supports Admob、MTG、Inmobi、Max 、AppLovin、Fyber platform
@property (nonatomic, assign) BOOL isMute;
/// shake sensor type
@property (nonatomic, assign, readonly) ATNetworkSensorType networkSensorType;
/// List of NetworkFirmIDs that need to enable the shake sensor
@property (nonatomic, nullable, strong, readonly) NSArray<NSNumber *> *networkSensorList;

@property (nonatomic, assign) ATDomainServiceType domainServiceType;

/// Configure whether to allow the use of the shake acceleration sensor. If disabled, ads cannot be triggered by shaking. Not configured by default, the platform default rules are used.
/// @param networkSensorType - shake sensor type
/// @param networkSensorList - List of NetworkFirmIDs that need to enable the shake sensor
- (void)setNetworkSensorType:(ATNetworkSensorType)networkSensorType networkSensorList:(NSArray<NSNumber *> * _Nullable)networkSensorList;

/// set custom data for the ad placement
/// @param customData - custom data
/// @param placementID - placement id
- (void)setCustomData:(NSDictionary *)customData forPlacementID:(NSString *)placementID;

/// get custom data
- (NSDictionary *)customDataForPlacementID:(NSString *)placementID;

/// set Wechat appID and universalLink, for register WechatOpenSDK
/// @param appID - Wechat appID
/// @param universalLink - Wechat universalLink
- (void)setWeChatAppID:(NSString *)appID universalLink:(NSString *)universalLink;

- (void)addCustomAdapterConfigArray:(NSArray <ATCustomNetworkMode *>*)array;

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

- (void)setPresetPlacementConfigPathBundle:(NSBundle *)bundle;

/// set location longitude
- (void)setLocationLongitude:(double)longitude dimension:(double)dimension;

- (void)setDebuggerConfig:(void(^_Nullable)(ATDebuggerConfig * _Nullable debuggerConfig))debuggerConfigBlock;

- (void)setDeviceInfoConfig:(void(^_Nullable)(ATDeviceInfoConfig * _Nullable deviceInfoConfig))deviceInfoConfigBlock;

/// Delete all ads cached for the placementId
- (void)removeAllCacheWithPlacementId:(NSString *)placementId;
- (void)removeAllCacheWithPlacementId:(NSString *)placementId index:(NSInteger)index;
- (void)removeAllCacheWithPlacementId:(NSString *)placementId adInfoDictArray:(NSArray<NSDictionary *> *)adInfoDictArray;


/// Set up anti-fraudulent traffic information
/// - Parameter config: config
- (void)setAntiBrushConfig:(ATAntiBrushConfig *)config;

/// Get risk tag
- (nullable ATRiskControlModel *)riskControlInfo;

- (ATCustomContentInfo *)customContentReviewResult:(NSArray<ATCustomContentInfo *> *)infos;

- (ATCustomContentResult *)customContentResultReviewByInfos:(NSArray<ATCustomContentInfo *> *)infos;


/// 是否允许异常信息收集
/// - Parameter isPermit: 默认为YES
- (void)setAbnormalCollect:(BOOL)isPermit;

/// 添加过滤器 开发者传入placementID
/// 多个placementID 可以共用一个过滤器
/// - Parameter filter: 过滤器
- (void)addFilter:(ATAdCustomFilter *)filter forPlacementID:(NSString *)placementID;

/// 删除所有过滤器
- (void)removeAllFilters;

/// 删除部分过滤器
/// - Parameter placementIDs: 过滤器对应的广告位id
- (void)removeFilterWithPlacementIDs:(NSArray <NSString *> *)placementIDs;

/// Set the unit IDs that need to be excluded when loading an placement, will take effect on the next load
/// @param placementid  - TopOn's ad placement id
/// @param unitIDArray - need to be excluded unit IDs
- (void)setExludePlacementid:(NSString *)placementid
                 unitIDArray:(NSArray <NSString *> *)unitIDArray;

/// Set the network that needs to be excluded when loading an placement, will take effect on the next load
/// @param placementid  - TopOn's ad placement id
/// @param networkFirmIDArray - need to be excluded networkFirmIds
- (void)setExludePlacementid:(NSString *)placementid
          networkFirmIDArray:(NSArray <NSNumber *> *)networkFirmIDArray;

/// Set the placement IDs that need custom filter
/// @param placementIDArray - placement IDs array
- (void)setAdSourceCustomizeFillterPlacementIDArray:(NSArray <NSString *> *)placementIDArray;

/// 开屏页从load到展示显示的启动图，有则展示，在load前设置，仅针对开屏广告有效
@property (copy, nonatomic) UIImage *splashLaunchDefaultImage;
/// 清除开屏页从load到展示显示的启动图，清除后不会再显示
- (void)cleanSplashLaunchDefaultImage;


@end

NS_ASSUME_NONNULL_END
