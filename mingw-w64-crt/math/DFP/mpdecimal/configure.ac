
AC_PREREQ([2.67])
AC_INIT(mpdecimal, 2.4.0, mpdecimal-bugs@bytereef.org, mpdecimal, http://www.bytereef.org/mpdecimal/index.html)
AC_CONFIG_HEADER(config.h)
AC_CONFIG_FILES([Makefile libmpdec/Makefile tests/Makefile libmpdec/mpdecimal.h])
AC_ARG_VAR(MACHINE, [force configuration: x64, uint128, ansi64, ppro, ansi32, ansi-legacy])

LIBSTATIC=libmpdec.a
LIBSONAME=libmpdec.so.2
LIBSHARED=libmpdec.so.2.4.0
AC_SUBST(LIBSTATIC)
AC_SUBST(LIBSONAME)
AC_SUBST(LIBSHARED)


# Apparently purely informational for this particular build:
AC_CANONICAL_HOST
AC_SUBST(build)
AC_SUBST(host)

# Language and compiler:
AC_LANG_C
saved_cflags=$CFLAGS
AC_PROG_CC
CFLAGS=$saved_cflags

# ar and ranlib:
AC_CHECK_TOOL(AR, ar, ar)
AC_PROG_RANLIB
AC_SUBST(RANLIB)

# System and machine type (only used for Solaris and Darwin):
AC_MSG_CHECKING(system as reported by uname -s)
ac_sys_system=`uname -s`
AC_MSG_RESULT($ac_sys_system)

# Checks for header files:
AC_HEADER_STDC
AC_CHECK_HEADERS(inttypes.h stdint.h)

# Type availability checks:
AC_TYPE_SIZE_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_CHECK_TYPE(__uint128_t, AC_DEFINE(HAVE_UINT128_T, 1,
              [Define if your compiler provides __uint128_t.]),,)

# Sizes of various types:
AC_CHECK_SIZEOF(size_t, 4)
AC_CHECK_SIZEOF(__uint128_t, 8)

# x64 with gcc asm:
AC_MSG_CHECKING(for x64 gcc inline assembler)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[
  __asm__ __volatile__ ("movq %rcx, %rax");
]])],[have_gcc_asm_for_x64=yes],[have_gcc_asm_for_x64=no])
AC_MSG_RESULT($have_gcc_asm_for_x64)
if test "$have_gcc_asm_for_x64" = yes; then
    AC_DEFINE(HAVE_GCC_ASM_FOR_X64, 1,
    [Define if we can use x64 gcc inline assembler.])
fi

# x87 with gcc asm:
AC_MSG_CHECKING(for x87 gcc inline assembler)
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[
  unsigned short cw;
  __asm__ __volatile__ ("fnstcw %0" : "=m" (cw));
  __asm__ __volatile__ ("fldcw %0" : : "m" (cw));
]])],[have_gcc_asm_for_x87=yes],[have_gcc_asm_for_x87=no])
AC_MSG_RESULT($have_gcc_asm_for_x87)
if test "$have_gcc_asm_for_x87" = yes; then
    AC_DEFINE(HAVE_GCC_ASM_FOR_X87, 1,
    [Define if we can use x87 gcc inline assembler.])
fi

# Availability of -O2:
AC_MSG_CHECKING(for -O2)
saved_cflags="$CFLAGS"
CFLAGS="-O2"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]], [[
]])],[have_O2=yes],[have_O2=no])
AC_MSG_RESULT($have_O2)
CFLAGS="$saved_cflags"

# Install program:
AC_PROG_INSTALL
AC_SUBST(INSTALL)

# _FORTIFY_SOURCE wrappers for memmove and bcopy are incorrect:
# http://sourceware.org/ml/libc-alpha/2010-12/msg00009.html
AC_MSG_CHECKING(for glibc _FORTIFY_SOURCE/memmove bug)
saved_cflags="$CFLAGS"
CFLAGS="-O2 -D_FORTIFY_SOURCE=2"
if test "$have_O2" = no; then
    CFLAGS=""
fi
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void foo(void *p, void *q) { memmove(p, q, 19); }
int main() {
  char a[32] = "123456789000000000";
  foo(&a[9], a);
  if (strcmp(a, "123456789123456789000000000") != 0)
    return 1;
  foo(a, &a[9]);
  if (strcmp(a, "123456789000000000") != 0)
    return 1;
  return 0;
}
]])],
[have_glibc_memmove_bug=no],
[have_glibc_memmove_bug=yes],
[have_glibc_memmove_bug=undefined])
CFLAGS="$saved_cflags"
AC_MSG_RESULT($have_glibc_memmove_bug)
if test "$have_glibc_memmove_bug" = yes; then
    AC_DEFINE(HAVE_GLIBC_MEMMOVE_BUG, 1,
    [Define if glibc has incorrect _FORTIFY_SOURCE wrappers
     for memmove and bcopy.])
fi

# suncc is dectected as cc:
case $ac_sys_system in
sun*|Sun*)
    case $CC in
        cc)
            CC=suncc
            ;;
    esac
esac

