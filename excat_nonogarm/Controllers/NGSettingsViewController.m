//
//  NGSettingsViewController.m
//  excat_nonogarm

#import "NGSettingsViewController.h"
#import "NGAboutViewController.h"
#import "NGTermsViewController.h"
#import "NGPrivacyViewController.h"
#import "NGFeedbackViewController.h"
#import "NGTheme.h"
#import "VTAdProxy.h"

// ---------------------------------------------------------------------------
#pragma mark - Settings Row Item
// ---------------------------------------------------------------------------

@interface NGSettingsItem : NSObject
@property (nonatomic, copy)   NSString *icon;
@property (nonatomic, copy)   NSString *title;
@property (nonatomic, copy)   NSString *subtitle;
@property (nonatomic, strong) UIColor  *iconColor;
+ (instancetype)icon:(NSString *)icon
               title:(NSString *)title
            subtitle:(NSString *)subtitle
           iconColor:(UIColor *)color;
@end

@implementation NGSettingsItem
+ (instancetype)icon:(NSString *)icon title:(NSString *)title subtitle:(NSString *)subtitle iconColor:(UIColor *)color {
    NGSettingsItem *it = [NGSettingsItem new];
    it.icon = icon; it.title = title; it.subtitle = subtitle; it.iconColor = color;
    return it;
}
@end

// ---------------------------------------------------------------------------
#pragma mark - Settings Cell
// ---------------------------------------------------------------------------

@interface NGSettingsCell : UITableViewCell
- (void)configureWithItem:(NGSettingsItem *)item;
@end

@implementation NGSettingsCell {
    UIView   *_iconBadge;
    UIImageView *_iconView;
    UILabel  *_titleLabel;
    UILabel  *_subtitleLabel;
    UIImageView *_chevron;
}

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (!self) return nil;
    self.backgroundColor = [UIColor colorWithRed:0.13 green:0.14 blue:0.19 alpha:1.0];
    self.selectionStyle = UITableViewCellSelectionStyleNone;

    _iconBadge = [[UIView alloc] init];
    _iconBadge.layer.cornerRadius = 10;
    _iconBadge.translatesAutoresizingMaskIntoConstraints = NO;

    _iconView = [[UIImageView alloc] init];
    _iconView.contentMode = UIViewContentModeScaleAspectFit;
    _iconView.tintColor = UIColor.whiteColor;
    _iconView.translatesAutoresizingMaskIntoConstraints = NO;
    [_iconBadge addSubview:_iconView];

    _titleLabel = [[UILabel alloc] init];
    _titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightSemibold];
    _titleLabel.textColor = UIColor.whiteColor;
    _titleLabel.translatesAutoresizingMaskIntoConstraints = NO;

    _subtitleLabel = [[UILabel alloc] init];
    _subtitleLabel.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    _subtitleLabel.textColor = [UIColor colorWithWhite:1 alpha:0.45];
    _subtitleLabel.translatesAutoresizingMaskIntoConstraints = NO;

    _chevron = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"chevron.right"]];
    _chevron.tintColor = [UIColor colorWithWhite:1 alpha:0.3];
    _chevron.translatesAutoresizingMaskIntoConstraints = NO;
    _chevron.preferredSymbolConfiguration = [UIImageSymbolConfiguration configurationWithPointSize:12 weight:UIImageSymbolWeightMedium];

    UIStackView *textStack = [[UIStackView alloc] initWithArrangedSubviews:@[_titleLabel, _subtitleLabel]];
    textStack.axis = UILayoutConstraintAxisVertical;
    textStack.spacing = 2;
    textStack.translatesAutoresizingMaskIntoConstraints = NO;

    [self.contentView addSubview:_iconBadge];
    [self.contentView addSubview:textStack];
    [self.contentView addSubview:_chevron];

    [NSLayoutConstraint activateConstraints:@[
        [_iconBadge.leadingAnchor constraintEqualToAnchor:self.contentView.leadingAnchor constant:16],
        [_iconBadge.centerYAnchor constraintEqualToAnchor:self.contentView.centerYAnchor],
        [_iconBadge.widthAnchor constraintEqualToConstant:40],
        [_iconBadge.heightAnchor constraintEqualToConstant:40],

        [_iconView.centerXAnchor constraintEqualToAnchor:_iconBadge.centerXAnchor],
        [_iconView.centerYAnchor constraintEqualToAnchor:_iconBadge.centerYAnchor],
        [_iconView.widthAnchor constraintEqualToConstant:20],
        [_iconView.heightAnchor constraintEqualToConstant:20],

        [textStack.leadingAnchor constraintEqualToAnchor:_iconBadge.trailingAnchor constant:14],
        [textStack.trailingAnchor constraintEqualToAnchor:_chevron.leadingAnchor constant:-10],
        [textStack.centerYAnchor constraintEqualToAnchor:self.contentView.centerYAnchor],

        [_chevron.trailingAnchor constraintEqualToAnchor:self.contentView.trailingAnchor constant:-16],
        [_chevron.centerYAnchor constraintEqualToAnchor:self.contentView.centerYAnchor],
        [_chevron.widthAnchor constraintEqualToConstant:14],
        [_chevron.heightAnchor constraintEqualToConstant:14],

        [self.contentView.heightAnchor constraintGreaterThanOrEqualToConstant:68],
    ]];
    return self;
}

