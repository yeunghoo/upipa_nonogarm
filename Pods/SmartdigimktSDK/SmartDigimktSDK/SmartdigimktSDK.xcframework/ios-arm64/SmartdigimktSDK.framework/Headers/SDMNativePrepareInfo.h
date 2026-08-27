//
//  SDMNativePrepareInfo.h
//  SmartdigimktNative
//
//  Created by GUO PENG on 2022/5/7.
//  Copyright © 2022 Smartdigimkt. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


NS_ASSUME_NONNULL_BEGIN

@interface SDMNativePrepareInfo : NSObject

@property (nonatomic, weak) UIView *advertiserLabel;
@property (nonatomic, weak) UIView *textLabel;
@property (nonatomic, weak) UIView *titleLabel;
@property (nonatomic, weak) UIView *ctaLabel;
@property (nonatomic, weak) UIView *ratingLabel;
@property (nonatomic, weak) UIView *iconImageView;
@property (nonatomic, weak) UIView *mainImageView;
@property (nonatomic, weak) UIView *logoImageView;
@property (nonatomic, weak) UIView *dislikeButton;
@property (nonatomic, weak) UIView *mediaView;
@property (nonatomic, weak) UIView *domainLabel;
@property (nonatomic, weak) UIView *warningLabel;
@property (nonatomic, weak) UIView *mediaContainerView;

+ (instancetype)loadPrepareInfo: (void(^)(SDMNativePrepareInfo *prepareInfo))loadPrepareInfoBlock;

@end

NS_ASSUME_NONNULL_END
