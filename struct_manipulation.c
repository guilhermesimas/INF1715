#include "struct_manipulation.h"
#include "tree_structure.h"

#include <stdlib.h>
#include <stdio.h>

Programa* createPrograma( Lista* rep_definicao ) {
	Programa* prog = MALLOC( 1, Programa );
	CHECK_MALLOC( prog );

	prog->rep_definicao = rep_definicao;
	return prog;
}
Definicao* createDefinicao( DefTag type, void* definicao ) {
	Definicao* def = MALLOC( 1, Definicao );
	CHECK_MALLOC( def );
	def->definicaoType = type;
	def->definicao = definicao;
	return def;
}
DefinicaoVariavel* createDefinicaoVariavel ( Type* type, Lista* lista_nomes ) {
	DefinicaoVariavel* defVar = MALLOC( 1, DefinicaoVariavel );
	CHECK_MALLOC( defVar );
	defVar->type = type;
	defVar->lista_nomes = lista_nomes;
	return defVar;
}
Type* createType ( char isVector, void* type ) {
	Type* ptype = MALLOC( 1, Type );
	CHECK_MALLOC( ptype );
	ptype->isVector = isVector;
	ptype->type = type;
	return ptype;
}

DefinicaoFuncao*  createDefinicaoFuncao( Type* type, char* id,
        Lista* parametros, Bloco* bloco ) {
	DefinicaoFuncao* defFunc = MALLOC( 1, DefinicaoFuncao );
	CHECK_MALLOC( defFunc );
	defFunc->type = type;
	defFunc->id = id;
	defFunc->parametros = parametros;
	defFunc->bloco = bloco;
	return defFunc;
}
Bloco* createBloco( Lista* def_variavel, Lista* comandos ) {
	Bloco* bloco = MALLOC( 1, Bloco );
	CHECK_MALLOC( bloco );
	bloco->def_variavel = def_variavel;
	bloco->comandos = comandos;
	return bloco;
}

Lista* createLista( void ) {
	Lista* lst = MALLOC( 1, Lista );
	CHECK_MALLOC( lst );
	lst->n = 0;
	lst->head = NULL;
	lst->tail = NULL;
	return lst;
}
//Adiciona um elemento ao final da lista
void addLista( Lista* lst, void* content ) {
	Element* elem = MALLOC( 1, Element );
	CHECK_MALLOC( elem );
	elem->content = content;
	elem->next = NULL;
	if ( lst->head == NULL ) {
		lst->head = elem;
		lst->tail = elem;
		return;
	}
	lst->tail->next = elem;
	lst->tail = elem;
	lst->n = lst->n + 1;
}
//Remove e retorna um elemento no inicio da lista
void* removeLista ( Lista* lst ) {
	if ( lst == NULL ) {
		return NULL;
	}
	Element* elem = lst->head;
	lst->head = lst->head->next;
	if ( elem == NULL ) {
		return NULL;
	}
	lst->n = lst->n - 1;
	return elem->content;
}
Comando* createComando ( ComandoTag comandoType, void* comando ) {
	Comando* com = MALLOC( 1, Comando );
	CHECK_MALLOC( com );
	com->comandoType = comandoType;
	com->comando = comando;
	return com;
}
ComandoReturn* createComandoReturn( char hasExp, Exp* exp ) {
	ComandoReturn* comret = MALLOC( 1, ComandoReturn );
	CHECK_MALLOC( comret );
	comret->hasExp = hasExp;
	comret->exp = exp;
	return comret;
}
ComandoAssignment* createComandoAssignment( Variavel* var, Exp* exp ) {
	ComandoAssignment* comass = MALLOC( 1, ComandoAssignment );
	CHECK_MALLOC( comass );
	comass->var = var;
	comass->exp = exp;
	return comass;
}
ComandoWhile* createComandoWhile( Exp*exp, Comando*comando ) {
	ComandoWhile* comwhile = MALLOC( 1, ComandoWhile );
	CHECK_MALLOC( comwhile );
	comwhile->exp = exp;
	comwhile->comando = comando;
	return comwhile;
}
ComandoIf* createComandoIf( Exp* exp, Comando* comando, char hasElse,
                            Comando* comandoElse ) {
	ComandoIf* comif = MALLOC( 1, ComandoIf );
	CHECK_MALLOC( comif );
	comif->exp = exp;
	comif->comando = comando;
	comif->hasElse = hasElse;
	comif->comandoElse = comandoElse;
	return comif;
}
Variavel* createVariavel ( VariavelType type, void* var ) {
	Variavel* variavel = MALLOC( 1, Variavel );
	CHECK_MALLOC( variavel );
	variavel->type = type;
	variavel->var = var;
	return variavel;
}
VariavelVector* createVariavelVector ( Exp* id, Exp* index ) {
	VariavelVector* varvec = MALLOC( 1, VariavelVector );
	CHECK_MALLOC( varvec );
	varvec->id = id;
	varvec->index = index;
	return varvec;
}
ExpBitwise* createExpBitwise( ExpBitwiseTag expBitwiseTag, Exp* exp1,
                              Exp* exp2 ) {
	ExpBitwise* expbit = MALLOC( 1, ExpBitwise );
	CHECK_MALLOC( expbit );
	expbit->expBitwiseTag = expBitwiseTag;
	expbit->exp1 = exp1;
	expbit->exp2 = exp2;
	return expbit;
}

