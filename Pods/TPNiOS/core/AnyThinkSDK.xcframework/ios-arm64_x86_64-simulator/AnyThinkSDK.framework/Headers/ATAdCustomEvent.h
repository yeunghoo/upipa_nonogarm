//
//  ATAdCustomEvent.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 05/07/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATTracker.h>
#import <AnyThinkSDK/ATBidInfo.h>
#import <AnyThinkSDK/ATAdManager+Internal.h>
#import <AnyThinkSDK/ATBaseTrackProtocol.h>
#import <AnyThinkSDK/ATInteriorTrackProtocol.h>
#import <AnyThinkSDK/ATLoadAdapterResult.h>
#import <AnyThinkSDK/ATPlacementModel.h>

@class ATSafeThreadDictionary, ATAdObject;
@class ATAdSourceRequestParams;

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kATSDKFailedToLoadSplashADMsg;
extern NSString *const kATSDKFailedToLoadBannerADMsg;
extern NSString *const kATSDKFailedToLoadInterstitialADMsg;
extern NSString *const kATSDKFailedToLoadNativeADMsg;
extern NSString *const kATSDKFailedToLoadRewardedVideoADMsg;
extern NSString *const kATSDKSplashADTooLongToLoadPlacementSettingMsg;
extern NSString *const kATSDKImportIssueErrorReason;
extern NSString *const kATAdAssetsAppIDKey;

extern NSString *const kATAdCustomEventNotificationKey;

typedef NS_OPTIONS(NSInteger, ATCustomEventType) {
    ATCustomEventLoaded = 0,
    ATCustomEventLoadFail = 1,
    ATCustomEventShow = 2,
    ATCustomEventShowFail = 3,
    ATCustomEventClick = 4,
    ATCustomEventClose = 5,
    ATCustomEventDetailViewWillPresentScreen = 6,
    ATCustomEventCloseBeforeViewAppear = 7, 
};

typedef NS_ENUM(NSUInteger,ATMediaPlayerStatus) {
   ATMediaPlayerStatusInitial = 0,         // 初始状态
   ATMediaPlayerStatusLoading = 1,         // 加载中
   ATMediaPlayerStatusStarted = 2,         // 开始播放
   ATMediaPlayerStatusPaused = 3,          // 用户行为导致暂停
   ATMediaPlayerStatusError = 4,           // 播放出错
   ATMediaPlayerStatusStoped = 5,          // 播放停止
   ATMediaPlayerStatusWillStart = 10,      // 即将播放
};

typedef NS_ENUM(NSInteger, ATADXDeepLinkInstallStatus) {
    ATADXDeepLinkInstallStatusUnknow = 0,
    ATADXDeepLinkInstallStatusYES = 1,
    ATADXDeepLinkInstallStatusNO = 2,
    ATADXDeepLinkInstallStatusElse = 3
};

#define ATAdShowTargetCustomEventKey @"at_adTargetCustomEvent"

#define ATAdTruthCustomEventKey @"ad_type"
#define ATAdRequestCallBackMode @"ad_s_reqf_mode"

#define ATAdSendC2SBidPriceKey @"ATAdSendC2SBidPriceKey"
#define ATAdSendC2SBidInfoKey @"ATAdSendC2SBidInfoKey"
#define ATAdSendC2SCurrencyTypeKey @"ATAdSendC2SCurrencyTypeKey"
#define ATAdSendC2SOriginPriceKey @"ATAdSendC2SOriginPriceKey"
@class ATAdOfferCacheModel;
@interface ATAdCustomEvent : NSObject<ATBaseTrackProtocol,ATRewardedTrackProtocol,ATSplashTrackProtocol,ATNativeTrackProtocol,ATInterstitialTrackProtocol,ATBannerTrackProtocol,ATInteriorTrackProtocol,ATMediaVideoTrackProtocol>

@property (atomic, copy) void(^requestCompletionBlock)( NSArray<NSDictionary *> * _Nullable assets,  NSError * _Nullable error);

//用户原生拼接插屏视频状态传递（腾讯）
@property(nonatomic, copy) void (^videoStatusCallback)(ATMediaPlayerStatus status);
/// 触发点击
@property(nonatomic, copy) void (^triggerClickCallback)(void);

