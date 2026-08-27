//
//  NGGameViewController.m
//  excat_nonogarm

#import "NGGameViewController.h"
#import "NGLevelSelectViewController.h"
#import "NGPuzzleGridView.h"
#import "NGLevelData.h"
#import "NGGameProgress.h"
#import "NGTheme.h"
#import "VTAdProxy.h"
#import <AVFoundation/AVFoundation.h>

static const NSInteger kMaxLives = 3;

// ---------------------------------------------------------------------------
#pragma mark - How-to-Play Overlay
// ---------------------------------------------------------------------------

@interface NGHowToPlayView : UIView
+ (instancetype)show:(UIView *)parent;
@end

@implementation NGHowToPlayView

+ (instancetype)show:(UIView *)parent {
    NGHowToPlayView *htp = [[NGHowToPlayView alloc] initWithFrame:parent.bounds];
    htp.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    htp.backgroundColor = [UIColor colorWithWhite:0 alpha:0.78];
    htp.alpha = 0;

    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [NGTheme cardBackgroundColor];
    card.layer.cornerRadius = [NGTheme cardCornerRadius];
    card.layer.shadowColor  = UIColor.blackColor.CGColor;
    card.layer.shadowOffset = CGSizeMake(0, 8);
    card.layer.shadowRadius = 20;
    card.layer.shadowOpacity = 0.5;
    card.translatesAutoresizingMaskIntoConstraints = NO;
    [htp addSubview:card];

    UILabel *title = [[UILabel alloc] init];
    title.text = @"How to Play";
    title.font = [NGTheme headerFontWithSize:22];
    title.textColor = [NGTheme clueTextColor];
    title.translatesAutoresizingMaskIntoConstraints = NO;

    NSArray *steps = @[
        @[@"square.fill", @"Tap a cell to fill it with the selected color."],
        @[@"xmark.square", @"Switch to Mark X to mark cells that must be empty."],
        @[@"number.square", @"Numbers show how many consecutive filled cells appear in that row or column."],
        @[@"heart.fill",  @"Each wrong tap costs one life. You have 3 lives per puzzle."],
        @[@"lightbulb",   @"Tap the Hint button (💡) to reveal one row or column."],
    ];

    UIStackView *stepsStack = [[UIStackView alloc] init];
    stepsStack.axis = UILayoutConstraintAxisVertical;
    stepsStack.spacing = 14;
    stepsStack.translatesAutoresizingMaskIntoConstraints = NO;

    for (NSArray *step in steps) {
        UIImageView *icon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:step[0]]];
        icon.contentMode = UIViewContentModeScaleAspectFit;
        icon.tintColor = [NGTheme accentColor];
        icon.translatesAutoresizingMaskIntoConstraints = NO;
        [icon.widthAnchor constraintEqualToConstant:22].active = YES;
        [icon.heightAnchor constraintEqualToConstant:22].active = YES;

        UILabel *lbl = [[UILabel alloc] init];
        lbl.text = step[1];
        lbl.font = [NGTheme bodyFontWithSize:13.5];
        lbl.textColor = [NGTheme clueTextColor];
        lbl.numberOfLines = 0;

        UIStackView *row = [[UIStackView alloc] initWithArrangedSubviews:@[icon, lbl]];
        row.axis = UILayoutConstraintAxisHorizontal;
        row.spacing = 12;
        row.alignment = UIStackViewAlignmentTop;
        [stepsStack addArrangedSubview:row];
    }

    UIButton *closeBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    closeBtn.backgroundColor = [NGTheme buttonPrimaryColor];
    [closeBtn setTitle:@"Got it!" forState:UIControlStateNormal];
    closeBtn.titleLabel.font = [NGTheme bodyFontWithSize:16];
    [closeBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    closeBtn.layer.cornerRadius = 12;
    closeBtn.clipsToBounds = YES;
    closeBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [closeBtn addTarget:htp action:@selector(dismiss) forControlEvents:UIControlEventTouchUpInside];

    [card addSubview:title];
    [card addSubview:stepsStack];
    [card addSubview:closeBtn];

    [NSLayoutConstraint activateConstraints:@[
        [card.centerXAnchor constraintEqualToAnchor:htp.centerXAnchor],
        [card.centerYAnchor constraintEqualToAnchor:htp.centerYAnchor],
        [card.widthAnchor constraintEqualToAnchor:htp.widthAnchor multiplier:0.88],

        [title.topAnchor constraintEqualToAnchor:card.topAnchor constant:24],
        [title.centerXAnchor constraintEqualToAnchor:card.centerXAnchor],

        [stepsStack.topAnchor constraintEqualToAnchor:title.bottomAnchor constant:20],
        [stepsStack.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:20],
        [stepsStack.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-20],

        [closeBtn.topAnchor constraintEqualToAnchor:stepsStack.bottomAnchor constant:22],
        [closeBtn.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:20],
        [closeBtn.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-20],
        [closeBtn.heightAnchor constraintEqualToConstant:48],
        [closeBtn.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-24],
    ]];

    [parent addSubview:htp];
    [UIView animateWithDuration:0.25 animations:^{ htp.alpha = 1; }];

    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] initWithTarget:htp action:@selector(dismiss)];
    [htp addGestureRecognizer:tap];
    return htp;
}

- (void)dismiss {
    [UIView animateWithDuration:0.2 animations:^{ self.alpha = 0; }
                     completion:^(BOOL f){ [self removeFromSuperview]; }];
}

@end

// ---------------------------------------------------------------------------
#pragma mark - NGGameViewController
// ---------------------------------------------------------------------------

@interface NGGameViewController () <NGPuzzleGridViewDelegate>

@property (nonatomic, strong) NGPuzzle *puzzle;
@property (nonatomic, assign) NSInteger livesRemaining;
@property (nonatomic, assign) BOOL isCompleted;

// Header
@property (nonatomic, strong) UIView   *headerView;
@property (nonatomic, strong) UILabel  *levelLabel;
@property (nonatomic, strong) UILabel  *puzzleNameLabel;
@property (nonatomic, strong) UIStackView *livesStack;

// Grid
@property (nonatomic, strong) UIScrollView   *scrollView;
@property (nonatomic, strong) NGPuzzleGridView *gridView;

// Toolbar
@property (nonatomic, strong) UIView       *toolbarView;
@property (nonatomic, strong) UIButton     *fillButton;
@property (nonatomic, strong) UIButton     *markXButton;
@property (nonatomic, strong) UIStackView  *colorPaletteStack;

