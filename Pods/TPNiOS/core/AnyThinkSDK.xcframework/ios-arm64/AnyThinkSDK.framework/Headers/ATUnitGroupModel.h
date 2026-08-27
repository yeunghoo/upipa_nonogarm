//
//  ATUnitGroupModel.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 11/04/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <AnyThinkSDK/ATModel.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATBidInfo.h>
#import <AnyThinkSDK/ATModelProtocol.h>
#import <AnyThinkSDK/ATAdAdapter.h>
#import <AnyThinkSDK/ATStorage.h>

@class ATAdSourceFltRuleModel;

#define ATBaiDuUnitIDKey @"ATBaiDuUnitIDKey"
#define ATBaiDuplacementIdKey @"ATBaiDuplacementIdKey"
#define ATBaiDuUpdateExposureNotificationKey @"ATBaiDuUpdateExposureNotificationKey"


typedef NS_ENUM(NSInteger, ATRenderingType) {
    ATRenderingTopOnType = 1,    //TopOn SDK渲染，默认
    ATRenderingSelfType = 2,     // 开发者自渲染
};

typedef NS_ENUM(NSInteger, ATMixRewardGiveOutType) {
    ATMixRewardGiveOutTypeClose = 1,
    ATMixRewardGiveOutTypeClick = 2,
};

typedef NS_ENUM(NSInteger, ATAdLoadedCallBackType) {
    ATAdLoadedCallBackTypeRendeSuccessr = 1,// 渲染成功,才回调
    ATAdLoadedCallBackTypeMetaData = 2,// 元数据加载完成,就回调
};

typedef NS_ENUM(NSInteger, ATRequestFiledType) {
    ATRequestFiledAdFodderDataType = 1,
    ATRequestFiledAdMetaDataType = 2,
};


typedef NS_ENUM(NSInteger, ATAdListType) {
    ATAdListTypeNormal = 1,
    ATAdListTypeC2S = 2,
    ATAdListTypeS2S = 3,
    ATAdListTypeAdx = 4,
    ATAdListTypeDsp = 5,
    ATAdListTypeOnLine = 6,
    ATAdListTypeInhouse = 7,
    ATAdListTypeDirect = 8,
    ATAdListTypeDynamicBid = 9,
    ATAdListTypeBottom = 10,
    ATAdListTypeBKS = 11,
    ATAdListTypeDynamicBidC2S = 12,
    ATAdListTypeDynamicBidS2S = 13,

};


typedef NS_ENUM(NSInteger, ATNetworkEstimatePriceType) {
    ATNetworkEstimatePriceTypeSort = 0,
    ATNetworkEstimatePriceTypeEstimate,
    ATNetworkEstimatePriceTypeReal,
    ATNetworkEstimatePriceTypeRealPriceNil,
    ATNetworkEstimatePriceTypeTimeOut,

};

typedef NS_ENUM(NSInteger, ATShowAutoLoadType) {
    ATShowAutoOneAdSupportLoadType = 1,
    ATShowAutoOneAdNotSupportLoadType,
    ATShowAutoOneNetWorkNotSupportLoadType,
};
/// ad type：0 Native, 1 Rewarded, 2 Banner, 3 Interstitial, 4 Splash
//typedef NS_ENUM(NSInteger, ATUnitGroupJointAdType) {
//    ATUnitGroupJointAdOtherType = -1,
//    ATUnitGroupJointAdNativeType = 0,
//    ATUnitGroupJointAdRewardedType = 1,
//    ATUnitGroupJointAdBannerType = 2,
//    ATUnitGroupJointAdInterstitialType = 3,
//    ATUnitGroupJointAdSplashType = 4,
//};

typedef NS_ENUM(NSInteger, ATNetworkCurrencyType) {
    ATNetworkCurrencyCNYType = 0,
    ATNetworkCurrencyUSDType,
};

typedef NS_ENUM(NSInteger, ATNUrlAuctionBidToWinType) {
    ATNUrlAuctionBidToWinTypeUseCurrentPrice = 1,
    ATNUrlAuctionBidToWinTypeUseZeroPrice = 2
};



