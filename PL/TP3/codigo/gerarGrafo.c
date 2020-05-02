#define _GNU_SOURCE
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "Estruturas.c"
#include <time.h>
#include <stdlib.h>



int nodo = 1;
#define PONTOS 300

#define Cor1 "blue"
#define Cor2 "cyan"
#define Cor3 "green4"
#define Cor4 "green"
#define Cor5 "magenta"
#define Cor6 "orange"
#define Cor7 "red"

char* daCor(float raio){

	switch((int)(raio/2.5f)){
		case 1: return Cor1;
		case 2: return Cor2;
		case 3: return Cor3;
		case 4: return Cor4;
		case 5: return Cor5;
		case 6: return Cor6;
		default: return Cor7;
	}
}
void criaGrafoArv(arvoreMusicas arv, double* raio, FILE* f){

	if(arv == NULL) return;


	criaGrafoArv(arv->esquerda,raio,f);
		
	int num = arv->numero;
	double radius = (*raio);
	float alpha = 2*M_PI/(num+1);
	listaMusicas aux = arv->musicas;
	float alfaPontos = (2*M_PI) / (PONTOS);
	double x,y;

	for(int j = 0; j < PONTOS; j++){
		x = cos(alfaPontos*(float)j)*radius;
		y = sin(alfaPontos*(float)j)*radius;
		char* l = "o";
		fprintf(f, "\t%d[label=\"%s\", pos=\"%f,%f!\", shape=\"point\"];\n", nodo++,l,x,y);
	}
	int i = 0;
	
	double ran = ((double)rand()) / (2*M_PI);
	
	ran = ran - (floor(ran));  
	
	while(aux){
		x = cos((alpha*(float)i)+ran)*radius;
		y = sin((alpha*(float)i)+ran)*radius;
		char* urlPag;
		asprintf(&urlPag,"%s.html",aux->musica->nome);
		fprintf(f, "\t%d[label=\"%s:\nAproximacao:%f\", pos=\"%f,%f!\", shape=\"folder\" , color=\"%s\" ,URL=\"%s\"];\n", nodo++,aux->musica->nome,aux->aproximacao,x,y, daCor(radius), urlPag);
		i++;
		aux = aux->proxima;

	}
	x = cos((alpha*(float)i)+ran)*radius;
	y = sin((alpha*(float)i)+ran)*radius;
	fprintf(f, "\t%d[label=\"Maximo:%f\nMinimo:%f\", pos=\"%f,%f!\", color=\"seashell\" , shape=\"box\"];\n", nodo++,arv->limiteSuperior,arv->limiteInferior,x,y);
	

	(*raio) = (*raio)-2;
	
	criaGrafoArv(arv->direita,raio,f);
}



