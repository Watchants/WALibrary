//
//  WAMacros.h
//  WALibrary
//
//  Created by panghu on 5/30/20.
//

#ifndef WAMACROS_H
#define WAMACROS_H

#import <WALibrary/WARuntime.h>

//
// waclass_addImplementation
#define __WARUNTIMEADDIMP(CLASS,NAME,TYPES,RETURN,ARGV,CODE,L)                          \
            __typeof__(CLASS) __WAX_PASTE__(__class,L) = (CLASS);                       \
            __typeof__(NAME) __WAX_PASTE__(__name,L) = (NAME);                          \
            __typeof__(TYPES) __WAX_PASTE__(__types,L) = (TYPES);                       \
            __attribute__((unused)) __WAX_ARGV_A3__(ARGV) = __WAX_PASTE__(__name,L);    \
            waclass_addImplementation(__WAX_PASTE__(__class,L),__WAX_PASTE__(__name,L),__WAX_PASTE__(__types,L), ^__typeof(RETURN)(__WAX_ARGV_DEL13__(ARGV))CODE);

//
// waclass_replaceImplementation
#define __WARUNTIMEREPLACEIMP(CLASS,NAME,TYPES,RETURN,ARGV,CODE,L)                      \
            __typeof__(CLASS) __WAX_PASTE__(__class,L) = (CLASS);                       \
            __typeof__(NAME) __WAX_PASTE__(__name,L) = (NAME);                          \
            __typeof__(TYPES) __WAX_PASTE__(__types,L) = (TYPES);                       \
            __attribute__((unused)) __WAX_ARGV_A3__(ARGV) = __WAX_PASTE__(__name,L);    \
            __block __typeof(RETURN) (*__wax_orig_imp_)(__WAX_ARGV_DEL__(ARGV)) =       \
                (__typeof(__wax_orig_imp_))waclass_replaceImplementation(__WAX_PASTE__(__class,L),__WAX_PASTE__(__name,L),__WAX_PASTE__(__types,L),^__typeof(RETURN)(__WAX_ARGV_DEL13__(ARGV))CODE); \
            __wax_orig_imp_;

//
// waclass_overrideImplementation
#define __WARUNTIMEOVERRIDEIMP(CLASS,NAME,TYPES,RETURN,ARGV,CODE,L)                     \
            __typeof__(CLASS) __WAX_PASTE__(__class,L) = (CLASS);                       \
            __typeof__(NAME) __WAX_PASTE__(__name,L) = (NAME);                          \
            __typeof__(TYPES) __WAX_PASTE__(__types,L) = (TYPES);                       \
            __attribute__((unused)) __WAX_ARGV_A3__(ARGV) = __WAX_PASTE__(__name,L);    \
            __block __typeof(RETURN) (*__wax_ovrd_imp_)(__WAX_ARGV_DEL__(ARGV)) =       \
                (__typeof(__wax_ovrd_imp_))waclass_overrideImplementation(__WAX_PASTE__(__class,L),__WAX_PASTE__(__name,L),__WAX_PASTE__(__types,L),^__typeof(RETURN)(__WAX_ARGV_DEL13__(ARGV))CODE); \
            __wax_ovrd_imp_;

///
/// waclass_addImplementation
#define WARUNTIMEADDIMP(CLASS,NAME,TYPES,RETURN,ARGV,CODE) ({                           \
            __WARUNTIMEADDIMP(__WAX_GUARD__(CLASS),__WAX_GUARD__(NAME),__WAX_GUARD__(TYPES),__WAX_GUARD__(RETURN),__WAX_ARGV__(ARGV),__WAX_GUARD__(CODE),__COUNTER__)       \
        })

///
/// waclass_replaceImplementation
#define WARUNTIMEREPLACEIMP(CLASS,NAME,TYPES,RETURN,ARGV,CODE) ({                       \
            __WARUNTIMEREPLACEIMP(__WAX_GUARD__(CLASS),__WAX_GUARD__(NAME),__WAX_GUARD__(TYPES),__WAX_GUARD__(RETURN),__WAX_ARGV__(ARGV),__WAX_GUARD__(CODE),__COUNTER__)   \
        })

///
/// waclass_overrideImplementation
#define WARUNTIMEOVERRIDEIMP(CLASS,NAME,TYPES,RETURN,ARGV,CODE) ({                      \
            __WARUNTIMEOVERRIDEIMP(__WAX_GUARD__(CLASS),__WAX_GUARD__(NAME),__WAX_GUARD__(TYPES),__WAX_GUARD__(RETURN),__WAX_ARGV__(ARGV),__WAX_GUARD__(CODE),__COUNTER__)  \
        })

///
/// ARGV
#define WAIMPARGV(ARGV...) ARGV

///
/// waclass_replaceImplementation call origin
#define WARUNTIMECALORIG(ARGV...) \
            __wax_orig_imp_(ARGV)

///
/// waclass_replaceImplementation call origin
#define WARUNTIMECALOVRD(ARGV...) \
            __wax_ovrd_imp_(ARGV)

#endif /* WAMACROS_H */
