//
//  NSString+KAKit.h
//  Demo
//
//  NSString分类 - KAKit工具扩展
//  提供字符串编码解码、加密、格式化、验证等常用功能
//  主要用于增强字符串处理的便利性和安全性
//
//  Created by Martin Lau on 27/03/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * @brief NSString的KAKit工具分类
 * 
 * 该分类为NSString添加了丰富的工具方法，主要功能包括：
 * - Base64编码解码（支持自定义编码表）
 * - MD5哈希计算
 * - URL编码解码
 * - 字符串格式化和验证
 * - 数据类型转换
 * - 文本尺寸计算
 * - 属性字符串创建
 * 
 * 使用场景：
 * - 需要进行字符串编码转换时
 * - 需要计算字符串哈希值时
 * - 需要处理URL编码时
 * - 需要验证字符串格式时
 * - 需要计算文本显示尺寸时
 */
@interface NSString (ATKAKit)

/**
 * @brief 使用自定义编码表进行Base64编码
 * 
 * 使用指定的编码表对字符串进行Base64编码
 *
 * @param table 自定义的Base64编码表
 * @return 返回编码后的字符串
 * 
 * @note 编码表必须包含64个字符，用于替换标准Base64字符
 */
- (NSString *)AT_base64EncodingUsingTable:(NSString *)table;

/**
 * @brief 使用自定义编码表进行Base64解码
 * 
 * 使用指定的编码表对Base64编码的字符串进行解码
 *
 * @param table 自定义的Base64编码表
 * @return 返回解码后的字符串
 * 
 * @note 编码表必须与编码时使用的表一致
 */
- (NSString *)AT_base64DecodingUsingTable:(NSString *)table;

/**
 * @brief 计算字符串的MD5哈希值
 * 
 * 对当前字符串计算MD5哈希值，返回32位十六进制字符串
 *
 * @return 返回MD5哈希值的十六进制字符串表示
 * 
 * @note MD5算法不适用于安全敏感的场景，仅用于数据校验
 */
- (NSString *)AT_md5;

/**
 * @brief 从NSData创建字符串
 * 
 * 使用指定的编码从NSData对象创建字符串
 *
 * @param data 源数据对象
 * @param encoding 字符串编码格式
 * @return 返回创建的字符串，如果转换失败返回nil
 * 
 * @note 该方法提供了安全的数据到字符串转换
 */
//+ (NSString *)AT_stringWithData:(NSData *)data usingEncoding:(NSStringEncoding)encoding;

/**
 * @brief 标准Base64编码
 * 
 * 使用标准Base64编码表对字符串进行编码
 *
 * @return 返回Base64编码后的字符串
 * 
 * @note 使用标准的Base64编码算法
 */
- (NSString *)stringByBase64Encoding_anythink;

/**
 * @brief 标准Base64解码
 * 
 * 对Base64编码的字符串进行标准解码
 *
 * @return 返回解码后的字符串
 * 
 * @note 使用标准的Base64解码算法
 */
- (NSString *)stringByBase64Decoding_anythink;

/**
 * @brief URL编码
 * 
 * 对字符串进行URL编码，转义特殊字符
 *
 * @return 返回URL编码后的字符串
 * 
 * @note 该方法会转义URL中的特殊字符，使其可以安全地用于URL
 */
//- (NSString *)AT_stringUrlEncode;

/**
 * @brief 创建带下划线的属性字符串
 * 
 * 创建一个带有下划线样式的NSMutableAttributedString
 *
 * @param color 下划线颜色
 * @param font 文字字体
 * @return 返回带下划线的属性字符串
 * 
 * @note 该方法用于创建带有下划线装饰的文本
 */
//- (NSMutableAttributedString *)AT_underlineAttributedStringWithColor:(UIColor *)color font:(UIFont *)font;

/**
 * @brief 返回可选值包装的字符串
 * 
 * 将当前字符串包装为可选值，用于处理可能为空的情况
 *
 * @return 返回包装后的字符串实例
 * 
 * @note 该方法用于可选值链式调用
 */
//- (instancetype)optional;

/**
 * @brief 转换为小数字符串
 * 
 * 将字符串转换为标准的小数格式字符串
 *
 * @return 返回格式化后的小数字符串
 * 
 * @note 该方法用于数字字符串的格式化处理
 */
- (NSString *)AT_decimalString;

/**
 * @brief 使用正则表达式判断是否为数字
 * 
 * 通过正则表达式验证字符串是否为有效的数字格式
 *
 * @return 如果是数字格式返回YES，否则返回NO
 * 
 * @note 该方法支持整数和小数的验证
 */
//- (BOOL)AT_judgeIsNumberByRegularExpression;

/**
 * @brief 移除浮点数末尾的零
 * 
 * 移除浮点数字符串末尾不必要的零，如"1.200"变为"1.2"
 *
 * @return 返回处理后的字符串
 * 
 * @note 该方法用于美化数字显示格式
 */
//- (NSString *)at_removeFloatAllZero;

/**
 * @brief 转换为字典对象
 * 
 * 将JSON格式的字符串转换为NSDictionary对象
 *
 * @return 返回转换后的字典对象，如果转换失败返回nil
 * 
 * @note 字符串必须是有效的JSON格式
 */
- (NSDictionary *)at_convertToDictionary;

/**
 * @brief 转换为数组对象
 * 
 * 将JSON格式的字符串转换为NSArray对象
 *
 * @return 返回转换后的数组对象，如果转换失败返回nil
 * 
 * @note 字符串必须是有效的JSON数组格式
 */
- (NSArray *)at_convertToArray;

/**
 * @brief 计算字符串在指定高度下的宽度
 * 
 * 根据指定的高度和字体计算字符串显示所需的宽度
 *
 * @param height 限制的高度
 * @param font 使用的字体
 * @return 返回计算出的宽度值
 * 
 * @note 该方法用于文本布局和尺寸计算
 */
//- (CGFloat)AT_calculateWidthWithHeight:(CGFloat)height
//                                  font:(UIFont *)font;

/**
 * @brief 特殊URL解码
 * 
 * 对特殊编码的URL字符串进行解码
 *
 * @param stringToDecode 需要解码的字符串
 * @return 返回解码后的字符串
 * 
 * @note 该方法处理特殊的URL编码格式
 */
+ (NSString *)AT_specially_url_decode:(NSString *)stringToDecode;

/**
 * @brief 返回字符串自身
 * 
 * NSString分类中的stringValue方法，直接返回字符串自身
 * 用于统一接口，避免某些系统版本中调用stringValue方法导致崩溃
 *
 * @return 返回字符串自身
 * 
 * @note 该方法主要用于提供统一的stringValue接口，确保NSString对象也能安全调用stringValue
 */
- (NSString *)stringValue;

@end
