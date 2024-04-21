/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/tpcas.y"


#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "tree.h"
int yylex(void);
void yyerror(char * msg);
extern int lineno;
extern int ch;
Node * node = NULL;


#line 85 "obj/tpcas.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "tpcas.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TYPE = 3,                       /* TYPE  */
  YYSYMBOL_VOID = 4,                       /* VOID  */
  YYSYMBOL_IF = 5,                         /* IF  */
  YYSYMBOL_ELSE = 6,                       /* ELSE  */
  YYSYMBOL_WHILE = 7,                      /* WHILE  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_OR = 9,                         /* OR  */
  YYSYMBOL_AND = 10,                       /* AND  */
  YYSYMBOL_CHARACTER = 11,                 /* CHARACTER  */
  YYSYMBOL_ADDSUB = 12,                    /* ADDSUB  */
  YYSYMBOL_DIVSTAR = 13,                   /* DIVSTAR  */
  YYSYMBOL_IDENT = 14,                     /* IDENT  */
  YYSYMBOL_ORDER = 15,                     /* ORDER  */
  YYSYMBOL_EQ = 16,                        /* EQ  */
  YYSYMBOL_NUM = 17,                       /* NUM  */
  YYSYMBOL_18_ = 18,                       /* ';'  */
  YYSYMBOL_19_ = 19,                       /* ','  */
  YYSYMBOL_20_ = 20,                       /* '['  */
  YYSYMBOL_21_ = 21,                       /* ']'  */
  YYSYMBOL_22_ = 22,                       /* '('  */
  YYSYMBOL_23_ = 23,                       /* ')'  */
  YYSYMBOL_24_ = 24,                       /* '{'  */
  YYSYMBOL_25_ = 25,                       /* '}'  */
  YYSYMBOL_26_ = 26,                       /* '='  */
  YYSYMBOL_27_ = 27,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 28,                  /* $accept  */
  YYSYMBOL_Prog = 29,                      /* Prog  */
  YYSYMBOL_DeclVars = 30,                  /* DeclVars  */
  YYSYMBOL_Declarateurs = 31,              /* Declarateurs  */
  YYSYMBOL_DeclFoncts = 32,                /* DeclFoncts  */
  YYSYMBOL_DeclFonct = 33,                 /* DeclFonct  */
  YYSYMBOL_EnTeteFonct = 34,               /* EnTeteFonct  */
  YYSYMBOL_Parametres = 35,                /* Parametres  */
  YYSYMBOL_ListTypVar = 36,                /* ListTypVar  */
  YYSYMBOL_Corps = 37,                     /* Corps  */
  YYSYMBOL_SuiteInstr = 38,                /* SuiteInstr  */
  YYSYMBOL_Instr = 39,                     /* Instr  */
  YYSYMBOL_Exp = 40,                       /* Exp  */
  YYSYMBOL_TB = 41,                        /* TB  */
  YYSYMBOL_FB = 42,                        /* FB  */
  YYSYMBOL_M = 43,                         /* M  */
  YYSYMBOL_E = 44,                         /* E  */
  YYSYMBOL_T = 45,                         /* T  */
  YYSYMBOL_F = 46,                         /* F  */
  YYSYMBOL_LValue = 47,                    /* LValue  */
  YYSYMBOL_Arguments = 48,                 /* Arguments  */
  YYSYMBOL_ListExp = 49                    /* ListExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   148

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  28
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  117

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   272


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    27,     2,     2,     2,     2,     2,     2,
      22,    23,     2,     2,    19,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    18,
       2,    26,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    20,     2,    21,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    24,     2,    25,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    31,    31,    42,    56,    61,    67,    71,    80,    91,
      95,   100,   107,   117,   129,   132,   137,   146,   153,   164,
     174,   181,   191,   196,   202,   208,   215,   221,   228,   233,
     237,   240,   244,   250,   254,   260,   264,   270,   274,   280,
     284,   290,   294,   300,   304,   309,   313,   316,   320,   324,
     327,   338,   344,   355,   358,   363,   367
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "TYPE", "VOID", "IF",
  "ELSE", "WHILE", "RETURN", "OR", "AND", "CHARACTER", "ADDSUB", "DIVSTAR",
  "IDENT", "ORDER", "EQ", "NUM", "';'", "','", "'['", "']'", "'('", "')'",
  "'{'", "'}'", "'='", "'!'", "$accept", "Prog", "DeclVars",
  "Declarateurs", "DeclFoncts", "DeclFonct", "EnTeteFonct", "Parametres",
  "ListTypVar", "Corps", "SuiteInstr", "Instr", "Exp", "TB", "FB", "M",
  "E", "T", "F", "LValue", "Arguments", "ListExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-92)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -92,     3,    66,   -92,    -4,    -1,    74,   -92,    -3,    32,
      37,    15,    67,   -92,   -92,   -92,    65,    76,   -92,    69,
      76,    63,    83,    68,    73,   -92,    70,    71,    72,    75,
      77,     1,   -92,    79,   -92,    85,    78,   -92,    80,    81,
      82,    31,    52,   -92,   -92,   -92,   -92,    84,    86,    87,
      88,    49,    49,   -92,    49,    53,   -92,   -92,    49,    49,
      11,    92,    89,    91,    96,    98,   -92,   -92,    49,    49,
       9,    49,   -92,    93,   -92,    13,    21,   -92,    49,    23,
     -92,    49,   -92,    49,    49,    49,    49,    49,    41,   103,
      94,    95,   -92,    50,    97,    33,    33,    99,   -92,    92,
      89,    91,    96,    98,   -92,   -92,   101,    49,   -92,   -92,
      90,   -92,   -92,   -92,   103,    33,   -92
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     2,    10,     0,     6,
       0,     0,     0,     9,     4,    11,     0,     0,     3,     0,
       0,     0,    22,     0,     0,    14,     0,    15,     5,     0,
       0,     0,     8,    17,    12,     0,     0,    13,     6,     0,
       0,     0,    51,    31,    22,    20,    21,     0,     0,     0,
       0,     0,     0,    48,     0,    51,    47,    29,     0,     0,
       0,    33,    35,    37,    39,    41,    43,    49,     0,    54,
       0,     0,    19,    16,     7,     0,     0,    44,    54,     0,
      45,     0,    28,     0,     0,     0,     0,     0,     0,    56,
       0,    53,    30,     0,     0,     0,     0,     0,    46,    32,
      34,    36,    38,    40,    42,    52,     0,     0,    23,    18,
      24,    26,    50,    27,    55,     0,    25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -92,   -92,   102,   -92,   -92,   109,   -92,   100,   -92,   -92,
     104,   -91,   -40,    16,    38,    10,    39,    40,   -52,   -31,
      45,   -92
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     2,    10,     6,     7,     8,    26,    27,    15,
      31,    46,    89,    61,    62,    63,    64,    65,    66,    67,
      90,    91
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      47,    60,    77,     3,   110,   111,    39,    80,    40,    41,
       9,    75,    76,    11,    39,    42,    40,    41,    79,    43,
      81,    14,    81,    42,   116,    44,    45,    43,    88,    82,
      81,    93,    81,    44,    92,   104,    95,    20,    39,    47,
      40,    41,    53,    54,    96,    55,    98,    42,    56,    57,
      81,    43,    16,    58,    17,    18,    19,    44,    59,    81,
      53,    54,   105,    55,    47,    47,    56,   114,   108,     4,
       5,    58,    68,    68,    69,    78,    59,    12,     5,    24,
      25,    21,    23,    28,    47,    17,    30,    33,    49,    32,
      35,    38,    36,    34,   101,    50,   115,    99,    37,    48,
      16,    73,    83,    51,    52,    84,    85,    72,    86,    74,
      71,    87,    81,    94,   107,    13,    22,   106,   109,   113,
      29,   100,   112,    97,   102,     0,   103,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    70
};

static const yytype_int8 yycheck[] =
{
      31,    41,    54,     0,    95,    96,     5,    59,     7,     8,
      14,    51,    52,    14,     5,    14,     7,     8,    58,    18,
       9,    24,     9,    14,   115,    24,    25,    18,    68,    18,
       9,    71,     9,    24,    25,    87,    23,    22,     5,    70,
       7,     8,    11,    12,    23,    14,    23,    14,    17,    18,
       9,    18,    20,    22,    22,    18,    19,    24,    27,     9,
      11,    12,    21,    14,    95,    96,    17,   107,    18,     3,
       4,    22,    20,    20,    22,    22,    27,     3,     4,     3,
       4,    14,    17,    14,   115,    22,     3,    14,     3,    21,
      19,    14,    20,    23,    84,    17,     6,    81,    23,    20,
      20,    14,    10,    22,    22,    16,    15,    21,    12,    21,
      26,    13,     9,    20,    19,     6,    14,    23,    21,    18,
      20,    83,    23,    78,    85,    -1,    86,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    29,    30,     0,     3,     4,    32,    33,    34,    14,
      31,    14,     3,    33,    24,    37,    20,    22,    18,    19,
      22,    14,    30,    17,     3,     4,    35,    36,    14,    35,
       3,    38,    21,    14,    23,    19,    20,    23,    14,     5,
       7,     8,    14,    18,    24,    25,    39,    47,    20,     3,
      17,    22,    22,    11,    12,    14,    17,    18,    22,    27,
      40,    41,    42,    43,    44,    45,    46,    47,    20,    22,
      38,    26,    21,    14,    21,    40,    40,    46,    22,    40,
      46,     9,    18,    10,    16,    15,    12,    13,    40,    40,
      48,    49,    25,    40,    20,    23,    23,    48,    23,    41,
      42,    43,    44,    45,    46,    21,    23,    19,    18,    21,
      39,    39,    23,    18,    40,     6,    39
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    28,    29,    30,    30,    31,    31,    31,    31,    32,
      32,    33,    34,    34,    35,    35,    36,    36,    36,    36,
      37,    38,    38,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    40,    40,    41,    41,    42,    42,    43,    43,
      44,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    47,    48,    48,    49,    49
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     4,     0,     3,     1,     6,     4,     2,
       1,     2,     5,     5,     1,     1,     4,     2,     6,     4,
       4,     2,     0,     4,     5,     7,     5,     5,     3,     2,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     2,     2,     3,     1,     1,     1,
       4,     1,     4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* Prog: DeclVars DeclFoncts  */
