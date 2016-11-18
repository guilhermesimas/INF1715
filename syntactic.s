%{
	#include<string.h>
	#include<stdlib.h>
	#include<stdio.h>
	#include"lexical.h"	
	#include"tree_structure.h"
	#include"struct_manipulation.h"
	#include"struct_print.h"
	extern Programa* prog;
	extern int yylineno;
%}
%token TK_UNKNOWN
%token TK_IDENTIFIER
%token TK_STRING
%token TK_COMMENT
/* INTEGER */
%token TK_INTEGER
%token TK_HEXADECIMAL
/* FLOAT */
%token TK_NUMBER_FLOAT
/* DOES NOT MATTER */
%token TK_LOGICAL_NOT
%token TK_OPERATOR_MUL
%token TK_OPERATOR_DIV
%token TK_OPERATOR_ADD
%token TK_OPERATOR_SUB
%token TK_COMPARATOR_LESS_OR_EQ
%token TK_COMPARATOR_LESS
%token TK_COMPARATOR_GREATER_OR_EQ
%token TK_COMPARATOR_GREATER
%token TK_COMPARATOR_EQUAL
%token TK_BOOLEAN_AND
%token TK_BOOLEAN_OR
%token TK_ASSIGNMENT
%token TK_SEMICOLON
%token TK_COMMA
%token TK_OPEN_BRACKET
%token TK_CLOSE_BRACKET
%token TK_OPEN_PARENTHESIS
%token TK_CLOSE_PARENTHESIS
%token TK_OPEN_SQR_BRACKET
%token TK_CLOSE_SQR_BRACKET
%token TK_CHAR
%token TK_ELSE
%token TK_FLOAT
%token TK_IF
%token TK_INT
%token TK_NEW
%token TK_RETURN
%token TK_VOID
%token TK_WHILE

%left TK_OPEN_SQR_BRACKET
%left TK_LOGICAL_NOT
%left TK_OPERATOR_MUL TK_OPERATOR_DIV
%left TK_OPERATOR_ADD TK_OPERATOR_SUB
%left TK_COMPARATOR_LESS_OR_EQ TK_COMPARATOR_LESS
%left TK_COMPARATOR_GREATER_OR_EQ TK_COMPARATOR_GREATER
%left TK_COMPARATOR_EQUAL
%left TK_BOOLEAN_AND
%left TK_BOOLEAN_OR
%left TK_ASSIGNMENT

%start programa

%%
programa	: rep_definicao {	prog =	createPrograma($1) ;
								$$ = prog;}
			;
rep_definicao	: rep_definicao definicao {printf("REP DEFINICAO\n");
											addLista((Lista*)$1,(void*)$2);
												$$=(int)$1;}
				| definicao {printf("DEFINICAO\n");
							Lista* lst = createLista();
							addLista(lst,(void*)$1);
							$$=(int)lst;}
				;
definicao	: def_variavel {printf("DEF_VARIAVEL 1\n");
							$$=(int)createDefinicao(DEF_VAR,(void*)$1);}
			| def_funcao {printf("DEF_FUNCAO\n");
							$$=(int)createDefinicao(DEF_FUNC,(void*)$1);}
			;
def_variavel	: tipo lista_nomes TK_SEMICOLON {printf("DEF_VARIAVEL 2\n");
												$$=(int)createDefinicaoVariavel((Type*)$1,(Lista*)$2);}
				;
lista_nomes	: TK_IDENTIFIER {printf("LISTA NOMES 1\n");
							char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
							strcpy(str,info.s);
							Lista* lst = createLista();
							addLista(lst,str);
							$$=(int)lst;
							}
			| lista_nomes TK_COMMA TK_IDENTIFIER {printf("LISTA NOMES 2\n");
													char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
													strcpy(str,info.s);
													addLista((Lista*)$1,str);
													$$=(int)$1;}
			;
tipo		: tipo TK_OPEN_SQR_BRACKET TK_CLOSE_SQR_BRACKET {printf("TIPO []\n");
															$$=(int)createType(1,(void*)$1);}
			| tipo_base {printf("TIPO_BASE\n");
						$$=(int)createType(0,(void*)$1);}
		;
