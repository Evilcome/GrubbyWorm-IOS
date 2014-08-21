#import <UIKit/UIKit.h>
#import "GADBannerViewDelegate.h"

@class RootViewController;
@class GADBannerView;
@class GADBannerViewDelegate;

@interface AppController : NSObject <UIApplicationDelegate, GADBannerViewDelegate> {
    UIWindow *window;
    GADBannerView *bannerAd; //新增代码
}

@property(nonatomic, readonly) RootViewController* viewController;

@end