void geraPagina(listaMusicas lm,char* caminho){
	char* fich;
	asprintf(&fich,"%s%s.html",caminho,lm->musica->nome);
	FILE *f = fopen(fich, "w");

	char* nome = strdup(lm->musica->nome);
	char* autores = strdup(lm->musica->autores);
	int ano = lm->musica->ano;
	char* editora = strdup(lm->musica->editor);
	char* letra = strdup(lm->musica->letra);
	char* estilo = strdup(lm->musica->estilo);
	char* musica = strdup(lm->musica->url);
	float acerto = lm->aproximacao;

	fprintf(f, "<html>\n\t<head>\n\t\t<title>Info</title>");

	fprintf(f, "\t<style>\n");
	fprintf(f, "\t\tbody {background-color: powdergray;}\n");
	fprintf(f, "\t\th2   {color: blue;}\n");
	fprintf(f, "\t\tlabel {font-weight: bold;}\n");

	fprintf(f, "\t\t#musicas {\n");
	fprintf(f, "\t\t\tfont-family: \"Trebuchet MS\", Arial, Helvetica, sans-serif;\n");
	fprintf(f, "\t\t\tborder-collapse: collapse;\n");
	fprintf(f, "\t\t\twidth: 20\%;\n\t\t}\n");
	fprintf(f, "\t\t#musicas td, #musicas th {\n");
	fprintf(f, "\t\t\tborder: 1px solid #ddd;\n");
	fprintf(f, "\t\t\tpadding: 8px;\n\t\t}\n");
	fprintf(f, "\t\t#musicas tr:nth-child(even){background-color: #f2f2f2;}\n");
	fprintf(f, "\t\t#musicas tr:hover {background-color: #ddd;}\n");
	fprintf(f, "\t\t#musicas th {\n");
	fprintf(f, "\t\t\tpadding-top: 12px;\n");
	fprintf(f, "\t\t\tpadding-bottom: 12px;\n");
	fprintf(f, "\t\t\ttext-align: left;\n");
	fprintf(f, "\t\t\tbackground-color: #4CAF50;\n");
	fprintf(f, "\t\t\tcolor: white;\n\t\t}\n");
	
	fprintf(f, "\t</style>\n");

	fprintf(f, "\t</head>\n");
	fprintf(f, "\t</body>\n");
	fprintf(f, "\t\t<h2>Informações da Música</h2>\n");

	fprintf(f, "\t\t<table id=\"musicas\">\n");

	//Nome da Musica
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Nome:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a>%s</a>\n", nome);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	//Autores
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Autores:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a>%s</a>\n", autores);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	//Lançamento
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Ano Lançamento:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a>%d</a>\n", ano);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	//Editora
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Editora:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a>%s</a>\n", editora);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	//Letra
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Letra:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a href=\"%s\">Clique Aqui!</a>\n", letra);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	//Estilo
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Estilo:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a>%s</a>\n", estilo);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	//Musica
	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Letra:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a href=\"%s\">Play!</a>\n", musica);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	fprintf(f, "\t\t<tr>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<label>Percentagem Acerto:</label>\n");
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t\t<td>\n");
	fprintf(f, "\t\t\t\t<a>%f</a>\n", acerto);
	fprintf(f, "\t\t\t</td>\n");
	fprintf(f, "\t\t</tr>\n");

	fprintf(f, "\t\t</table>\n");

	fprintf(f, "\t</body>\n");

	fprintf(f, "</html>\n");

	fclose(f);


}

void criaPaginasMusicas(arvoreMusicas arv, char* cam){

	
	if(arv == NULL) return;



	criaPaginasMusicas(arv->esquerda,cam);

	listaMusicas aux = arv->musicas;

	while(aux){
		
		geraPagina(aux,cam);
		aux = aux->proxima;
	}

	criaPaginasMusicas(arv->direita,cam);
}

int criaGrafo(arvoreMusicas arv, char* pasta){

	double x, y;
	double radius = 0;
	srand(time(NULL));
	
	/*har* args[1];
	args[0] = pasta;
	execvp("mkdir",args);
	*/
	char* comando;
	asprintf(&comando,"mkdir %s",pasta);
	system(comando);
	char* pastaC;
	asprintf(&pastaC,"%s/",pasta);

	char* nomeF;
	asprintf(&nomeF,"%scirculoGerado.gv",pastaC);
	FILE *f = fopen(nomeF, "w");
  	fprintf(f, "digraph G {\n\tlayout=\"neato\"\n");
  	fprintf(f, "\tnode [style=\"rounded,filled,bold\"];\n");

	fprintf(f, "\tTU[label=\"O seu estado!\", pos=\"0,0!\", shape=\"star\" color=\"yellow\"];\n");
	
	radius = 17.5;
	criaGrafoArv(arv,&radius,f);
	fprintf(f, "}\n");
	fclose(f);

	char* cmdDot;
	asprintf(&cmdDot,"dot -Tsvg %s -o %scirculoGerado.svg",nomeF,pastaC);
	system(cmdDot);

	asprintf(&cmdDot,"dot -Tpng %s -o %scirculoGerado.png",nomeF,pastaC);
	system(cmdDot);

	char* nomeFicheiroIndex;
	asprintf(&nomeFicheiroIndex, "%sindex.html", pastaC);

	
	FILE* fi = fopen(nomeFicheiroIndex, "w");
	
	fprintf(fi, "<html>\n");
	fprintf(fi, "<body>\n");
	fprintf(fi, "\t<object data=\"circuloGerado.svg\" type=\"image/svg+xml\">\n");
	fprintf(fi, "\t\t<img src=\"circuloGerado.png\" />\n");
	fprintf(fi, "\t</object>\n");
	fprintf(fi, "</body>\n");
	fprintf(fi, "</html>\n");

	fclose(fi);

	criaPaginasMusicas(arv,pastaC);

	return 0;

}

