//
//  ATBaseNativeMixView.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/12/17.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN
@protocol ATNativeMaterialProtocol;

@class ATCustomNetworkNativeAd,ATAdOfferCacheModel;

@interface ATBaseNativeMixView : UIView
/// domain
@property(nonatomic, strong) UILabel *domainLabel;
/// 警告
@property(nonatomic, strong) UILabel *warningLabel;

/// 广告商
@property(nonatomic, strong) UILabel *advertiserLabel;

/// 广告内容
@property(nonatomic, strong) UILabel *textLabel;

/// 广告标题
@property(nonatomic, strong) UILabel *titleLabel;

/// 下载
@property(nonatomic, strong) UILabel *ctaLabel;

/// 评分
@property(nonatomic, strong) UILabel *ratingLabel;
/// 赞助商,来源
@property(nonatomic, strong) UILabel *sponsorLabel;
/// 价格
@property(nonatomic, strong) UILabel *priceLabel;
/// icon
@property(nonatomic, strong) UIImageView *iconImageView;

/// 主图
@property(nonatomic, strong) UIImageView *mainImageView;

/// logo
@property(nonatomic, strong) UIImageView *logoImageView;

/// dislike
@property(nonatomic, strong) UIButton *dislikeButton;

/// 三方SDKMediaView
@property (nonatomic, strong) UIView *netWorkMediaView;

/// 三方SDKOptionView
@property (nonatomic, strong) UIView *netWorkOptionView;

/// 背景图片
@property (nonatomic, strong) UIImageView *backgroundImageView;

@property (nonatomic, strong) UIVisualEffectView *blurView;

/// 素材
@property (nonatomic, strong) id <ATNativeMaterialProtocol>nativeAdMaterial;

#pragma mark - 注册点击
- (void)registerClickableViewArray:(NSArray<UIView*> *)clickableViewArray;

- (NSMutableArray<UIView*> *)clickableViews;

/// 图片素材的方向
- (BOOL)isMaterialLandscape;


/// 获取自渲染摇一摇视图
- (UIView *)getNetworkShakeViewWithFrame:(CGRect)frame;
/// 开启摇一摇
- (void)startShake;
/// 关闭摇一摇
- (void)stopShake;



@end

NS_ASSUME_NONNULL_END
