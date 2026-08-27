//
//  SDMNativeLayoutParams.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/13.
//

#import <UIKit/UIKit.h>
#import <SmartdigimktSDK/SDMNativePrepareInfo.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, SDMNativeAdOfferVideoPlayType) {
    SDMNativeAdOfferVideoPlayAlwaysAutoPlayType  = 0,
    SDMNativeAdOfferVideoPlayOnlyWiFiAutoPlayType,
    SDMNativeAdOfferVideoPlayClickAutoPlayType,
};

@interface SDMNativeLayoutParams : UIView

/**
 You can store some extra network specific context info in this dictionary.
 */
@property (nonatomic, copy) NSDictionary *context;
@property (nonatomic) Class renderingViewClass;
@property (nonatomic) CGRect AdFrame;
@property (nonatomic) CGRect mediaViewFrame;
@property (nonatomic, weak) UIViewController *rootViewController;
@property (nonatomic) BOOL sizeToFit;
@property (nonatomic) BOOL useCustomPlayer;
@property (nonatomic, assign) SDMNativeAdOfferVideoPlayType videoPlayType;
@property (nonatomic, assign) CGRect logoViewFrame;
@property (nonatomic, assign) CGPoint adChoicesViewOrigin;

@end

NS_ASSUME_NONNULL_END
