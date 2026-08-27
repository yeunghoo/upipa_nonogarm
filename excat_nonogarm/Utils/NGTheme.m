//
//  NGTheme.m
//  excat_nonogarm

#import "NGTheme.h"
#import "NGPuzzle.h"

@implementation NGTheme

+ (UIColor *)appBackgroundColor   { return [UIColor colorWithRed:0.08 green:0.08 blue:0.13 alpha:1.0]; }
+ (UIColor *)gridBackgroundColor  { return [UIColor colorWithRed:0.10 green:0.10 blue:0.16 alpha:1.0]; }
+ (UIColor *)headerBackgroundColor{ return [UIColor colorWithRed:0.06 green:0.06 blue:0.10 alpha:1.0]; }
+ (UIColor *)toolbarBackgroundColor{ return [UIColor colorWithRed:0.10 green:0.10 blue:0.16 alpha:1.0]; }
+ (UIColor *)cardBackgroundColor  { return [UIColor colorWithRed:0.14 green:0.14 blue:0.22 alpha:1.0]; }
+ (UIColor *)surfaceColor         { return [UIColor colorWithRed:0.12 green:0.12 blue:0.19 alpha:1.0]; }
+ (UIColor *)separatorColor       { return [UIColor colorWithWhite:1.0 alpha:0.07]; }

+ (UIColor *)cellEmptyColor       { return [UIColor colorWithRed:0.17 green:0.17 blue:0.26 alpha:1.0]; }
+ (UIColor *)cellEmptyBorderColor { return [UIColor colorWithRed:0.26 green:0.26 blue:0.38 alpha:1.0]; }
+ (UIColor *)cellXColor           { return [UIColor colorWithRed:0.13 green:0.13 blue:0.19 alpha:1.0]; }
+ (UIColor *)cellXForegroundColor { return [UIColor colorWithRed:0.50 green:0.50 blue:0.62 alpha:1.0]; }
+ (UIColor *)cellCorrectHighlightColor { return [UIColor colorWithRed:0.25 green:0.85 blue:0.45 alpha:0.35]; }
+ (UIColor *)cellErrorColor       { return [UIColor colorWithRed:0.95 green:0.25 blue:0.25 alpha:1.0]; }
+ (UIColor *)hintRowHighlightColor{ return [UIColor colorWithRed:1.00 green:0.85 blue:0.20 alpha:0.28]; }

+ (UIColor *)clueTextColor        { return [UIColor colorWithRed:0.92 green:0.92 blue:0.96 alpha:1.0]; }
+ (UIColor *)clueCompletedTextColor { return [UIColor colorWithRed:0.40 green:0.40 blue:0.52 alpha:1.0]; }
+ (UIColor *)clueBackgroundColor  { return [UIColor colorWithRed:0.12 green:0.12 blue:0.19 alpha:1.0]; }

+ (UIColor *)livesActiveColor     { return [UIColor colorWithRed:0.96 green:0.28 blue:0.38 alpha:1.0]; }
+ (UIColor *)livesInactiveColor   { return [UIColor colorWithRed:0.28 green:0.28 blue:0.38 alpha:1.0]; }
+ (UIColor *)accentColor          { return [UIColor colorWithRed:0.42 green:0.65 blue:1.00 alpha:1.0]; }
+ (UIColor *)accentSecondaryColor { return [UIColor colorWithRed:0.10 green:0.82 blue:0.82 alpha:1.0]; }
+ (UIColor *)buttonPrimaryColor   { return [UIColor colorWithRed:0.28 green:0.52 blue:0.96 alpha:1.0]; }
+ (UIColor *)buttonSecondaryColor { return [UIColor colorWithRed:0.20 green:0.20 blue:0.30 alpha:1.0]; }
+ (UIColor *)buttonSelectedBorderColor { return [UIColor colorWithRed:0.42 green:0.82 blue:1.00 alpha:1.0]; }
+ (UIColor *)goldColor            { return [UIColor colorWithRed:1.00 green:0.80 blue:0.20 alpha:1.0]; }

+ (UIColor *)levelLockedColor     { return [UIColor colorWithRed:0.14 green:0.14 blue:0.20 alpha:1.0]; }
+ (UIColor *)levelUnlockedColor   { return [UIColor colorWithRed:0.18 green:0.18 blue:0.28 alpha:1.0]; }
+ (UIColor *)levelCompletedColor  { return [UIColor colorWithRed:0.12 green:0.28 blue:0.18 alpha:1.0]; }
+ (UIColor *)levelCurrentBorderColor { return [UIColor colorWithRed:0.42 green:0.65 blue:1.00 alpha:1.0]; }

