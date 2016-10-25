/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_UNKNOWN = 258,
    TK_IDENTIFIER = 259,
    TK_STRING = 260,
    TK_COMMENT = 261,
    TK_INTEGER = 262,
    TK_HEXADECIMAL = 263,
    TK_NUMBER_FLOAT = 264,
    TK_LOGICAL_NOT = 265,
    TK_OPERATOR_MUL = 266,
    TK_OPERATOR_DIV = 267,
    TK_OPERATOR_ADD = 268,
    TK_OPERATOR_SUB = 269,
    TK_COMPARATOR_LESS_OR_EQ = 270,
    TK_COMPARATOR_LESS = 271,
    TK_COMPARATOR_GREATER_OR_EQ = 272,
    TK_COMPARATOR_GREATER = 273,
    TK_COMPARATOR_EQUAL = 274,
    TK_BOOLEAN_AND = 275,
    TK_BOOLEAN_OR = 276,
    TK_ASSIGNMENT = 277,
    TK_SEMICOLON = 278,
    TK_COMMA = 279,
    TK_OPEN_BRACKET = 280,
    TK_CLOSE_BRACKET = 281,
    TK_OPEN_PARENTHESIS = 282,
    TK_CLOSE_PARENTHESIS = 283,
    TK_OPEN_SQR_BRACKET = 284,
    TK_CLOSE_SQR_BRACKET = 285,
    TK_CHAR = 286,
    TK_ELSE = 287,
    TK_FLOAT = 288,
    TK_IF = 289,
    TK_INT = 290,
    TK_NEW = 291,
    TK_RETURN = 292,
    TK_VOID = 293,
    TK_WHILE = 294
  };
#endif
/* Tokens.  */
#define TK_UNKNOWN 258
#define TK_IDENTIFIER 259
#define TK_STRING 260
#define TK_COMMENT 261
#define TK_INTEGER 262
#define TK_HEXADECIMAL 263
#define TK_NUMBER_FLOAT 264
#define TK_LOGICAL_NOT 265
#define TK_OPERATOR_MUL 266
#define TK_OPERATOR_DIV 267
#define TK_OPERATOR_ADD 268
#define TK_OPERATOR_SUB 269
#define TK_COMPARATOR_LESS_OR_EQ 270
#define TK_COMPARATOR_LESS 271
#define TK_COMPARATOR_GREATER_OR_EQ 272
#define TK_COMPARATOR_GREATER 273
#define TK_COMPARATOR_EQUAL 274
#define TK_BOOLEAN_AND 275
#define TK_BOOLEAN_OR 276
#define TK_ASSIGNMENT 277
#define TK_SEMICOLON 278
#define TK_COMMA 279
#define TK_OPEN_BRACKET 280
#define TK_CLOSE_BRACKET 281
#define TK_OPEN_PARENTHESIS 282
#define TK_CLOSE_PARENTHESIS 283
#define TK_OPEN_SQR_BRACKET 284
#define TK_CLOSE_SQR_BRACKET 285
#define TK_CHAR 286
#define TK_ELSE 287
#define TK_FLOAT 288
#define TK_IF 289
#define TK_INT 290
#define TK_NEW 291
#define TK_RETURN 292
#define TK_VOID 293
#define TK_WHILE 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
