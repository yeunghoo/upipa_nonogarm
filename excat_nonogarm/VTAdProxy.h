//
//  VTAdProxy.h
//  excat_nonogarm
//
//  TopOn 中介广告代理（ADX / Meta / Vungle / Bigo / InMobi / Chartboost / DT）
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VTAdProxy : NSObject

+ (instancetype)vt_shared;
+ (void)vt_launch;
+ (void)vt_applyConsent:(NSDictionary * _Nullable)consentDictionary;

+ (void)vt_showBanner;
+ (void)vt_raiseBanner;
+ (void)vt_buildHolder;
+ (void)vt_centerBanner;

+ (void)vt_concealBanner;
+ (void)vt_embedBannerIn:(UIView *)hostView;
+ (void)vt_dismissOverlay;
+ (void)vt_displayInterstitial;
+ (void)vt_displayInterstitialPostRestart;
+ (void)vt_pushInterstitial;
+ (void)vt_startRewarded;
+ (void)vt_startRewardedWithHandler:(nullable void(^)(BOOL earned))completion;
+ (bool)vt_isRewardedLoaded;
+ (void)vt_dumpBannerInfo;

/// 追加一条本会话广告日志（供业务侧写入）
+ (void)vt_appendSessionLog:(NSString *)line;
/// 导出本会话广告日志文本（供设置页复制）
+ (NSString *)vt_sessionLogText;

@end

NS_ASSUME_NONNULL_END
