//
//  ATInspectNetworkModel.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2023/8/14.
//  Copyright © 2023 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN

#define ATNetworkSDKInfoNameKey @"ATNetworkSDKInfoNameKey"
#define ATNetworkSDKInfoClassKey @"ATNetworkSDKInfoClassKey"
#define ATNetworkSDKCheckInfoKey @"ATNetworkSDKCheckInfoKey"


#define ATNetworkName_Facebook @"Meta"
#define ATNetworkName_Admob @"Admob"
#define ATNetworkName_Inmobi @"Inmobi"
#define ATNetworkName_Applovin @"Applovin"
#define ATNetworkName_Mintegral @"Mintegral"
#define ATNetworkName_GDT @"GDT"
#define ATNetworkName_Chartboost @"Chartboost"
#define ATNetworkName_Tapjoy @"Tapjoy"
#define ATNetworkName_IronSource @"IronSource"
#define ATNetworkName_UnityAds @"UnityAds"
#define ATNetworkName_Vungle @"Vungle"
#define ATNetworkName_AdColony @"AdColony"
#define ATNetworkName_Helium @"Helium"
#define ATNetworkName_CSJ @"CSJ"
#define ATNetworkName_Baidu @"Baidu"
#define ATNetworkName_Nend @"Nend"
#define ATNetworkName_Maio @"Maio"
#define ATNetworkName_StartApp @"Start.io"
#define ATNetworkName_KS @"KuaiShou"
#define ATNetworkName_Sigmob @"Sigmob"
#define ATNetworkName_Fyber @"Fyber"
#define ATNetworkName_Kidoz @"Kidoz"
#define ATNetworkName_MyTarget @"MyTarget"
#define ATNetworkName_Yandex @"Yandex"
#define ATNetworkName_Ogury @"Ogury"
#define ATNetworkName_Klevin @"Klevin"
#define ATNetworkName_Bigo @"Bigo"
#define ATNetworkName_Pangle @"Pangle"
#define ATNetworkName_PubNative @"Verve"
#define ATNetworkName_Qumeng @"Qumeng"
#define ATNetworkName_Smaato @"Smaato"
#define ATNetworkName_BidMachine @"Bidmachine"
#define ATNetworkName_Tanx @"tanx"
#define ATNetworkName_JDYun @"jd"
#define ATNetworkName_PangleCombine @"pangleCombine"
#define ATNetworkName_Kwai @"kwai"
#define ATNetworkName_MS @"MS"
#define ATNetworkName_AQY @"AQY"
#define ATNetworkName_ADX @"ADX"


#define ATNetworkName_Adapter_Framework_Key @"ATNetworkName_Adapter_Framework_Key"
#define ATNetworkName_Class_Key @"ATNetworkName_Class_Key"
#define ATNetworkName_Framework_Key @"ATNetworkName_Framework_Key"
#define ATNetworkName_Bundle_Key @"ATNetworkName_Bundle_Key"


