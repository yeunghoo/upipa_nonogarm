//
//  VTAdProxy.m
//  excat_nonogarm
//
//  TopOn（TPNiOS）中介广告代理
//  广告源：ADX / Meta / Vungle / Bigo / InMobi / Chartboost / DT(Fyber)
//  插页 & 激励：一调用 show 立刻预加载下一条，播放期间跑完瀑布流
//

#import "VTAdProxy.h"
#import <UIKit/UIKit.h>
#import <AppTrackingTransparency/AppTrackingTransparency.h>
#import <AdSupport/AdSupport.h>
#import <AnyThinkSDK/AnyThinkSDK.h>
#import <FBAudienceNetwork/FBAdSettings.h>

#pragma mark - TopOn 配置

static NSString * const kVTTopOnAppID  = @"h6a8d186037102";
static NSString * const kVTTopOnAppKey = @"a02e48bec289b744f0c5b99e08a07eaf3";

static NSString * const kVTBannerPID      = @"n6a8d187956cec";
static NSString * const kVTInterstitialPID = @"n6a8d187a93378";
static NSString * const kVTRewardedPID     = @"n6a8d187b637c7";

static const CGFloat kVTBannerWidth  = 320.0;
static const CGFloat kVTBannerHeight = 50.0;
static const NSInteger kVTMaxAttempt = 8;

@interface VTAdProxy () <ATAdLoadingDelegate, ATBannerDelegate, ATInterstitialDelegate, ATRewardedVideoDelegate>
@end

@implementation VTAdProxy

#pragma mark - 状态

static UIView *vt_overlayHost;
static UIView *vt_bannerHolder;
static ATBannerView *vt_bannerView;

static NSInteger vt_bnrAttempt = 0;
static NSInteger vt_interAttempt = 0;
static NSInteger vt_rwdAttempt = 0;

static BOOL vt_bnrFetching = NO;
static BOOL vt_interFetching = NO;
static BOOL vt_interShowing = NO;
static BOOL vt_rwdFetching = NO;
static BOOL vt_rwdShowing = NO;
static BOOL vt_rwdEarned = NO;
static BOOL vt_sdkReady = NO;

static void (^vt_rwdBlock)(BOOL) = nil;
static NSDictionary *vt_gdprConsent;

static NSMutableString *vt_sessionLog;
static NSDate *vt_sessionStart;
static NSDateFormatter *vt_logFormatter;

#pragma mark - 会话日志

+ (NSString *)vt_buildLabel {
#if TARGET_IPHONE_SIMULATOR
    return @"Simulator";
#elif DEBUG
    return @"Debug-Device";
#else
    return @"Release-Device";
#endif
}

+ (NSString *)vt_describeObject:(id)obj {
    if (!obj || obj == [NSNull null]) { return @"nil"; }
    if ([obj isKindOfClass:[NSDictionary class]] || [obj isKindOfClass:[NSArray class]]) {
        NSError *jsonErr = nil;
        NSData *data = [NSJSONSerialization dataWithJSONObject:obj options:0 error:&jsonErr];
        if (data) {
            return [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] ?: [obj description];
        }
    }
    return [obj description] ?: @"?";
}

+ (NSString *)vt_describeError:(NSError *)error {
    if (!error) { return @"error=nil"; }
    NSMutableString *s = [NSMutableString string];
    [s appendFormat:@"domain=%@ | code=%ld", error.domain ?: @"?", (long)error.code];
    if (error.localizedDescription.length) {
        [s appendFormat:@" | desc=%@", error.localizedDescription];
    }
    if (error.localizedFailureReason.length) {
        [s appendFormat:@" | reason=%@", error.localizedFailureReason];
    }
    if (error.localizedRecoverySuggestion.length) {
        [s appendFormat:@" | suggest=%@", error.localizedRecoverySuggestion];
    }
    NSDictionary *info = error.userInfo;
    if (info.count) {
        // 去掉超大/无用字段，保留诊断关键
        NSMutableDictionary *slim = [NSMutableDictionary dictionary];
        [info enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
            if ([key isEqual:NSUnderlyingErrorKey] && [obj isKindOfClass:[NSError class]]) {
                slim[key] = [self vt_describeError:(NSError *)obj];
            } else if (![obj isKindOfClass:[NSData class]]) {
                slim[key] = obj;
            }
        }];
        [s appendFormat:@" | userInfo=%@", [self vt_describeObject:slim]];
    }
    NSError *underlying = error.userInfo[NSUnderlyingErrorKey];
    if ([underlying isKindOfClass:[NSError class]]) {
        [s appendFormat:@" | underlying={%@}", [self vt_describeError:underlying]];
    }
    return s;
}

+ (NSString *)vt_describeExtra:(NSDictionary *)extra {
    if (!extra.count) { return @"{}"; }
    // 优先提取常见 TopOn 字段，完整字典也附上
    NSArray *keys = @[
        @"network_firm_id", @"network_placement_id", @"adsource_id", @"adsource_price",
        @"adsource_bid_type", @"ad_source_type", @"adunit_id", @"req_id",
        @"currency", @"ecpm", @"publisher_revenue", @"precision", @"network_name",
        @"scenario_id", @"abtest_id", @"s_id"
    ];
    NSMutableArray *parts = [NSMutableArray array];
    for (NSString *k in keys) {
        id v = extra[k];
        if (v) { [parts addObject:[NSString stringWithFormat:@"%@=%@", k, v]]; }
    }
    NSString *highlight = parts.count ? [parts componentsJoinedByString:@", "] : @"";
    NSString *full = [self vt_describeObject:extra];
    if (highlight.length) {
        return [NSString stringWithFormat:@"{%@} full=%@", highlight, full];
    }
    return full;
}

+ (NSString *)vt_placementTag:(NSString *)placementID {
    if ([placementID isEqualToString:kVTBannerPID]) return @"横幅";
    if ([placementID isEqualToString:kVTInterstitialPID]) return @"插页";
    if ([placementID isEqualToString:kVTRewardedPID]) return @"激励视频";
    return placementID ?: @"?";
}

