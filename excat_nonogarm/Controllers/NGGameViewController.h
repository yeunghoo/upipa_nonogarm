//
//  NGGameViewController.h
//  excat_nonogarm
//
//  The main game screen that hosts the puzzle grid, lives display,
//  fill/mark-X toggle, and color palette for multi-color levels.

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NGGameViewController : UIViewController

/// 1-based level number to load when the view appears.
@property (nonatomic, assign) NSInteger levelNumber;

/// Designated initializer.
- (instancetype)initWithLevel:(NSInteger)level;

@end

NS_ASSUME_NONNULL_END
