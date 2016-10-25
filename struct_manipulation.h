#ifndef _STRUCT_MANIPULATION_
#define _STRUCT_MANIPULATION_

#include <stdlib.h>
#include <stdio.h>
#include "tree_structure.h"

#define MALLOC(N,DTYPE) {(DTYPE*)malloc(N*sizeof(DTYPE))}
#define CHECK_MALLOC(VAR) {if(VAR==NULL){fprintf(stderr, "Out of memory when allocating VAR at LN:%d\n",yylineno );exit(1);}}

Programa* createPrograma( Lista* rep_definicao ) ;
Definicao* createDefinicao( DefTag type, void* definicao ) ;
DefinicaoVariavel* createDefinicaoVariavel ( Type* type, Lista* lista_nomes ) ;
Type* createType ( char isVector, void* type ) ;

DefinicaoFuncao*  createDefinicaoFuncao( Type* type, char* id,
        Lista* parametros, Bloco* bloco ) ;
Bloco* createBloco( Lista* def_variavel, Lista* comandos ) ;

Lista* createLista( void ) ;
//Adiciona um elemento ao final da lista
void addLista( Lista* lst, void* content ) ;
//Remove e retorna um elemento no inicio da lista
void* removeLista ( Lista* lst ) ;
Comando* createComando ( ComandoTag comandoType, void* comando ) ;
ComandoReturn* createComandoReturn( char hasExp, Exp* exp ) ;
ComandoAssignment* createComandoAssignment( Variavel* var, Exp* exp ) ;
ComandoWhile* createComandoWhile( Exp*exp, Comando*comando ) ;
ComandoIf* createComandoIf( Exp* exp, Comando* comando, char hasElse,
                            Comando* comandoElse ) ;
Variavel* createVariavel ( VariavelType type, void* var ) ;
VariavelVector* createVariavelVector ( Exp* id, Exp* index ) ;
ExpBitwise* createExpBitwise( ExpBitwiseTag expBitwiseTag, Exp* exp1,
                              Exp* exp2 ) ;

ExpValue* createExpValue( ExpValueTag expValueTag, void* exp ) ;
ExpComp * createExpComp ( ExpCompTag expCompType, Exp* exp1, Exp* exp2 ) ;
ExpBinary* createExpBinary ( ExpBinaryTag expBinaryTag, Exp* exp1, Exp* exp2 ) ;
ExpUnary* createExpUnary ( ExpUnaryTag expUnaryTag, Exp* exp ) ;
Chamada* createChamada ( char* id, Lista* lista_exp ) ;
Parametro* createParametro ( Type* type, char* id ) ;
Exp * createExp ( ExpTypeTag type, void* exp ) ;
ExpNew * createExpNew ( Type* type, Exp* exp ) ;

#endif