typedef NS_ENUM(NSInteger, ATNativeMaterialType) {
    ATNativeMaterialTypeCrossPic = 1,
    ATNativeMaterialTypeVerticalPic = 2,
    ATNativeMaterialTypeCrossVideo = 3,
    ATNativeMaterialTypeVerticalVideo = 4,
    ATNativeMaterialTypeThreePic = 5,
    ATNativeMaterialTypeBanner = 6,
    ATNativeMaterialTypeOther = 7,
};

typedef NS_ENUM(NSInteger, ATCallBackPriceType) {
    ATCallBackPriceTypeCurrentPrice        = 1,   // 返回price
    ATCallBackPriceTypeSortPriorityLevel   = 2,   // 返回sortPriorityLevel，本期先当price处理，后续再补充。
    ATCallBackPriceTypeZeroPrice           = 3    // 返回0
};

typedef NS_ENUM(NSInteger, ATWinpriceForLossToPMPDealType) {
    ATWinpriceForLossToPMPDealTypeRandomPrice         = 1,  // 竞败方最高价格*130%内随机取值（默认值，默认不下发该字段）
    ATWinpriceForLossToPMPDealTypeHighestPricePlus    = 2,  // 竞败方最高价格+0.01
    ATWinpriceForLossToPMPDealTypeRealPMPPrice        = 3,  // 传真实PMP价格
    ATWinpriceForLossToPMPDealTypeZeroPrice           = 4,  // 设置为0
    ATWinpriceForLossToPMPDealTypeNegativeOnePrice    = 5   // 设置为-1
};

// v6450 竞价链路上报
typedef NS_ENUM(NSInteger, ATAdSourceLoadLinkNode) {
    ATAdSourceLoadLinkNodeBid = 1,
    ATAdSourceLoadLinkNodeBidReponse,
    ATAdSourceLoadLinkNodeLoad,
    ATAdSourceLoadLinkNodeFill,
    ATAdSourceLoadLinkNodeSendWL,
    ATAdSourceLoadLinkNodeShow
};

@class ATAdAdapterManager;
// TODO: 瀑布流移除 readUnitGroupWithIdentifier,彻底删除 无用协议
@interface ATUnitGroupModel : NSObject <ATModelProtocol, ATStorageEntityProtocol>
-(instancetype) initWithDictionary:(NSDictionary *)dictionary;