#line 31 "src/tpcas.y"
                           {
    node = makeNode(Prog);
    Node * declV = makeNode(Global_vars);
    Node * declFuncs = makeNode(Functions);
    addChild(node, declV);
    addChild(declV, (yyvsp[-1].node));
    addChild(node, declFuncs);
    addChild(declFuncs, (yyvsp[0].node));
    }
#line 1202 "obj/tpcas.c"
    break;

  case 3: /* DeclVars: DeclVars TYPE Declarateurs ';'  */
#line 42 "src/tpcas.y"
                                      {
        if((yyvsp[-3].node)){
            (yyval.node) = (yyvsp[-3].node);
            Node * tmp = makeNode(Type);
            tmp->ident = strdup((yyvsp[-2].ident));
            addChild(tmp, (yyvsp[-1].node));
            addSibling((yyval.node), tmp);
        }
        else{
            (yyval.node) = makeNode(Type);
            (yyval.node)->ident = strdup((yyvsp[-2].ident));
            addChild((yyval.node), (yyvsp[-1].node));
        }
    }
#line 1221 "obj/tpcas.c"
    break;

  case 4: /* DeclVars: %empty  */
#line 56 "src/tpcas.y"
      {
        (yyval.node) = NULL;
        }
#line 1229 "obj/tpcas.c"
    break;

  case 5: /* Declarateurs: Declarateurs ',' IDENT  */
