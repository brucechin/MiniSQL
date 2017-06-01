/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 21 "parse.y"

#include "parse.h"
#include "miniSqlDef.h"
#include <assert.h>
#line 13 "parse.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    miniSqlParserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is miniSqlParserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    miniSqlParserARG_SDECL     A static variable declaration for the %extra_argument
**    miniSqlParserARG_PDECL     A parameter declaration for the %extra_argument
**    miniSqlParserARG_STORE     Code to store %extra_argument into yypParser
**    miniSqlParserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 61
#define YYACTIONTYPE unsigned char
#define miniSqlParserTOKENTYPE Token
typedef union {
  int yyinit;
  miniSqlParserTOKENTYPE yy0;
  int yy52;
  SrcList* yy67;
  NameList* yy100;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define miniSqlParserARG_SDECL Parser *pParser;
#define miniSqlParserARG_PDECL ,Parser *pParser
#define miniSqlParserARG_FETCH Parser *pParser = yypParser->pParser
#define miniSqlParserARG_STORE yypParser->pParser = pParser
#define YYNSTATE 86
#define YYNRULE 42
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (116)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   129,    1,   53,   52,   83,   27,   86,   21,   30,   14,
 /*    10 */    64,   30,   46,   66,   45,   41,   42,   73,   72,   85,
 /*    20 */    52,   83,   27,   76,   49,   74,   28,   25,   35,   28,
 /*    30 */    32,   35,   26,   32,   17,   29,   14,   17,   68,   14,
 /*    40 */    61,   23,   18,   50,    9,   78,   45,   21,   42,   14,
 /*    50 */    24,   73,   72,   54,   56,   67,   84,   31,   38,   81,
 /*    60 */    60,   58,   34,   41,   22,   41,   41,   41,   13,   48,
 /*    70 */    47,   79,   75,   41,   44,   20,   19,   16,   70,   12,
 /*    80 */    15,   39,    3,   33,   62,   59,    6,   57,   82,    5,
 /*    90 */     4,   51,    2,   11,   40,   10,    8,   36,    7,   80,
 /*   100 */    71,   55,   43,   69,   63,  130,  130,  130,   65,  130,
 /*   110 */   130,  130,  130,   37,  130,   77,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    39,   40,   41,   42,   43,   44,    0,   50,    2,   52,
 /*    10 */    47,    2,   55,   56,   14,   52,   16,   17,   18,   41,
 /*    20 */    42,   43,   44,   11,   12,   13,   20,    3,   22,   20,
 /*    30 */    24,   22,   48,   24,   50,   48,   52,   50,    5,   52,
 /*    40 */     5,    3,    9,   14,    9,   16,   14,   50,   16,   52,
 /*    50 */    26,   17,   18,   58,   59,   52,    1,   54,   47,    5,
 /*    60 */    47,   47,   47,   52,   26,   52,   52,   52,   47,    4,
 /*    70 */    10,   15,    5,   52,   15,    9,    4,   19,    5,    4,
 /*    80 */    27,    7,    4,    4,    8,    8,   23,    5,   45,   25,
 /*    90 */     4,   49,    9,   46,    6,   46,   57,    6,   57,   51,
 /*   100 */    56,   21,   52,   52,   52,   60,   60,   60,   51,   60,
 /*   110 */    60,   60,   60,   52,   60,   53,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_COUNT (52)
#define YY_SHIFT_MIN   (0)
#define YY_SHIFT_MAX   (91)
static const signed char yy_shift_ofst[] = {
 /*     0 */     9,    6,    0,   34,   34,   34,   34,   34,   34,   34,
 /*    10 */    34,   34,   34,   80,   12,   34,   34,   29,   34,   34,
 /*    20 */    32,   29,   91,   91,   88,   88,   83,   86,   38,   35,
 /*    30 */    24,   33,   64,   82,   79,   63,   77,   78,   53,   76,
 /*    40 */    74,   58,   75,   73,   72,   59,   66,   67,   60,   65,
 /*    50 */    56,   54,   55,
};
#define YY_REDUCE_USE_DFLT (-44)
#define YY_REDUCE_COUNT (27)
#define YY_REDUCE_MIN   (-43)
#define YY_REDUCE_MAX   (62)
static const signed char yy_reduce_ofst[] = {
 /*     0 */   -39,  -22,  -43,  -13,  -16,   21,   15,   14,   13,   -3,
 /*    10 */    11,  -37,    3,   -5,   62,   61,   52,   57,   51,   50,
 /*    20 */    44,   48,   41,   39,   49,   47,   42,   43,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   128,  128,  128,  128,  128,  128,  128,  128,  128,  128,
 /*    10 */   128,  128,  128,  121,   99,  128,  128,  103,  128,  128,
 /*    20 */   128,  103,  119,  119,   94,   94,  112,  128,  128,  128,
 /*    30 */   128,  128,  128,  128,  128,  128,  128,  128,  128,  128,
 /*    40 */   128,  108,  128,  128,  128,  128,  113,  128,  128,  128,
 /*    50 */   128,  128,  128,   88,  125,  123,  122,  124,  127,  120,
 /*    60 */   118,  126,   95,  109,   92,   97,  115,  111,  117,  110,
 /*    70 */   116,  114,  107,  106,  102,  101,  100,   98,  105,  104,
 /*    80 */    96,   93,   91,   90,   89,   87,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  miniSqlParserARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void miniSqlParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "SEMICOLON",     "CREATE",        "TABLE",       
  "LP",            "RP",            "IF",            "NOT",         
  "EXISTS",        "COMMA",         "INTEGER",       "INT_TYPE",    
  "CHAR_TYPE",     "FLOAT_TYPE",    "PRIMARY",       "KEY",         
  "UNIQUE",        "STRING",        "ID",            "DOT",         
  "DROP",          "WHERE",         "INSERT",        "INTO",        
  "DELETE",        "FROM",          "INDEX",         "ON",          
  "OR",            "AND",           "IS",            "NE",          
  "EQ",            "BETWEEN",       "GT",            "LE",          
  "LT",            "GE",            "error",         "input",       
  "cmdlist",       "cmd_and_end",   "singlecmd",     "cmd",         
  "create_table",  "create_table_args",  "if_not_exists",  "full_name",   
  "columnlist",    "optional_constraint_list",  "column_name",   "column_constraint",
  "name",          "type_token",    "name_list",     "constraint_list",
  "table_constraint",  "if_exists",     "opt_where_clause",  "where_clause",
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "input ::= cmdlist",
 /*   1 */ "cmdlist ::= cmdlist cmd_and_end",
 /*   2 */ "cmdlist ::= cmd_and_end",
 /*   3 */ "cmd_and_end ::= singlecmd SEMICOLON",
 /*   4 */ "singlecmd ::= cmd",
 /*   5 */ "cmd ::= create_table create_table_args",
 /*   6 */ "create_table ::= CREATE TABLE if_not_exists full_name",
 /*   7 */ "create_table_args ::= LP columnlist optional_constraint_list RP",
 /*   8 */ "if_not_exists ::=",
 /*   9 */ "if_not_exists ::= IF NOT EXISTS",
 /*  10 */ "columnlist ::= columnlist COMMA column_name column_constraint",
 /*  11 */ "columnlist ::= column_name column_constraint",
 /*  12 */ "column_name ::= name type_token",
 /*  13 */ "type_token ::=",
 /*  14 */ "type_token ::= INT_TYPE",
 /*  15 */ "type_token ::= CHAR_TYPE LP INTEGER RP",
 /*  16 */ "type_token ::= FLOAT_TYPE",
 /*  17 */ "column_constraint ::=",
 /*  18 */ "column_constraint ::= PRIMARY KEY",
 /*  19 */ "column_constraint ::= UNIQUE",
 /*  20 */ "name ::= STRING",
 /*  21 */ "name ::= ID",
 /*  22 */ "full_name ::= name",
 /*  23 */ "full_name ::= name DOT name",
 /*  24 */ "name_list ::= name_list COMMA name",
 /*  25 */ "name_list ::= name",
 /*  26 */ "optional_constraint_list ::=",
 /*  27 */ "optional_constraint_list ::= COMMA constraint_list",
 /*  28 */ "constraint_list ::= constraint_list COMMA table_constraint",
 /*  29 */ "constraint_list ::= table_constraint",
 /*  30 */ "table_constraint ::= PRIMARY KEY LP name RP",
 /*  31 */ "table_constraint ::= UNIQUE LP name_list RP",
 /*  32 */ "cmd ::= DROP TABLE if_exists full_name",
 /*  33 */ "if_exists ::=",
 /*  34 */ "if_exists ::= IF EXISTS",
 /*  35 */ "opt_where_clause ::=",
 /*  36 */ "opt_where_clause ::= where_clause",
 /*  37 */ "where_clause ::= WHERE",
 /*  38 */ "cmd ::= INSERT INTO full_name LP RP",
 /*  39 */ "cmd ::= DELETE FROM full_name opt_where_clause",
 /*  40 */ "cmd ::= CREATE INDEX if_not_exists full_name ON name LP columnlist RP",
 /*  41 */ "cmd ::= DROP INDEX if_exists full_name",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to miniSqlParser and miniSqlParserFree.
*/
void *miniSqlParserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  miniSqlParserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 47: /* full_name */
{
#line 80 "parse.y"

//TODO: add destructor

#line 451 "parse.c"
}
      break;
    case 54: /* name_list */
{
#line 92 "parse.y"

#line 458 "parse.c"
}
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from miniSqlParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void miniSqlParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int miniSqlParserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   miniSqlParserARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
#line 15 "parse.y"

    miniSqlError(pParser, "parser stack overflow");
#line 643 "parse.c"
   miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 39, 1 },
  { 40, 2 },
  { 40, 1 },
  { 41, 2 },
  { 42, 1 },
  { 43, 2 },
  { 44, 4 },
  { 45, 4 },
  { 46, 0 },
  { 46, 3 },
  { 48, 4 },
  { 48, 2 },
  { 50, 2 },
  { 53, 0 },
  { 53, 1 },
  { 53, 4 },
  { 53, 1 },
  { 51, 0 },
  { 51, 2 },
  { 51, 1 },
  { 52, 1 },
  { 52, 1 },
  { 47, 1 },
  { 47, 3 },
  { 54, 3 },
  { 54, 1 },
  { 49, 0 },
  { 49, 2 },
  { 55, 3 },
  { 55, 1 },
  { 56, 5 },
  { 56, 4 },
  { 43, 4 },
  { 57, 0 },
  { 57, 2 },
  { 58, 0 },
  { 58, 1 },
  { 59, 1 },
  { 43, 5 },
  { 43, 4 },
  { 43, 9 },
  { 43, 4 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  miniSqlParserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 4: /* singlecmd ::= cmd */
#line 36 "parse.y"
{
    // reach here doesn't mean there is no mistake in the statement
    miniSqlLog(pParser, "finish a command");
}
#line 802 "parse.c"
        break;
      case 6: /* create_table ::= CREATE TABLE if_not_exists full_name */
#line 44 "parse.y"
{
    //
}
#line 809 "parse.c"
        break;
      case 7: /* create_table_args ::= LP columnlist optional_constraint_list RP */
      case 12: /* column_name ::= name type_token */ yytestcase(yyruleno==12);
      case 13: /* type_token ::= */ yytestcase(yyruleno==13);
      case 14: /* type_token ::= INT_TYPE */ yytestcase(yyruleno==14);
      case 15: /* type_token ::= CHAR_TYPE LP INTEGER RP */ yytestcase(yyruleno==15);
      case 16: /* type_token ::= FLOAT_TYPE */ yytestcase(yyruleno==16);
      case 25: /* name_list ::= name */ yytestcase(yyruleno==25);
      case 30: /* table_constraint ::= PRIMARY KEY LP name RP */ yytestcase(yyruleno==30);
      case 31: /* table_constraint ::= UNIQUE LP name_list RP */ yytestcase(yyruleno==31);
      case 32: /* cmd ::= DROP TABLE if_exists full_name */ yytestcase(yyruleno==32);
      case 41: /* cmd ::= DROP INDEX if_exists full_name */ yytestcase(yyruleno==41);
#line 48 "parse.y"
{

}
#line 826 "parse.c"
        break;
      case 8: /* if_not_exists ::= */
      case 17: /* column_constraint ::= */ yytestcase(yyruleno==17);
      case 33: /* if_exists ::= */ yytestcase(yyruleno==33);
#line 53 "parse.y"
{yygotominor.yy52 = 0;}
#line 833 "parse.c"
        break;
      case 9: /* if_not_exists ::= IF NOT EXISTS */
      case 18: /* column_constraint ::= PRIMARY KEY */ yytestcase(yyruleno==18);
      case 34: /* if_exists ::= IF EXISTS */ yytestcase(yyruleno==34);
#line 54 "parse.y"
{yygotominor.yy52 = 1;}
#line 840 "parse.c"
        break;
      case 19: /* column_constraint ::= UNIQUE */
#line 73 "parse.y"
{yygotominor.yy52 = 2;}
#line 845 "parse.c"
        break;
      case 22: /* full_name ::= name */
#line 83 "parse.y"
{
// TODO: alloc for SrcList
// transform Token to Src
}
#line 853 "parse.c"
        break;
      case 23: /* full_name ::= name DOT name */
#line 87 "parse.y"
{
// TODO: alloc for SrcList
}
#line 860 "parse.c"
        break;
      case 26: /* optional_constraint_list ::= */
#line 102 "parse.y"
{yygotominor.yy0.n = 0; yygotominor.yy0.text = 0;}
#line 865 "parse.c"
        break;
      case 36: /* opt_where_clause ::= where_clause */
#line 126 "parse.y"
{yygotominor.yy0 = yymsp[0].minor.yy0;}
#line 870 "parse.c"
        break;
      default:
      /* (0) input ::= cmdlist */ yytestcase(yyruleno==0);
      /* (1) cmdlist ::= cmdlist cmd_and_end */ yytestcase(yyruleno==1);
      /* (2) cmdlist ::= cmd_and_end */ yytestcase(yyruleno==2);
      /* (3) cmd_and_end ::= singlecmd SEMICOLON */ yytestcase(yyruleno==3);
      /* (5) cmd ::= create_table create_table_args */ yytestcase(yyruleno==5);
      /* (10) columnlist ::= columnlist COMMA column_name column_constraint */ yytestcase(yyruleno==10);
      /* (11) columnlist ::= column_name column_constraint */ yytestcase(yyruleno==11);
      /* (20) name ::= STRING */ yytestcase(yyruleno==20);
      /* (21) name ::= ID */ yytestcase(yyruleno==21);
      /* (24) name_list ::= name_list COMMA name */ yytestcase(yyruleno==24);
      /* (27) optional_constraint_list ::= COMMA constraint_list */ yytestcase(yyruleno==27);
      /* (28) constraint_list ::= constraint_list COMMA table_constraint */ yytestcase(yyruleno==28);
      /* (29) constraint_list ::= table_constraint */ yytestcase(yyruleno==29);
      /* (35) opt_where_clause ::= */ yytestcase(yyruleno==35);
      /* (37) where_clause ::= WHERE */ yytestcase(yyruleno==37);
      /* (38) cmd ::= INSERT INTO full_name LP RP */ yytestcase(yyruleno==38);
      /* (39) cmd ::= DELETE FROM full_name opt_where_clause */ yytestcase(yyruleno==39);
      /* (40) cmd ::= CREATE INDEX if_not_exists full_name ON name LP columnlist RP */ yytestcase(yyruleno==40);
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  miniSqlParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  miniSqlParserARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 10 "parse.y"

    // TODO: add location of error
    miniSqlError(pParser, "syntax error");
#line 954 "parse.c"
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  miniSqlParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  miniSqlParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "miniSqlParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void miniSqlParser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  miniSqlParserTOKENTYPE yyminor       /* The value for the token */
  miniSqlParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  miniSqlParserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
