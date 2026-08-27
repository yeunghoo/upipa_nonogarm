//
//  ZScrollLabel.h
//  WeexDemo
//
//  Created by WSCN on 09/05/2017.
//  Copyright © 2017 wallstreetcn.com. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * @brief 滚动标签对齐方式枚举
 * 
 * 定义当文字长度未超过视图宽度时的文字对齐方式。
 */
typedef NS_ENUM(NSUInteger, ATScrollLabelAlignment) {
    ATScrollLabelAlignmentLeft = 0,     ///< 左对齐
    ATScrollLabelAlignmentCenter,       ///< 居中对齐（默认）
    ATScrollLabelAlignmentRight         ///< 右对齐
};

/**
 * @brief 跑马灯滚动标签视图
 * 
 * 智能滚动标签组件，当文本宽度超过视图宽度时自动启用滚动效果，
 * 当文本宽度未超过视图宽度时显示静态文本。
 * 支持自定义滚动速度、延迟时间、暂停间隔等参数。
 * 
 * @discussion 功能特性：
 * - 智能检测文本长度，自动决定是否启用滚动
 * - 支持自定义滚动速度和持续时间
 * - 支持延迟启动和循环间隔暂停
 * - 支持多种文字对齐方式
 * - 自动处理应用前后台切换
 * - 支持手动控制滚动开始和停止
 * - 使用双Label实现无缝循环滚动效果
 */
@interface ATScrollLabel : UIView

/// @name 文本样式属性

/**
 * @brief 文本字体
 * 
 * 设置滚动标签的字体样式，影响文本的显示效果和宽度计算。
 */
@property (nonatomic, strong) UIFont *font;

/**
 * @brief 文本颜色
 * 
 * 设置滚动标签的文本颜色。
 */
@property (nonatomic, strong) UIColor *textColor;

/**
 * @brief 显示文本内容
 * 
 * 设置要显示的文本内容。当文本宽度超过视图宽度时自动启用滚动效果。
 */
@property (nonatomic, strong) NSString *text;

/// @name 滚动行为属性

/**
 * @brief 滚动总时长
 * 
 * 完成一次完整滚动所需的时间（单位：秒），默认为10秒。
 * 此属性与scrollVelocity互斥，优先使用scrollVelocity。
 */
@property (nonatomic, assign) CGFloat scrollDuration;

/**
 * @brief 滚动速率
 * 
 * 滚动的像素速度（单位：pt/s），默认为37.5。
 * 赋值必须大于0，否则使用默认值37.5。
 */
@property (nonatomic, assign) CGFloat scrollVelocity;

/**
 * @brief 标签间距
 * 
 * 循环滚动时两个标签之间的距离（单位：pt），默认为20。
 */
@property (nonatomic, assign) CGFloat paddingBetweenLabels;

/**
 * @brief 文字对齐方式
 * 
 * 当文字长度未超过视图宽度时的对齐方式，默认为居中对齐。
 */
@property (nonatomic, assign) ATScrollLabelAlignment labelAlignment;

/// @name 时间控制属性

/**
 * @brief 延迟启动时间
 * 
 * 延迟开始第一次滚动的时间（单位：秒），默认为3秒。
 */
@property (nonatomic, assign) CGFloat delayInterval;

/**
 * @brief 循环暂停时间
 * 
 * 循环滚动时每次滚动完成后的暂停时长（单位：秒），默认为3秒。
 */
@property (nonatomic, assign) CGFloat pauseInterval;

/// @name 控制属性

/**
 * @brief 是否自动开始滚动
 * 
 * 设置是否在文本设置后自动开始滚动，默认为NO。
 * 设置为NO时需要手动调用startScrollAnimation方法启动滚动。
 */
@property (nonatomic, assign) BOOL autoBeginScroll;

/**
 * @brief 滚动状态
 * 
 * 只读属性，表示当前是否正在滚动。
 */
@property (nonatomic, assign, getter=isScrolling) BOOL scrolling;

/// @name 控制方法

/**
 * @brief 开始滚动动画
 * 
 * 手动启动滚动动画。当调用stopScrollAnimation方法停止动画后，
 * 如果需要重新开始动画时调用此方法。
 * 
 * @discussion 只有当文本宽度超过视图宽度时才会实际开始滚动，
 * 否则文本将以设定的对齐方式静态显示。
 */
- (void)startScrollAnimation;

/**
 * @brief 停止滚动动画
 * 
 * 立即停止当前的滚动动画，文本将回到初始位置。
 * 停止后需要调用startScrollAnimation方法才能重新开始滚动。
 */
- (void)stopScrollAnimation;

@end
