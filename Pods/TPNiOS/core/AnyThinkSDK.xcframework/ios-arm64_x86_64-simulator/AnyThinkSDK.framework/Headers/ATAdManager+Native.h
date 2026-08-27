//
//  ATAdManager+Native.h
//  AnyThinkNative
//
//  Created by Martin Lau on 07/07/2018.
//  Copyright © 2018 Martin Lau. All rights reserved.
//

#import <AnyThinkSDK/AnyThinkSDK.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *const kATNativeADAssetsAdvertiserKey;
extern NSString *const kATNativeADAssetsMainTextKey;
extern NSString *const kATNativeADAssetsMainTitleKey;
extern NSString *const kATNativeADAssetsMainImageKey;
extern NSString *const kATNativeADAssetsIconImageKey;
extern NSString *const kATNativeADAssetsLogoImageKey;
extern NSString *const kATNativeADAssetsCTATextKey;
extern NSString *const kATNativeADAssetsRatingKey;
extern NSString *const kATNativeADAssetsContainsVideoFlag;
extern NSString *const kATNativeADAssetsUnitIDKey;
extern NSString *const kATNativeADAssetsIconURLKey;
extern NSString *const kATNativeADAssetsImageURLKey;
extern NSString *const kATNativeADAssetsLogoURLKey;
extern NSString *const kATNativeADAssetsLogoViewKey;
extern NSString *const kATNativeADAssetsLogoSetKey;
extern NSString *const kATNativeADAssetsVideoUrlKey;
extern NSString *const kATAdAssetsCustomObjectKey;
extern NSString *const kATNativeADAssetsMediaViewKey;
extern NSString *const kATNativeADAssetsImageListKey;
extern NSString *const kATNativeADAssetsVideoDurationKey;
extern NSString *const kATNativeADAssetsVideoAspectRatioKey;
extern NSString *const kATNativeADAssetsNativeExpressAdViewWidthKey;
extern NSString *const kATNativeADAssetsNativeExpressAdViewHeightKey;
extern NSString *const kATNativeADAssetsInteractionTypeKey;
extern NSString *const kATNativeADAssetsVideoMutedTypeKey;
extern NSString *const kATNativeADAssetsMainImageWidthKey;
extern NSString *const kATNativeADAssetsMainImageHeightKey;
extern NSString *const kATNativeADAssetsMediaExtKey;
extern NSString *const kATNativeADAssetsSourceKey;
extern NSString *const kATNativeADAssetsCommentNumKey;
extern NSString *const kATNativeADAssetsAppSizeKey;
extern NSString *const kATNativeADAssetsAppPriceKey;
extern NSString *const kATNativeADAssetsDomainKey;
extern NSString *const kATNativeADAssetsWarningKey;
extern NSString *const kATNativeADAssetsIsExpressAdKey;

//Currently only GDT supports these two keys.
extern NSString *const kATExtraInfoNativeAdSizeKey;//the value has to be an NSValue wrapped CGSize object.
extern NSString *const kATExtraInfoNativeAdTypeKey;//The value is requried for GDT native ad and has to be an NSNumber warpped ATGDTNativeAdType(NSInteger); Pass @(ATGDTNativeAdTypeTemplate)(@1) for template ads and @(ATGDTNativeAdTypeSelfRendering)(@2) for self rendering ads.
//Following keys are supported by nend only  TODO_待优化至Nend Adapter
extern NSString *const kATExtraInfoNativeAdUserIDKey;
extern NSString *const kATExtraInfoNativeAdMediationNameKey;
extern NSString *const kATExtraInfoNaitveAdUserFeatureKey;
extern NSString *const kATExtraInfoNativeAdLocationEnabledFlagKey;

extern NSString *const kATNativeAdSizeToFitKey;
typedef NS_ENUM(NSInteger, ATGDTNativeAdType) {
    ATGDTNativeAdTypeTemplate = 1,
    ATGDTNativeAdTypeSelfRendering = 2
};
@class ATNativeADView;
@class ATNativeADConfiguration;
@class ATNativeAdOffer;

@interface ATAdManager (Native)

/// Get Native creative
- (nullable ATNativeAdOffer *)getNativeAdOfferWithPlacementID:(NSString *)placementID;

/// Get Native creative
/// @param placementID - TopOn's ad placement id
/// @param scene - scene id
- (nullable ATNativeAdOffer *)getNativeAdOfferWithPlacementID:(NSString *)placementID
                                                        scene:(NSString *)scene;

- (nullable ATNativeAdOffer *)getNativeAdOfferWithPlacementID:(NSString *)placementID
                                                   showConfig:(ATShowConfig *)showConfig;

/// check whether the native ad is ready
- (BOOL)nativeAdReadyForPlacementID:(NSString *)placementID;

/// Get the status object of the current ad slot ATCheckLoadModel
/// v5.7.06+
- (ATCheckLoadModel *)checkNativeLoadStatusForPlacementID:(NSString *)placementID;
/// Query all cached information of the ad slot
/// v5.7.53+
- (nullable NSArray<NSDictionary *> *)getNativeValidAdsForPlacementID:(NSString *)placementID;

///  Enter the current ad slot cache status statistics in the business scenario.
/// @param scene - ad Scenario
/// v5.7.91+
- (void)entryNativeScenarioWithPlacementID:(NSString *)placementID
                                     scene:(NSString *)scene;

@end

NS_ASSUME_NONNULL_END
