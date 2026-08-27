//
//  ATConstraintMaker.h
//  Masonry
//
//  Created by Jonas Budelmann on 20/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//

#import <AnyThinkSDK/ATConstraint.h>
#import <AnyThinkSDK/ATMasUtilities.h>

typedef NS_OPTIONS(NSInteger, ATAttribute) {
    ATAttributeLeft = 1 << NSLayoutAttributeLeft,
    ATAttributeRight = 1 << NSLayoutAttributeRight,
    ATAttributeTop = 1 << NSLayoutAttributeTop,
    ATAttributeBottom = 1 << NSLayoutAttributeBottom,
    ATAttributeLeading = 1 << NSLayoutAttributeLeading,
    ATAttributeTrailing = 1 << NSLayoutAttributeTrailing,
    ATAttributeWidth = 1 << NSLayoutAttributeWidth,
    ATAttributeHeight = 1 << NSLayoutAttributeHeight,
    ATAttributeCenterX = 1 << NSLayoutAttributeCenterX,
    ATAttributeCenterY = 1 << NSLayoutAttributeCenterY,
    ATAttributeBaseline = 1 << NSLayoutAttributeBaseline,

    ATAttributeFirstBaseline = 1 << NSLayoutAttributeFirstBaseline,
    ATAttributeLastBaseline = 1 << NSLayoutAttributeLastBaseline,
    
#if TARGET_OS_IPHONE || TARGET_OS_TV
    
    ATAttributeLeftMargin = 1 << NSLayoutAttributeLeftMargin,
    ATAttributeRightMargin = 1 << NSLayoutAttributeRightMargin,
    ATAttributeTopMargin = 1 << NSLayoutAttributeTopMargin,
    ATAttributeBottomMargin = 1 << NSLayoutAttributeBottomMargin,
    ATAttributeLeadingMargin = 1 << NSLayoutAttributeLeadingMargin,
    ATAttributeTrailingMargin = 1 << NSLayoutAttributeTrailingMargin,
    ATAttributeCenterXWithinMargins = 1 << NSLayoutAttributeCenterXWithinMargins,
    ATAttributeCenterYWithinMargins = 1 << NSLayoutAttributeCenterYWithinMargins,

#endif
    
};

/**
 *  Provides factory methods for creating ATConstraints.
 *  Constraints are collected until they are ready to be installed
 *
 */
@interface ATConstraintMaker : NSObject

/**
 *	The following properties return a new ATViewConstraint
 *  with the first item set to the makers associated view and the appropriate ATViewAttribute
 */
@property (nonatomic, strong, readonly) ATConstraint *left;
@property (nonatomic, strong, readonly) ATConstraint *top;
@property (nonatomic, strong, readonly) ATConstraint *right;
@property (nonatomic, strong, readonly) ATConstraint *bottom;
@property (nonatomic, strong, readonly) ATConstraint *leading;
@property (nonatomic, strong, readonly) ATConstraint *trailing;
@property (nonatomic, strong, readonly) ATConstraint *width;
@property (nonatomic, strong, readonly) ATConstraint *height;
@property (nonatomic, strong, readonly) ATConstraint *centerX;
@property (nonatomic, strong, readonly) ATConstraint *centerY;
@property (nonatomic, strong, readonly) ATConstraint *baseline;

@property (nonatomic, strong, readonly) ATConstraint *firstBaseline;
@property (nonatomic, strong, readonly) ATConstraint *lastBaseline;

#if TARGET_OS_IPHONE || TARGET_OS_TV

@property (nonatomic, strong, readonly) ATConstraint *leftMargin;
@property (nonatomic, strong, readonly) ATConstraint *rightMargin;
@property (nonatomic, strong, readonly) ATConstraint *topMargin;
@property (nonatomic, strong, readonly) ATConstraint *bottomMargin;
@property (nonatomic, strong, readonly) ATConstraint *leadingMargin;
@property (nonatomic, strong, readonly) ATConstraint *trailingMargin;
@property (nonatomic, strong, readonly) ATConstraint *centerXWithinMargins;
@property (nonatomic, strong, readonly) ATConstraint *centerYWithinMargins;

#endif

/**
 *  Returns a block which creates a new ATCompositeConstraint with the first item set
 *  to the makers associated view and children corresponding to the set bits in the
 *  ATAttribute parameter. Combine multiple attributes via binary-or.
 */
@property (nonatomic, copy, readonly) ATConstraint *(^attributes)(ATAttribute attrs);

/**
 *	Creates a ATCompositeConstraint with type ATCompositeConstraintTypeEdges
 *  which generates the appropriate ATViewConstraint children (top, left, bottom, right)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) ATConstraint *edges;

/**
 *	Creates a ATCompositeConstraint with type ATCompositeConstraintTypeSize
 *  which generates the appropriate ATViewConstraint children (width, height)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) ATConstraint *size;

/**
 *	Creates a ATCompositeConstraint with type ATCompositeConstraintTypeCenter
 *  which generates the appropriate ATViewConstraint children (centerX, centerY)
 *  with the first item set to the makers associated view
 */
@property (nonatomic, strong, readonly) ATConstraint *center;

/**
 *  Whether or not to check for an existing constraint instead of adding constraint
 */
@property (nonatomic, assign) BOOL updateExisting;

/**
 *  Whether or not to remove existing constraints prior to installing
 */
@property (nonatomic, assign) BOOL removeExisting;

/**
 *	initialises the maker with a default view
 *
 *	@param	view	any ATConstraint are created with this view as the first item
 *
 *	@return	a new ATConstraintMaker
 */
- (id)initWithView:(MAS_VIEW *)view;

/**
 *	Calls install method on any ATConstraints which have been created by this maker
 *
 *	@return	an array of all the installed ATConstraints
 */
- (NSArray *)install;

- (ATConstraint * (^)(dispatch_block_t))group;

@end
