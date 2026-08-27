//
//  NSDictionary+KAKit.h
//  Demo
//
//  NSDictionary分类 - KAKit工具扩展
//  提供字典处理的常用工具方法，包括JSON转换、安全访问、弱引用存储等
//  主要用于增强字典操作的便利性和安全性
//
//  Created by Martin Lau on 27/03/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief NSDictionary的KAKit工具分类
 * 
 * 该分类为NSDictionary添加了常用的工具方法，主要功能包括：
 * - JSON字符串转换功能
 * - 安全的键值访问
 * - 字典变化计算
 * - 可选值处理
 * 
 * 使用场景：
 * - 需要将字典转换为JSON字符串时
 * - 需要安全访问字典内容时
 * - 需要检测字典内容变化时
 * - 调试时需要格式化输出字典内容
 */
@interface NSDictionary (ATKAKit)

/**
 * @brief 将字典转换为格式化的JSON字符串（调试用）
 * 
 * 将字典内容序列化为格式化的JSON字符串，主要用于调试和日志输出
 * 返回的JSON字符串具有良好的可读性，包含缩进和换行
 *
 * @return 返回格式化的JSON字符串，如果转换失败返回nil
 * 
 * @note 该方法主要用于调试目的，生产环境建议使用jsonString_anythink
 */
- (NSString *)jsonString_format_debug_anythink;

/**
 * @brief 将字典转换为JSON字符串
 * 
 * 将字典内容序列化为紧凑的JSON格式字符串，用于数据传输或存储
 *
 * @return 返回JSON格式的字符串，如果转换失败返回nil
 * 
 * @note 字典中的值必须是可JSON序列化的对象
 */
- (NSString *)jsonString_anythink;

/**
 * @brief 安全检查字典是否包含指定键
 * 
 * 安全地检查字典中是否包含指定的键，避免因键为nil导致的异常
 *
 * @param key 需要检查的键
 * @return 如果字典包含该键返回YES，否则返回NO
 * 
 * @note 该方法会处理key为nil的情况，提供更安全的访问方式
 */
- (BOOL)AT_containsObjectForKey:(id)key;

/**
 * @brief 计算字典对象变化的字符串表示
 * 
 * 分析字典中对象的变化情况，返回变化的字符串描述
 * 主要用于监控和调试字典内容的变化
 *
 * @return 返回描述对象变化的字典
 * 
 * @note 该方法用于跟踪字典内容的变化情况
 */
- (NSDictionary *)AT_calculateObjectChangeStringForKey;

/**
 * @brief 返回可选值包装的字典
 * 
 * 将当前字典包装为可选值，用于处理可能为空的情况
 *
 * @return 返回包装后的字典实例
 * 
 * @note 该方法用于可选值链式调用
 */
//- (instancetype)optional;

@end

/**
 * @brief NSMutableDictionary的弱引用扩展分类
 * 
 * 该分类为NSMutableDictionary添加了弱引用存储功能，主要功能包括：
 * - 弱引用对象的存储和获取
 * - 安全的字典值设置
 * - 字典合并操作
 * 
 * 使用场景：
 * - 需要存储弱引用对象避免循环引用时
 * - 需要安全设置字典值时
 * - 需要合并多个字典时
 */
@interface NSMutableDictionary(ATWeakMutable)

/**
 * @brief 设置弱引用对象
 * 
 * 在字典中存储一个弱引用对象，当对象被释放时自动从字典中移除
 *
 * @param anObject 需要存储的弱引用对象
 * @param aKey 存储对象的键
 * 
 * @note 使用弱引用可以避免循环引用问题
 */
- (void)AT_setWeakObject:(__weak id)anObject forKey:(id<NSCopying>)aKey;

/**
 * @brief 获取弱引用对象
 * 
 * 从字典中获取之前存储的弱引用对象
 *
 * @param aKey 对象的键
 * @return 返回存储的弱引用对象，如果对象已被释放或不存在则返回nil
 * 
 * @note 如果原对象已被释放，该方法会返回nil
 */
- (id)AT_weakObjectForKey:(id)aKey;

/**
 * @brief 移除弱引用对象
 * 
 * 从字典中移除指定键的弱引用对象
 *
 * @param key 需要移除的对象的键
 * 
 * @note 该方法会清理弱引用存储
 */
- (void)AT_removeWeakObjectForKey:(id)key;

/**
 * @brief 安全设置字典值
 * 
 * 安全地向字典中设置键值对，会处理value或key为nil的情况
 *
 * @param value 需要设置的值，可以为nil
 * @param key 键名，不能为nil
 * 
 * @note 该方法会检查参数有效性，避免因nil值导致的崩溃
 */
- (void)AT_setDictValue:(id)value key:(NSString *)key;

/**
 * @brief 安全合并字典
 * 
 * 将另一个字典的内容安全地合并到当前字典中
 *
 * @param diction 需要合并的源字典，可以为nil
 * 
 * @note 该方法会检查源字典的有效性，避免因nil字典导致的异常
 */
- (void)AT_addEntriesFromDictionary:(NSDictionary *)diction;

@end
