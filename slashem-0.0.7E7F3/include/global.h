/*	SCCS Id: @(#)global.h	3.4	2003/08/31	*/
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>

/* #define ALPHA */	/* if an alpha-test copy */
/* #define BETA */	/* if an alpha- or beta-test copy */
/* #define OBJ_SANITY *//* Object sanity checks for all players */

/*
 * Files expected to exist in the playground directory if file areas are not
 * enabled and in the named areas otherwise.
 * [WAC] - put a NH_ prefix on all the names to prevent conflicts
 */

#define NH_RECORD		"record"  /* a file containing list of topscorers */
#define NH_RECORD_AREA	FILE_AREA_VAR
#define NH_HELP		"help"	  /* a file containing command descriptions */
#define NH_HELP_AREA	FILE_AREA_SHARE
#define NH_SHELP		"hh"		/* abbreviated form of the same */
#define NH_SHELP_AREA	FILE_AREA_SHARE
#define NH_DEBUGHELP	"wizhelp"	/* a file containing debug mode cmds */
#define NH_DEBUGHELP_AREA	FILE_AREA_SHARE
#define NH_RUMORFILE	"rumors"	/* a file with fortune cookies */
#define NH_RUMORAREA	FILE_AREA_SHARE
#define NH_ORACLEFILE	"oracles"	/* a file with oracular information */
#define NH_ORACLEAREA	FILE_AREA_SHARE
#define NH_DATAFILE	"data"	/* a file giving the meaning of symbols used */
#define NH_DATAAREA	FILE_AREA_SHARE
#define NH_CMDHELPFILE	"cmdhelp"	/* file telling what commands do */
#define NH_CMDHELPAREA	FILE_AREA_SHARE
#define NH_HISTORY		"history"	/* a file giving nethack's history */
#define NH_HISTORY_AREA	FILE_AREA_SHARE
#define NH_LICENSE		"license"	/* file with license information */
#define NH_LICENSE_AREA	FILE_AREA_DOC
#define NH_OPTIONFILE	"opthelp"	/* a file explaining runtime options */
#define NH_OPTIONAREA	FILE_AREA_SHARE
#define NH_OPTIONS_USED	"options"	/* compile-time options, for #version */
#define NH_OPTIONS_USED_AREA FILE_AREA_SHARE
#ifdef SHORT_FILENAMES
# define NH_GUIDEBOOK       "guideboo.txt"        /* Nethack Guidebook*/
#else
#define NH_GUIDEBOOK       "Guidebook.txt"       /* Nethack Guidebook*/
#endif
#define NH_GUIDEBOOK_AREA	FILE_AREA_DOC

#define LEV_EXT	".lev"		/* extension for special level files */


/* Assorted definitions that may depend on selections in config.h. */

/*
 * for DUMB preprocessor and compiler, e.g., cpp and pcc supplied
 * with Microport SysV/AT, which have small symbol tables;
 * DUMB if needed is defined in CFLAGS
 */
#ifdef DUMB
#ifdef BITFIELDS
#undef BITFIELDS
#endif
#ifndef STUPID
#define STUPID
#endif
#endif	/* DUMB */

/*
 * type xchar: small integers in the range 0 - 127, usually coordinates
 * although they are nonnegative they must not be declared unsigned
 * since otherwise comparisons with signed quantities are done incorrectly
 */
typedef schar	xchar;
#ifndef SKIP_BOOLEAN
typedef xchar	boolean;		/* 0 or 1 */
#endif

#ifndef TRUE		/* defined in some systems' native include files */
#define TRUE	((boolean)1)
#define FALSE	((boolean)0)
#endif

#ifndef STRNCMPI
# if !defined(__SASC_60) && !defined(__MINGW32__) /* SAS/C already shifts to stricmp */
#  define strcmpi(a,b) strncmpi((a),(b),-1)
# endif
#endif

/* comment out to test effects of each #define -- these will probably
 * disappear eventually
 */
#ifdef INTERNAL_COMP
# define RLECOMP	/* run-length compression of levl array - JLee */
# define ZEROCOMP	/* zero-run compression of everything - Olaf Seibert */
#endif

/* #define SPECIALIZATION */	/* do "specialized" version of new topology */


#ifdef BITFIELDS
#define Bitfield(x,n)	unsigned x:n
#else
#define Bitfield(x,n)	uchar x
#endif

