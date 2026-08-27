//
//  NGLevelSelectViewController.m
//  excat_nonogarm
//
//  Level selection grid. States: completed ✓, unlocked (playable), locked 🔒.

#import "NGLevelSelectViewController.h"
#import "NGGameViewController.h"
#import "NGSettingsViewController.h"
#import "NGLevelData.h"
#import "NGGameProgress.h"
#import "NGTheme.h"
#import <objc/runtime.h>

static NSString * const kCellID = @"LevelCell";

// ---------------------------------------------------------------------------
#pragma mark - Level Cell
// ---------------------------------------------------------------------------

@interface NGLevelCell : UICollectionViewCell
- (void)configureForLevel:(NSInteger)level
                completed:(BOOL)completed
                 unlocked:(BOOL)unlocked
                  current:(BOOL)current;
@end

@implementation NGLevelCell {
    UILabel   *_numberLabel;
    UILabel   *_checkLabel;
    UIImageView *_lockIcon;
    UIView    *_badgeView;
}

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (!self) return nil;

    self.contentView.layer.cornerRadius  = 14.0;
    self.contentView.layer.masksToBounds = YES;
    self.contentView.backgroundColor = [NGTheme levelUnlockedColor];

    // Border glow ring (shown when current)
    self.layer.cornerRadius  = 14.0;
    self.layer.borderWidth   = 0;
    self.layer.masksToBounds = NO;

    // Number label
    _numberLabel = [[UILabel alloc] init];
    _numberLabel.textAlignment = NSTextAlignmentCenter;
    _numberLabel.font = [NGTheme monoFontWithSize:17.0];
    _numberLabel.translatesAutoresizingMaskIntoConstraints = NO;
    [self.contentView addSubview:_numberLabel];

    // Check mark label (completed)
    _checkLabel = [[UILabel alloc] init];
    _checkLabel.text = @"✓";
    _checkLabel.textAlignment = NSTextAlignmentCenter;
    _checkLabel.font = [UIFont systemFontOfSize:10 weight:UIFontWeightBold];
    _checkLabel.hidden = YES;
    _checkLabel.translatesAutoresizingMaskIntoConstraints = NO;
    [self.contentView addSubview:_checkLabel];

    // Lock icon
    _lockIcon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"lock.fill"]];
    _lockIcon.contentMode = UIViewContentModeScaleAspectFit;
    _lockIcon.tintColor = [UIColor colorWithWhite:1.0 alpha:0.20];
    _lockIcon.hidden = YES;
    _lockIcon.translatesAutoresizingMaskIntoConstraints = NO;
    [self.contentView addSubview:_lockIcon];

    [NSLayoutConstraint activateConstraints:@[
        [_numberLabel.centerXAnchor constraintEqualToAnchor:self.contentView.centerXAnchor],
        [_numberLabel.centerYAnchor constraintEqualToAnchor:self.contentView.centerYAnchor],

        [_checkLabel.trailingAnchor constraintEqualToAnchor:self.contentView.trailingAnchor constant:-6],
        [_checkLabel.topAnchor constraintEqualToAnchor:self.contentView.topAnchor constant:6],

        [_lockIcon.centerXAnchor constraintEqualToAnchor:self.contentView.centerXAnchor],
        [_lockIcon.centerYAnchor constraintEqualToAnchor:self.contentView.centerYAnchor],
        [_lockIcon.widthAnchor constraintEqualToConstant:20],
        [_lockIcon.heightAnchor constraintEqualToConstant:20],
    ]];

    return self;
}

- (void)configureForLevel:(NSInteger)level
                completed:(BOOL)completed
                 unlocked:(BOOL)unlocked
                  current:(BOOL)current {

    if (!unlocked) {
        // Locked
        self.contentView.backgroundColor = [NGTheme levelLockedColor];
        _numberLabel.text = [NSString stringWithFormat:@"%ld", (long)level];
        _numberLabel.textColor = [UIColor colorWithWhite:1.0 alpha:0.18];
        _lockIcon.hidden  = NO;
        _checkLabel.hidden = YES;
        _numberLabel.hidden = YES;
        self.layer.borderWidth = 0;
        self.layer.borderColor = nil;
        self.layer.shadowOpacity = 0;
    } else if (completed) {
        // Completed — green tint with checkmark
        self.contentView.backgroundColor = [NGTheme levelCompletedColor];
        _numberLabel.text = [NSString stringWithFormat:@"%ld", (long)level];
        _numberLabel.textColor = [NGTheme accentSecondaryColor];
        _numberLabel.hidden = NO;
        _lockIcon.hidden  = YES;
        _checkLabel.hidden = NO;
        _checkLabel.textColor = [NGTheme accentSecondaryColor];
        self.layer.borderWidth  = 0;
        self.layer.borderColor  = nil;
        self.layer.shadowOpacity = 0;
    } else {
        // Unlocked but not completed
        self.contentView.backgroundColor = [NGTheme levelUnlockedColor];
        _numberLabel.text = [NSString stringWithFormat:@"%ld", (long)level];
        _numberLabel.textColor = [NGTheme clueTextColor];
        _numberLabel.hidden = NO;
        _lockIcon.hidden   = YES;
        _checkLabel.hidden = YES;

        if (current) {
            // Current next level — glowing border
            self.layer.borderWidth  = 2.0;
            self.layer.borderColor  = [NGTheme levelCurrentBorderColor].CGColor;
            self.layer.shadowColor  = [NGTheme accentColor].CGColor;
            self.layer.shadowOffset  = CGSizeZero;
            self.layer.shadowRadius  = 8.0;
            self.layer.shadowOpacity = 0.6;
            _numberLabel.textColor  = [NGTheme accentColor];
        } else {
            self.layer.borderWidth  = 0;
            self.layer.borderColor  = nil;
            self.layer.shadowOpacity = 0;
            _numberLabel.textColor  = [NGTheme clueTextColor];
        }
    }
}
@end