#define ATNetworkName_Bigo_Class @"ATBigoInitAdapter"
#define ATNetworkName_PubNative_Class @"ATPubNativeInitAdapter"
#define ATNetworkName_Pangle_Class @"ATPangleInitAdapter"
#define ATNetworkName_Yandex_Class @"ATYandexInitAdapter"
#define ATNetworkName_MyTarget_Class @"ATMyTargetInitAdapter"
#define ATNetworkName_Kidoz_Class @"ATKidozInitAdapter"
#define ATNetworkName_Adcolony_Class @"ATAdcolonyInitAdapter"
#define ATNetworkName_Admob_Class @"ATAdmobInitAdapter"
#define ATNetworkName_A4G_Class @"ATAdmobInitAdapter"
#define ATNetworkName_Applovin_Class @"ATApplovinInitAdapter"
#define ATNetworkName_Baidu_Class @"ATBaiduInitAdapter"
#define ATNetworkName_Chartboost_Class @"ATChartboostInitAdapter"
#define ATNetworkName_Helium_Class @"ATHeliumInitAdapter"
#define ATNetworkName_FaceBook_Class @"ATFaceBookInitAdapter"
#define ATNetworkName_Fyber_Class @"ATFyberInitAdapter"
#define ATNetworkName_GDT_Class @"ATGDTInitAdapter"
#define ATNetworkName_Inmobi_Class @"ATInmobiInitAdapter"
#define ATNetworkName_Ironsource_Class @"ATIronsourceInitAdapter"
#define ATNetworkName_Klevin_Class @"ATKlevinInitAdapter"
#define ATNetworkName_KS_Class @"ATKSInitAdapter"
#define ATNetworkName_Maio_Class @"ATMaioInitAdapter"
#define ATNetworkName_Mintegral_Class @"ATMintegralInitAdapter"
#define ATNetworkName_Nend_Class @"ATNendInitAdapter"
#define ATNetworkName_Ogury_Class @"ATOguryInitAdapter"
#define ATNetworkName_TT_Class @"ATTTInitAdapter"
#define ATNetworkName_Sigmo_Class @"ATSigmoInitAdapter"
#define ATNetworkName_StartApp_Class @"ATStartAppInitAdapter"
#define ATNetworkName_Tapjoy_Class @"ATTapjoyInitAdapter"
#define ATNetworkName_UnityAds_Class @"ATUnityAdsInitAdapter"
#define ATNetworkName_Vungle_Class @"ATVungleInitAdapter"
#define ATNetworkName_QM_Class @"ATQMInitAdapter"
#define ATNetworkName_Smaato_Class @"ATSmaatoInitAdapter"
#define ATNetworkName_BidMachine_Class @"ATBidMachineInitAdapter"
#define ATNetworkName_Tanx_Class @"ATTanxInitAdapter"
#define ATNetworkName_JDYun_Class @"ATJDYunBaseInitAdapter"
#define ATNetworkName_Kwai_Class @"ATKwaiInitAdapter"
#define ATNetworkName_PAGCombine_Class @"ATPAGCombineInitAdapter"
#define ATNetworkName_AQY_Class @"ATAQYInitAdapter"
#define ATNetworkName_MS_Class @"ATMSInitAdapter"




typedef NS_ENUM(NSInteger, ATInspectNetworkSDKBundleType) {
    ATInspectNetworkSDKBundleTypeWithout = 0,
    ATInspectNetworkSDKBundleTypeSucceed,
    ATInspectNetworkSDKBundleTypeLose,
};

typedef NS_ENUM(NSInteger, ATInspectNetworkSDKStauts) {
    ATInspectNetworkSDKStautsWithout = 0,
    ATInspectNetworkSDKStautsSucceed,
    ATInspectNetworkSDKStautsLose,
};

@interface ATInspectNetworkModel : NSObject
/// 集成三方SDK ID
@property (nonatomic, assign) NSInteger networkFirmID;
/// 集成三方SDK ID String
@property (nonatomic, strong) NSString *networkFirmIDString;
/// 集成三方SDK 优先级
@property (nonatomic, strong) NSNumber *networkPriority;


/// 集成三方SDK名称
@property (nonatomic, strong) NSString *networkNameString;
/// 集成三方SDK的版本号
@property (nonatomic, strong) NSString *networkVersionsString;
/// 集成失败的原因
@property (nonatomic, strong) NSString *inspectFailReasonString;
/// 集成三方SDK Framework 是否成功
@property (nonatomic, assign) BOOL isNetworkIntegrationSucceed;
/// 集成三方SDK Bundle 类型
@property (nonatomic, assign) ATInspectNetworkSDKBundleType inspectNetworkSDKBundleType;
/// 集成Adapter是否成功
@property (nonatomic, assign) BOOL isAdapterIntegrationSucceed;
/// TopOnSDK 推荐使用三方SDK版本
@property (nonatomic, strong) NSArray<NSString *> *recommendVersionsArray;
/// TopOnSDK adapter 版本
@property (nonatomic, strong) NSString *adapterVersionString;

/// 集成三方SDK 具体 Framework
@property (nonatomic, strong) NSArray *sdkFrameworkArray;
/// 集成三方SDK 具体 Bundle
@property (nonatomic, strong) NSString *sdkBundleNameString;
/// adapter 具体 Framework
@property (nonatomic, strong) NSString *adapterNameString;

/// 文案最大高度
@property (nonatomic, assign) CGFloat rowHeight;

/// 获取最后集成结果
- (ATInspectNetworkSDKStauts)getInspectNetworkSDKStauts;
/// 获取打印日志
- (NSDictionary *)getIntegrationResult;

@end

NS_ASSUME_NONNULL_END
