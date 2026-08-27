//
//  NGTheme.h
//  excat_nonogarm

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface NGTheme : NSObject

// Backgrounds
+ (UIColor *)appBackgroundColor;
+ (UIColor *)gridBackgroundColor;
+ (UIColor *)headerBackgroundColor;
+ (UIColor *)toolbarBackgroundColor;
+ (UIColor *)cardBackgroundColor;      // elevated card surface
+ (UIColor *)surfaceColor;             // slightly elevated from app bg
+ (UIColor *)separatorColor;

// Cell states
+ (UIColor *)cellEmptyColor;
+ (UIColor *)cellEmptyBorderColor;
+ (UIColor *)cellXColor;
+ (UIColor *)cellXForegroundColor;
+ (UIColor *)cellCorrectHighlightColor;
+ (UIColor *)cellErrorColor;
+ (UIColor *)hintRowHighlightColor;

// Clue labels
+ (UIColor *)clueTextColor;
+ (UIColor *)clueCompletedTextColor;
+ (UIColor *)clueBackgroundColor;

// UI elements
+ (UIColor *)livesActiveColor;
+ (UIColor *)livesInactiveColor;
+ (UIColor *)accentColor;
+ (UIColor *)accentSecondaryColor;     // teal accent
+ (UIColor *)buttonPrimaryColor;
+ (UIColor *)buttonSecondaryColor;
+ (UIColor *)buttonSelectedBorderColor;
+ (UIColor *)goldColor;                // stars / completed

// Level select states
+ (UIColor *)levelLockedColor;
+ (UIColor *)levelUnlockedColor;
+ (UIColor *)levelCompletedColor;
+ (UIColor *)levelCurrentBorderColor;

// Puzzle color palette (colorIndex 1–8)
+ (UIColor *)puzzleColorForIndex:(NSInteger)index;
+ (NSArray<UIColor *> *)allPuzzleColors;

// Fonts
+ (UIFont *)clueFontWithSize:(CGFloat)size;
+ (UIFont *)headerFontWithSize:(CGFloat)size;
+ (UIFont *)bodyFontWithSize:(CGFloat)size;
+ (UIFont *)monoFontWithSize:(CGFloat)size;

// Layout
+ (CGFloat)cellCornerRadius;
+ (CGFloat)cardCornerRadius;
+ (CGFloat)gridLineWidth;
+ (CGFloat)minCellSize;

// Helpers
/// Draw a filled rounded-rect image — useful for button backgrounds.
+ (UIImage *)solidImageWithColor:(UIColor *)color cornerRadius:(CGFloat)r size:(CGSize)sz;

/// Render puzzle solution to a UIImage of the given pixel size.
+ (UIImage *)previewImageForPuzzle:(id)puzzle size:(CGSize)sz;

@end

NS_ASSUME_NONNULL_END