#line 61 "src/tpcas.y"
                              {
        (yyval.node) = (yyvsp[-2].node);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[0].ident));
        addSibling((yyval.node), tmp);
        }
#line 1240 "obj/tpcas.c"
    break;

  case 6: /* Declarateurs: IDENT  */
#line 67 "src/tpcas.y"
             {
        (yyval.node) = makeNode(Ident);
        (yyval.node)->ident = strdup((yyvsp[0].ident));
        }
#line 1249 "obj/tpcas.c"
    break;

  case 7: /* Declarateurs: Declarateurs ',' IDENT '[' NUM ']'  */
#line 71 "src/tpcas.y"
                                          {
        (yyval.node) = (yyvsp[-5].node);
        Node * tmp1 = makeNode(Ident);
        tmp1->ident = strdup((yyvsp[-3].ident));
        addChild((yyval.node), tmp1);
        Node * num = makeNode(Num);
        num->num = (yyvsp[-1].num);
        addChild((yyval.node), num);
        }
#line 1263 "obj/tpcas.c"
    break;

  case 8: /* Declarateurs: IDENT '[' NUM ']'  */
#line 80 "src/tpcas.y"
                         {
        (yyval.node) = makeNode(Array);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[-3].ident));
        addChild((yyval.node), tmp);
        Node * num = makeNode(Num);
        num->num = (yyvsp[-1].num);
        addChild(tmp, num);
        }
