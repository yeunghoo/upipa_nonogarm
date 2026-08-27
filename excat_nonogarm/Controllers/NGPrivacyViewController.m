//  NGPrivacyViewController.m
//  excat_nonogarm

#import "NGPrivacyViewController.h"

static UIColor *_pvBgC(void)    { return [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0]; }
static UIColor *_pvCardC(void)  { return [UIColor colorWithRed:0.13 green:0.14 blue:0.19 alpha:1.0]; }
static UIColor *_pvAccentC(void){ return [UIColor colorWithRed:0.65 green:0.25 blue:0.85 alpha:1.0]; }

@implementation NGPrivacyViewController {
    UIScrollView *_scroll;
    UIStackView  *_stack;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = _pvBgC();
    [self buildUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    self.navigationItem.title = @"Privacy Policy";
    UINavigationBarAppearance *a = [[UINavigationBarAppearance alloc] init];
    [a configureWithOpaqueBackground];
    a.backgroundColor = _pvBgC();
    a.titleTextAttributes = @{NSForegroundColorAttributeName: UIColor.whiteColor,
                               NSFontAttributeName: [UIFont systemFontOfSize:17 weight:UIFontWeightSemibold]};
    self.navigationController.navigationBar.standardAppearance = a;
    self.navigationController.navigationBar.scrollEdgeAppearance = a;
    self.navigationController.navigationBar.tintColor = _pvAccentC();
    UIBarButtonItem *back = [[UIBarButtonItem alloc] initWithImage:[UIImage systemImageNamed:@"chevron.left"]
                                                             style:UIBarButtonItemStylePlain
                                                            target:self action:@selector(goBack)];
    self.navigationItem.leftBarButtonItem = back;
}

- (void)goBack { [self.navigationController popViewControllerAnimated:YES]; }

- (void)buildUI {
    _scroll = [[UIScrollView alloc] init];
    _scroll.translatesAutoresizingMaskIntoConstraints = NO;
    _scroll.showsVerticalScrollIndicator = NO;
    [self.view addSubview:_scroll];

    _stack = [[UIStackView alloc] init];
    _stack.axis = UILayoutConstraintAxisVertical;
    _stack.spacing = 14;
    _stack.translatesAutoresizingMaskIntoConstraints = NO;
    [_scroll addSubview:_stack];

    UILayoutGuide *safe = self.view.safeAreaLayoutGuide;
    [NSLayoutConstraint activateConstraints:@[
        [_scroll.topAnchor constraintEqualToAnchor:safe.topAnchor constant:44],
        [_scroll.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor],
        [_scroll.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor],
        [_scroll.bottomAnchor constraintEqualToAnchor:self.view.bottomAnchor],
        [_stack.topAnchor constraintEqualToAnchor:_scroll.topAnchor constant:20],
        [_stack.leadingAnchor constraintEqualToAnchor:_scroll.leadingAnchor constant:20],
        [_stack.trailingAnchor constraintEqualToAnchor:_scroll.trailingAnchor constant:-20],
        [_stack.bottomAnchor constraintEqualToAnchor:_scroll.bottomAnchor constant:-30],
        [_stack.widthAnchor constraintEqualToAnchor:_scroll.widthAnchor constant:-40],
    ]];

    [self addPrivacyBadge];

    NSArray *sections = @[
        @[@"Information We Collect",
          @"We are committed to your privacy. The App collects minimal data:\n\n"
           "• Game Progress: Your level completion status and current level are stored locally on your device "
           "using iOS's built-in secure storage. This data never leaves your device.\n\n"
           "• Crash Reports (Optional): Anonymous crash data may be collected by iOS to help us improve stability. "
           "You can disable this in your device's Privacy settings.\n\n"
           "We do NOT collect names, email addresses, location data, device identifiers, or any personal information."],
        @[@"How We Use Information",
          @"The limited data we store is used exclusively to:\n"
           "• Save your puzzle progress across sessions.\n"
           "• Remember which levels you have unlocked and completed.\n"
           "• Maintain your current game state.\n\n"
           "We do not use this data for advertising, analytics, or any purpose other than providing you "
           "with a seamless gameplay experience."],
        @[@"Data Storage & Security",
          @"All game data is stored locally on your device using Apple's NSUserDefaults, which is protected "
           "by iOS's built-in security model. We do not operate servers, and no data is transmitted over the "
           "internet by our App.\n\n"
           "Your data remains under your full control at all times. You can delete all saved data by "
           "uninstalling the App."],
        @[@"Third-Party Services",
          @"Nonogram Pixel Puzzle does not integrate any third-party analytics SDKs, advertising networks, "
           "social media platforms, or tracking services.\n\n"
           "The App does not contain any in-app advertisements. We believe in a pure, distraction-free "
           "puzzle experience."],
        @[@"Children's Privacy",
          @"Our App is suitable for all ages, including children under 13. We do not knowingly collect "
           "any personal information from children. Since we collect no personal data at all, the App "
           "is compliant with COPPA and other children's privacy regulations."],
        @[@"Your Rights",
          @"Since we do not collect personal data, there is no personal information to access, correct, "
           "or delete on our servers. You have full control over locally stored game progress through "
           "your device's app management settings."],
        @[@"Changes to This Policy",
          @"We may update this Privacy Policy occasionally to reflect improvements to our App. "
           "Any significant changes will be communicated through an App update. Continued use of the App "
           "after updates constitutes acceptance of the revised policy."],
        @[@"Contact Us",
          @"If you have any questions or concerns about our privacy practices, please reach out:\n"
           "caydance_kalem253@mail.com\n\n"
           "We take all privacy inquiries seriously and will respond within 5 business days."],
    ];

    for (NSArray *s in sections) {
        [self addCard:s[0] body:s[1]];
    }
}

- (void)addPrivacyBadge {
    UIView *badge = [[UIView alloc] init];
    badge.backgroundColor = [UIColor colorWithRed:0.18 green:0.10 blue:0.26 alpha:1.0];
    badge.layer.cornerRadius = 12;
    badge.layer.borderWidth = 1;
    badge.layer.borderColor = [UIColor colorWithRed:0.65 green:0.25 blue:0.85 alpha:0.35].CGColor;
    badge.translatesAutoresizingMaskIntoConstraints = NO;

    UIImageView *shieldIcon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"lock.shield.fill"]];
    shieldIcon.tintColor = _pvAccentC();
    shieldIcon.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *title = [[UILabel alloc] init];
    title.text = @"Your Privacy is Protected";
    title.font = [UIFont systemFontOfSize:15 weight:UIFontWeightSemibold];
    title.textColor = UIColor.whiteColor;
    title.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *sub = [[UILabel alloc] init];
    sub.text = @"No personal data is collected or transmitted.";
    sub.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    sub.textColor = [UIColor colorWithWhite:1 alpha:0.5];
    sub.translatesAutoresizingMaskIntoConstraints = NO;

    [badge addSubview:shieldIcon]; [badge addSubview:title]; [badge addSubview:sub];
    [_stack addArrangedSubview:badge];

    [NSLayoutConstraint activateConstraints:@[
        [shieldIcon.leadingAnchor constraintEqualToAnchor:badge.leadingAnchor constant:14],
        [shieldIcon.centerYAnchor constraintEqualToAnchor:badge.centerYAnchor],
        [shieldIcon.widthAnchor constraintEqualToConstant:32], [shieldIcon.heightAnchor constraintEqualToConstant:32],
        [title.leadingAnchor constraintEqualToAnchor:shieldIcon.trailingAnchor constant:12],
        [title.topAnchor constraintEqualToAnchor:badge.topAnchor constant:14],
        [sub.leadingAnchor constraintEqualToAnchor:title.leadingAnchor],
        [sub.topAnchor constraintEqualToAnchor:title.bottomAnchor constant:3],
        [sub.bottomAnchor constraintEqualToAnchor:badge.bottomAnchor constant:-14],
    ]];
}

