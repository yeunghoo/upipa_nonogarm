//
//  ATUMPConsentHandler.h
//  AnyThinkSDK
//
//  Created by Topon on 12/13/23.
//  Copyright © 2023 AnyThink. All rights reserved.
//

/*
 模块说明（ATUMPConsentHandler）
 
 该模块封装 Google UMP（User Messaging Platform）相关能力的动态调用，提供隐私弹窗与同意信息采集流程：
 
 特点与约束：
 - 使用运行时反射与 `NSInvocation` 进行动态调用，避免编译期对 UMP SDK 的强依赖；
 - 在 `TCString` 已存在时可快速回调完成，提升用户体验与初始化效率；
 - 结合 `ATPrivacySettingHandler` 在同意采集结束后，初始化并解析隐私配置。
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef void(^ConsentGatheringComplete)(NSError *_Nullable);

@interface ATUMPConsentHandler : NSObject

/**
 是否可以请求广告。
 - 返回：UMP `ConsentInformation.canRequestAds` 动态读取结果。
 - 失败处理：若 UMP 不可用返回 NO，并记录日志。
 */
+ (BOOL)canRequestAds;
/**
 是否需要展示隐私选项页。
 - 返回：UMP `privacyOptionsRequirementStatus` 为 Required 时返回 YES。
 - 失败处理：若 UMP 不可用或接口不可用返回 NO。
 */
+ (BOOL)isPrivacyOptionsRequired;
/**
 采集 GDPR/UMP 同意流程。
 - 参数：`viewController` 展示弹窗的控制器，可为当前界面；
        `consentGatheringComplete` 完成回调，错误为 `nil` 表示成功或可继续流程。
 - 行为：
   1) 若已存在 `TCString` 则提前回调成功；
   2) 动态调用 UMP 更新同意信息与加载/展示表单；
   3) 表单错误但 `canRequestAds == YES` 仍回调成功。
 - 线程：需在主线程触发 UI 展示，回调也建议回到主线程。
 */
+ (void)gatherConsentFromConsentPresentationViewController:(UIViewController *)viewController
                                  consentGatheringComplete:(void (^)(NSError *_Nullable))consentGatheringComplete;
/**
 展示隐私选项页。
 - 参数：`viewController` 展示弹窗的控制器；`completionHandler` 完成回调。
 - 失败处理：如 UMP 不可用或方法不可用，通过回调返回错误。
 - 线程：主线程展示与回调。
 */
+ (void)presentPrivacyOptionsFromViewController:(UIViewController *)viewController
                              completionHandler:(void (^)(NSError *_Nullable))completionHandler;

@end

NS_ASSUME_NONNULL_END