tipo_base	: TK_INT {printf("TIPO BASE INT\n");
				$$=$1;}
			| TK_CHAR {printf("TIPO BASE CHAR\n");
				$$=$1;}
			| TK_FLOAT {printf("TIPO BASE FLOAT\n");
				$$=$1;}
			| TK_VOID {printf("TIPO VOID\n");
				$$=$1;}
			;
def_funcao	: tipo TK_IDENTIFIER TK_OPEN_PARENTHESIS parametros TK_CLOSE_PARENTHESIS bloco
				{printf("DEF DEF_FUNCAO\n");
				char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
				strcpy(str,info.s);
				$$=(int)createDefinicaoFuncao((Type*)$1,str,(Lista*)$4,(Bloco*)$6);}
			;
parametros	:  rep_parametros {printf("PARAMETROS 1\n");
				$$=(int)$1;}
			| /*empty*/{printf("PARAMETROS 2\n");}
			;
rep_parametros	: rep_parametros TK_COMMA parametro {printf("REP PARAMETROS 2\n");
													addLista((Lista*)$1,(void*)$3);
													$$=(int)$1;}
				| parametro {printf("REP PARAMETROS 1\n");
							Lista* lst = createLista();
							addLista(lst,(void*)$1);
							$$=(int)lst;}
				;
parametro	: tipo TK_IDENTIFIER {printf("PARAMETRO\n");
				char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
				strcpy(str,info.s);
				$$ = (int)createParametro((Type*)$1,str);
				}
			;
bloco	: TK_OPEN_BRACKET rep_def_variavel rep_comando TK_CLOSE_BRACKET {printf("BLOCO\n");
																		$$=(int)createBloco((Lista*)$2,(Lista*)$3);}
		;

rep_def_variavel	: def_variavel rep_def_variavel {printf("REP DEF_VARIAVEL 1\n");
													addLista((Lista*)$2,(void*)$1);
													$$=(int)$2;}
					| /*empty*/ {printf("REP DEF VARIAVEL 2\n");
								$$=(int)createLista();}
					;
rep_comando	: comando rep_comando {printf("REP COMANDO 1\n");
									addLista((Lista*)$2,(void*)$1);
									$$=(int)$2;}
			| /*empty*/ {printf("REP COMANDO 2\n");
						$$=(int)createLista();}
			;
comando	: TK_IF TK_OPEN_PARENTHESIS exp TK_CLOSE_PARENTHESIS comando opt_else
			{printf("COMANDO 1\n");
			ComandoIf* comif;
			if($6==NULL){
				comif = createComandoIf((Exp*)$3,(Comando*)$5,0,(Comando*)NULL);
			}else{
				comif = createComandoIf((Exp*)$3,(Comando*)$5,1,(Comando*)$6);
			}
			$$=(int)createComando(IF_ELSE,comif);
			}
		| TK_WHILE TK_OPEN_PARENTHESIS exp TK_CLOSE_PARENTHESIS comando
			{printf("COMANDO 2\n");
			Comando* comwhile = createComandoWhile((Exp*)$3,(Comando*)$5);
			$$=(int)createComando(WHILE,comwhile);}
		| var TK_ASSIGNMENT exp TK_SEMICOLON
			{printf("COMANDO 3\n");
			ComandoAssignment* comass=createComandoAssignment((Variavel*)$1,(Exp*)$3);
			$$=(int)createComando(ASSIGNMENT,comass);}
		| TK_RETURN opt_exp TK_SEMICOLON
			{printf("COMANDO 4\n");
			ComandoReturn* comret;
			if($2==NULL){
				comret=createComandoReturn(0,(Exp*)NULL);
			}else{
				comret=createComandoReturn(1,(Exp*)$2);
			}
			$$=(int)createComando(RETURN,comret);
			}
		| chamada TK_SEMICOLON
			{printf("COMANDO 5\n");
			$$=(int)createComando(C_CHAMADA,(void*)$1);
			}
		| bloco 
			{printf("COMANDO 6\n");
			$$=(int)createComando(BLOCO,(void*)$1);}
		;