+ (void)vt_resetSessionLog {
    vt_sessionStart = [NSDate date];
    vt_sessionLog = [NSMutableString string];
    if (!vt_logFormatter) {
        vt_logFormatter = [[NSDateFormatter alloc] init];
        vt_logFormatter.locale = [NSLocale localeWithLocaleIdentifier:@"en_US_POSIX"];
        vt_logFormatter.timeZone = [NSTimeZone localTimeZone];
        vt_logFormatter.dateFormat = @"HH:mm:ss.SSS";
    }
    NSString *ver = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"] ?: @"?";
    NSString *build = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"] ?: @"?";
    NSString *bid = [[NSBundle mainBundle] bundleIdentifier] ?: @"?";
    NSString *att = @"N/A";
    if (@available(iOS 14, *)) {
        att = [self vt_attLabel:[ATTrackingManager trackingAuthorizationStatus]];
    }
    [vt_sessionLog appendFormat:@"===== Ad Session Start %@ =====\n", vt_sessionStart];
    [vt_sessionLog appendFormat:@"App: %@ %@ (%@)\n", bid, ver, build];
    [vt_sessionLog appendFormat:@"iOS: %@ | Model: %@ | Env: %@\n",
     UIDevice.currentDevice.systemVersion,
     UIDevice.currentDevice.model,
     [self vt_buildLabel]];
    [vt_sessionLog appendFormat:@"ATT: %@ | FacebookATE: follow ATT\n", att];
    [vt_sessionLog appendFormat:@"TopOn AppID: %@\n", kVTTopOnAppID];
    [vt_sessionLog appendFormat:@"TopOn AppKey: %@…%@\n",
     [kVTTopOnAppKey substringToIndex:MIN(6, kVTTopOnAppKey.length)],
     [kVTTopOnAppKey substringFromIndex:MAX((NSInteger)kVTTopOnAppKey.length - 4, 0)]];
    [vt_sessionLog appendFormat:@"Placement Banner: %@\n", kVTBannerPID];
    [vt_sessionLog appendFormat:@"Placement Interstitial: %@\n", kVTInterstitialPID];
    [vt_sessionLog appendFormat:@"Placement Rewarded: %@\n", kVTRewardedPID];
    [vt_sessionLog appendString:@"---- Events ----\n"];
}

+ (void)vt_appendSessionLog:(NSString *)line {
    if (!line.length) { return; }
    if (!vt_sessionLog) { [self vt_resetSessionLog]; }
    NSString *ts = [vt_logFormatter stringFromDate:[NSDate date]] ?: @"";
    @synchronized (self) {
        // 防止极端情况下日志无限膨胀（约保留最近 ~400KB）
        if (vt_sessionLog.length > 400000) {
            NSString *tail = [vt_sessionLog substringFromIndex:vt_sessionLog.length - 300000];
            vt_sessionLog = [[NSMutableString alloc] initWithFormat:@"…(truncated earlier logs)…\n%@", tail];
        }
        [vt_sessionLog appendFormat:@"[%@] %@\n", ts, line];
    }
}

+ (NSString *)vt_sessionLogText {
    if (!vt_sessionLog) { return @"(No details yet)"; }
    BOOL bReady = [[ATAdManager sharedManager] bannerAdReadyForPlacementID:kVTBannerPID];
    BOOL iReady = [[ATAdManager sharedManager] interstitialReadyForPlacementID:kVTInterstitialPID];
    BOOL rReady = [[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:kVTRewardedPID];
    NSMutableString *out;
    @synchronized (self) {
        out = [vt_sessionLog mutableCopy];
    }
    [out appendString:@"---- Snapshot at copy ----\n"];
    [out appendFormat:@"Ready Banner=%@ Interstitial=%@ Rewarded=%@\n",
     bReady ? @"YES" : @"NO", iReady ? @"YES" : @"NO", rReady ? @"YES" : @"NO"];
    [out appendFormat:@"Fetching Banner=%@ Interstitial=%@ Rewarded=%@\n",
     vt_bnrFetching ? @"YES" : @"NO",
     vt_interFetching ? @"YES" : @"NO",
     vt_rwdFetching ? @"YES" : @"NO"];
    [out appendFormat:@"RetryCount Banner=%ld Interstitial=%ld Rewarded=%ld\n",
     (long)vt_bnrAttempt, (long)vt_interAttempt, (long)vt_rwdAttempt];
    [out appendFormat:@"Showing Interstitial=%@ Rewarded=%@ | SDKReady=%@\n",
     vt_interShowing ? @"YES" : @"NO",
     vt_rwdShowing ? @"YES" : @"NO",
     vt_sdkReady ? @"YES" : @"NO"];
    if (@available(iOS 14, *)) {
        [out appendFormat:@"ATT now: %@\n", [self vt_attLabel:[ATTrackingManager trackingAuthorizationStatus]]];
    }
    [out appendString:@"===== End =====\n"];
    return out;
}

static void VTAdLog(NSString *format, ...) NS_FORMAT_FUNCTION(1, 2);
static void VTAdLog(NSString *format, ...) {
    va_list args;
    va_start(args, format);
    NSString *msg = [[NSString alloc] initWithFormat:format arguments:args];
    va_end(args);
    NSLog(@"%@", msg);
    [VTAdProxy vt_appendSessionLog:msg];
}

#pragma mark - 单例 / 启动

+ (instancetype)vt_shared {
    static VTAdProxy *shared = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        shared = [[self alloc] init];
    });
    return shared;
}

+ (void)vt_applyConsent:(NSDictionary * _Nullable)consentDictionary {
    vt_gdprConsent = consentDictionary;
    VTAdLog(@"[TopOn广告] 已更新同意配置: %@", consentDictionary ?: @"nil");
}

+ (void)vt_launch {
    [self vt_resetSessionLog];
    VTAdLog(@"[广告规则] ====== 广告系统点火初始化（TopOn 多广告源中介） ======");
    vt_bnrAttempt = 0;
    vt_interAttempt = 0;
    vt_rwdAttempt = 0;
    vt_bnrFetching = NO;
    vt_interFetching = NO;
    vt_interShowing = NO;
    vt_rwdFetching = NO;
    vt_rwdShowing = NO;
    vt_rwdEarned = NO;
    vt_rwdBlock = nil;
    vt_sdkReady = NO;

    VTAdLog(@"[广告规则] 开始初始化 TopOn SDK 并预加载横幅/插页/激励视频（无冷启动插页限制）");
    [self vt_bootup];
}