# Compiler dependent settings:
MPD_WARN="-Wall"
MPD_OPT="-O2 -fpic"
MPD_PGEN=
MPD_PUSE=
case $CC in
    *gcc*)
        MPD_WARN="-Wall -W -Wno-unknown-pragmas -std=c99 -pedantic"
        MPD_OPT="-O2 -fpic"
        MPD_PGEN="-fprofile-generate -fprofile-values"
        MPD_PUSE="-fprofile-use -freorder-blocks"
        ;;
    *icc*)
        AR=xiar
        MPD_WARN="-Wall -Wno-unknown-pragmas"
        MPD_OPT="-O2 -fpic"
        MPD_PGEN="-wd11505 -prof-gen"
        MPD_PUSE="-wd11505 -prof-use"
        ;;
    *clang*)
        MPD_WARN="-Wall -W -Wno-unknown-pragmas"
        MPD_OPT="-O2 -fpic"
        ;;
    *suncc*)
        MPD_WARN=
        MPD_OPT="-O2 -fpic"
        ;;
    *ccomp*)
        MPD_WARN=
        MPD_CONFIG="-DCONFIG_32 -DANSI -DLEGACY_COMPILER"
        MPD_OPT="-fstruct-passing -fstruct-assign"
        LD="gcc"
        LDFLAGS="-m32"
        ;;
esac

# Values for the MPD_HEADER_CONFIG variable:
CONFIG_64="
/* ABI: 64-bit */
#ifdef CONFIG_32
  #error \"cannot use CONFIG_32 with 64-bit header.\"
#endif

#ifndef CONFIG_64
  #define CONFIG_64
#endif"

CONFIG_32="
/* ABI: 32-bit */
#ifdef CONFIG_64
  #error \"cannot use CONFIG_64 with 32-bit header.\"
#endif

#ifndef CONFIG_32
  #define CONFIG_32
#endif"

CONFIG_32_LEGACY="
/* ABI: 32-bit */
#ifdef CONFIG_64
  #error \"cannot use CONFIG_64 with 32-bit header.\"
#endif

#ifndef CONFIG_32
  #define CONFIG_32
#endif

/* libmpdec was compiled without support for int64_t */
#ifndef LEGACY_COMPILER
  #define LEGACY_COMPILER
#endif"

CONFIG_UNIVERSAL="
/* Mac OS X: support for building universal binaries */
#if defined(CONFIG_64) || defined(CONFIG_32)
  #error \"cannot use CONFIG_64 or CONFIG_32 with universal header.\"
#endif

#if defined(__ppc__)
  #define CONFIG_32
  #define ANSI
#elif defined(__ppc64__)
  #define CONFIG_64
  #define ANSI
#elif defined(__i386__)
  #define CONFIG_32
  #define ANSI
#elif defined(__x86_64__)
  #define CONFIG_64
  #define ASM
#else
  #error \"unknown architecture for universal build.\"
#endif"

CONFIG_FULLCOV="
/* DO NOT USE IN PRODUCTION! */
#if defined(CONFIG_64) || !defined(CONFIG_32)
  #error \"CONFIG_32 must be defined for full coverage.\"
#endif"

# Auto-detect machine dependent settings:
M64=
M32=
if test -n "$MACHINE"; then
    M64="-m64 "
    M32="-m32 "
    case "$MACHINE" in
        x64|uint128|ansi64|full_coverage|ppro|ansi32|ansi-legacy|universal)
            : ;;
        *)
            echo "configure: error: invalid MACHINE variable: $MACHINE"
            exit 1 ;;
    esac
elif test $ac_cv_sizeof_size_t -eq 8; then
    if test $have_gcc_asm_for_x64 = yes; then
        MACHINE="x64"
    elif test $ac_cv_sizeof__uint128_t -eq 8; then
        MACHINE="uint128"
    else
        MACHINE="ansi64"
    fi
else
    # Macros for detecting uint64_t and int64_t are unreliable:
    case $CC in
        *ccomp*)
            MACHINE="ansi-legacy"
            ;;
        *)
            MACHINE="ansi32"
            ;;
    esac
    if test $have_gcc_asm_for_x87 = yes; then
        case $CC in
            *gcc*|*clang*) # icc >= 11.0 works as well
                case $ac_sys_system in
                    darwin*|Darwin*)
                    ;;
                *)
                    MACHINE="ppro"
                    ;;
                esac
            ;;
        esac
    fi
fi

