
 
//
//  NSMutableArray+ATErrorHandle.h
//  AnyThinkSDK
//
//  NSMutableArray分类 - 错误处理扩展
//  提供安全的数组操作方法，避免因无效参数导致的崩溃
//  主要用于增强数组操作的安全性和稳定性
//
//  Created by Martin Lau on 2018/4/18.
//  Copyright © 2018年 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief NSMutableArray的错误处理分类
 * 
 * 该分类为NSMutableArray添加了安全的操作方法，主要功能包括：
 * - 安全的对象插入操作
 * - 安全的对象添加操作
 * - 批量添加数组元素
 * - 数组差集运算
 * 
 * 使用场景：
 * - 需要安全操作数组避免崩溃时
 * - 处理可能为nil的对象时
 * - 需要进行数组运算时
 * - 批量处理数组数据时
 */
@interface NSMutableArray (ATErrorHandle)

/**
 * @brief 安全插入对象到指定位置
 * 
 * 在指定索引位置安全地插入对象，会验证对象和索引的有效性
 * 如果对象为nil或索引无效，操作将被忽略而不会导致崩溃
 *
 * @param anObject 需要插入的对象，如果为nil则不执行插入操作
 * @param index 插入位置的索引，必须在有效范围内
 * 
 * @note 该方法会检查参数有效性，提供比系统方法更安全的插入操作
 */
- (void)AT_insertObjectVerify:(id)anObject atIndex:(NSUInteger)index;

/**
 * @brief 安全添加对象到数组末尾
 * 
 * 安全地向数组末尾添加对象，会验证对象的有效性
 * 如果对象为nil，操作将被忽略而不会导致崩溃
 *
 * @param anObject 需要添加的对象，如果为nil则不执行添加操作
 * 
 * @note 该方法会检查对象有效性，避免因添加nil对象导致的崩溃
 */
- (void)AT_addObjectVerify:(id)anObject;

/**
 * @brief 从数组中批量添加对象
 * 
 * 将源数组中的所有对象安全地添加到当前数组中
 * 会验证源数组和其中对象的有效性
 *
 * @param array 源数组，包含需要添加的对象
 * 
 * @note 该方法会过滤掉源数组中的nil对象，确保添加操作的安全性
 */
- (void)AT_addObjectFromArray:(NSArray *)array;

/**
 * @brief 创建排除指定对象的新数组
 * 
 * 从当前数组中移除指定数组中包含的所有对象，返回新的数组
 * 相当于执行数组的差集运算
 *
 * @param array 包含需要排除对象的数组
 * @return 返回移除指定对象后的新数组
 * 
 * @note 该方法不会修改原数组，而是返回一个新的数组实例
 */
//- (NSArray *)AT_arrayBySubstractingObjectsFromArray:(NSArray *)array;

@end