- (void)configureWithItem:(NGSettingsItem *)item {
    _iconBadge.backgroundColor = item.iconColor;
    UIImageSymbolConfiguration *cfg = [UIImageSymbolConfiguration configurationWithPointSize:18 weight:UIImageSymbolWeightMedium];
    _iconView.image = [UIImage systemImageNamed:item.icon withConfiguration:cfg];
    _titleLabel.text = item.title;
    _subtitleLabel.text = item.subtitle;
}

- (void)setHighlighted:(BOOL)highlighted animated:(BOOL)animated {
    [super setHighlighted:highlighted animated:animated];
    [UIView animateWithDuration:0.15 animations:^{
        self.contentView.alpha = highlighted ? 0.6 : 1.0;
    }];
}
@end

// ---------------------------------------------------------------------------
#pragma mark - NGSettingsViewController
// ---------------------------------------------------------------------------

@interface NGSettingsViewController () <UITableViewDataSource, UITableViewDelegate>
@end

@implementation NGSettingsViewController {
    UITableView        *_tableView;
    NSArray<NGSettingsItem *> *_items;
    UILabel            *_copyHintLabel;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0];
    [self buildHeader];
    [self buildTable];
    [self buildSupportFooter];
}

- (void)buildHeader {
    // tableHeaderView must use frame-based layout (no Auto Layout on the view itself)
    CGFloat screenW = UIScreen.mainScreen.bounds.size.width;
    UIView *banner = [[UIView alloc] initWithFrame:CGRectMake(0, 0, screenW, 170)];
    banner.backgroundColor = [UIColor clearColor];

    CGFloat iconSize = 72;
    CGFloat iconX = (screenW - iconSize) / 2.0;
    UIImageView *iconIV = [[UIImageView alloc] initWithFrame:CGRectMake(iconX, 24, iconSize, iconSize)];
    iconIV.image = [UIImage imageNamed:@"AppIconImage"];
    iconIV.contentMode = UIViewContentModeScaleAspectFill;
    iconIV.clipsToBounds = YES;
    iconIV.layer.cornerRadius = 18;
    iconIV.layer.borderWidth = 1.5;
    iconIV.layer.borderColor = [UIColor colorWithWhite:1 alpha:0.20].CGColor;

    UILabel *nameLabel = [[UILabel alloc] init];
    nameLabel.text = @"Nonogram Pixel Puzzle";
    nameLabel.font = [UIFont systemFontOfSize:17 weight:UIFontWeightBold];
    nameLabel.textColor = UIColor.whiteColor;
    nameLabel.textAlignment = NSTextAlignmentCenter;
    [nameLabel sizeToFit];
    nameLabel.frame = CGRectMake(0, CGRectGetMaxY(iconIV.frame) + 10, screenW, nameLabel.bounds.size.height);

    NSString *version = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"] ?: @"1.0";
    UILabel *verLabel = [[UILabel alloc] init];
    verLabel.text = [NSString stringWithFormat:@"Version %@", version];
    verLabel.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    verLabel.textColor = [UIColor colorWithWhite:1 alpha:0.4];
    verLabel.textAlignment = NSTextAlignmentCenter;
    [verLabel sizeToFit];
    verLabel.frame = CGRectMake(0, CGRectGetMaxY(nameLabel.frame) + 4, screenW, verLabel.bounds.size.height);

    CGFloat bannerH = CGRectGetMaxY(verLabel.frame) + 20;
    banner.frame = CGRectMake(0, 0, screenW, bannerH);

    [banner addSubview:iconIV];
    [banner addSubview:nameLabel];
    [banner addSubview:verLabel];

    _tableView = [[UITableView alloc] initWithFrame:CGRectZero style:UITableViewStyleInsetGrouped];
    _tableView.backgroundColor = [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0];
    _tableView.separatorColor = [UIColor colorWithWhite:1 alpha:0.08];
    _tableView.separatorInset = UIEdgeInsetsMake(0, 70, 0, 0);
    _tableView.dataSource = self;
    _tableView.delegate = self;
    _tableView.translatesAutoresizingMaskIntoConstraints = NO;
    _tableView.tableHeaderView = banner;
    [_tableView registerClass:[NGSettingsCell class] forCellReuseIdentifier:@"cell"];
}

