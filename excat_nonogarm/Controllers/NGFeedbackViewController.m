//  NGFeedbackViewController.m
//  excat_nonogarm

#import "NGFeedbackViewController.h"

static UIColor *_fbBgC(void)    { return [UIColor colorWithRed:0.09 green:0.10 blue:0.14 alpha:1.0]; }
static UIColor *_fbCardC(void)  { return [UIColor colorWithRed:0.13 green:0.14 blue:0.19 alpha:1.0]; }
static UIColor *_fbAccentC(void){ return [UIColor colorWithRed:0.95 green:0.55 blue:0.15 alpha:1.0]; }

@interface NGFeedbackViewController () <UITextViewDelegate>
@end

@implementation NGFeedbackViewController {
    UIScrollView *_scroll;
    UIStackView  *_stack;
    UITextView   *_textView;
    UILabel      *_charCount;
    NSArray<NSDictionary *> *_topics;
    NSInteger    _selectedTopic;
    NSMutableArray<UIButton *> *_topicButtons;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = _fbBgC();
    _selectedTopic = -1;
    _topicButtons = [NSMutableArray array];
    [self buildUI];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(keyboardChanged:)
                                                 name:UIKeyboardWillChangeFrameNotification
                                               object:nil];
}

- (void)dealloc {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.navigationController.navigationBarHidden = NO;
    self.navigationItem.title = @"Feedback";
    UINavigationBarAppearance *a = [[UINavigationBarAppearance alloc] init];
    [a configureWithOpaqueBackground];
    a.backgroundColor = _fbBgC();
    a.titleTextAttributes = @{NSForegroundColorAttributeName: UIColor.whiteColor,
                               NSFontAttributeName: [UIFont systemFontOfSize:17 weight:UIFontWeightSemibold]};
    self.navigationController.navigationBar.standardAppearance = a;
    self.navigationController.navigationBar.scrollEdgeAppearance = a;
    self.navigationController.navigationBar.tintColor = _fbAccentC();
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
    _scroll.keyboardDismissMode = UIScrollViewKeyboardDismissModeOnDrag;
    [self.view addSubview:_scroll];

    _stack = [[UIStackView alloc] init];
    _stack.axis = UILayoutConstraintAxisVertical;
    _stack.spacing = 16;
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

    // Topic picker
    [self addTopicPicker];

    // Message box
    [self addMessageBox];

    // Submit area
    [self addSubmitArea];

    // FAQ
    [self addFAQ];
}