+ (void)vt_bootup {
#if DEBUG
    [ATAPI setLogEnabled:YES];
    VTAdLog(@"[TopOn广告] Debug 日志已开启");
#endif

    if (@available(iOS 14, *)) {
        ATTrackingManagerAuthorizationStatus status = [ATTrackingManager trackingAuthorizationStatus];
        VTAdLog(@"[TopOn广告] 当前 ATT 状态: %ld (%@)", (long)status, [self vt_attLabel:status]);

        if (status == ATTrackingManagerAuthorizationStatusNotDetermined) {
            VTAdLog(@"[TopOn广告] ATT 未确定，延时 2 秒后请求授权");
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                [ATTrackingManager requestTrackingAuthorizationWithCompletionHandler:^(ATTrackingManagerAuthorizationStatus result) {
                    VTAdLog(@"[TopOn广告] ATT 授权结果: %ld (%@)", (long)result, [self vt_attLabel:result]);
                    [self vt_applyFacebookATE:result];
                    dispatch_async(dispatch_get_main_queue(), ^{
                        [self vt_initSDK];
                    });
                }];
            });
        } else {
            VTAdLog(@"[TopOn广告] ATT 已确定（%@），直接初始化 SDK", [self vt_attLabel:status]);
            [self vt_applyFacebookATE:status];
            [self vt_initSDK];
        }
    } else {
        VTAdLog(@"[TopOn广告] iOS 14 以下，直接初始化 SDK");
        [self vt_initSDK];
    }
}

+ (void)vt_applyFacebookATE:(ATTrackingManagerAuthorizationStatus)status API_AVAILABLE(ios(14)) {
    BOOL enabled = (status == ATTrackingManagerAuthorizationStatusAuthorized);
    [FBAdSettings setAdvertiserTrackingEnabled:enabled];
    VTAdLog(@"[Facebook广告] 已设置 AdvertiserTrackingEnabled=%@", enabled ? @"YES" : @"NO");
}

+ (void)vt_initSDK {
    VTAdLog(@"[TopOn广告] 开始初始化 SDK，AppID=%@ AppKey=%@", kVTTopOnAppID, kVTTopOnAppKey);
    NSError *error = nil;
    BOOL ok = [[ATAPI sharedInstance] startWithAppID:kVTTopOnAppID appKey:kVTTopOnAppKey error:&error];
    if (!ok || error) {
        VTAdLog(@"[TopOn广告] SDK 初始化失败 ok=%@ | %@，10 秒后重试",
                ok ? @"YES" : @"NO", [self vt_describeError:error]);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(10.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            VTAdLog(@"[TopOn广告] 重试 SDK 初始化");
            [self vt_initSDK];
        });
        return;
    }

    vt_sdkReady = YES;
    VTAdLog(@"[TopOn广告] SDK 初始化成功 Env=%@", [self vt_buildLabel]);
    [self vt_buildHolder];

    NSTimeInterval delay = 3.0;
    if (@available(iOS 14, *)) {
        ATTrackingManagerAuthorizationStatus status = [ATTrackingManager trackingAuthorizationStatus];
        if (status == ATTrackingManagerAuthorizationStatusDenied) {
            delay = 5.0;
            VTAdLog(@"[TopOn广告] 用户拒绝追踪，延迟 %.0f 秒后加载广告（上下文模式）", delay);
        } else if (status == ATTrackingManagerAuthorizationStatusNotDetermined) {
            delay = 4.0;
            VTAdLog(@"[TopOn广告] ATT 未确定，延迟 %.0f 秒后加载广告", delay);
        }
    }

    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        VTAdLog(@"[TopOn广告] 延迟 %.1f 秒后开始预加载全部广告", delay);
        [self vt_verifyThenLoad];
    });
}

#pragma mark - 预加载

+ (void)vt_verifyThenLoad {
    VTAdLog(@"[TopOn广告] 开始异步网络检测");
#if TARGET_IPHONE_SIMULATOR || DEBUG
    VTAdLog(@"[TopOn广告] 模拟器/Debug 跳过网络检测，直接预加载");
    [self vt_reloadAll];
#else
    NSURL *url = [NSURL URLWithString:@"https://captive.apple.com/hotspot-detect.html"];
    NSURLRequest *req = [NSURLRequest requestWithURL:url
                                         cachePolicy:NSURLRequestReloadIgnoringLocalCacheData
                                     timeoutInterval:3.0];
    [[[NSURLSession sharedSession] dataTaskWithRequest:req
                                     completionHandler:^(NSData *d, NSURLResponse *r, NSError *e) {
        dispatch_async(dispatch_get_main_queue(), ^{
            if (e) {
                VTAdLog(@"[TopOn广告] 网络检测失败（%@），3 秒后重试", e.localizedDescription);
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                    [self vt_verifyThenLoad];
                });
            } else {
                VTAdLog(@"[TopOn广告] 网络就绪，开始预加载全部广告");
                [self vt_reloadAll];
            }
        });
    }] resume];
#endif
}

+ (void)vt_reloadAll {
    if (!vt_sdkReady) {
        VTAdLog(@"[TopOn广告] SDK 尚未就绪，跳过预加载");
        return;
    }
    VTAdLog(@"[TopOn广告] 开始预加载：横幅 / 插页 / 激励视频");
    [self vt_fetchBanner];
    [self vt_loadInterstitial];
    [self vt_loadRewarded];
}

+ (void)vt_fetchBanner {
    if (!vt_sdkReady) {
        VTAdLog(@"[横幅广告] SDK 未就绪，无法加载");
        return;
    }
    if (vt_bnrFetching) {
        VTAdLog(@"[横幅广告] 正在加载中，跳过重复请求");
        return;
    }
    vt_bnrFetching = YES;
    VTAdLog(@"[横幅广告] 开始加载 placement=%@ size=%.0fx%.0f retry=%ld",
            kVTBannerPID, kVTBannerWidth, kVTBannerHeight, (long)vt_bnrAttempt);

    NSMutableDictionary *extra = [NSMutableDictionary dictionary];
    [extra setValue:[NSValue valueWithCGSize:CGSizeMake(kVTBannerWidth, kVTBannerHeight)]
             forKey:kATAdLoadingExtraBannerAdSizeKey];
    [[ATAdManager sharedManager] loadADWithPlacementID:kVTBannerPID
                                                 extra:extra
                                              delegate:[self vt_shared]];
}

