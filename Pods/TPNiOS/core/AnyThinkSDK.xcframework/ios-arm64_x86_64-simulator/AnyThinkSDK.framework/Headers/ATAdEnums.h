//
//  ATAdEnums.h
//  AnyThinkSDK
//
//  Created by Captain on 2024/9/18.
//  Copyright © 2024 AnyThink. All rights reserved.
//
// TODO: 枚举类拆分到各自模块
#ifndef ATAdEnums_h
#define ATAdEnums_h

#define kATExtraInfoMediaViewFrameKey @"kATExtraInfoMediaViewFrameKey"

#define kATTrackerExtraNetworkTransIDKey @"third_trans_id"
#define kDeviceWidth [UIScreen mainScreen].bounds.size.width
#define KDeviceHeight [UIScreen mainScreen].bounds.size.height


#define kATKuaishouLossUserInfoKeyHasShow  @"kATKuaishouLossUserInfoKeyHasShow"
#define kATKuaishouLossUserInfoKeyHasClick @"kATKuaishouLossUserInfoKeyHasClick"
#define kATKuaishouLossUserInfoKeyRequestID @"kATKuaishouLossUserInfoKeyRequestID"
#define kATKuaishouLossAdvertiserUserInfoKeyRequestID @"kATKuaishouLossAdvertiserUserInfoKeyRequestID"
#define kATKuaishouLossUserInfoKeyAdTitle @"kATKuaishouLossUserInfoKeyAdTitle"
#define kATKuaishouLossUserInfoKeyTiming @"kATKuaishouLossUserInfoKeyTiming"
#define kATGDTLossUserInfoKeyTypeNetworkFirmID @"kATGDTLossUserInfoKeyTypeNetworkFirmID"
#define kATGDTLossUserInfoKeyTypeSeatId @"kATGDTLossUserInfoKeyTypeSeatId"
#define kATWinLossAdJoinKeyTypeJoinAd @"kATWinLossAdJoinKeyTypeJoinAd"
#define kATWinLossAdTypekeyWinPrice @"kATWinLossAdTypekeyWinPrice"
#define kATWinLossAdTypeKeyBidInfo @"kATWinLossAdTypeKeyBidInfo"
#define kATWinLossAdWinnerNetworkFirmID @"kATWinLossAdWinnerNetworkFirmID"
#define kATWinLossAdWinnerNextUnitID @"kATWinLossAdWinnerNextUnitID"
#define kATWinLossAdWinnerNextUnitNetworkFirmID @"kATWinLossAdWinnerNextUnitNetworkFirmID"
#define kATWinLossUserInfoKeyAdDesc @"kATWinLossUserInfoKeyAdDesc"
#define kATWinLossUserInfoKeyAdInteractionType @"kATWinLossUserInfoKeyAdInteractionType"
#define kATWinLossUserInfoKeyNetworkPlacementId @"kATWinLossUserInfoKeyNetworkPlacementId"

#define kATWinLossAuthNetworkKey @"kATWinLossAuthNetworkKey"
#define kATWinLossSendWinKey @"kATWinLossSendWinKey"

#define kATWinLossNativeMaterialTypeKey @"kATWinLossNativeMaterialTypeKey"

#define kATSendWinLossCompletionKey @"kATSendWinLossCompletionKey"

typedef NS_ENUM(NSInteger, ATAdFormat) {
    ATAdFormatNative = 0,
    ATAdFormatRewardedVideo = 1,
    ATAdFormatBanner = 2,
    ATAdFormatInterstitial = 3,
    ATAdFormatSplash = 4,
    ATAdFormatMediaVideo = 50
};

typedef NS_ENUM(NSInteger, ATEndCardClickable) {
    ATEndCardClickableFullscreen = 1,
    ATEndCardClickableCTA,
    ATEndCardClickableBanner
};

typedef NS_ENUM(NSInteger, ATScreenOrientation) {
    ATScreenOrientationPortrait,
    ATScreenOrientationLandscape
};

typedef NS_ENUM(NSInteger, ATInterstitialType) {
    ATInterstitialVideo = 1,
    ATInterstitialPicture
};

