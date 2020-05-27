//
//  Tests.m
//  Tests
//
//  Created by Panghu on 3/21/20.
//

#import <XCTest/XCTest.h>
#import <objc/runtime.h>
#import <WALibrary/WALibrary.h>

@interface _RumtimeTestsClass : NSObject

@property (nonatomic, strong) NSObject *relpace;
@property (nonatomic, strong) NSObject *override;

@end

@interface _RumtimeTestsSubClass : _RumtimeTestsClass

@end

@implementation _RumtimeTestsClass

- (NSObject *)testRelpace {
    _relpace = [NSObject new];
    return _relpace;
}

- (NSObject *)testOverride:(NSObject *)override {
    _override = override;
    return _override;
}

@end

@implementation _RumtimeTestsSubClass

@end

#pragma mark Tests

@interface RumtimeTests : XCTestCase

@end

@implementation RumtimeTests

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"

- (void)setUp {
    
}

- (void)testRuntimeAdd {
    __block BOOL runing = false;
    __block _RumtimeTestsClass *cls1 = nil;
    SEL sel = NSSelectorFromString(@"testAdd");
    BOOL success = WARUNTIMEADDIMP(_RumtimeTestsClass.class, sel, NULL, void, WAIMPARGV(_RumtimeTestsClass *self, SEL name), {
        runing = true;
        cls1 = self;
    });
    _RumtimeTestsClass *cls2 = [_RumtimeTestsClass new];
    [cls2 performSelector:sel];
    
    Method method = class_getInstanceMethod(_RumtimeTestsClass.class, sel);
    
    XCTAssertTrue(success);
    XCTAssertTrue(runing);
    XCTAssertTrue(method != NULL);
    XCTAssertNotNil(cls1);
    XCTAssertTrue(cls1 == cls2);
}

- (void)testRuntimeReplace {
    __block BOOL runing = false;
    __block _RumtimeTestsClass *cls1 = nil;
    __block NSObject * ret = nil;
    SEL sel = @selector(testRelpace);
    __auto_type imp = WARUNTIMEREPLACEIMP(_RumtimeTestsClass.class, sel, NULL, NSObject *, WAIMPARGV(_RumtimeTestsClass *self, SEL name), {
        runing = true;
        cls1 = self;
        ret = WARUNTIMECALORIG(self, name);
        return ret;
    });

    _RumtimeTestsClass *cls2 = [_RumtimeTestsClass new];
    [cls2 testRelpace];
    
    XCTAssertTrue(imp != NULL);
    XCTAssertTrue(runing);
    XCTAssertNotNil(cls1);
    XCTAssertTrue(cls1 == cls2);
    XCTAssertTrue(ret == cls2.relpace);
}

- (void)testRuntimeOverride {
    __block BOOL runing = false;
    __block _RumtimeTestsSubClass *cls1 = nil;
    __block NSObject * ret = nil;
    SEL sel = @selector(testOverride:);
    __auto_type imp1 = WARUNTIMEREPLACEIMP(_RumtimeTestsClass.class, sel, NULL, NSObject *, WAIMPARGV(_RumtimeTestsSubClass *self, SEL name, NSObject *override), {
        runing = true;
        cls1 = self;
        ret = WARUNTIMECALORIG(self, name, override);
        return ret;
    });
    NSObject *override = [NSObject new];
    Method method = class_getInstanceMethod(_RumtimeTestsClass.class, sel);
    _RumtimeTestsSubClass *cls2 = [_RumtimeTestsSubClass new];
    [cls2 testOverride:override];
    
    bool is_mine;
    IMP imp2 = waclass_implementation([_RumtimeTestsSubClass class], sel, &is_mine);
    XCTAssertTrue(!is_mine);
    
    XCTAssertTrue(imp1 != NULL);
    XCTAssertTrue(imp2 != NULL);
    XCTAssertTrue((IMP)imp1 != imp2);
    XCTAssertTrue(runing);
    XCTAssertNotNil(cls1);
    XCTAssertTrue(method != NULL);
    XCTAssertTrue(cls1 == cls2);
    XCTAssertTrue(ret == override);
    XCTAssertTrue(ret == cls1.override);
}

- (void)testObjectMessageGetImplementation {
    {
        bool is_mine;
        IMP imp = waclass_implementation([self class], @selector(testObjectMessageGetImplementation), &is_mine);
        XCTAssertTrue(is_mine);
        XCTAssertTrue(imp != NULL);
    }
    {
        bool is_mine;
        IMP imp = waclass_implementation([self class], @selector(tearDown), &is_mine);
        XCTAssertTrue(!is_mine);
        XCTAssertTrue(imp != NULL);
    }
    {
        bool is_mine;
        IMP imp = waclass_implementation([self class], NSSelectorFromString(@"XXXXXX"), &is_mine);
        XCTAssertTrue(!is_mine);
        XCTAssertTrue(imp == NULL);
    }
}

- (void)testObjectMessageAdd {
    bool add = waclass_addImplementation([self class], NSSelectorFromString(@"YYYYYY"), NULL, ^ { });
    XCTAssertTrue(add);
}

- (void)testObjectMessageReaplce {
    IMP imp = waclass_replaceImplementation([self class], @selector(setUp), NULL, ^ { });
    XCTAssertTrue(imp != NULL);
}

- (void)testObjectMessageOveride {
    IMP imp = waclass_overrideImplementation([self class], @selector(invokeTest), NULL, ^ { });
    XCTAssertTrue(imp != NULL);
}

#pragma clang diagnostic pop

@end