/// force=YES：show 后立刻预加载下一条，即使缓存里仍有 ready 也继续请求瀑布流
+ (void)vt_loadInterstitial {
    [self vt_loadInterstitialForce:NO];
}

+ (void)vt_loadInterstitialForce:(BOOL)force {
    if (!vt_sdkReady) {
        VTAdLog(@"[插页广告] SDK 未就绪，无法加载");
        return;
    }
    if (vt_interFetching) {
        VTAdLog(@"[插页广告] 正在加载中，跳过重复请求");
        return;
    }
    if (!force && [[ATAdManager sharedManager] interstitialReadyForPlacementID:kVTInterstitialPID]) {
        VTAdLog(@"[插页广告] 已就绪，跳过重复加载");
        return;
    }
    vt_interFetching = YES;
    VTAdLog(@"[插页广告] 开始加载 placement=%@ retry=%ld force=%@",
            kVTInterstitialPID, (long)vt_interAttempt, force ? @"YES" : @"NO");
    [[ATAdManager sharedManager] loadADWithPlacementID:kVTInterstitialPID
                                                 extra:nil
                                              delegate:[self vt_shared]];
}

+ (void)vt_loadRewarded {
    [self vt_loadRewardedForce:NO];
}

+ (void)vt_loadRewardedForce:(BOOL)force {
    if (!vt_sdkReady) {
        VTAdLog(@"[激励视频] SDK 未就绪，无法加载");
        return;
    }
    if (vt_rwdFetching) {
        VTAdLog(@"[激励视频] 正在加载中，跳过重复请求");
        return;
    }
    if (!force && [[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:kVTRewardedPID]) {
        VTAdLog(@"[激励视频] 已就绪，跳过重复加载");
        return;
    }
    vt_rwdFetching = YES;
    VTAdLog(@"[激励视频] 开始加载 placement=%@ retry=%ld force=%@",
            kVTRewardedPID, (long)vt_rwdAttempt, force ? @"YES" : @"NO");
    [[ATAdManager sharedManager] loadADWithPlacementID:kVTRewardedPID
                                                 extra:nil
                                              delegate:[self vt_shared]];
}

/// show 当下立刻预加载下一条，利用播放窗口跑瀑布流
+ (void)vt_prefetchNextInterstitialAfterShow {
    VTAdLog(@"[插页广告] show 后立即预加载下一条（播放期间跑瀑布流）");
    vt_interAttempt = 0;
    [self vt_loadInterstitialForce:YES];
}

+ (void)vt_prefetchNextRewardedAfterShow {
    VTAdLog(@"[激励视频] show 后立即预加载下一条（播放期间跑瀑布流）");
    vt_rwdAttempt = 0;
    [self vt_loadRewardedForce:YES];
}

#pragma mark - 激励视频展示

+ (void)vt_deliverReward:(BOOL)earned {
    void (^cb)(BOOL) = vt_rwdBlock;
    vt_rwdBlock = nil;
    vt_rwdEarned = NO;
    if (cb) {
        dispatch_async(dispatch_get_main_queue(), ^{
            VTAdLog(@"[激励视频] 回调业务层，earned=%@", earned ? @"YES" : @"NO");
            cb(earned);
        });
    }
}

+ (void)vt_startRewarded {
    if (vt_rwdShowing) {
        VTAdLog(@"[激励视频] 跳过展示：当前已有激励视频正在展示");
        [self vt_deliverReward:NO];
        return;
    }

    BOOL ready = [[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:kVTRewardedPID];
    if (!ready) {
        VTAdLog(@"[激励视频] 跳过展示：广告未就绪，触发重新加载");
        [self vt_loadRewarded];
        [self vt_deliverReward:NO];
        return;
    }

    UIViewController *rootVC = [self vt_currentVC];
    if (!rootVC || !rootVC.view.window) {
        VTAdLog(@"[激励视频] 错误：无法获取有效的根视图控制器");
        [self vt_deliverReward:NO];
        return;
    }

    VTAdLog(@"[激励视频] 广告已就绪，即将展示");
    vt_rwdShowing = YES;
    [[ATAdManager sharedManager] showRewardedVideoWithPlacementID:kVTRewardedPID
                                                 inViewController:rootVC
                                                         delegate:[self vt_shared]];
    // 一调用 show 就立刻 load 下一条，播放几十秒内把瀑布流跑完
    [self vt_prefetchNextRewardedAfterShow];
}

+ (void)vt_startRewardedWithHandler:(void (^)(BOOL))completion {
    VTAdLog(@"[激励视频] 设置奖励回调并开始播放");
    vt_rwdEarned = NO;
    vt_rwdBlock = [completion copy];
    [self vt_startRewarded];
}

+ (bool)vt_isRewardedLoaded {
    return [[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:kVTRewardedPID];
}

#pragma mark - 插页展示

+ (void)vt_displayInterstitialPostRestart {
    VTAdLog(@"[广告规则] 关卡重新开始后请求插页（界面应已切换完成）");
    [self vt_displayInterstitial];
}

+ (void)vt_displayInterstitial {
    VTAdLog(@"[广告规则] ====== 插页资格检查开始 ======");

    if (vt_interShowing) {
        VTAdLog(@"[广告规则] 跳过：已有插页正在展示");
        VTAdLog(@"[广告规则] ====== 插页资格检查结束 ======");
        return;
    }

    BOOL ready = [[ATAdManager sharedManager] interstitialReadyForPlacementID:kVTInterstitialPID];
    if (!ready) {
        VTAdLog(@"[广告规则] 跳过：插页未就绪（%@）", vt_interFetching ? @"加载中" : @"需重新加载");
        [self vt_loadInterstitial];
        VTAdLog(@"[广告规则] ====== 插页资格检查结束 ======");
        return;
    }

    UIViewController *rootVC = [self vt_currentVC];
    if (!rootVC || !rootVC.view.window) {
        VTAdLog(@"[广告规则] 无法展示：顶层 VC 无效");
        VTAdLog(@"[广告规则] ====== 插页资格检查结束 ======");
        return;
    }

    VTAdLog(@"[广告规则] 插页已就绪，即将展示（无冷启动时间限制）");
    vt_interShowing = YES;
    [[ATAdManager sharedManager] showInterstitialWithPlacementID:kVTInterstitialPID
                                                inViewController:rootVC
                                                        delegate:[self vt_shared]];
    // 一调用 show 就立刻 load 下一条，展示期间把瀑布流跑完
    [self vt_prefetchNextInterstitialAfterShow];
    VTAdLog(@"[广告规则] ====== 插页资格检查结束 ======");
}

+ (void)vt_pushInterstitial {
    if (vt_interShowing) {
        VTAdLog(@"[插页广告][强制] 跳过：已有插页正在展示");
        return;
    }

    BOOL ready = [[ATAdManager sharedManager] interstitialReadyForPlacementID:kVTInterstitialPID];
    if (!ready) {
        VTAdLog(@"[插页广告][强制] 未就绪，触发加载并跳过本次展示");
        [self vt_loadInterstitial];
        return;
    }

    UIViewController *rootVC = [self vt_currentVC];
    if (!rootVC || !rootVC.view.window) {
        VTAdLog(@"[插页广告][强制] 错误：无法获取有效根视图控制器");
        return;
    }

    VTAdLog(@"[插页广告][强制] 广告已就绪，即将展示");
    vt_interShowing = YES;
    [[ATAdManager sharedManager] showInterstitialWithPlacementID:kVTInterstitialPID
                                                inViewController:rootVC
                                                        delegate:[self vt_shared]];
    [self vt_prefetchNextInterstitialAfterShow];
}

#pragma mark - Banner 容器

+ (void)vt_attachBannerViewIfNeeded {
    if (!vt_sdkReady) { return; }
    if (![[ATAdManager sharedManager] bannerAdReadyForPlacementID:kVTBannerPID]) {
        VTAdLog(@"[横幅广告] 尚未就绪，无法取出 BannerView");
        return;
    }

    ATBannerView *banner = [[ATAdManager sharedManager] retrieveBannerViewForPlacementID:kVTBannerPID];
    if (!banner) {
        VTAdLog(@"[横幅广告] retrieveBannerView 返回 nil");
        return;
    }

    banner.delegate = [self vt_shared];
    banner.presentingViewController = [self vt_currentVC];
    vt_bannerView = banner;
    VTAdLog(@"[横幅广告] 已获取 BannerView，尺寸=%.0fx%.0f", banner.frame.size.width, banner.frame.size.height);

    [self vt_buildHolder];
    if (vt_bannerHolder) {
        if (vt_bannerView.superview != vt_bannerHolder) {
            [vt_bannerView removeFromSuperview];
            [vt_bannerHolder addSubview:vt_bannerView];
        }
        [self vt_centerBanner];
        if (vt_overlayHost == nil) {
            vt_bannerHolder.hidden = YES;
            VTAdLog(@"[横幅广告] 非弹窗场景，横幅保持隐藏等待主动显示");
        }
    }
}

+ (void)vt_showBanner {
    VTAdLog(@"[横幅广告] vt_showBanner 被调用");
    dispatch_async(dispatch_get_main_queue(), ^{
        UIViewController *topVC = [self vt_currentVC];
        if (!topVC) {
            VTAdLog(@"[横幅广告] 无法获取顶层视图控制器");
            return;
        }

        if (!vt_bannerHolder || vt_bannerHolder.superview != topVC.view) {
            if (vt_bannerHolder) { [vt_bannerHolder removeFromSuperview]; }
            vt_bannerHolder = [[UIView alloc] init];
            vt_bannerHolder.translatesAutoresizingMaskIntoConstraints = NO;
            vt_bannerHolder.backgroundColor = [UIColor clearColor];
            vt_bannerHolder.clipsToBounds = YES;
            [topVC.view addSubview:vt_bannerHolder];
            [self vt_setupConstraints];
        }

        if (!vt_bannerView) {
            [self vt_attachBannerViewIfNeeded];
        }

        if (vt_bannerView) {
            if (vt_bannerView.superview != vt_bannerHolder) {
                [vt_bannerView removeFromSuperview];
                [vt_bannerHolder addSubview:vt_bannerView];
            }
            [self vt_centerBanner];
        } else {
            VTAdLog(@"[横幅广告] BannerView 为空，触发加载");
            [self vt_fetchBanner];
        }

        if (vt_bannerHolder) {
            vt_bannerHolder.hidden = NO;
            [topVC.view bringSubviewToFront:vt_bannerHolder];
            VTAdLog(@"[横幅广告] 容器已显示并置顶");
        }
    });
}

+ (void)vt_concealBanner {
    VTAdLog(@"[横幅广告] vt_concealBanner 被调用");
    dispatch_async(dispatch_get_main_queue(), ^{
        if (vt_bannerHolder) {
            vt_bannerHolder.hidden = YES;
            VTAdLog(@"[横幅广告] 容器已隐藏");
        }
    });
}

+ (void)vt_embedBannerIn:(UIView *)hostView {
    if (!hostView) {
        VTAdLog(@"[横幅广告] 嵌入失败：hostView 为 nil");
        return;
    }
    dispatch_async(dispatch_get_main_queue(), ^{
        vt_overlayHost = hostView;
        if (!vt_bannerView) {
            [self vt_attachBannerViewIfNeeded];
        }
        if (!vt_bannerView) {
            VTAdLog(@"[横幅广告] 嵌入时 BannerView 未就绪，先加载");
            [self vt_fetchBanner];
            return;
        }

        [vt_bannerHolder removeFromSuperview];
        [NSLayoutConstraint deactivateConstraints:vt_bannerHolder.constraints];

        if (!vt_bannerHolder) {
            vt_bannerHolder = [[UIView alloc] init];
        }
        vt_bannerHolder.translatesAutoresizingMaskIntoConstraints = NO;
        vt_bannerHolder.backgroundColor = [UIColor clearColor];
        vt_bannerHolder.clipsToBounds = YES;
        vt_bannerHolder.hidden = NO;
        [hostView addSubview:vt_bannerHolder];

        if (vt_bannerView.superview != vt_bannerHolder) {
            [vt_bannerView removeFromSuperview];
            [vt_bannerHolder addSubview:vt_bannerView];
        }
        vt_bannerView.translatesAutoresizingMaskIntoConstraints = NO;
        [NSLayoutConstraint deactivateConstraints:vt_bannerView.constraints];

        [NSLayoutConstraint activateConstraints:@[
            [vt_bannerHolder.leadingAnchor constraintEqualToAnchor:hostView.leadingAnchor],
            [vt_bannerHolder.trailingAnchor constraintEqualToAnchor:hostView.trailingAnchor],
            [vt_bannerHolder.bottomAnchor constraintEqualToAnchor:hostView.safeAreaLayoutGuide.bottomAnchor],
            [vt_bannerHolder.heightAnchor constraintEqualToConstant:kVTBannerHeight],
        ]];
        [NSLayoutConstraint activateConstraints:@[
            [vt_bannerView.leadingAnchor constraintEqualToAnchor:vt_bannerHolder.leadingAnchor],
            [vt_bannerView.trailingAnchor constraintEqualToAnchor:vt_bannerHolder.trailingAnchor],
            [vt_bannerView.topAnchor constraintEqualToAnchor:vt_bannerHolder.topAnchor],
            [vt_bannerView.bottomAnchor constraintEqualToAnchor:vt_bannerHolder.bottomAnchor],
        ]];
        [hostView bringSubviewToFront:vt_bannerHolder];
        VTAdLog(@"[横幅广告] 已嵌入对话框遮罩层底部（与弹窗同层级）");
    });
}

+ (void)vt_dismissOverlay {
    dispatch_async(dispatch_get_main_queue(), ^{
        vt_overlayHost = nil;
        if (vt_bannerHolder) {
            [vt_bannerHolder removeFromSuperview];
            vt_bannerHolder.hidden = YES;
        }
        if (vt_bannerView) {
            vt_bannerView.translatesAutoresizingMaskIntoConstraints = YES;
        }
        [self vt_buildHolder];
        VTAdLog(@"[横幅广告] 弹窗遮罩已关闭，横幅容器恢复隐藏");
    });
}

+ (void)vt_raiseBanner {
    VTAdLog(@"[横幅广告] vt_raiseBanner 被调用");
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!vt_bannerHolder) { [self vt_buildHolder]; }
        if (vt_bannerHolder) {
            vt_bannerHolder.hidden = NO;
            [vt_bannerHolder.superview bringSubviewToFront:vt_bannerHolder];
            VTAdLog(@"[横幅广告] 已安全显示");
        }
    });
}

