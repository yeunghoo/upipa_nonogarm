//
//  NGGameProgress.m
//  excat_nonogarm

#import "NGGameProgress.h"

static NSString * const kCompletedLevelsKey = @"ng_completedLevels";

@implementation NGGameProgress

+ (instancetype)shared {
    static NGGameProgress *instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        instance = [[NGGameProgress alloc] init];
    });
    return instance;
}

- (NSMutableSet<NSNumber *> *)completedSet {
    NSArray *arr = [[NSUserDefaults standardUserDefaults] arrayForKey:kCompletedLevelsKey];
    if (!arr) return [NSMutableSet set];
    return [NSMutableSet setWithArray:arr];
}

- (void)saveSet:(NSSet<NSNumber *> *)set {
    [[NSUserDefaults standardUserDefaults] setObject:set.allObjects forKey:kCompletedLevelsKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

- (BOOL)isLevelCompleted:(NSInteger)level {
    return [[self completedSet] containsObject:@(level)];
}

- (void)markLevelCompleted:(NSInteger)level {
    NSMutableSet *set = [self completedSet];
    [set addObject:@(level)];
    [self saveSet:set];
}

- (NSInteger)highestUnlockedLevel {
    NSMutableSet *set = [self completedSet];
    NSInteger highest = 1;
    for (NSNumber *n in set) {
        highest = MAX(highest, n.integerValue + 1);
    }
    return MIN(highest, 99);
}

- (NSInteger)completedLevelCount {
    return (NSInteger)[self completedSet].count;
}

- (void)resetProgress {
    [[NSUserDefaults standardUserDefaults] removeObjectForKey:kCompletedLevelsKey];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

@end
