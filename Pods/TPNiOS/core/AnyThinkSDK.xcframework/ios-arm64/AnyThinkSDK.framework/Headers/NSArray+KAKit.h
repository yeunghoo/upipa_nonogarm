//
//  NSArray+KAKit.h
//  AnyThinkSDK
//
//  NSArray分类 - KAKit工具扩展
//  提供数组的常用工具方法，包括JSON转换、函数式编程支持等
//  主要用于增强数组操作的便利性和功能性
//
//  Created by Jason on 2020/10/15.
//  Copyright © 2020 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief NSArray的KAKit工具分类
 * 
 * 该分类为NSArray添加了常用的工具方法，主要功能包括：
 * - JSON字符串转换功能
 * - 数组随机打乱功能
 * - 函数式编程支持（map、filter、reduce）
 * - 可选值处理
 * 
 * 使用场景：
 * - 需要将数组转换为JSON字符串时
 * - 需要对数组进行函数式操作时
 * - 需要随机打乱数组元素时
 * - 调试时需要格式化输出数组内容
 */
@interface NSArray (ATKAKit)

/**
 * @brief 返回可选值包装的数组
 * 
 * 将当前数组包装为可选值，用于处理可能为空的情况
 *
 * @return 返回包装后的数组实例
 * 
 * @note 该方法用于可选值链式调用
 */
//- (instancetype)optional;

/**
 * @brief 将数组转换为JSON字符串
 * 
 * 将数组内容序列化为JSON格式的字符串，用于数据传输或存储
 *
 * @return 返回JSON格式的字符串，如果转换失败返回nil
 * 
 * @note 数组中的元素必须是可JSON序列化的对象
 */
- (NSString *)jsonString_anythink;

/**
 * @brief 返回随机打乱的数组
 * 
 * 创建一个新数组，其中包含当前数组的所有元素，但顺序被随机打乱
 *
 * @return 返回元素顺序被随机打乱的新数组
 * 
 * @note 原数组不会被修改，返回的是新的数组实例
 */
//- (NSArray *)shuffledArray_anythink;

/**
 * @brief 将数组转换为格式化的JSON字符串（调试用）
 * 
 * 将数组内容序列化为格式化的JSON字符串，主要用于调试和日志输出
 * 相比jsonString_anythink方法，该方法返回的JSON字符串具有更好的可读性
 *
 * @return 返回格式化的JSON字符串，如果转换失败返回nil
 * 
 * @note 该方法主要用于调试目的，生产环境建议使用jsonString_anythink
 */
- (NSString *)jsonString_format_debug_anythink;

/**
 * @brief 映射操作 - 函数式编程支持
 * 
 * 对数组中的每个元素应用给定的转换函数，返回包含转换结果的新数组
 *
 * @param handle 转换函数，接收数组元素作为参数，返回转换后的结果
 * @return 返回包含转换结果的新数组
 * 
 * @note 这是函数式编程中的map操作，不会修改原数组
 */
//- (NSArray *)map:(id(^)(id))handle;

/**
 * @brief 过滤操作 - 函数式编程支持
 * 
 * 根据给定的条件函数过滤数组元素，返回包含满足条件元素的新数组
 *
 * @param handle 条件判断函数，接收数组元素作为参数，返回BOOL值表示是否保留该元素
 * @return 返回包含满足条件元素的新数组
 * 
 * @note 这是函数式编程中的filter操作，不会修改原数组
 */
- (NSArray *)filter_anythink:(BOOL(^)(id))handle;

/**
 * @brief 归约操作 - 函数式编程支持
 * 
 * 将数组中的所有元素通过给定的归约函数合并为单个值
 *
 * @param handle 归约函数，接收累积值和当前元素作为参数，返回新的累积值
 * @param initial 初始累积值
 * @return 返回最终的归约结果
 * 
 * @note 这是函数式编程中的reduce操作，可用于求和、连接等聚合操作
 */
//- (id)reduce:(id(^)(id, id))handle initial:(id)initial;

@end


