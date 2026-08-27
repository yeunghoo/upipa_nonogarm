//
//  ATPlacementModel.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 11/04/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <AnyThinkSDK/ATModel.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>
#import <UIKit/UIKit.h>

#import <AnyThinkSDK/ATStorage.h>
#import <AnyThinkSDK/ATModelProtocol.h>
#import <AnyThinkSDK/ATDynamicWaterfallParams.h>
#import <AnyThinkSDK/ATPlatfromInfo.h>

#import <AnyThinkSDK/ATEcwfModel.h>
#import <AnyThinkSDK/ATAdsLgStModel.h>

typedef NS_ENUM(NSInteger, ATADShowType) {
    /**
     * priority -> show times -> added time
     */
    ATADShowTypePriority = 0,
    /**
     * show times -> priority -> added time
     */
    ATADShowTypeSerial = 1
};

typedef enum : NSUInteger {
    ATLoadingRequestConcurrentFixedType = 1,
    ATLoadingRequestConcurrentEqualPriceType = 2,
} ATLoadingRequestModelType;

typedef NS_ENUM(NSInteger, ATNativeMixBannerStyleType) {
    ATNativeMixBannerStyleTypeToponOne = 1,
};

/// 广告请求类型
typedef NS_ENUM(NSInteger, ATLoadingAdApiType) {
    ATLoadingAdApiTypeDefault = 0, // 默认
    ATLoadingAdApiTypeRefresh = 1, // 刷新
    ATLoadingAdApiTypePlayAgain = 2, // 再看一个
    ATLoadingAdApiTypeAutoLoadInitiation = 3,// 自动请求: 初始化或创建广告对象
    ATLoadingAdApiTypeAutoLoadLoadFailed = 4, // 自动请求: 加载失败
    ATLoadingAdApiTypeAutoLoadNotReady  = 5,// 自动请求: isReady 为false
    ATLoadingAdApiTypeAutoLoadShowStart = 6,// 自动请求: 开始展示
    ATLoadingAdApiTypeAutoLoadShowFailed = 7,// 自动请求: 展示失败
    ATLoadingAdApiTypeFailedRetry = 8,// 非全自动加载模式: 加载失败自动请求
    ATLoadingAdApiTypeSerialMultiCachMode  = 9,// 串行多缓存
    ATLoadingAdApiTypeSharedPlacementPreload    = 10,// 共享广告位: 启动预加载
    ATLoadingAdApiTypeSharedPlacementTimer     = 11,//共享广告位: 定时任务请求
    ATLoadingAdApiTypeSharedPlacementSameFormatLoad     = 12, // 共享广告位:：绑定了共享池的广告位在生命周期内首次回调Load结果后执行相同广告类型共享池的预加载
    ATLoadingAdApiTypePresetCool    = 13,// 使用SDK内置策略执行WF后，额外增加使用线上冷启动策略发起请求
    ATLoadingAdApiTypePresetNormal  = 14,// 使用SDK内置策略执行WF后，额外增加使用线上非冷启动策略发起请求
};

typedef NS_ENUM(NSInteger, ATLoadModeType) {
    ATLoadModeTypeAutoLoad   = 1, /// 全自动请求
    ATLoadModeTypeDefault    = 2  /// 手动（默认）
};

typedef NS_ENUM(NSInteger, ATCallSuccessType) {
    ATCallSuccessShowPriorityType = 1,
    ATCallSuccessPricePriorityType = 2,
};
extern NSString *const kATPlacementModelCacheDateKey;
extern NSString *const kATPlacementModelCustomDataKey;

typedef NS_ENUM(NSUInteger, ATPlacementModelUserValueTimingType) {
    ATPlacementModelUserValueTimingTypeNone = 0,
    ATPlacementModelUserValueTimingTypeShow = 1,
};

typedef NS_ENUM(NSUInteger, ATPlacementModelUserValueStrategyIndexType) {
    ATPlacementModelUserValueStrategyIndexTypeLocal = 0,
    ATPlacementModelUserValueStrategyIndexTypeShowPrice = 1,
};

typedef NS_ENUM(NSUInteger, ATPlacementModelWaterfallModeType) {
    ATPlacementModelWaterfallModeTypeSerialMultiCach = 1,
    ATPlacementModelWaterfallModeTypeNormal = 2,
};


