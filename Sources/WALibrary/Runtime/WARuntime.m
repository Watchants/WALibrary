//
//  WARuntime.m
//  WALibrary
//
//  Created by panghu on 5/30/20.
//

#import "WARuntime.h"

#import <objc/runtime.h>
#import <objc/message.h>

IMP _Nullable waclass_implementation(Class _Nonnull cls, SEL _Nonnull name, bool * _Nullable is_mine) {
    *is_mine = false;

    if (object_isClass(cls) == false) return NULL;
    
    Method method = class_isMetaClass(cls) ? class_getClassMethod(cls, name) : class_getInstanceMethod(cls, name);
    if (method == NULL) return NULL;
        
    unsigned int count;
    Method *methods = class_copyMethodList(cls, &count);
    
    for (unsigned int index = 0; index < count; index ++) {
        method = methods[index];
        SEL sel = method_getName(method);
        if (sel_isEqual(sel, name)) {
            *is_mine = true;
            break;
        }
    }
    
    if (methods != NULL) free(methods);
    
    return method != NULL ? method_getImplementation(method) : NULL;
}

bool waclass_addImplementation(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block) {
    bool is_mine;
    IMP imp = waclass_implementation(cls, name, &is_mine);
    if (imp == NULL && is_mine == false) {
        return class_addMethod(cls, name, imp_implementationWithBlock(block), types);
    } else {
        return false;
    }
}

IMP _Nullable waclass_replaceImplementation(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block) {
    bool is_mine;
    IMP imp = waclass_implementation(cls, name, &is_mine);
    if (imp != NULL && is_mine == true) {
        return class_replaceMethod(cls, name, imp_implementationWithBlock(block), types);
    } else {
        return NULL;
    }
}

IMP _Nullable waclass_overrideImplementation(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block) {
    bool is_mine;
    IMP imp = waclass_implementation(cls, name, &is_mine);
    if (imp != NULL && is_mine == false) {
        bool success = class_addMethod(cls, name, imp_implementationWithBlock(block), types);
        return success ? imp : NULL;
    } else {
        return NULL;
    }
}