// Hint 广告相关
@property (nonatomic, assign) NSInteger hintCredits;
@property (nonatomic, weak)   UIButton  *hintBtn;
@property (nonatomic, weak)   UILabel   *hintBadge;

// 广告对话框 overlay
@property (nonatomic, strong) UIView *adDialogOverlay;

// Overlay
@property (nonatomic, strong) UIView *completionOverlay;

// Audio
@property (nonatomic, strong) AVAudioPlayer *audioPlayer;

@end

@implementation NGGameViewController

- (instancetype)initWithLevel:(NSInteger)level {
    self = [super initWithNibName:nil bundle:nil];
    if (self) {
        _levelNumber    = level;
        _livesRemaining = kMaxLives;
        _hintCredits    = 0;
    }
    return self;
}

- (instancetype)init { return [self initWithLevel:1]; }

// ---------------------------------------------------------------------------
#pragma mark - Lifecycle
// ---------------------------------------------------------------------------

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [NGTheme appBackgroundColor];
    [self loadPuzzle];
    [self buildHeader];
    [self buildScrollView];
    [self buildToolbar];
    [self setupConstraints];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [_gridView setNeedsLayout];
    [_gridView layoutIfNeeded];
}

- (void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator {
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
    [coordinator animateAlongsideTransition:^(id ctx) { [self->_gridView setNeedsLayout]; } completion:nil];
}

// ---------------------------------------------------------------------------
#pragma mark - Data
// ---------------------------------------------------------------------------

- (void)loadPuzzle {
    _puzzle = [NGLevelData puzzleForLevel:_levelNumber];
    if (!_puzzle) { _levelNumber = 1; _puzzle = [NGLevelData puzzleForLevel:1]; }
    _livesRemaining = kMaxLives;
    _isCompleted    = NO;
}

// ---------------------------------------------------------------------------
#pragma mark - Header
// ---------------------------------------------------------------------------

- (void)buildHeader {
    _headerView = [[UIView alloc] init];
    _headerView.backgroundColor = [NGTheme headerBackgroundColor];
    _headerView.translatesAutoresizingMaskIntoConstraints = NO;

    UIView *line = [[UIView alloc] init];
    line.backgroundColor = [NGTheme separatorColor];
    line.translatesAutoresizingMaskIntoConstraints = NO;
    [_headerView addSubview:line];

    UIButton *backBtn = [self makeIconButton:@"chevron.left" action:@selector(handleBack)];
    backBtn.tintColor = [NGTheme accentColor];

    _levelLabel = [[UILabel alloc] init];
    _levelLabel.text = [NSString stringWithFormat:@"Level %ld", (long)_levelNumber];
    _levelLabel.font = [NGTheme bodyFontWithSize:12.0];
    _levelLabel.textColor = [NGTheme clueCompletedTextColor];
    _levelLabel.textAlignment = NSTextAlignmentCenter;

    _puzzleNameLabel = [[UILabel alloc] init];
    _puzzleNameLabel.text = _puzzle.name;
    _puzzleNameLabel.font = [NGTheme headerFontWithSize:20.0];
    _puzzleNameLabel.textColor = [NGTheme clueTextColor];
    _puzzleNameLabel.textAlignment = NSTextAlignmentCenter;

    UILabel *sizeLabel = [[UILabel alloc] init];
    sizeLabel.text = [NSString stringWithFormat:@"%ld × %ld", (long)_puzzle.rows, (long)_puzzle.cols];
    sizeLabel.font = [NGTheme bodyFontWithSize:11.0];
    sizeLabel.textColor = [NGTheme clueCompletedTextColor];
    sizeLabel.textAlignment = NSTextAlignmentCenter;

    UIStackView *centerStack = [[UIStackView alloc] initWithArrangedSubviews:@[_levelLabel, _puzzleNameLabel, sizeLabel]];
    centerStack.axis = UILayoutConstraintAxisVertical;
    centerStack.alignment = UIStackViewAlignmentCenter;
    centerStack.spacing = 1.0;
    centerStack.translatesAutoresizingMaskIntoConstraints = NO;

    _livesStack = [[UIStackView alloc] init];
    _livesStack.axis = UILayoutConstraintAxisHorizontal;
    _livesStack.spacing = 5.0;
    _livesStack.alignment = UIStackViewAlignmentCenter;
    _livesStack.translatesAutoresizingMaskIntoConstraints = NO;
    [self rebuildLivesStack];

    UIButton *restartBtn = [self makeIconButton:@"arrow.counterclockwise" action:@selector(handleRestart)];
    restartBtn.tintColor = [UIColor colorWithWhite:1.0 alpha:0.55];

    UIButton *helpBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    [helpBtn setTitle:@"?" forState:UIControlStateNormal];
    helpBtn.titleLabel.font = [UIFont systemFontOfSize:15 weight:UIFontWeightBold];
    [helpBtn setTitleColor:[UIColor colorWithRed:0.40 green:0.65 blue:1.0 alpha:0.90] forState:UIControlStateNormal];
    helpBtn.backgroundColor = [UIColor colorWithRed:0.40 green:0.65 blue:1.0 alpha:0.14];
    helpBtn.layer.cornerRadius = 14;
    helpBtn.layer.borderWidth = 1.0;
    helpBtn.layer.borderColor = [UIColor colorWithRed:0.40 green:0.65 blue:1.0 alpha:0.30].CGColor;
    helpBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [helpBtn addTarget:self action:@selector(handleHelp) forControlEvents:UIControlEventTouchUpInside];

    [_headerView addSubview:backBtn];
    [_headerView addSubview:helpBtn];
    [_headerView addSubview:centerStack];
    [_headerView addSubview:_livesStack];
    [_headerView addSubview:restartBtn];
    [self.view addSubview:_headerView];

    [NSLayoutConstraint activateConstraints:@[
        [line.bottomAnchor constraintEqualToAnchor:_headerView.bottomAnchor],
        [line.leadingAnchor constraintEqualToAnchor:_headerView.leadingAnchor],
        [line.trailingAnchor constraintEqualToAnchor:_headerView.trailingAnchor],
        [line.heightAnchor constraintEqualToConstant:1],

        [backBtn.leadingAnchor constraintEqualToAnchor:_headerView.leadingAnchor constant:12],
        [backBtn.topAnchor constraintEqualToAnchor:_headerView.topAnchor constant:10],

        [helpBtn.leadingAnchor constraintEqualToAnchor:_headerView.leadingAnchor constant:14],
        [helpBtn.topAnchor constraintEqualToAnchor:backBtn.bottomAnchor constant:8],
        [helpBtn.widthAnchor constraintEqualToConstant:28],
        [helpBtn.heightAnchor constraintEqualToConstant:28],

        [restartBtn.trailingAnchor constraintEqualToAnchor:_headerView.trailingAnchor constant:-12],
        [restartBtn.topAnchor constraintEqualToAnchor:_headerView.topAnchor constant:10],

        [centerStack.centerXAnchor constraintEqualToAnchor:_headerView.centerXAnchor],
        [centerStack.topAnchor constraintEqualToAnchor:_headerView.topAnchor constant:8],

        [_livesStack.centerXAnchor constraintEqualToAnchor:_headerView.centerXAnchor],
        [_livesStack.topAnchor constraintEqualToAnchor:centerStack.bottomAnchor constant:5],
        [_livesStack.bottomAnchor constraintEqualToAnchor:_headerView.bottomAnchor constant:-10],
    ]];
}

- (UIButton *)makeIconButton:(NSString *)sysName action:(SEL)action {
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIImageSymbolConfiguration *cfg = [UIImageSymbolConfiguration
                                       configurationWithPointSize:17
                                       weight:UIImageSymbolWeightMedium];
    UIImage *img = [[UIImage systemImageNamed:sysName] imageByApplyingSymbolConfiguration:cfg];
    [btn setImage:img forState:UIControlStateNormal];
    btn.translatesAutoresizingMaskIntoConstraints = NO;
    [btn addTarget:self action:action forControlEvents:UIControlEventTouchUpInside];
    [btn.widthAnchor constraintEqualToConstant:36].active = YES;
    [btn.heightAnchor constraintEqualToConstant:36].active = YES;
    return btn;
}

- (void)rebuildLivesStack {
    for (UIView *v in _livesStack.arrangedSubviews) {
        [_livesStack removeArrangedSubview:v];
        [v removeFromSuperview];
    }
    for (NSInteger i = 0; i < kMaxLives; i++) {
        UIImageView *h = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"heart.fill"]];
        h.contentMode = UIViewContentModeScaleAspectFit;
        h.tintColor = (i < _livesRemaining) ? [NGTheme livesActiveColor] : [NGTheme livesInactiveColor];
        [h.widthAnchor constraintEqualToConstant:20].active = YES;
        [h.heightAnchor constraintEqualToConstant:20].active = YES;
        [_livesStack addArrangedSubview:h];
    }
}

