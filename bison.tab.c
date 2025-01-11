
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "bison.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>

    extern int yylex(void);
    int yyerror(char* s);

    const int MAX = 100;
    const int MAX_FUN = 50;
    int varCount = 0;
    int funCount = 0;
    int conditionMatch = 0;
    int currentFun = 0;
    int currentParameter = 0;
    int functionRejected = 0;

    int maincase = 0,subcase = 0;
    double dmaincase = 0, dsubcase = 0;

    #define YYDEBUG 1
    #define UNIQUE 1
    #define DUPLICATE -1
    #define NUMBER  1
    #define FLOAT 2
    #define STRING 3

    typedef struct {
        char *name;
        int type;
        int length;
        int *ival;
        double *dval;
        char **sval;
        int is_array;
    } varStruct;
    varStruct *varptr;

    typedef struct {
        char *fname;
        varStruct *fptr;
        int var_cnt;
    } funStruct;
    funStruct *funcptr;

    void var_does_not_exist(char *name) {
        printf("variable \"%s\" doesn't exist.\n", name);
    }
    int check_unique(char *name) {
        for(int i = 0; i < varCount; ++i) {
            if(strcmp(varptr[i].name, name) == 0) {
                return DUPLICATE;
            }
        }
        return UNIQUE;
    } 

    
    int get_var_index(char *name) {
        for(int i = 0; i < varCount; ++i) {
            if(strcmp(varptr[i].name, name) == 0) {
                return i;
            }
        }
        return -1;
    }
    void store_value(char *n, int t, int l, int p, void *v, int is_Array) {
        varptr[p].name = n;
        varptr[p].type = t;
        varptr[p].length = l;
        varptr[p].is_array = is_Array;
        if(t == NUMBER) {
            int *value = (int *) v;
            varptr[p].ival = malloc(l * sizeof(int));
            for(int i = 0; i < l; ++i) {
                varptr[p].ival[i] = value[i];
            }
            printf("Variable name is: %s", varptr[p].name);
            printf(" and value is: %d\n", *varptr[p].ival);
        } else if(t == FLOAT) {
            double *value = (double *) v;
            varptr[p].dval = malloc(l * sizeof(double));
            for(int i = 0; i < l; ++i) {
                varptr[p].dval[i] = value[i];
            }
            printf("Variable name is: %s", varptr[p].name);
            printf(" and value is: %lf\n", *varptr[p].dval);
        } else if(t == STRING) {
            char **s = ((char**) v);
            varptr[p].sval = malloc(l * sizeof(char**));
            for(int i = 0; i < l; ++i) {
                varptr[p].sval[i] = s[i];
            }
            printf("Variable name is: %s", varptr[p].name);
            printf(" and value is: %s\n", *varptr[p].sval);
        }
    }
    void read_value(char *name) {
        int p = 0 ;
        printf("Scan Input for %s: ", name);
        int index = get_var_index(name);
        printf("index: %d\n", index);
        if (index == -1) {
            var_does_not_exist(name);
        } else {
            if(p >= varptr[index].length) {
                printf("Maximum Number of Variables Used.\n");
            } else {
                if (varptr[index].type == FLOAT) {
                    scanf("%lf", &varptr[index].dval[p]);
                } else if (varptr[index].type == NUMBER) {
                    scanf("%d", &varptr[index].ival[p]);
                    printf("%d\n", varptr[index].ival[p]);
                } else if(varptr[index].type == STRING) {
                    char str [1000];
                    scanf("%s", str);
                    varptr[index].sval[p] = str;
                }
            }
        }
    }
    void show_value(char *name) {
        int index = get_var_index(name);
        if(index == -1) {
            var_does_not_exist(name);
        } else {
            if(varptr[index].is_array) {
                //array print.
            } else {
                printf("Value of %s is: ", name);
                if(varptr[index].type == NUMBER) {
                    printf("%d\n", varptr[index].ival[0]);
                } else if(varptr[index].type == FLOAT) {
                    printf("%lf\n", varptr[index].dval[0]);
                } else if(varptr[index].type == STRING) {
                    printf("%s\n", varptr[index].sval[0]);
                }
            }
        }
    }

    void not_unique(char *name) {
        printf("variable \"%s\" already exists.\n", name);
    }

    
    
    int get_function_index(char *name){
        for(int i = 0; i < funCount; ++i) {
            if(strcmp(funcptr[i].fname, name) == 0) {
                return i;
            }
        }
        return -1;
    }
    unsigned long long factorial(int n) {
        if (n == 0 || n == 1) {
            return 1;
        } else {
            return n * factorial(n - 1);
        }
        return -1;
    }

    int prime(int n) {    
        if (n <= 1) {
            printf(" not Prime\n");
            return 0;
        } else {
            int is_prime = 1;  
            for (int i = 2; i <= n / 2; i++) {
                if (n % i == 0) {
                    is_prime = 0;
                    break;  
                }
            }
            if (is_prime) {
                printf(" prime\n");
                return 0;
            } else {
                printf(" not prime\n");
                return 1;
            }
        }
        
    }



/* Line 189 of yacc.c  */
#line 264 "bison.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     HEADER = 258,
     SCOM = 259,
     MCOM = 260,
     EOL = 261,
     VARIABLE = 262,
     ARROW = 263,
     INPUT = 264,
     PRINT = 265,
     INT_TYPE = 266,
     FLOAT_TYPE = 267,
     STRING_TYPE = 268,
     INT_VALUE = 269,
     FLOAT_VALUE = 270,
     STRING_VALUE = 271,
     ARR = 272,
     SWITCH = 273,
     CASE = 274,
     DEFAULT = 275,
     POW = 276,
     SIN = 277,
     COS = 278,
     TAN = 279,
     LOG10 = 280,
     LOG2 = 281,
     LN = 282,
     SQRT = 283,
     FACT = 284,
     PRIME = 285,
     ABS = 286,
     AND = 287,
     OR = 288,
     XOR = 289,
     NOT = 290,
     INC = 291,
     DEC = 292,
     LT = 293,
     GT = 294,
     EQ = 295,
     NE = 296,
     LE = 297,
     GE = 298,
     IF = 299,
     ELSIF = 300,
     ELSE = 301,
     FOR = 302,
     IN = 303,
     WHILE = 304,
     FUN = 305,
     CALL = 306,
     IFO = 307
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 193 "bison.y"

	int integer;
	double real;
	char *string;



