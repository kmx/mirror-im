/* configuration file for the IM_FFTW3 library */

/* extra CFLAGS for codelets */
#define CODELET_OPTIM	""

/* Define to a macro mangling the given C identifier (in lower and upper
   case), which must not contain underscores, for linking with Fortran. */
#undef F77_FUNC

/* As F77_FUNC, but for C identifiers containing underscores. */
#undef F77_FUNC_

/* Define if F77_FUNC and F77_FUNC_ are equivalent. */
#undef F77_FUNC_EQUIV

/* C compiler name and flags */
#define FFTW_CC	""

/* Define to enable extra FFTW debugging code. */
#undef FFTW_DEBUG

/* Define to enable alignment debugging hacks. */
#undef FFTW_DEBUG_ALIGNMENT

/* Define to enable debugging malloc. */
#undef FFTW_DEBUG_MALLOC

/* enable fast, unsafe modular multiplications, risking overflow for large
   prime sizes */
#undef FFTW_ENABLE_UNSAFE_MULMOD

/* Define to compile in long-double precision. */
#undef FFTW_LDOUBLE

/* Define to compile in single precision. */
#define FFTW_SINGLE 1

/* Define to enable 3DNow! optimizations. */
#undef HAVE_3DNOW

/* Define to 1 if you have `alloca', as a function or macro. */
#undef HAVE_ALLOCA

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#undef HAVE_ALLOCA_H

/* Define to enable Altivec optimizations. */
#undef HAVE_ALTIVEC

/* Define to 1 if you have the `BSDgettimeofday' function. */
#undef HAVE_BSDGETTIMEOFDAY

/* Define to 1 if you have the `clock_gettime' function. */
#undef HAVE_CLOCK_GETTIME

/* Define to 1 if you have the `cosl' function. */
#undef HAVE_COSL

/* Define to 1 if you have the <c_asm.h> header file. */
#undef HAVE_C_ASM_H

/* Define to 1 if you have the declaration of `drand48', and to 0 if you don't. */
#define HAVE_DECL_DRAND48	0

/* Define to 1 if you have the declaration of `memalign', and to 0 if you
   don't. */
#define HAVE_DECL_MEMALIGN	0

/* Define to 1 if you have the declaration of `posix_memalign', and to 0 if
   you don't. */
#define HAVE_DECL_POSIX_MEMALIGN	0

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
#undef HAVE_DOPRNT

/* Define to 1 if you have the `drand48' function. */
#undef HAVE_DRAND48

/* Define to 1 if you have the `gethrtime' function. */
#undef HAVE_GETHRTIME

/* Define to 1 if you have the `gettimeofday' function. */
#undef HAVE_GETTIMEOFDAY

/* Define to 1 if hrtime_t is defined in <sys/time.h> */
#undef HAVE_HRTIME_T

/* Define to 1 if you have the <intrinsics.h> header file. */
#undef HAVE_INTRINSICS_H

/* Define to 1 if you have the <inttypes.h> header file. */
#undef HAVE_INTTYPES_H

/* Define if the isnan() function/macro is available. */
#define HAVE_ISNAN	1

/* Define to enable AMD K7 optimizations. */
#undef HAVE_K7

/* Define to 1 if you have the <libintl.h> header file. */
#undef HAVE_LIBINTL_H

/* Define to 1 if you have the `m' library (-lm). */
#undef HAVE_LIBM

/* Define to 1 if you have the <limits.h> header file. */
#define HAVE_LIMITS_H	1

/* Define to 1 if you have the <malloc.h> header file. */
/* #define HAVE_MALLOC_H	1 */

/* Define to 1 if you have the `memalign' function. */
#undef HAVE_MEMALIGN

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H	1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET	1

/* Define to 1 if you have the `posix_memalign' function. */
#undef HAVE_POSIX_MEMALIGN

/* Define if you have POSIX threads libraries and header files. */
#undef HAVE_PTHREAD

/* Define to 1 if you have the `read_real_time' function. */
#undef HAVE_READ_REAL_TIME

/* Define to 1 if you have the `sinl' function. */
#define HAVE_SINL	1

/* Define to 1 if you have the `sqrt' function. */
#define HAVE_SQRT	1