#ifdef UNWIDENED_PROTOTYPES
# define CHAR_P char
# define SCHAR_P schar
# define UCHAR_P uchar
# define XCHAR_P xchar
# define SHORT_P short
#ifndef SKIP_BOOLEAN
# define BOOLEAN_P boolean
#endif
# define ALIGNTYP_P aligntyp
#else
# ifdef WIDENED_PROTOTYPES
#  define CHAR_P int
#  define SCHAR_P int
#  define UCHAR_P int
#  define XCHAR_P int
#  define SHORT_P int
#  define BOOLEAN_P int
#  define ALIGNTYP_P int
# endif
#endif
#if defined(ULTRIX_PROTO) && !defined(__STDC__)
/* The ultrix 2.0 and 2.1 compilers (on Ultrix 4.0 and 4.2 respectively) can't
 * handle "struct obj *" constructs in prototypes.  Their bugs are different,
 * but both seem to work if we put "void*" in the prototype instead.  This
 * gives us minimal prototype checking but avoids the compiler bugs.
 *
 * OBJ_P and MONST_P should _only_ be used for declaring function pointers.
 */
#define OBJ_P void*
#define MONST_P void*
#else
#define OBJ_P struct obj*
#define MONST_P struct monst*
#endif

#define SIZE(x)	(int)(sizeof(x) / sizeof(x[0]))


/* A limit for some NetHack int variables.  It need not, and for comparable
 * scoring should not, depend on the actual limit on integers for a
 * particular machine, although it is set to the minimum required maximum
 * signed integer for C (2^15 -1).
 */
#define LARGEST_INT	32767


#ifdef REDO
#define Getchar pgetchar
#endif


#include "coord.h"
/*
 * Automatic inclusions for the subsidiary files.
 * Please don't change the order.  It does matter.
 */

#ifdef VMS
#include "vmsconf.h"
#endif

#ifdef UNIX
#include "unixconf.h"
#endif

#ifdef OS2
#include "os2conf.h"
#endif

#ifdef MSDOS
#include "pcconf.h"
#endif

#ifdef TOS
#include "tosconf.h"
#endif

#ifdef AMIGA
#include "amiconf.h"
#endif

#ifdef MAC
#include "macconf.h"
#endif

#ifdef __BEOS__
#include "beconf.h"
#endif

#ifdef WIN32
#ifdef WIN_CE
#include "wceconf.h"
#else
#include "ntconf.h"
#endif
#endif

#ifndef FILE_AREAS

#define fopen_datafile_area(area, filename, mode, use_spfx) \
 		fopen_datafile(filename, mode, use_spfx)
#define lock_file_area(area, filename, prefix, retryct) \
 		lock_file(filename, prefix, retryct)
#define unlock_file_area(area, filename) unlock_file(filename)
#define dlb_fopen_area(area, name, mode) dlb_fopen(name, mode)

/*
 * ALI
 *
 * By defining these, functions can pass them around even though they're
 * not actually used. This can make the code easier to read at the cost
 * of some efficiency. Given the high overhead of dealing with files anyway,
 * this is often a good trade-off.
 */

#define FILE_AREA_VAR		NULL
#define FILE_AREA_SAVE		NULL
#define FILE_AREA_LEVL		NULL
#define FILE_AREA_BONES		NULL
#define FILE_AREA_SHARE		NULL
#define FILE_AREA_UNSHARE	NULL

#endif

/* Include Android configuration file. /FF */
#ifdef ANDROID
#include "androidconf.h"
#endif

/* Displayable name of this port; don't redefine if defined in *conf.h */
#ifndef PORT_ID
# ifdef AMIGA
#  define PORT_ID	"Amiga"
# endif
# ifdef MAC
#  define PORT_ID	"Mac"
#  if 0
#  ifdef MAC_MPW_PPC
#   define PORT_SUB_ID "PPC"
#  else
#   ifdef MAC_MPW_68K
#    define PORT_SUB_ID "68K"
#   endif
#  endif
#  endif
# endif
# ifdef MSDOS
#  ifdef PC9800
#  define PORT_ID	"PC-9800"
#  else
#  define PORT_ID	"PC"
#  endif
#  ifdef DJGPP
#  define PORT_SUB_ID	"djgpp"
#  else
#   ifdef OVERLAY
#  define PORT_SUB_ID	"overlaid"
#   else
#  define PORT_SUB_ID	"non-overlaid"
#   endif
#  endif
# endif
# ifdef OS2
#  define PORT_ID	"OS/2"
# endif
# ifdef TOS
#  define PORT_ID	"ST"
# endif
# ifdef UNIX
#  define PORT_ID	"Unix"
# endif
# ifdef VMS
#  define PORT_ID	"VMS"
# endif
# ifdef WIN32
#  define PORT_ID	"Windows"
#  ifndef PORT_SUB_ID
#   if defined(MSWIN_GRAPHICS) || defined(GTK_GRAPHICS)
#    define PORT_SUB_ID	"graphical"
#   else
#    define PORT_SUB_ID	"tty"
#   endif
#  endif
# endif
#endif