typedef NS_ENUM(NSInteger, ATLinkType) {
    ATLinkTypeAppStore           = 1, // storekit打开
    ATLinkTypeSafari             = 2, // 外部浏览器
    ATLinkTypeWebView            = 3, // 内部webView vc打开
    ATLinkTypeAPKDownload        = 4, // APK下载，Android特有，iOS不支持
    ATLinkTypeInnerSafari        = 5, // 调起内部safari浏览器
    ATLinkTypeWXMiniProgram      = 6, // 微信小程序
    ATLinkTypeQuickApp           = 7, // 快应用，Android特有，iOS不支持
    ATLinkTypeWXNativePage       = 8  // 微信原生页
};

typedef NS_ENUM(NSInteger, ATOfferLayoutType) {
    ATOfferLayoutTypeNormal = 0,
    ATOfferLayoutTypeExpress
};

typedef NS_ENUM(NSInteger, ATClickMode) {
    ATClickModeSync = 1,
    ATClickModeAsync
};
//
//typedef NS_ENUM(NSInteger, ATLoadType) {
//    ATLoadTypeBrowser = 1,
//    ATLoadTypeInternalBrowser
//};
typedef NS_ENUM(NSInteger, ATLoadType) {
    ATLoadTypeSafari = 1,
    ATLoadTypeInternalWebview
};


typedef NS_ENUM(NSInteger, ATLoadStorekitTime) {
    ATLoadStorekitTimePreload = 1,
    ATATLoadStorekitTimeClick,
    ATATLoadStorekitTimeNone
};
typedef NS_ENUM(NSInteger, ATVideoClickable) {
    ATVideoClickableNone = 1,
    ATVideoClickableWithCTA
};

typedef NS_ENUM(NSInteger, ATNetworkFirmId) {
    ATNetworkFirmIdADX =  66,
    ATNetworkFirmIdMyOffer = 35,
    ATNetworkFirmIdGDTOnline = 42,
    ATNetworkFirmIdDirectOffer =  67,
};

typedef NS_ENUM(NSInteger, ATOfferModelType) {
    ATOfferModelMyOffer = 1,
    ATOfferModelADX =  2,
    ATOfferModelOnlineApi =  3,
    ATOfferModelDirectOffer =  4,
};

typedef NS_ENUM(NSInteger, ATOfferCrtType) {
    ATOfferCrtTypeOneImage = 1,
    ATOfferCrtTypeImages = 2,
    ATOfferCrtTypeOneImageWithText = 3,
    ATOfferCrtTypeImagesWithText = 4,
    ATOfferCrtTypeVideo = 5,
    ATOfferCrtTypeXHTML = 6
};

typedef NS_ENUM(NSInteger, ATDeepLinkClickMode) {
    ATDeepLinkModeNone = 1,
    ATDeepLinkModePreClickUrl = 2,
    ATDeepLinkModeLastClickUrl = 3
};

typedef NS_ENUM(NSInteger, ATClickType) {
    ATClickTypeClickUrl = 1,
    ATClickTypeDeepLinkUrl,
    ATClickTypeClickJumpUrl,
    ATClickTypeClickUniversalLinkUrl,
    ATClickTypeClickMarketUrl

};

typedef NS_ENUM(NSInteger, ATUnitGroupType) {
    ATUnitGroupTypeNormal = 1,
    ATUnitGroupTypeAdx,
    ATUnitGroupTypeC2S,
    ATUnitGroupTypeS2S,
    ATUnitGroupTypeInHouse,
    ATUnitGroupTypeBKS,
    ATUnitGroupTypeDirectOffer,
    ATUnitGroupTypeDefault,
    ATUnitGroupTypeDynamicHB,
    ATUnitGroupTypeDynamicC2S,
    ATUnitGroupTypeDynamicS2S,

};

typedef NS_ENUM(NSInteger, ATSplashType) {
    ATSplashTypeSplice = 1,
    ATSplashTypeFullScreen
};

typedef NS_ENUM(NSInteger, ATSplashImageScaleType) {
    ATSplashImageScaleTypeFit = 1,
    ATSplashImageScaleTypeFill
};