#line 1277 "obj/tpcas.c"
    break;

  case 9: /* DeclFoncts: DeclFoncts DeclFonct  */
#line 91 "src/tpcas.y"
                            {
        (yyval.node) = (yyvsp[-1].node);
        addSibling((yyval.node), (yyvsp[0].node));
        }
#line 1286 "obj/tpcas.c"
    break;

  case 10: /* DeclFoncts: DeclFonct  */
#line 95 "src/tpcas.y"
                 {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1294 "obj/tpcas.c"
    break;

  case 11: /* DeclFonct: EnTeteFonct Corps  */
#line 100 "src/tpcas.y"
                         {
        (yyval.node) = makeNode(Function);
        addChild((yyval.node), (yyvsp[-1].node));
        addChild((yyval.node), (yyvsp[0].node));
        }
#line 1304 "obj/tpcas.c"
    break;

  case 12: /* EnTeteFonct: TYPE IDENT '(' Parametres ')'  */
#line 107 "src/tpcas.y"
                                     {
        (yyval.node) = makeNode(Type);
        (yyval.node)->ident = strdup((yyvsp[-4].ident));
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[-3].ident));
        addSibling((yyval.node), tmp);
        Node *tmp2 = makeNode(Parameters);
        addSibling((yyval.node), tmp2);
        addChild(tmp2, (yyvsp[-1].node));
        }
#line 1319 "obj/tpcas.c"
    break;

  case 13: /* EnTeteFonct: VOID IDENT '(' Parametres ')'  */
#line 117 "src/tpcas.y"
                                     {
        (yyval.node) = makeNode(Void);
        (yyval.node)->ident = strdup((yyvsp[-4].ident));
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[-3].ident));
        addSibling((yyval.node), tmp);
        Node *tmp2 = makeNode(Parameters);
        addSibling((yyval.node), tmp2);
        addChild(tmp2, (yyvsp[-1].node));
        }
#line 1334 "obj/tpcas.c"
    break;

  case 14: /* Parametres: VOID  */
#line 129 "src/tpcas.y"
            {
        (yyval.node) = makeNode(Void);
        }
#line 1342 "obj/tpcas.c"
    break;

  case 15: /* Parametres: ListTypVar  */
#line 132 "src/tpcas.y"
                  {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1350 "obj/tpcas.c"
    break;

  case 16: /* ListTypVar: ListTypVar ',' TYPE IDENT  */
#line 137 "src/tpcas.y"
                                 {
        (yyval.node) = (yyvsp[-3].node); 
        Node * tmp1 = makeNode(Type); 
        tmp1->ident = strdup((yyvsp[-1].ident));
        Node * tmp2 = makeNode(Ident); 
        tmp2->ident = strdup((yyvsp[0].ident));
        addChild(tmp1, tmp2); 
        addSibling((yyval.node), tmp1);
        }
#line 1364 "obj/tpcas.c"
    break;

  case 17: /* ListTypVar: TYPE IDENT  */
#line 146 "src/tpcas.y"
                  {
        (yyval.node) = makeNode(Type);
        (yyval.node)->ident = strdup((yyvsp[-1].ident));
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[0].ident));
        addChild((yyval.node), tmp);
        }