+ (void)vt_setupConstraints {
    UIViewController *rootVC = [self vt_currentVC];
    if (!rootVC || !vt_bannerHolder) {
        VTAdLog(@"[横幅广告] 设置约束失败：rootVC 或容器为 nil");
        return;
    }
    [vt_bannerHolder removeFromSuperview];
    [NSLayoutConstraint deactivateConstraints:vt_bannerHolder.constraints];
    [rootVC.view addSubview:vt_bannerHolder];

    [NSLayoutConstraint activateConstraints:@[
        [vt_bannerHolder.heightAnchor constraintEqualToConstant:kVTBannerHeight],
        [vt_bannerHolder.widthAnchor constraintEqualToConstant:kVTBannerWidth],
        [vt_bannerHolder.centerXAnchor constraintEqualToAnchor:rootVC.view.centerXAnchor],
        [vt_bannerHolder.bottomAnchor constraintEqualToAnchor:rootVC.view.safeAreaLayoutGuide.bottomAnchor],
    ]];
    VTAdLog(@"[横幅广告] 约束设置完成：%.0fx%.0f", kVTBannerWidth, kVTBannerHeight);
}

+ (void)vt_centerBanner {
    dispatch_async(dispatch_get_main_queue(), ^{
        if (!vt_bannerHolder || !vt_bannerView) { return; }
        [vt_bannerHolder layoutIfNeeded];

        CGFloat cw = vt_bannerHolder.frame.size.width ?: kVTBannerWidth;
        CGFloat ch = vt_bannerHolder.frame.size.height ?: kVTBannerHeight;
        CGFloat aw = vt_bannerView.frame.size.width ?: kVTBannerWidth;
        CGFloat ah = vt_bannerView.frame.size.height ?: kVTBannerHeight;
        CGFloat x = (cw - aw) / 2.0;
        CGFloat y = (ch - ah) / 2.0;
        vt_bannerView.frame = CGRectMake(x, y, aw, ah);
        VTAdLog(@"[横幅广告] 居中完成，位置=(%.0f, %.0f) 尺寸=%.0fx%.0f", x, y, aw, ah);
    });
}

