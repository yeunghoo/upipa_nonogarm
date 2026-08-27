//
//  NGSplashViewController.m
//  excat_nonogarm
//
//  Splash screen: rounded app icon + tagline, fades into LevelSelect after 1.5s.

#import "NGSplashViewController.h"
#import "NGLevelSelectViewController.h"
#import "NGGameViewController.h"
#import "NGGameProgress.h"
#import "NGLevelData.h"
#import "NGTheme.h"

@implementation NGSplashViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [NGTheme appBackgroundColor];
    [self buildUI];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(1.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [self transitionToGame];
    });
}

// ---------------------------------------------------------------------------
#pragma mark - UI
// ---------------------------------------------------------------------------

- (void)buildUI {
    // Subtle radial gradient background via gradient layer
    CAGradientLayer *grad = [CAGradientLayer layer];
    grad.frame = self.view.bounds;
    grad.type = kCAGradientLayerRadial;
    UIColor *center = [UIColor colorWithRed:0.12 green:0.10 blue:0.22 alpha:1.0];
    UIColor *edge   = [NGTheme appBackgroundColor];
    grad.colors = @[(id)center.CGColor, (id)edge.CGColor];
    grad.startPoint = CGPointMake(0.5, 0.5);
    grad.endPoint   = CGPointMake(1.0, 1.0);
    [self.view.layer insertSublayer:grad atIndex:0];

    // App icon image view
    UIImageView *iconView = [[UIImageView alloc] init];
    iconView.contentMode = UIViewContentModeScaleAspectFill;
    iconView.clipsToBounds = YES;
    iconView.layer.cornerRadius = 26.0;   // iOS-style squircle approximation
    iconView.layer.borderWidth = 1.5;
    iconView.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.18].CGColor;

    // Load the splash icon from the dedicated imageset "AppIconImage"
    UIImage *icon = [UIImage imageNamed:@"AppIconImage"];
    if (!icon) {
        // Programmatic fallback that looks nice
        CGSize sz = CGSizeMake(120, 120);
        UIGraphicsBeginImageContextWithOptions(sz, NO, 0);
        CGContextRef ctx = UIGraphicsGetCurrentContext();
        // Background gradient
        CGColorSpaceRef cs = CGColorSpaceCreateDeviceRGB();
        CGFloat comps[] = { 0.20, 0.45, 0.95, 1.0,
                             0.10, 0.25, 0.75, 1.0 };
        CGGradientRef gr = CGGradientCreateWithColorComponents(cs, comps, NULL, 2);
        CGContextDrawLinearGradient(ctx, gr,
                                    CGPointMake(0, 0), CGPointMake(sz.width, sz.height), 0);
        CGGradientRelease(gr);
        CGColorSpaceRelease(cs);
        // Letter
        NSDictionary *attrs = @{NSFontAttributeName: [UIFont systemFontOfSize:62 weight:UIFontWeightHeavy],
                                NSForegroundColorAttributeName: [UIColor whiteColor]};
        NSAttributedString *str = [[NSAttributedString alloc] initWithString:@"N" attributes:attrs];
        CGSize ts = str.size;
        [str drawAtPoint:CGPointMake((sz.width - ts.width) * 0.5,
                                     (sz.height - ts.height) * 0.5)];
        icon = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    iconView.image = icon;
    iconView.translatesAutoresizingMaskIntoConstraints = NO;

    // Glow shadow behind icon
    UIView *glowView = [[UIView alloc] init];
    glowView.backgroundColor = [UIColor clearColor];
    glowView.translatesAutoresizingMaskIntoConstraints = NO;
    glowView.layer.shadowColor  = [NGTheme buttonPrimaryColor].CGColor;
    glowView.layer.shadowOffset = CGSizeZero;
    glowView.layer.shadowRadius = 30.0;
    glowView.layer.shadowOpacity = 0.6;
    glowView.layer.cornerRadius = 28.0;

    // App name label
    UILabel *nameLabel = [[UILabel alloc] init];
    nameLabel.text = @"Exactigram";
    nameLabel.font = [NGTheme headerFontWithSize:34.0];
    nameLabel.textColor = [NGTheme clueTextColor];
    nameLabel.textAlignment = NSTextAlignmentCenter;
    nameLabel.translatesAutoresizingMaskIntoConstraints = NO;

    // Tagline
    UILabel *tagLabel = [[UILabel alloc] init];
    tagLabel.text = @"Fill the grid. Reveal the art.";
    tagLabel.font = [NGTheme bodyFontWithSize:15.0];
    tagLabel.textColor = [NGTheme clueCompletedTextColor];
    tagLabel.textAlignment = NSTextAlignmentCenter;
    tagLabel.translatesAutoresizingMaskIntoConstraints = NO;

    // Loading dots (3 animated dots)
    UIStackView *dotsStack = [self makeLoadingDots];
    dotsStack.translatesAutoresizingMaskIntoConstraints = NO;

    [self.view addSubview:glowView];
    [self.view addSubview:iconView];
    [self.view addSubview:nameLabel];
    [self.view addSubview:tagLabel];
    [self.view addSubview:dotsStack];

    [NSLayoutConstraint activateConstraints:@[
        [iconView.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],
        [iconView.centerYAnchor constraintEqualToAnchor:self.view.centerYAnchor constant:-60],
        [iconView.widthAnchor constraintEqualToConstant:120],
        [iconView.heightAnchor constraintEqualToConstant:120],

        [glowView.centerXAnchor constraintEqualToAnchor:iconView.centerXAnchor],
        [glowView.centerYAnchor constraintEqualToAnchor:iconView.centerYAnchor],
        [glowView.widthAnchor constraintEqualToAnchor:iconView.widthAnchor],
        [glowView.heightAnchor constraintEqualToAnchor:iconView.heightAnchor],

        [nameLabel.topAnchor constraintEqualToAnchor:iconView.bottomAnchor constant:20],
        [nameLabel.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],

        [tagLabel.topAnchor constraintEqualToAnchor:nameLabel.bottomAnchor constant:8],
        [tagLabel.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],

        [dotsStack.bottomAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.bottomAnchor constant:-36],
        [dotsStack.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],
    ]];

    // Entrance animation
    iconView.alpha = 0;
    iconView.transform = CGAffineTransformMakeScale(0.7, 0.7);
    nameLabel.alpha = 0;
    tagLabel.alpha = 0;

    [UIView animateWithDuration:0.6 delay:0.1
         usingSpringWithDamping:0.72 initialSpringVelocity:0.5
                        options:0 animations:^{
        iconView.alpha = 1;
        iconView.transform = CGAffineTransformIdentity;
    } completion:nil];
    [UIView animateWithDuration:0.5 delay:0.4 options:0 animations:^{
        nameLabel.alpha = 1;
        tagLabel.alpha = 1;
    } completion:nil];
}