#line 1376 "obj/tpcas.c"
    break;

  case 18: /* ListTypVar: ListTypVar ',' TYPE IDENT '[' ']'  */
#line 153 "src/tpcas.y"
                                         {
        (yyval.node) = (yyvsp[-5].node);
        Node * arr = makeNode(Array);
        Node * tmp1 = makeNode(Type);
        tmp1->ident = strdup((yyvsp[-3].ident));
        Node * tmp2 = makeNode(Ident);
        tmp2->ident = strdup((yyvsp[-2].ident));
        addChild(tmp1, tmp2);
        addChild(arr, tmp1);
        addSibling((yyval.node), arr);
        }
#line 1392 "obj/tpcas.c"
    break;

  case 19: /* ListTypVar: TYPE IDENT '[' ']'  */
#line 164 "src/tpcas.y"
                          {
        (yyval.node) = makeNode(Array);
        Node * tmp1 = makeNode(Type);
        (yyval.node)->ident = strdup((yyvsp[-3].ident));
        Node * tmp2 = makeNode(Ident);
        tmp2->ident = strdup((yyvsp[-2].ident));
        addChild(tmp1, tmp2);
        addChild((yyval.node), tmp1);
        }
#line 1406 "obj/tpcas.c"
    break;

  case 20: /* Corps: '{' DeclVars SuiteInstr '}'  */
#line 174 "src/tpcas.y"
                                   {
    (yyval.node) = makeNode(Corps);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[-1].node));
    }
#line 1416 "obj/tpcas.c"
    break;

  case 21: /* SuiteInstr: SuiteInstr Instr  */
#line 181 "src/tpcas.y"
                        {
        if((yyvsp[-1].node)){
            (yyval.node) = (yyvsp[-1].node);
            addChild((yyval.node), (yyvsp[0].node));
            }
        else{
            (yyval.node) = makeNode(instructions);
            addChild((yyval.node), (yyvsp[0].node));
            }
        }
#line 1431 "obj/tpcas.c"
    break;

  case 22: /* SuiteInstr: %empty  */
#line 191 "src/tpcas.y"
      {
        (yyval.node) = NULL;
        }
#line 1439 "obj/tpcas.c"
    break;

  case 23: /* Instr: LValue '=' Exp ';'  */
#line 196 "src/tpcas.y"
                          {
        (yyval.node) = makeNode(Equals);
        (yyval.node)->ident = "=";
        addChild((yyval.node), (yyvsp[-3].node));
        addChild((yyval.node), (yyvsp[-1].node));
        }
#line 1450 "obj/tpcas.c"
    break;

  case 24: /* Instr: IF '(' Exp ')' Instr  */
#line 202 "src/tpcas.y"
                            {
        (yyval.node) = makeNode(If);
        (yyval.node)->ident = strdup((yyvsp[-4].ident));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
        }
#line 1461 "obj/tpcas.c"
    break;

  case 25: /* Instr: IF '(' Exp ')' Instr ELSE Instr  */
#line 208 "src/tpcas.y"
                                       {
        (yyval.node) = makeNode(If);
        (yyval.node)->ident = strdup((yyvsp[-6].ident));
        addChild((yyval.node), (yyvsp[-4].node));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
        }
#line 1473 "obj/tpcas.c"
    break;

  case 26: /* Instr: WHILE '(' Exp ')' Instr  */
#line 215 "src/tpcas.y"
                               {
        (yyval.node) = makeNode(While);
        (yyval.node)->ident = strdup((yyvsp[-4].ident));
        addChild((yyval.node), (yyvsp[-2].node));
        addChild((yyval.node), (yyvsp[0].node));
        }
