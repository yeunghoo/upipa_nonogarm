//
//  SDMNativeAdOffer.h
//  SmartdigimktSDK
//
//  Created by xuejingwei on 2025/8/13.
//

#import <Foundation/Foundation.h>
#import <SmartdigimktSDK/SDMAdFormatDefine.h>
#import <UIKit/UIKit.h>

typedef NS_ENUM (NSInteger, SDMNativeAdInteractionType) {
    SDMNativeAdInteractionTypeUnknown        = 0,
    SDMNativeAdInteractionTypeNone           = 1,  // pure ad display
    SDMNativeAdInteractionTypeURL            = 2,  // open the webpage using a browser
    SDMNativeAdInteractionTypePage           = 3,  // open the webpage within the app
    SDMNativeAdInteractionTypeDownload       = 4,  // download the app
    SDMNativeAdInteractionTypePhone          = 5,  // make a call
    SDMNativeAdInteractionTypeMessage        = 6,  // send messages
    SDMNativeAdInteractionTypeEmail          = 7,  // send email
    SDMNativeAdInteractionTypeVideoAdDetail  = 8,  // video ad details page
    SDMNativeAdInteractionTypeWechat         = 9,  // open wechat
    SDMNativeAdInteractionTypeOthers         = 100 // types returned by other ad sdk
};

NS_ASSUME_NONNULL_BEGIN

@interface SDMNativeAdOffer : NSObject

@property (nonatomic, assign, readonly) SDMNativeAdRenderType nativeAdRenderType;
/// network template ad view
@property (nonatomic, strong, readonly, nullable) UIView *templateView;
/// is video type
@property (nonatomic, assign, readonly) BOOL isVideoContents;
/// ad title
@property (nonatomic, copy, readonly, nullable) NSString *title;
/// Ad details
@property (nonatomic, copy, readonly, nullable) NSString *mainText;
/// CTA Button text such as 'download/install'
@property (nonatomic, copy, readonly, nullable) NSString *ctaText;
/// app icon url
@property (nonatomic, copy, readonly, nullable) NSString *iconUrl;
/// main image url
@property (nonatomic, copy, readonly, nullable) NSString *imageUrl;
/// ad logo url
@property (nonatomic, copy, readonly, nullable) NSString *logoUrl;
/// mediaView
@property (nonatomic, strong, readonly, nullable) UIView *mediaView;
/// video aspect ratio (width/height), if no value or exception returns 0
@property (nonatomic, assign, readonly) CGFloat videoAspectRatio;
/// video duration, in second, if there is no value, return 0
@property (nonatomic, assign, readonly) CGFloat videoDuration;
/// main image width
@property (nonatomic, assign, readonly) CGFloat mainImageWidth;
/// main image height
@property (nonatomic, assign, readonly) CGFloat mainImageHeight;
/// TemplateView Type
@property (nonatomic, assign, readonly) NSInteger expressType;
/// Ad-supported jump types
@property (nonatomic, assign, readonly) SDMNativeAdInteractionType interactionType;

@end

NS_ASSUME_NONNULL_END