+ (void)vt_buildHolder {
    if (vt_bannerHolder && vt_bannerHolder.superview) {
        if (vt_bannerView && vt_bannerView.superview != vt_bannerHolder) {
            [vt_bannerView removeFromSuperview];
            [vt_bannerHolder addSubview:vt_bannerView];
            [self vt_centerBanner];
        }
        return;
    }
    if (vt_bannerHolder && !vt_bannerHolder.superview) {
        UIViewController *rootVC = [self vt_currentVC];
        if (!rootVC) { return; }
        vt_bannerHolder.hidden = YES;
        vt_bannerHolder.translatesAutoresizingMaskIntoConstraints = NO;
        [rootVC.view addSubview:vt_bannerHolder];
        [self vt_setupConstraints];
        if (vt_bannerView && vt_bannerView.superview != vt_bannerHolder) {
            [vt_bannerView removeFromSuperview];
            [vt_bannerHolder addSubview:vt_bannerView];
            [self vt_centerBanner];
        }
        return;
    }

    UIViewController *rootVC = [self vt_currentVC];
    if (!rootVC) {
        VTAdLog(@"[横幅广告] ensure: rootVC 尚未就绪");
        return;
    }
    vt_bannerHolder = [[UIView alloc] init];
    vt_bannerHolder.translatesAutoresizingMaskIntoConstraints = NO;
    vt_bannerHolder.backgroundColor = [UIColor clearColor];
    vt_bannerHolder.clipsToBounds = YES;
    vt_bannerHolder.hidden = YES;
    [rootVC.view addSubview:vt_bannerHolder];
    [self vt_setupConstraints];
    if (vt_bannerView) {
        [vt_bannerHolder addSubview:vt_bannerView];
        [self vt_centerBanner];
    }
    VTAdLog(@"[横幅广告] 容器已创建（默认隐藏）");
}