typedef NS_ENUM(NSInteger, ATBiddingCurrencyType) {
    ATBiddingCurrencyTypeUS        = 1,
    ATBiddingCurrencyTypeCNY       = 2,
    ATBiddingCurrencyTypeCNYCents  = 3
};

typedef NS_ENUM(NSInteger, ATOfferClickAdType) {
    ATOfferClickAdTypeUserClick = 1,
    ATOfferClickAdTypeAutoClickAfterDelay =  2,
    ATOfferClickAdTypeAutoClickAfterFinish = 3,
    ATOfferClickAdTypeShakeClick = 4,
    ATOfferClickAdTypeAutoClickImageClick = 5,
    ATOfferClickAdTypeAutoClickVideoClick = 6,
    ATOfferClickAdTypeAutoClickEndCardClick = 7,
    ATOfferClickAdTypeStoresKitClick = 8,
    ATOfferClickAdTypeSKOverlyClick = 9,
    ATOfferClickAdTypeInvalidCloseButtonClick = 10,
    ATOfferClickAdTypeGuideOverlyClick = 11,
    ATOfferClickAdTypeAdWithoutSlideClick = 12,
    ATOfferClickAdTypeAdInsideSlideClick = 13,
    ATOfferClickAdTypeEndCardFloatingLayerGuideClick = 14,
    ATOfferClickAdTypeEndCardRetentionPageClick = 15,
    ATOfferClickAdTypeRewardedVideoTaskClick = 16,
    ATOfferClickAdTypeBubbleDropClick = 17,
};

typedef NS_ENUM (NSInteger, ATNativeAdInteractionType) {
    ATNativeAdInteractionTypeUnknown        = 0,
    ATNativeAdInteractionTypeNone           = 1,  // pure ad display
    ATNativeAdInteractionTypeURL            = 2,  // open the webpage using a browser
    ATNativeAdInteractionTypePage           = 3,  // open the webpage within the app
    ATNativeAdInteractionTypeDownload       = 4,  // download the app
    ATNativeAdInteractionTypePhone          = 5,  // make a call
    ATNativeAdInteractionTypeMessage        = 6,  // send messages
    ATNativeAdInteractionTypeEmail          = 7,  // send email
    ATNativeAdInteractionTypeVideoAdDetail  = 8,  // video ad details page
    ATNativeAdInteractionTypeWechat         = 9,  // open wechat
    ATNativeAdInteractionTypeOthers         = 100 // types returned by other ad sdk
};



typedef NS_ENUM(NSInteger, ATOfferAdpType) {
    ATOfferAdpTypeNormal = 0,
    ATOfferAdpTypeMraid = 1,
    ATOfferAdpTypeVast = 2
};

typedef NS_ENUM(NSInteger, ATOfferADPAcceptType) {
    ATOfferADPAcceptTypeMraid = 1,
    ATOfferADPAcceptTypeVast = 2,
    ATOfferADPAcceptTypePMP = 3,
    ATOfferADPAcceptTypeWebTemplate = 4,
};

typedef NS_ENUM(NSInteger, ATGuideClickOverlayType) {
    ATGuideClickOverlayTypeUnknown            = 0,
    ATGuideClickOverlayTypeGestureGuidance    = 1,  // 滑动手势
    ATGuideClickOverlayTypeDragPuzzle         = 2,  // 拖动拼图
    ATGuideClickOverlayTypeQAPopup            = 3,  // 问答弹窗
    ATGuideClickOverlayTypeNoviceGuide        = 4,  // 引导弹窗
    ATGuideClickOverlayTypeConfirmJump        = 5,  // 跳转确认
    ATGuideClickOverlayTypeFingerClickGuide   = 6,  // 手指点击引导
    ATGuideClickOverlayTypeFullScreenSwipe    = 7,  // 全屏滑动
    ATGuideClickOverlayTypeLuckybag           = 8,  // 福袋
    ATGuideClickOverlayTypeChopOnce           = 9,  // 砍一刀
    ATGuideClickOverlayTypeSlidePuzzle        = 10, // 滑动拼图有惊喜
    ATGuideClickOverlayTypeGestureSlide       = 11, // 新滑动手势
    ATGuideClickOverlayTypeGesureClick        = 12, // 新手指点击引导
    ATGuideClickOverlayTypeBigWhiteHand       = 13  // 大白指滑动
};