- (void)addHeroCard {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = [UIColor colorWithRed:0.20 green:0.13 blue:0.07 alpha:1.0];
    card.layer.cornerRadius = 16;
    card.layer.borderWidth = 1;
    card.layer.borderColor = [UIColor colorWithRed:0.95 green:0.55 blue:0.15 alpha:0.30].CGColor;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UIImageView *icon = [[UIImageView alloc] initWithImage:[UIImage systemImageNamed:@"bubble.left.and.bubble.right.fill"]];
    icon.tintColor = _fbAccentC();
    icon.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *title = [[UILabel alloc] init];
    title.text = @"We'd Love to Hear From You";
    title.font = [UIFont systemFontOfSize:17 weight:UIFontWeightBold];
    title.textColor = UIColor.whiteColor;
    title.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *sub = [[UILabel alloc] init];
    sub.text = @"Your feedback helps us create better puzzles and a more enjoyable experience. "
                "Every message is read by our team.";
    sub.font = [UIFont systemFontOfSize:13 weight:UIFontWeightRegular];
    sub.textColor = [UIColor colorWithWhite:1 alpha:0.55];
    sub.numberOfLines = 0;
    sub.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:icon]; [card addSubview:title]; [card addSubview:sub];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [icon.topAnchor constraintEqualToAnchor:card.topAnchor constant:16],
        [icon.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [icon.widthAnchor constraintEqualToConstant:28], [icon.heightAnchor constraintEqualToConstant:28],
        [title.centerYAnchor constraintEqualToAnchor:icon.centerYAnchor],
        [title.leadingAnchor constraintEqualToAnchor:icon.trailingAnchor constant:10],
        [title.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [sub.topAnchor constraintEqualToAnchor:icon.bottomAnchor constant:10],
        [sub.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [sub.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [sub.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-16],
    ]];
}

- (void)addTopicPicker {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = _fbCardC();
    card.layer.cornerRadius = 14;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *lbl = [[UILabel alloc] init];
    lbl.text = @"TOPIC";
    lbl.font = [UIFont systemFontOfSize:11 weight:UIFontWeightSemibold];
    lbl.textColor = [UIColor colorWithWhite:1 alpha:0.35];
    lbl.translatesAutoresizingMaskIntoConstraints = NO;

    _topics = @[
        @{@"icon": @"star.fill",      @"label": @"Bug Report"},
        @{@"icon": @"lightbulb.fill", @"label": @"Suggestion"},
        @{@"icon": @"puzzlepiece.fill",@"label": @"Puzzle Issue"},
        @{@"icon": @"heart.fill",     @"label": @"General"},
    ];

    UIStackView *grid = [[UIStackView alloc] init];
    grid.axis = UILayoutConstraintAxisVertical;
    grid.spacing = 8;
    grid.translatesAutoresizingMaskIntoConstraints = NO;

    for (NSInteger row = 0; row < 2; row++) {
        UIStackView *rowStack = [[UIStackView alloc] init];
        rowStack.axis = UILayoutConstraintAxisHorizontal;
        rowStack.spacing = 8;
        rowStack.distribution = UIStackViewDistributionFillEqually;
        rowStack.translatesAutoresizingMaskIntoConstraints = NO;

        for (NSInteger col = 0; col < 2; col++) {
            NSInteger idx = row * 2 + col;
            NSDictionary *topic = _topics[idx];
            UIButton *btn = [UIButton buttonWithType:UIButtonTypeSystem];
            btn.tag = idx;
            btn.layer.cornerRadius = 10;
            btn.layer.borderWidth = 1.5;
            btn.layer.borderColor = [UIColor colorWithWhite:1 alpha:0.12].CGColor;
            btn.backgroundColor = [UIColor colorWithRed:0.16 green:0.17 blue:0.22 alpha:1.0];
            btn.translatesAutoresizingMaskIntoConstraints = NO;
            [btn.heightAnchor constraintEqualToConstant:52].active = YES;

            UIImageSymbolConfiguration *cfg = [UIImageSymbolConfiguration configurationWithPointSize:14 weight:UIImageSymbolWeightMedium];
            UIImage *img = [UIImage systemImageNamed:topic[@"icon"] withConfiguration:cfg];
            [btn setImage:img forState:UIControlStateNormal];
            [btn setTitle:[NSString stringWithFormat:@"  %@", topic[@"label"]] forState:UIControlStateNormal];
            btn.tintColor = [UIColor colorWithWhite:1 alpha:0.5];
            btn.titleLabel.font = [UIFont systemFontOfSize:13 weight:UIFontWeightMedium];
            [btn setTitleColor:[UIColor colorWithWhite:1 alpha:0.5] forState:UIControlStateNormal];
            [btn addTarget:self action:@selector(topicTapped:) forControlEvents:UIControlEventTouchUpInside];

            [_topicButtons addObject:btn];
            [rowStack addArrangedSubview:btn];
        }
        [grid addArrangedSubview:rowStack];
    }

    [card addSubview:lbl];
    [card addSubview:grid];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [lbl.topAnchor constraintEqualToAnchor:card.topAnchor constant:14],
        [lbl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [grid.topAnchor constraintEqualToAnchor:lbl.bottomAnchor constant:10],
        [grid.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:12],
        [grid.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-12],
        [grid.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-12],
    ]];
}