/* Line 214 of yacc.c  */
#line 360 "bison.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 372 "bison.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   748

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  67
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  128
/* YYNRULES -- Number of states.  */
#define YYNSTATES  299

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    57,     2,     2,
      61,    62,    55,    53,    63,    54,     2,    56,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    66,     2,
       2,    60,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    58,     2,    59,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    64,     2,    65,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     8,     9,    12,    14,    18,    20,
      22,    25,    28,    31,    34,    36,    38,    40,    42,    45,
      47,    50,    53,    60,    67,    72,    77,    81,    83,    88,
      92,    94,   105,   107,   109,   111,   113,   114,   118,   120,
     123,   126,   132,   134,   138,   140,   142,   150,   158,   166,
     168,   171,   174,   179,   184,   188,   202,   210,   215,   220,
     225,   230,   235,   240,   244,   247,   254,   261,   262,   264,
     267,   269,   272,   274,   282,   287,   290,   293,   296,   300,
     302,   306,   308,   312,   314,   318,   320,   324,   326,   330,
     332,   336,   338,   342,   344,   346,   348,   351,   354,   357,
     360,   364,   368,   372,   376,   380,   384,   388,   392,   396,
     400,   404,   408,   412,   416,   420,   423,   426,   429,   433,
     438,   443,   448,   453,   458,   463,   468,   473,   478
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      68,     0,    -1,     3,    69,    -1,    69,    -1,    -1,    69,
      70,    -1,     6,    -1,    70,     6,    70,    -1,     4,    -1,
       5,    -1,    75,     6,    -1,    73,     6,    -1,    99,     6,
      -1,   106,     6,    -1,    93,    -1,    90,    -1,    91,    -1,
      77,    -1,    82,     6,    -1,    86,    -1,    71,     6,    -1,
      72,     6,    -1,    11,    17,     7,    58,    14,    59,    -1,
       7,    58,    14,    59,    60,   108,    -1,    10,    61,    74,
      62,    -1,    10,    61,    16,    62,    -1,    74,    63,     7,
      -1,     7,    -1,     9,    61,    76,    62,    -1,    76,    63,
       7,    -1,     7,    -1,    50,    79,    61,    80,    62,     8,
      78,    64,    69,    65,    -1,    11,    -1,    12,    -1,    13,
      -1,     7,    -1,    -1,    80,    63,    81,    -1,    81,    -1,
      11,     7,    -1,    12,     7,    -1,    51,    83,    61,    84,
      62,    -1,     7,    -1,    84,    63,    85,    -1,    85,    -1,
       7,    -1,    18,    61,    14,    62,    64,    87,    65,    -1,
      18,    61,    15,    62,    64,    87,    65,    -1,    18,    61,
       7,    62,    64,    87,    65,    -1,    88,    -1,    88,    89,
      -1,    88,    87,    -1,    19,    14,    66,    69,    -1,    19,
      15,    66,    69,    -1,    20,    66,    69,    -1,    47,     7,
      48,    58,   108,    63,   108,    63,   108,    59,    64,    69,
      65,    -1,    49,    61,    92,    62,    64,    69,    65,    -1,
       7,    36,    38,   108,    -1,     7,    36,    42,   108,    -1,
       7,    36,    41,   108,    -1,     7,    37,    39,   108,    -1,
       7,    37,    43,   108,    -1,     7,    37,    41,   108,    -1,
      44,    94,    95,    -1,    44,    94,    -1,    61,   108,    62,
      64,    70,    65,    -1,    61,   108,    62,    64,    93,    65,
      -1,    -1,    96,    -1,    96,    98,    -1,    98,    -1,    96,
      97,    -1,    97,    -1,    45,    61,   108,    62,    64,    70,
      65,    -1,    46,    64,    70,    65,    -1,    11,   104,    -1,
      12,   102,    -1,    13,   100,    -1,   100,    63,   101,    -1,
     101,    -1,     7,    60,    16,    -1,     7,    -1,   102,    63,
     103,    -1,   103,    -1,     7,    60,   108,    -1,     7,    -1,
     104,    63,   105,    -1,   105,    -1,     7,    60,   108,    -1,
       7,    -1,   106,    63,   107,    -1,   107,    -1,     7,    60,
     108,    -1,    14,    -1,    15,    -1,     7,    -1,    53,   108,
      -1,    54,   108,    -1,    36,   108,    -1,    37,   108,    -1,
     108,    53,   108,    -1,   108,    54,   108,    -1,   108,    55,
     108,    -1,   108,    56,   108,    -1,   108,    57,   108,    -1,
     108,    21,   108,    -1,   108,    40,   108,    -1,   108,    41,
     108,    -1,   108,    38,   108,    -1,   108,    39,   108,    -1,
     108,    42,   108,    -1,   108,    43,   108,    -1,   108,    32,
     108,    -1,   108,    33,   108,    -1,   108,    34,   108,    -1,
      35,   108,    -1,     7,    36,    -1,     7,    37,    -1,    61,
     108,    62,    -1,    22,    61,   108,    62,    -1,    23,    61,
     108,    62,    -1,    24,    61,   108,    62,    -1,    25,    61,
     108,    62,    -1,    26,    61,   108,    62,    -1,    27,    61,
     108,    62,    -1,    28,    61,   108,    62,    -1,    29,    61,
     108,    62,    -1,    30,    61,   108,    62,    -1,    31,    61,
     108,    62,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   219,   219,   220,   223,   224,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   246,   252,   258,   259,   263,   264,   268,   272,
     273,   276,   279,   280,   281,   285,   297,   298,   299,   303,
     312,   324,   334,   347,   348,   352,   367,   371,   375,   390,
     391,   392,   396,   408,   419,   425,   442,   449,   464,   479,
     494,   509,   524,   542,   543,   547,   557,   558,   559,   560,
     561,   565,   566,   569,   585,   596,   597,   598,   602,   603,
     606,   616,   623,   624,   627,   636,   643,   644,   648,   657,
     665,   666,   670,   683,   686,   689,   700,   701,   702,   703,
     704,   705,   706,   707,   708,   709,   710,   711,   712,   713,
     714,   715,   716,   717,   718,   719,   720,   733,   746,   747,
     748,   749,   750,   751,   752,   753,   754,   755,   756
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "HEADER", "SCOM", "MCOM", "EOL",
  "VARIABLE", "ARROW", "INPUT", "PRINT", "INT_TYPE", "FLOAT_TYPE",
  "STRING_TYPE", "INT_VALUE", "FLOAT_VALUE", "STRING_VALUE", "ARR",
  "SWITCH", "CASE", "DEFAULT", "POW", "SIN", "COS", "TAN", "LOG10", "LOG2",
  "LN", "SQRT", "FACT", "PRIME", "ABS", "AND", "OR", "XOR", "NOT", "INC",
  "DEC", "LT", "GT", "EQ", "NE", "LE", "GE", "IF", "ELSIF", "ELSE", "FOR",
  "IN", "WHILE", "FUN", "CALL", "IFO", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'['", "']'", "'='", "'('", "')'", "','", "'{'", "'}'", "':'", "$accept",
  "program", "statements", "statement", "array_int", "assign_array",
  "print", "output_var", "input", "in_vars", "function_declare",
  "return_types", "function_name", "fun_var", "parameter_var",
  "function_call", "fun_call_name", "parameters", "single_parameter",
  "switch_statements", "case_stmts", "case_stmt", "def_stmt", "for_loop",
  "while_loop", "while_conditions", "if_blocks", "if_block", "else_part",
  "elif_part", "single_elif_part", "single_else_part", "declarations",
  "str_vars", "str_var", "float_vars", "float_var", "int_vars", "int_var",
  "assignments", "assignment", "expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,    43,    45,    42,    47,    37,    91,    93,
      61,    40,    41,    44,   123,   125,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    67,    68,    68,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      70,    70,    71,    72,    73,    73,    74,    74,    75,    76,
      76,    77,    78,    78,    78,    79,    80,    80,    80,    81,
      81,    82,    83,    84,    84,    85,    86,    86,    86,    87,
      87,    87,    88,    88,    89,    90,    91,    92,    92,    92,
      92,    92,    92,    93,    93,    94,    94,    95,    95,    95,
      95,    96,    96,    97,    98,    99,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     106,   106,   107,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     2,     1,     3,     1,     1,
       2,     2,     2,     2,     1,     1,     1,     1,     2,     1,
       2,     2,     6,     6,     4,     4,     3,     1,     4,     3,
       1,    10,     1,     1,     1,     1,     0,     3,     1,     2,
       2,     5,     1,     3,     1,     1,     7,     7,     7,     1,
       2,     2,     4,     4,     3,    13,     7,     4,     4,     4,
       4,     4,     4,     3,     2,     6,     6,     0,     1,     2,
       1,     2,     1,     7,     4,     2,     2,     2,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     1,     1,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     3,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     4,     0,     3,     2,     1,     8,     9,     6,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     0,     0,     0,     0,    17,     0,    19,    15,
      16,    14,     0,     0,    91,     0,     0,     0,     0,    89,
       0,    75,    87,    85,    76,    83,    81,    77,    79,     0,
       0,    64,     0,     0,    35,     0,    42,     0,     0,    20,
      21,    11,    10,    18,    12,    13,     0,     0,    95,    93,
      94,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    92,    30,     0,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    63,    68,    72,    70,
       0,     0,     0,    36,     0,     7,     0,    90,     0,   116,
     117,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   115,    98,    99,    96,    97,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,    25,    24,     0,    88,     0,    86,
      84,    82,    80,    78,     0,     0,     0,     0,     0,     0,
      71,    69,     0,     0,     0,     0,     0,     0,     0,    38,
      45,     0,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,   105,   112,   113,   114,   108,
     109,   106,   107,   110,   111,   100,   101,   102,   103,   104,
      29,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     4,    39,    40,     0,
       0,    41,     0,    23,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    22,     0,     0,    49,     0,     0,
       0,    14,     0,    74,     0,    57,    59,    58,    60,    62,
      61,     0,     0,    37,    43,     0,     0,    48,     0,    51,
      50,    46,    47,    65,    66,     0,     0,    56,    32,    33,
      34,     0,     4,     4,     4,     0,     0,     4,    52,    53,
      54,    73,     0,     0,     0,    31,     4,     0,    55
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    21,    22,    23,    24,    92,    25,    89,
      26,   281,    55,   178,   179,    27,    57,   181,   182,    28,
     246,   247,   270,    29,    30,   112,    31,    51,   106,   107,
     108,   109,    32,    47,    48,    44,    45,    41,    42,    33,
      34,    87
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -189
static const yytype_int16 yypact[] =
{
      17,  -189,    31,   253,   253,  -189,  -189,  -189,  -189,    62,
     -38,   -15,    11,    51,    53,     6,    46,   108,    72,   117,
     130,   136,   141,   145,   146,   152,  -189,   153,  -189,  -189,
    -189,  -189,   155,    19,  -189,   148,   219,   156,     8,   105,
     159,   104,  -189,   109,   107,  -189,   121,   124,  -189,    15,
     219,   -29,   140,   161,  -189,   128,  -189,   129,   253,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,   185,   134,    50,  -189,
    -189,   133,   135,   137,   138,   139,   142,   143,   147,   149,
     150,   219,   219,   219,   219,   219,   219,   691,  -189,    63,
    -189,   144,    65,   219,   151,   188,   219,    51,   181,    53,
     154,   165,   166,   325,   157,   167,  -189,   -29,  -189,  -189,
     163,    93,   168,   120,   194,   136,   169,  -189,   172,  -189,
    -189,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,     0,   691,   691,    28,    28,   351,   219,   219,   219,
     219,   219,   219,   219,   219,   219,   219,   219,   219,   219,
     219,   219,  -189,   195,  -189,  -189,   200,   691,   198,  -189,
     691,  -189,  -189,  -189,   171,   175,   176,   187,   219,   253,
    -189,  -189,   219,    23,    75,   189,   206,   207,    73,  -189,
    -189,    76,  -189,   219,   377,   403,   429,   455,   481,   507,
     533,   559,   585,   611,  -189,   691,     0,     0,     0,   100,
     100,   100,   100,   100,   100,    28,    28,   215,   215,   215,
    -189,  -189,   193,   196,   196,   196,   253,   637,    -3,   273,
     219,   219,   219,   219,   219,   219,  -189,  -189,  -189,   259,
     120,  -189,   194,   691,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,   126,   203,   125,   204,   205,
      -2,   209,   197,  -189,   219,   691,   691,   691,   691,   691,
     691,     1,    58,  -189,  -189,   210,   211,  -189,   212,  -189,
    -189,  -189,  -189,  -189,  -189,   253,   299,  -189,  -189,  -189,
    -189,   220,  -189,  -189,  -189,     3,   219,  -189,   253,   253,
     253,  -189,   663,    99,   221,  -189,  -189,   173,  -189
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -189,  -189,    -1,   -56,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,    45,  -189,  -189,  -189,    47,  -189,
    -188,  -189,  -189,  -189,  -189,  -189,    71,  -189,  -189,  -189,
     182,   183,  -189,  -189,   192,  -189,   191,  -189,   201,  -189,
     226,   -49
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
       4,   103,   115,    58,    58,     6,     7,     8,     9,    58,
      10,    11,    12,    13,    14,    90,   104,   105,    39,    15,
       1,   137,   100,    37,    91,    65,   248,   249,    40,   101,
     102,     5,   131,   132,   133,   134,   135,   136,   141,   142,
     143,   144,   145,   146,   157,    16,    38,   160,    17,   137,
      18,    19,    20,   147,   148,   149,   150,   151,    43,   269,
      46,   220,   253,   273,   221,   222,   277,    49,   291,   278,
     279,   280,   184,   185,   186,   187,   188,   189,   190,   191,
     192,   193,    66,   149,   150,   151,   119,   120,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,     6,     7,     8,     9,    50,    10,    11,
      12,    13,    14,   218,   223,    52,   224,    15,   225,   217,
      35,   137,    36,   219,    54,   152,   153,   155,   156,   173,
     174,   176,   177,    53,   233,   229,   230,    56,   231,   232,
     265,   266,    58,    16,   245,   268,    17,    59,    18,    19,
      20,    60,    61,   147,   148,   149,   150,   151,    62,    63,
     250,    64,    67,    88,   295,    93,    94,    95,   111,    96,
      97,   255,   256,   257,   258,   259,   260,     6,     7,     8,
       9,    98,    10,    11,    12,    13,    14,    99,   110,   113,
     114,    15,   116,   118,   121,    39,   122,   162,   123,   124,
     125,   180,   210,   126,   127,   276,   154,   211,   128,   158,
     129,   130,   212,   227,   228,   245,   164,    16,   168,   285,
      17,   172,    18,    19,    20,   261,    68,   165,   166,    36,
     175,   169,   183,    69,    70,   213,   137,   292,   298,   214,
     215,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,   216,   244,   226,    81,    82,    83,     6,     7,     8,
       9,   275,    10,    11,    12,    13,    14,   262,   267,   271,
     272,    15,    84,    85,   274,   263,   282,   283,   284,   264,
      86,   288,   289,   290,   287,   296,   293,   251,   161,   170,
     171,   163,   117,     0,   137,   297,   159,    16,     0,     0,
      17,     0,    18,    19,    20,   138,   139,   140,     0,     0,
       0,   141,   142,   143,   144,   145,   146,     0,     0,     0,
     137,     0,     0,     0,     0,     0,   147,   148,   149,   150,
     151,   138,   139,   140,     0,     0,   254,   141,   142,   143,
     144,   145,   146,     0,     0,     0,   137,     0,     0,     0,
       0,     0,   147,   148,   149,   150,   151,   138,   139,   140,
       0,     0,   286,   141,   142,   143,   144,   145,   146,     0,
       0,     0,   137,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   138,   139,   140,     0,   167,     0,   141,
     142,   143,   144,   145,   146,     0,     0,     0,   137,     0,
       0,     0,     0,     0,   147,   148,   149,   150,   151,   138,
     139,   140,     0,   194,     0,   141,   142,   143,   144,   145,
     146,     0,     0,     0,   137,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   138,   139,   140,     0,   234,
       0,   141,   142,   143,   144,   145,   146,     0,     0,     0,
     137,     0,     0,     0,     0,     0,   147,   148,   149,   150,
     151,   138,   139,   140,     0,   235,     0,   141,   142,   143,
     144,   145,   146,     0,     0,     0,   137,     0,     0,     0,
       0,     0,   147,   148,   149,   150,   151,   138,   139,   140,
       0,   236,     0,   141,   142,   143,   144,   145,   146,     0,
       0,     0,   137,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   138,   139,   140,     0,   237,     0,   141,
     142,   143,   144,   145,   146,     0,     0,     0,   137,     0,
       0,     0,     0,     0,   147,   148,   149,   150,   151,   138,
     139,   140,     0,   238,     0,   141,   142,   143,   144,   145,
     146,     0,     0,     0,   137,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   138,   139,   140,     0,   239,
       0,   141,   142,   143,   144,   145,   146,     0,     0,     0,
     137,     0,     0,     0,     0,     0,   147,   148,   149,   150,
     151,   138,   139,   140,     0,   240,     0,   141,   142,   143,
     144,   145,   146,     0,     0,     0,   137,     0,     0,     0,
       0,     0,   147,   148,   149,   150,   151,   138,   139,   140,
       0,   241,     0,   141,   142,   143,   144,   145,   146,     0,
       0,     0,   137,     0,     0,     0,     0,     0,   147,   148,
     149,   150,   151,   138,   139,   140,     0,   242,     0,   141,
     142,   143,   144,   145,   146,     0,     0,     0,   137,     0,
       0,     0,     0,     0,   147,   148,   149,   150,   151,   138,
     139,   140,     0,   243,     0,   141,   142,   143,   144,   145,
     146,     0,     0,     0,   137,     0,     0,     0,     0,     0,
     147,   148,   149,   150,   151,   138,   139,   140,     0,   252,
       0,   141,   142,   143,   144,   145,   146,     0,     0,     0,
       0,     0,   137,     0,     0,     0,   147,   148,   149,   150,
     151,     0,   294,   138,   139,   140,     0,     0,     0,   141,
     142,   143,   144,   145,   146,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   148,   149,   150,   151
};

