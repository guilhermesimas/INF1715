#include "struct_print.h"
#include "tree_structure.h"

#include <stdio.h>

void printPrograma( Programa* prog, int ident ) {
	printIdent( ident );
	printf( "PROGRAMA {\n" );

	printLista( prog->rep_definicao, printDefinicao, ident + 1 );

	printIdent( ident );
	printf( "}\n" );
}

void printIdent( int n ) {
	for ( int i = 0; i < n; i++ ) {
		printf( "  " );
	}
}

void printLista( Lista* lst, void ( *printFunc )( void* content, int id ),
                 int ident ) {
	if ( lst == NULL ) {
		return;
	}
	Element* elem = lst->head;
	for ( int i = 0; i < lst->n; i++ ) {
		printFunc( elem->content, ident );
		elem = elem->next;
	}
}
void printDefinicao( void* content, int ident ) {
	Definicao* def = ( Definicao* )content;
	if ( def->definicaoType == DEF_VAR ) {
		printDefinicaoVariavel( ( DefinicaoVariavel* )def->definicao, ident );
	} else {
		printDefinicaoFuncao( ( DefinicaoFuncao* )def->definicao, ident );
	}
}
void printDefinicaoVariavel( DefinicaoVariavel* defvar, int ident ) {
	printType( defvar->type, ident );
	printLista( defvar->lista_nomes, printNome , ident );
}
void printDefinicaoFuncao( DefinicaoFuncao* deff, int ident ) {
	printIdent( ident );
	printType( deff->type, ident );
	printf( " %s ", deff->id );
	printLista( deff->parametros, printParametro , ident );
	printBloco( deff->bloco, ident );
}

void printType( Type* type, int ident ) {
	if ( type->isVector ) {
		printType( type->type, 0 );
		printf( "[]" );
		return;
	}
	switch ( ( int )( type->type ) ) {
	case T_INT:
		printf( "int " );
		break;
	case T_CHAR:
		printf( "char " );
		break;
	case T_FLOAT:
		printf( "float " );
		break;
	case T_VOID:
		printf( "void " );
		break;
	default:
		printf( "UNKNOWN TYPE" );
	}
}

void printNome( void * content, int id ) {
	printf( "%s ", content );
}

void printParametro( void* content, int id ) {
	Parametro* p = ( Parametro* )content;
	printType( p->type, 0 );
	printf( " %s ", p->id );
}

void printBloco( Bloco* bloco, int ident ) {
	printLista( bloco->def_variavel, printDefinicaoVariavel, ident );
	printLista( bloco->comandos, printComando, ident );
}

void printComando( void* content, int id ) {
	Comando* c = ( Comando* )content;
	switch ( c->comandoType ) {
	case IF_ELSE:
		printComandoIfElse( c->comando, id );
		break;
	case WHILE:
		printComandoWhile( c->comando, id );
		break;
	case ASSIGNMENT:
		printComandoAssignment( c->comando, id );
		break;
	case RETURN:
		printComandoReturn( c->comando, id );
		break;
	case C_CHAMADA:
		printChamada( c->comando, id );
		break;
	case BLOCO:
		printBloco( c->comando, id );
		break;
	}
}

void printComandoIfElse ( ComandoIf* c, int id ) {
	printf( "IF " );
	printExp( c->exp, id );
	printf( " THEN" );
	printComando( c->comando, id );
	if ( c->hasElse ) {
		printf( " ELSE " );
		printComando( c->comandoElse, id );
	}
}
void printComandoWhile ( ComandoWhile* c, int id ) {
	printf( "WHILE " );
	printExp( c->exp, id );
	printComando( c->comando , id );
}
void printComandoAssignment ( ComandoAssignment* c, int id ) {
	printVar( c->var, id );
	printf( " = " );
	printExp( c->exp, id );

}
void printComandoReturn ( ComandoReturn* c, int id ) {
	printf( "RETURN " );
	if ( c->hasExp ) {
		printExp( c->exp, id );
	}
}
void printChamada ( Chamada* c, int id ) {
	printf( "%s ", c->id );
	printLista( c->lista_exp, printExp, id );
}
void printExp( Exp* exp, int id ) {
	switch ( exp->expType ) {
	case VALUE:
		printExpValue( exp->exp, id );
		break;
	case STRING:
		printf( "%s", exp->exp );
		break;
	case VAR:
		printVar( exp->exp, id );
		break;
	case CHAMADA:
		printChamada( exp->exp, id );
		break;
	case NEW:
		printNew( exp->exp, id );
		break;
	case UNARY:
		printUnary( exp->exp, id );
		break;
	case BINARY:
		printBinary( exp->exp, id );
		break;
	case COMP:
		printComp( exp->exp, id );
		break;
	case BOOLEAN:
		printBitwise( exp->exp, id );
		break;
	default:
		printf( "UNKNOWN EXP\n" );
		break;
	}
}
void printVar( Variavel* var, int id ) {
	switch ( var->type ) {
	case VECTOR:
		printVarVector( var->var, id );
		break;
	case NORMAL:
		printf( "%s", var->var );
		break;
	}
}
void printExpValue( ExpValue* exp, int id ) {
	switch ( exp->expValueType ) {
	case E_INT:
		printf( "%d", exp->exp );
		break;
	case E_FLOAT:
		printf( "%f", exp->exp );
		break;
	default:
		printf( "UNKNOWN EXP VAL\n" );
		break;
	}
}
void printNew( ExpNew* exp, int id ) {
	printType( exp->type, id );
	printExp( exp->exp, id );
}
void printUnary( ExpUnary* exp, int id ) {
	switch ( exp->expUnaryTag ) {
	case MINUS:
		printf( "MINUS " );
		break;
	case NOT:
		printf( "NOT " );
		break;
	default:
		printf( "UNKNOWN UNARY\n" );
		break;
	}
	printExp( exp->exp, id );
}
void printBinary( ExpBinary* exp, int id ) {
	printExp( exp->exp1, id );
	switch ( exp->expBinaryTag ) {
	case ADD:
		printf( " ADD " );
		break;
	case SUB:
		printf( " SUB " );
		break;
	case MUL:
		printf( " MUL " );
		break;
	case DIV:
		printf( " DIV " );
		break;
	default:
		printf( "UNKNOWN BINARY\n" );
	}
	printExp( exp->exp2, id );
}
void printComp( ExpComp* exp, int id ) {
	printExp( exp->exp1, id );
	switch ( exp->expCompTag ) {
	case EQ:
		printf( " EQ " );
		break;
	case LESS_EQ:
		printf( " LESS_EQ " );
		break;
	case GREATER_EQ:
		printf( " GREATER_EQ " );
		break;
	case LESS:
		printf( " LESS " );
		break;
	case GREATER:
		printf( " GREATER " );
		break;
	default:
		printf( "UNKNOWN COMP\n" );
	}
	printExp( exp->exp2, id );
}
void printBitwise( ExpBitwise* exp, int id ) {
	printExp( exp->exp1, id );
	switch ( exp->expBitwiseTag ) {
	case AND:
		printf( " AND " );
		break;
	case OR:
		printf( " OR " );
		break;
	default:
		printf( "UNKNOWN BITWISE\n" );
	}
	printExp( exp->exp2, id );
}
void printVarVector( VariavelVector* var, int id ) {
	//Duas exps
	printExp( var->id, id );
	printf( "[" );
	printExp( var->index, id );
	printf( "]" );
}