var	: TK_IDENTIFIER {printf("VAR 1 - %s\n",info.s);
					char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
					strcpy(str,info.s);
					$$=(int)createVariavel(NORMAL,str);}
	| exp TK_OPEN_SQR_BRACKET exp TK_CLOSE_SQR_BRACKET {printf("VAR 2\n");
														$$=(int)createVariavelVector((Exp*)$1,(Exp*)$3);}
	;
exp	: TK_INTEGER {printf("EXP 1\n");
					long int *i=(long int*)malloc(sizeof(long int));
					*i=info.i;
					ExpValue* expval = createExpValue(E_INT,i);
					$$=(int)createExp(VALUE,expval);}
	| TK_NUMBER_FLOAT {printf("EXP 2\n");
						double* f=(double*)malloc(sizeof(double));
						*f=info.f;
						ExpValue* expval = createExpValue(E_FLOAT,f);
						$$=(int)createExp(VALUE,expval);}
	| TK_HEXADECIMAL {printf("EXP 3\n");
					long int *i=(long int*)malloc(sizeof(long int));
					*i=info.i;
					ExpValue* expval = createExpValue(E_INT,i);
					$$=(int)createExp(VALUE,expval);
					}
	| TK_STRING {printf("EXP 4\n");
				char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
				strcpy(str,info.s);
				$$=(int)createExp(STRING,str);}
	| var {printf("EXP 5\n");
			$$=createExp(VAR,(void*)$1);
			}
	| TK_OPEN_PARENTHESIS exp TK_CLOSE_PARENTHESIS {printf("EXP 6\n");
													$$=(int)$2;} 
	| chamada {printf("EXP 7\n");
				$$=(int)createExp(CHAMADA,(void*)$1);}
	| TK_NEW tipo TK_OPEN_SQR_BRACKET exp TK_CLOSE_SQR_BRACKET {printf("EXP 8\n");
																ExpNew* expnew = createExpNew((Type*)$2,(Exp*)$4);
																$$=(int)createExp(NEW,expnew);}
	| exp_not {printf("EXP 19\n");
				$$=(int)createExp(UNARY,(void*)$1);}
	| exp_unary_minus {printf("EXP 10\n");
						$$=(int)createExp(UNARY,(void*)$1);}
	| exp_add {printf("EXP 10\n");
				$$=(int)createExp(BINARY,(void*)$1);}
	| exp_sub {printf("EXP 11\n");
				$$=(int)createExp(BINARY,(void*)$1);}
	| exp_mul {printf("EXP 12\n");
				$$=(int)createExp(BINARY,(void*)$1);}
	| exp_div {printf("EXP 13\n");
				$$=(int)createExp(BINARY,(void*)$1);}
	| exp_comp_eq {printf("EXP 14\n");
				$$=(int)createExp(COMP,(void*)$1);}
	| exp_comp_less_eq {printf("EXP 15\n");
				$$=(int)createExp(COMP,(void*)$1);}
	| exp_comp_greater_eq {printf("EXP 16\n");
				$$=(int)createExp(COMP,(void*)$1);}
	| exp_comp_less {printf("EXP 17\n");
				$$=(int)createExp(COMP,(void*)$1);}
	| exp_comp_greater {printf("EXP 18\n");
				$$=(int)createExp(COMP,(void*)$1);}
	| exp_boolean_and {printf("EXP 20\n");
				$$=(int)createExp(BOOLEAN,(void*)$1);}
	| exp_boolean_or {printf("EXP 21\n");
				$$=(int)createExp(COMP,(void*)$1);}
	;

exp_not	: TK_LOGICAL_NOT exp {printf("EXP NOT\n");
								$$=(int)createExpUnary(NOT,(Exp*)$2);}
		;
exp_unary_minus	: TK_OPERATOR_SUB exp %prec TK_LOGICAL_NOT{printf("EXP UNARY MINUS\n");
															$$=(int)createExpUnary(MINUS,(Exp*)$2);}
				;