// ---------------------------------------------------------------------------
#pragma mark - Level Select VC
// ---------------------------------------------------------------------------

@interface NGLevelSelectViewController () <UICollectionViewDataSource, UICollectionViewDelegate>
@property (nonatomic, strong) UICollectionView *collectionView;
@end

@implementation NGLevelSelectViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [NGTheme appBackgroundColor];
    [self buildHeader];
    [self buildCollectionView];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [_collectionView reloadData];
}

// ---------------------------------------------------------------------------
#pragma mark - Build UI
// ---------------------------------------------------------------------------

- (void)buildHeader {
    UIView *headerBg = [[UIView alloc] init];
    headerBg.backgroundColor = [NGTheme headerBackgroundColor];
    headerBg.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view addSubview:headerBg];

    // Bottom separator
    UIView *sep = [[UIView alloc] init];
    sep.backgroundColor = [NGTheme separatorColor];
    sep.translatesAutoresizingMaskIntoConstraints = NO;
    [headerBg addSubview:sep];

    UILabel *title = [[UILabel alloc] init];
    title.text = @"Choose Level";
    title.font = [NGTheme headerFontWithSize:24.0];
    title.textColor = [NGTheme clueTextColor];
    title.translatesAutoresizingMaskIntoConstraints = NO;
    [headerBg addSubview:title];

    // Settings gear button at top-right
    UIButton *settingsBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    UIImageSymbolConfiguration *cfg = [UIImageSymbolConfiguration configurationWithPointSize:20 weight:UIImageSymbolWeightMedium];
    [settingsBtn setImage:[UIImage systemImageNamed:@"gearshape" withConfiguration:cfg] forState:UIControlStateNormal];
    settingsBtn.tintColor = [UIColor colorWithWhite:1.0 alpha:0.55];
    settingsBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [settingsBtn addTarget:self action:@selector(handleSettings) forControlEvents:UIControlEventTouchUpInside];
    [headerBg addSubview:settingsBtn];

    NGGameProgress *prog = [NGGameProgress shared];
    NSInteger done = [prog completedLevelCount];
    NSInteger total = [NGLevelData totalLevelCount];
    UILabel *progressLabel = [[UILabel alloc] init];
    progressLabel.text = [NSString stringWithFormat:@"%ld / %ld Completed", (long)done, (long)total];
    progressLabel.font = [NGTheme bodyFontWithSize:13.0];
    progressLabel.textColor = [NGTheme clueCompletedTextColor];
    progressLabel.translatesAutoresizingMaskIntoConstraints = NO;
    [headerBg addSubview:progressLabel];

    // Progress bar
    UIView *barBg = [[UIView alloc] init];
    barBg.backgroundColor = [UIColor colorWithWhite:1.0 alpha:0.08];
    barBg.layer.cornerRadius = 3.0;
    barBg.translatesAutoresizingMaskIntoConstraints = NO;
    [headerBg addSubview:barBg];

    UIView *barFill = [[UIView alloc] init];
    CGFloat ratio = total > 0 ? (CGFloat)done / total : 0;
    barFill.backgroundColor = [NGTheme accentColor];
    barFill.layer.cornerRadius = 3.0;
    barFill.translatesAutoresizingMaskIntoConstraints = NO;
    [barBg addSubview:barFill];

    [NSLayoutConstraint activateConstraints:@[
        [headerBg.topAnchor constraintEqualToAnchor:self.view.topAnchor],
        [headerBg.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [headerBg.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],

        [title.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor constant:16],
        [title.leadingAnchor constraintEqualToAnchor:headerBg.leadingAnchor constant:20],

        [settingsBtn.centerYAnchor constraintEqualToAnchor:title.centerYAnchor],
        [settingsBtn.trailingAnchor constraintEqualToAnchor:headerBg.trailingAnchor constant:-16],
        [settingsBtn.widthAnchor constraintEqualToConstant:40],
        [settingsBtn.heightAnchor constraintEqualToConstant:40],

        [progressLabel.topAnchor constraintEqualToAnchor:title.bottomAnchor constant:4],
        [progressLabel.leadingAnchor constraintEqualToAnchor:title.leadingAnchor],

        [barBg.topAnchor constraintEqualToAnchor:progressLabel.bottomAnchor constant:8],
        [barBg.leadingAnchor constraintEqualToAnchor:headerBg.leadingAnchor constant:20],
        [barBg.trailingAnchor constraintEqualToAnchor:headerBg.trailingAnchor constant:-20],
        [barBg.heightAnchor constraintEqualToConstant:4],
        [barBg.bottomAnchor constraintEqualToAnchor:headerBg.bottomAnchor constant:-14],

        [barFill.topAnchor constraintEqualToAnchor:barBg.topAnchor],
        [barFill.bottomAnchor constraintEqualToAnchor:barBg.bottomAnchor],
        [barFill.leadingAnchor constraintEqualToAnchor:barBg.leadingAnchor],
        [barFill.widthAnchor constraintEqualToAnchor:barBg.widthAnchor multiplier:ratio],

        [sep.bottomAnchor constraintEqualToAnchor:headerBg.bottomAnchor],
        [sep.leadingAnchor constraintEqualToAnchor:headerBg.leadingAnchor],
        [sep.trailingAnchor constraintEqualToAnchor:headerBg.trailingAnchor],
        [sep.heightAnchor constraintEqualToConstant:1],
    ]];

    // Anchor collection view top to headerBg bottom
    self.view.tag = (NSInteger)headerBg.hash;  // store ref via tag workaround
    objc_setAssociatedObject(self, "headerBg", headerBg, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)buildCollectionView {
    UICollectionViewFlowLayout *layout = [[UICollectionViewFlowLayout alloc] init];
    layout.minimumInteritemSpacing = 10;
    layout.minimumLineSpacing = 10;
    layout.sectionInset = UIEdgeInsetsMake(16, 16, 24, 16);

    _collectionView = [[UICollectionView alloc] initWithFrame:CGRectZero
                                         collectionViewLayout:layout];
    _collectionView.backgroundColor = [UIColor clearColor];
    _collectionView.dataSource = self;
    _collectionView.delegate   = self;
    _collectionView.showsVerticalScrollIndicator = NO;
    _collectionView.translatesAutoresizingMaskIntoConstraints = NO;
    [_collectionView registerClass:[NGLevelCell class] forCellWithReuseIdentifier:kCellID];
    [self.view addSubview:_collectionView];

    UIView *headerBg = objc_getAssociatedObject(self, "headerBg");
    [NSLayoutConstraint activateConstraints:@[
        [_collectionView.topAnchor constraintEqualToAnchor:headerBg.bottomAnchor],
        [_collectionView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [_collectionView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [_collectionView.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
    ]];
}

// ---------------------------------------------------------------------------
#pragma mark - UICollectionViewDataSource
// ---------------------------------------------------------------------------

- (NSInteger)collectionView:(UICollectionView *)cv numberOfItemsInSection:(NSInteger)section {
    return [NGLevelData totalLevelCount];
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)cv
                  cellForItemAtIndexPath:(NSIndexPath *)indexPath {
    NGLevelCell *cell = [cv dequeueReusableCellWithReuseIdentifier:kCellID forIndexPath:indexPath];
    NSInteger level = indexPath.item + 1;
    NGGameProgress *prog = [NGGameProgress shared];
    NSInteger highUnlocked = [prog highestUnlockedLevel];
    BOOL completed = [prog isLevelCompleted:level];
    BOOL unlocked  = (level <= highUnlocked);
    BOOL current   = (level == highUnlocked && !completed);
    [cell configureForLevel:level completed:completed unlocked:unlocked current:current];
    return cell;
}

// ---------------------------------------------------------------------------
#pragma mark - UICollectionViewDelegate
// ---------------------------------------------------------------------------

- (void)collectionView:(UICollectionView *)cv didSelectItemAtIndexPath:(NSIndexPath *)indexPath {
    NSInteger level = indexPath.item + 1;
    NGGameProgress *prog = [NGGameProgress shared];
    if (level > [prog highestUnlockedLevel]) return; // locked

    NGGameViewController *vc = [[NGGameViewController alloc] initWithLevel:level];
    [self.navigationController pushViewController:vc animated:YES];
}

- (void)handleSettings {
    NGSettingsViewController *vc = [[NGSettingsViewController alloc] init];
    [self.navigationController pushViewController:vc animated:YES];
}

// ---------------------------------------------------------------------------
#pragma mark - UICollectionViewDelegateFlowLayout
// ---------------------------------------------------------------------------

- (CGSize)collectionView:(UICollectionView *)cv
                  layout:(UICollectionViewLayout *)layout
  sizeForItemAtIndexPath:(NSIndexPath *)indexPath {
    CGFloat width = cv.bounds.size.width;
    UIEdgeInsets inset = ((UICollectionViewFlowLayout *)layout).sectionInset;
    CGFloat spacing = ((UICollectionViewFlowLayout *)layout).minimumInteritemSpacing;
    NSInteger cols = 5;
    CGFloat available = width - inset.left - inset.right - spacing * (cols - 1);
    CGFloat side = floor(available / cols);
    return CGSizeMake(side, side);
}

@end