- (void)addCard:(NSString *)title body:(NSString *)body {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = _pvCardC();
    card.layer.cornerRadius = 12;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *tl = [[UILabel alloc] init];
    tl.text = title; tl.font = [UIFont systemFontOfSize:14 weight:UIFontWeightSemibold];
    tl.textColor = _pvAccentC(); tl.translatesAutoresizingMaskIntoConstraints = NO;

    UIView *dv = [[UIView alloc] init];
    dv.backgroundColor = [UIColor colorWithWhite:1 alpha:0.07];
    dv.translatesAutoresizingMaskIntoConstraints = NO;
    [dv.heightAnchor constraintEqualToConstant:1].active = YES;

    UILabel *bl = [[UILabel alloc] init];
    bl.text = body; bl.font = [UIFont systemFontOfSize:14 weight:UIFontWeightRegular];
    bl.textColor = [UIColor colorWithWhite:1 alpha:0.75]; bl.numberOfLines = 0;
    bl.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:tl]; [card addSubview:dv]; [card addSubview:bl];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [tl.topAnchor constraintEqualToAnchor:card.topAnchor constant:14],
        [tl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [tl.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [dv.topAnchor constraintEqualToAnchor:tl.bottomAnchor constant:8],
        [dv.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [dv.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [bl.topAnchor constraintEqualToAnchor:dv.bottomAnchor constant:10],
        [bl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [bl.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [bl.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-14],
    ]];
}

@end