- (void)topicTapped:(UIButton *)sender {
    _selectedTopic = sender.tag;
    [_topicButtons enumerateObjectsUsingBlock:^(UIButton *btn, NSUInteger idx, BOOL *stop) {
        BOOL selected = (NSInteger)idx == self->_selectedTopic;
        [UIView animateWithDuration:0.2 animations:^{
            btn.backgroundColor = selected
                ? [UIColor colorWithRed:0.22 green:0.13 blue:0.06 alpha:1.0]
                : [UIColor colorWithRed:0.16 green:0.17 blue:0.22 alpha:1.0];
            btn.layer.borderColor = selected
                ? [UIColor colorWithRed:0.95 green:0.55 blue:0.15 alpha:0.80].CGColor
                : [UIColor colorWithWhite:1 alpha:0.12].CGColor;
            btn.tintColor = selected ? _fbAccentC() : [UIColor colorWithWhite:1 alpha:0.5];
            [btn setTitleColor:selected ? _fbAccentC() : [UIColor colorWithWhite:1 alpha:0.5]
                      forState:UIControlStateNormal];
        }];
    }];
}

- (void)addMessageBox {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = _fbCardC();
    card.layer.cornerRadius = 14;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *lbl = [[UILabel alloc] init];
    lbl.text = @"MESSAGE";
    lbl.font = [UIFont systemFontOfSize:11 weight:UIFontWeightSemibold];
    lbl.textColor = [UIColor colorWithWhite:1 alpha:0.35];
    lbl.translatesAutoresizingMaskIntoConstraints = NO;

    _textView = [[UITextView alloc] init];
    _textView.backgroundColor = [UIColor colorWithRed:0.10 green:0.11 blue:0.16 alpha:1.0];
    _textView.layer.cornerRadius = 10;
    _textView.font = [UIFont systemFontOfSize:15];
    _textView.textColor = [UIColor colorWithWhite:1 alpha:0.75];
    _textView.text = @"Share your thoughts here...";
    _textView.textColor = [UIColor colorWithWhite:1 alpha:0.25];
    _textView.tintColor = _fbAccentC();
    _textView.textContainerInset = UIEdgeInsetsMake(12, 12, 12, 12);
    _textView.delegate = self;
    _textView.translatesAutoresizingMaskIntoConstraints = NO;

    _charCount = [[UILabel alloc] init];
    _charCount.text = @"0 / 500";
    _charCount.font = [UIFont systemFontOfSize:11 weight:UIFontWeightRegular];
    _charCount.textColor = [UIColor colorWithWhite:1 alpha:0.3];
    _charCount.textAlignment = NSTextAlignmentRight;
    _charCount.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:lbl]; [card addSubview:_textView]; [card addSubview:_charCount];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [lbl.topAnchor constraintEqualToAnchor:card.topAnchor constant:14],
        [lbl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [_textView.topAnchor constraintEqualToAnchor:lbl.bottomAnchor constant:10],
        [_textView.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:12],
        [_textView.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-12],
        [_textView.heightAnchor constraintEqualToConstant:130],
        [_charCount.topAnchor constraintEqualToAnchor:_textView.bottomAnchor constant:6],
        [_charCount.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-14],
        [_charCount.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-10],
    ]];
}