typedef NS_ENUM(NSUInteger, ATBannerAutoRefreshType) {
    ATBannerAutoRefreshTypePlacementStrategy = 1,
    ATBannerAutoRefreshTypeAdSourceStrategy = 2,
};

typedef NS_ENUM(NSInteger, ATPlacementModelBaiduReportType) {
    ATPlacementModelBaiduReportTypeUnKonw = 0,
    ATPlacementModelBaiduReportTypeNormalWin = 1 << 0,
    ATPlacementModelBaiduReportTypeNormalLoss = 1 << 1,
    ATPlacementModelBaiduReportTypeBiddingWin = 1 << 2,
    ATPlacementModelBaiduReportTypeBiddingLoss = 1 << 3,
    
};

typedef NS_ENUM(NSUInteger, ATPlacementSettingType) {
    ATPlacementSettingTypeNormal,
    ATPlacementSettingTypePreset,
    ATPlacementSettingTypeCool,
};

typedef NS_ENUM(NSInteger, ATPlacementModelAutoLoadType) {
    ATPlacementModelAutoLoadTypeUnKonw = 0,
    ATPlacementModelAutoLoadTypeLoadFailed = 1 << 0,
    ATPlacementModelAutoLoadTypeIsReadyFalse = 1 << 1,
    ATPlacementModelAutoLoadTypeShow = 1 << 2,
    ATPlacementModelAutoLoadTypeShowFailed = 1 << 3,
    
};

#pragma mark - ATPlacementModel
@interface ATPlacementModel : NSObject

-(instancetype) initWithDictionary:(NSDictionary *)dictionary associatedCustomData:(NSDictionary*)customData placementID:(NSString*)placementID;
-(instancetype) initWithDictionary:(NSDictionary *)dictionary placementID:(NSString*)placementID;

#pragma mark - 服务器返回
/// sdk本地缓存的接口内容
@property (nonatomic, strong, readonly) NSDictionary *cachedDic;
/// 服务端告诉SDK，需要更新本地缓存
@property (nonatomic, strong, readonly) NSDictionary *updateCachedDic;
/// 广告位填充成功回调模式（sdk6.1.51）1: 展示优先 2: 价格优先
@property (nonatomic, assign, readonly) ATCallSuccessType callSuccessType;
/// 优先使用持久化Setting Yes or No, 默认Yes 1为yes ，0表示no
@property (nonatomic, assign, readonly) BOOL cachesPlacementSetting;
/// 广告类型
@property (nonatomic, assign, readonly) ATAdFormat format;
/// 广告位 ID
@property (nonatomic, copy, readonly) NSString *placementID;
/// 广告位是否可用 1开0关
@property (nonatomic, assign, readonly) BOOL adDeliverySwitch;
/// 返回该次使用的groupid(segment_id)
@property (nonatomic, assign, readonly) NSInteger groupID;

/**
 Auto refresh is for banner.
 */
/// auto refresh 0 关闭，1 开启
@property (nonatomic, assign, readonly) BOOL autoRefresh;
/// auto refresh time 毫秒
@property (nonatomic, assign, readonly) NSTimeInterval autoRefreshInterval;
///Banner广告刷新策略1：使用现有广告位策略的自动刷新时间，在开发者后台配置（字段：auto_refresh_time，待确定）2：使用运营后台广告位广告平台(广告源)策略的自动刷新时间
@property (nonatomic, assign, readonly) ATBannerAutoRefreshType bannerAutoRefreshType;
/**
 * How many unit groups to be loaded concurrently
 */
/// 控制并行请求类型，枚举说明如下：1: 为固定数量请求，2: 为同价格请求，并行数量由req_ug_numsp控制，即同价格最大并行请求数量为req_ug_numsp
@property (nonatomic, assign, readonly) ATLoadingRequestModelType loadingRequestModelType;
/// 一次并行请求的最多ugroup个数
@property (nonatomic, assign, readonly) NSInteger fixedMaxConcurrentRequestCount;
/// 同价格最大并行请求数量
@property (nonatomic, assign, readonly) NSInteger equalPriceMaxConcurrentRequestCount;
/// 广告位展示逻辑,0 按优先级，1 轮播
@property (nonatomic, assign, readonly) ATADShowType showType;

