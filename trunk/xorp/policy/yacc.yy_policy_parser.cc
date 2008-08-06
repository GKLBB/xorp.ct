#include <stdlib.h>
#ifndef lint
#ifdef __unused
__unused
#endif
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.37 2003/02/12 18:03:55 davidc Exp $";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
#if defined(__cplusplus) || __STDC__
static int yygrowstack(void);
#else
static int yygrowstack();
#endif
#define yyparse yy_policy_parserparse
#define yylex yy_policy_parserlex
#define yyerror yy_policy_parsererror
#define yychar yy_policy_parserchar
#define yyval yy_policy_parserval
#define yylval yy_policy_parserlval
#define yydebug yy_policy_parserdebug
#define yynerrs yy_policy_parsernerrs
#define yyerrflag yy_policy_parsererrflag
#define yyss yy_policy_parserss
#define yyssp yy_policy_parserssp
#define yyvs yy_policy_parservs
#define yyvsp yy_policy_parservsp
#define yylhs yy_policy_parserlhs
#define yylen yy_policy_parserlen
#define yydefred yy_policy_parserdefred
#define yydgoto yy_policy_parserdgoto
#define yysindex yy_policy_parsersindex
#define yyrindex yy_policy_parserrindex
#define yygindex yy_policy_parsergindex
#define yytable yy_policy_parsertable
#define yycheck yy_policy_parsercheck
#define yyname yy_policy_parsername
#define yyrule yy_policy_parserrule
#define yysslim yy_policy_parsersslim
#define yystacksize yy_policy_parserstacksize
#define YYPREFIX "yy_policy_parser"
#line 2 "policy.y"
/*
 * Grammar may be simplified, by allowing "any structure", semantic checking is
 * done at run time anyway...
 * By any structure i mean that you may add / multiple boolean expressions for
 * example. This will give more run time flexibility
 *
 * yacc -d -p yy_policy_parser -o yacc.yy_policy_parser.cc policy.y
 *
 * XXX: with my version of yacc i need to move the #include <stdlib.h> under the
 * yyrcsid
 */

#include <vector>

#include "policy_module.h"
#include "libxorp/xorp.h"
#include "policy/common/element.hh"
#include "policy/common/element_factory.hh"
#include "policy/common/operator.hh"
#include "policy_parser.hh"

extern int  yylex(void);
extern void yyerror(const char *m);

using namespace policy_parser;

static ElementFactory _ef;