+ (void)vt_dumpBannerInfo {
    VTAdLog(@"[横幅广告] === 状态调试 ===");
    VTAdLog(@"[横幅广告] BannerView=%@ Holder=%@ OverlayHost=%@",
          vt_bannerView ? @"有" : @"无",
          vt_bannerHolder ? @"有" : @"无",
          vt_overlayHost ? @"有" : @"无");
    VTAdLog(@"[横幅广告] 就绪=%@ 加载中=%@",
          [[ATAdManager sharedManager] bannerAdReadyForPlacementID:kVTBannerPID] ? @"是" : @"否",
          vt_bnrFetching ? @"是" : @"否");
}

#pragma mark - Helpers

+ (UIViewController *)vt_currentVC {
    __block UIViewController *rootVC = nil;
    NSSet *scenes = [UIApplication sharedApplication].connectedScenes;
    [scenes enumerateObjectsUsingBlock:^(__kindof UIScene *scene, BOOL *stop) {
        if (scene.activationState == UISceneActivationStateForegroundActive &&
            [scene isKindOfClass:[UIWindowScene class]]) {
            for (UIWindow *window in ((UIWindowScene *)scene).windows) {
                if (window.isKeyWindow) {
                    rootVC = window.rootViewController;
                    *stop = YES;
                    break;
                }
            }
        }
    }];
    if (!rootVC) {
        for (UIScene *scene in scenes) {
            if ([scene isKindOfClass:[UIWindowScene class]]) {
                rootVC = ((UIWindowScene *)scene).windows.firstObject.rootViewController;
                if (rootVC) { break; }
            }
        }
    }
    if (rootVC) {
        UIViewController *top = rootVC;
        while (top.presentedViewController) {
            top = top.presentedViewController;
        }
        return top;
    }
    return rootVC;
}

+ (NSString *)vt_attLabel:(ATTrackingManagerAuthorizationStatus)status API_AVAILABLE(ios(14)) {
    switch (status) {
        case ATTrackingManagerAuthorizationStatusNotDetermined: return @"未确定";
        case ATTrackingManagerAuthorizationStatusRestricted: return @"受限";
        case ATTrackingManagerAuthorizationStatusDenied: return @"拒绝";
        case ATTrackingManagerAuthorizationStatusAuthorized: return @"授权";
        default: return @"未知";
    }
}

+ (void)vt_scheduleRetryForPlacement:(NSString *)placementID {
    NSInteger *retryIdx = NULL;
    NSString *tag = @"[TopOn广告]";
    if ([placementID isEqualToString:kVTBannerPID]) {
        retryIdx = &vt_bnrAttempt;
        tag = @"[横幅广告]";
    } else if ([placementID isEqualToString:kVTInterstitialPID]) {
        retryIdx = &vt_interAttempt;
        tag = @"[插页广告]";
    } else if ([placementID isEqualToString:kVTRewardedPID]) {
        retryIdx = &vt_rwdAttempt;
        tag = @"[激励视频]";
    }
    if (!retryIdx) { return; }

    if (*retryIdx >= kVTMaxAttempt) {
        VTAdLog(@"%@ 已达最大重试次数(%ld)，5 分钟后兜底重试", tag, (long)kVTMaxAttempt);
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(300.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            VTAdLog(@"%@ 兜底重试：重置计数并重新加载", tag);
            *retryIdx = 0;
            if ([placementID isEqualToString:kVTBannerPID]) {
                [self vt_fetchBanner];
            } else if ([placementID isEqualToString:kVTInterstitialPID]) {
                [self vt_loadInterstitial];
            } else {
                [self vt_loadRewarded];
            }
        });
        return;
    }

    // TopOn 失败后有加载频控（1019），最短间隔 60 秒，避免过快重试被拒
    NSTimeInterval delay = 60.0 * MIN(*retryIdx + 1, 3);
    (*retryIdx)++;
    VTAdLog(@"%@ 将在 %.0f 秒后重试（第 %ld 次）", tag, delay, (long)*retryIdx);
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delay * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        VTAdLog(@"%@ 开始重试加载", tag);
        if ([placementID isEqualToString:kVTBannerPID]) {
            [self vt_fetchBanner];
        } else if ([placementID isEqualToString:kVTInterstitialPID]) {
            [self vt_loadInterstitial];
        } else {
            [self vt_loadRewarded];
        }
    });
}

#pragma mark - ATAdLoadingDelegate

- (void)didFinishLoadingADWithPlacementID:(NSString *)placementID {
    NSString *tag = [VTAdProxy vt_placementTag:placementID];
    VTAdLog(@"[%@广告] 加载成功 placement=%@", tag, placementID);
    if ([placementID isEqualToString:kVTBannerPID]) {
        vt_bnrFetching = NO;
        vt_bnrAttempt = 0;
        [VTAdProxy vt_attachBannerViewIfNeeded];
        if (vt_overlayHost) {
            [VTAdProxy vt_embedBannerIn:vt_overlayHost];
        }
    } else if ([placementID isEqualToString:kVTInterstitialPID]) {
        vt_interFetching = NO;
        vt_interAttempt = 0;
    } else if ([placementID isEqualToString:kVTRewardedPID]) {
        vt_rwdFetching = NO;
        vt_rwdAttempt = 0;
    }
}

- (void)didFailToLoadADWithPlacementID:(NSString *)placementID error:(NSError *)error {
    NSString *tag = [VTAdProxy vt_placementTag:placementID];
    VTAdLog(@"[%@广告] 加载失败 placement=%@ | %@", tag, placementID, [VTAdProxy vt_describeError:error]);
    if ([placementID isEqualToString:kVTBannerPID]) {
        vt_bnrFetching = NO;
    } else if ([placementID isEqualToString:kVTInterstitialPID]) {
        vt_interFetching = NO;
    } else if ([placementID isEqualToString:kVTRewardedPID]) {
        vt_rwdFetching = NO;
    }
    [VTAdProxy vt_scheduleRetryForPlacement:placementID];
}

