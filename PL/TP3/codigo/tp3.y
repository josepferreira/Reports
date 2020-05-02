%{
	#define _GNU_SOURCE
	#include<stdio.h>
	#include<math.h>
	#include<string.h>
	#include<stdlib.h>
	#include<time.h>
	#include "ligarMysql.c"
	#include "tp3.h"


	char* nomePagina = "pedido";
	int pedido = 0;

	time_t rawtime;
	



float totalPercentagem = 0;
%}



%union {
	float n;
	char* c;
	listaTipo tipos;
	MEspiritual musica;
}

%token <n> num
%token <c> string
%token <c> url

%type <musica> Musica;
%type <tipos> Tipo Pedido;
%type <c> Video Editor Estilo Autores Nome Autor Descritor Letra;
%type <n> ID Ano Percentagem


%%

Musiteca: Musicas '<' '/' '/' '>' Pedidos
	;

Musicas: Musica ';' Musicas {}
	  | Musica {}
	;

Musica: ID':' Nome '|' Autores '|' Ano '|' Editor '|' Letra '|' Estilo '|' Tipo '|' Video 
{ 		
		if(totalPercentagem != 100){
			printf("ERRO: percentagem != 100\n");
			yyerror("erro na percentagem do tipo");
			return 0;
			
		}
		$$ = consMEspiritual($1,$3,$5,$7,$9,$13,$17,$11,$15);
		imprimeMEspiritual($$);
		adicionaBD($$);
}
	;

Nome: string Nome { asprintf(&$$,"%s %s", $1, $2); }
	| string { asprintf(&$$, "%s", $1);  }
	;

Autores: Autor { asprintf(&$$,"%s", $1);  }
	| Autor ';' Autores { asprintf(&$$,"%s ; %s", $1, $3); }
	;

Autor: string Autor { asprintf(&$$,"%s %s", $1, $2); }
	| string { asprintf(&$$,"%s", $1); }
	;

Editor: string Editor { asprintf(&$$,"%s %s", $1, $2); }
	| string { asprintf(&$$,"%s", $1);  }
	;

Letra: url { $$ = strdup($1); }
	;

Ano: num { $$ = $1;
	if((((int)$$)-1900) > localtime(&rawtime)->tm_year){
		yyerror("Ano errado!");
		return 0;
	} 
}
	;

Estilo: string { $$ = strdup($1); if(!verificaEstilo($1)){
				printf("ERRO: estilo\n");
				yyerror("erro no estilo, é inexistente");
				return 0;
			}  }
	;

Tipo: '{' Descritor ',' Percentagem '}' ';' Tipo { 
				totalPercentagem += $4;
				if(!verificaDescritorTipo($2)){
					printf("ERRO: descritor\n");
					yyerror("erro no descritor, é inexistente");
					return 0;	
				} 
				$$ = consListaTipo($2,$4,$7);			
			}
	| '{' Descritor ',' Percentagem '}' { 
			totalPercentagem = $4; 
			/* podiamos logo verificar aqui as percentagens */
			if(!verificaDescritorTipo($2)){
				printf("ERRO: descritor\n");
				yyerror("erro no descritor, é inexistente");
				return 0;
				
			} 
			$$ = consListaTipo($2,$4,NULL); 
		}
	;

Descritor: string { $$ = strdup($1);  }
	;

Percentagem: num { $$ = $1;  }
	;

Video: url { $$ = strdup($1);  }
	;

ID: num {  $$ = $1; }
	;

Pedidos: PedidoAux ';' Pedidos
	| { }
	;

PedidoAux: Pedido { pedido++;$1=atualizaPercentagemTipo($1,totalPercentagem); char* aux; asprintf(&aux,"%s%d",nomePagina,pedido); criaPedido(aux,$1);}
	;

Pedido: '{' Descritor ',' Percentagem '}' ',' Pedido { 
				totalPercentagem += $4;
				
				if(!verificaDescritorTipo($2)){
					printf("ERRO: descritor do estado de espirito do cliente\n");
					yyerror("erro no descritor do estado de espirito do cliente, é inexistente");
					return 0;
				} 
				
				$$ = consListaTipo($2,$4,$7);
						
			}
	| '{' Descritor ',' Percentagem '}' {
			totalPercentagem = $4; 
			/* podiamos logo verificar aqui as percentagens */
			if(!verificaDescritorTipo($2)){
				printf("ERRO: descritor do estado de espirito do cliente\n");
				yyerror("erro no descritor do estado de espirito do cliente, é inexistente");
				return 0;
			} 
			$$ = consListaTipo($2,$4,NULL); 
		}
	;

%%
#include "lex.yy.c"

int yyerror(char* s){
	printf("Erro sintático: %s! %s\n",s,yytext);
	return 0;
}

int main(){
	time( &rawtime );
	yyparse();
	return 0;
}