- (void)buildTable {
    _items = @[
        [NGSettingsItem icon:@"info.circle.fill"
                       title:@"About Us"
                    subtitle:@"Learn more about our team"
                   iconColor:[UIColor colorWithRed:0.20 green:0.50 blue:0.98 alpha:1.0]],
        [NGSettingsItem icon:@"doc.text.fill"
                       title:@"Terms of Service"
                    subtitle:@"Usage rules and agreements"
                   iconColor:[UIColor colorWithRed:0.35 green:0.70 blue:0.45 alpha:1.0]],
        [NGSettingsItem icon:@"lock.shield.fill"
                       title:@"Privacy Policy"
                    subtitle:@"How we protect your data"
                   iconColor:[UIColor colorWithRed:0.65 green:0.25 blue:0.85 alpha:1.0]],
        [NGSettingsItem icon:@"envelope.fill"
                       title:@"Feedback"
                    subtitle:@"Share your thoughts with us"
                   iconColor:[UIColor colorWithRed:0.95 green:0.55 blue:0.15 alpha:1.0]],
    ];

    [self.view addSubview:_tableView];
    [NSLayoutConstraint activateConstraints:@[
        [_tableView.topAnchor constraintEqualToAnchor:self.view.topAnchor],
        [_tableView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [_tableView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [_tableView.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
    ]];
    [_tableView reloadData];
}

- (void)buildSupportFooter {
    CGFloat screenW = UIScreen.mainScreen.bounds.size.width;
    CGFloat contentW = screenW - 40;
    UIView *footer = [[UIView alloc] initWithFrame:CGRectMake(0, 0, screenW, 220)];
    footer.backgroundColor = UIColor.clearColor;

    UILabel *title = [[UILabel alloc] initWithFrame:CGRectMake(20, 28, contentW, 22)];
    title.text = @"Having trouble?";
    title.font = [UIFont systemFontOfSize:15 weight:UIFontWeightSemibold];
    title.textColor = [UIColor colorWithWhite:1 alpha:0.88];
    title.numberOfLines = 1;

    UILabel *desc = [[UILabel alloc] initWithFrame:CGRectMake(20, 54, contentW, 0)];
    desc.text = @"If something isn’t working right, please copy the details and email them to us. A little extra context helps us help you much faster.";
    desc.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    desc.textColor = [UIColor colorWithWhite:1 alpha:0.42];
    desc.numberOfLines = 0;
    CGSize descSize = [desc sizeThatFits:CGSizeMake(contentW, CGFLOAT_MAX)];
    desc.frame = CGRectMake(20, 54, contentW, ceil(descSize.height));

    UIButton *copyBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    copyBtn.frame = CGRectMake(20, CGRectGetMaxY(desc.frame) + 16, contentW, 46);
    [copyBtn setTitle:@"Copy Details" forState:UIControlStateNormal];
    [copyBtn setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    copyBtn.titleLabel.font = [UIFont systemFontOfSize:15 weight:UIFontWeightSemibold];
    copyBtn.backgroundColor = [UIColor colorWithRed:0.28 green:0.48 blue:0.92 alpha:1.0];
    copyBtn.layer.cornerRadius = 12;
    copyBtn.clipsToBounds = YES;
    [copyBtn addTarget:self action:@selector(handleCopyDetails) forControlEvents:UIControlEventTouchUpInside];

    _copyHintLabel = [[UILabel alloc] initWithFrame:CGRectMake(20, CGRectGetMaxY(copyBtn.frame) + 10, contentW, 18)];
    _copyHintLabel.text = @"";
    _copyHintLabel.font = [UIFont systemFontOfSize:12 weight:UIFontWeightMedium];
    _copyHintLabel.textColor = [UIColor colorWithRed:0.45 green:0.82 blue:0.55 alpha:1.0];
    _copyHintLabel.textAlignment = NSTextAlignmentCenter;
    _copyHintLabel.alpha = 0;

    footer.frame = CGRectMake(0, 0, screenW, CGRectGetMaxY(_copyHintLabel.frame) + 28);
    [footer addSubview:title];
    [footer addSubview:desc];
    [footer addSubview:copyBtn];
    [footer addSubview:_copyHintLabel];
    _tableView.tableFooterView = footer;
}

- (void)handleCopyDetails {
    NSString *text = [VTAdProxy vt_sessionLogText] ?: @"";
    if (text.length == 0) {
        text = @"(No details yet)";
    }
    UIPasteboard.generalPasteboard.string = text;
    NSLog(@"[设置] 已复制本会话详情到剪贴板，长度=%ld", (long)text.length);

    _copyHintLabel.text = @"✓ Copied — paste into your email";
    _copyHintLabel.alpha = 1.0;
    [UIView animateWithDuration:0.25 delay:2.2 options:0 animations:^{
        self->_copyHintLabel.alpha = 0;
    } completion:nil];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    self.navigationItem.title = @"Settings";
    UINavigationBarAppearance *app = [[UINavigationBarAppearance alloc] init];
    [app configureWithOpaqueBackground];
    app.backgroundColor = [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0];
    app.titleTextAttributes = @{NSForegroundColorAttributeName: UIColor.whiteColor,
                                NSFontAttributeName: [UIFont systemFontOfSize:17 weight:UIFontWeightSemibold]};
    self.navigationController.navigationBar.standardAppearance = app;
    self.navigationController.navigationBar.scrollEdgeAppearance = app;
    self.navigationController.navigationBar.tintColor = [UIColor colorWithRed:0.40 green:0.65 blue:1.0 alpha:1.0];
    UIBarButtonItem *back = [[UIBarButtonItem alloc] initWithImage:[UIImage systemImageNamed:@"chevron.left"]
                                                             style:UIBarButtonItemStylePlain
                                                            target:self
                                                            action:@selector(handleBack)];
    back.tintColor = [UIColor colorWithRed:0.40 green:0.65 blue:1.0 alpha:1.0];
    self.navigationItem.leftBarButtonItem = back;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    self.navigationController.navigationBarHidden = YES;
}

- (void)handleBack {
    [self.navigationController popViewControllerAnimated:YES];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView { return 1; }
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section { return _items.count; }

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    NGSettingsCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell" forIndexPath:indexPath];
    [cell configureWithItem:_items[indexPath.row]];
    return cell;
}

- (UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
    UILabel *lbl = [[UILabel alloc] init];
    lbl.text = @"  GENERAL";
    lbl.font = [UIFont systemFontOfSize:11 weight:UIFontWeightSemibold];
    lbl.textColor = [UIColor colorWithWhite:1 alpha:0.35];
    return lbl;
}
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section { return 32; }

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    UIViewController *dest;
    switch (indexPath.row) {
        case 0: dest = [[NGAboutViewController alloc] init]; break;
        case 1: dest = [[NGTermsViewController alloc] init]; break;
        case 2: dest = [[NGPrivacyViewController alloc] init]; break;
        case 3: dest = [[NGFeedbackViewController alloc] init]; break;
        default: return;
    }
    [self.navigationController pushViewController:dest animated:YES];
}

@end
