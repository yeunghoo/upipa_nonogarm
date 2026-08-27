//
//  NGPuzzleGridView.m
//  excat_nonogarm

#import "NGPuzzleGridView.h"
#import "NGTheme.h"

// ---------------------------------------------------------------------------
// Layout constants
// ---------------------------------------------------------------------------
static const CGFloat kCluePadding      = 2.0;   // padding inside clue cells
static const CGFloat kGridGap          = 1.0;   // gap between cells
static const CGFloat kClueRatio        = 0.75;  // clue cell = cellSize * kClueRatio
static const CGFloat kGroupLineThick   = 2.0;   // thicker lines every 5 cells
static const NSInteger kGroupLineEvery = 5;

@interface NGPuzzleGridView () <NGCellViewDelegate>
// Layout state
@property (nonatomic, assign) CGFloat cellSize;
@property (nonatomic, assign) CGFloat clueSize;
@property (nonatomic, assign) CGFloat rowClueAreaWidth;
@property (nonatomic, assign) CGFloat colClueAreaHeight;

// Cell grid
@property (nonatomic, strong) NSMutableArray<NSMutableArray<NGCellView *> *> *cellViews;

// Player state: 2-D array of colorIndex filled (0=empty, -1=X, >0=filled)
@property (nonatomic, strong) NSMutableArray<NSMutableArray<NSNumber *> *> *playerGrid;

// Clue completion tracking
@property (nonatomic, strong) NSMutableArray<NSNumber *> *rowClueComplete; // BOOL per row
@property (nonatomic, strong) NSMutableArray<NSNumber *> *colClueComplete; // BOOL per col
@property (nonatomic, strong) NSMutableArray<NSMutableArray<UILabel *> *> *rowClueLabels;
@property (nonatomic, strong) NSMutableArray<NSMutableArray<UILabel *> *> *colClueLabels;

@property (nonatomic, assign) NSInteger correctFilledCount;
@end

@implementation NGPuzzleGridView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        self.backgroundColor = [NGTheme gridBackgroundColor];
        _fillMode = NGFillModeFill;
        _selectedColorIndex = 1;
    }
    return self;
}

// ---------------------------------------------------------------------------
#pragma mark - Public
// ---------------------------------------------------------------------------

- (void)loadPuzzle:(NGPuzzle *)puzzle {
    // Remove existing subviews
    for (UIView *v in self.subviews) {
        [v removeFromSuperview];
    }

    _puzzle = puzzle;
    _correctFilledCount = 0;
    _selectedColorIndex = (puzzle.colors.count > 0) ? 1 : 1;

    // Initialize player grid (0 = untouched)
    NSMutableArray *pg = [NSMutableArray arrayWithCapacity:puzzle.rows];
    for (NSInteger r = 0; r < puzzle.rows; r++) {
        NSMutableArray *row = [NSMutableArray arrayWithCapacity:puzzle.cols];
        for (NSInteger c = 0; c < puzzle.cols; c++) {
            [row addObject:@0];
        }
        [pg addObject:row];
    }
    _playerGrid = pg;

    _rowClueComplete = [NSMutableArray arrayWithCapacity:puzzle.rows];
    _colClueComplete = [NSMutableArray arrayWithCapacity:puzzle.cols];
    for (NSInteger i = 0; i < puzzle.rows; i++) [_rowClueComplete addObject:@NO];
    for (NSInteger i = 0; i < puzzle.cols; i++) [_colClueComplete addObject:@NO];

    [self calculateLayout];
    [self buildUI];
    [self setNeedsLayout];
}

- (NSArray<NSArray<NSNumber *> *> *)currentCellStates {
    return [_playerGrid copy];
}

- (void)revealSolution {
    for (NSInteger r = 0; r < _puzzle.rows; r++) {
        for (NSInteger c = 0; c < _puzzle.cols; c++) {
            NSInteger solutionColor = [_puzzle.solution[r][c] integerValue];
            NGCellView *cell = _cellViews[r][c];
            if (solutionColor > 0) {
                cell.fillColor = [self colorForIndex:solutionColor];
                cell.state = NGCellStateFilled;
            } else {
                cell.state = NGCellStateEmpty;
            }
        }
    }
    [self markAllCluesComplete];
}

