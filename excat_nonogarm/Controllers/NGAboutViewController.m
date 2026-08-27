//
//  NGAboutViewController.m
//  excat_nonogarm

#import "NGAboutViewController.h"
#import "NGTheme.h"

// ── Shared helper: dark scroll page base ───────────────────────────────────
static UIColor *bgColor(void)   { return [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0]; }
static UIColor *cardColor(void) { return [UIColor colorWithRed:0.13 green:0.14 blue:0.19 alpha:1.0]; }
static UIColor *accentBlue(void){ return [UIColor colorWithRed:0.40 green:0.65 blue:1.00 alpha:1.0]; }

static void applyNavStyle(UIViewController *vc, NSString *title) {
    vc.navigationItem.title = title;
    UINavigationBarAppearance *a = [[UINavigationBarAppearance alloc] init];
    [a configureWithOpaqueBackground];
    a.backgroundColor = bgColor();
    a.titleTextAttributes = @{NSForegroundColorAttributeName: UIColor.whiteColor,
                               NSFontAttributeName: [UIFont systemFontOfSize:17 weight:UIFontWeightSemibold]};
    vc.navigationController.navigationBar.standardAppearance = a;
    vc.navigationController.navigationBar.scrollEdgeAppearance = a;
    vc.navigationController.navigationBar.tintColor = accentBlue();
}

static UILabel *sectionTitle(NSString *text) {
    UILabel *l = [[UILabel alloc] init];
    l.text = text;
    l.font = [UIFont systemFontOfSize:13 weight:UIFontWeightSemibold];
    l.textColor = accentBlue();
    l.translatesAutoresizingMaskIntoConstraints = NO;
    return l;
}

static UILabel *bodyText(NSString *text) {
    UILabel *l = [[UILabel alloc] init];
    l.text = text;
    l.font = [UIFont systemFontOfSize:15 weight:UIFontWeightRegular];
    l.textColor = [UIColor colorWithWhite:1 alpha:0.78];
    l.numberOfLines = 0;
    l.lineBreakMode = NSLineBreakByWordWrapping;
    l.translatesAutoresizingMaskIntoConstraints = NO;
    return l;
}

static UIView *divider(void) {
    UIView *v = [[UIView alloc] init];
    v.backgroundColor = [UIColor colorWithWhite:1 alpha:0.07];
    v.translatesAutoresizingMaskIntoConstraints = NO;
    [v.heightAnchor constraintEqualToConstant:1].active = YES;
    return v;
}

static UIView *statCard(NSString *value, NSString *label) {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [UIColor colorWithRed:0.16 green:0.18 blue:0.26 alpha:1.0];
    card.layer.cornerRadius = 12;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *vl = [[UILabel alloc] init];
    vl.text = value; vl.font = [UIFont systemFontOfSize:26 weight:UIFontWeightBold];
    vl.textColor = accentBlue(); vl.textAlignment = NSTextAlignmentCenter;
    vl.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *ll = [[UILabel alloc] init];
    ll.text = label; ll.font = [UIFont systemFontOfSize:11 weight:UIFontWeightMedium];
    ll.textColor = [UIColor colorWithWhite:1 alpha:0.45]; ll.textAlignment = NSTextAlignmentCenter;
    ll.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:vl]; [card addSubview:ll];
    [NSLayoutConstraint activateConstraints:@[
        [vl.topAnchor constraintEqualToAnchor:card.topAnchor constant:14],
        [vl.centerXAnchor constraintEqualToAnchor:card.centerXAnchor],
        [ll.topAnchor constraintEqualToAnchor:vl.bottomAnchor constant:4],
        [ll.centerXAnchor constraintEqualToAnchor:card.centerXAnchor],
        [ll.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-14],
    ]];
    return card;
}

// ── NGAboutViewController ───────────────────────────────────────────────────
@implementation NGAboutViewController {
    UIScrollView *_scroll;
    UIStackView  *_stack;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = bgColor();
    [self buildUI];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    applyNavStyle(self, @"About Us");
    UIBarButtonItem *back = [[UIBarButtonItem alloc] initWithImage:[UIImage systemImageNamed:@"chevron.left"]
                                                             style:UIBarButtonItemStylePlain
                                                            target:self
                                                            action:@selector(goBack)];
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
    _stack.spacing = 0;
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

    // Hero card
    [self addHeroCard];
    [self addSpacing:24];

    // Story section
    [self addSection:@"OUR STORY" content:
        @"Nonogram Pixel Puzzle was born from a passion for both logic and art. "
         "We believe every great puzzle is a miniature universe waiting to be discovered — "
         "one cell at a time.\n\n"
         "Our small but dedicated team has spent countless hours crafting 99 hand-designed levels "
         "that take you on a journey from simple 5×5 grids all the way to intricate 20×20 pixel masterpieces. "
         "Each puzzle is carefully verified to have one and only one logical solution."];
    [self addSpacing:20];

    // Mission section
    [self addSection:@"OUR MISSION" content:
        @"We aim to make logical thinking joyful and accessible for everyone. "
         "Whether you have 5 minutes or 5 hours, our puzzles are designed to fit your lifestyle "
         "while keeping your mind sharp and entertained.\n\n"
         "We are committed to a clean, ad-free, and distraction-free experience so you can "
         "focus entirely on the joy of solving."];
    [self addSpacing:20];

    // Team section
    [self addSection:@"THE TEAM" content:
        @"We are a small indie studio passionate about puzzle games and pixel art. "
         "Our team includes puzzle designers, software engineers, and pixel artists who all share "
         "one common goal: creating the most satisfying nonogram experience on mobile.\n\n"
         "Every level you play has been hand-crafted, tested, and polished with love."];
    [self addSpacing:20];

    // Contact card
    [self addContactCard];
    [self addSpacing:30];
}

