%{
#include"lexical.h" 
#include"y.tab.h" /* header generated by Yacc with Token definitions */
#define YY_NO_INPUT
void lexicalError(const char* message, int lineNumber){
	printf("Something went wrong. Check stderr for more information\n");
	fprintf(stderr,"ERROR IN LINENUMBER:%d:\t%s\n",lineNumber,message);
	exit(1);
}
int copyString ( char * destination, char * source, int length ) {
	int i = 0, n = 0;
	for ( i = 1, n = 0; i < length - 1 ; i++, n++ ) {
		if ( source[i] == ( '\\' ) ) {
			switch ( source[i + 1] ) {
			case ( 't' ):
				destination[n] = '\t';
				break;
			case ( 'n' ):
				destination[n] = '\n';
				break;
			case ( '\"' ):
				destination[n] = '\"';
				break;
			case ( '\\' ):
				destination[n] = '\\';

			default:
				//BAD ESCAPE CHARACTER
				lexicalError("Bad escape character",yylineno);
			}
			i++;
		} else {
			destination[n] = source [i];
			if(source[i]=='\n'){
				lexicalError("Unfinished string",yylineno);
			}
		}
	}
	destination[n] = '\0';
	return 1;
}
void updateLineNumber(const char* comment,int length){
	int i=0;
	for(i=2;i<length-2;i++){
		if(comment[i]=='\n'){
			yylineno++;
		}
	}
}
int returnToken (int tk) {
	if(tk<INTEGER+ASCII_OFFSET){
		//STRING
		free(info.s);
		info.s = malloc(yyleng*sizeof(char));
		if(tk==TK_STRING){
			copyString (info.s,yytext,yyleng);
		} else{
			strcpy(info.s,yytext);
		}
	} else if(tk < FLOAT+ASCII_OFFSET){
		//INTEGER
		if(tk == TK_HEXADECIMAL){
			info.i = strtol(yytext,NULL,16);
		} else {
			info.i = strtol(yytext,NULL,10);
		}
	} else if (tk == FLOAT+ASCII_OFFSET){
		//FLOAT
		info.f = strtod(yytext,NULL);
	}
	return tk;
}

%}
%option nounput

IDENTIFIER	[A-Za-z][A-Za-z0-9]*

INTEGER	[0-9]+
HEXADECIMAL	0x[A-Fa-f0-9]+
FLOAT	(([0-9]*"."[0-9]+)|([0-9]+"."[0-9]*))

ASSIGNMENT	=
OPERATOR_ADD \+
OPERATOR_SUB \-
OPERATOR_MUL \*
OPERATOR_DIV \/

COMPARATOR_EQUAL ==
COMPARATOR_LESS_OR_EQ <=
COMPARATOR_GREATER_OR_EQ >=
COMPARATOR_LESS <
COMPARATOR_GREATER >

BOOLEAN_AND &&
BOOLEAN_OR "||"
LOGICAL_NOT !

STRING \"(\\.|[^\\"])*\"
ML_COMMENT	"/*"[^"*/"]*"*/"
SL_COMMENT	"//"[^\n]*\n

INVALID_STRING	\"(\\.|[^\\"])*\n
INVALID_COMMENT	"/*"[^"*/"]*

%%

\n		{yylineno++;}
"	"	{}
" "		{}

{INVALID_STRING}	{lexicalError("Unfinished string",yylineno);}
{STRING}	{return returnToken(TK_STRING);}
{ML_COMMENT}	{updateLineNumber(yytext,yyleng);}
{INVALID_COMMENT}	{lexicalError("Unfinished comment",yylineno);}
{SL_COMMENT}	{yylineno++;}

;	{return returnToken(TK_SEMICOLON);}
,	{return returnToken(TK_COMMA);}

{ASSIGNMENT}	{return returnToken(TK_ASSIGNMENT);}
{OPERATOR_ADD}	{return returnToken(TK_OPERATOR_ADD);}
{OPERATOR_SUB}	{return returnToken(TK_OPERATOR_SUB);}
{OPERATOR_MUL}	{return returnToken(TK_OPERATOR_MUL);}
{OPERATOR_DIV}	{return returnToken(TK_OPERATOR_DIV);}
{COMPARATOR_EQUAL}	{return returnToken(TK_COMPARATOR_EQUAL);}
{COMPARATOR_LESS_OR_EQ}	{return returnToken(TK_COMPARATOR_LESS_OR_EQ);}
{COMPARATOR_GREATER_OR_EQ}	{return returnToken(TK_COMPARATOR_GREATER_OR_EQ);}
{COMPARATOR_LESS}	{return returnToken(TK_COMPARATOR_LESS);}
{COMPARATOR_GREATER}	{return returnToken(TK_COMPARATOR_GREATER);}
{BOOLEAN_AND}	{return returnToken(TK_BOOLEAN_AND);}
{BOOLEAN_OR}	{return returnToken(TK_BOOLEAN_OR);}
{LOGICAL_NOT}	{return returnToken(TK_LOGICAL_NOT);}

{HEXADECIMAL}	{return returnToken(TK_HEXADECIMAL);}
{INTEGER}		{return returnToken(TK_INTEGER);}
{FLOAT}		{return returnToken(TK_NUMBER_FLOAT);}

"{"	{return returnToken(TK_OPEN_BRACKET);}
"}"	{return returnToken(TK_CLOSE_BRACKET);}
"("	{return returnToken(TK_OPEN_PARENTHESIS);}
")"	{return returnToken(TK_CLOSE_PARENTHESIS);}
"["	{return returnToken(TK_OPEN_SQR_BRACKET);}
"]"	{return returnToken(TK_CLOSE_SQR_BRACKET);}


char	{return returnToken(TK_CHAR);}
else	{return returnToken(TK_ELSE);}
float	{return returnToken(TK_FLOAT);}
if		{return returnToken(TK_IF);}
int		{return returnToken(TK_INT);}
new		{return returnToken(TK_NEW);}
return	{return returnToken(TK_RETURN);}
void	{return returnToken(TK_VOID);}
while	{return returnToken(TK_WHILE);}

{IDENTIFIER}	{return returnToken(TK_IDENTIFIER);}

<<EOF>>		{return returnToken(TK_EOF);}

.		{lexicalError("Unknown token",yylineno); return returnToken(TK_UNKNOWN);}

%%

int yywrap (void) {
	return 1;
}