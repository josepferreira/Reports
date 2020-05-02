%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
%}

%x LISTA NEGRITO ITALICO SUBLINHADO CABECALHO DICIONARIO ELEMENTO TABELA

%option stack

%%


#T# {
	printf("\\begin{table}");
	yy_push_state(TABELA);
}


<*>\\[*_&#$] {printf("%s",yytext);}

<CABECALHO>\$ {
	printf("}");
	
		yy_pop_state();

}

<NEGRITO>\*	{
		printf("}");
		
			yy_pop_state();
	
	}

<ITALICO>& {

		printf("}");

	
	
			yy_pop_state();
	}

<SUBLINHADO>_ {

		printf("}");
			yy_pop_state();

}

<LISTA>#	{

		printf("\\item");
}

<LISTA>#FO#	{
	printf("\\end{enumerate}");
	yy_pop_state();
}

<LISTA>#FN#	{
	printf("\\end{itemize}");
	yy_pop_state();
}

<DICIONARIO>#\[[^#*_&]+\]	{

		printf("\\item%s",yytext+1);
		
}

<DICIONARIO>#FD#	{
	printf("\\end{description}");
	yy_pop_state();
}

<TABELA>\\\> {printf(">");}

<TABELA>\>C {printf("\\centering");}

<TABELA>\>L {printf("\\caption{");}

<TABELA>\>FL {printf("}");}

<TABELA>\| {printf("&");}

<TABELA>\\\| {printf("|");}

<TABELA># {printf("\\\\");}

<TABELA>#FT# { printf("\\end{table}"); yy_pop_state();}

$+	{
	int tam = strlen(yytext);
	switch(tam){
		case 1: printf("\\chapter{"); break;
		case 2: printf("\\section{"); break;
		case 3: printf("\\subsection{"); break;
		default: printf("\\subsubsection{");
	}
	yy_push_state(CABECALHO);
}

<*>\*	{ 
		printf("\\textbf{");
		yy_push_state(NEGRITO);
 
		}

<*>&	{ 
		printf("\\textit{");
		yy_push_state(ITALICO);


}

<*>_ { 

		printf("\\underline{");
		yy_push_state(SUBLINHADO);

}

<*>#O# { 
		printf("\\begin{enumerate}");
		yy_push_state(LISTA);
}

<*>#N# { 
		printf("\\begin{itemize}");
		yy_push_state(LISTA);
}

<*>#D# {
		printf("\\begin{description}");
		yy_push_state(DICIONARIO);
}


%%

int yywrap(){
	return 1;
}

int main(int argc, char** argv) {
	
	yylex();
	

	return 0;
}
