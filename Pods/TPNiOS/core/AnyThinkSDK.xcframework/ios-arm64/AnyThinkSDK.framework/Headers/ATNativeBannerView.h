//
//  ATNativeBannerView.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2023/6/8.
//  Copyright © 2023 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <AnyThinkSDK/ATScrollLabel.h>
#import <AnyThinkSDK/ATUnitGroupModel.h>
#import <AnyThinkSDK/ATBaseNativeMixView.h>



NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, ATNativeBannerSizeType) {
    ATNativeBannerSizeTypeSmall,// 320 * 50
    ATNativeBannerSizeTypeMiddle,// 320 * 90
    ATNativeBannerSizeTypeBig,// 300 * 250
    ATNativeBannerSizeTypeLARGE,// 728 * 90
};

@interface ATNativeBannerView : ATBaseNativeMixView
/// 子控件的super view
@property (nonatomic, strong) UIView *containerView;

@property (nonatomic, strong) NSString *customExtString;

@property (nonatomic, strong) NSDictionary *configurationDic;

@property (nonatomic, strong) ATPlacementModel *placementModel;

@property(nonatomic,strong) UILabel *ADLabel;
/// netWorkMedia 背景 view
@property (nonatomic, strong) UIView *netWorkMediaBackView;

/// TopOn渲染展示横幅尺寸
@property (nonatomic, assign) ATNativeBannerSizeType nativeBannerSizeType;
/// 广告渲染类型
@property (nonatomic, assign) ATRenderingType nativeBannerRenderType;

- (void)showAd;
@end

NS_ASSUME_NONNULL_END