/// 广告位本身天维度的最多展示次数。若group中的unit有配置cap_day 则返回group 维度中设置的cap_day；若group无配置则获取unit策略配置的cap_day，有则返回cap_day，无则使用-1（不限制条数）
@property (nonatomic, assign, readonly) NSInteger unitCapsByDay;
/// 广告位本身小时维度的最多展示次数。若group中的unit有配置cap_hour 则返回group 维度中设置的cap_hour；若group无配置则获取unit策略配置的cap_hour，有则返回cap_hour，无则使用-1（不限制条数）
@property (nonatomic, assign, readonly) NSInteger unitCapsByHour;
/// 表示unit每次展示之间最小时间间隔，单位毫秒，若group中的unit有配置pacing 则返回group 维度中设置的pacing；若group无配置则获取unit策略配置的pacing，有则返回pacing，无则使用-1（不限制条数）
@property (nonatomic, assign, readonly) NSTimeInterval unitPacing;
/// Wifi 自动播放,1开0关
@property (nonatomic, assign, readonly) BOOL wifiAutoSwitch;

@property (nonatomic, assign, readonly) BOOL autoloadingEnabled;
/// 所有的广告源
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* allUnitGroups;
/// 常规
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* unitGroups;
/// C2S
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* headerBiddingUnitGroups;
/// S2S
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* S2SHeaderBiddingUnitGroups;
/// online
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* olApiUnitGroups;
/// inhouse
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* inhouseUnitGroups;
/// bks
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* bksUnitGroups;
/// 兜底
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* bottomListUnitGroups;
/// 直投
@property (atomic, strong, readonly) NSArray<ATUnitGroupModel*>* directOfferHeaderBiddingUnitGroups;
/// adx
@property (nonatomic, strong, readonly) NSArray<ATUnitGroupModel*>* adxUnitGroups;
/// adx
@property (nonatomic, strong, readonly) NSArray<ATUnitGroupModel*>* adxOpenUnitGroups;
/// 动态出价
@property (nonatomic, strong, readonly) NSArray<ATUnitGroupModel*>* dynamicHeaderBiddingUnitGroups;
/// 动态出价客户端竞价广告源列表
@property (nonatomic, strong, readonly) NSArray<ATUnitGroupModel*>* dynamicBiddingC2SUnitGroups;
/// 动态出价服务端竞价广告源列表
@property (nonatomic, strong, readonly) NSArray<ATUnitGroupModel*>* dynamicBiddingS2SUnitGroups;
/// app所有广告位下的所有max平台自动出价类型三方广告源id, 分广告样式（format的id为key），json结构
@property (nonatomic, strong, readonly) NSDictionary *dynamicHBAdUnitIds;
/// 兜底广告请求发起时间,毫秒为单位
@property (nonatomic, assign, readonly) NSTimeInterval bottomRreqts;     // bottomAd dalay request time
/// Bid询价最大等待时间（毫秒）默认10000 ms
@property (nonatomic, assign, readonly) NSTimeInterval headerBiddingRequestLongTimeout;
/// WaterFall_HB最大启动时间（毫秒）默认2000 ms
@property (nonatomic, assign, readonly) NSTimeInterval headerBiddingRequestShortTimeout;
/// bid询价地址
@property (nonatomic, copy, readonly) NSString *S2SBidRequestAddress;
/// sdk在bid询价成功后执行Waterfall排序
@property (nonatomic, copy, readonly) NSString *waterFallBidRequestAddress;
/// 广告位Load Cap的计时周期 控制广告位Load Cap的计时周期时长，默认900000毫秒
@property (nonatomic, assign, readonly) NSTimeInterval loadCapDuration;
/// 广告位Load Cap设置 控制广告位在计时周期内可以发起Load的次数。默认-1（不限制次数）
@property (nonatomic, assign, readonly) NSInteger loadCap;
/// 有效缓存数量设置 控制WaterFall在回调Load Sucess后，继续执行WaterFall流程，直到全部广告源执行完成或达到缓存数量要求。默认1
@property (nonatomic, assign, readonly) NSInteger expectedNumberOfOffers;
/// WaterFall填充后等待竞价广告源询价结果时间，单位毫秒
@property (nonatomic, assign, readonly) NSTimeInterval bidWaitTimeout;
/// WaterFall填充后等待竞价广告源请求结果时间，单位毫秒
@property (nonatomic, assign, readonly) NSTimeInterval reqWaitTimeout;
/// Load失败后重试最小等待时间(毫秒) Load失败后需要等待指定时间后才可以重试Load。默认10000毫秒
@property (nonatomic, assign, readonly) NSTimeInterval loadFailureInterval;
/// StoreKit加载时机
@property (nonatomic, assign, readonly) NSTimeInterval offerLoadingTimeout;
/// dsource维度：LoadSuccess状态标记UP_status有效期，默认900秒(15分钟)；输出单位毫秒
@property (nonatomic, assign, readonly) NSTimeInterval statusValidDuration;//Upstatus
/// 接口通过placementid+adsourcelist所有的内容生成hashid值
@property (nonatomic, copy, readonly) NSString *asid;//generated by server side
/// traffic_group_id对应默认分组或者ab test分组
@property (nonatomic, copy, readonly) NSString *trafficGroupID;

