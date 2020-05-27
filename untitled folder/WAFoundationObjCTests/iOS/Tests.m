//
//  Tests.m
//  WAFoundation
//
//  Created by Panghu on 3/21/20.
//

#import <XCTest/XCTest.h>

#import <WAFoundationObjC/WAFoundationObjC.h>

@interface Tests : XCTestCase

@end

@implementation Tests

- (void)setUp {
    
}

- (void)testObjectMessageGetImplementation {
    {
        bool existSelf;
        IMP imp = WANSObjectMessageClassGetImplementation([self class], @selector(testObjectMessageGetImplementation), &existSelf);
        XCTAssertTrue(existSelf);
        XCTAssertTrue(imp != NULL);
    }
    {
        bool existSelf;
        IMP imp = WANSObjectMessageClassGetImplementation([self class], @selector(tearDown), &existSelf);
        XCTAssertTrue(!existSelf);
        XCTAssertTrue(imp != NULL);
    }
    {
        bool existSelf;
        IMP imp = WANSObjectMessageClassGetImplementation([self class], NSSelectorFromString(@"testSelf1"), &existSelf);
        XCTAssertTrue(!existSelf);
        XCTAssertTrue(imp == NULL);
    }
}

- (void)testObjectMessageAdd {
    bool add = WANSObjectMessageClassAddMethod([self class], NSSelectorFromString(@"testSelf2"), NULL, ^ { });
    XCTAssertTrue(add);
}

- (void)testObjectMessageReaplce {
    IMP imp = WANSObjectMessageClassReplaceMethod([self class], @selector(setUp), NULL, ^ { });
    XCTAssertTrue(imp != NULL);
}

- (void)testObjectMessageOveride {
    IMP imp = WANSObjectMessageClassOverrideMethod([self class], @selector(invokeTest), NULL, ^ { });
    XCTAssertTrue(imp != NULL);
}

@end
