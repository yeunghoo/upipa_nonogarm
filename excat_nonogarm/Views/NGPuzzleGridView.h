//
//  NGPuzzleGridView.h
//  excat_nonogarm
//
//  The full puzzle board: column clues (top) + row clues (left) + cell grid.
//  Supports adaptive sizing for all iPhone and iPad screen sizes.

#import <UIKit/UIKit.h>
#import "NGPuzzle.h"
#import "NGCellView.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NGFillMode) {
    NGFillModeFill = 0,   // tap to fill a cell
    NGFillModeMarkX = 1,  // tap to place X on a cell
};

@class NGPuzzleGridView;

@protocol NGPuzzleGridViewDelegate <NSObject>
/// Called when the player taps a cell.
/// @param correct YES if the action matches the solution.
- (void)puzzleGridView:(NGPuzzleGridView *)gridView
      didTapCellAtRow:(NSInteger)row
                  col:(NSInteger)col
              correct:(BOOL)correct;

/// Called when all filled cells have been correctly placed.
- (void)puzzleGridViewDidComplete:(NGPuzzleGridView *)gridView;
@end

@interface NGPuzzleGridView : UIView

/// The puzzle being displayed.
@property (nonatomic, strong) NGPuzzle *puzzle;

/// Current fill mode (fill vs mark-X).
@property (nonatomic, assign) NGFillMode fillMode;

/// Currently selected color index (1-based; ignored for single-color puzzles).
@property (nonatomic, assign) NSInteger selectedColorIndex;

/// Delegate for game events.
@property (nonatomic, weak) id<NGPuzzleGridViewDelegate> delegate;

/// Initialize with a puzzle. Call this instead of setting puzzle property directly.
- (void)loadPuzzle:(NGPuzzle *)puzzle;

/// Returns a snapshot of the current player grid state (2-D array of NGCellState values).
- (NSArray<NSArray<NSNumber *> *> *)currentCellStates;

/// Reveal the completed puzzle (e.g., on level completion).
- (void)revealSolution;

/// Show a semi-transparent hint stripe on one unsolved row or column.
/// Returns YES if a hint was shown, NO if puzzle is already solved.
- (BOOL)showHintStripe;

@end

NS_ASSUME_NONNULL_END
