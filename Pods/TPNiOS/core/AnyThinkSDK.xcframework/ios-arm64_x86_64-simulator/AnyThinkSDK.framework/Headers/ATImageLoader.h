//
//  ATImageLoader.h
//  AnyThinkSDK
//
//  Created by Martin Lau on 27/04/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 * 图片加载器类，用于异步加载网络图片并提供缓存功能
 * 支持多种图片加载方式，包括URL和字符串形式的图片地址
 */
@interface ATImageLoader : NSObject

/**
 * 获取图片加载器的单例实例
 * @return ATImageLoader的共享实例
 * 不能修改该单例初始化方法，外部adapter有在使用
 */
+ (instancetype)shareLoader;

/**
 * 异步加载指定URL的图片
 * 完成回调可能不会在调用此方法的同一线程上调用
 * 目前仅支持HTTP-GET请求
 * @param URL 图片的URL地址
 * @param completion 加载完成的回调块，包含加载的图片或错误信息
 */
- (void)loadImageWithURL:(NSURL *)URL completion:(void(^)(UIImage *image, NSError *error))completion;

/**
 * 同步获取指定URL的图片（从缓存中获取）
 * @param URL 图片的URL地址
 * @return 缓存中的图片，如果不存在则返回nil
 */
- (UIImage *)getImageWithURL:(NSURL *)URL;

/**
 * 使用字符串URL异步加载图片（新版本方法，使用ATWebImage处理）
 * @param imageUrl 图片URL的字符串形式
 * @param completion 加载完成的回调块，包含加载的图片或错误信息
 */
- (void)newLoadImageWithURL:(NSString *)imageUrl completion:(void(^)(UIImage *image, NSError *error))completion;

/**
 * 同步获取指定字符串URL的图片（新版本方法，从缓存中获取，使用ATWebImage处理）
 * @param URLString 图片URL的字符串形式
 * @return 缓存中的图片，如果不存在则返回nil
 */
- (UIImage *)getNewImageWithURLString:(NSString *)URLString;

/**
 * 异步加载图片并返回图片数据
 * @param imageUrl 图片URL的字符串形式
 * @param completion 加载完成的回调块，包含加载的图片、原始数据或错误信息
 */
- (void)loadImageDataWithURL:(NSString *)imageUrl completion:(void(^)(UIImage *image, NSData *data, NSError *error))completion;

/**
 * 检查指定URL的图片资源是否在缓存中有效
 * @param imageUrl 图片URL的字符串形式
 * @return YES表示缓存中存在有效资源，NO表示不存在或已失效
 */
- (BOOL)isValidResourceInCache:(NSString *)imageUrl;

@end