# Set configuration variables:
MPD_PREC=9
MPD_DPREC=18
CONFIGURE_LDFLAGS=
case "$MACHINE" in
    x64)
        MPD_HEADER_CONFIG=$CONFIG_64
        MPD_CONFIG=$M64"-DCONFIG_64 -DASM"
        CONFIGURE_LDFLAGS=$M64
        MPD_PREC=19
        MPD_DPREC=38
        ;;
    uint128)
        MPD_HEADER_CONFIG=$CONFIG_64
        MPD_CONFIG=$M64"-DCONFIG_64 -DANSI -DHAVE_UINT128_T"
        CONFIGURE_LDFLAGS=$M64
        MPD_PREC=19
        MPD_DPREC=38
        ;;
    ansi64)
        MPD_HEADER_CONFIG=$CONFIG_64
        MPD_CONFIG=$M64"-DCONFIG_64 -DANSI"
        CONFIGURE_LDFLAGS=$M64
        MPD_PREC=19
        MPD_DPREC=38
        ;;
    full_coverage)
        # Formerly ansi64c32, for testing only!
        MPD_HEADER_CONFIG=$CONFIG_FULLCOV
        MPD_CONFIG=$M64"-DCONFIG_32 -DANSI"
        CONFIGURE_LDFLAGS=$M64
        ;;
    ppro)
        MPD_HEADER_CONFIG=$CONFIG_32
        MPD_CONFIG=$M32"-DCONFIG_32 -DPPRO -DASM"
        CONFIGURE_LDFLAGS=$M32
        # Some versions of gcc miscompile inline asm:
        # http://gcc.gnu.org/bugzilla/show_bug.cgi?id=46491
        # http://gcc.gnu.org/ml/gcc/2010-11/msg00366.html
        case $CC in
            *gcc*)
                AC_MSG_CHECKING(for gcc ipa-pure-const bug)
                saved_cflags="$CFLAGS"
                CFLAGS="-O2"
                AC_RUN_IFELSE([AC_LANG_SOURCE([[
                __attribute__((noinline)) int
                foo(int *p) {
                  int r;
                  asm ( "movl \$6, (%1)\n\t"
                        "xorl %0, %0\n\t"
                        : "=r" (r) : "r" (p) : "memory"
                  );
                  return r;
                }
                int main() {
                  int p = 8;
                  if ((foo(&p) ? : p) != 6)
                    return 1;
                  return 0;
                }
                ]])],
                [have_ipa_pure_const_bug=no],
                [have_ipa_pure_const_bug=yes],
                [have_ipa_pure_const_bug=undefined])
                CFLAGS="$saved_cflags"
                AC_MSG_RESULT($have_ipa_pure_const_bug)
                if test "$have_ipa_pure_const_bug" = yes; then
                    MPD_CONFIG="$MPD_CONFIG -fno-ipa-pure-const"
                    AC_DEFINE(HAVE_IPA_PURE_CONST_BUG, 1,
                [Define if gcc has the ipa-pure-const bug.])
                fi
            ;;
        esac
        ;;
    ansi32)
        MPD_HEADER_CONFIG=$CONFIG_32
        MPD_CONFIG=$M32"-DCONFIG_32 -DANSI"
        CONFIGURE_LDFLAGS=$M32
        ;;
    ansi-legacy)
        MPD_HEADER_CONFIG=$CONFIG_32_LEGACY
        MPD_CONFIG=$M32"-DCONFIG_32 -DANSI -DLEGACY_COMPILER"
        CONFIGURE_LDFLAGS=$M32
        ;;
    universal)
        MPD_HEADER_CONFIG=$CONFIG_UNIVERSAL
        MPD_CONFIG="-DUNIVERSAL"
esac


# Substitute variables and generate output:
if test -z "$LD"; then
    LD="$CC"
fi
AC_SUBST(LD)
AC_SUBST(AR)
AC_SUBST(MPD_HEADER)
AC_SUBST(MPD_WARN)
AC_SUBST(MPD_CONFIG)
AC_SUBST(MPD_HEADER_CONFIG)
AC_SUBST(MPD_OPT)

AC_SUBST(MPD_PGEN)
AC_SUBST(MPD_PUSE)
AC_SUBST(MPD_PREC)
AC_SUBST(MPD_DPREC)

if test -z "$CFLAGS"; then
    CONFIGURE_CFLAGS="$MPD_WARN $MPD_CONFIG $MPD_OPT"
else
    CONFIGURE_CFLAGS="$MPD_WARN $MPD_CONFIG $MPD_OPT $CFLAGS"
fi
if test "$have_glibc_memmove_bug" = yes; then
    CONFIGURE_CFLAGS="$CONFIGURE_CFLAGS -U_FORTIFY_SOURCE"
fi

if test -n "$LDFLAGS"; then
    CONFIGURE_LDFLAGS="$LDFLAGS"
fi

AC_SUBST(CONFIGURE_CFLAGS)
AC_SUBST(CONFIGURE_LDFLAGS)

AC_OUTPUT

GLIBC_MEMMOVE_BUG_WARN="
***************************** WARNING *********************************

Detected glibc _FORTIFY_SOURCE/memmove bug. See:

    http://sourceware.org/ml/libc-alpha/2010-12/msg00009.html

Enabling -U_FORTIFY_SOURCE workaround. If -D_FORTIFY_SOURCE is also
present in the command line, make sure that the order of the two
options is:

   ... -D_FORTIFY_SOURCE=2 ... -U_FORTIFY_SOURCE ...

A better solution is to upgrade glibc or to report the bug to your
OS vendor.

***************************** WARNING *********************************
"
if test "$have_glibc_memmove_bug" = yes; then
    echo "$GLIBC_MEMMOVE_BUG_WARN"
fi

