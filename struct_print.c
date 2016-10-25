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

void printLista( Lista* lst, ( void )( *printFunc )( void* content, int id ),
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
}
void printDefinicaoFuncao( DefinicaoFuncao* deff, int ident );

void printType( Type* type, int ident );