/// 在缓存失效后，SDK实时更新策略。用于控制SDK的策略更新超时时间。 (返回给客户端都是毫秒) Ad type=Splash   默认0秒 Ad type=Native & Native Template=Native Splash，默认0秒 Ad type=RV、interstitial、Banner，Native 默认2秒
@property (nonatomic, assign, readonly) NSTimeInterval updateTolerateInterval;

/// 自定义流量分组策略变更时，新增的超时时间ps_ct_out_cus
@property (nonatomic, assign, readonly) NSTimeInterval waitUpdateTimeoutInterval;
/// Placement策略的有效缓存时间，默认1800秒 (返回给客户端都是毫秒)
@property (nonatomic, assign, readonly) NSTimeInterval cacheValidDuration;
/// myOfferSetting用字典存储 offers数组格式 placeHolders字典
@property (nonatomic, strong, readonly) NSArray* offers;
/// my offer setting 下面是my offer setting的数据 （myoffer新增）
@property (nonatomic, strong, readonly) NSDictionary *myOfferSetting;
/// 需要对myofferurl占位符替换的字典
@property (nonatomic, strong, readonly) NSDictionary *placeHolders;
/// 当Waterfall没有填充时，是否使用兜底的myoffer，默认Yes 默认是1 不使用默认是0
@property (nonatomic, assign, readonly) NSInteger usesDefaultMyOffer;
/// 否预加载myoffer，默认Yes,默认是1 不使用默认是0
@property (nonatomic, assign, readonly) BOOL preloadMyOffer;
/// placement维度的callback回调信息
@property (nonatomic, strong, readonly) NSDictionary *callback;
/// 默认2000ms
@property (nonatomic, assign, readonly) NSInteger FBHBTimeOut;
/// adx offer adtype setting
@property (nonatomic, strong, readonly) NSDictionary *adxSettingDict;
/// adx offer adtype setting
@property (nonatomic, strong, readonly) NSDictionary *olApiSettingDict;
/// Waterfall填充等待时间,单位毫秒
@property (nonatomic, assign, readonly) NSTimeInterval waterfallFillTime;
/// 货币单位
@property (nonatomic, copy, readonly) NSString *currency;
/// USD兑开发者账号币种的汇率(v5.7.9新增)当开发者账号币种为USD时，exch_r=1.0
@property (nonatomic, copy, readonly) NSString *exchangeRate;
/// 上报Display Notification的广告平台id列表，例子：[”1“,“15”]
@property (nonatomic, strong, readonly) NSArray *bURLNotificationFirms;

