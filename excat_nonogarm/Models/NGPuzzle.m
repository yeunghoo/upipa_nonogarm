//
//  NGPuzzle.m
//  excat_nonogarm

#import "NGPuzzle.h"

// ---------------------------------------------------------------------------
#pragma mark - NGPuzzleClue
// ---------------------------------------------------------------------------

@implementation NGPuzzleClue

+ (instancetype)clueWithCount:(NSInteger)count colorIndex:(NSInteger)colorIndex {
    NGPuzzleClue *c = [[NGPuzzleClue alloc] init];
    c.count = count;
    c.colorIndex = colorIndex;
    return c;
}

- (NSString *)description {
    return [NSString stringWithFormat:@"Clue(%ld,c%ld)", (long)self.count, (long)self.colorIndex];
}

@end


// ---------------------------------------------------------------------------
#pragma mark - NGPuzzle
// ---------------------------------------------------------------------------

// Redeclare the readonly public properties as readwrite internally.
// Property names MUST match the public header exactly so auto-synthesis
// maps them to the same ivar (e.g. rowClues -> _rowClues).
@interface NGPuzzle ()
@property (nonatomic, strong) NSArray<NSArray<NGPuzzleClue *> *> *rowClues;
@property (nonatomic, strong) NSArray<NSArray<NGPuzzleClue *> *> *colClues;
@property (nonatomic, assign) NSInteger maxRowClueCount;
@property (nonatomic, assign) NSInteger maxColClueCount;
@property (nonatomic, assign) NSInteger totalFilledCells;
@end

@implementation NGPuzzle

+ (instancetype)puzzleWithRows:(NSInteger)rows
                          cols:(NSInteger)cols
                      flatGrid:(NSArray<NSNumber *> *)flatGrid
                        colors:(NSArray<UIColor *> *)colors
                          name:(NSString *)name
                         level:(NSInteger)level {
    NGPuzzle *puzzle = [[NGPuzzle alloc] init];
    puzzle.rows = rows;
    puzzle.cols = cols;
    puzzle.colors = colors;
    puzzle.name = name;
    puzzle.levelNumber = level;

    // Build 2-D solution array
    NSMutableArray *solution = [NSMutableArray arrayWithCapacity:rows];
    for (NSInteger r = 0; r < rows; r++) {
        NSMutableArray *row = [NSMutableArray arrayWithCapacity:cols];
        for (NSInteger c = 0; c < cols; c++) {
            NSInteger idx = r * cols + c;
            [row addObject:(idx < (NSInteger)flatGrid.count) ? flatGrid[idx] : @0];
        }
        [solution addObject:[row copy]];
    }
    puzzle.solution = [solution copy];

    [puzzle computeClues];
    return puzzle;
}

+ (instancetype)puzzleWithGridString:(NSString *)gridString
                              colors:(NSArray<UIColor *> *)colors
                                name:(NSString *)name
                               level:(NSInteger)level {
    NSArray<NSString *> *rowStrings = [gridString componentsSeparatedByString:@"|"];
    NSInteger rows = rowStrings.count;
    NSInteger cols = rows > 0 ? (NSInteger)rowStrings[0].length : 0;

    NSMutableArray *flatGrid = [NSMutableArray arrayWithCapacity:rows * cols];
    for (NSString *rowStr in rowStrings) {
        for (NSInteger i = 0; i < (NSInteger)rowStr.length; i++) {
            unichar ch = [rowStr characterAtIndex:i];
            NSInteger val = (ch >= '0' && ch <= '9') ? (ch - '0') : 0;
            [flatGrid addObject:@(val)];
        }
    }

    return [self puzzleWithRows:rows
                           cols:cols
                       flatGrid:flatGrid
                         colors:colors
                           name:name
                          level:level];
}

- (void)computeClues {
    _rowClues = [self buildRowClues];
    _colClues = [self buildColClues];

    NSInteger maxRow = 0;
    for (NSArray *clues in _rowClues) {
        maxRow = MAX(maxRow, (NSInteger)clues.count);
    }
    _maxRowClueCount = MAX(maxRow, 1);

    NSInteger maxCol = 0;
    for (NSArray *clues in _colClues) {
        maxCol = MAX(maxCol, (NSInteger)clues.count);
    }
    _maxColClueCount = MAX(maxCol, 1);

    NSInteger total = 0;
    for (NSArray<NSNumber *> *row in self.solution) {
        for (NSNumber *cell in row) {
            if (cell.integerValue > 0) total++;
        }
    }
    _totalFilledCells = total;
}

/// Compute clues for a sequence of cells (used for both rows and columns).
- (NSArray<NGPuzzleClue *> *)cluesForCells:(NSArray<NSNumber *> *)cells {
    NSMutableArray<NGPuzzleClue *> *clues = [NSMutableArray array];
    NSInteger currentColor = 0;
    NSInteger currentCount = 0;

    for (NSNumber *cell in cells) {
        NSInteger val = cell.integerValue;
        if (val == 0) {
            if (currentCount > 0) {
                [clues addObject:[NGPuzzleClue clueWithCount:currentCount colorIndex:currentColor]];
                currentCount = 0;
                currentColor = 0;
            }
        } else {
            if (currentColor != val && currentCount > 0) {
                // Color change mid-sequence (no gap needed between different colors)
                [clues addObject:[NGPuzzleClue clueWithCount:currentCount colorIndex:currentColor]];
                currentCount = 1;
                currentColor = val;
            } else {
                currentCount++;
                currentColor = val;
            }
        }
    }
    if (currentCount > 0) {
        [clues addObject:[NGPuzzleClue clueWithCount:currentCount colorIndex:currentColor]];
    }

    return [clues copy];
}

- (NSArray<NSArray<NGPuzzleClue *> *> *)buildRowClues {
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:self.rows];
    for (NSInteger r = 0; r < self.rows; r++) {
        NSArray<NGPuzzleClue *> *clues = [self cluesForCells:self.solution[r]];
        [result addObject:clues];
    }
    return [result copy];
}

- (NSArray<NSArray<NGPuzzleClue *> *> *)buildColClues {
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:self.cols];
    for (NSInteger c = 0; c < self.cols; c++) {
        NSMutableArray *colCells = [NSMutableArray arrayWithCapacity:self.rows];
        for (NSInteger r = 0; r < self.rows; r++) {
            [colCells addObject:self.solution[r][c]];
        }
        NSArray<NGPuzzleClue *> *clues = [self cluesForCells:colCells];
        [result addObject:clues];
    }
    return [result copy];
}

@end
