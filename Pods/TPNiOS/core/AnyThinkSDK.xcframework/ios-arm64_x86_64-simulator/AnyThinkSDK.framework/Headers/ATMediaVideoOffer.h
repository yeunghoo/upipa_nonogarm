//
//  ATMediaVideoObject.h
//  AnyThinkMediaVideo
//
//  Created by li zhixuan on 2024/3/6.
//  Copyright © 2024 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AnyThinkSDK/ATAPI.h>
#import <AnyThinkSDK/ATAdObject.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ATMediaVideoOfferType) {
    ATMediaVideoOfferTypeUnknow,
    ATMediaVideoOfferTypeVAST,
    ATMediaVideoOfferTypeVMAP,
};

@interface ATMediaVideoOffer : NSObject

@property (nonatomic, readonly) ATShowConfig *showConfig;

@property (nonatomic, strong, nullable) UIView *loadView;

@property (nonatomic, assign) ATMediaVideoOfferType type;

- (instancetype)initWithAd:(ATAdObject *)ad showConfig:(ATShowConfig *)showConfig;

- (void)contentPlayhead:(id)contentPlayhead;

- (id)customNetworkObj;
- (id)adsManager;

- (void)start;
- (void)startWithViewController:(nullable UIViewController *)viewController;

- (void)pause;

- (void)resume;

- (void)skip;

- (void)clicked;

- (void)destory;

- (void)discardAdBreak;

- (void)contentComplete;

- (void)registerFriendlyObstruction:(id)friendlyObstruction;
- (void)unregisterAllFriendlyObstructions;

@end

NS_ASSUME_NONNULL_END