typedef NS_ENUM(NSInteger, ATRVTncentiveTaskType) {
    ATRVTncentiveTaskTypeNone              = 1,
    ATRVTncentiveTaskTypeReduceDuration    = 2,
    ATRVTncentiveTaskTypeADFree            = 3
};

typedef NS_ENUM(NSInteger, ATAdOfferInterType) {
    ATAdOfferInterTypeFull = 1,
    ATAdOfferInterTypeHalf
};

typedef NS_ENUM(NSInteger, ATAdOfferTemplateRatioType) {
    ATAdOfferTemplateRatioType9_16 = 1,
    ATAdOfferTemplateRatioType1_1
};

typedef NS_ENUM(NSInteger, ATADXMixFormat) {
    ATADXMixFormatNative = 1,
    ATADXMixFormatRewardedVideo = 2,
    ATADXMixFormatBanner = 3,
    ATADXMixFormatInterstitial = 4,
    ATADXMixFormatSplash = 5,
};

typedef NS_OPTIONS(NSInteger, ATAdCloseType) {
    ATAdCloseUnknow = 1,            // ad close type unknow
    ATAdCloseSkip = 2,              // ad skip to close
    ATAdCloseCountdown = 3,         // ad countdown to close
    ATAdCloseClickcontent = 4,      // ad clickcontent to close
    ATAdCloseShowfail = 99          // ad showfail to close
};

typedef NS_ENUM(NSInteger, ATNativeAdRenderType) {
    ATNativeAdRenderSelfRender = 1,
    ATNativeAdRenderExpress = 2,
};

typedef NS_ENUM(NSInteger, ATNativeAdType) {
    ATNativeAdTypeFeed = 1, //In-feed Ads (Native Ads)
    ATNativeAdTypePaster = 2 //Patch Ads
};

typedef NS_ENUM(NSInteger, ATAdMaterialFormat) {
    ATAdMaterialFormatUnknown = 1,// 未知 或 adn不支持获取物料格式
    ATAdMaterialFormatImage,
    ATAdMaterialFormatVideo,
    ATAdMaterialFormatOther
};

typedef NS_ENUM(NSInteger, ATPlayerStatus) {
    ATPlayerStatusStartPlay,
    ATPlayerStatusPause,
    ATPlayerStatusFinish,
    ATPlayerStatusResume,
    ATPlayerStatusAbort
};

typedef NS_ENUM(NSUInteger, ATToponTemplateExpressType) {
    ATToponTemplateExpressType_LeftImage = 1,
    ATToponTemplateExpressType_LeftText,
    ATToponTemplateExpressType_AboveImage,
    ATToponTemplateExpressType_AboveText,
    ATToponTemplateExpressType_TextFloating,
    ATToponTemplateExpressType_Default,
};


/// Video Player Status
typedef NS_ENUM(NSUInteger, ATVideoPlayerStatus) {
    ATVideoPlayerStatusDefault,    // 默认状态
    ATVideoPlayerStatusWillStart,  // 调用play方法
    ATVideoPlayerStatusBuffered,   // 缓存完成
    ATVideoPlayerStatusStarted,    // 播放中
    ATVideoPlayerStatusFinished,   // 播放完成
    ATVideoPlayerStatusPaused,     // 播放暂停
    ATVideoPlayerStatusResumed,    // 播放复播
    ATVideoPlayerStatusError,      // 播放异常
};

typedef NS_ENUM(NSInteger, ATOwnAdOfferRenderType) {
    ATOwnAdOfferRenderTypeNormal = 0,
    ATOwnAdOfferRenderTypeMraid = 1,
    ATOwnAdOfferRenderTypeH5Template = 2
};

