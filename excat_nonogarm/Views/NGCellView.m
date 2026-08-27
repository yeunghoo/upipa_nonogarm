//
//  NGCellView.m
//  excat_nonogarm

#import "NGCellView.h"
#import "NGTheme.h"

@interface NGCellView ()
@property (nonatomic, strong) UILabel *xLabel;
@property (nonatomic, strong) UITapGestureRecognizer *tapGesture;
@end

@implementation NGCellView

- (instancetype)initWithFrame:(CGRect)frame {
    self = [super initWithFrame:frame];
    if (self) {
        [self setupView];
    }
    return self;
}

- (instancetype)initWithCoder:(NSCoder *)coder {
    self = [super initWithCoder:coder];
    if (self) {
        [self setupView];
    }
    return self;
}

- (void)setupView {
    self.layer.cornerRadius = [NGTheme cellCornerRadius];
    self.layer.borderWidth = [NGTheme gridLineWidth];
    self.backgroundColor = [NGTheme cellEmptyColor];
    self.layer.borderColor = [NGTheme cellEmptyBorderColor].CGColor;
    self.clipsToBounds = YES;

    // X label (hidden by default)
    _xLabel = [[UILabel alloc] init];
    _xLabel.text = @"✕";
    _xLabel.textAlignment = NSTextAlignmentCenter;
    _xLabel.textColor = [NGTheme cellXForegroundColor];
    _xLabel.adjustsFontSizeToFitWidth = YES;
    _xLabel.minimumScaleFactor = 0.5;
    _xLabel.hidden = YES;
    _xLabel.translatesAutoresizingMaskIntoConstraints = NO;
    [self addSubview:_xLabel];

    [NSLayoutConstraint activateConstraints:@[
        [_xLabel.centerXAnchor constraintEqualToAnchor:self.centerXAnchor],
        [_xLabel.centerYAnchor constraintEqualToAnchor:self.centerYAnchor],
        [_xLabel.widthAnchor constraintEqualToAnchor:self.widthAnchor multiplier:0.7],
        [_xLabel.heightAnchor constraintEqualToAnchor:self.heightAnchor multiplier:0.7],
    ]];

    _tapGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTap:)];
    [self addGestureRecognizer:_tapGesture];

    self.userInteractionEnabled = YES;
}

- (void)setState:(NGCellState)state {
    _state = state;
    [self updateAppearance];
}

- (void)setFillColor:(UIColor *)fillColor {
    _fillColor = fillColor;
    if (_state == NGCellStateFilled) {
        [self updateAppearance];
    }
}

- (void)updateAppearance {
    switch (_state) {
        case NGCellStateEmpty:
            self.backgroundColor = [NGTheme cellEmptyColor];
            self.layer.borderColor = [NGTheme cellEmptyBorderColor].CGColor;
            _xLabel.hidden = YES;
            break;

        case NGCellStateFilled: {
            UIColor *color = _fillColor ?: [NGTheme accentColor];
            self.backgroundColor = color;
            self.layer.borderColor = [color colorWithAlphaComponent:0.6].CGColor;
            _xLabel.hidden = YES;
            break;
        }

        case NGCellStateMarkedX:
            self.backgroundColor = [NGTheme cellXColor];
            self.layer.borderColor = [NGTheme cellEmptyBorderColor].CGColor;
            _xLabel.hidden = NO;

            // Update font size relative to current cell size
            CGFloat fontSize = MIN(self.bounds.size.width, self.bounds.size.height) * 0.52;
            _xLabel.font = [NGTheme clueFontWithSize:MAX(fontSize, 8.0)];
            break;
    }
}

- (void)layoutSubviews {
    [super layoutSubviews];
    // Refresh font size on layout change
    if (_state == NGCellStateMarkedX) {
        CGFloat fontSize = MIN(self.bounds.size.width, self.bounds.size.height) * 0.52;
        _xLabel.font = [NGTheme clueFontWithSize:MAX(fontSize, 8.0)];
    }
}

- (void)handleTap:(UITapGestureRecognizer *)gesture {
    [self.delegate cellViewDidTap:self];
}

- (void)playErrorAnimation {
    // Flash red then return to current state
    UIColor *originalBG = self.backgroundColor;
    [UIView animateWithDuration:0.08 animations:^{
        self.backgroundColor = [NGTheme cellErrorColor];
        self.transform = CGAffineTransformMakeScale(0.88, 0.88);
    } completion:^(BOOL finished) {
        [UIView animateWithDuration:0.25 animations:^{
            self.backgroundColor = originalBG;
            self.transform = CGAffineTransformIdentity;
        }];
    }];
}

- (void)playSuccessAnimation {
    [UIView animateWithDuration:0.10 animations:^{
        self.transform = CGAffineTransformMakeScale(1.12, 1.12);
    } completion:^(BOOL finished) {
        [UIView animateWithDuration:0.15 animations:^{
            self.transform = CGAffineTransformIdentity;
        }];
    }];
}

@end
