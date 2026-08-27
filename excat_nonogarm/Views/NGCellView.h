//
//  NGCellView.h
//  excat_nonogarm
//
//  Represents a single cell in the Nonogram puzzle grid.
//
//  Cell states:
//    NGCellStateEmpty   – untouched, default grey
//    NGCellStateFilled  – player filled this cell (shows puzzle color)
//    NGCellStateMarkedX – player placed an X (cell is excluded)

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NGCellState) {
    NGCellStateEmpty    = 0,
    NGCellStateFilled   = 1,
    NGCellStateMarkedX  = 2,
};

@class NGCellView;

@protocol NGCellViewDelegate <NSObject>
/// Called when the user taps the cell.
- (void)cellViewDidTap:(NGCellView *)cellView;
@end

@interface NGCellView : UIView

@property (nonatomic, assign) NSInteger row;
@property (nonatomic, assign) NSInteger col;

/// Current display state.
@property (nonatomic, assign) NGCellState state;

/// The color to use when state == NGCellStateFilled.
@property (nonatomic, strong) UIColor *fillColor;

/// If YES the cell animates a brief error flash (wrong answer).
- (void)playErrorAnimation;

/// Brief success pulse animation (correct fill).
- (void)playSuccessAnimation;

@property (nonatomic, weak) id<NGCellViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