ExpValue* createExpValue( ExpValueTag expValueTag, void* exp ) {
	ExpValue* expval = MALLOC( 1, ExpValue );
	CHECK_MALLOC( expval );
	expval->expValueType = expValueTag;
	expval->exp = exp;
	return expval;
}
ExpComp * createExpComp ( ExpCompTag expCompType, Exp* exp1, Exp* exp2 ) {
	ExpComp* expcomp = MALLOC( 1, ExpComp );
	CHECK_MALLOC( expcomp );
	expcomp->expCompTag = expCompType;
	expcomp->exp1 = exp1;
	expcomp->exp2 = exp2;
	return expcomp;
}
ExpBinary* createExpBinary ( ExpBinaryTag expBinaryTag, Exp* exp1, Exp* exp2 ) {
	ExpBinary* expbin = MALLOC( 1, ExpBinary );
	CHECK_MALLOC( expbin );
	expbin->expBinaryTag = expBinaryTag;
	expbin->exp1 = exp1;
	expbin->exp2 = exp2;
	return expbin;
}
ExpUnary* createExpUnary ( ExpUnaryTag expUnaryTag, Exp* exp ) {
	ExpUnary* expun = MALLOC( 1, ExpUnary );
	CHECK_MALLOC( expun );
	expun->expUnaryTag = expUnaryTag;
	expun->exp = exp;
	return expun;
}
Chamada* createChamada ( char* id, Lista* lista_exp ) {
	Chamada* chamada = MALLOC( 1, Chamada );
	CHECK_MALLOC( chamada );
	chamada->id = id;
	chamada->lista_exp = lista_exp;
	return chamada;
}
Parametro* createParametro ( Type* type, char* id ) {
	Parametro* par = MALLOC( 1, Parametro );
	CHECK_MALLOC( par );
	par->type = type;
	par->id = id;
	return par;
}
Exp * createExp ( ExpTypeTag type, void* exp ) {
	Exp* expr = MALLOC( 1, Exp );
	CHECK_MALLOC( expr );
	expr->expType = type;
	expr->exp = exp;
	return expr;
}
ExpNew * createExpNew ( Type* type, Exp* exp ) {
	ExpNew * expnew = MALLOC( 1, ExpNew );
	CHECK_MALLOC( expnew );
	expnew->type = type;
	expnew->exp = exp;
	return expnew;
}
