
//
//  NSArray+ATErrorHandle.h
//  AnyThinkSDK
//
//  NSArray分类 - 错误处理扩展
//  提供安全的数组访问方法，防止数组越界导致的崩溃
//  主要用于增强数组操作的安全性和稳定性
//

#import <Foundation/Foundation.h>

/**
 * @brief NSArray的错误处理分类
 * 
 * 该分类为NSArray添加了安全的访问方法，主要功能包括：
 * - 防止数组越界访问导致的崩溃
 * - 提供安全的下标访问方法
 * - 安全的数组初始化方法
 * 
 * 使用场景：
 * - 需要安全访问数组元素时
 * - 防止因下标越界导致的应用崩溃
 * - 提高应用的稳定性和健壮性
 */
@interface NSArray (ATErrorHandle)

/**
 * @brief 安全的数组元素访问方法
 * 
 * 为数组分类添加的方法，可以在应用中直接调用，可以防止数组越界导致的crash
 * 当索引超出数组范围时，返回nil而不是崩溃
 *
 * @param index 传入的取值下标，需要访问的数组元素索引
 * @return 返回指定索引位置的元素，如果索引越界则返回nil
 * 
 * @note 该方法会自动检查索引的有效性，避免数组越界异常
 */
- (id)AT_objectAtIndexVerify:(NSUInteger)index;


/**
 * @brief 安全的数组初始化方法
 * 
 * 使用另一个数组安全地初始化新数组，避免传入nil数组导致的问题
 *
 * @param array 用于初始化的源数组，可以为nil
 * @return 返回新创建的数组实例，如果源数组为nil则返回空数组
 * 
 * @note 该方法会处理nil输入，确保返回有效的数组对象
 */
+ (instancetype)AT_initWithArray:(NSArray *)array;

@end