// ---------------------------------------------------------------------------
#pragma mark - Layout calculation
// ---------------------------------------------------------------------------

- (void)calculateLayout {
    NGPuzzle *p = _puzzle;
    NSInteger maxRowClues = p.maxRowClueCount;
    NSInteger maxColClues = p.maxColClueCount;

    CGFloat availWidth  = self.bounds.size.width  > 0 ? self.bounds.size.width  : UIScreen.mainScreen.bounds.size.width;
    CGFloat availHeight = self.bounds.size.height > 0 ? self.bounds.size.height : UIScreen.mainScreen.bounds.size.height - 200;

    // Compute optimal cell size directly:
    //   totalWidth  = maxRowClues * cs * kClueRatio + cols * cs + (cols-1) * gap
    //               = cs * (maxRowClues * kClueRatio + cols) + (cols-1) * gap
    //   => cs = (availWidth - (cols-1)*gap) / (maxRowClues*kClueRatio + cols)
    CGFloat cellByW = (availWidth  - (p.cols - 1) * kGridGap) / (maxRowClues * kClueRatio + p.cols);
    CGFloat cellByH = (availHeight - (p.rows - 1) * kGridGap) / (maxColClues * kClueRatio + p.rows);

    CGFloat cs = floor(MIN(cellByW, cellByH));
    cs = MAX(cs, 12.0); // minimum 12pt — remains tap-friendly

    _cellSize          = cs;
    _clueSize          = cs * kClueRatio;
    _rowClueAreaWidth  = maxRowClues * _clueSize;
    _colClueAreaHeight = maxColClues * _clueSize;
}

// ---------------------------------------------------------------------------
#pragma mark - Build UI
// ---------------------------------------------------------------------------

- (void)buildUI {
    [self buildClueLabels];
    [self buildCells];
}

- (void)buildClueLabels {
    NGPuzzle *p = _puzzle;
    _rowClueLabels = [NSMutableArray arrayWithCapacity:p.rows];
    _colClueLabels = [NSMutableArray arrayWithCapacity:p.cols];

    CGFloat clueFont = MAX(_clueSize * 0.55, 7.0);

    // Row clue labels
    for (NSInteger r = 0; r < p.rows; r++) {
        NSArray<NGPuzzleClue *> *clues = p.rowClues[r];
        NSMutableArray *labels = [NSMutableArray array];
        for (NGPuzzleClue *clue in clues) {
            UILabel *lbl = [self makeClueLabel:clue fontSize:clueFont];
            [self addSubview:lbl];
            [labels addObject:lbl];
        }
        [_rowClueLabels addObject:labels];
    }

    // Column clue labels
    for (NSInteger c = 0; c < p.cols; c++) {
        NSArray<NGPuzzleClue *> *clues = p.colClues[c];
        NSMutableArray *labels = [NSMutableArray array];
        for (NGPuzzleClue *clue in clues) {
            UILabel *lbl = [self makeClueLabel:clue fontSize:clueFont];
            [self addSubview:lbl];
            [labels addObject:lbl];
        }
        [_colClueLabels addObject:labels];
    }
}

- (UILabel *)makeClueLabel:(NGPuzzleClue *)clue fontSize:(CGFloat)fontSize {
    UILabel *lbl = [[UILabel alloc] init];
    lbl.text = [NSString stringWithFormat:@"%ld", (long)clue.count];
    lbl.font = [NGTheme clueFontWithSize:fontSize];
    lbl.textAlignment = NSTextAlignmentCenter;

    if (clue.colorIndex > 0 && clue.colorIndex <= (NSInteger)_puzzle.colors.count) {
        lbl.textColor = _puzzle.colors[clue.colorIndex - 1];
    } else {
        lbl.textColor = [NGTheme clueTextColor];
    }
    lbl.backgroundColor = [NGTheme clueBackgroundColor];
    lbl.layer.cornerRadius = 2.0;
    lbl.clipsToBounds = YES;
    return lbl;
}

