#define _GNU_SOURCE
#include <stdio.h>
#include <mysql/mysql.h>
#include <stdlib.h>  
#include "gerarGrafo.c"


#define HOST "localhost"
#define USER "root"
#define PASS "1234"
#define DB "MusicaPL"

arvoreMusicas arvoreMusica = NULL;

void adicionaBD(MEspiritual m)
{

   MYSQL conexao; 
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
  
   int conta; //Contador comum
	char *query;
	asprintf(&query,"INSERT INTO Musica VALUES (NULL,'%s','%s','%d','%s','%s','%s','%s');",m->nome,m->autores,m->ano,m->editor,m->letra,m->estilo,m->url);

	
			listaTipo tipos = m->tipos;
			while(tipos){
				
				asprintf(&query,"%sINSERT INTO Tipo VALUES ('%s','%f',(SELECT id FROM Musica ORDER BY id DESC LIMIT 1));",query,tipos->tipo->descritor,tipos->tipo->percentagem);
				tipos = tipos->proximo;
			}

   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

        
           //passa os dados dos campos para a variável campos
           //escreve na tela os nomes dos campos dando
           //um tab somente
           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		          //enquanto retonrnar registros, conta até o
		          //número de colunas que a tabela tem e escreve na
		          //tela com um tab, depois pula a linha e tenta
		          //pegar outro registro
		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++)
		                printf("%s\t",linhas[conta]);
		             printf("\n");
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

   
}


int verificaDescritorTipo(char* descritor){
	//aqui vamos aceder onde temos a informação dos tipos (por exemplo BD) e vamos verificar se esse tipo existe	
	
   MYSQL conexao; 
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   int res = 0;
  
   int conta; //Contador comum
	char *query;
	asprintf(&query,"SELECT EXISTS(SELECT * FROM Descritores WHERE pai='%s' OR filho='%s')",descritor,descritor);
   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

        
           //passa os dados dos campos para a variável campos
           //escreve na tela os nomes dos campos dando
           //um tab somente
           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		          //enquanto retonrnar registros, conta até o
		          //número de colunas que a tabela tem e escreve na
		          //tela com um tab, depois pula a linha e tenta
		          //pegar outro registro
		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++){
		                printf("%s\t",linhas[conta]);
		            	res = atoi(linhas[conta]);
		            }
		             printf("\n");
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

   return res;
}

int verificaEstilo(char* descritor){
	//aqui vamos aceder onde temos a informação dos estilos (por exemplo BD) e vamos verificar se esse estilo existe	
	
 	MYSQL conexao; 
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   int res = 0;
  
   int conta; //Contador comum
	char *query;
	asprintf(&query,"SELECT EXISTS(SELECT * FROM Estilo WHERE idEstilo='%s')",descritor);
   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

        
           //passa os dados dos campos para a variável campos
           //escreve na tela os nomes dos campos dando
           //um tab somente
           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		          //enquanto retonrnar registros, conta até o
		          //número de colunas que a tabela tem e escreve na
		          //tela com um tab, depois pula a linha e tenta
		          //pegar outro registro
		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++){
		                printf("%s\t",linhas[conta]);
		            	res = atoi(linhas[conta]);
		            }
		             printf("\n");
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

   return res;
}

char* listaTipos(listaTipo l){

	MYSQL conexao; 
	MYSQL_RES *resp;
	MYSQL_ROW linhas;
	MYSQL_FIELD *campos;
	//int res = 0;
  	char* res = "";
	int conta; //Contador comum
	listaTipo aux = l;
	char *query;
	while(aux){
		asprintf(&query,"SELECT filho FROM Descritores WHERE pai='%s';",aux->tipo->descritor);
		aux = aux->proximo;
	}

	
   	mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		         
		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++){
		                printf("%s\t",linhas[conta]);
		            	asprintf(&res,"%s'%s',",res,linhas[conta]);
		            }
		             printf("\n");
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

   res[strlen(res)-1] = '\0';

   return res;

}

listaTipo daTiposMusica(char* id){
	listaTipo res = NULL;

	MYSQL conexao; 
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   //int res = 0;
  
   int conta; //Contador comum
	char *query;
	asprintf(&query,"SELECT descritor,percentagem FROM Tipo WHERE Musica='%s'",id);
   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++){
		                printf("%s\t",linhas[conta]);
		            	
		            }
		             printf("\n");
		             res = consListaTipo(linhas[0],atof(linhas[1]),res);
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

   return res;
}