/// 同步展示频次给Mintegral SDK的开关 1: 开（默认）2: 关
@property (nonatomic, assign, readonly) BOOL isShowSendMTG;
/// 同步Mediation id给优量汇SDK的开关 1: 开（默认）2: 关
@property (nonatomic, assign, readonly) BOOL isMediationIDSendGDT;
/// placement config 配置 SDK在 TK & DA 直接上报这个结构体
@property (atomic, strong, readonly) NSDictionary *placementABDic;
/// 有配置的开发者，在下发广告位策略时，sr_sw=1（需要返回Admob SDK展示收益）没有配置的开发者，在下发广告位策略时，sr_sw=2（不需要返回Admob SDK展示收益）
@property (nonatomic, assign, readonly) BOOL isDisplayPriceSwitch;
/// 使用Admob广告源最近N次展示回调收益预估Admob排序价格
@property (nonatomic, assign, readonly) NSInteger networkEstimatePriceNum;
/// bid接口sdk展示offer信息的缓存数量，每次请求广告时在bid接口上报 -1：不用缓存展示信息 大于0：需要缓存的展示数 默认保存10条
@property (nonatomic, assign, readonly) NSInteger bidImprssionExtraNum;
/// 广告位又接入共享位时，共享位的uuid，注意：没接入时不返回该字段或返回空字符串
@property (nonatomic, copy, readonly) NSString *sharePlacementId;

/// 轮播数量
@property (nonatomic, assign, readonly) NSInteger rotationNum;
/// 轮播间隔
@property (nonatomic, assign, readonly) NSTimeInterval rotationInter;
/// 轮播 查询缓存时间
@property (nonatomic, assign) NSTimeInterval rotationCacheTs;

/// sdk impression事件发生后，是否发起impression请求，用于激励视频反作弊。1:开启. 2关闭
@property (nonatomic, assign, readonly) BOOL iRSwitch;
/// impression的url从这里拿
@property (nonatomic, strong, readonly) NSDictionary *addrSt;
/// impression的url
@property (nonatomic, copy, readonly) NSString *impT;

/// ADX bidding独立请求开关SDK v6.4.44 以上支持，1开 2关
@property (nonatomic, assign, readonly) BOOL adxIndependentBiddingSwitch;

@property (nonatomic, assign, readonly) NSInteger maxCacheNum;

/// SDK向TopOn 服务端请求 OnRewardVerify接口（上报激励视频回调事件）时请求信息采用的非对称加密算法标识，暂时只支持RSA
@property (nonatomic, assign, readonly) NSInteger encryptFlag;
/// SDK向TopOn 服务端请求 OnRewardVerify接口（上报激励视频回调事件）时请求信息用的非对称加密算法的公钥
@property (nonatomic, copy, readonly) NSString *encryptPublicKey;
/// 额外下发给sdk的动态信息，这些信息sdk在激励回调时必须透传给tk,
@property (nonatomic, strong, readonly) NSDictionary *encryptApiDynamicInfoDic;

/// 动态瀑布流开关
@property (nonatomic, assign, readonly) BOOL dynamicWaterfallSwitch;
/// 瀑布流开关，默认2，枚举说明 1：打开动态瀑布流策略，下面的配置有效，且同时记录历史填充数据 2：关闭动态瀑布流策略，不记录历史填充数据
@property (nonatomic, strong, readonly) ATDynamicWaterfallParams *dynamicWaterfall;

/// 缓存最大过期时间，默认：604800(秒），7天
@property (nonatomic, assign, readonly) NSTimeInterval maxCacheExpirationTime;
/// 等待策略缓存最大过期时间后的更新超时时间(pl_refresh_timeout)，单位毫秒，默认5000ms
@property (nonatomic, assign, readonly) NSTimeInterval placementRefreshTimeout;
/// 开屏广告SDK API传入超时时间，毫秒 大于0：开屏广告SDK API传入超时时间优先采用广告位策略下发的该参数 小于0或不下发：不使用该超时时间，即开关为关
@property (nonatomic, assign, readonly) NSTimeInterval splashSdkPriorityTimeOut;

/// 纯Bidding模式下已返回竞价结果的竞价广告源等待其他竞价广告源的结果再发请求的时间，单位毫秒（sdk6.3.75）大于0时：等待指定时间再发起广告请求 小于等于0时或不下发：不等待（默认）
@property (nonatomic, assign, readonly) NSTimeInterval biddingWaitOtherTime;
/// WaterFallHb 最大超时时间(hb_start_time)比开屏广告SDK API传入TimeOut时间提前,单位毫秒（sdk6.3.75）：大于0：WaterFallHb 最大超时时间(hb_start_time)比开屏广告SDK API传入TimeOut时间提前小于0或不下发：不使用该超时时间，即开关为关
@property (nonatomic, assign, readonly) NSTimeInterval adjustWaterFallHbTime;
/// 全自动加载模式触发时机（支持多选），支持以下枚举类型，且支持多选（sdk6.4.10）：

