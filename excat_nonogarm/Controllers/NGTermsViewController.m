//  NGTermsViewController.m
//  excat_nonogarm

#import "NGTermsViewController.h"

static UIColor *_bgC(void)    { return [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0]; }
static UIColor *_cardC(void)  { return [UIColor colorWithRed:0.13 green:0.14 blue:0.19 alpha:1.0]; }
static UIColor *_accentC(void){ return [UIColor colorWithRed:0.35 green:0.70 blue:0.45 alpha:1.0]; }

@implementation NGTermsViewController {
    UIScrollView *_scroll;
    UIStackView  *_stack;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = _bgC();
    [self buildUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    self.navigationItem.title = @"Terms of Service";
    UINavigationBarAppearance *a = [[UINavigationBarAppearance alloc] init];
    [a configureWithOpaqueBackground];
    a.backgroundColor = _bgC();
    a.titleTextAttributes = @{NSForegroundColorAttributeName: UIColor.whiteColor,
                               NSFontAttributeName: [UIFont systemFontOfSize:17 weight:UIFontWeightSemibold]};
    self.navigationController.navigationBar.standardAppearance = a;
    self.navigationController.navigationBar.scrollEdgeAppearance = a;
    self.navigationController.navigationBar.tintColor = _accentC();
    UIBarButtonItem *back = [[UIBarButtonItem alloc] initWithImage:[UIImage systemImageNamed:@"chevron.left"]
                                                             style:UIBarButtonItemStylePlain
                                                            target:self action:@selector(goBack)];
    self.navigationItem.leftBarButtonItem = back;
}

- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
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

    // Effective date banner
    [self addBanner:@"Effective Date: January 1, 2025"];

    NSArray *sections = @[
        @[@"1. Acceptance of Terms",
          @"By downloading or using Nonogram Pixel Puzzle (the \"App\"), you agree to be bound by these "
           "Terms of Service. If you do not agree to these terms, please do not use the App."],
        @[@"2. License",
          @"We grant you a limited, non-exclusive, non-transferable, revocable license to use the App "
           "for personal, non-commercial entertainment purposes. You may not copy, modify, distribute, "
           "sell, or lease any part of the App."],
        @[@"3. User Conduct",
          @"You agree not to:\n"
           "• Attempt to reverse-engineer or decompile any part of the App.\n"
           "• Use automated tools to extract puzzle solutions or game data.\n"
           "• Exploit bugs or glitches to gain unfair advantages.\n"
           "• Interfere with the proper functioning of the App."],
        @[@"4. Intellectual Property",
          @"All puzzles, pixel artwork, sounds, code, and design elements within the App are the "
           "exclusive intellectual property of the developer. Unauthorized reproduction or distribution "
           "of any content is strictly prohibited."],
        @[@"5. In-App Purchases",
          @"The App may offer optional in-app purchases. All purchases are final and non-refundable "
           "except as required by applicable law. We reserve the right to modify pricing and content "
           "availability at any time."],
        @[@"6. Disclaimers",
          @"The App is provided \"as is\" without warranties of any kind. We do not guarantee that the App "
           "will be error-free, uninterrupted, or free of harmful components. Use the App at your own risk."],
        @[@"7. Limitation of Liability",
          @"To the fullest extent permitted by law, we shall not be liable for any indirect, incidental, "
           "special, consequential, or punitive damages arising from your use of or inability to use the App."],
        @[@"8. Changes to Terms",
          @"We reserve the right to modify these Terms at any time. Continued use of the App after changes "
           "constitutes acceptance of the updated Terms. We recommend reviewing these Terms periodically."],
        @[@"9. Contact Us",
          @"If you have any questions about these Terms of Service, please contact us at:\n"
           "caydance_kalem253@mail.com"],
    ];

    for (NSArray *section in sections) {
        [self addSectionTitle:section[0] body:section[1]];
    }
}

- (void)addBanner:(NSString *)dateText {
    UIView *banner = [[UIView alloc] init];
    banner.backgroundColor = [UIColor colorWithRed:0.12 green:0.22 blue:0.14 alpha:1.0];
    banner.layer.cornerRadius = 10;
    banner.layer.borderWidth = 1;
    banner.layer.borderColor = [UIColor colorWithRed:0.35 green:0.70 blue:0.45 alpha:0.35].CGColor;
    banner.translatesAutoresizingMaskIntoConstraints = NO;

    UIImageView *icon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"checkmark.seal.fill"]];
    icon.tintColor = _accentC();
    icon.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *lbl = [[UILabel alloc] init];
    lbl.text = dateText;
    lbl.font = [UIFont systemFontOfSize:13 weight:UIFontWeightMedium];
    lbl.textColor = _accentC();
    lbl.translatesAutoresizingMaskIntoConstraints = NO;

    [banner addSubview:icon]; [banner addSubview:lbl];
    [_stack addArrangedSubview:banner];
    [NSLayoutConstraint activateConstraints:@[
        [icon.leadingAnchor constraintEqualToAnchor:banner.leadingAnchor constant:14],
        [icon.centerYAnchor constraintEqualToAnchor:banner.centerYAnchor],
        [icon.widthAnchor constraintEqualToConstant:18], [icon.heightAnchor constraintEqualToConstant:18],
        [lbl.leadingAnchor constraintEqualToAnchor:icon.trailingAnchor constant:8],
        [lbl.topAnchor constraintEqualToAnchor:banner.topAnchor constant:12],
        [lbl.bottomAnchor constraintEqualToAnchor:banner.bottomAnchor constant:-12],
    ]];
}

- (void)addSectionTitle:(NSString *)title body:(NSString *)body {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = _cardC();
    card.layer.cornerRadius = 12;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *tl = [[UILabel alloc] init];
    tl.text = title;
    tl.font = [UIFont systemFontOfSize:14 weight:UIFontWeightSemibold];
    tl.textColor = _accentC();
    tl.translatesAutoresizingMaskIntoConstraints = NO;

    UIView *dv = [[UIView alloc] init];
    dv.backgroundColor = [UIColor colorWithWhite:1 alpha:0.07];
    dv.translatesAutoresizingMaskIntoConstraints = NO;
    [dv.heightAnchor constraintEqualToConstant:1].active = YES;

    UILabel *bl = [[UILabel alloc] init];
    bl.text = body;
    bl.font = [UIFont systemFontOfSize:14 weight:UIFontWeightRegular];
    bl.textColor = [UIColor colorWithWhite:1 alpha:0.75];
    bl.numberOfLines = 0;
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