#line 1484 "obj/tpcas.c"
    break;

  case 27: /* Instr: IDENT '(' Arguments ')' ';'  */
#line 221 "src/tpcas.y"
                                    {
        (yyval.node) = makeNode(Function);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[-4].ident));
        addChild(tmp, (yyvsp[-2].node));
        addChild((yyval.node), tmp);
        }
#line 1496 "obj/tpcas.c"
    break;

  case 28: /* Instr: RETURN Exp ';'  */
#line 228 "src/tpcas.y"
                      {
        (yyval.node) = makeNode(Return);
        (yyval.node)->ident = strdup((yyvsp[-2].ident));
        addChild((yyval.node), (yyvsp[-1].node));
        }
#line 1506 "obj/tpcas.c"
    break;

  case 29: /* Instr: RETURN ';'  */
#line 233 "src/tpcas.y"
                  {
        (yyval.node) = makeNode(Return);
        (yyval.node)->ident = strdup((yyvsp[-1].ident));
        }
#line 1515 "obj/tpcas.c"
    break;

  case 30: /* Instr: '{' SuiteInstr '}'  */
#line 237 "src/tpcas.y"
                          {
        (yyval.node) = (yyvsp[-1].node);
        }
#line 1523 "obj/tpcas.c"
    break;

  case 31: /* Instr: ';'  */
#line 240 "src/tpcas.y"
           {
        (yyval.node) = makeNode(None);
        }
#line 1531 "obj/tpcas.c"
    break;

  case 32: /* Exp: Exp OR TB  */
#line 244 "src/tpcas.y"
                 {
    (yyval.node) = makeNode(Or);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[0].node));
    (yyval.node)->ident = strdup((yyvsp[-1].ident));
    }
#line 1542 "obj/tpcas.c"
    break;

  case 33: /* Exp: TB  */
#line 250 "src/tpcas.y"
          {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1550 "obj/tpcas.c"
    break;

  case 34: /* TB: TB AND FB  */
#line 254 "src/tpcas.y"
                 {
    (yyval.node) = makeNode(And);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[0].node));
    (yyval.node)->ident = strdup((yyvsp[-1].ident));
    }
#line 1561 "obj/tpcas.c"
    break;

  case 35: /* TB: FB  */
#line 260 "src/tpcas.y"
          {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1569 "obj/tpcas.c"
    break;

  case 36: /* FB: FB EQ M  */
#line 264 "src/tpcas.y"
               {
    (yyval.node) = makeNode(Eq);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[0].node));
    (yyval.node)->ident = strdup((yyvsp[-1].ident));
    }
#line 1580 "obj/tpcas.c"
    break;

  case 37: /* FB: M  */
#line 270 "src/tpcas.y"
         {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1588 "obj/tpcas.c"
    break;

  case 38: /* M: M ORDER E  */
#line 274 "src/tpcas.y"
                 {
    (yyval.node) = makeNode(Order);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[0].node));
    (yyval.node)->ident = strdup((yyvsp[-1].ident));
    }
#line 1599 "obj/tpcas.c"
    break;

  case 39: /* M: E  */
#line 280 "src/tpcas.y"
         {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1607 "obj/tpcas.c"
    break;

  case 40: /* E: E ADDSUB T  */
#line 284 "src/tpcas.y"
                  {
    (yyval.node) = makeNode(Addsub);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[0].node));
    (yyval.node)->ident = strdup((yyvsp[-1].ident));
    }
#line 1618 "obj/tpcas.c"
    break;

  case 41: /* E: T  */
