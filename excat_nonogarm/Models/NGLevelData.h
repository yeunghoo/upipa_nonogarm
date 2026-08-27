//
//  NGLevelData.h
//  excat_nonogarm
//
//  Provides all 99 Nonogram puzzle definitions.
//  Levels 1-15   : 5×5  grids (1 color) — basic shapes
//  Levels 16-30  : 7×7  grids (1 color) — medium shapes
//  Levels 31-45  : 7×7  grids (2 colors) — simple pixel art
//  Levels 46-60  : 10×10 grids (2 colors) — pixel art
//  Levels 61-72  : 10×10 grids (3 colors) — multi-color pixel art
//  Levels 73-85  : 15×15 grids (3-4 colors) — detailed art
//  Levels 86-99  : 20×20 grids (3-5 colors) — complex art

#import <Foundation/Foundation.h>
#import "NGPuzzle.h"

NS_ASSUME_NONNULL_BEGIN

@interface NGLevelData : NSObject

/// Returns all 99 puzzles in order (index 0 = Level 1).
+ (NSArray<NGPuzzle *> *)allLevels;

/// Returns the puzzle for a specific 1-based level number.
+ (nullable NGPuzzle *)puzzleForLevel:(NSInteger)level;

/// Total number of levels.
+ (NSInteger)totalLevelCount;

@end

NS_ASSUME_NONNULL_END