#if defined(MICRO)
#if !defined(AMIGA) && !defined(TOS) && !defined(OS2_HPFS)
#define SHORT_FILENAMES		/* filenames are 8.3 */
#endif
#endif

#ifdef VMS
/* vms_exit() (sys/vms/vmsmisc.c) expects the non-VMS EXIT_xxx values below.
 * these definitions allow all systems to be treated uniformly, provided
 * main() routines do not terminate with return(), whose value is not
 * so massaged.
 */
# ifdef EXIT_SUCCESS
#  undef EXIT_SUCCESS
# endif
# ifdef EXIT_FAILURE
#  undef EXIT_FAILURE
# endif
#endif

#ifndef EXIT_SUCCESS
# define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
# define EXIT_FAILURE 1
#endif

#if defined(X11_GRAPHICS) || defined(QT_GRAPHICS) || defined(GNOME_GRAPHICS) || defined(MSWIN_GRAPHICS)
# ifndef USE_TILES
#  define USE_TILES		/* glyph2tile[] will be available */
# endif
#endif
#if defined(AMII_GRAPHICS) || defined(GEM_GRAPHICS) || defined(GTK_GRAPHICS)
# ifndef USE_TILES
#  define USE_TILES
# endif
#endif
#if defined(GL_GRAPHICS) || defined(SDL_GRAPHICS)
# ifndef USE_TILES
#  define USE_TILES
# endif
#endif

#define Sprintf  (void) sprintf
#define Strcat   (void) strcat
#define Strcpy   (void) strcpy
#ifdef NEED_VARARGS
#define Vprintf  (void) vprintf
#define Vfprintf (void) vfprintf
#define Vsprintf (void) vsprintf
#endif


/* primitive memory leak debugging; see alloc.c */
#ifdef MONITOR_HEAP
extern long *FDECL(nhalloc, (unsigned int,const char *,int));
extern void FDECL(nhfree, (genericptr_t,const char *,int));
#ifdef INTERNAL_MALLOC
extern void FDECL(monitor_heap_push, (const char *, int));
extern unsigned long FDECL(monitor_heap_pop, (const char *, int, unsigned long));
extern void FDECL(monitor_heap_set_subid, (const char *, int ));
extern size_t NDECL(monitor_heap_getmem);
extern boolean FDECL(monitor_heap_trace, (boolean flag));
extern void NDECL(monitor_heap_mark);
#endif
# ifndef __FILE__
#  define __FILE__ ""
# endif
# ifndef __LINE__
#  define __LINE__ 0
# endif
# define alloc(a) nhalloc(a,__FILE__,(int)__LINE__)
# define free(a) nhfree(a,__FILE__,(int)__LINE__)
#else	/* !MONITOR_HEAP */
extern long *FDECL(alloc, (unsigned int));		/* alloc.c */
#endif

/* Used for consistency checks of various data files; declare it here so
   that utility programs which include config.h but not hack.h can see it. */
struct version_info {
	unsigned long	incarnation;	/* actual version number */
	unsigned long	feature_set;	/* bitmask of config settings */
	unsigned long	entity_count;	/* # of monsters and objects */
	unsigned long	struct_sizes;	/* size of key structs */
};

/*
 * Configurable internal parameters.
 *
 * Please be very careful if you are going to change one of these.  Any
 * changes in these parameters, unless properly done, can render the
 * executable inoperative.
 */

/* size of terminal screen is (at least) (ROWNO+3) by COLNO */
#define COLNO	80
#define ROWNO	21

#define MAXNROFROOMS	40	/* max number of rooms per level */
#define MAX_SUBROOMS	24	/* max # of subrooms in a given room */
#define DOORMAX		120	/* max number of doors per level */

#define BUFSZ		256	/* for getlin buffers */
#define QBUFSZ		128	/* for building question text */
#define TBUFSZ		300	/* toplines[] buffer max msg: 3 81char names */
				/* plus longest prefix plus a few extra words */

#define PL_NSIZ		32	/* name of player, ghost, shopkeeper */
#define PL_CSIZ		32	/* sizeof pl_character */
#define PL_FSIZ		32	/* fruit name */
#define PL_PSIZ		63	/* player-given names for pets, other
				 * monsters, objects */

#define MAXDUNGEON	32	/* current maximum number of dungeons */
#define MAXLEVEL	50	/* max number of levels in one dungeon */
#define MAXSTAIRS	1	/* max # of special stairways in a dungeon */
#define ALIGNWEIGHT	10	/* generation weight of alignment */

#define MAXULEV		30	/* max character experience level */

#define MAXMONNO	120	/* extinct monst after this number created */
#define MHPMAX		500	/* maximum monster hp */

#endif /* GLOBAL_H */
