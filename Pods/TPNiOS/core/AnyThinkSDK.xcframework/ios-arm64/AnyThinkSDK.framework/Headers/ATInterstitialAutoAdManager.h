//
//  ATInterstitialAutoAdManager.h
//  AnyThinkInterstitial
//
//  Created by Jason on 2021/12/31.
//  Copyright © 2021 AnyThink. All rights reserved.
//

/**
 * 插屏广告自动加载管理器（头文件）
 *
 * 职责：对指定 placement 的插屏广告进行「自动预加载」与「展示」的统一管理。
 * - 支持批量添加/移除需要自动加载的 placementID
 * - 在未就绪时触发自动加载（如 autoLoadInterstitialReady 返回 NO 时）
 * - 提供展示、场景上报、本地参数、加载状态与缓存校验等 API
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <AnyThinkSDK/ATInterstitialDelegate.h>
#import <AnyThinkSDK/ATCheckLoadModel.h>
#import <AnyThinkSDK/ATAPI.h>

NS_ASSUME_NONNULL_BEGIN

@interface ATInterstitialAutoAdManager : NSObject

/// 加载回调代理，用于接收自动加载相关回调（如加载成功/失败）
@property(nonatomic, weak) id<ATAdLoadingDelegate> delegate;

/// 单例
+ (instancetype)sharedInstance;

#pragma mark - 自动加载配置

/// 批量添加需要自动加载的插屏 placementID
- (void)addAutoLoadAdPlacementIDArray:(NSArray <NSString *> *)placementIDArray;
/// 批量移除自动加载的插屏 placementID
- (void)removeAutoLoadAdPlacementIDArray:(NSArray<NSString *> *)placementIDArray;

#pragma mark - 本地参数与状态查询

/// 为指定 placement 设置本地透传参数（加载时带上）
- (void)setLocalExtra:(NSDictionary * _Nullable)extra placementID:(NSString *)placementID;
/// 当前 placement 是否有可用的自动加载插屏广告
- (BOOL)autoLoadInterstitialReadyForPlacementID:(NSString *)placementID;
/// 查询该 placement 下有效广告缓存列表（用于调试/统计）
- (NSArray<NSDictionary *> *)checkValidAdCachesWithPlacementID:(NSString *)placementID;
/// 查询该 placement 的插屏加载状态（是否正在加载等）
- (ATCheckLoadModel *)checkInterstitialLoadStatusForPlacementID:(NSString *)placementID;

#pragma mark - 展示

/// 在指定控制器中展示自动加载的插屏广告（无场景）
- (void)showAutoLoadInterstitialWithPlacementID:(NSString*)placementID inViewController:(UIViewController*)viewController delegate:(id<ATInterstitialDelegate>)delegate;

/// 带场景的展示（已废弃，请用 showConfig 版本）
- (void)showAutoLoadInterstitialWithPlacementID:(NSString*)placementID scene:( NSString* _Nullable )scene inViewController:(UIViewController*)viewController delegate:(id<ATInterstitialDelegate>)delegate DEPRECATED_MSG_ATTRIBUTE("use showAutoLoadInterstitialWithPlacementID:showConfig:showConfig:inViewController: delegate");

/// 使用 showConfig 在指定控制器中展示自动加载的插屏广告（推荐）
- (void)showAutoLoadInterstitialWithPlacementID:(NSString*)placementID showConfig:(ATShowConfig * _Nullable )showConfig inViewController:(UIViewController*)viewController delegate:(id<ATInterstitialDelegate>)delegate;

#pragma mark - 场景上报

/// 上报广告场景，用于与展示时的 scene 关联统计
- (void)entryAdScenarioWithPlacementID:(NSString *)placementID scenarioID:(NSString *)scenarioID;

@end

NS_ASSUME_NONNULL_END