float percentagemDescritores(char* pai, char* filho){

	MYSQL conexao; 
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   float res = 0;
  
   int conta; //Contador comum
	char *query;
	asprintf(&query,"SELECT percentagem FROM Descritores WHERE pai='%s' AND filho='%s'",pai,filho);
   mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++){
		                printf("%s\t",linhas[conta]);
		            	res = atof(linhas[conta]);
		            }
		             printf("\n");
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

   return res;
}

float selecaoMusica(listaTipo tipos, listaTipo estados){
	/* extrai da BD as musicas que contem aqueles tipos 
		depois para cada musica:
			para cada estado de esrpirito:
				vê a relacao dos descritores com esse estado
				para cada descritor:
					vê a relacao das musicas com esse descritor e atualiza valor 
					a percentagem de acerto
*/


	listaTipo auxTipo = tipos;
	listaTipo auxEstados = estados;

	float percentagem = 0;
	while(auxTipo){

		while(auxEstados){

			float auxPer = percentagemDescritores(auxEstados->tipo->descritor,auxTipo->tipo->descritor);
			
			
			percentagem += (auxPer * (auxTipo->tipo->percentagem/100.0f) * auxEstados->tipo->percentagem);
			auxEstados = auxEstados->proximo;
		}

		auxTipo = auxTipo->proximo;
		auxEstados = estados;
	}

	

	return (percentagem > 1 ? 1 : percentagem);
}

void criaPedido(char* nome, listaTipo tipos){
	

	arvoreMusica = iniciaArvoreMusica();
	

	MYSQL conexao; 
   MYSQL_RES *resp;
   MYSQL_ROW linhas;
   MYSQL_FIELD *campos;
   int res = 0;
  	
  	char* lista = listaTipos(tipos);
	int conta; //Contador comum
	char *query;
	asprintf(&query,"SELECT DISTINCT * FROM Musica INNER JOIN (SELECT Musica FROM Tipo  WHERE Tipo.descritor IN (%s)) AS Ti ON Musica.id=Ti.Musica",lista);
	
	mysql_init(&conexao);
   if (mysql_real_connect(&conexao,HOST,USER,PASS,DB,0,NULL,CLIENT_MULTI_STATEMENTS))
   {
      printf("Conectado com Sucesso!\n");
      if (mysql_query(&conexao,query))
         printf("Erro: %s\n",mysql_error(&conexao));
      else
      {
			
		int status = 0;
        while (status==0) //se houver consulta
		{
         resp = mysql_store_result(&conexao);//recebe a consulta

           if(resp){
				campos = mysql_fetch_fields(resp);
		       for (conta=0;conta<mysql_num_fields(resp);conta++) {
		          printf("%s",(campos[conta]).name);
		          if (mysql_num_fields(resp)>1)
		              printf("\t");
		          }
		     
		          printf("\n");   

		          
		          while ((linhas=mysql_fetch_row(resp)) != NULL)
		          {
		             for (conta=0;conta<mysql_num_fields(resp);conta++){
		                printf("%s\t",linhas[conta]);
		            	
		            }
		            
		            listaTipo lMusica = daTiposMusica(linhas[0]);
		            
		            float percentagemAcerto = selecaoMusica(lMusica,tipos);
		            if(percentagemAcerto >= 0.65){

		            	arvoreMusica = adicionaArvoreMusica(arvoreMusica,linhas[0],linhas[1],linhas[2],linhas[3],linhas[4],linhas[5],linhas[6],linhas[7],tipos, percentagemAcerto);
		            }
		            printf("\n");
		          }
					mysql_free_result(resp);//limpa a variável do resultado: resp
				}
			else{
				//break; 
			}
			status = mysql_next_result(&conexao);
          }
          
        }
        mysql_close(&conexao);
   }
   else 
   {
      printf("Conexao Falhou\n");
      if (mysql_errno(&conexao))
         printf("Erro %d : %s\n", mysql_errno(&conexao), mysql_error(&conexao));
   }

	//cria um pedido com o nome da pagina

	/* para cada estado de esirito do cliente (tipo) vai à B 
	para cada musica que contenha um desses estados e para cada 
	estado de espirito da musica faz a combinacao */

	imprimeArvore(arvoreMusica);

	int auy = criaGrafo(arvoreMusica,nome);


}