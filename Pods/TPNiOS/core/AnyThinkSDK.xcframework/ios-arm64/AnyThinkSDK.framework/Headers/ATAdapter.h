//
//  ATAdapter.h
//  ToponSdkDemo
//
//  Created by li zhixuan on 2022/11/18.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAdAdapter.h>


NS_ASSUME_NONNULL_BEGIN

@protocol ATAdapterDelegate;

#pragma mark - ATAdapterProtocol
@protocol ATAdapterProtocol <NSObject>

/// 代理
@property (nonatomic, weak) id<ATAdapterDelegate> delegate;
// 无用
//- (void)loadWithUserInfo:(NSDictionary<id, id> *)userInfo;
/// 展示广告
- (void)show;

@end

#pragma mark - ATAdapterDelegate
@protocol ATAdapterDelegate <NSObject>

/// 广告加载完成回调
- (void)adapter:(id<ATAdapterProtocol>)adapter adDidLoadCompletionWithUserInfo:(NSDictionary *)userInfo error:(nullable NSError *)error;

@end

#pragma mark - ATAdapter
@interface ATAdapter : NSObject<ATAdAdapter>

/// 初始化方法
- (instancetype)initWithClass:(Class)clazz;

//- (BOOL)adReadyForInfo:(NSDictionary *)info;
//- (ATAdObject *)readyFilledAdWithPlacementModel:(ATPlacementModel *)placementModel
//                                  requestID:(NSString *)requestID
//                                   priority:(NSInteger)priority
//                                  unitGroup:(ATUnitGroupModel *)unitGroup
//                                  localInfo:(NSDictionary *)localInfo;

@end

NS_ASSUME_NONNULL_END
