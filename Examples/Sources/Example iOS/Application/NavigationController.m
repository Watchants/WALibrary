//
//  NavigationController.m
//  Example iOS
//
//  Created by Panghu on 3/22/20.
//

#import "NavigationController.h"

#import <WALibrary/WALibrary.h>

@interface NavigationController ()

@end

@implementation NavigationController

- (void)viewDidLayoutSubviews {
//    NSLog(@"%s", __func__);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    bool success = WARUNTIMEADDIMP(UIViewController.class, NSSelectorFromString(@"viewDidLoad1"), NULL, void, WAIMPARGV(NavigationController * self, SEL name), {
        NSLog(@"%@ %@", NSStringFromSelector(name), self);
    });
    NSLog(@"%d", success);
    
    __auto_type imp1 = WARUNTIMEREPLACEIMP(UIViewController.class, NSSelectorFromString(@"viewDidLayoutSubviews"), NULL, void, WAIMPARGV(NavigationController * self, SEL name), {
        NSLog(@"%@ %@", NSStringFromSelector(name), self);
        WARUNTIMECALORIG(self, name);
    });
    NSLog(@"%p", imp1);
    
    __auto_type imp2 = WARUNTIMEOVERRIDEIMP(UIViewController.class, NSSelectorFromString(@"viewDidAppear:"), NULL, bool, WAIMPARGV(NavigationController * self, SEL name, bool b), {
        NSLog(@"%@ %@", NSStringFromSelector(name), self);
        return WARUNTIMECALOVRD(self, name, b);
    });
    NSLog(@"%p", imp2);
    
}

@end