#line 290 "src/tpcas.y"
         {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1626 "obj/tpcas.c"
    break;

  case 42: /* T: T DIVSTAR F  */
#line 294 "src/tpcas.y"
                   {
    (yyval.node) = makeNode(Divstar);
    addChild((yyval.node), (yyvsp[-2].node));
    addChild((yyval.node), (yyvsp[0].node));
    (yyval.node)->ident = strdup((yyvsp[-1].ident));
    }
#line 1637 "obj/tpcas.c"
    break;

  case 43: /* T: F  */
#line 300 "src/tpcas.y"
         {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1645 "obj/tpcas.c"
    break;

  case 44: /* F: ADDSUB F  */
#line 304 "src/tpcas.y"
                {
        (yyval.node) = makeNode(Addsub);
        addChild((yyval.node), (yyvsp[0].node));
        (yyval.node)->ident = strdup((yyvsp[-1].ident));
        }
#line 1655 "obj/tpcas.c"
    break;

  case 45: /* F: '!' F  */
#line 309 "src/tpcas.y"
             {
        (yyval.node) = makeNode(Not);
        addChild((yyval.node), (yyvsp[0].node));
        }
#line 1664 "obj/tpcas.c"
    break;

  case 46: /* F: '(' Exp ')'  */
#line 313 "src/tpcas.y"
                   {
        (yyval.node) = (yyvsp[-1].node);
        }
#line 1672 "obj/tpcas.c"
    break;

  case 47: /* F: NUM  */
#line 316 "src/tpcas.y"
           {
        (yyval.node) = makeNode(Num);
        (yyval.node)->num = (yyvsp[0].num);
        }
#line 1681 "obj/tpcas.c"
    break;

  case 48: /* F: CHARACTER  */
#line 320 "src/tpcas.y"
                 {
        (yyval.node) = makeNode(Character);
        (yyval.node)->ident = strdup((yyvsp[0].ident));
        }
#line 1690 "obj/tpcas.c"
    break;

  case 49: /* F: LValue  */
#line 324 "src/tpcas.y"
              {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1698 "obj/tpcas.c"
    break;

  case 50: /* F: IDENT '(' Arguments ')'  */
#line 327 "src/tpcas.y"
                                {
        (yyval.node) = makeNode(Function);
        Node * tmp = makeNode(Ident);
        Node * arg = makeNode(Parameters);
        tmp->ident = strdup((yyvsp[-3].ident));
        addChild(arg, (yyvsp[-1].node));
        addChild(tmp, arg);
        addChild((yyval.node), tmp);
        }
#line 1712 "obj/tpcas.c"
    break;

  case 51: /* LValue: IDENT  */
#line 338 "src/tpcas.y"
             {
        (yyval.node) = makeNode(Variable);
        Node * tmp = makeNode(Ident);
        tmp->ident = strdup((yyvsp[0].ident));
        addChild((yyval.node), tmp);
        }
#line 1723 "obj/tpcas.c"
    break;

  case 52: /* LValue: IDENT '[' Exp ']'  */
#line 344 "src/tpcas.y"
                         {
        (yyval.node) = makeNode(Variable);
        Node * tmp = makeNode(Array);
        addChild((yyval.node), tmp);
        Node * tmp2 = makeNode(Ident);
        tmp2->ident = strdup((yyvsp[-3].ident));
        addChild(tmp, tmp2);
        addChild(tmp2, (yyvsp[-1].node));
        }
#line 1737 "obj/tpcas.c"
    break;

  case 53: /* Arguments: ListExp  */
#line 355 "src/tpcas.y"
               {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1745 "obj/tpcas.c"
    break;

  case 54: /* Arguments: %empty  */
#line 358 "src/tpcas.y"
      {
        (yyval.node) = NULL;
        }
#line 1753 "obj/tpcas.c"
    break;

  case 55: /* ListExp: ListExp ',' Exp  */
#line 363 "src/tpcas.y"
                       {
        (yyval.node) = (yyvsp[-2].node);
        addSibling((yyval.node), (yyvsp[0].node));
        }
#line 1762 "obj/tpcas.c"
    break;

  case 56: /* ListExp: Exp  */
#line 367 "src/tpcas.y"
           {
        (yyval.node) = (yyvsp[0].node);
        }
#line 1770 "obj/tpcas.c"
    break;


#line 1774 "obj/tpcas.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 371 "src/tpcas.y"


void yyerror(char * s){
    fprintf(stderr, "%s : line %d, col %d\n", s, lineno, ch);
}
