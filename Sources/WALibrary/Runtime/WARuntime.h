//
//  WARuntime.h
//  WALibrary
//
//  Created by panghu on 5/30/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXTERN IMP _Nullable waclass_implementation(Class _Nonnull cls, SEL _Nonnull name, bool * _Nullable is_mine);

FOUNDATION_EXTERN bool waclass_addImplementation(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

FOUNDATION_EXTERN IMP _Nullable waclass_replaceImplementation(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

FOUNDATION_EXTERN IMP _Nullable waclass_overrideImplementation(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

NS_ASSUME_NONNULL_END
