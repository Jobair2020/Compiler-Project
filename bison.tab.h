
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 193 "bison.y"

	int integer;
	double real;
	char *string;



/* Line 1676 of yacc.c  */
#line 112 "bison.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