#line 32 "policy.y"
typedef union {
	char*		c_str;
	Node*		node;
	BinOper*	op;
} YYSTYPE;
#line 85 "yacc.yy_policy_parser.cc"
#define YYERRCODE 256
#define YY_BOOL 257
#define YY_INT 258
#define YY_UINT 259
#define YY_UINTRANGE 260
#define YY_STR 261
#define YY_ID 262
#define YY_IPV4 263
#define YY_IPV4RANGE 264
#define YY_IPV4NET 265
#define YY_IPV6 266
#define YY_IPV6RANGE 267
#define YY_IPV6NET 268
#define YY_SEMICOLON 269
#define YY_LPAR 270
#define YY_RPAR 271
#define YY_ASSIGN 272
#define YY_SET 273
#define YY_REGEX 274
#define YY_ACCEPT 275
#define YY_REJECT 276
#define YY_PROTOCOL 277
#define YY_NEXT 278
#define YY_POLICY 279
#define YY_PLUS_EQUALS 280
#define YY_MINUS_EQUALS 281
#define YY_NOT 282
#define YY_AND 283
#define YY_XOR 284
#define YY_OR 285
#define YY_HEAD 286
#define YY_CTR 287
#define YY_NE_INT 288
#define YY_EQ 289
#define YY_NE 290
#define YY_LE 291
#define YY_GT 292
#define YY_LT 293
#define YY_GE 294
#define YY_IPNET_EQ 295
#define YY_IPNET_LE 296
#define YY_IPNET_GT 297
#define YY_IPNET_LT 298
#define YY_IPNET_GE 299
#define YY_ADD 300
#define YY_SUB 301
#define YY_MUL 302
const short yy_policy_parserlhs[] = {                                        -1,
    0,    0,    0,    1,    2,    2,    2,    2,    6,    7,
    7,    7,    3,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    4,    4,    4,    5,    5,    5,    5,    5,    5,    5,
    5,    5,    5,    5,    5,    5,    5,    5,    5,    5,
    5,    5,
};
const short yy_policy_parserlen[] = {                                         2,
    2,    2,    0,    2,    1,    1,    1,    2,    3,    1,
    1,    1,    2,    3,    2,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    2,    3,    3,    1,
    1,    1,    1,    1,    1,    2,    1,    1,    1,    1,
    1,    1,
};
const short yy_policy_parserdefred[] = {                                      3,
    0,   44,   43,   41,   42,   40,    0,   47,   48,   51,
   49,   50,   52,    0,    0,    6,    7,    0,    0,    0,
    0,    0,    1,    0,    2,    0,    0,    5,   10,   11,
   12,    0,   45,    0,    0,   46,    0,    8,   15,    0,
    0,    0,    4,   13,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   32,   39,   14,    0,    0,
   16,   17,   18,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   36,
};
const short yy_policy_parserdgoto[] = {                                       1,
   23,   24,   25,   26,   27,   28,   32,
};
const short yy_policy_parsersindex[] = {                                      0,
   48,    0,    0,    0,    0,    0, -268,    0,    0,    0,
    0,    0,    0,   79, -259,    0,    0, -283, -262,   79,
  110,  110,    0, -247,    0, -264,  111,    0,    0,    0,
    0,  110,    0, -269,    2,    0, -252,    0,    0,  110,
 -232, -206,    0,    0,   79,   79,   79,  110,  110,  110,
  110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
  110,  110,  110,  110, -232,    0,    0,    0, -270, -232,
    0,    0,    0, -232, -232, -232, -232, -232, -232, -232,
 -232, -232, -232, -232, -232, -232, -232, -275, -275,    0,
};
const short yy_policy_parserrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,  140,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -70,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -240,    0,    0,    0,    0,  -27,
    0,    0,    0, -260, -198, -192,  174,  177,  180,  183,
  200,  203,  206,  209,  226,  229,  232, -160, -115,    0,
};
const short yy_policy_parsergindex[] = {                                      0,
    0,    0,    0,   70,  -14,    0,    0,
};
#define YYTABLESIZE 517
const short yy_policy_parsertable[] = {                                      35,
   67,   66,   36,   29,   44,   37,   41,   42,   33,   68,
   33,   30,   31,   45,   46,   47,   38,   65,   45,   46,
   47,   43,   33,   33,   33,   69,   64,   70,    9,   62,
   63,   64,    0,   74,   75,   76,   77,   78,   79,   80,
   81,   82,   83,   84,   85,   86,   87,   88,   89,   90,
    2,    3,    4,    5,    6,   33,    8,    9,   10,   11,
   12,   13,    0,   40,    0,    0,   15,   62,   63,   64,
   26,    0,   26,    0,    0,    0,   31,    0,   31,   21,
   22,    0,    0,   34,   26,   26,   26,    0,    0,   39,
   31,   31,   31,   62,   63,   64,   34,   34,   34,   34,
   34,   34,   34,   34,   34,   34,   34,   34,   34,   34,
   34,    0,   34,   34,   71,   72,   73,    0,    0,    0,
    0,   34,   34,   34,   34,   34,   34,   34,   34,   34,
   34,   34,   34,   34,   34,   34,   34,   34,   34,   34,
   34,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,    0,   35,   35,    0,
    0,    0,    0,    0,    0,    0,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   35,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,    0,   37,   37,    0,    0,    0,    0,    0,    0,
    0,   37,   37,   37,   37,   37,   37,   37,   37,   37,
   37,   37,   37,   37,   37,   37,   37,   37,   37,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,    0,   38,   38,    0,    0,    0,
    0,    0,    0,    0,   38,   38,   38,   38,   38,   38,
   38,   38,   38,   38,   38,   38,   38,   38,   38,   38,
   38,   38,   67,    0,    0,   48,    0,    0,    0,    0,
    0,    0,    0,   49,    0,    0,    0,    0,    0,   50,
   51,   52,   53,   54,   55,   56,   57,   58,   59,   60,
   61,   62,   63,   64,    2,    3,    4,    5,    6,    7,
    8,    9,   10,   11,   12,   13,    0,   14,    0,    0,
   15,    0,   16,   17,   18,   19,    0,    0,    0,   20,
    0,    0,    0,   21,   22,    2,    3,    4,    5,    6,
   33,    8,    9,   10,   11,   12,   13,    0,   14,    0,
    0,   15,    0,    0,    0,   18,    0,    0,    0,    0,
   20,    0,    0,    0,   21,   22,    2,    3,    4,    5,
    6,   33,    8,    9,   10,   11,   12,   13,    0,   40,
    0,    0,   15,    0,   48,    0,    0,    0,    0,    0,
    0,    0,   49,    0,    0,   21,   22,    0,   50,   51,
   52,   53,   54,   55,   56,   57,   58,   59,   60,   61,
   62,   63,   64,   45,    0,    0,    0,    0,    0,    0,
    0,   45,    0,    0,    0,    0,    0,   45,   45,   45,
   45,   45,   45,   45,   45,   45,   45,   45,   45,   45,
   45,   45,   19,    0,   19,   20,    0,   20,   23,    0,
   23,   22,    0,   22,    0,    0,   19,   19,   19,   20,
   20,   20,   23,   23,   23,   22,   22,   22,   21,    0,
   21,   24,    0,   24,   25,    0,   25,   29,    0,   29,
    0,    0,   21,   21,   21,   24,   24,   24,   25,   25,
   25,   29,   29,   29,   28,    0,   28,   27,    0,   27,
   30,    0,   30,    0,    0,    0,    0,    0,   28,   28,
   28,   27,   27,   27,   30,   30,   30,
};
const short yy_policy_parsercheck[] = {                                      14,
  271,  271,  262,  272,  269,  289,   21,   22,  269,  262,
  271,  280,  281,  283,  284,  285,  279,   32,  283,  284,
  285,  269,  283,  284,  285,   40,  302,   42,  269,  300,
  301,  302,   -1,   48,   49,   50,   51,   52,   53,   54,
   55,   56,   57,   58,   59,   60,   61,   62,   63,   64,
  257,  258,  259,  260,  261,  262,  263,  264,  265,  266,
  267,  268,   -1,  270,   -1,   -1,  273,  300,  301,  302,
  269,   -1,  271,   -1,   -1,   -1,  269,   -1,  271,  286,
  287,   -1,   -1,   14,  283,  284,  285,   -1,   -1,   20,
  283,  284,  285,  300,  301,  302,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,   -1,  273,  274,   45,   46,   47,   -1,   -1,   -1,
   -1,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
  301,  257,  258,  259,  260,  261,  262,  263,  264,  265,
  266,  267,  268,  269,  270,  271,   -1,  273,  274,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  282,  283,  284,  285,
  286,  287,  288,  289,  290,  291,  292,  293,  294,  295,
  296,  297,  298,  299,  300,  301,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,  269,  270,
  271,   -1,  273,  274,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  282,  283,  284,  285,  286,  287,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  257,
  258,  259,  260,  261,  262,  263,  264,  265,  266,  267,
  268,  269,  270,  271,   -1,  273,  274,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  282,  283,  284,  285,  286,  287,
  288,  289,  290,  291,  292,  293,  294,  295,  296,  297,
  298,  299,  271,   -1,   -1,  274,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  282,   -1,   -1,   -1,   -1,   -1,  288,
  289,  290,  291,  292,  293,  294,  295,  296,  297,  298,
  299,  300,  301,  302,  257,  258,  259,  260,  261,  262,
  263,  264,  265,  266,  267,  268,   -1,  270,   -1,   -1,
  273,   -1,  275,  276,  277,  278,   -1,   -1,   -1,  282,
   -1,   -1,   -1,  286,  287,  257,  258,  259,  260,  261,
  262,  263,  264,  265,  266,  267,  268,   -1,  270,   -1,
   -1,  273,   -1,   -1,   -1,  277,   -1,   -1,   -1,   -1,
  282,   -1,   -1,   -1,  286,  287,  257,  258,  259,  260,
  261,  262,  263,  264,  265,  266,  267,  268,   -1,  270,
   -1,   -1,  273,   -1,  274,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  282,   -1,   -1,  286,  287,   -1,  288,  289,
  290,  291,  292,  293,  294,  295,  296,  297,  298,  299,
  300,  301,  302,  274,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  282,   -1,   -1,   -1,   -1,   -1,  288,  289,  290,
  291,  292,  293,  294,  295,  296,  297,  298,  299,  300,
  301,  302,  269,   -1,  271,  269,   -1,  271,  269,   -1,
  271,  269,   -1,  271,   -1,   -1,  283,  284,  285,  283,
  284,  285,  283,  284,  285,  283,  284,  285,  269,   -1,
  271,  269,   -1,  271,  269,   -1,  271,  269,   -1,  271,
   -1,   -1,  283,  284,  285,  283,  284,  285,  283,  284,
  285,  283,  284,  285,  269,   -1,  271,  269,   -1,  271,
  269,   -1,  271,   -1,   -1,   -1,   -1,   -1,  283,  284,
  285,  283,  284,  285,  283,  284,  285,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 302
#if YYDEBUG
const char * const yy_policy_parsername[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"YY_BOOL","YY_INT","YY_UINT",
"YY_UINTRANGE","YY_STR","YY_ID","YY_IPV4","YY_IPV4RANGE","YY_IPV4NET","YY_IPV6",
"YY_IPV6RANGE","YY_IPV6NET","YY_SEMICOLON","YY_LPAR","YY_RPAR","YY_ASSIGN",
"YY_SET","YY_REGEX","YY_ACCEPT","YY_REJECT","YY_PROTOCOL","YY_NEXT","YY_POLICY",
"YY_PLUS_EQUALS","YY_MINUS_EQUALS","YY_NOT","YY_AND","YY_XOR","YY_OR","YY_HEAD",
"YY_CTR","YY_NE_INT","YY_EQ","YY_NE","YY_LE","YY_GT","YY_LT","YY_GE",
"YY_IPNET_EQ","YY_IPNET_LE","YY_IPNET_GT","YY_IPNET_LT","YY_IPNET_GE","YY_ADD",
"YY_SUB","YY_MUL",
};
const char * const yy_policy_parserrule[] = {
"$accept : statement",
"statement : statement actionstatement",
"statement : statement boolstatement",
"statement :",
"actionstatement : action YY_SEMICOLON",
"action : assignexpr",
"action : YY_ACCEPT",
"action : YY_REJECT",
"action : YY_NEXT YY_POLICY",
"assignexpr : YY_ID assignop expr",
"assignop : YY_ASSIGN",
"assignop : YY_PLUS_EQUALS",
"assignop : YY_MINUS_EQUALS",
"boolstatement : boolexpr YY_SEMICOLON",
"boolexpr : YY_PROTOCOL YY_EQ YY_ID",
"boolexpr : YY_NOT boolexpr",
"boolexpr : boolexpr YY_AND boolexpr",
"boolexpr : boolexpr YY_XOR boolexpr",
"boolexpr : boolexpr YY_OR boolexpr",
"boolexpr : expr YY_EQ expr",
"boolexpr : expr YY_NE expr",
"boolexpr : expr YY_LT expr",
"boolexpr : expr YY_GT expr",
"boolexpr : expr YY_LE expr",
"boolexpr : expr YY_GE expr",
"boolexpr : expr YY_IPNET_EQ expr",
"boolexpr : expr YY_NOT expr",
"boolexpr : expr YY_IPNET_LT expr",
"boolexpr : expr YY_IPNET_GT expr",
"boolexpr : expr YY_IPNET_LE expr",
"boolexpr : expr YY_IPNET_GE expr",
"boolexpr : expr YY_NE_INT expr",
"boolexpr : YY_LPAR boolexpr YY_RPAR",
"boolexpr : expr YY_REGEX expr",
"expr : expr YY_ADD expr",
"expr : expr YY_SUB expr",
"expr : expr YY_MUL expr",
"expr : YY_HEAD expr",
"expr : YY_CTR expr expr",
"expr : YY_LPAR expr YY_RPAR",
"expr : YY_STR",
"expr : YY_UINT",
"expr : YY_UINTRANGE",
"expr : YY_INT",
"expr : YY_BOOL",
"expr : YY_ID",
"expr : YY_SET YY_ID",
"expr : YY_IPV4",
"expr : YY_IPV4RANGE",
"expr : YY_IPV6",
"expr : YY_IPV6RANGE",
"expr : YY_IPV4NET",
"expr : YY_IPV6NET",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 55 "policy.y"
{ _parser_nodes->push_back(yyvsp[0].node); }
break;
case 2:
#line 56 "policy.y"
{ _parser_nodes->push_back(yyvsp[0].node); }
break;
case 4:
#line 61 "policy.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 6:
#line 66 "policy.y"
{ yyval.node = new NodeAccept(_parser_lineno); }
break;
case 7:
#line 67 "policy.y"
{ yyval.node = new NodeReject(_parser_lineno); }
break;
case 8:
#line 69 "policy.y"
{ yyval.node = new NodeNext(_parser_lineno, NodeNext::POLICY); }
break;
case 9:
#line 74 "policy.y"
{ yyval.node = new NodeAssign(yyvsp[-2].c_str, yyvsp[-1].op, yyvsp[0].node, _parser_lineno); free(yyvsp[-2].c_str); }
break;
case 10:
#line 78 "policy.y"
{ yyval.op = NULL; }
break;
case 11:
#line 79 "policy.y"
{ yyval.op = new OpAdd; }
break;
case 12:
#line 80 "policy.y"
{ yyval.op = new OpSub; }
break;
case 13:
#line 84 "policy.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 14:
#line 88 "policy.y"
{ yyval.node = new NodeProto(yyvsp[0].c_str,_parser_lineno); free(yyvsp[0].c_str); }
break;
case 15:
#line 89 "policy.y"
{ yyval.node = new NodeUn(new OpNot,yyvsp[0].node,_parser_lineno); }
break;
case 16:
#line 90 "policy.y"
{ yyval.node = new NodeBin(new OpAnd,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 17:
#line 91 "policy.y"
{ yyval.node = new NodeBin(new OpXor,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 18:
#line 92 "policy.y"
{ yyval.node = new NodeBin(new OpOr,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 19:
#line 94 "policy.y"
{ yyval.node = new NodeBin(new OpEq,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 20:
#line 95 "policy.y"
{ yyval.node = new NodeBin(new OpNe,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 21:
#line 97 "policy.y"
{ yyval.node = new NodeBin(new OpLt,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 22:
#line 98 "policy.y"
{ yyval.node = new NodeBin(new OpGt,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 23:
#line 99 "policy.y"
{ yyval.node = new NodeBin(new OpLe,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 24:
#line 100 "policy.y"
{ yyval.node = new NodeBin(new OpGe,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 25:
#line 102 "policy.y"
{ yyval.node = new NodeBin(new OpEq,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 26:
#line 103 "policy.y"
{ yyval.node = new NodeBin(new OpNe,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 27:
#line 104 "policy.y"
{ yyval.node = new NodeBin(new OpLt,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 28:
#line 105 "policy.y"
{ yyval.node = new NodeBin(new OpGt,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 29:
#line 106 "policy.y"
{ yyval.node = new NodeBin(new OpLe,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 30:
#line 107 "policy.y"
{ yyval.node = new NodeBin(new OpGe,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 31:
#line 109 "policy.y"
{ yyval.node = new NodeBin(new OpNEInt, yyvsp[-2].node, yyvsp[0].node, _parser_lineno); }
break;
case 32:
#line 111 "policy.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 33:
#line 113 "policy.y"
{ yyval.node = new NodeBin(new OpRegex, yyvsp[-2].node, yyvsp[0].node, _parser_lineno); }
break;
case 34:
#line 117 "policy.y"
{ yyval.node = new NodeBin(new OpAdd,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 35:
#line 118 "policy.y"
{ yyval.node = new NodeBin(new OpSub,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 36:
#line 119 "policy.y"
{ yyval.node = new NodeBin(new OpMul,yyvsp[-2].node,yyvsp[0].node,_parser_lineno); }
break;
case 37:
#line 121 "policy.y"
{ yyval.node = new NodeUn(new OpHead, yyvsp[0].node, _parser_lineno); }
break;
case 38:
#line 122 "policy.y"
{ yyval.node = new NodeBin(new OpCtr, yyvsp[-1].node, yyvsp[0].node, _parser_lineno); }
break;
case 39:
#line 124 "policy.y"
{ yyval.node = yyvsp[-1].node; }
break;
case 40:
#line 126 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemStr::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
case 41:
#line 127 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemU32::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str);}
break;
case 42:
#line 128 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemU32Range::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str);}
break;
case 43:
#line 129 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemInt32::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str);}
break;
case 44:
#line 130 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemBool::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str);}
break;
case 45:
#line 131 "policy.y"
{ yyval.node = new NodeVar(yyvsp[0].c_str,_parser_lineno); free(yyvsp[0].c_str); }
break;
case 46:
#line 132 "policy.y"
{ yyval.node = new NodeSet(yyvsp[0].c_str,_parser_lineno); free(yyvsp[0].c_str); }
break;
case 47:
#line 133 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemIPv4::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
case 48:
#line 134 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemIPv4Range::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
case 49:
#line 135 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemIPv6::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
case 50:
#line 136 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemIPv6Range::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
case 51:
#line 137 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemIPv4Net::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
case 52:
#line 138 "policy.y"
{ yyval.node = new NodeElem(_ef.create(ElemIPv6Net::id,yyvsp[0].c_str),_parser_lineno); free(yyvsp[0].c_str); }
break;
#line 796 "yacc.yy_policy_parser.cc"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