// ---------------------------------------------------------------------------
#pragma mark - Grid
// ---------------------------------------------------------------------------

- (void)buildScrollView {
    _scrollView = [[UIScrollView alloc] init];
    _scrollView.translatesAutoresizingMaskIntoConstraints = NO;
    _scrollView.backgroundColor = [NGTheme appBackgroundColor];
    _scrollView.showsHorizontalScrollIndicator = NO;
    _scrollView.showsVerticalScrollIndicator   = NO;
    _scrollView.bounces = YES;
    [self.view addSubview:_scrollView];

    _gridView = [[NGPuzzleGridView alloc] initWithFrame:CGRectZero];
    _gridView.translatesAutoresizingMaskIntoConstraints = NO;
    _gridView.delegate = self;
    [_scrollView addSubview:_gridView];
    [_gridView loadPuzzle:_puzzle];
}

// ---------------------------------------------------------------------------
#pragma mark - Toolbar
// ---------------------------------------------------------------------------

- (void)buildToolbar {
    _toolbarView = [[UIView alloc] init];
    _toolbarView.backgroundColor = [NGTheme toolbarBackgroundColor];
    _toolbarView.translatesAutoresizingMaskIntoConstraints = NO;

    UIView *topLine = [[UIView alloc] init];
    topLine.backgroundColor = [NGTheme separatorColor];
    topLine.translatesAutoresizingMaskIntoConstraints = NO;
    [_toolbarView addSubview:topLine];

    _colorPaletteStack = [[UIStackView alloc] init];
    _colorPaletteStack.axis = UILayoutConstraintAxisHorizontal;
    _colorPaletteStack.spacing = 8.0;
    _colorPaletteStack.alignment = UIStackViewAlignmentCenter;
    _colorPaletteStack.translatesAutoresizingMaskIntoConstraints = NO;
    [self buildColorPalette];

    _fillButton  = [self makeModeButton:@"Fill"   icon:@"square.fill"  action:@selector(handleFillMode)];
    _markXButton = [self makeModeButton:@"Mark X" icon:@"xmark.square" action:@selector(handleMarkXMode)];

    // Hint 按钮：改造为广告标识角标样式
    UIButton *hintBtn = [self makeModeButton:@"Hint" icon:@"lightbulb" action:@selector(handleHint)];
    hintBtn.backgroundColor = [UIColor colorWithRed:0.22 green:0.19 blue:0.06 alpha:1.0];
    hintBtn.clipsToBounds = NO; // 允许角标超出按钮边界
    _hintBtn = hintBtn;

    // 创建广告角标
    UILabel *badgeLbl = [[UILabel alloc] init];
    badgeLbl.translatesAutoresizingMaskIntoConstraints = NO;
    badgeLbl.backgroundColor = [UIColor colorWithRed:1.0 green:0.45 blue:0.0 alpha:1.0];
    badgeLbl.textColor = UIColor.whiteColor;
    badgeLbl.font = [UIFont systemFontOfSize:9 weight:UIFontWeightBold];
    badgeLbl.textAlignment = NSTextAlignmentCenter;
    badgeLbl.layer.cornerRadius = 9;
    badgeLbl.clipsToBounds = YES;
    [hintBtn addSubview:badgeLbl];
    _hintBadge = badgeLbl;

    [NSLayoutConstraint activateConstraints:@[
        [badgeLbl.topAnchor constraintEqualToAnchor:hintBtn.topAnchor constant:-6],
        [badgeLbl.trailingAnchor constraintEqualToAnchor:hintBtn.trailingAnchor constant:6],
        [badgeLbl.heightAnchor constraintEqualToConstant:18],
        [badgeLbl.widthAnchor constraintGreaterThanOrEqualToConstant:18],
    ]];

    [self updateHintBadge];

    UIStackView *modeRow = [[UIStackView alloc] initWithArrangedSubviews:@[_fillButton, _markXButton, hintBtn]];
    modeRow.axis = UILayoutConstraintAxisHorizontal;
    modeRow.spacing = 8.0;
    modeRow.distribution = UIStackViewDistributionFillEqually;
    modeRow.clipsToBounds = NO; // 允许角标超出 StackView 边界
    modeRow.translatesAutoresizingMaskIntoConstraints = NO;

    [_toolbarView addSubview:modeRow];
    [_toolbarView addSubview:_colorPaletteStack];
    [self.view addSubview:_toolbarView];

    _colorPaletteStack.hidden = (_puzzle.colors.count <= 1);

    [NSLayoutConstraint activateConstraints:@[
        [topLine.topAnchor constraintEqualToAnchor:_toolbarView.topAnchor],
        [topLine.leadingAnchor constraintEqualToAnchor:_toolbarView.leadingAnchor],
        [topLine.trailingAnchor constraintEqualToAnchor:_toolbarView.trailingAnchor],
        [topLine.heightAnchor constraintEqualToConstant:1],

        [modeRow.topAnchor constraintEqualToAnchor:_toolbarView.topAnchor constant:12],
        [modeRow.leadingAnchor constraintEqualToAnchor:_toolbarView.leadingAnchor constant:16],
        [modeRow.trailingAnchor constraintEqualToAnchor:_toolbarView.trailingAnchor constant:-16],
        [modeRow.heightAnchor constraintEqualToConstant:50],

        [_colorPaletteStack.topAnchor constraintEqualToAnchor:modeRow.bottomAnchor constant:10],
        [_colorPaletteStack.centerXAnchor constraintEqualToAnchor:_toolbarView.centerXAnchor],
        [_colorPaletteStack.heightAnchor constraintEqualToConstant:32],
    ]];

    [self updateModeButtons];
}