- (void)buildCells {
    NGPuzzle *p = _puzzle;
    _cellViews = [NSMutableArray arrayWithCapacity:p.rows];

    for (NSInteger r = 0; r < p.rows; r++) {
        NSMutableArray *rowViews = [NSMutableArray arrayWithCapacity:p.cols];
        for (NSInteger c = 0; c < p.cols; c++) {
            NGCellView *cell = [[NGCellView alloc] initWithFrame:CGRectZero];
            cell.row = r;
            cell.col = c;
            cell.delegate = self;
            cell.state = NGCellStateEmpty;
            [self addSubview:cell];
            [rowViews addObject:cell];
        }
        [_cellViews addObject:rowViews];
    }
}

// ---------------------------------------------------------------------------
#pragma mark - Layout
// ---------------------------------------------------------------------------

- (void)layoutSubviews {
    [super layoutSubviews];

    if (!_puzzle) return;
    [self calculateLayout];

    NGPuzzle *p = _puzzle;
    CGFloat cs = _cellSize;
    CGFloat qs = _clueSize;
    CGFloat rawW = _rowClueAreaWidth;
    CGFloat rawH = _colClueAreaHeight;

    // Center the whole puzzle inside the view
    CGFloat totalW = rawW + p.cols * cs + (p.cols - 1) * kGridGap;
    CGFloat totalH = rawH + p.rows * cs + (p.rows - 1) * kGridGap;
    CGFloat ox = MAX(0, (self.bounds.size.width  - totalW) * 0.5);
    CGFloat oy = MAX(0, (self.bounds.size.height - totalH) * 0.5);

    // ---- Row clue labels ----
    NSInteger maxRowClues = p.maxRowClueCount;
    CGFloat clueFont = MAX(qs * 0.55, 7.0);

    for (NSInteger r = 0; r < p.rows; r++) {
        NSArray<UILabel *> *labels = _rowClueLabels[r];
        CGFloat cellY = oy + rawH + r * (cs + kGridGap);
        // Right-align clues inside the row clue area
        NSInteger offset = (NSInteger)(maxRowClues - labels.count);
        for (NSInteger i = 0; i < (NSInteger)labels.count; i++) {
            UILabel *lbl = labels[i];
            lbl.font = [NGTheme clueFontWithSize:clueFont];
            CGFloat lx = ox + (offset + i) * qs + kCluePadding;
            lbl.frame = CGRectMake(lx, cellY + (cs - qs) * 0.5, qs - kCluePadding, qs);
        }
    }

    // ---- Column clue labels ----
    NSInteger maxColClues = p.maxColClueCount;
    for (NSInteger c = 0; c < p.cols; c++) {
        NSArray<UILabel *> *labels = _colClueLabels[c];
        CGFloat cellX = ox + rawW + c * (cs + kGridGap);
        NSInteger offset = (NSInteger)(maxColClues - labels.count);
        for (NSInteger i = 0; i < (NSInteger)labels.count; i++) {
            UILabel *lbl = labels[i];
            lbl.font = [NGTheme clueFontWithSize:clueFont];
            CGFloat ly = oy + (offset + i) * qs + kCluePadding;
            lbl.frame = CGRectMake(cellX + (cs - qs) * 0.5, ly, qs, qs - kCluePadding);
        }
    }

    // ---- Cells ----
    for (NSInteger r = 0; r < p.rows; r++) {
        for (NSInteger c = 0; c < p.cols; c++) {
            NGCellView *cell = _cellViews[r][c];
            CGFloat cx = ox + rawW + c * (cs + kGridGap);
            CGFloat cy = oy + rawH + r * (cs + kGridGap);
            cell.frame = CGRectMake(cx, cy, cs, cs);
        }
    }
}