/* Define to enable SSE optimizations. */
#undef HAVE_SSE
/*#define HAVE_SSE 1 */

/* Define to enable SSE2 optimizations. */
#undef HAVE_SSE2

/* Define to 1 if you have the <stddef.h> header file. */
#define HAVE_STDDEF_H	1

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H	1

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H	1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H	1

/* Define to 1 if you have the <sys/time.h> header file. */
#undef HAVE_SYS_TIME_H

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H	1

/* Define to 1 if you have the `tanl' function. */
#define HAVE_TANL	1

/* Define if we have a threads library. */
#undef HAVE_THREADS

/* Define to 1 if you have the `time_base_to_time' function. */
#undef HAVE_TIME_BASE_TO_TIME

/* Define to 1 if the system has the type `uintptr_t'. */
/* #undef HAVE_UINTPTR_T */

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define to 1 if you have the `vprintf' function. */
#define HAVE_VPRINTF

/* Define to 1 if you have the `_mm_free' function. */
#undef HAVE__MM_FREE

/* Define to 1 if you have the `_mm_malloc' function. */
#undef HAVE__MM_MALLOC

/* Define if you have the UNICOS _rtc() intrinsic. */
#undef HAVE__RTC

/* Name of package */
#define PACKAGE	"FFTW"

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#define PACKAGE_NAME	"FFTW_PACKAGENAME"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING	"FFTW V3"

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the version of this package. */
#define PACKAGE_VERSION	3

/* Define to the necessary symbol if this constant uses a non-standard name on
   your system. */
#undef PTHREAD_CREATE_JOINABLE

/* The size of a `double', as computed by sizeof. */
#define SIZEOF_DOUBLE	8

/* The size of a `int', as computed by sizeof. */
#define SIZEOF_INT	4

/* The size of a `long', as computed by sizeof. */
#define SIZEOF_LONG	4

/* The size of a `long double', as computed by sizeof. */
#define SIZEOF_LONG_DOUBLE	8

/* The size of a `long long', as computed by sizeof. */
#undef SIZEOF_LONG_LONG	/* NO LONG LONG IN VC++ */

/* The size of a `unsigned int', as computed by sizeof. */
#define SIZEOF_UNSIGNED_INT	4

/* The size of a `unsigned long', as computed by sizeof. */
#define SIZEOF_UNSIGNED_LONG	4

/* The size of a `unsigned long long', as computed by sizeof. */
#undef SIZEOF_UNSIGNED_LONG_LONG

/* The size of a `void *', as computed by sizeof. */
#define SIZEOF_VOID_P	4

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
        STACK_DIRECTION > 0 => grows toward higher addresses
        STACK_DIRECTION < 0 => grows toward lower addresses
        STACK_DIRECTION = 0 => direction of growth unknown */
#undef STACK_DIRECTION

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS	1

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#undef TIME_WITH_SYS_TIME

/* Define if we have and are using OpenMP multithreading directives */
#undef USING_OPENMP_THREADS

/* Define if we have and are using POSIX threads. */
#undef USING_POSIX_THREADS

/* Version number of package */
#define VERSION	"3"

/* Use common Windows Fortran mangling styles for the Fortran interfaces. */
#undef WINDOWS_F77_MANGLING

/* Use our own 16-byte aligned malloc routine; mainly helpful for Windows
   systems lacking aligned allocation system-library routines. */
#undef WITHOUT_CYCLE_COUNTER

/* Use our own 16-byte aligned malloc routine; mainly helpful for Windows
   systems lacking aligned allocation system-library routines. */
#define WITH_OUR_MALLOC16	1

/* Define to empty if `const' does not conform to ANSI C. */
#undef const

/* Define as `__inline' if that's what the C compiler calls it, or to nothing
   if it is not supported. */
#define inline	__inline

/* Define to `unsigned' if <sys/types.h> does not define. */
#undef size_t

/*			 VC++ specific parameters  */
/*			added May14th 2003, S.Ruel */
#define		HAVE_CONFIG_H		1
#define		isnan				_isnan
#define		__inline__			__inline
#define		__asm__				__asm

/* The intel and processor pack libraries should be compatible */
#ifdef _MSC_VER
#define		__ICC				1
#endif