- (UIButton *)makeModeButton:(NSString *)title icon:(NSString *)iconName action:(SEL)action {
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeCustom];
    btn.backgroundColor = [NGTheme buttonSecondaryColor];
    btn.layer.cornerRadius = 10.0;
    btn.clipsToBounds = YES;
    btn.translatesAutoresizingMaskIntoConstraints = NO;

    UIImageSymbolConfiguration *cfg = [UIImageSymbolConfiguration
                                       configurationWithPointSize:14
                                       weight:UIImageSymbolWeightMedium];
    UIImage *img = [[UIImage systemImageNamed:iconName] imageByApplyingSymbolConfiguration:cfg];

    [btn setImage:img forState:UIControlStateNormal];
    [btn setTitle:[NSString stringWithFormat:@"  %@", title] forState:UIControlStateNormal];
    btn.titleLabel.font = [NGTheme bodyFontWithSize:13.0];
    btn.tintColor = [NGTheme clueTextColor];
    [btn setTitleColor:[NGTheme clueTextColor] forState:UIControlStateNormal];
    [btn addTarget:self action:action forControlEvents:UIControlEventTouchUpInside];
    return btn;
}

- (void)buildColorPalette {
    for (UIView *v in _colorPaletteStack.arrangedSubviews) {
        [_colorPaletteStack removeArrangedSubview:v];
        [v removeFromSuperview];
    }
    for (NSInteger i = 0; i < (NSInteger)_puzzle.colors.count; i++) {
        UIColor *color = _puzzle.colors[i];
        NSInteger idx  = i + 1;
        UIButton *btn  = [UIButton buttonWithType:UIButtonTypeCustom];
        btn.backgroundColor = color;
        btn.layer.cornerRadius = 15.0;
        btn.layer.borderWidth  = (idx == _gridView.selectedColorIndex) ? 3.0 : 1.5;
        btn.layer.borderColor  = (idx == _gridView.selectedColorIndex)
            ? [NGTheme buttonSelectedBorderColor].CGColor
            : [UIColor colorWithWhite:1.0 alpha:0.15].CGColor;
        btn.clipsToBounds = YES;
        btn.tag = idx;
        [btn addTarget:self action:@selector(handleColorSelected:) forControlEvents:UIControlEventTouchUpInside];
        btn.translatesAutoresizingMaskIntoConstraints = NO;
        [btn.widthAnchor constraintEqualToConstant:30].active = YES;
        [btn.heightAnchor constraintEqualToConstant:30].active = YES;
        [_colorPaletteStack addArrangedSubview:btn];
    }
}

// ---------------------------------------------------------------------------
#pragma mark - Auto Layout
// ---------------------------------------------------------------------------

