//
//  NGPuzzle.h
//  excat_nonogarm
//
//  Core Nonogram puzzle data model.
//  Solution grid uses integer color indices: 0=empty, 1–8=filled with color N.
//  Row/column clues are computed automatically from the solution grid.

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

// ---------------------------------------------------------------------------
// NGPuzzleClue  –  a single clue segment (count + color)
// ---------------------------------------------------------------------------
@interface NGPuzzleClue : NSObject

/// Number of consecutive filled cells in this group.
@property (nonatomic, assign) NSInteger count;

/// 1-based index into the puzzle's colors array. 0 is unused.
@property (nonatomic, assign) NSInteger colorIndex;

+ (instancetype)clueWithCount:(NSInteger)count colorIndex:(NSInteger)colorIndex;

@end


// ---------------------------------------------------------------------------
// NGPuzzle  –  one Nonogram level
// ---------------------------------------------------------------------------
@interface NGPuzzle : NSObject

@property (nonatomic, assign) NSInteger rows;
@property (nonatomic, assign) NSInteger cols;

/// 2-D solution: solution[row][col] = colorIndex (0=empty, 1–8=filled).
@property (nonatomic, strong) NSArray<NSArray<NSNumber *> *> *solution;

/// Color palette for this puzzle. Index 0 = color for colorIndex 1, etc.
@property (nonatomic, strong) NSArray<UIColor *> *colors;

/// Human-readable name shown in the game header.
@property (nonatomic, strong) NSString *name;

/// 1-based level number.
@property (nonatomic, assign) NSInteger levelNumber;

/// Computed row clues (one array of NGPuzzleClue per row).
@property (nonatomic, strong, readonly) NSArray<NSArray<NGPuzzleClue *> *> *rowClues;

/// Computed column clues (one array of NGPuzzleClue per column).
@property (nonatomic, strong, readonly) NSArray<NSArray<NGPuzzleClue *> *> *colClues;

/// Maximum number of clue segments in any single row (used for layout sizing).
@property (nonatomic, assign, readonly) NSInteger maxRowClueCount;

/// Maximum number of clue segments in any single column (used for layout sizing).
@property (nonatomic, assign, readonly) NSInteger maxColClueCount;

/// Total filled cells (convenience for completion checking).
@property (nonatomic, assign, readonly) NSInteger totalFilledCells;

/**
 * Designated factory method.
 * @param rows      Grid row count.
 * @param cols      Grid column count.
 * @param flatGrid  Row-major array of (rows × cols) NSNumbers (colorIndex values).
 * @param colors    Puzzle-specific color palette (index 0 → colorIndex 1).
 * @param name      Puzzle display name.
 * @param level     1-based level number.
 */
+ (instancetype)puzzleWithRows:(NSInteger)rows
                          cols:(NSInteger)cols
                      flatGrid:(NSArray<NSNumber *> *)flatGrid
                        colors:(NSArray<UIColor *> *)colors
                          name:(NSString *)name
                         level:(NSInteger)level;

/**
 * Convenience factory that parses a compact grid string.
 * Format: rows separated by '|', each cell one digit (0–8).
 * Example 5×5: "00100|01110|11111|01110|00100"
 */
+ (instancetype)puzzleWithGridString:(NSString *)gridString
                              colors:(NSArray<UIColor *> *)colors
                                name:(NSString *)name
                               level:(NSInteger)level;

@end

NS_ASSUME_NONNULL_END