@property (nonatomic, copy) void (^customEventMetaDataDidLoadedBlock)(void);

@property (nonatomic, copy) ATLoadAdapterResultBlock loadAdapterResultBlock;

@property (nonatomic, readonly) NSMutableArray<NSDictionary *> *assets;
@property (nonatomic, readonly) NSDate *showDate;
@property (nonatomic, readonly) NSString *psIDOnShow;
//@property (nonatomic, strong) NSNumber *sdkTime;
@property (nonatomic, strong) NSDictionary *serverInfo;
@property (nonatomic, strong) NSDictionary *localInfo;
@property (nonatomic, strong) NSDate *displaySuccessDate;
@property (nonatomic, strong) NSString *networkUnitId;
@property (nonatomic, strong) NSDictionary *networkCustomInfo;
@property (nonatomic, strong) NSString *networkAdvertisingID;
@property (nonatomic, strong) ATSafeThreadDictionary *networkExtarInfoDic;
@property (nonatomic, strong) ATTrackerInfo *trackerExtraInfo;
@property (nonatomic, assign) ATRequestFiledType requestFiledType;
@property (nonatomic, assign) ATOfferClickAdType clickType;
@property (nonatomic, assign) ATAdCloseType closeType;
@property (nonatomic, assign) NSInteger requestNumber;
/**
 * Failed or successful, a request's considered finished.
 */
@property (nonatomic, assign) NSInteger numberOfFinishedRequests;
@property (nonatomic, assign) BOOL isC2SBiding;
@property (nonatomic, assign) BOOL rewardGranted;
@property (nonatomic, weak) ATAdOfferCacheModel *ad;
@property (nonatomic, weak) id adapter;
@property (nonatomic, weak) id delegate;
@property (nonatomic, strong) id _Nullable protectLifeCycleObject;

/// 是否由 core层的 发送 TK 4
@property (nonatomic, assign) BOOL isSendImpressionTrackingIfNeed;

@property (nonatomic, strong) NSDictionary *trackCustomExtraInfo;

@property (nonatomic,copy)NSString *placementID;
@property (nonatomic,assign)NSInteger format;
@property (nonatomic,assign)ATPlacementModelAutoLoadType placementModelAutoLoadType;
@property (nonatomic,assign)BOOL autoRefresh;
/// 是否是补充点击
@property (nonatomic, assign) BOOL  isRepenishClick;
- (instancetype)initWithUnitID:(NSString *)unitID serverInfo:(NSDictionary *)serverInfo localInfo:(NSDictionary *)localInfo;
+ (NSDictionary *)serverInfoWithPlacementModel:(ATPlacementModel *)placementModel requestID:(NSString *)requestID adSourceRequestParams:(ATAdSourceRequestParams *)adSourceRequestParams;
+ (NSInteger)calculateAdPriority:(ATAdObject *)ad;
- (NSDictionary *)delegateExtra;
- (NSDictionary *)getDelegateExtraWithCaller:(ATAdManagerReadyAPICaller)caller;
- (void)handleAssets:(NSDictionary *)assets;
- (void)handleLoadingFailure:(NSError *)error;
- (void)handleClose;
- (void)handleShow;
- (void)handleShowFailed;
- (void)handleFailToPlayVideoWithError:(NSError *)error extra:(NSDictionary *)extraDic;

- (void)trackClick;
- (void)notifyAdapterShow;

- (void)saveShowAPIContext;
- (void)unionTrackAdWithTrackType:(ATADTrackType)trackType extraBlock:(void (^) (ATSafeThreadDictionary *trackingExtra))block;
- (void)unionTrackAdClickWithBlock:(void (^) (ATSafeThreadDictionary *trackingExtra))block;
- (void)unionTrackAdShowWithBlock:(void (^) (ATSafeThreadDictionary *trackingExtra))block;
- (void)unionTrackAdShowAgainWithBlock:(void (^) (ATSafeThreadDictionary *trackingExtra))block;

- (ATADXDeepLinkInstallStatus)getDeepLinkInstallStatus;
- (ATNativeADSourceType)adSourceType;

- (void)getNetworkExtendInfo:(id)networkAd;

@end

NS_ASSUME_NONNULL_END