// ---------------------------------------------------------------------------
#pragma mark - Cell tap handling
// ---------------------------------------------------------------------------

- (void)cellViewDidTap:(NGCellView *)cellView {
    NSInteger r = cellView.row;
    NSInteger c = cellView.col;
    NSInteger solutionColor = [_puzzle.solution[r][c] integerValue];
    NSInteger currentPlayer = [_playerGrid[r][c] integerValue];

    if (_fillMode == NGFillModeFill) {
        if (currentPlayer > 0) {
            // Already filled – unfill
            _playerGrid[r][c] = @0;
            if (solutionColor > 0) _correctFilledCount--;
            cellView.state = NGCellStateEmpty;
            [self checkClueCompletionForRow:r col:c];
            return;
        }
        if (currentPlayer == -1) {
            // Was X – remove X first, then fill
            _playerGrid[r][c] = @0;
        }

        // Determine the color to fill with
        NSInteger fillColorIdx;
        if (_puzzle.colors.count <= 1) {
            fillColorIdx = 1; // single color puzzle
        } else {
            fillColorIdx = _selectedColorIndex;
        }

        BOOL correct = (solutionColor > 0) && (fillColorIdx == solutionColor);

        if (correct) {
            _playerGrid[r][c] = @(solutionColor);
            cellView.fillColor = [self colorForIndex:solutionColor];
            cellView.state = NGCellStateFilled;
            [cellView playSuccessAnimation];
            _correctFilledCount++;
            [self checkClueCompletionForRow:r col:c];
            [self notifyDelegateCorrect:YES row:r col:c];

            if (_correctFilledCount >= _puzzle.totalFilledCells) {
                [self onPuzzleComplete];
            }
        } else {
            // Wrong: auto-X, lose a life
            _playerGrid[r][c] = @(-1);
            cellView.state = NGCellStateMarkedX;
            [cellView playErrorAnimation];
            [self notifyDelegateCorrect:NO row:r col:c];
        }

    } else {
        // Mark-X mode
        if (currentPlayer == -1) {
            // Remove X
            _playerGrid[r][c] = @0;
            cellView.state = NGCellStateEmpty;
        } else if (currentPlayer > 0) {
            // Was filled – mark as X (wrong X on filled cell)
            NSInteger removedColor = currentPlayer;
            if ([_puzzle.solution[r][c] integerValue] == removedColor) {
                _correctFilledCount--;
            }
            _playerGrid[r][c] = @(-1);
            cellView.state = NGCellStateMarkedX;
            // Placing X on a cell that should be filled = wrong
            BOOL wrongX = (solutionColor > 0);
            if (wrongX) {
                [cellView playErrorAnimation];
                [self notifyDelegateCorrect:NO row:r col:c];
            }
        } else {
            // Empty → X
            _playerGrid[r][c] = @(-1);
            cellView.state = NGCellStateMarkedX;
            // Placing X on a cell that should be filled = wrong
            if (solutionColor > 0) {
                [cellView playErrorAnimation];
                [self notifyDelegateCorrect:NO row:r col:c];
            }
        }
        [self checkClueCompletionForRow:r col:c];
    }
}

- (UIColor *)colorForIndex:(NSInteger)index {
    if (index < 1 || index > (NSInteger)_puzzle.colors.count) {
        return [NGTheme accentColor];
    }
    return _puzzle.colors[index - 1];
}

// ---------------------------------------------------------------------------
#pragma mark - Clue completion
// ---------------------------------------------------------------------------

- (void)checkClueCompletionForRow:(NSInteger)r col:(NSInteger)c {
    // Check row r
    BOOL rowDone = [self isRowComplete:r];
    if (rowDone != [_rowClueComplete[r] boolValue]) {
        _rowClueComplete[r] = @(rowDone);
        [self updateRowClueAppearance:r complete:rowDone];
    }

    // Check col c
    BOOL colDone = [self isColComplete:c];
    if (colDone != [_colClueComplete[c] boolValue]) {
        _colClueComplete[c] = @(colDone);
        [self updateColClueAppearance:c complete:colDone];
    }
}

