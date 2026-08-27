//
//  ATTimer.h
//  ATSDK
//
//  Created by 陈俊杰 on 2017/6/6.
//  Copyright © 2017年 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * 基于NSTimer的定时器封装类
 * 提供更灵活的定时器控制功能，支持暂停、恢复、重新启动等操作
 * 相比原生NSTimer增加了更多的状态管理和控制方法
 */
@interface ATTimer : NSObject

/**
 * RunLoop模式设置
 * 指定定时器在哪种RunLoop模式下运行，默认为NSDefaultRunLoopMode
 */
@property (nonatomic, copy) NSString *runLoopMode;

/**
 * 创建定时器实例（基础版本）
 * @param seconds 定时器触发间隔（秒）
 * @param target 定时器触发时调用的目标对象
 * @param aSelector 定时器触发时调用的方法选择器
 * @param repeats 是否重复执行，YES为重复，NO为单次执行
 * @return 配置好的ATTimer实例
 */
+ (ATTimer *)timerWithTimeInterval:(NSTimeInterval)seconds
                            target:(id)target
                          selector:(SEL)aSelector
                           repeats:(BOOL)repeats;

/**
 * 创建定时器实例（完整版本）
 * @param seconds 定时器触发间隔（秒）
 * @param target 定时器触发时调用的目标对象
 * @param aSelector 定时器触发时调用的方法选择器
 * @param userInfo 传递给目标方法的用户信息，可以为nil
 * @param repeats 是否重复执行，YES为重复，NO为单次执行
 * @return 配置好的ATTimer实例
 */
+ (ATTimer *)timerWithTimeInterval:(NSTimeInterval)seconds
                            target:(id)target
                          selector:(SEL)aSelector
                          userInfo:(nullable id)userInfo
                           repeats:(BOOL)repeats;

/**
 * 检查定时器是否有效
 * @return YES表示定时器有效，NO表示定时器已失效
 */
- (BOOL)isValid;

/**
 * 中断定时器
 * 停止定时器并使其失效，无法再次启动
 */
- (void)invalidate;

/**
 * 检查定时器是否已启动
 * @return YES表示定时器已启动，NO表示未启动
 */
- (BOOL)isScheduled;

/**
 * 立即启动定时器
 * 将定时器添加到当前RunLoop中开始执行
 * @return YES表示启动成功，NO表示启动失败
 */
- (BOOL)scheduleNow;

/**
 * 暂停定时器
 * 暂停定时器的执行，保持当前状态
 * @return YES表示暂停成功，NO表示暂停失败
 */
- (BOOL)pause;

/**
 * 恢复定时器
 * 从暂停状态恢复定时器的执行
 * @return YES表示恢复成功，NO表示恢复失败
 */
- (BOOL)resume;

/**
 * 新的恢复方法
 * 从暂停时间开始重新计算定时器间隔
 * @return YES表示恢复成功，NO表示恢复失败
 */
- (BOOL)newResume;

/**
 * 获取初始时间间隔
 * @return 定时器创建时设置的时间间隔
 */
- (NSTimeInterval)initialTimeInterval;

@end