- (void)setupConstraints {
    UILayoutGuide *safe = self.view.safeAreaLayoutGuide;

    CGFloat toolbarH = (_puzzle.colors.count > 1) ? 148.0 : 100.0;

    [NSLayoutConstraint activateConstraints:@[
        [_headerView.topAnchor constraintEqualToAnchor:safe.topAnchor],
        [_headerView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [_headerView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],

        [_toolbarView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [_toolbarView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [_toolbarView.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
        [_toolbarView.heightAnchor constraintEqualToConstant:toolbarH],

        [_scrollView.topAnchor constraintEqualToAnchor:_headerView.bottomAnchor],
        [_scrollView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [_scrollView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [_scrollView.bottomAnchor constraintEqualToAnchor:_toolbarView.topAnchor],

        [_gridView.topAnchor constraintEqualToAnchor:_scrollView.topAnchor],
        [_gridView.leadingAnchor constraintEqualToAnchor:_scrollView.leadingAnchor],
        [_gridView.widthAnchor constraintEqualToAnchor:_scrollView.widthAnchor],
        [_gridView.heightAnchor constraintEqualToAnchor:_scrollView.heightAnchor],
    ]];
}

// ---------------------------------------------------------------------------
#pragma mark - Audio
// ---------------------------------------------------------------------------

- (void)playSound:(NSString *)name {
    NSString *path = [[NSBundle mainBundle] pathForResource:name ofType:@"mp3"];
    if (!path) return;
    NSURL *url = [NSURL fileURLWithPath:path];
    NSError *err = nil;
    AVAudioPlayer *player = [[AVAudioPlayer alloc] initWithContentsOfURL:url error:&err];
    if (!player || err) return;
    player.volume = 1.0;
    [player prepareToPlay];
    [player play];
    _audioPlayer = player;
}

// ---------------------------------------------------------------------------
#pragma mark - Actions
// ---------------------------------------------------------------------------

- (void)handleBack {
    if (self.navigationController) {
        for (UIViewController *vc in self.navigationController.viewControllers) {
            if ([vc isKindOfClass:[NGLevelSelectViewController class]]) {
                [self.navigationController popToViewController:vc animated:YES];
                return;
            }
        }
        [self.navigationController popViewControllerAnimated:YES];
    } else {
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

/// 重置游戏状态（不含广告逻辑）
- (void)performGameReset {
    NSLog(@"[游戏] 执行关卡重置：清除完成界面、恢复生命值、重新加载谜题");
    [_completionOverlay removeFromSuperview];
    _completionOverlay = nil;
    _livesRemaining = kMaxLives;
    _isCompleted    = NO;
    [self rebuildLivesStack];
    [_gridView loadPuzzle:_puzzle];
    _gridView.selectedColorIndex = 1;
    [self buildColorPalette];
    [self updateModeButtons];
}

/// 头部"重新开始"按钮 → 重置游戏后展示插页广告
- (void)handleRestart {
    NSLog(@"[广告规则] 用户点击「重新开始」按钮，开始重置关卡界面");
    [self performGameReset];

    // 关卡界面已切换完成，在下一个 run loop 帧显示插页广告
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"[广告规则] 关卡界面切换完成，准备展示插页广告");
        [VTAdProxy vt_displayInterstitialPostRestart];
    });
}

- (void)handleFillMode {
    _gridView.fillMode = NGFillModeFill;
    [self updateModeButtons];
}

- (void)handleMarkXMode {
    _gridView.fillMode = NGFillModeMarkX;
    [self updateModeButtons];
}

// ---------------------------------------------------------------------------
#pragma mark - Hint 广告逻辑
// ---------------------------------------------------------------------------

/// Hint 按钮点击：有次数直接使用，没有次数弹出观看广告弹窗
- (void)handleHint {
    if (_hintCredits > 0) {
        NSLog(@"[提示功能] 使用1次提示次数，使用前剩余: %ld次", (long)_hintCredits);
        _hintCredits--;
        [self updateHintBadge];
        [_gridView showHintStripe];
        NSLog(@"[提示功能] 提示已触发，使用后剩余: %ld次", (long)_hintCredits);
    } else {
        NSLog(@"[提示功能] 提示次数为0，弹出「观看广告获得提示」对话框");
        [self showWatchAdDialog];
    }
}

/// 更新 Hint 按钮角标：无次数显示广告标识，有次数显示剩余数量
- (void)updateHintBadge {
    if (!_hintBadge) return;
    if (_hintCredits > 0) {
        _hintBadge.text = [NSString stringWithFormat:@" %ld ", (long)_hintCredits];
        _hintBadge.backgroundColor = [UIColor colorWithRed:0.2 green:0.7 blue:0.3 alpha:1.0];
        NSLog(@"[提示功能] 更新角标：剩余 %ld 次提示", (long)_hintCredits);
    } else {
        _hintBadge.text = @" ▶ ";
        _hintBadge.backgroundColor = [UIColor colorWithRed:1.0 green:0.45 blue:0.0 alpha:1.0];
        NSLog(@"[提示功能] 更新角标：显示广告标识（无剩余次数）");
    }
}

// ---------------------------------------------------------------------------
#pragma mark - 观看广告对话框 + 横幅广告
// ---------------------------------------------------------------------------

/// 弹出"是否观看视频获得提示"对话框，同时在底部显示横幅广告（同层级）
- (void)showWatchAdDialog {
    if (_adDialogOverlay) {
        NSLog(@"[广告对话框] 对话框已经在显示中，跳过重复弹出");
        return;
    }
    NSLog(@"[广告对话框] 弹出观看视频对话框，同步展示横幅广告");

    // 创建全屏半透明遮罩
    UIView *overlay = [[UIView alloc] init];
    overlay.backgroundColor = [UIColor colorWithWhite:0 alpha:0.72];
    overlay.translatesAutoresizingMaskIntoConstraints = NO;
    overlay.alpha = 0;
    [self.view addSubview:overlay];
    _adDialogOverlay = overlay;

    [NSLayoutConstraint activateConstraints:@[
        [overlay.topAnchor constraintEqualToAnchor:self.view.topAnchor],
        [overlay.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
        [overlay.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [overlay.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
    ]];

    // 将横幅广告嵌入到遮罩层（与对话框同层级，底部对齐）
    [VTAdProxy vt_embedBannerIn:overlay];
    NSLog(@"[横幅广告] 横幅广告已嵌入对话框遮罩层底部");

    // 对话框卡片
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [NGTheme cardBackgroundColor];
    card.layer.cornerRadius = [NGTheme cardCornerRadius];
    card.layer.shadowColor  = UIColor.blackColor.CGColor;
    card.layer.shadowOffset = CGSizeMake(0, 8);
    card.layer.shadowRadius = 20;
    card.layer.shadowOpacity = 0.5;
    card.translatesAutoresizingMaskIntoConstraints = NO;
    [overlay addSubview:card];

    // 广告图标
    UIImageView *adIcon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"play.rectangle.fill"]];
    adIcon.tintColor = [UIColor colorWithRed:1.0 green:0.55 blue:0.0 alpha:1.0];
    adIcon.contentMode = UIViewContentModeScaleAspectFit;
    adIcon.translatesAutoresizingMaskIntoConstraints = NO;
    [adIcon.widthAnchor constraintEqualToConstant:40].active = YES;
    [adIcon.heightAnchor constraintEqualToConstant:40].active = YES;

    UILabel *titleLbl = [[UILabel alloc] init];
    titleLbl.text = @"Watch an Ad for a Hint?";
    titleLbl.font = [NGTheme headerFontWithSize:18];
    titleLbl.textColor = [NGTheme clueTextColor];
    titleLbl.textAlignment = NSTextAlignmentCenter;
    titleLbl.numberOfLines = 0;

    UILabel *msgLbl = [[UILabel alloc] init];
    msgLbl.text = @"Watch a short video to earn 1 Hint usage.\nThe hint will reveal one row or column.";
    msgLbl.font = [NGTheme bodyFontWithSize:13];
    msgLbl.textColor = [NGTheme clueCompletedTextColor];
    msgLbl.textAlignment = NSTextAlignmentCenter;
    msgLbl.numberOfLines = 0;

    // 观看视频按钮
    UIButton *watchBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    watchBtn.backgroundColor = [UIColor colorWithRed:1.0 green:0.45 blue:0.0 alpha:1.0];
    [watchBtn setTitle:@"▶  Watch Video" forState:UIControlStateNormal];
    watchBtn.titleLabel.font = [NGTheme bodyFontWithSize:15];
    [watchBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    watchBtn.layer.cornerRadius = 12;
    watchBtn.clipsToBounds = YES;
    watchBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [watchBtn addTarget:self action:@selector(handleWatchVideo) forControlEvents:UIControlEventTouchUpInside];

    // 稍后再说按钮
    UIButton *cancelBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    [cancelBtn setTitle:@"Maybe Later" forState:UIControlStateNormal];
    cancelBtn.titleLabel.font = [NGTheme bodyFontWithSize:14];
    [cancelBtn setTitleColor:[NGTheme accentColor] forState:UIControlStateNormal];
    cancelBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [cancelBtn addTarget:self action:@selector(dismissAdDialog) forControlEvents:UIControlEventTouchUpInside];

    UIStackView *stack = [[UIStackView alloc] initWithArrangedSubviews:@[adIcon, titleLbl, msgLbl, watchBtn, cancelBtn]];
    stack.axis = UILayoutConstraintAxisVertical;
    stack.spacing = 12;
    stack.alignment = UIStackViewAlignmentCenter;
    stack.translatesAutoresizingMaskIntoConstraints = NO;
    [card addSubview:stack];

    // 卡片位置：整体偏上避免被底部横幅广告遮挡
    [NSLayoutConstraint activateConstraints:@[
        [card.centerXAnchor constraintEqualToAnchor:overlay.centerXAnchor],
        [card.centerYAnchor constraintEqualToAnchor:overlay.centerYAnchor constant:-50],
        [card.widthAnchor constraintEqualToAnchor:overlay.widthAnchor multiplier:0.84],

        [stack.topAnchor constraintEqualToAnchor:card.topAnchor constant:24],
        [stack.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:20],
        [stack.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-20],
        [stack.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-24],

        [watchBtn.widthAnchor constraintEqualToAnchor:stack.widthAnchor],
        [watchBtn.heightAnchor constraintEqualToConstant:48],
    ]];

    // 入场动画
    card.transform = CGAffineTransformMakeScale(0.85, 0.85);
    [UIView animateWithDuration:0.35 delay:0
         usingSpringWithDamping:0.8 initialSpringVelocity:0.5 options:0 animations:^{
        overlay.alpha = 1.0;
        card.transform = CGAffineTransformIdentity;
    } completion:nil];
}

/// 关闭广告对话框，同时隐藏横幅广告
- (void)dismissAdDialog {
    NSLog(@"[广告对话框] 关闭对话框，同步收起横幅广告");
    [VTAdProxy vt_dismissOverlay];

    UIView *overlay = _adDialogOverlay;
    _adDialogOverlay = nil;
    if (!overlay) return;

    [UIView animateWithDuration:0.2 animations:^{
        overlay.alpha = 0;
    } completion:^(BOOL f) {
        [overlay removeFromSuperview];
        NSLog(@"[广告对话框] 对话框与横幅广告已完全关闭");
    }];
}

/// 用户点击"观看视频" → 关闭对话框 → 播放激励视频广告
- (void)handleWatchVideo {
    NSLog(@"[激励视频] 用户选择观看视频，关闭弹窗并启动激励视频广告");
    [self dismissAdDialog];

    __weak typeof(self) weakSelf = self;
    [VTAdProxy vt_startRewardedWithHandler:^(BOOL earned) {
        dispatch_async(dispatch_get_main_queue(), ^{
            __strong typeof(weakSelf) self = weakSelf;
            if (!self) return;

            if (earned) {
                NSLog(@"[激励视频] ✅ 用户完整观看视频，获得奖励，直接执行提示功能");
                [self showTopToast:@"Reward earned! Hint activated ✓"];
                // 成功看完广告后直接触发提示功能
                [self->_gridView showHintStripe];
            } else {
                NSLog(@"[激励视频] ❌ 视频未完整观看或广告未加载，未获得奖励");
                [self showTopToast:@"No reward. Watch the full video to earn a hint."];
            }
        });
    }];
}

// ---------------------------------------------------------------------------
#pragma mark - 顶部 Toast 提示
// ---------------------------------------------------------------------------

/// 在界面顶部显示小型提示条，2.5 秒后自动消失，无按钮
- (void)showTopToast:(NSString *)message {
    NSLog(@"[Toast提示] 显示顶部提示：%@", message);

    UIView *container = [[UIView alloc] init];
    container.backgroundColor = [UIColor colorWithWhite:0.08 alpha:0.88];
    container.layer.cornerRadius = 8;
    container.clipsToBounds = YES;
    container.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *label = [[UILabel alloc] init];
    label.text = message;
    label.font = [NGTheme bodyFontWithSize:12.5];
    label.textColor = UIColor.whiteColor;
    label.textAlignment = NSTextAlignmentCenter;
    label.numberOfLines = 0;
    label.translatesAutoresizingMaskIntoConstraints = NO;
    [container addSubview:label];

    [NSLayoutConstraint activateConstraints:@[
        [label.topAnchor constraintEqualToAnchor:container.topAnchor constant:8],
        [label.bottomAnchor constraintEqualToAnchor:container.bottomAnchor constant:-8],
        [label.leadingAnchor constraintEqualToAnchor:container.leadingAnchor constant:14],
        [label.trailingAnchor constraintEqualToAnchor:container.trailingAnchor constant:-14],
    ]];

    [self.view addSubview:container];
    [self.view bringSubviewToFront:container];

    UILayoutGuide *safe = self.view.safeAreaLayoutGuide;
    [NSLayoutConstraint activateConstraints:@[
        [container.topAnchor constraintEqualToAnchor:safe.topAnchor constant:10],
        [container.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor],
        [container.widthAnchor constraintLessThanOrEqualToAnchor:self.view.widthAnchor constant:-60],
    ]];

    container.alpha = 0;
    [UIView animateWithDuration:0.3 animations:^{
        container.alpha = 1.0;
    } completion:^(BOOL f) {
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            [UIView animateWithDuration:0.3 animations:^{
                container.alpha = 0;
            } completion:^(BOOL f2) {
                [container removeFromSuperview];
            }];
        });
    }];
}

// ---------------------------------------------------------------------------
#pragma mark - 其他按钮动作
// ---------------------------------------------------------------------------

- (void)handleHelp {
    [NGHowToPlayView show:self.view];
}

- (void)handleColorSelected:(UIButton *)sender {
    _gridView.selectedColorIndex = sender.tag;
    _gridView.fillMode = NGFillModeFill;
    [self buildColorPalette];
    [self updateModeButtons];
}

- (void)updateModeButtons {
    BOOL fill = (_gridView.fillMode == NGFillModeFill);
    _fillButton.backgroundColor  = fill ? [NGTheme buttonPrimaryColor] : [NGTheme buttonSecondaryColor];
    _markXButton.backgroundColor = fill ? [NGTheme buttonSecondaryColor] : [NGTheme buttonPrimaryColor];
}

// ---------------------------------------------------------------------------
#pragma mark - Delegate
// ---------------------------------------------------------------------------

- (void)puzzleGridView:(NGPuzzleGridView *)gv didTapCellAtRow:(NSInteger)r col:(NSInteger)c correct:(BOOL)correct {
    if (correct) {
        [self playSound:@"excat_nonogarm_action_003"];
    } else if (!_isCompleted) {
        [self playSound:@"excat_nonogarm_mistake_002"];
        _livesRemaining--;
        [self rebuildLivesStack];
        if (_livesRemaining <= 0) [self showGameOverOverlay];
    }
}

- (void)puzzleGridViewDidComplete:(NGPuzzleGridView *)gv {
    _isCompleted = YES;
    [[NGGameProgress shared] markLevelCompleted:_levelNumber];
    [self showCompletionOverlay];
}

// ---------------------------------------------------------------------------
#pragma mark - Completion Overlay
// ---------------------------------------------------------------------------

- (void)showCompletionOverlay {
    [self playSound:@"excat_nonogarm_success_004"];
    [_completionOverlay removeFromSuperview];

    UIView *overlay = [[UIView alloc] init];
    overlay.backgroundColor = [UIColor colorWithWhite:0 alpha:0.75];
    overlay.translatesAutoresizingMaskIntoConstraints = NO;
    overlay.alpha = 0;
    [self.view addSubview:overlay];
    _completionOverlay = overlay;

    [NSLayoutConstraint activateConstraints:@[
        [overlay.topAnchor constraintEqualToAnchor:self.view.topAnchor],
        [overlay.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
        [overlay.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [overlay.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
    ]];

    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [NGTheme cardBackgroundColor];
    card.layer.cornerRadius = [NGTheme cardCornerRadius];
    card.layer.shadowColor  = UIColor.blackColor.CGColor;
    card.layer.shadowOffset = CGSizeMake(0, 10);
    card.layer.shadowRadius = 24;
    card.layer.shadowOpacity = 0.55;
    card.translatesAutoresizingMaskIntoConstraints = NO;
    [overlay addSubview:card];

    CGFloat previewSz = 140.0;
    UIImageView *previewImg = [[UIImageView alloc] init];
    previewImg.contentMode = UIViewContentModeScaleAspectFill;
    previewImg.clipsToBounds = YES;
    previewImg.layer.cornerRadius = 12.0;
    previewImg.layer.borderWidth  = 2.0;
    previewImg.layer.borderColor  = [UIColor colorWithWhite:1.0 alpha:0.12].CGColor;
    previewImg.image = [NGTheme previewImageForPuzzle:_puzzle size:CGSizeMake(previewSz, previewSz)];
    previewImg.translatesAutoresizingMaskIntoConstraints = NO;

    NSInteger stars = (_livesRemaining == 3) ? 3 : (_livesRemaining == 2) ? 3 : (_livesRemaining == 1) ? 2 : 1;
    UIStackView *starsRow = [self makeStarsView:stars];
    starsRow.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *titleLbl = [[UILabel alloc] init];
    titleLbl.text = @"Puzzle Complete!";
    titleLbl.font = [NGTheme headerFontWithSize:22];
    titleLbl.textColor = [NGTheme clueTextColor];
    titleLbl.textAlignment = NSTextAlignmentCenter;

    UILabel *subLbl = [[UILabel alloc] init];
    subLbl.text = [NSString stringWithFormat:@"Level %ld  ·  %@", (long)_levelNumber, _puzzle.name];
    subLbl.font = [NGTheme bodyFontWithSize:13];
    subLbl.textColor = [NGTheme clueCompletedTextColor];
    subLbl.textAlignment = NSTextAlignmentCenter;

    BOOL hasNext = (_levelNumber + 1 <= [NGLevelData totalLevelCount]);
    UIButton *nextBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    nextBtn.backgroundColor = [NGTheme buttonPrimaryColor];
    NSString *nextTitle = hasNext ? @"Next Level  →" : @"🎉  All Done!";
    [nextBtn setTitle:nextTitle forState:UIControlStateNormal];
    nextBtn.titleLabel.font = [NGTheme bodyFontWithSize:15];
    [nextBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    nextBtn.layer.cornerRadius = 12;
    nextBtn.clipsToBounds = YES;
    nextBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [nextBtn addTarget:self action:@selector(handleNextLevel) forControlEvents:UIControlEventTouchUpInside];

    UIButton *menuBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    [menuBtn setTitle:@"Level Select" forState:UIControlStateNormal];
    menuBtn.titleLabel.font = [NGTheme bodyFontWithSize:14];
    [menuBtn setTitleColor:[NGTheme accentColor] forState:UIControlStateNormal];
    menuBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [menuBtn addTarget:self action:@selector(handleBack) forControlEvents:UIControlEventTouchUpInside];

    UIStackView *stack = [[UIStackView alloc] initWithArrangedSubviews:@[
        previewImg, starsRow, titleLbl, subLbl, nextBtn, menuBtn
    ]];
    stack.axis = UILayoutConstraintAxisVertical;
    stack.spacing = 10;
    stack.alignment = UIStackViewAlignmentCenter;
    stack.translatesAutoresizingMaskIntoConstraints = NO;
    [card addSubview:stack];

    [NSLayoutConstraint activateConstraints:@[
        [card.centerXAnchor constraintEqualToAnchor:overlay.centerXAnchor],
        [card.centerYAnchor constraintEqualToAnchor:overlay.centerYAnchor],
        [card.widthAnchor constraintEqualToAnchor:overlay.widthAnchor multiplier:0.84],

        [stack.topAnchor constraintEqualToAnchor:card.topAnchor constant:24],
        [stack.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:20],
        [stack.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-20],
        [stack.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-24],

        [previewImg.widthAnchor constraintEqualToConstant:previewSz],
        [previewImg.heightAnchor constraintEqualToConstant:previewSz],

        [nextBtn.widthAnchor constraintEqualToAnchor:stack.widthAnchor],
        [nextBtn.heightAnchor constraintEqualToConstant:48],
    ]];

    card.transform = CGAffineTransformMakeScale(0.85, 0.85);
    [UIView animateWithDuration:0.4 delay:0.05
         usingSpringWithDamping:0.78 initialSpringVelocity:0.6 options:0 animations:^{
        overlay.alpha = 1;
        card.transform = CGAffineTransformIdentity;
    } completion:nil];
}

- (UIStackView *)makeStarsView:(NSInteger)stars {
    UIStackView *row = [[UIStackView alloc] init];
    row.axis = UILayoutConstraintAxisHorizontal;
    row.spacing = 4;
    row.alignment = UIStackViewAlignmentCenter;
    for (NSInteger i = 1; i <= 3; i++) {
        UIImageView *star = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:(i <= stars) ? @"star.fill" : @"star"]];
        star.tintColor = (i <= stars) ? [NGTheme goldColor] : [NGTheme livesInactiveColor];
        star.contentMode = UIViewContentModeScaleAspectFit;
        [star.widthAnchor constraintEqualToConstant:26].active = YES;
        [star.heightAnchor constraintEqualToConstant:26].active = YES;
        [row addArrangedSubview:star];
    }
    return row;
}

// ---------------------------------------------------------------------------
#pragma mark - Game Over Overlay
// ---------------------------------------------------------------------------

- (void)showGameOverOverlay {
    [self playSound:@"excat_nonogarm_defeat_001"];
    [_completionOverlay removeFromSuperview];

    UIView *overlay = [[UIView alloc] init];
    overlay.backgroundColor = [UIColor colorWithWhite:0 alpha:0.75];
    overlay.translatesAutoresizingMaskIntoConstraints = NO;
    overlay.alpha = 0;
    [self.view addSubview:overlay];
    _completionOverlay = overlay;

    [NSLayoutConstraint activateConstraints:@[
        [overlay.topAnchor constraintEqualToAnchor:self.view.topAnchor],
        [overlay.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
        [overlay.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [overlay.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
    ]];

    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [NGTheme cardBackgroundColor];
    card.layer.cornerRadius = [NGTheme cardCornerRadius];
    card.translatesAutoresizingMaskIntoConstraints = NO;
    [overlay addSubview:card];

    UILabel *emoji = [[UILabel alloc] init];
    emoji.text = @"💔";
    emoji.font = [UIFont systemFontOfSize:52];
    emoji.textAlignment = NSTextAlignmentCenter;

    UILabel *titleLbl = [[UILabel alloc] init];
    titleLbl.text = @"No Lives Left";
    titleLbl.font = [NGTheme headerFontWithSize:22];
    titleLbl.textColor = [NGTheme clueTextColor];
    titleLbl.textAlignment = NSTextAlignmentCenter;

    UILabel *sub = [[UILabel alloc] init];
    sub.text = @"Logic is the key — try again!";
    sub.font = [NGTheme bodyFontWithSize:13];
    sub.textColor = [NGTheme clueCompletedTextColor];
    sub.textAlignment = NSTextAlignmentCenter;

    UIButton *retryBtn = [UIButton buttonWithType:UIButtonTypeCustom];
    retryBtn.backgroundColor = [NGTheme livesActiveColor];
    [retryBtn setTitle:@"Try Again" forState:UIControlStateNormal];
    retryBtn.titleLabel.font = [NGTheme bodyFontWithSize:15];
    [retryBtn setTitleColor:[UIColor whiteColor] forState:UIControlStateNormal];
    retryBtn.layer.cornerRadius = 12;
    retryBtn.clipsToBounds = YES;
    retryBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [retryBtn addTarget:self action:@selector(handleRetry) forControlEvents:UIControlEventTouchUpInside];

    UIButton *backBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    [backBtn setTitle:@"Level Select" forState:UIControlStateNormal];
    backBtn.titleLabel.font = [NGTheme bodyFontWithSize:14];
    [backBtn setTitleColor:[NGTheme accentColor] forState:UIControlStateNormal];
    backBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [backBtn addTarget:self action:@selector(handleBack) forControlEvents:UIControlEventTouchUpInside];

    UIStackView *stack = [[UIStackView alloc] initWithArrangedSubviews:@[emoji, titleLbl, sub, retryBtn, backBtn]];
    stack.axis = UILayoutConstraintAxisVertical;
    stack.spacing = 12;
    stack.alignment = UIStackViewAlignmentCenter;
    stack.translatesAutoresizingMaskIntoConstraints = NO;
    [card addSubview:stack];

    [NSLayoutConstraint activateConstraints:@[
        [card.centerXAnchor constraintEqualToAnchor:overlay.centerXAnchor],
        [card.centerYAnchor constraintEqualToAnchor:overlay.centerYAnchor],
        [card.widthAnchor constraintEqualToAnchor:overlay.widthAnchor multiplier:0.82],

        [stack.topAnchor constraintEqualToAnchor:card.topAnchor constant:28],
        [stack.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:20],
        [stack.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-20],
        [stack.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-28],

        [retryBtn.widthAnchor constraintEqualToAnchor:stack.widthAnchor],
        [retryBtn.heightAnchor constraintEqualToConstant:48],
    ]];

    [UIView animateWithDuration:0.3 animations:^{ overlay.alpha = 1; }];
}

/// 游戏失败界面"Try Again" → 仅重置游戏，不触发广告
- (void)handleRetry {
    NSLog(@"[游戏] 用户点击「Try Again」，仅重置游戏状态，不触发插页广告");
    [self performGameReset];
}

- (void)handleNextLevel {
    NSInteger next = _levelNumber + 1;
    if (next > [NGLevelData totalLevelCount]) { [self handleBack]; return; }
    NGGameViewController *vc = [[NGGameViewController alloc] initWithLevel:next];
    if (self.navigationController) {
        NSMutableArray *vcs = [self.navigationController.viewControllers mutableCopy];
        [vcs removeLastObject];
        [vcs addObject:vc];
        [self.navigationController setViewControllers:vcs animated:YES];
    }
}

@end