static const yytype_int16 yycheck[] =
{
       1,    50,    58,     6,     6,     4,     5,     6,     7,     6,
       9,    10,    11,    12,    13,     7,    45,    46,     7,    18,
       3,    21,     7,    61,    16,     6,   214,   215,    17,    14,
      15,     0,    81,    82,    83,    84,    85,    86,    38,    39,
      40,    41,    42,    43,    93,    44,    61,    96,    47,    21,
      49,    50,    51,    53,    54,    55,    56,    57,     7,   247,
       7,    38,    65,    65,    41,    42,    65,    61,    65,    11,
      12,    13,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,    63,    55,    56,    57,    36,    37,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,     4,     5,     6,     7,    61,     9,    10,
      11,    12,    13,   169,    39,     7,    41,    18,    43,   168,
      58,    21,    60,   172,     7,    62,    63,    62,    63,    36,
      37,    11,    12,    61,   183,    62,    63,     7,    62,    63,
      14,    15,     6,    44,    19,    20,    47,     6,    49,    50,
      51,     6,     6,    53,    54,    55,    56,    57,     6,     6,
     216,     6,    14,     7,    65,    60,     7,    63,     7,    60,
      63,   220,   221,   222,   223,   224,   225,     4,     5,     6,
       7,    60,     9,    10,    11,    12,    13,    63,    48,    61,
      61,    18,     7,    59,    61,     7,    61,    16,    61,    61,
      61,     7,     7,    61,    61,   254,    62,     7,    61,    58,
      61,    61,    14,     7,     7,    19,    62,    44,    61,   275,
      47,    58,    49,    50,    51,   226,     7,    62,    62,    60,
      62,    64,    60,    14,    15,    64,    21,   286,    65,    64,
      64,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    64,    59,    64,    35,    36,    37,     4,     5,     6,
       7,    64,     9,    10,    11,    12,    13,     8,    65,    65,
      65,    18,    53,    54,    65,   230,    66,    66,    66,   232,
      61,   282,   283,   284,    64,    64,   287,   216,    97,   107,
     107,    99,    66,    -1,    21,   296,    95,    44,    -1,    -1,
      47,    -1,    49,    50,    51,    32,    33,    34,    -1,    -1,
      -1,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    32,    33,    34,    -1,    -1,    63,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    32,    33,    34,
      -1,    -1,    63,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    32,    33,    34,    -1,    62,    -1,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    32,
      33,    34,    -1,    62,    -1,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    32,    33,    34,    -1,    62,
      -1,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    32,    33,    34,    -1,    62,    -1,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    32,    33,    34,
      -1,    62,    -1,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    32,    33,    34,    -1,    62,    -1,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    32,
      33,    34,    -1,    62,    -1,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    32,    33,    34,    -1,    62,
      -1,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      21,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    32,    33,    34,    -1,    62,    -1,    38,    39,    40,
      41,    42,    43,    -1,    -1,    -1,    21,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    32,    33,    34,
      -1,    62,    -1,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    32,    33,    34,    -1,    62,    -1,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    21,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    32,
      33,    34,    -1,    62,    -1,    38,    39,    40,    41,    42,
      43,    -1,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    32,    33,    34,    -1,    62,
      -1,    38,    39,    40,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    21,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    -1,    59,    32,    33,    34,    -1,    -1,    -1,    38,
      39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    68,    69,    69,     0,     4,     5,     6,     7,
       9,    10,    11,    12,    13,    18,    44,    47,    49,    50,
      51,    70,    71,    72,    73,    75,    77,    82,    86,    90,
      91,    93,    99,   106,   107,    58,    60,    61,    61,     7,
      17,   104,   105,     7,   102,   103,     7,   100,   101,    61,
      61,    94,     7,    61,     7,    79,     7,    83,     6,     6,
       6,     6,     6,     6,     6,     6,    63,    14,     7,    14,
      15,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    35,    36,    37,    53,    54,    61,   108,     7,    76,
       7,    16,    74,    60,     7,    63,    60,    63,    60,    63,
       7,    14,    15,   108,    45,    46,    95,    96,    97,    98,
      48,     7,    92,    61,    61,    70,     7,   107,    59,    36,
      37,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,   108,   108,   108,   108,   108,   108,    21,    32,    33,
      34,    38,    39,    40,    41,    42,    43,    53,    54,    55,
      56,    57,    62,    63,    62,    62,    63,   108,    58,   105,
     108,   103,    16,   101,    62,    62,    62,    62,    61,    64,
      97,    98,    58,    36,    37,    62,    11,    12,    80,    81,
       7,    84,    85,    60,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,    62,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
       7,     7,    14,    64,    64,    64,    64,   108,    70,   108,
      38,    41,    42,    39,    41,    43,    64,     7,     7,    62,
      63,    62,    63,   108,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    59,    19,    87,    88,    87,    87,
      70,    93,    62,    65,    63,   108,   108,   108,   108,   108,
     108,    69,     8,    81,    85,    14,    15,    65,    20,    87,
      89,    65,    65,    65,    65,    64,   108,    65,    11,    12,
      13,    78,    66,    66,    66,    70,    63,    64,    69,    69,
      69,    65,   108,    69,    59,    65,    64,    69,    65
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 219 "bison.y"
    {  printf("\n\nCOMPILATION SUCCESSFUL!\n"); ;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 220 "bison.y"
    {  printf("\n\nCOMPILATION SUCCESSFUL!\n"); ;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 223 "bison.y"
    {;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 236 "bison.y"
    { conditionMatch = 0; ;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 241 "bison.y"
    {printf("*** switch block*****\n");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 246 "bison.y"
    {
  

    printf("array %s is declared of size %d\n",(yyvsp[(3) - (6)].string),(yyvsp[(5) - (6)].integer));
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 252 "bison.y"
    {
    printf("array %s [ %d ] assigned to %.2f",(yyvsp[(1) - (6)].string),(yyvsp[(3) - (6)].integer),(yyvsp[(6) - (6)].real));
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 258 "bison.y"
    { ;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 259 "bison.y"
    { printf("%s\n",(yyvsp[(3) - (4)].string));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 263 "bison.y"
    { show_value((yyvsp[(3) - (3)].string));;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 264 "bison.y"
    { show_value((yyvsp[(1) - (1)].string)); ;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 268 "bison.y"
    { printf("Enter input from console\n"); ;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 272 "bison.y"
    { read_value((yyvsp[(3) - (3)].string));;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 273 "bison.y"
    { read_value((yyvsp[(1) - (1)].string)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 276 "bison.y"
    {;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 285 "bison.y"
    {
        int index = get_function_index((yyvsp[(1) - (1)].string));
        if(index != -1) {
            printf("Function Already Declared.\n");
        } else {
            printf("Declaring Function\n");
            funcptr[funCount].fname = malloc((strlen((yyvsp[(1) - (1)].string)) + 10) * sizeof(char));
            strcpy(funcptr[funCount].fname, (yyvsp[(1) - (1)].string));
            funcptr[funCount].var_cnt = 0;
            funcptr[funCount].fptr = malloc(4 * sizeof(funStruct));
        }
    ;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 303 "bison.y"
    {
        int index = funcptr[funCount].var_cnt;
        int value = 0;
        store_value((yyvsp[(2) - (2)].string), NUMBER, 1, varCount, &value, 0);
        funcptr[funCount].fptr[index] = varptr[varCount];
        varCount++;
        funcptr[funCount].var_cnt++;
        funCount++;
    ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 312 "bison.y"
    {
        int index = funcptr[funCount].var_cnt;
        double value = 0;
        store_value((yyvsp[(2) - (2)].string), FLOAT, 1, varCount, &value, 0);
        funcptr[funCount].fptr[index] = varptr[varCount];
        varCount++;
        funcptr[funCount].var_cnt++;
        funCount++;
    ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 324 "bison.y"
    {
        if(functionRejected) {
            printf("Function Not Declared.\n");
        } else {
            printf("Function Successfully Called.\n");
        }
    ;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 334 "bison.y"
    {
        int index = get_function_index((yyvsp[(1) - (1)].string));
        if(index == -1) {
            printf("Function Doesn't Exist.\n");
        } else {
            currentFun = index;
            currentParameter = 0;
            functionRejected = 0;
        }
    ;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 352 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (1)].string));
        if(currentParameter >= funcptr[currentFun].var_cnt) {
            printf("Way too many arguments.\n");
            functionRejected = 1;
        } else if(funcptr[currentFun].fptr[currentParameter].type != varptr[index].type) {
            printf("Data Types Don't Match.\n");
            functionRejected = 1;
        } else {
            currentParameter++;
        }
    ;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 367 "bison.y"
    {
        maincase =(int)(yyvsp[(3) - (7)].integer);
        printf("Inside switch statement int value %d\n",(yyvsp[(3) - (7)].integer));
    ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 371 "bison.y"
    {
            dmaincase =(double)(yyvsp[(3) - (7)].real);
        printf ("Inside switch statement double %f\n",(yyvsp[(3) - (7)].real));
    ;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 375 "bison.y"
    {
        int i = get_var_index((yyvsp[(3) - (7)].string));
        if(i == -1) {
            var_does_not_exist((yyvsp[(3) - (7)].string));
            
        } else if(varptr[i].type == NUMBER) {
            maincase = varptr[i].ival[0];
        } else if(varptr[i].type == FLOAT) {
            dmaincase = varptr[i].dval[0];
        }
        printf ("Inside switch statement with variable name %s and value \n",(yyvsp[(3) - (7)].string));
    ;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 396 "bison.y"
    {
    subcase = (int)(yyvsp[(2) - (4)].integer);
    printf("inside int case %d : \n",(yyvsp[(2) - (4)].integer));
    
    if(maincase == subcase) {
        printf("%d matched\n",subcase);
    }else{
        printf("%d doen't match\n",subcase);
    }
    subcase = 0;
    
    ;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 408 "bison.y"
    {
    dsubcase = (double) (yyvsp[(2) - (4)].real);
    if(dmaincase == dsubcase){
        printf("%.2lf matched\n",dsubcase);
     }else{
        printf("%.2lf not matched\n",dsubcase);
     }
    dsubcase = 0;
    ;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 419 "bison.y"
    {
  printf("default case from switch case\n");
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 425 "bison.y"
    {
        printf("**** For Loop Block ****\n");
        int from = (yyvsp[(5) - (13)].real);
        int to = (yyvsp[(7) - (13)].real);
        int inc = (yyvsp[(9) - (13)].real);
        int sub = to - from;
        if(sub * inc < 0) {
            printf("Infinite FOR Loop\n");
        } else {
            int c = 1;
            for(int i = from; i <= to; i += inc) {
                printf("For Loop Iteration: %d\n", c);
                c++;
            }
        }
    ;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 442 "bison.y"
    {
        printf("*** WHILE BLOCK ***\n");
        for(int i = 0; i < (yyvsp[(3) - (7)].real); ++i) {
            printf("Repeat Loop Iteration: %d\n", i + 1);
        }
    ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 449 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > (yyvsp[(4) - (4)].real)) {
                (yyval.real) = -1;
            } else {
                (yyval.real) = (int) (yyvsp[(4) - (4)].real) - value;
            }
        }
    ;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 464 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > (yyvsp[(4) - (4)].real)) {
                (yyval.real) = -1;
            } else {
                (yyval.real) = (int) (yyvsp[(4) - (4)].real) - value + 1;
            }
        }
    ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 479 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value > (yyvsp[(4) - (4)].real)) {
                (yyval.real) = -1;
            } else {
                (yyval.real) = (int) (yyvsp[(4) - (4)].real) - value;
            }
        }
    ;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 494 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < (yyvsp[(4) - (4)].real)) {
                (yyval.real) = -1;
            } else {
                (yyval.real) = value - (int) (yyvsp[(4) - (4)].real);
            }
        }
    ;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 509 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < (yyvsp[(4) - (4)].real)) {
                (yyval.real) = -1;
            } else {
                (yyval.real) = value - (int) (yyvsp[(4) - (4)].real) + 1;
            }
        }
    ;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 524 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (4)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (4)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Variable should be NUMBER Type.\n");
        } else {
            int value = varptr[index].ival[0];
            if(value < (yyvsp[(4) - (4)].real)) {
                (yyval.real) = -1;
            } else {
                (yyval.real) = value - (int) (yyvsp[(4) - (4)].real);
            }
        }
    ;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 542 "bison.y"
    { printf("******if else block finished*******\n\n"); ;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 543 "bison.y"
    { printf("***only if block finished*****\n\n");;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 547 "bison.y"
    {
        printf("<<< IF BLOCK >>>\n");
        int condition = (fabs((yyvsp[(2) - (6)].real)) > 1e-9);
        if(condition) {
            conditionMatch = 1;
            printf("Condition Matched in if Block.\n");
        } else {
            printf("Condition Didn't match in if Block.\n");
        }
    ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 557 "bison.y"
    { printf("*****Nested if else found********\n\n"); ;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 569 "bison.y"
    {
        if(conditionMatch == 1) {
            printf("Condition Already Matched in IF Block.\n");
        } else {
            int condition = (fabs((yyvsp[(3) - (7)].real)) > 1e-9);
            if(condition) {
                printf("Condition Matched in else if Block.\n");
                conditionMatch = 1;
            } else {
                printf("Condition Didn't Match in else if Block.\n");
            }
        }
    ;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 585 "bison.y"
    {
        if(conditionMatch == 1) {
            printf("Condition Already Matched.\n");
        } else {
            printf("Condition Matched in ELSE Block.\n");
        }
    ;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 606 "bison.y"
    {
        int exists = check_unique((yyvsp[(1) - (3)].string));
        if(exists == DUPLICATE) {
            not_unique((yyvsp[(1) - (3)].string));
        } else {
            char *value = (yyvsp[(3) - (3)].string);
            store_value((yyvsp[(1) - (3)].string), STRING, 1, varCount, &value, 0);
            varCount++;
        }
    ;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 616 "bison.y"
    {
        char *value = "";
        store_value((yyvsp[(1) - (1)].string), STRING, 1, varCount, &value, 0);
        varCount++;
    ;}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 627 "bison.y"
    {
        if(check_unique((yyvsp[(1) - (3)].string)) == DUPLICATE) {
            not_unique((yyvsp[(1) - (3)].string));
        } else {
            double value = (yyvsp[(3) - (3)].real);
            store_value((yyvsp[(1) - (3)].string), FLOAT, 1, varCount, &value, 0);
            varCount++;
        }
    ;}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 636 "bison.y"
    {
        double value = 0.0;
        store_value((yyvsp[(1) - (1)].string), FLOAT, 1, varCount, &value, 0);
        varCount++;
    ;}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 648 "bison.y"
    {
        if(check_unique((yyvsp[(1) - (3)].string)) == UNIQUE) {
            int value = (yyvsp[(3) - (3)].real);
            store_value((yyvsp[(1) - (3)].string), NUMBER, 1, varCount, &value, 0);
            varCount++;
        } else {
            not_unique((yyvsp[(1) - (3)].string));
        }
    ;}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 657 "bison.y"
    {
        int value = 0;
        store_value((yyvsp[(1) - (1)].string), NUMBER, 1, varCount, &value, 0);
        varCount++;
    ;}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 670 "bison.y"
    {
        int i = get_var_index((yyvsp[(1) - (3)].string));
        if(i == -1) {
            var_does_not_exist((yyvsp[(1) - (3)].string));
            (yyval.real) = 0;
        } else if(varptr[i].type == NUMBER) {
            (yyval.real) = varptr[i].ival[0];
        } else if(varptr[i].type == FLOAT) {
            (yyval.real) = varptr[i].dval[0];
        }
    ;}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 683 "bison.y"
    {
        (yyval.real) = (yyvsp[(1) - (1)].integer);
    ;}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 686 "bison.y"
    {
        (yyval.real) = (yyvsp[(1) - (1)].real);
    ;}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 689 "bison.y"
    {
        int i = get_var_index((yyvsp[(1) - (1)].string));
        if(i == -1) {
            var_does_not_exist((yyvsp[(1) - (1)].string));
            (yyval.real) = 0;
        } else if(varptr[i].type == NUMBER) {
            (yyval.real) = varptr[i].ival[0];
        } else if(varptr[i].type == FLOAT) {
            (yyval.real) = varptr[i].dval[0];
        }
    ;}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 700 "bison.y"
    { (yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 701 "bison.y"
    { (yyval.real) = -(yyvsp[(2) - (2)].real);;}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 702 "bison.y"
    { (yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 703 "bison.y"
    { (yyval.real) = (yyvsp[(2) - (2)].real);;}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 704 "bison.y"
    { (yyval.real) = (yyvsp[(1) - (3)].real) + (yyvsp[(3) - (3)].real);;}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 705 "bison.y"
    { (yyval.real) = (yyvsp[(1) - (3)].real) - (yyvsp[(3) - (3)].real);;}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 706 "bison.y"
    { (yyval.real) = (yyvsp[(1) - (3)].real) * (yyvsp[(3) - (3)].real);;}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 707 "bison.y"
    { (yyval.real) = (yyvsp[(1) - (3)].real) / (yyvsp[(3) - (3)].real);;}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 708 "bison.y"
    {  (yyval.real) = (int)(yyvsp[(1) - (3)].real) % (int)(yyvsp[(3) - (3)].real);;}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 709 "bison.y"
    {  (yyval.real) = pow((yyvsp[(1) - (3)].real), (yyvsp[(3) - (3)].real));;}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 710 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) == (yyvsp[(3) - (3)].real));;}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 711 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) != (yyvsp[(3) - (3)].real));;}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 712 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) < (yyvsp[(3) - (3)].real));;}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 713 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) > (yyvsp[(3) - (3)].real));;}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 714 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) <= (yyvsp[(3) - (3)].real));;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 715 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) >= (yyvsp[(3) - (3)].real));;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 716 "bison.y"
    { (yyval.real) = ( (yyvsp[(1) - (3)].real) && (yyvsp[(3) - (3)].real));;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 717 "bison.y"
    { (yyval.real) = ((yyvsp[(1) - (3)].real) || (yyvsp[(3) - (3)].real));;}
    break;

  case 114:

/* Line 1455 of yacc.c  */
#line 718 "bison.y"
    { (yyval.real) = ((int)(yyvsp[(1) - (3)].real) ^ (int)(yyvsp[(3) - (3)].real));;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 719 "bison.y"
    { (yyval.real) = !(yyvsp[(2) - (2)].real);;}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 721 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (2)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (2)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Can't Increment Incompatible Types.\n");
        } else {
            varptr[index].ival[0]++;
            (yyval.real) = varptr[index].ival[0];

        }
    ;}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 734 "bison.y"
    {
        int index = get_var_index((yyvsp[(1) - (2)].string));
        if(index == -1) {
            var_does_not_exist((yyvsp[(1) - (2)].string));
        } else if(varptr[index].type != NUMBER) {
            printf("Can't Increment Incompatible Types.\n");
        } else {
            varptr[index].ival[0]--;
            (yyval.real) = varptr[index].ival[0];

        }
    ;}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 746 "bison.y"
    {  (yyval.real) = (yyvsp[(2) - (3)].real);;}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 747 "bison.y"
    {  (yyval.real) = sin((yyvsp[(3) - (4)].real));  ;}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 748 "bison.y"
    {  (yyval.real) = cos((yyvsp[(3) - (4)].real));  ;}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 749 "bison.y"
    {  (yyval.real) = tan((yyvsp[(3) - (4)].real));  ;}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 750 "bison.y"
    {  (yyval.real) = log10((yyvsp[(3) - (4)].real));  ;}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 751 "bison.y"
    {  (yyval.real) = log2((yyvsp[(3) - (4)].real));  ;}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 752 "bison.y"
    {  (yyval.real) = log((yyvsp[(3) - (4)].real));  ;}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 753 "bison.y"
    {  (yyval.real) = sqrt((yyvsp[(3) - (4)].real));  ;}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 754 "bison.y"
    {  (yyval.real) = factorial((yyvsp[(3) - (4)].real));  ;}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 755 "bison.y"
    {  (yyval.real) = prime((yyvsp[(3) - (4)].real));  ;}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 756 "bison.y"
    {  (yyval.real) = abs((yyvsp[(3) - (4)].real));  ;}
    break;



/* Line 1455 of yacc.c  */
#line 2813 "bison.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 760 "bison.y"

int main() {
    varptr = malloc(MAX * sizeof(varStruct));
    funcptr = malloc(MAX_FUN * sizeof(funStruct));

    FILE *yyin = freopen("input.txt", "r", stdin);
    FILE *yyout = freopen("output.txt", "w", stdout);

    yyparse();

fclose(yyin);
fclose(yyout);

    free(varptr);
    free(funcptr);

    return 0;
}