/// 触发自动加载模式的时机：1：loadFailed 2：isReady为False 3：开始show 4：show Failed
@property (nonatomic, assign, readonly) ATPlacementModelAutoLoadType placementModelAutoLoadType;

/* v6450 **/
/// 激励防刷 相关参数
@property (nonatomic, strong, readonly) ATAdsLgStModel *adsLgSetting;
/* v6450 **/

/// v6470 动态瀑布流在智能优化（串行多缓存）模式下不过滤广告源的开关
@property (nonatomic, assign, readonly) BOOL wf2NfSwitch;
/// Banner使用自渲染原生广告源时的点击区域
@property (nonatomic, strong, readonly) NSArray *mixAdClickAreaArray;
/// HB广告源获取buyeruid最大等待时间，毫秒为单位
@property (nonatomic, assign, readonly) NSInteger getBuyeruIdWaitTime;
/// Topon bks请求地址（未配置时返回空字符串）
@property (nonatomic, copy, readonly) NSString *inhouseUrl;

/// bks url of third plantforms
@property (nonatomic, copy, readonly) NSString *thirdInhouseUrl;
/// 人民币兑美元汇率
@property (nonatomic, copy, readonly) NSString *exchRateC2U;
/// 竞价底价过滤字段bidfloord的值，注意：0代表不限
@property (nonatomic, copy, readonly) NSString *bidFloor;
/// S2S竞价广告源最大返回数, 注意：0代表不限
@property (nonatomic, assign, readonly) NSInteger s2sBidMax;
/// 请求成功重试开关，枚举说明如下：1：开 2：关
@property (nonatomic, assign, readonly) BOOL loadSuccessRetrySwitch;
/// 请求失败重试开关，枚举说明如下：1：开 2：关
@property (nonatomic, assign, readonly) BOOL loadFailRetrySwitch;
/// 请求合并开关req_merge,枚举说明如下
@property (nonatomic,assign, readonly) BOOL requestMerge;
/// 控制不同平台二价比例，三方平台账号id为key, 比例为值（double
@property (nonatomic, strong, readonly) NSDictionary *gspRatesDic;
/// Adx拓展信息【
@property (nonatomic, copy, readonly) NSString *adxExtJson;
/// 以下Load模式下打开广告源填充失败请求间隔，支持以下枚举类型，且支持多选：1：手动调研Load模式2：广告位请求失败后重试3：全自动Load模式
@property (nonatomic, strong, readonly) NSArray *loaddingTypeSwitchArray;
/// 同步Request id给Pangle SDK的开关 1: 开（默认）2: 关
@property (nonatomic, assign, readonly) BOOL isSetPangleRequestId;

