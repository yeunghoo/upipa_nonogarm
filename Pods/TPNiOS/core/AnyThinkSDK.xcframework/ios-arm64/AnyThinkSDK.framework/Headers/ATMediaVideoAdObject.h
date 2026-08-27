//
//  ATMediaVideoAdObject.h
//  AnyThinkSDK
//
//  Created by zhouzhenhua on 2025/2/17.
//  Copyright © 2025 AnyThink. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ATMediaVideoAdType) {
    ATMediaVideoAdTypeUnknow,
    ATMediaVideoAdTypeVAST,
    ATMediaVideoAdTypeVMAP,
};

@interface ATMediaVideoAdObject : NSObject

@property (nonatomic, assign) ATMediaVideoAdType type;

- (void)updateContentPlayhead:(id)contentPlayhead;

- (void)updateAdDisplayContainerViewController:(UIViewController *)viewController;

- (id)getAdsManager;

/**
 * Starts advertisement playback.
 */
- (void)start;

/**
 * Pauses advertisement.
 */
- (void)pause;

/**
 * Resumes the advertisement.
 */
- (void)resume;

/**
 * Skips the advertisement if the ad is skippable and the skip offset has been reached.
 */
- (void)skip;

/**
 * Performs a clickthrough on the advertisement if the UI was successfully disabled via
 * AdsRenderingSettings.disableUi.
 * :nodoc:
 */
- (void)clicked;

/**
 * Causes the ads manager to stop the ad and clean its internal state.
 */
- (void)destroy;

/**
 * If an ad break is currently playing, discard it and resume content.
 * Otherwise, ignore the next scheduled ad break.
 */
- (void)discardAdBreak;

/**
 * Signal to the SDK that the content has completed. The SDK will play
 * post-rolls at this time, if any are scheduled.
 */
- (void)contentComplete;

/**
 * Registers a view that overlays or obstructs this container as "friendly" for viewability
 * measurement purposes.
 */
- (void)registerFriendlyObstruction:(id)friendlyObstruction;

/**
 * Unregisters all previously registered friendly obstructions.
 */
- (void)unregisterAllFriendlyObstructions;

@end

NS_ASSUME_NONNULL_END