#pragma mark -  服务器返回
/// 广告源填充回调 1：使用广告素材填充回调，默认2：使用广告数据填充回调
@property (nonatomic, assign) ATRequestFiledType requestFiledType;
/// netwok对应的sdk实现的adapter的类路径
@property(nonatomic, weak, readonly) Class adapterClass;
/// netwok对应的sdk实现的adapter的类路径
@property(nonatomic, copy, readonly) NSString *adapterClassString;
/// 天维度中，指unit对应的mediation group中的各个network对应的展示次数限制，若对应network达到上限，则不再请求和展示该network的广告。无配置则返回-1（无限制）
@property(nonatomic, assign, readonly) NSInteger capByDay;
/// 小时维度中，指unit对应的mediation group中的各个network对应的展示次数限制，若对应network达到上限，则不再请求和展示该network的广告。无配置则返回-1（无限制）
@property(nonatomic, assign, readonly) NSInteger capByHour;
/// network缓存时间，毫秒
@property(nonatomic, assign, readonly) NSTimeInterval networkCacheTime;
/// networkFirmID
@property(nonatomic, assign, readonly) NSInteger networkFirmID;
/// networkName
@property(nonatomic, copy, readonly) NSString *networkName;
/// 广告源名称，暂时只有debug_key模式才响应该参数
@property (nonatomic, strong, readonly) NSString *unitName;
/// network每次请求广告条数 ;对应strategy_placement表中 nw_offer_requests字段
@property(nonatomic, assign, readonly) NSInteger networkRequestNum;
/// Network广告数据超时时间 默认值：5秒 （输出单位毫秒）
@property(nonatomic, assign, readonly) NSTimeInterval networkDataTimeout;
/// network超时时间，毫秒
@property(nonatomic, assign, readonly) NSTimeInterval networkTimeout;
/// 上次无填充时，本次不发请求的指定时间
@property(nonatomic, assign, readonly) NSTimeInterval skipIntervalAfterLastLoadingFailure;
/// 上次Bid失败后，下次重新发起Bid时间（毫秒）默认值：2000（2秒）
@property(nonatomic, assign, readonly) NSTimeInterval skipIntervalAfterLastBiddingFailure;
/// unitID
@property(nonatomic, copy, readonly) NSString *unitID;
/// UG 请求广告需要到的广告位信息，采用json格式返回，
@property(nonatomic, strong, readonly) NSDictionary *content;
/// 指unit对应的mediation group中的广告请求间隔。无配置则返回-1（无限制）
@property(nonatomic, assign, readonly) NSTimeInterval showingInterval;
/// 广告尺寸
@property(nonatomic, assign, readonly) CGSize adSize;
/// 广告源策略的下发的自动刷新时间（在广告源的conten下发）单位为毫秒，默认15000毫秒
@property(nonatomic, assign, readonly) NSTimeInterval autoRefreshInterval;
/// 主要针对账号为非USD币种的用户下发。具体数据为开发者设置的自身币种的eCPM Floor或者是自身币种的自动优化eCPM Floor
@property(nonatomic, strong) NSString *ecpmByCurrency;
/// ecpm层级，由小到大
@property(nonatomic, assign, readonly) NSInteger ecpmLevel;
///bh 请求超时 毫秒下发
@property(nonatomic, assign, readonly) NSTimeInterval headerBiddingRequestTimeout;
/// header_bidding 自动 Request时是否重新发起Bid  1不支持，2是支持
@property(nonatomic, assign, readonly) BOOL headerBidding;
/// 广告源类型
@property(atomic, assign, readonly) ATUnitGroupType unitGroupType;
/// adsource维度：Bid Token缓存有效期，默认值1800秒（30分钟）输出单位毫秒
@property(nonatomic, assign, readonly) NSTimeInterval bidTokenTime;
/// adsource维度：LoadSuccess状态标记UP_status有效期，默认900秒(15分钟)；输出单位毫秒
//@property(nonatomic, assign, readonly) NSTimeInterval statusTime;
/// 同步展示广告对象给独立插件开关
@property(nonatomic, assign, readonly) BOOL postsNotificationOnShow;
/// 同步点击广告对象给独立插件开关
@property(nonatomic, assign, readonly) BOOL postsNotificationOnClick;
/// 精度 只有uglist 正常广告源和myoffer才会下发，hb下发为空
@property(nonatomic, strong) NSString *precision;
/// 广告源在isready查询时，是否将自填充的广告源加入Offer缓存
@property(nonatomic, assign, readonly) BOOL canAutoReady;
/// HB&Adx广告源，WaterFall结束后未使用的Bid Token标记成过期的控制参数（v5.7.30新增）1：否，按Bid Token缓存有效期进行处理 （默认）2：是，WaterFall结束后未使用的Bid Token标记成过期
@property(nonatomic, assign, readonly) BOOL waterfallTimeOutSW;
/// 控制全部Tracking和埋点是否上报Bid Price
@property(nonatomic, assign, readonly) BOOL reportBidPriceSW;
/// 控制Header Bidding & Adx广告源是否每次Load时均发起实时竞价 1：关，在Bid Token有效期和Offer有效缓存期内不实时竞价2：开，每次Load时均实时竞价
@property(nonatomic, assign, readonly) BOOL bidRealTimeLoadSW;
/// 废弃
@property(nonatomic, assign, readonly) BOOL returnHBEcpmSW;
/// 标记是否使用TopOn激励视频的S2S回调
@property(nonatomic, assign, readonly) BOOL unitGroupS2SSW;
/// 控制同价格广告源的优先展示权重，取值 1~99
@property(nonatomic, assign, readonly) NSInteger weight;
/// 直投 oid
@property(nonatomic, copy, readonly) NSString *directOfferOid;

/// 触发show后插入loading图层的时长，单位毫秒，默认0表示不插入
@property (nonatomic, assign, readonly) NSTimeInterval showDelay;
/// ad type：0 Native, 1 Rewarded, 2 Banner, 3 Interstitial, 4 Splash
@property(nonatomic, assign) ATUnitGroupJointAdType jointAdType;
/// 排序价格
@property (nonatomic, strong) NSString *sortPriorityLevel;
/// S2S广告源填充价格比缓存第N高价低时发Loss
@property(nonatomic,assign, readonly) NSInteger s2sSendLossPosition;
/// Gromore 常规/bidding 广告源的币种参数 人民币：CNY美元：USD
@property (nonatomic, assign, readonly) ATNetworkCurrencyType networkCurrencyType;

