#ifndef _TREE_STRUCTURE_
#define _TREE_STRUCTURE_

#include"y.tab.h"

extern int yylineno;

typedef struct element Element;

typedef struct element {
	void* content;
	Element* next;
} Element;

typedef struct {
	int n;
	Element* head;
	Element* tail;
} Lista;


typedef struct {
	char* id;
	Lista* lista_exp;
} Chamada;

typedef enum {
	VALUE,
	STRING,
	VAR,
	CHAMADA,
	NEW,
	UNARY,
	BINARY,
	COMP,
	BOOLEAN,
} ExpTypeTag;

typedef struct {
	ExpTypeTag expType;
	void* exp;
} Exp;

typedef struct {
	char isVector;
	void* type;
} Type;

typedef struct {
	Type* type;
	Exp* exp;
} ExpNew;

typedef enum {
	E_INT,
	E_FLOAT
} ExpValueTag;

typedef struct {
	ExpValueTag expValueType;
	void* exp;
} ExpValue;

typedef enum {
	MINUS,
	NOT
} ExpUnaryTag;

typedef struct {
	ExpUnaryTag expUnaryTag;
	Exp* exp;
} ExpUnary;

typedef enum {
	ADD,
	SUB,
	MUL,
	DIV
} ExpBinaryTag;

typedef struct {
	ExpBinaryTag expBinaryTag;
	Exp* exp1;
	Exp* exp2;
} ExpBinary;

typedef enum {
	EQ,
	LESS_EQ,
	GREATER_EQ,
	LESS,
	GREATER
} ExpCompTag;

typedef struct {
	ExpCompTag expCompTag;
	Exp* exp1;
	Exp* exp2;
} ExpComp;

typedef enum {
	AND,
	OR
} ExpBitwiseTag;

typedef struct {
	ExpBitwiseTag expBitwiseTag;
	Exp* exp1;
	Exp* exp2;
} ExpBitwise;

typedef enum {
	VECTOR,
	NORMAL
} VariavelType;

typedef struct {
	Exp* id;
	Exp* index;
} VariavelVector;

typedef struct {
	VariavelType type;
	void* var;
} Variavel;

typedef enum {
	IF_ELSE,
	WHILE,
	ASSIGNMENT,
	RETURN,
	C_CHAMADA,
	BLOCO
} ComandoTag;

typedef struct {
	ComandoTag comandoType;
	void* comando;
} Comando;

typedef struct {
	Exp* exp;
	Comando* comando;
	char hasElse;
	Comando* comandoElse;
} ComandoIf;

typedef struct {
	Exp* exp;
	Comando* comando;
} ComandoWhile;

typedef struct {
	Variavel* var;
	Exp* exp;
} ComandoAssignment;

typedef struct {
	char hasExp;
	Exp* exp;
} ComandoReturn;

// typedef struct {
// 	Chamada* chamada;
// } ComandoChamada;

// typedef struct {
// 	Bloco* bloco;
// } ComandoBloco;


typedef struct {
	Lista* def_variavel;
	Lista* comandos;
} Bloco;

typedef struct {
	Type* type;
	char* id;
} Parametro;

typedef struct {
	Type* type;
	char* id;
	Lista* parametros;
	Bloco* bloco;
} DefinicaoFuncao;

typedef enum {
	T_INT = TK_INT,
	T_CHAR = TK_CHAR,
	T_FLOAT = TK_FLOAT,
	T_VOID = TK_VOID
} TypeTag;


typedef struct {
	Type* type;
	Lista* lista_nomes;
} DefinicaoVariavel;

typedef enum {
	DEF_VAR,
	DEF_FUNC
} DefTag;

typedef struct {
	DefTag definicaoType;
	void* definicao;
} Definicao;

typedef struct {
	Lista *rep_definicao;
} Programa;

#endif