- (BOOL)isRowComplete:(NSInteger)r {
    for (NSInteger c = 0; c < _puzzle.cols; c++) {
        NSInteger solution = [_puzzle.solution[r][c] integerValue];
        NSInteger player   = [_playerGrid[r][c] integerValue];
        if (solution > 0 && player != solution) return NO;
        if (solution == 0 && player > 0) return NO;
    }
    return YES;
}

- (BOOL)isColComplete:(NSInteger)c {
    for (NSInteger r = 0; r < _puzzle.rows; r++) {
        NSInteger solution = [_puzzle.solution[r][c] integerValue];
        NSInteger player   = [_playerGrid[r][c] integerValue];
        if (solution > 0 && player != solution) return NO;
        if (solution == 0 && player > 0) return NO;
    }
    return YES;
}

- (void)updateRowClueAppearance:(NSInteger)r complete:(BOOL)complete {
    UIColor *color = complete ? [NGTheme clueCompletedTextColor] : nil; // nil → reset to original
    for (NSInteger i = 0; i < (NSInteger)_rowClueLabels[r].count; i++) {
        UILabel *lbl = _rowClueLabels[r][i];
        if (complete) {
            lbl.textColor = [NGTheme clueCompletedTextColor];
        } else {
            NGPuzzleClue *clue = _puzzle.rowClues[r][i];
            lbl.textColor = (clue.colorIndex > 0 && clue.colorIndex <= (NSInteger)_puzzle.colors.count)
                ? _puzzle.colors[clue.colorIndex - 1]
                : [NGTheme clueTextColor];
        }
        (void)color;
    }
}

- (void)updateColClueAppearance:(NSInteger)c complete:(BOOL)complete {
    for (NSInteger i = 0; i < (NSInteger)_colClueLabels[c].count; i++) {
        UILabel *lbl = _colClueLabels[c][i];
        if (complete) {
            lbl.textColor = [NGTheme clueCompletedTextColor];
        } else {
            NGPuzzleClue *clue = _puzzle.colClues[c][i];
            lbl.textColor = (clue.colorIndex > 0 && clue.colorIndex <= (NSInteger)_puzzle.colors.count)
                ? _puzzle.colors[clue.colorIndex - 1]
                : [NGTheme clueTextColor];
        }
    }
}

- (void)markAllCluesComplete {
    for (NSInteger r = 0; r < _puzzle.rows; r++) {
        [self updateRowClueAppearance:r complete:YES];
    }
    for (NSInteger c = 0; c < _puzzle.cols; c++) {
        [self updateColClueAppearance:c complete:YES];
    }
}

// ---------------------------------------------------------------------------
#pragma mark - Completion
// ---------------------------------------------------------------------------

- (void)onPuzzleComplete {
    [self revealSolution];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.4 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        if ([self.delegate respondsToSelector:@selector(puzzleGridViewDidComplete:)]) {
            [self.delegate puzzleGridViewDidComplete:self];
        }
    });
}

// ---------------------------------------------------------------------------
#pragma mark - Hint stripe
// ---------------------------------------------------------------------------