- (void)addHeroCard {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = cardColor();
    card.layer.cornerRadius = 16;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UIImageView *iconIV = [[UIImageView alloc] init];
    iconIV.image = [UIImage imageNamed:@"AppIconImage"];
    iconIV.contentMode = UIViewContentModeScaleAspectFill;
    iconIV.clipsToBounds = YES;
    iconIV.layer.cornerRadius = 18;
    iconIV.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *name = [[UILabel alloc] init];
    name.text = @"Nonogram Pixel Puzzle";
    name.font = [UIFont systemFontOfSize:20 weight:UIFontWeightBold];
    name.textColor = UIColor.whiteColor;
    name.textAlignment = NSTextAlignmentCenter;
    name.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *tagline = [[UILabel alloc] init];
    tagline.text = @"Think logically. Paint beautifully.";
    tagline.font = [UIFont systemFontOfSize:14 weight:UIFontWeightRegular];
    tagline.textColor = [UIColor colorWithWhite:1 alpha:0.5];
    tagline.textAlignment = NSTextAlignmentCenter;
    tagline.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:iconIV];
    [card addSubview:name];
    [card addSubview:tagline];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [iconIV.topAnchor constraintEqualToAnchor:card.topAnchor constant:20],
        [iconIV.centerXAnchor constraintEqualToAnchor:card.centerXAnchor],
        [iconIV.widthAnchor constraintEqualToConstant:80],
        [iconIV.heightAnchor constraintEqualToConstant:80],
        [name.topAnchor constraintEqualToAnchor:iconIV.bottomAnchor constant:12],
        [name.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [name.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [tagline.topAnchor constraintEqualToAnchor:name.bottomAnchor constant:6],
        [tagline.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [tagline.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [tagline.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-20],
    ]];
}

- (void)addStatsRow {
    NSArray *values = @[@"99",   @"3",     @"1"];
    NSArray *labels = @[@"Levels", @"Colors", @"Solution"];
    UIStackView *row = [[UIStackView alloc] init];
    row.axis = UILayoutConstraintAxisHorizontal;
    row.spacing = 10;
    row.distribution = UIStackViewDistributionFillEqually;
    row.translatesAutoresizingMaskIntoConstraints = NO;
    for (NSInteger i = 0; i < values.count; i++) {
        [row addArrangedSubview:statCard(values[i], labels[i])];
    }
    [_stack addArrangedSubview:row];
}

- (void)addSection:(NSString *)title content:(NSString *)content {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = cardColor();
    card.layer.cornerRadius = 14;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *tl = sectionTitle(title);
    UIView *dv = divider();
    UILabel *bl = bodyText(content);

    [card addSubview:tl];
    [card addSubview:dv];
    [card addSubview:bl];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [tl.topAnchor constraintEqualToAnchor:card.topAnchor constant:16],
        [tl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [tl.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [dv.topAnchor constraintEqualToAnchor:tl.bottomAnchor constant:10],
        [dv.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [dv.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [bl.topAnchor constraintEqualToAnchor:dv.bottomAnchor constant:12],
        [bl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [bl.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [bl.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-16],
    ]];
}

- (void)addContactCard {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [UIColor colorWithRed:0.14 green:0.16 blue:0.28 alpha:1.0];
    card.layer.cornerRadius = 14;
    card.layer.borderWidth = 1;
    card.layer.borderColor = [UIColor colorWithRed:0.40 green:0.65 blue:1.0 alpha:0.30].CGColor;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UIImageView *envIcon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"envelope.circle.fill"]];
    envIcon.tintColor = accentBlue();
    envIcon.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *ctTitle = [[UILabel alloc] init];
    ctTitle.text = @"Get in Touch";
    ctTitle.font = [UIFont systemFontOfSize:15 weight:UIFontWeightSemibold];
    ctTitle.textColor = UIColor.whiteColor;
    ctTitle.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *ctEmail = [[UILabel alloc] init];
    ctEmail.text = @"caydance_kalem253@mail.com";
    ctEmail.font = [UIFont systemFontOfSize:13 weight:UIFontWeightRegular];
    ctEmail.textColor = accentBlue();
    ctEmail.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:envIcon];
    [card addSubview:ctTitle];
    [card addSubview:ctEmail];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [envIcon.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [envIcon.centerYAnchor constraintEqualToAnchor:card.centerYAnchor],
        [envIcon.widthAnchor constraintEqualToConstant:36],
        [envIcon.heightAnchor constraintEqualToConstant:36],
        [ctTitle.leadingAnchor constraintEqualToAnchor:envIcon.trailingAnchor constant:12],
        [ctTitle.topAnchor constraintEqualToAnchor:card.topAnchor constant:16],
        [ctEmail.leadingAnchor constraintEqualToAnchor:ctTitle.leadingAnchor],
        [ctEmail.topAnchor constraintEqualToAnchor:ctTitle.bottomAnchor constant:4],
        [ctEmail.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-16],
    ]];
}

- (void)addSpacing:(CGFloat)h {
    UIView *sp = [[UIView alloc] init];
    sp.translatesAutoresizingMaskIntoConstraints = NO;
    [sp.heightAnchor constraintEqualToConstant:h].active = YES;
    [_stack addArrangedSubview:sp];
}

@end