+ (UIColor *)puzzleColorForIndex:(NSInteger)index {
    switch (index) {
        case 1: return [UIColor colorWithRed:0.58 green:0.22 blue:0.92 alpha:1.0]; // Purple
        case 2: return [UIColor colorWithRed:0.22 green:0.58 blue:0.98 alpha:1.0]; // Blue
        case 3: return [UIColor colorWithRed:0.20 green:0.80 blue:0.44 alpha:1.0]; // Green
        case 4: return [UIColor colorWithRed:0.96 green:0.28 blue:0.34 alpha:1.0]; // Red
        case 5: return [UIColor colorWithRed:1.00 green:0.58 blue:0.12 alpha:1.0]; // Orange
        case 6: return [UIColor colorWithRed:0.06 green:0.78 blue:0.78 alpha:1.0]; // Teal
        case 7: return [UIColor colorWithRed:1.00 green:0.84 blue:0.12 alpha:1.0]; // Yellow/Gold
        case 8: return [UIColor colorWithRed:1.00 green:0.44 blue:0.72 alpha:1.0]; // Pink
        default: return [UIColor whiteColor];
    }
}

+ (NSArray<UIColor *> *)allPuzzleColors {
    NSMutableArray *c = [NSMutableArray array];
    for (NSInteger i = 1; i <= 8; i++) [c addObject:[self puzzleColorForIndex:i]];
    return c;
}

+ (UIFont *)clueFontWithSize:(CGFloat)size   { return [UIFont systemFontOfSize:size weight:UIFontWeightBold]; }
+ (UIFont *)headerFontWithSize:(CGFloat)size { return [UIFont systemFontOfSize:size weight:UIFontWeightHeavy]; }
+ (UIFont *)bodyFontWithSize:(CGFloat)size   { return [UIFont systemFontOfSize:size weight:UIFontWeightMedium]; }
+ (UIFont *)monoFontWithSize:(CGFloat)size   {
    return [UIFont monospacedDigitSystemFontOfSize:size weight:UIFontWeightSemibold];
}

+ (CGFloat)cellCornerRadius  { return 3.0; }
+ (CGFloat)cardCornerRadius  { return 18.0; }
+ (CGFloat)gridLineWidth     { return 1.0; }
+ (CGFloat)minCellSize       { return 12.0; }

// ---------------------------------------------------------------------------
#pragma mark - Helpers
// ---------------------------------------------------------------------------

+ (UIImage *)solidImageWithColor:(UIColor *)color cornerRadius:(CGFloat)r size:(CGSize)sz {
    UIGraphicsBeginImageContextWithOptions(sz, NO, 0);
    UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:CGRectMake(0,0,sz.width,sz.height)
                                                   cornerRadius:r];
    [color setFill];
    [path fill];
    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

+ (UIImage *)previewImageForPuzzle:(id)puzzleObj size:(CGSize)sz {
    NGPuzzle *puzzle = (NGPuzzle *)puzzleObj;
    if (!puzzle || puzzle.rows == 0 || puzzle.cols == 0) return nil;

    CGFloat cellW = sz.width  / puzzle.cols;
    CGFloat cellH = sz.height / puzzle.rows;
    CGFloat gap   = 1.0;

    UIGraphicsBeginImageContextWithOptions(sz, NO, 0);
    CGContextRef ctx = UIGraphicsGetCurrentContext();

    // Background
    CGContextSetFillColorWithColor(ctx, [UIColor colorWithRed:0.10 green:0.10 blue:0.16 alpha:1.0].CGColor);
    CGContextFillRect(ctx, CGRectMake(0, 0, sz.width, sz.height));

    for (NSInteger r = 0; r < puzzle.rows; r++) {
        for (NSInteger c = 0; c < puzzle.cols; c++) {
            NSInteger colorIdx = [puzzle.solution[r][c] integerValue];
            UIColor *fill;
            if (colorIdx > 0 && colorIdx <= (NSInteger)puzzle.colors.count) {
                fill = puzzle.colors[colorIdx - 1];
            } else {
                fill = [UIColor colorWithRed:0.17 green:0.17 blue:0.26 alpha:1.0];
            }
            CGRect cellRect = CGRectMake(c * cellW + gap * 0.5,
                                         r * cellH + gap * 0.5,
                                         cellW - gap, cellH - gap);
            CGContextSetFillColorWithColor(ctx, fill.CGColor);
            CGContextFillRect(ctx, cellRect);
        }
    }

    UIImage *img = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    return img;
}

@end
