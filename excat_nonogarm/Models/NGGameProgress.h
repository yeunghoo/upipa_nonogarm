//
//  NGGameProgress.h
//  excat_nonogarm
//
//  Persists completed levels and game statistics using NSUserDefaults.

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NGGameProgress : NSObject

/// Singleton instance.
+ (instancetype)shared;

/// Returns YES if the given level (1-based) has been completed.
- (BOOL)isLevelCompleted:(NSInteger)level;

/// Mark a level as completed.
- (void)markLevelCompleted:(NSInteger)level;

/// Highest level the player has unlocked (all levels up to this are playable).
- (NSInteger)highestUnlockedLevel;

/// Number of completed levels.
- (NSInteger)completedLevelCount;

/// Reset all progress (for testing).
- (void)resetProgress;

@end

NS_ASSUME_NONNULL_END
