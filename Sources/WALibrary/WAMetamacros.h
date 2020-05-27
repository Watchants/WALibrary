//
//  WAMetamacros.h
//  WALibrary
//
//  Created by panghu on 5/30/20.
//

#ifndef WAMETAMACROS_H
#define WAMETAMACROS_H

#define __WAX_PASTE__(A,B) A##B

#define __WAX_GUARD__(A) A
#define __WAX_ARGV__(ARGV...) DEL, ##ARGV

#define __WAX_ARGV_A3__(A1,A2,A3,ARGV...) A3                // (DEL, id self, SEL name, ) => (SEL name)
#define __WAX_ARGV_DEL__(A1,A2,ARGV...) A2, ##ARGV          // (DEL, id self, SEL name, ) => (id self, SEL name, )
#define __WAX_ARGV_DEL13__(A1,A2,A3,ARGV...) A2, ##ARGV     // (DEL, id self, SEL name, ) => (id self, )

#define __WAX_CALORIG__(L,RT,ARGV...) if(__builtin_expect((__WAL_PASTE__(__origimp,L) != NULL), 1)) { ((__typeof(RT))__WAL_PASTE__(__origimp,L))(ARGV); }
#define __WAX_CALOVRD__(L,RT,ARGV...) if(__builtin_expect((__WAL_PASTE__(__ovrdimp,L) != NULL), 1)) { ((__typeof(RT))__WAL_PASTE__(__ovrdimp,L))(LS); }

#endif /* WAMetamacros_h */