- (UIStackView *)makeLoadingDots {
    UIStackView *stack = [[UIStackView alloc] init];
    stack.axis = UILayoutConstraintAxisHorizontal;
    stack.spacing = 6.0;
    stack.alignment = UIStackViewAlignmentCenter;

    for (NSInteger i = 0; i < 3; i++) {
        UIView *dot = [[UIView alloc] init];
        dot.backgroundColor = [UIColor colorWithWhite:1.0 alpha:0.25];
        dot.layer.cornerRadius = 3.0;
        dot.translatesAutoresizingMaskIntoConstraints = NO;
        [dot.widthAnchor constraintEqualToConstant:6].active = YES;
        [dot.heightAnchor constraintEqualToConstant:6].active = YES;
        [stack addArrangedSubview:dot];

        // Pulse animation staggered
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(i * 0.18 * NSEC_PER_SEC)),
                       dispatch_get_main_queue(), ^{
            CABasicAnimation *anim = [CABasicAnimation animationWithKeyPath:@"opacity"];
            anim.fromValue = @0.25;
            anim.toValue   = @0.9;
            anim.duration  = 0.5;
            anim.autoreverses = YES;
            anim.repeatCount  = HUGE_VALF;
            [dot.layer addAnimation:anim forKey:@"pulse"];
        });
    }
    return stack;
}

// ---------------------------------------------------------------------------
#pragma mark - Transition
// ---------------------------------------------------------------------------

- (void)transitionToGame {
    // Navigation stack: LevelSelect (root, hidden) → Game (current level)
    // This way back-button from game lands on LevelSelect.
    NSInteger currentLevel = MAX(1, [[NGGameProgress shared] highestUnlockedLevel]);
    currentLevel = MIN(currentLevel, [NGLevelData totalLevelCount]);

    NGLevelSelectViewController *selectVC = [[NGLevelSelectViewController alloc] init];
    NGGameViewController *gameVC = [[NGGameViewController alloc] initWithLevel:currentLevel];

    UINavigationController *nav = [[UINavigationController alloc] initWithRootViewController:selectVC];
    nav.navigationBarHidden = YES;
    // Set full stack at once: selectVC (back destination) → gameVC (visible)
    [nav setViewControllers:@[selectVC, gameVC] animated:NO];

    UIWindow *window = self.view.window;
    [UIView transitionWithView:window
                      duration:0.45
                       options:UIViewAnimationOptionTransitionCrossDissolve
                    animations:^{ window.rootViewController = nav; }
                    completion:nil];
}

@end
