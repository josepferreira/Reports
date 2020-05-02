#define _GNU_SOURCE

/* Estruturas relevantes para a linguagem e para as querys */
	typedef struct sTipo{
		char* descritor; // nome do tipo
		float percentagem; //percentagem desse tipo na musica
	} TipoS;

	typedef TipoS* Tipo;

	typedef struct lTipo{
		Tipo tipo;
		struct lTipo* proximo;
	} TipoL;

	typedef TipoL* listaTipo;	

	typedef struct sMusica{
		int id;
		char* nome; // nome da musica
		char* autores; // autores da musica
		int ano; // ano da musica
		char* editor; // editores da musica
		char* letra; // letra da musica (pode ser um ficheiro com a letra ou um url também)
		char* estilo; // estilo da musica
		char* url; // url do video da musica
		listaTipo tipos; // lista dos tipos da musica
	} MusicaS;
	
	typedef MusicaS* MEspiritual;

listaTipo consListaTipo(char* desc, float perc, listaTipo l){
	Tipo aux = (Tipo)malloc(sizeof(struct sTipo));
	aux->descritor = strdup(desc);
	aux->percentagem = perc;
	
	listaTipo nova = (listaTipo)malloc(sizeof(struct lTipo));
	nova->tipo = aux;
	nova->proximo = l;

	return nova;
}

MEspiritual consMEspiritual(int id, char* nome, char* autores, int ano, char* editor, char* estilo, char* url, char* letra, listaTipo tipo)
{
  	MEspiritual aux;

  	aux = (MEspiritual)malloc(sizeof(struct sMusica));
	
	aux->id = (int)(id); 	
	aux->nome = strdup(nome);
	aux->autores = strdup(autores);
	aux->ano = (ano);
	aux->editor = strdup(editor);
	aux->letra = strdup(letra);
	aux->estilo = strdup(estilo);
	aux->url = strdup(url);
	aux->tipos = tipo;
  	
	return aux;
}

void imprimeMEspiritual(MEspiritual m){
	char* s;

	printf("-----------------------Musica---------------------\n");

	printf("ID: %d! Nome: %s! Autores: %s! Ano: %d! Editor: %s! Letra: %s! Estilo: %s! Video: %s!\n\n",
		m->id,m->nome,m->autores,m->ano,m->editor,m->letra,m->estilo,m->url);
	
	listaTipo aux = m->tipos;

	printf("Tipos\n");

	while(aux){
		
		printf("Descritor: %s! Percentagem: %f\n",aux->tipo->descritor,aux->tipo->percentagem);
		aux = aux->proximo;
	}	

	printf("-----------------------FimMusica---------------------\n\n");
}


listaTipo atualizaPercentagemTipo(listaTipo tipos, float percentagemTotal){
	listaTipo res = tipos;
	while(tipos){

		tipos->tipo->percentagem /= percentagemTotal;
		tipos = tipos->proximo;
	}

	return res;
}


/* Estrutura para os nodos do grafo que se aproximam do que o utilizador quer */

/* Entre 65 e 100 por cento, em intervalos de 5% (7 intervalos) */
	typedef struct musLista{
		MEspiritual musica;
		float aproximacao;
		struct musLista* proxima;	
	} *listaMusicas;

	typedef struct musArvore{

		listaMusicas musicas;
		float limiteInferior;
		float limiteSuperior;
		struct musArvore* esquerda;
		struct musArvore* direita;
		int numero;
	} *arvoreMusicas;


listaMusicas consListaMusicas(MEspiritual m, float perc, listaMusicas l){
	listaMusicas aux = (listaMusicas)malloc(sizeof(struct musLista));
	
	aux->musica = m;
	aux->aproximacao = perc;
	aux->proxima = l;

	return aux;
}

arvoreMusicas iniciaArvoreMusica(){
	arvoreMusicas aux1;

  	aux1 = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	aux1->musicas = NULL;
  	aux1->limiteInferior = 0.65;
  	aux1->limiteSuperior = 0.7;
  	aux1->esquerda = NULL;
  	aux1->direita = NULL;
  	aux1->numero = 0;

  	arvoreMusicas aux2;

  	aux2 = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	aux2->musicas = NULL;
  	aux2->limiteInferior = 0.75;
  	aux2->limiteSuperior = 0.8;
  	aux2->esquerda = NULL;
  	aux2->direita = NULL;
  	aux2->numero = 0;

  	arvoreMusicas aux3;

  	aux3 = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	aux3->musicas = NULL;
  	aux3->limiteInferior = 0.7;
  	aux3->limiteSuperior = 0.75;
  	aux3->esquerda = aux1;
  	aux3->direita = aux2;
  	aux3->numero = 0;

  	arvoreMusicas aux4;

  	aux4 = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	aux4->musicas = NULL;
  	aux4->limiteInferior = 0.85;
  	aux4->limiteSuperior = 0.9;
  	aux4->esquerda = NULL;
  	aux4->direita = NULL;
	aux4->numero = 0;

  	arvoreMusicas aux5;

  	aux5 = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	aux5->musicas = NULL;
  	aux5->limiteInferior = 0.95;
  	aux5->limiteSuperior = 1.1;
  	aux5->esquerda = NULL;
  	aux5->direita = NULL;
  	aux5->numero = 0;

  	arvoreMusicas aux6;

  	aux6 = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	aux6->musicas = NULL;
  	aux6->limiteInferior = 0.9;
  	aux6->limiteSuperior = 0.95;
  	aux6->esquerda = aux4;
  	aux6->direita = aux5;
  	aux6->numero = 0;
  	

  	arvoreMusicas res;

  	res = (arvoreMusicas)malloc(sizeof(struct musArvore));
  	res->musicas = NULL;
  	res->limiteInferior = 0.8;
  	res->limiteSuperior = 0.85;
  	res->esquerda = aux3;
  	res->direita = aux6;
  	res->numero = 0;


  	return res;

}


arvoreMusicas adicionaArvoreMusica(arvoreMusicas atual,char* id,char* nome,char* autores,char* ano,char* editor,char* letra,char* estilo,char* url,listaTipo tipos, float percentagem){

	arvoreMusicas res = atual;

	MEspiritual me = consMEspiritual(atoi(id),nome,autores,atoi(ano),editor,estilo,url,letra,tipos);

	while(res){
		if(percentagem < res->limiteInferior){
			res = res->esquerda;
		}

		else{

			if(percentagem >= res->limiteSuperior){

				res = res->direita;
			}

			else{

				res->musicas = consListaMusicas(me,percentagem,res->musicas);
				res->numero++;
				break;
			}
		}
	}

	return atual;
}

void imprimeArvore(arvoreMusicas arv){


	if(arv == NULL) return;


	imprimeArvore(arv->esquerda);


	printf("Nodo: Máximo: %f! Mínimo: %f! QUANTOS? %d\n",arv->limiteSuperior,arv->limiteInferior,arv->numero);

	listaMusicas aux = arv->musicas;

	while(aux){

		printf("Musica: %d %s, perc: %f\n", aux->musica->id,aux->musica->nome,aux->aproximacao);

		aux = aux->proxima;
	}

	imprimeArvore(arv->direita);
}