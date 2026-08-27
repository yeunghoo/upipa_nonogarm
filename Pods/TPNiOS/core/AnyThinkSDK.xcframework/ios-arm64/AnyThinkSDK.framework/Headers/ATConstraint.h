//
//  ATConstraint.h
//  Masonry
//
//  Created by Jonas Budelmann on 22/07/13.
//  Copyright (c) 2013 cloudling. All rights reserved.
//
#import <AnyThinkSDK/ATMasUtilities.h>
/**
 *	Enables Constraints to be created with chainable syntax
 *  Constraint can represent single NSLayoutConstraint (ATViewConstraint) 
 *  or a group of NSLayoutConstraints (MASComposisteConstraint)
 */
@interface ATConstraint : NSObject

// Chaining Support

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeTop, NSLayoutAttributeLeft, NSLayoutAttributeBottom, NSLayoutAttributeRight
 */
- (ATConstraint * (^)(MASEdgeInsets insets))insets;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeTop, NSLayoutAttributeLeft, NSLayoutAttributeBottom, NSLayoutAttributeRight
 */
- (ATConstraint * (^)(CGFloat inset))inset;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeWidth, NSLayoutAttributeHeight
 */
- (ATConstraint * (^)(CGSize offset))sizeOffset;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeCenterX, NSLayoutAttributeCenterY
 */
- (ATConstraint * (^)(CGPoint offset))centerOffset;

/**
 *	Modifies the NSLayoutConstraint constant
 */
- (ATConstraint * (^)(CGFloat offset))offset;

/**
 *  Modifies the NSLayoutConstraint constant based on a value type
 */
- (ATConstraint * (^)(NSValue *value))valueOffset;

/**
 *	Sets the NSLayoutConstraint multiplier property
 */
- (ATConstraint * (^)(CGFloat multiplier))multipliedBy;

/**
 *	Sets the NSLayoutConstraint multiplier to 1.0/dividedBy
 */
- (ATConstraint * (^)(CGFloat divider))dividedBy;

/**
 *	Sets the NSLayoutConstraint priority to a float or MASLayoutPriority
 */
- (ATConstraint * (^)(MASLayoutPriority priority))priority;

/**
 *	Sets the NSLayoutConstraint priority to MASLayoutPriorityLow
 */
- (ATConstraint * (^)(void))priorityLow;

/**
 *	Sets the NSLayoutConstraint priority to MASLayoutPriorityMedium
 */
- (ATConstraint * (^)(void))priorityMedium;

/**
 *	Sets the NSLayoutConstraint priority to MASLayoutPriorityHigh
 */
- (ATConstraint * (^)(void))priorityHigh;

/**
 *	Sets the constraint relation to NSLayoutRelationEqual
 *  returns a block which accepts one of the following:
 *    ATViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (ATConstraint * (^)(id attr))equalTo;

/**
 *	Sets the constraint relation to NSLayoutRelationGreaterThanOrEqual
 *  returns a block which accepts one of the following:
 *    ATViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (ATConstraint * (^)(id attr))greaterThanOrEqualTo;

/**
 *	Sets the constraint relation to NSLayoutRelationLessThanOrEqual
 *  returns a block which accepts one of the following:
 *    ATViewAttribute, UIView, NSValue, NSArray
 *  see readme for more details.
 */
- (ATConstraint * (^)(id attr))lessThanOrEqualTo;

/**
 *	Optional semantic property which has no effect but improves the readability of constraint
 */
- (ATConstraint *)with;

/**
 *	Optional semantic property which has no effect but improves the readability of constraint
 */
- (ATConstraint *)and;

/**
 *	Creates a new ATCompositeConstraint with the called attribute and reciever
 */
- (ATConstraint *)left;
- (ATConstraint *)top;
- (ATConstraint *)right;
- (ATConstraint *)bottom;
- (ATConstraint *)leading;
- (ATConstraint *)trailing;
- (ATConstraint *)width;
- (ATConstraint *)height;
- (ATConstraint *)centerX;
- (ATConstraint *)centerY;
- (ATConstraint *)baseline;

