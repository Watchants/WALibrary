//
//  WANSObjectMessage.h
//  WAFoundation
//
//  Created by Panghu on 3/21/20.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT IMP _Nullable WANSObjectMessageClassGetImplementation(Class _Nonnull cls, SEL _Nonnull name, bool * _Nullable existSelf);

FOUNDATION_EXPORT bool WANSObjectMessageClassAddMethod(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

FOUNDATION_EXPORT IMP _Nullable WANSObjectMessageClassReplaceMethod(Class _Nullable cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

FOUNDATION_EXPORT IMP _Nullable WANSObjectMessageClassOverrideMethod(Class _Nonnull cls, SEL _Nonnull name, const char * _Nullable types, id _Nonnull block);

#define _WANSObjectMessageArguments(arguments...) DEL, ##arguments
#define _WANSObjectMessageArgument(argument) argument

#define _WANSObjectMessageWrapArguments(arguments...) arguments
#define _WANSObjectMessageWrapImplementArguments(a1, a2, arguments...) a2, ##arguments  // (DEL, id self, SEL name) => (id self, SEL name)
#define _WANSObjectMessageWrapBlockArguments(a1, a2, a3, arguments...) a2, ##arguments  // (DEL, id self, SEL name) => (id self)

#define _WANSObjectMessageWrapGetClass(code) Class __cls = code
#define _WANSObjectMessageWrapGetSelector(code) SEL __name = code
#define _WANSObjectMessageWrapGetTypes(code) const char * _Nullable __types = code

#define _WANSObjectMessageCallOriginal(arguments...) if(__builtin_expect((__ph_original_imp != NULL), 1)) { ((__typeof(__ph_original_impType))__ph_original_imp)(arguments); }
#define _WANSObjectMessageCallOverride(arguments...) if(__builtin_expect((__ph_override_imp != NULL), 1)) { ((__typeof(__ph_override_impType))__ph_override_imp)(arguments); }

// Public

/// A macro for wrapping the return type of the swizzled method.
#define WANSObjectMessageReturnType(type) type

/// A macro for wrapping arguments of the swizzled method.
#define WANSObjectMessageArguments(arguments...) _WANSObjectMessageArguments(arguments)

/// A macro for casting and calling original implementation.
/// May be used only in WANSObjectMessageReplaceMethod.
#define WANSObjectMessageCallOriginal(arguments...) _WANSObjectMessageCallOriginal(arguments)

/// A macro for casting and calling override implementation.
/// May be used only in WANSObjectMessageOverrideMethod.
#define WANSObjectMessageCallOverride(arguments...) _WANSObjectMessageCallOverride(arguments)

#define _WANSObjectMessageAddMethod(CLS, NAME, TYPES, ReturnType, Arguments, Code)                                              \
            _WANSObjectMessageWrapGetClass(CLS);                                                                                \
            _WANSObjectMessageWrapGetSelector(NAME);                                                                            \
            _WANSObjectMessageWrapGetTypes(TYPES);                                                                              \
            WANSObjectMessageClassAddMethod(__cls, __name, __types, ^ReturnType(_WANSObjectMessageWrapBlockArguments(Arguments))  \
                Code                                                                                                          \
            );

#define _WANSObjectMessageReplaceMethod(CLS, NAME, TYPES, ReturnType, Arguments, Code)                                                  \
            _WANSObjectMessageWrapGetClass(CLS);                                                                                        \
            _WANSObjectMessageWrapGetSelector(NAME);                                                                                    \
            _WANSObjectMessageWrapGetTypes(TYPES);                                                                                      \
            ReturnType (*__ph_original_impType)(_WANSObjectMessageWrapImplementArguments(Arguments));                                   \
            __ph_original_impType = NULL;                                                                                             \
            __block IMP __ph_original_imp;                                                                                            \
            __ph_original_imp =                                                                                                       \
                WANSObjectMessageClassReplaceMethod(__cls, __name, __types, ^ReturnType(_WANSObjectMessageWrapBlockArguments(Arguments))  \
                    Code                                                                                                              \
            );


#define _WANSObjectMessageOverrideMethod(CLS, NAME, TYPES, ReturnType, Arguments, Code)                                                 \
            _WANSObjectMessageWrapGetClass(CLS);                                                                                        \
            _WANSObjectMessageWrapGetSelector(NAME);                                                                                    \
            _WANSObjectMessageWrapGetTypes(TYPES);                                                                                      \
            __block IMP __ph_override_imp;                                                                                            \
            ReturnType (*__ph_override_impType)(_WANSObjectMessageWrapImplementArguments(Arguments));                                   \
            __ph_override_impType = NULL;                                                                                             \
            __ph_override_imp =                                                                                                       \
                WANSObjectMessageClassOverrideMethod(__cls, __name, __types, ^ReturnType(_WANSObjectMessageWrapBlockArguments(Arguments)) \
                    Code                                                                                                              \
            );

#define WANSObjectMessageAddMethod(cls, name, types, return_type, arguments, code)      \
    do {                                                                              \
        _WANSObjectMessageAddMethod(_WANSObjectMessageArgument(cls),                      \
                                _WANSObjectMessageArgument(name),                       \
                                _WANSObjectMessageArgument(types),                      \
                                _WANSObjectMessageArgument(return_type),                \
                                _WANSObjectMessageWrapArguments(arguments),             \
                                _WANSObjectMessageWrapArguments(code))                  \
    } while (false)

#define WANSObjectMessageReplaceMethod(cls, name, types, return_type, arguments, code)      \
    do {                                                                                  \
        _WANSObjectMessageReplaceMethod(_WANSObjectMessageArgument(cls),                      \
                                    _WANSObjectMessageArgument(name),                       \
                                    _WANSObjectMessageArgument(types),                      \
                                    _WANSObjectMessageArgument(return_type),                \
                                    _WANSObjectMessageWrapArguments(arguments),             \
                                    _WANSObjectMessageWrapArguments(code))                  \
    } while (false)

#define WANSObjectMessageOverrideMethod(cls, name, types, return_type, arguments, code)     \
do {                                                                                      \
    _WANSObjectMessageOverrideMethod(_WANSObjectMessageArgument(cls),                         \
                                _WANSObjectMessageArgument(name),                           \
                                _WANSObjectMessageArgument(types),                          \
                                _WANSObjectMessageArgument(return_type),                    \
                                _WANSObjectMessageWrapArguments(arguments),                 \
                                _WANSObjectMessageWrapArguments(code))                      \
} while (false)

NS_ASSUME_NONNULL_END
