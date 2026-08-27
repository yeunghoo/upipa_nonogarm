//
//  UIView+ATAdditions.h
//  Masonry
//
//  Created by Jonas Budelmann on 20/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//

#import <AnyThinkSDK/ATMasUtilities.h>
#import <AnyThinkSDK/ATConstraintMaker.h>
#import <AnyThinkSDK/ATViewAttribute.h>

/**
 *	Provides constraint maker block
 *  and convience methods for creating ATViewAttribute which are view + NSLayoutAttribute pairs
 */
@interface MAS_VIEW (ATAdditions)

/**
 *	following properties return a new ATViewAttribute with current view and appropriate NSLayoutAttribute
 */
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_left;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_top;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_right;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_bottom;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_leading;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_trailing;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_width;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_height;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_centerX;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_centerY;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_baseline;
@property (nonatomic, copy, readonly) ATViewAttribute *(^AT_mas_attribute)(NSLayoutAttribute attr);

@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_firstBaseline;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_lastBaseline;

#if TARGET_OS_IPHONE || TARGET_OS_TV

@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_leftMargin;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_rightMargin;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_topMargin;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_bottomMargin;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_leadingMargin;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_trailingMargin;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_centerXWithinMargins;
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_centerYWithinMargins;

@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuide NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideLeading NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideTrailing NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideLeft NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideRight NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideTop NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideBottom NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideWidth NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideHeight NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideCenterX NS_AVAILABLE_IOS(11.0);
@property (nonatomic, strong, readonly) ATViewAttribute *AT_mas_safeAreaLayoutGuideCenterY NS_AVAILABLE_IOS(11.0);

#endif

/**
 *	a key to associate with this view
 */
@property (nonatomic, strong) id AT_mas_key;

/**
 *	Finds the closest common superview between this view and another view
 *
 *	@param	view	other view
 *
 *	@return	returns nil if common superview could not be found
 */
- (instancetype)AT_mas_closestCommonSuperview:(MAS_VIEW *)view;

/**
 *  Creates a ATConstraintMaker with the callee view.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to the view.
 *
 *  @return Array of created ATConstraints
 */
- (NSArray *)AT_mas_makeConstraints:(void(NS_NOESCAPE ^)(ATConstraintMaker *make))block;

/**
 *  Creates a ATConstraintMaker with the callee view.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing.
 *  If an existing constraint exists then it will be updated instead.
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to the view.
 *
 *  @return Array of created/updated ATConstraints
 */
- (NSArray *)AT_mas_updateConstraints:(void(NS_NOESCAPE ^)(ATConstraintMaker *make))block;

/**
 *  Creates a ATConstraintMaker with the callee view.
 *  Any constraints defined are added to the view or the appropriate superview once the block has finished executing.
 *  All constraints previously installed for the view will be removed.
 *
 *  @param block scope within which you can build up the constraints which you wish to apply to the view.
 *
 *  @return Array of created/updated ATConstraints
 */
- (NSArray *)AT_mas_remakeConstraints:(void(NS_NOESCAPE ^)(ATConstraintMaker *make))block;

@end