/// 仅在展示时发送Win
@property (nonatomic, assign, readonly) BOOL onlyDisplaySendWin;

/// 使用Admob当次展示回调的收益时
@property (nonatomic, assign, readonly) BOOL networkEstimatePriceSwitch;
/// Banner使用自渲染原生广告源时的点击区域
@property (nonatomic, strong, readonly) NSArray *mixAdClickAreaArray;
/// Admob应用内容映射地址列表，暂时只有Admob使用
@property (nonatomic, strong, readonly) NSArray<NSString *> *contentURLStrings;

/// TopOn SDK允许京媒平台竞价广告源返回的最大bid price
@property (nonatomic, assign, readonly) CGFloat permitMaxBidPrice;
/// 对京媒平台竞价广告源返回的bid price进行价格扣量的系数
@property (nonatomic, assign, readonly) CGFloat quantityDiscountRate;

/// 是否使用topon的账号，注意：暂时只有京媒平台使用（sdk6_2_95）
@property (nonatomic, assign, readonly) BOOL isUseTopOnAccount;
/// 广告源最大缓存数量（
@property (nonatomic, assign, readonly) NSInteger adsMaxCacheNum;
/// 控制客户端广告源是否发送Win通知
@property (nonatomic, assign, readonly) BOOL isPermitSendWin;
/// 控制客户端广告源是否发送Loss通知
@property (nonatomic, assign, readonly) BOOL isPermitSendLoss;
/// 上报给Google的requestAgent的标识
@property (nonatomic, strong, readonly) NSString *admobRequestAgent;
/// 广告源摇一摇开关
@property (nonatomic, assign, readonly) BOOL isNativeShakeSwitch;

///  admobBibType
@property(nonatomic, assign, readonly) NSInteger admobBibType;
/// 控制Admob广告源在Admob Hybird模式下是否上报request_id及设置is_hybrid_setup
@property(nonatomic, assign, readonly) BOOL isAdmobHybrid;
/// TopOn广告平台账号ID（20231019新增），sdk需要透传给adx（目的：adx需要根据这个id来查出admob bidding 不同证书）
@property(nonatomic, assign, readonly) NSInteger networkId;

/// 自定义conten
@property (nonatomic, strong, readonly) NSString *customExtString;

@property (nonatomic, strong, readonly) NSArray<NSNumber *> *supportExpressType;

/// 模板比例类型
@property(nonatomic, assign) ATAdOfferTemplateRatioType template_ratio;
/// 混用原生渲染类型
@property(nonatomic, assign, readonly) ATRenderingType renderingType;
/// 全屏半屏类型
@property(nonatomic, assign) ATAdOfferInterType interType;
/// 竞价信息埋点开关
@property (nonatomic, assign, readonly) BOOL isHBInfoDaSwitch;
///混用激励下发时机
@property (nonatomic, assign, readonly) ATMixRewardGiveOutType mixRewardGiveOutType;

/// 动态竞价底价开关，默认下发为2，关
@property (nonatomic, assign, readonly) BOOL isDynamicBidFloorSwitch;

///优量汇堆栈信息上报开关（sdk6.3.45新增），暂时只有优量汇用到，枚举说明 1：开启（默认）2：关闭
@property (nonatomic, assign, readonly) BOOL isGdtStackSwitch;
/// 有当前竞价广告源出价或出价最低时Win通知上报的第二高价的方法
@property (nonatomic, assign, readonly) ATNUrlAuctionBidToWinType nUrlAuctionBidToWinType;


/// 用于标记每次广告位策略请求标识，每个广告源在每次广告位策略请求中都会获得唯一的unique_id
@property (nonatomic, strong, readonly) NSString *uniqueId;
/// 用于ecpm加密的密钥数据 服务端密钥对应的唯一标识
@property (nonatomic, assign, readonly) NSInteger serverKeyId;
/// 客户端密钥对应的唯一标识
@property (nonatomic, assign, readonly) NSInteger clientKeyId;
/// 客户端竞价广告源非对称加密算法的公钥
@property (nonatomic, strong, readonly) NSString *clientPubKey;
/// ecpm加密后的(ecpm+unitid)数据
@property (nonatomic, strong, readonly) NSString *clientSideEcpmKeyString;
/// 广告源加载限制,请求次数的周期
@property(nonatomic, assign, readonly) NSTimeInterval loadCapDuration;
/// 广告源请求次数上限
@property(nonatomic, assign, readonly) NSInteger loadCapTime;
/// 广告源维度无填充过滤规则(req_filter_rule),无配置或非法时为 nil
@property(nonatomic, strong, readonly) ATAdSourceFltRuleModel *reqFilterRule;
/// 延迟发起竞价时间
@property(nonatomic, assign, readonly) NSInteger bidReqDelayDuration;
/// 广告源或广告平台价格系数
@property(nonatomic, assign, readonly) CGFloat sptyCoefficient;