- (BOOL)showHintStripe {
    if (!_puzzle) return NO;

    // Collect unsolved rows and cols
    NSMutableArray *unsolvedRows = [NSMutableArray array];
    NSMutableArray *unsolvedCols = [NSMutableArray array];
    for (NSInteger r = 0; r < _puzzle.rows; r++) {
        if (![_rowClueComplete[r] boolValue]) [unsolvedRows addObject:@(r)];
    }
    for (NSInteger c = 0; c < _puzzle.cols; c++) {
        if (![_colClueComplete[c] boolValue]) [unsolvedCols addObject:@(c)];
    }
    if (unsolvedRows.count == 0 && unsolvedCols.count == 0) return NO;

    // Pick randomly between a row or column
    NSMutableArray *candidates = [NSMutableArray array];
    for (NSNumber *n in unsolvedRows) [candidates addObject:@[@"row", n]];
    for (NSNumber *n in unsolvedCols) [candidates addObject:@[@"col", n]];

    NSArray *pick = candidates[arc4random_uniform((uint32_t)candidates.count)];
    BOOL isRow    = [pick[0] isEqualToString:@"row"];
    NSInteger idx = [pick[1] integerValue];

    // Build the stripe rect from current cell frames
    CGRect stripe = CGRectZero;
    if (isRow) {
        CGRect first = _cellViews[idx][0].frame;
        CGRect last  = _cellViews[idx][_puzzle.cols - 1].frame;
        stripe = CGRectMake(0, first.origin.y - 2,
                            self.bounds.size.width,
                            first.size.height + 4);
        // Overlay: also show correct colors dimly
        for (NSInteger c = 0; c < _puzzle.cols; c++) {
            NSInteger sol = [_puzzle.solution[idx][c] integerValue];
            if (sol > 0 && [_playerGrid[idx][c] integerValue] == 0) {
                NGCellView *cell = _cellViews[idx][c];
                UIColor *hint = [[self colorForIndex:sol] colorWithAlphaComponent:0.35];
                UIView *overlay = [[UIView alloc] initWithFrame:cell.frame];
                overlay.backgroundColor = hint;
                overlay.layer.cornerRadius = [NGTheme cellCornerRadius];
                overlay.tag = 9999;
                overlay.userInteractionEnabled = NO;
                [self addSubview:overlay];
            }
        }
        (void)last;
    } else {
        CGRect first = _cellViews[0][idx].frame;
        CGRect last  = _cellViews[_puzzle.rows - 1][idx].frame;
        stripe = CGRectMake(first.origin.x - 2, 0,
                            first.size.width + 4,
                            self.bounds.size.height);
        for (NSInteger r = 0; r < _puzzle.rows; r++) {
            NSInteger sol = [_puzzle.solution[r][idx] integerValue];
            if (sol > 0 && [_playerGrid[r][idx] integerValue] == 0) {
                NGCellView *cell = _cellViews[r][idx];
                UIColor *hint = [[self colorForIndex:sol] colorWithAlphaComponent:0.35];
                UIView *overlay = [[UIView alloc] initWithFrame:cell.frame];
                overlay.backgroundColor = hint;
                overlay.layer.cornerRadius = [NGTheme cellCornerRadius];
                overlay.tag = 9999;
                overlay.userInteractionEnabled = NO;
                [self addSubview:overlay];
            }
        }
        (void)last;
    }

    // Semi-transparent stripe background
    UIView *stripeView = [[UIView alloc] initWithFrame:stripe];
    stripeView.backgroundColor = [NGTheme hintRowHighlightColor];
    stripeView.tag = 9998;
    stripeView.userInteractionEnabled = NO;
    [self insertSubview:stripeView atIndex:0];

    // Auto-dismiss after 2s
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)),
                   dispatch_get_main_queue(), ^{
        [UIView animateWithDuration:0.4 animations:^{
            for (UIView *v in self.subviews) {
                if (v.tag == 9998 || v.tag == 9999) v.alpha = 0;
            }
        } completion:^(BOOL fin) {
            for (UIView *v in [self.subviews copy]) {
                if (v.tag == 9998 || v.tag == 9999) [v removeFromSuperview];
            }
        }];
    });

    return YES;
}

// ---------------------------------------------------------------------------
#pragma mark - Delegate helpers
// ---------------------------------------------------------------------------

- (void)notifyDelegateCorrect:(BOOL)correct row:(NSInteger)r col:(NSInteger)c {
    if ([self.delegate respondsToSelector:@selector(puzzleGridView:didTapCellAtRow:col:correct:)]) {
        [self.delegate puzzleGridView:self didTapCellAtRow:r col:c correct:correct];
    }
}

@end
