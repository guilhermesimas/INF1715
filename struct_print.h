#ifndef _STRUCT_PRINT_
#define _STRUCT_PRINT_

#include "tree_structure.h"

void printPrograma( Programa* prog, int ident ) ;

void printIdent( int n ) ;

void printLista( Lista* lst, void ( *printFunc )( void* content, int id ),
                 int ident ) ;

void printDefinicao( void* content, int ident ) ;

void printDefinicaoVariavel( DefinicaoVariavel* defvar, int ident ) ;

void printDefinicaoFuncao( DefinicaoFuncao* deff, int ident ) ;

void printType( Type* type, int ident ) ;

void printNome( void * content, int id ) ;

void printParametro( void* content, int id ) ;

void printBloco( Bloco* bloco, int ident ) ;

void printComando( void* content, int id ) ;

void printComandoIfElse ( ComandoIf* c, int id ) ;

void printComandoWhile ( ComandoWhile* c, int id ) ;

void printComandoAssignment ( ComandoAssignment* c, int id ) ;

void printComandoReturn ( ComandoReturn* c, int id ) ;

void printChamada ( Chamada* c, int id ) ;

void printExp( Exp* exp, int id ) ;

void printVar( Variavel* var, int id ) ;

void printExpValue( ExpValue* exp, int id ) ;

void printNew( ExpNew* exp, int id ) ;

void printUnary( ExpUnary* exp, int id ) ;

void printBinary( ExpBinary* exp, int id ) ;

void printComp( ExpComp* exp, int id ) ;

void printBitwise( ExpBitwise* exp, int id ) ;

void printVarVector( VariavelVector* var, int id ) ;

#endif