/// 竞价成功
@property (nonatomic, assign, readonly) ATCallBackPriceType adSourceBidSuccessCallBackPriceType;
/// 广告源请求开始
@property (nonatomic, assign, readonly) ATCallBackPriceType adSourceRequestCallBackPriceType;
/// 广告源填充成功或者失败
@property (nonatomic, assign, readonly) ATCallBackPriceType adSourceRequestResultRCallBackPriceType;
/// 查询广告缓存
@property (nonatomic, assign, readonly) ATCallBackPriceType checkAdCacheCallBackPriceType;
/// 广告展示及展示后行为
@property (nonatomic, assign, readonly) ATCallBackPriceType showCallBackPriceType;
/// 输给PMP时胜出价上报逻辑
@property (nonatomic, assign, readonly) ATWinpriceForLossToPMPDealType winpriceForLossToPMPDealType;

@property (nonatomic, assign, readonly) BOOL shouldAdapterLoadedSendWin;
/* 插屏广告点击跳转后，是否自动关闭广告 v6430添加 */
/// 轮播启动时点击后是否关闭
@property (nonatomic, assign, readonly) BOOL closeAfterClick;
/// 轮播开关 1开启 2关闭
@property (nonatomic, assign, readonly) BOOL rotationSwitch;
/// 默认值4.5秒，支持填0-10，可置空。下发单位毫秒
@property (nonatomic, assign, readonly) NSTimeInterval rotationSpiInter;

/// 是否给广告平台上报Bidfloor，决定是否需要在请求中带上sdk上报的竞价底价
@property (nonatomic, assign, readonly) NSInteger pBfSwitch;
/// 是否为开启激励防刷的平台
@property (nonatomic, assign) BOOL isAntiCheating;
/// 百度展示回调类型1：onAdPresent2：onAdExposed
@property (nonatomic, assign, readonly) NSInteger bdIT;
/// 价&自定义价格过滤广告源Loss通知使用底价
@property (nonatomic, assign, readonly) BOOL isUseBidfloorPriceWinLoss;

///广告源是否支持show时请求下一条广告源,仅针对激励视频、插屏和开屏广告,枚举说明：1：支持；2：单条广告源不支持；3（v5.8.11新增）：同广告平台且同广告类型不支持
@property(nonatomic, assign, readonly) ATShowAutoLoadType showAutoLoadType;

/// 竞价广告源是否支持提前请求
@property(nonatomic, assign, readonly) BOOL isHBAdvanceRequest;

/// 广告源维度底价
@property (atomic,strong, readonly) NSString *bidFloor;


#pragma mark -  非服务器返回
/// bidinfo 获取的 bidid
@property(nonatomic, strong) NSString *tpBidID;
/// 是否触发关闭按钮误点击
@property (nonatomic, assign) BOOL isAccidentalClick;
/// 广告源类型
@property (nonatomic, assign) ATAdListType adListType;

/// networkFirmString
@property(atomic, strong) NSString *networkFirmString;

/// 废弃 unitGroupID
@property(atomic, copy) NSString *unitGroupID;
/// tk1,4,6,11 上报networkid, 后续新增广告平台需适配该字段
@property(atomic, copy) NSString *network_placementId;

/// 开屏zoom
@property(nonatomic, assign) BOOL splashZoomOut;
/// 广告源价格
@property(atomic, strong) NSString *price;
/// 广告源 bid 价格
@property(atomic, strong) NSString *bidPrice;
/// 广告源 bidtoken
@property(atomic, strong) NSString *bidToken;

