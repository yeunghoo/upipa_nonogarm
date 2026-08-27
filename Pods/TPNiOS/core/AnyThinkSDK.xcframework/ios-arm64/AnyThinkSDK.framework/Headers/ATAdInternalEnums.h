//
//  ATAdInternalEnums.h
//  AnyThinkSDK
//
//  Created by Captain on 2025/4/24.
//

#ifndef ATAdInternalEnums_h
#define ATAdInternalEnums_h
@class ATSafeThreadDictionary;
//某些 adapter需要, 但是又不想对开发者开发的 放这里 区别ATAdEnums中的枚举
#define kATKuaishouLossUserInfoKeyHasShow  @"kATKuaishouLossUserInfoKeyHasShow"
#define kATKuaishouLossUserInfoKeyHasClick @"kATKuaishouLossUserInfoKeyHasClick"
#define kATKuaishouLossUserInfoKeyRequestID @"kATKuaishouLossUserInfoKeyRequestID"
#define kATKuaishouLossAdvertiserUserInfoKeyRequestID @"kATKuaishouLossAdvertiserUserInfoKeyRequestID"
#define kATKuaishouLossUserInfoKeyAdTitle @"kATKuaishouLossUserInfoKeyAdTitle"
#define kATKuaishouLossUserInfoKeyTiming @"kATKuaishouLossUserInfoKeyTiming"
#define kATWinLossAdWinnerNetworkFirmID @"kATWinLossAdWinnerNetworkFirmID"
#define kATWinLossAdTypekeyWinPrice @"kATWinLossAdTypekeyWinPrice"
#define kATWinLossAuthNetworkKey @"kATWinLossAuthNetworkKey"
#define kATWinLossAdJoinKeyTypeJoinAd @"kATWinLossAdJoinKeyTypeJoinAd"
#define kATWinLossAdTypeKeyBidInfo @"kATWinLossAdTypeKeyBidInfo"
#define kATWinLossAdWinnerNextUnitID @"kATWinLossAdWinnerNextUnitID"
#define kATWinLossNativeMaterialTypeKey @"kATWinLossNativeMaterialTypeKey"
#define kATSendWinLossCompletionKey @"kATSendWinLossCompletionKey"
#define kATWinLossSendResultErrorCodeKey @"errorCode" // 注意要用number类型
#define kATWinLossSendResultErrorMessageKey @"message"

typedef NS_ENUM(NSUInteger, ATWinLossSendResult) {
    ATWinLossSendResult_No_Support = 1,// adn不支持返回winloss上报的结果 (目前s2s 以及百度c2s全都是该选项)
    ATWinLossSendResult_Success,       // 上报成功
    ATWinLossSendResult_Fail,          // 上报失败
};

typedef NS_ENUM(NSInteger, ATFBBKFacebookAdBidFormat) {
    ATFBBKFacebookAdBidFormatBanner_320_50,     // Bid For Banner 320x50
    ATFBBKFacebookAdBidFormatBanner_HEIGHT_50,  // Bid For Banner with flexible width and height 50
    ATFBBKFacebookAdBidFormatBanner_HEIGHT_90,  // Bid For Banner with flexible width and height 90
    ATFBBKFacebookAdBidFormatBanner_HEIGHT_250, // Bid For Banner with flexible width and height 250
    ATFBBKFacebookAdBidFormatInterstitial,      // Bid For Interstitial
    ATFBBKFacebookAdBidFormatInstreamVideo,     // Bid For Instream Video
    ATFBBKFacebookAdBidFormatRewardedVideo,     // Bid For Rewarded Video
    ATFBBKFacebookAdBidFormatNative,            // Bid For Native
    ATFBBKFacebookAdBidFormatNativeBanner,      // Bid For Native Banner
};

typedef NS_ENUM(NSInteger, ATFBBKBidderType) {
    ATFBBKBidderType_FackBook,
    ATFBBKBidderType_IronSource
};

typedef NS_ENUM(NSUInteger, ATWinLossModeTiming) {
    ATWinLossModeTimingWin = 1,//展示广告(win)
    ATWinLossModeTimingWaterfallFinishWin = 2,//Waterfall结束时发win（包括：短超时，且最高价；短超时后填，且最高价；填充最高价，且没有更高价bid广告源正在请求）(win)
    ATWinLossModeTimingFilledWin = 3,//填充时触发策略“填充时发win wn_st_fl_sw”(win)
    ATWinLossModeTimingAdxWin = 4,//adx单接模式时，由开发者调用sdk的api，触发win(win)
    ATWinLossModeTimingFilledLowNLoss = 21,//填充低于缓存第n位(loss)
    ATWinLossModeTimingTokenExpiresLoss = 22,//wf结束后未使用的token标记为过期(wfe_t_sw)(loss)
    ATWinLossModeTimingFilledLowBidFloorLoss = 23,//填充价格低于竞价底价(loss)
    ATWinLossModeTimingS2SFillFailedLoss = 24,//s2s填充失败(loss)
    ATWinLossModeTimingExpiresWhenLoadShowIsReadyLoss = 25,//调load或isready或show，查到广告源过期且没有发过win(loss)
    ATWinLossModeTimingFilledHighCacheWhenRTBidLoss = 26,//开启实时竞价后，填充价格高于缓存，缓存发loss(loss)
    ATWinLossModeTimingFilledLowCacheWhenRTBidLoss = 27,//开启实时竞价后，填充价格小于等于缓存，新填充发loss(loss)
    ATWinLossModeTimingAdxLoss = 28,//adx单接模式时，由开发者调用sdk的api，触发loss(loss)
    ATWinLossModeTimingBidTimeoutAfterC2SFilledLoss = 29,//bid长超时后，才返回价格(loss)
    ATWinLossModeTimingRemoveCacheLoss = 30,//开发者调用sdk的api，指定清除缓存(loss)
    ATWinLossModeTimingC2SFillFailedLoss = 31, // c2s填充失败(loss)
    ATWinLossModeTimingShowOrClickKSLoss = 32, // 曝光或点击时发送快手的loss
    ATWinLossModeTimingDeveloperEcpmFiltrationLoss = 33, // 开发者设置ecpm过滤发送 loss
    ATWinLossModeTimingDeveloperPriceWinLoss = 34, // 回调Loaded,和开发者传入价格比价,大于则发 win/loss
    ATWinLossModeTimingRemoveWithCacheReason = 36, //当任意广告源获取Offer后因为缓存逻辑被丢弃时，记录
    // 6.4.35--6.4.60使用,6.4.60之后废弃
    ATWinLossModeTimingLoaddingWhenShowLoss = 99,//开发者在loadding过程中调用show，之后bid结果才返回的，补发loss(loss)

};

typedef void(^ATSendWinLossCompletion)(ATWinLossSendResult result, ATSafeThreadDictionary *errorInfo);


#endif /* ATAdInternalEnums_h */