exp_add 	: exp TK_OPERATOR_ADD exp {printf("EXP ADD\n");
										$$=(int)createExpBinary(ADD,(Exp*)$1,(Exp*)$3);}
			;
exp_sub 	: exp TK_OPERATOR_SUB exp {printf("EXP SUB\n");
										$$=(int)createExpBinary(SUB,(Exp*)$1,(Exp*)$3);}
			;
exp_mul 	: exp TK_OPERATOR_MUL exp {printf("EXP MUL\n");
										$$=(int)createExpBinary(MUL,(Exp*)$1,(Exp*)$3);}
			;
exp_div 	: exp TK_OPERATOR_DIV exp {printf("EXP DIV\n");
										$$=(int)createExpBinary(DIV,(Exp*)$1,(Exp*)$3);}
			;
exp_comp_eq	: exp TK_COMPARATOR_EQUAL exp {printf("EXP COMP EQ\n");
										$$=(int)createExpComp(EQ,(Exp*)$1,(Exp*)$3);}
			;
exp_comp_less_eq 	: exp TK_COMPARATOR_LESS_OR_EQ exp {printf("EXP COMP LESS EQ\n");
										$$=(int)createExpComp(LESS_EQ,(Exp*)$1,(Exp*)$3);}
					;
exp_comp_greater_eq 	: exp TK_COMPARATOR_GREATER_OR_EQ exp {printf("EXP COMP GREATER EQ\n");
										$$=(int)createExpComp(GREATER_EQ,(Exp*)$1,(Exp*)$3);}
						;
exp_comp_less 	: exp TK_COMPARATOR_LESS exp {printf("EXP COMP LESS\n");
										$$=(int)createExpComp(LESS,(Exp*)$1,(Exp*)$3);}
				;
exp_comp_greater 	: exp TK_COMPARATOR_GREATER exp {printf("EXP COMP GREATER\n");
										$$=(int)createExpComp(GREATER,(Exp*)$1,(Exp*)$3);}
					;
exp_boolean_and 	: exp TK_BOOLEAN_AND exp {printf("EXP BOOL AND\n");
										$$=(int)createExpBitwise(AND,$1,$3);}
					;
exp_boolean_or 	: exp TK_BOOLEAN_OR exp {printf("EXP BOOL OR\n");
										$$=(int)createExpBitwise(AND,$1,$3);}
				;

chamada	: TK_IDENTIFIER TK_OPEN_PARENTHESIS lista_exp TK_CLOSE_PARENTHESIS 
			{printf("CHAMADA\n");
			char* str = (char*)malloc(1+strlen(info.s)*sizeof(char));
			strcpy(str,info.s);
			$$=(int)createChamada(str,(Lista*)$3);
			}
		;
lista_exp	: rep_exp {printf("LISTA_EXP 1\n");
						$$=(int)$1;}
			| /*empty*/ {printf("LISTA_EXP 2\n");
						$$=(int)NULL;}
			;
rep_exp	: exp{printf("REP EXP 1\n");
				Lista* lst = createLista();
				addLista(lst,(void*)$1);
				$$=(int)lst;}
		| rep_exp TK_COMMA exp {printf("REP_EXP 2\n");
								addLista((Lista*)$1,(void*)$3);
								$$=(int)$1;}
		;
opt_else	: TK_ELSE comando {printf("ELSE 1\n");
								$$=(int)$2;}
			| /*empty*/ {printf("ELSE 2\n");
						$$=(int)NULL;}
			;
opt_exp	: exp {printf("OPT EXP 1\n");
				$$=(int)$1;}
		| /*empty */ {printf("OPT EXP 2\n");
						$$=(int)NULL;}
		;

%%
extern char yytext[];
#define YYDEBUG_LEXER_TEXT yytext
int yydebug=1;
Info_t info;
Programa* prog;
int main (void) {
	yyparse();
	printPrograma(prog,0);
	return 0;
}
yyerror(s) char *s; {
                fprintf( stderr, " yyerror: %s\n", s );
                }