/// when ad is filterd
@property(nonatomic,assign) NSInteger priority;
/// when ad is filterd
@property (atomic, strong) NSDecimalNumber *sortPriorityLevelNumber;
/// bid 广告源 ecpm 字符串
@property (atomic, strong) NSString *bidinfoEcpmStr;

/// 预估价格类型
@property (nonatomic, assign) ATNetworkEstimatePriceType networkEstimatePriceType;
/// 预估价格
@property (atomic, strong) NSString *networkEstimatePresentShowEcpmPrice;

/// C2S 广告加载成功 时间戳
@property (atomic, strong) NSDate *adDataSucceedDate;
/// C2S 渲染成功 时间戳
@property (atomic, strong) NSDate *adRenderSucceedDate;
/// 广告 开始请求 时间戳
@property (atomic, strong) NSDate *requestStartDate;

/// 广告位原始数据
@property (atomic, strong) NSDictionary *originalPlacementDic;

/// see -[ATUnitGroup updateSamePriceWeight]
@property (atomic, assign) CGFloat samePriceWeight;

/// 动态出价底价
@property (atomic, strong) NSString *dynamicFloorPrice;

/// 缓存排序价格,客户端排序价格=填充价格(s_pty)*p_coef
@property (atomic, strong) NSString *showCacheSortPriorityLevel;

/// 开发者设置的过滤 ecpm 价格
@property (atomic, strong) NSString *developerCustomFilterEcpm;
@property (atomic, strong) NSString *developerCustomFilterRules;

// 三方广告信息
/// 原生广告素材类型(百度需要)
@property (nonatomic, assign) ATNativeMaterialType nativeMaterialType;
/// 广告源请求时间戳
@property (atomic, strong) NSNumber *requestTimesTamp;
/// 三方广告 请求ID
@property (atomic, strong) NSString *network_requestID;

@property (atomic, strong) NSDictionary *winAdInfoDic;
///三方广告 加密价格
@property (atomic, strong) NSString *network_en_p;
/// 用于上报 轮播数
@property (nonatomic, assign) NSInteger event_rotation_count;
/// 用于上报 关闭时可以播的缓存数
@property (nonatomic, assign) NSInteger event_rotation_close_cache_count;
/// 用于上报 关闭原因
@property (nonatomic, assign) NSInteger event_rotation_close_reason;
/// 用于上报 关闭原因 这个是本地的校验之后的结果对其进行赋值, 不是从服务器上获取的
@property (nonatomic, assign) BOOL rotation_switch;

/// 激励回调来源 1：广告平台平台回调 2：topon依赖playend事件兜底补充的回调（仅定制版本会兜底，主版本没有兜）
@property (nonatomic, assign) NSInteger rewardFrom; // 目前固定为 1  安卓也是这样的
/// 触发激励时, 广告平台是否回调playend csj 使用agin回调 和现有的分开  1:已经触发end 2:未触发end
@property (nonatomic, assign) BOOL isPlayend;
/// 广告平台回调成功或者失败 激励是否成功 1: 成功  2: 失败 现在ios的设计只能传1
@property (nonatomic, assign) BOOL isRewarded;
/// app策略 s2s_addr
@property (atomic, copy) NSString *url;
/// 是否请求超时
@property (nonatomic, assign) BOOL isRequestTimeout;

- (void)setLoadLinkNode:(ATAdSourceLoadLinkNode)linkNode;

- (NSString *)getLoadLink;

/// same price need a order, use samePriceWeight to order, when ad cache return
/// @param newWeight when water fall load, will calculate new weight
- (void)updateSamePriceWeight:(CGFloat)newWeight;
- (BOOL)saveWithUnitGroup:(ATUnitGroupModel *)unitGroup;
- (void)updateWithUnitGroup:(ATUnitGroupModel *)unitGroup;
- (void)removeWithUnitGroup:(ATUnitGroupModel *)unitGroup;
/// 注意:获取最新加载生成的 UnitGroupModel
- (ATUnitGroupModel *)readUnitGroupWithIdentifier:(NSString *)identifier;

- (void)updateServerKeyId:(NSInteger)serverKeyId clientSideEcpmKeyString:(NSString *)clientSideEcpmKeyString;
- (BOOL)isAuthNetworkPrivacy;

- (BOOL)isC2SType;
- (BOOL)isS2SType;
//- (BOOL)isPMPType;

@end