/// 当使用SDK预置策略（或 开屏内置广告源）请求WF时,在WF结束后TopOn SDK根据广告位策略参数(presetwf_reload_sw)判断本次是否需要在WF结束后使用线上返回的广告位策略再执行一次WF
@property (nonatomic, assign, readonly) BOOL shouldLoadMoreWhenPresetLoaded;
/// 开发者是否存在首次请求流量分组规则并且能命中，下发是条件为：配置有+能命中 1-是2否
@property (nonatomic, assign, readonly) BOOL hasCoolPlacementSettings;
/// 本次返回的广告位策略是否为冷启动策略特殊说明：使用0枚举是sdk旧版本已经使用了这些枚举0：普通的策略(非冷启动策略）1：SDK预置策略2：冷策略策略
@property (nonatomic, assign) ATPlacementSettingType type;
/// 广告位价格存储策略 1：存储到本地数据库（默认为1）2：不存储到本地数据库，且需要将本地保存数据清除
@property (nonatomic, assign, readonly) BOOL isSaveUserValueData;
///广告位策略接口sdk上报的广告价格数组的信息条数（fill_price和imp_priced数组的item数）-1：SDK不用上报填充/展示信息大于0：需要缓存的填充/展示数默认保存10条
@property (nonatomic, assign, readonly) ATPlacementModelUserValueTimingType userValueTimingType;
/// 触发广告位策略更新的信息
@property (nonatomic, assign, readonly) ATPlacementModelUserValueStrategyIndexType userValueStrategyIndex;
/// 广告位策略接口sdk上报的广告价格数组的信息条数
@property (nonatomic, assign, readonly) NSInteger userValueReportCount;
/// 触发阈值，[][2]double 外层为变成数组，item是固定长度2的浮点数数组
@property (nonatomic, strong, readonly) NSArray<NSArray<NSNumber *> *> *userValuePriceRanges;
/// 开启“串行+多缓存”模式，打开开关后，TopOn SDK将会执行缓存两次WaterFall结果流程（即WF填充后会再执行一次串行WF流程）
@property (nonatomic, assign, readonly) ATPlacementModelWaterfallModeType waterfallModeType;
/// 串行+多缓存”模式第二次WaterFall请求的并行数据，默认1
@property (nonatomic, assign, readonly) NSInteger serialMultiCachModeMaxConcurrentRequsetCount;
/// 串行+多缓存”模式并行请求模式，第二次串行WF下，默认按1 1：固定数量请求2：同价格并行
@property (nonatomic, assign, readonly) ATLoadingRequestModelType serialMultiCachModeRequestModelType;
/// Load Failed自动重试Load发起时间间隔，默认2000毫秒
@property (nonatomic, assign, readonly) NSTimeInterval LoadFailedAutoRetryLoadInterval;
@property (nonatomic, assign, readonly) NSInteger statusNum;
/// 制百度SDK在本次请求时是否携带上次竞价信息
@property (nonatomic, assign, readonly) ATPlacementModelBaiduReportType baiduReportType;
/// 标记是否使用TopOn激励视频的S2S回调
@property (nonatomic, assign, readonly) BOOL s2sSwitch;
/// 样式模板
@property (nonatomic, assign, readonly) ATNativeMixBannerStyleType nativeMixBannerStyleType;
/// 智能瀑布流所需的数据
@property (atomic, strong) ATEcwfModel *ecwfModel;


#pragma mark - 非服务器返回
/// 是否存在 HB 广告源
@property (nonatomic, assign) BOOL isExistHBAdSource;
/// 是否是 CDN 请求结果
@property (nonatomic, assign) BOOL isCDNResult;
/// 原始策略
@property (atomic, strong) NSDictionary *originalPlacementDic;
/// 开发者自定义规则
@property (atomic, strong) NSDictionary *associatedCustomData;

/// ad名称: 比如:(native,splash......)
@property (atomic, strong) NSString *formatNameString;
/// ad 枚举字符串: 比如: @"1"
@property (atomic, strong) NSString *formatString;

/// 策略缓存时间
@property (atomic, strong) NSDate *cacheDate;

@property (atomic, copy) NSString *campaign;
/// 判断是否是共享广告位ID
@property (nonatomic, assign) BOOL hasSharePlacementId;
/// 判断是否是共享广告位
@property (nonatomic, assign) BOOL isSharePlacement;
/// 百度上报信息
@property (atomic, strong) NSDictionary *baiduReportDic;

/* v6435 */

/// 是否超过最大有效时长,默认24小时
@property (nonatomic, assign) BOOL isExceedMaxValidity;

/// 所有的广告源信息
@property (atomic, copy) NSArray<ATUnitGroupModel*>* allUnitGroupArray;

/// 直投广告源 ID
@property (atomic, strong) NSArray *directOfferUnitIDArray;
/// 开发者传入的 size
@property (atomic, strong) NSValue *developerBannerSizeValue;
/// 开发者传入的 size
@property (nonatomic, assign) CGSize developerBannerSize;

#pragma mark - 方法
- (Class)adManagerClass;

- (NSDictionary *)revenueToPlatforms;

- (CGFloat)getNetworkgspRate:(NSString *)networkFirmID;
- (void)parsingUnitGroupsWithDictionary:(NSDictionary *)dictionary;

@end