- (void)didStartLoadingADSourceWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[广告源] 开始加载 %@ | extra=%@", [VTAdProxy vt_placementTag:placementID], [VTAdProxy vt_describeExtra:extra]);
}

- (void)didFinishLoadingADSourceWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[广告源] 加载成功 %@ | extra=%@", [VTAdProxy vt_placementTag:placementID], [VTAdProxy vt_describeExtra:extra]);
}

- (void)didFailToLoadADSourceWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra error:(NSError *)error {
    VTAdLog(@"[广告源] 加载失败 %@ | %@ | extra=%@",
            [VTAdProxy vt_placementTag:placementID],
            [VTAdProxy vt_describeError:error],
            [VTAdProxy vt_describeExtra:extra]);
}

- (void)didStartBiddingADSourceWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[竞价] 开始 %@ | extra=%@", [VTAdProxy vt_placementTag:placementID], [VTAdProxy vt_describeExtra:extra]);
}

- (void)didFinishBiddingADSourceWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[竞价] 成功 %@ | extra=%@", [VTAdProxy vt_placementTag:placementID], [VTAdProxy vt_describeExtra:extra]);
}

- (void)didFailBiddingADSourceWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra error:(NSError *)error {
    VTAdLog(@"[竞价] 失败 %@ | %@ | extra=%@",
            [VTAdProxy vt_placementTag:placementID],
            [VTAdProxy vt_describeError:error],
            [VTAdProxy vt_describeExtra:extra]);
}

- (void)didRevenueForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[收益] %@ | extra=%@", [VTAdProxy vt_placementTag:placementID], [VTAdProxy vt_describeExtra:extra]);
}

#pragma mark - ATBannerDelegate

- (void)bannerView:(ATBannerView *)bannerView didShowAdWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[横幅广告] 已展示 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)bannerView:(ATBannerView *)bannerView didClickWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[横幅广告] 用户点击 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)bannerView:(ATBannerView *)bannerView didTapCloseButtonWithPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[横幅广告] 用户关闭 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)bannerView:(ATBannerView *)bannerView didAutoRefreshWithPlacement:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[横幅广告] 自动刷新成功 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)bannerView:(ATBannerView *)bannerView failedToAutoRefreshWithPlacementID:(NSString *)placementID error:(NSError *)error {
    VTAdLog(@"[横幅广告] 自动刷新失败 placement=%@ | %@", placementID, [VTAdProxy vt_describeError:error]);
}

#pragma mark - ATInterstitialDelegate

- (void)interstitialDidShowForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[插页广告] 已展示 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
    vt_interShowing = YES;
    // 兜底：若 show 瞬间预加载未触发成功，这里再补一次
    [VTAdProxy vt_prefetchNextInterstitialAfterShow];
}

- (void)interstitialDidClickForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[插页广告] 用户点击 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)interstitialDidCloseForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[插页广告] 用户关闭 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
    vt_interShowing = NO;
    vt_interAttempt = 0;
    // show 时已预加载；关闭时若仍未就绪则再补加载
    if (![[ATAdManager sharedManager] interstitialReadyForPlacementID:kVTInterstitialPID]) {
        VTAdLog(@"[插页广告] 关闭后下一条仍未就绪，补一次加载");
        [VTAdProxy vt_loadInterstitialForce:YES];
    } else {
        VTAdLog(@"[插页广告] 关闭时下一条已就绪，可直接再展示");
    }
}

- (void)interstitialFailedToShowForPlacementID:(NSString *)placementID error:(NSError *)error extra:(NSDictionary *)extra {
    VTAdLog(@"[插页广告] 展示失败 placement=%@ | %@ | extra=%@",
            placementID, [VTAdProxy vt_describeError:error], [VTAdProxy vt_describeExtra:extra]);
    vt_interShowing = NO;
    [VTAdProxy vt_loadInterstitialForce:YES];
}

#pragma mark - ATRewardedVideoDelegate

- (void)rewardedVideoDidStartPlayingForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[激励视频] 开始播放 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
    vt_rwdShowing = YES;
    // 兜底：播放开始时确保下一条瀑布流已在跑
    [VTAdProxy vt_prefetchNextRewardedAfterShow];
}

- (void)rewardedVideoDidEndPlayingForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[激励视频] 播放结束 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)rewardedVideoDidClickForPlacementID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[激励视频] 用户点击 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
}

- (void)rewardedVideoDidRewardSuccessForPlacemenID:(NSString *)placementID extra:(NSDictionary *)extra {
    VTAdLog(@"[激励视频] 奖励发放成功 placement=%@ | extra=%@", placementID, [VTAdProxy vt_describeExtra:extra]);
    vt_rwdEarned = YES;
    [[NSNotificationCenter defaultCenter] postNotificationName:@"VTRewardGranted" object:nil userInfo:nil];
}

- (void)rewardedVideoDidCloseForPlacementID:(NSString *)placementID rewarded:(BOOL)rewarded extra:(NSDictionary *)extra {
    BOOL earned = rewarded || vt_rwdEarned;
    VTAdLog(@"[激励视频] 关闭 placement=%@ rewarded=%@ earned=%@ | extra=%@",
            placementID, rewarded ? @"YES" : @"NO", earned ? @"YES" : @"NO", [VTAdProxy vt_describeExtra:extra]);
    vt_rwdShowing = NO;
    vt_rwdAttempt = 0;
    [VTAdProxy vt_deliverReward:earned];
    if (![[ATAdManager sharedManager] rewardedVideoReadyForPlacementID:kVTRewardedPID]) {
        VTAdLog(@"[激励视频] 关闭后下一条仍未就绪，补一次加载");
        [VTAdProxy vt_loadRewardedForce:YES];
    } else {
        VTAdLog(@"[激励视频] 关闭时下一条已就绪，可直接再播放");
    }
}

- (void)rewardedVideoDidFailToPlayForPlacementID:(NSString *)placementID error:(NSError *)error extra:(NSDictionary *)extra {
    VTAdLog(@"[激励视频] 播放失败 placement=%@ | %@ | extra=%@",
            placementID, [VTAdProxy vt_describeError:error], [VTAdProxy vt_describeExtra:extra]);
    vt_rwdShowing = NO;
    [VTAdProxy vt_deliverReward:NO];
    [VTAdProxy vt_loadRewardedForce:YES];
}

@end