- (void)addSubmitArea {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = _fbCardC();
    card.layer.cornerRadius = 14;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *emailLbl = [[UILabel alloc] init];
    emailLbl.text = @"Replies will be sent to:";
    emailLbl.font = [UIFont systemFontOfSize:12 weight:UIFontWeightRegular];
    emailLbl.textColor = [UIColor colorWithWhite:1 alpha:0.4];
    emailLbl.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *emailAddr = [[UILabel alloc] init];
    emailAddr.text = @"caydance_kalem253@mail.com";
    emailAddr.font = [UIFont systemFontOfSize:13 weight:UIFontWeightMedium];
    emailAddr.textColor = _fbAccentC();
    emailAddr.translatesAutoresizingMaskIntoConstraints = NO;

    UIButton *submitBtn = [UIButton buttonWithType:UIButtonTypeSystem];
    [submitBtn setTitle:@"Submit Feedback" forState:UIControlStateNormal];
    submitBtn.titleLabel.font = [UIFont systemFontOfSize:16 weight:UIFontWeightSemibold];
    [submitBtn setTitleColor:UIColor.whiteColor forState:UIControlStateNormal];
    submitBtn.backgroundColor = _fbAccentC();
    submitBtn.layer.cornerRadius = 12;
    submitBtn.translatesAutoresizingMaskIntoConstraints = NO;
    [submitBtn addTarget:self action:@selector(submitTapped) forControlEvents:UIControlEventTouchUpInside];

    [card addSubview:emailLbl]; [card addSubview:emailAddr]; [card addSubview:submitBtn];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [emailLbl.topAnchor constraintEqualToAnchor:card.topAnchor constant:14],
        [emailLbl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [emailAddr.topAnchor constraintEqualToAnchor:emailLbl.bottomAnchor constant:3],
        [emailAddr.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [submitBtn.topAnchor constraintEqualToAnchor:emailAddr.bottomAnchor constant:14],
        [submitBtn.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [submitBtn.trailingAnchor constraintEqualToAnchor:card.trailingAnchor constant:-16],
        [submitBtn.heightAnchor constraintEqualToConstant:48],
        [submitBtn.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-16],
    ]];
}

- (void)addFAQ {
    UIView *card = [[UIView alloc] init];
    card.backgroundColor = _fbCardC();
    card.layer.cornerRadius = 14;
    card.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *headerLbl = [[UILabel alloc] init];
    headerLbl.text = @"FREQUENTLY ASKED";
    headerLbl.font = [UIFont systemFontOfSize:11 weight:UIFontWeightSemibold];
    headerLbl.textColor = [UIColor colorWithWhite:1 alpha:0.35];
    headerLbl.translatesAutoresizingMaskIntoConstraints = NO;

    NSArray *faqs = @[
        @[@"How long does it take to get a response?",
          @"We typically respond within 2–5 business days. Check your email's spam folder if you haven't heard back."],
        @[@"I found a puzzle with no solution — what should I do?",
          @"Please use the Bug Report topic and describe the level number. We'll investigate and fix it promptly."],
        @[@"Can I suggest a new puzzle theme?",
          @"Absolutely! Choose the Suggestion topic and describe your idea. We review all suggestions for future updates."],
    ];

    UIStackView *faqStack = [[UIStackView alloc] init];
    faqStack.axis = UILayoutConstraintAxisVertical;
    faqStack.spacing = 0;
    faqStack.translatesAutoresizingMaskIntoConstraints = NO;

    [card addSubview:headerLbl];
    [card addSubview:faqStack];
    [_stack addArrangedSubview:card];

    [NSLayoutConstraint activateConstraints:@[
        [headerLbl.topAnchor constraintEqualToAnchor:card.topAnchor constant:14],
        [headerLbl.leadingAnchor constraintEqualToAnchor:card.leadingAnchor constant:16],
        [faqStack.topAnchor constraintEqualToAnchor:headerLbl.bottomAnchor constant:10],
        [faqStack.leadingAnchor constraintEqualToAnchor:card.leadingAnchor],
        [faqStack.trailingAnchor constraintEqualToAnchor:card.trailingAnchor],
        [faqStack.bottomAnchor constraintEqualToAnchor:card.bottomAnchor constant:-4],
    ]];

    for (NSInteger i = 0; i < (NSInteger)faqs.count; i++) {
        NSArray *faq = faqs[i];
        if (i > 0) {
            UIView *sep = [[UIView alloc] init];
            sep.backgroundColor = [UIColor colorWithWhite:1 alpha:0.06];
            [sep.heightAnchor constraintEqualToConstant:1].active = YES;
            [faqStack addArrangedSubview:sep];
        }
        UIView *faqItem = [self makeFAQItem:faq[0] answer:faq[1]];
        [faqStack addArrangedSubview:faqItem];
    }
}

- (UIView *)makeFAQItem:(NSString *)question answer:(NSString *)answer {
    UIView *item = [[UIView alloc] init];
    item.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *qLbl = [[UILabel alloc] init];
    qLbl.text = question;
    qLbl.font = [UIFont systemFontOfSize:13 weight:UIFontWeightSemibold];
    qLbl.textColor = UIColor.whiteColor;
    qLbl.numberOfLines = 0;
    qLbl.translatesAutoresizingMaskIntoConstraints = NO;

    UILabel *aLbl = [[UILabel alloc] init];
    aLbl.text = answer;
    aLbl.font = [UIFont systemFontOfSize:13 weight:UIFontWeightRegular];
    aLbl.textColor = [UIColor colorWithWhite:1 alpha:0.5];
    aLbl.numberOfLines = 0;
    aLbl.translatesAutoresizingMaskIntoConstraints = NO;

    [item addSubview:qLbl]; [item addSubview:aLbl];
    [NSLayoutConstraint activateConstraints:@[
        [qLbl.topAnchor constraintEqualToAnchor:item.topAnchor constant:12],
        [qLbl.leadingAnchor constraintEqualToAnchor:item.leadingAnchor constant:16],
        [qLbl.trailingAnchor constraintEqualToAnchor:item.trailingAnchor constant:-16],
        [aLbl.topAnchor constraintEqualToAnchor:qLbl.bottomAnchor constant:4],
        [aLbl.leadingAnchor constraintEqualToAnchor:item.leadingAnchor constant:16],
        [aLbl.trailingAnchor constraintEqualToAnchor:item.trailingAnchor constant:-16],
        [aLbl.bottomAnchor constraintEqualToAnchor:item.bottomAnchor constant:-12],
    ]];
    return item;
}

- (void)submitTapped {
    [_textView resignFirstResponder];

    UIAlertController *ok = [UIAlertController
        alertControllerWithTitle:@"Thank You!"
        message:@"Your feedback has been received. We appreciate you taking the time to help us improve.\n\nWe'll get back to you at caydance_kalem253@mail.com within 2–5 business days."
        preferredStyle:UIAlertControllerStyleAlert];
    [ok addAction:[UIAlertAction actionWithTitle:@"Done" style:UIAlertActionStyleDefault handler:^(UIAlertAction *a) {
        // Reset form to initial state
        self->_textView.text = @"Share your thoughts here...";
        self->_textView.textColor = [UIColor colorWithWhite:1 alpha:0.25];
        for (UIButton *btn in self->_topicButtons) {
            btn.backgroundColor = [UIColor colorWithRed:0.16 green:0.17 blue:0.22 alpha:1.0];
            btn.layer.borderColor = [UIColor colorWithWhite:1 alpha:0.12].CGColor;
            btn.tintColor = [UIColor colorWithWhite:1 alpha:0.5];
            [btn setTitleColor:[UIColor colorWithWhite:1 alpha:0.5] forState:UIControlStateNormal];
        }
        self->_selectedTopic = -1;
        self->_charCount.text = @"0 / 500";
    }]];
    [self presentViewController:ok animated:YES completion:nil];
}

- (void)keyboardChanged:(NSNotification *)notif {
    CGRect kbFrame = [notif.userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
    CGFloat inset = CGRectGetMaxY(self.view.frame) - kbFrame.origin.y;
    _scroll.contentInset = UIEdgeInsetsMake(0, 0, MAX(0, inset), 0);
}

// UITextViewDelegate – placeholder behavior
- (void)textViewDidBeginEditing:(UITextView *)textView {
    if ([textView.textColor isEqual:[UIColor colorWithWhite:1 alpha:0.25]]) {
        textView.text = @"";
        textView.textColor = [UIColor colorWithWhite:1 alpha:0.80];
    }
}

- (void)textViewDidEndEditing:(UITextView *)textView {
    if (textView.text.length == 0) {
        textView.text = @"Share your thoughts here...";
        textView.textColor = [UIColor colorWithWhite:1 alpha:0.25];
    }
}

- (void)textViewDidChange:(UITextView *)textView {
    if ([textView.textColor isEqual:[UIColor colorWithWhite:1 alpha:0.25]]) return;
    NSInteger count = MIN((NSInteger)textView.text.length, 500);
    _charCount.text = [NSString stringWithFormat:@"%ld / 500", (long)count];
    _charCount.textColor = count >= 480
        ? [UIColor colorWithRed:1.0 green:0.35 blue:0.25 alpha:1.0]
        : [UIColor colorWithWhite:1 alpha:0.30];
    if (textView.text.length > 500) {
        textView.text = [textView.text substringToIndex:500];
    }
}

@end
