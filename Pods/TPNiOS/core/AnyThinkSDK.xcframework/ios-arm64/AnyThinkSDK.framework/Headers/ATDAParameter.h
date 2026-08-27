//
//  ATDAParameter.h
//  AnyThinkSDK
//
//  Created by GUO PENG on 2024/3/8.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ATLoadParams, ATAdSourceRequestParams, ATPlacementModel, ATUnitGroupModel;

NS_ASSUME_NONNULL_BEGIN

@interface ATDAParameter : NSObject

+ (ATDAParameter *(^)(NSString *))daKey;

#pragma mark - 核心参数（推荐，新增埋点都推荐使用该参数传入）
- (ATDAParameter *(^)(ATLoadParams *))loadParams;
- (ATDAParameter *(^)(ATAdSourceRequestParams *))adSourceRequestParams;
/// extraDic 信息优先级最高
- (ATDAParameter *(^)(NSDictionary *))extraDic;

#pragma mark - 兼容参数（用于无法获取 loadParams/adSourceRequestParams 的场景，兼容旧逻辑，目前adapter那边还有些埋点在用）
- (ATDAParameter *(^)(ATPlacementModel *))placementModel;
- (ATDAParameter *(^)(ATUnitGroupModel *))unitGroupModel;
- (ATDAParameter *(^)(NSString *))placementID;
- (ATDAParameter *(^)(NSInteger))format;
- (ATDAParameter *(^)(NSString *))requsetId;

#pragma mark - 消息字段
- (ATDAParameter *(^)(id))msg;
- (ATDAParameter *(^)(id))msg1;
- (ATDAParameter *(^)(id))msg2;
- (ATDAParameter *(^)(id))msg3;
- (ATDAParameter *(^)(id))msg4;
- (ATDAParameter *(^)(id))msg5;
- (ATDAParameter *(^)(id))msg6;
- (ATDAParameter *(^)(id))msg7;
- (ATDAParameter *(^)(id))msg8;
- (ATDAParameter *(^)(id))msg9;
- (ATDAParameter *(^)(id))msg10;
- (ATDAParameter *(^)(id))msg11;
- (ATDAParameter *(^)(id))msg12;
- (ATDAParameter *(^)(id))msg13;
- (ATDAParameter *(^)(id))msg14;
- (ATDAParameter *(^)(id))msg15;
- (ATDAParameter *(^)(id))msg16;
- (ATDAParameter *(^)(id))msg17;
- (ATDAParameter *(^)(id))msg18;
- (ATDAParameter *(^)(id))msg19;
- (ATDAParameter *(^)(id))msg20;
- (ATDAParameter *(^)(id))msg21;
- (ATDAParameter *(^)(id))msg22;
- (ATDAParameter *(^)(id))msg23;
- (ATDAParameter *(^)(id))msg24;
- (ATDAParameter *(^)(id))msg25;
- (ATDAParameter *(^)(id))msg26;
- (ATDAParameter *(^)(id))msg27;
- (ATDAParameter *(^)(id))msg28;
- (ATDAParameter *(^)(id))msg29;
- (ATDAParameter *(^)(id))msg30;

#pragma mark - 内部使用
@property (atomic, copy, readonly) NSString *at_daKeyString;
@property (nonatomic, strong) ATAdSourceRequestParams *at_adSourceRequestParams;
@property (nonatomic, strong) ATLoadParams *at_loadParams;

#pragma mark - 派生属性（从 loadParams/adSourceRequestParams 获取）
@property (nonatomic, copy, readonly) NSString *at_placementID;
@property (nonatomic, assign, readonly) NSInteger at_format;
@property (nonatomic, strong, readonly) ATPlacementModel *at_placementModel;
@property (nonatomic, strong, readonly) ATUnitGroupModel *at_unitGroupModel;

- (NSDictionary *)getDASendParameterDic;

@end

NS_ASSUME_NONNULL_END