- (ATConstraint *)firstBaseline;
- (ATConstraint *)lastBaseline;

#if TARGET_OS_IPHONE || TARGET_OS_TV

- (ATConstraint *)leftMargin;
- (ATConstraint *)rightMargin;
- (ATConstraint *)topMargin;
- (ATConstraint *)bottomMargin;
- (ATConstraint *)leadingMargin;
- (ATConstraint *)trailingMargin;
- (ATConstraint *)centerXWithinMargins;
- (ATConstraint *)centerYWithinMargins;

#endif


/**
 *	Sets the constraint debug name
 */
- (ATConstraint * (^)(id key))key;

// NSLayoutConstraint constant Setters
// for use outside of mas_updateConstraints/mas_makeConstraints blocks

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeTop, NSLayoutAttributeLeft, NSLayoutAttributeBottom, NSLayoutAttributeRight
 */
- (void)setInsets:(MASEdgeInsets)insets;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeTop, NSLayoutAttributeLeft, NSLayoutAttributeBottom, NSLayoutAttributeRight
 */
- (void)setInset:(CGFloat)inset;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeWidth, NSLayoutAttributeHeight
 */
- (void)setSizeOffset:(CGSize)sizeOffset;

/**
 *	Modifies the NSLayoutConstraint constant,
 *  only affects ATConstraints in which the first item's NSLayoutAttribute is one of the following
 *  NSLayoutAttributeCenterX, NSLayoutAttributeCenterY
 */
- (void)setCenterOffset:(CGPoint)centerOffset;

/**
 *	Modifies the NSLayoutConstraint constant
 */
- (void)setOffset:(CGFloat)offset;


// NSLayoutConstraint Installation support

#if TARGET_OS_MAC && !(TARGET_OS_IPHONE || TARGET_OS_TV)
/**
 *  Whether or not to go through the animator proxy when modifying the constraint
 */
@property (nonatomic, copy, readonly) ATConstraint *animator;
#endif

/**
 *  Activates an NSLayoutConstraint if it's supported by an OS. 
 *  Invokes install otherwise.
 */
- (void)activate;

/**
 *  Deactivates previously installed/activated NSLayoutConstraint.
 */
- (void)deactivate;

/**
 *	Creates a NSLayoutConstraint and adds it to the appropriate view.
 */
- (void)install;

/**
 *	Removes previously installed NSLayoutConstraint
 */
- (void)uninstall;

@end


/**
 *  Convenience auto-boxing macros for ATConstraint methods.
 *
 *  Defining MAS_SHORTHAND_GLOBALS will turn on auto-boxing for default syntax.
 *  A potential drawback of this is that the unprefixed macros will appear in global scope.
 */
#define mas_equalTo(...)                 equalTo(MASBoxValue((__VA_ARGS__)))
#define mas_greaterThanOrEqualTo(...)    greaterThanOrEqualTo(MASBoxValue((__VA_ARGS__)))
#define mas_lessThanOrEqualTo(...)       lessThanOrEqualTo(MASBoxValue((__VA_ARGS__)))

#define mas_offset(...)                  valueOffset(MASBoxValue((__VA_ARGS__)))


#ifdef MAS_SHORTHAND_GLOBALS

#define equalTo(...)                     mas_equalTo(__VA_ARGS__)
#define greaterThanOrEqualTo(...)        mas_greaterThanOrEqualTo(__VA_ARGS__)
#define lessThanOrEqualTo(...)           mas_lessThanOrEqualTo(__VA_ARGS__)

#define offset(...)                      mas_offset(__VA_ARGS__)

#endif


@interface ATConstraint (AutoboxingSupport)

/**
 *  Aliases to corresponding relation methods (for shorthand macros)
 *  Also needed to aid autocompletion
 */
- (ATConstraint * (^)(id attr))mas_equalTo;
- (ATConstraint * (^)(id attr))mas_greaterThanOrEqualTo;
- (ATConstraint * (^)(id attr))mas_lessThanOrEqualTo;

/**
 *  A dummy method to aid autocompletion
 */
- (ATConstraint * (^)(id offset))mas_offset;

@end