/// ad type：0 Native, 1 Rewarded, 2 Banner, 3 Interstitial, 4 Splash
typedef NS_ENUM(NSInteger, ATUnitGroupJointAdType) {
    ATUnitGroupJointAdOtherType = -1,
    ATUnitGroupJointAdNativeType = 0,
    ATUnitGroupJointAdRewardedType = 1,
    ATUnitGroupJointAdBannerType = 2,
    ATUnitGroupJointAdInterstitialType = 3,
    ATUnitGroupJointAdSplashType = 4,
};

typedef NS_ENUM(NSUInteger, ATCtaAnimationType) {
    ATCtaAnimationTypeBreath = 1,// 呼吸
    ATCtaAnimationTypeSway,// 中心点摆动
    ATCtaAnimationTypeStreak,// 斜边划过
    ATCtaAnimationTypeBreathAndStreaks,// 呼吸&划过
    ATCtaAnimationTypeHandClick,// 小手点击
};

typedef NS_ENUM(NSInteger, ATBannerClickType) {
    ATBannerClickTypeTap = 1,
    ATBannerClickTypeInsideSlideTap,
    ATBannerClickTypeAllClick,
};

typedef NS_ENUM(NSInteger, ATOfferInterActableArea) {
    ATOfferInterActableAreaAll,
    ATOfferInterActableAreaVisibleItems,
    ATOfferInterActableAreaCTA
};

typedef NS_ENUM(NSUInteger, ATAssetsResourceMaterialType) {
    ATAssetsResourceMaterialTypeUnknown           = 0, // 未设置
    ATAssetsResourceMaterialTypeOnlyImage         = 1, // 仅图片
    ATAssetsResourceMaterialTypeOnlyVideo         = 2, // 仅视频
    ATAssetsResourceMaterialTypeImageWithVideo    = 3, // 同时包含图片和视频
    ATAssetsResourceMaterialTypeNoImageAndVideo   = 4, // 无视频无主图（icon或xhtml）
    ATAssetsResourceMaterialTypeOnlyXHTML         = 5, // 仅mraid
    ATAssetsResourceMaterialTypeXHTMLAndVideo     = 6, // mraid+视频
    ATAssetsResourceMaterialTypeWebTemplateVideo  = 7, // h5模版+视频广告
    ATAssetsResourceMaterialTypeWebTemplate       = 8, // 纯图h5模版广告
};

typedef NS_ENUM(NSUInteger, ATOfferMediaViewExpressType) {
    ATOfferMediaViewExpressTypeLeftImage = 1,
    ATOfferMediaViewExpressTypeLeftText,
    ATOfferMediaViewExpressTypeAboveImage,
    ATOfferMediaViewExpressTypeAboveText,
    ATOfferMediaViewExpressTypeTextFloating,
    ATOfferMediaViewExpressTypeDefault,
};

typedef NS_ENUM(NSUInteger, ATTriggerCloseClickType) {
    ATTriggerCloseClickTypeClickUnknown = 0, // 未设置
    ATTriggerCloseClickTypeClickClose = 1, // 开发者点击关闭按钮
    ATTriggerCloseClickTypeCountdownClose = 2, // 广告倒计时结束关闭
    ATTriggerCloseClickTypeForcedClose = 3, // 广告视图收到系统的关闭通知时的异常关闭上报
    ATTriggerCloseClickTypeTemplateClose = 4, // adx mtg 模板关闭
    ATTriggerCloseClickTypeMraidRenderClose = 5, // mraid 渲染异常关闭
    ATTriggerCloseClickTypeSplashClickClose = 6, // 开屏跳转后关闭广告策略（click_close）触发的关闭
    ATTriggerCloseClickTypeSplashCountDownPlayClose = 7, // 开屏视频倒计时结束后继续播放场景的自然关闭
    ATTriggerCloseClickTypeWebCallBackClose = 8, // H5回调关闭事件
    ATTriggerCloseClickTypeWebDefaultClose = 9, // H5模版原生兜底关闭按钮
    ATTriggerCloseClickTypeWebShowFailClose = 10, // H5展示失败触发关闭
    ATTriggerCloseClickTypeSplashUserClickAfterNoClose = 11, // 开屏广告倒计时结束后不自动关闭，用户手动点击关闭按钮触发关闭事件
};
#endif /* ATAdEnums_h */
