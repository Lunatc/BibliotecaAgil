#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

int num_livros = 0;

//Lista encadeada de livros
typedef struct livro{
  int codigo;
  char nome[100];
  char autor[50];
  int ano;
  char status[50];
  char emprestado_p[50];
  struct livro *prox;
}livro;

//Função para ler livros disponíveis
void Disponiveis(livro *l){
  livro *aux;
  aux = l;

  if(l == NULL)
    printf("Não ha livros disponiveis.\n");
  
  else{
    while(aux != NULL){
    	if(strcmp(aux->status,"Disponivel") == 0){
	      printf("Código:%d\n",aux->codigo);
	      printf("Título: %s\n",aux->nome);
	      printf("Autor:%s\n",aux->autor);
	      printf("Ano:%d\n",aux->ano);
	      aux = aux->prox;
	      printf("\n");
	    }
	    else
	    	aux = aux->prox;
    }
  }
}

//Função para retirar um livro
void Retira(livro *l){
	  livro *aux, *anterior;
	  aux = l;
	  int cod, linha = 0;
	  char aux_nome[50], pessoa[50], temp[] = "temp.txt";
	  char str[256];
	
	  printf("Você pode retirar um dos seguintes livros:\n\n");
	  Disponiveis(l);
	
	  if(l == NULL)
	    printf("Portanto não é possível retirar nenhum livro.\n");
	
	  else{
	    printf("\nDigite o código do livro que gostaria de retirar:\n");
	    scanf("%d",&cod);
	
		while(aux != NULL){
			if(cod == aux->codigo){
				break;	
			}
			else aux = aux->prox;
		}
		
		if(aux == NULL)
			printf("Livro não encontrado.\n");
		
		if(strcmp(aux->status, "Indisponivel") == 0 ){
			printf("Este livro não está disponível.\n");
		}
		
		else{
			
			printf("Digite o nome da pessoa que deseja reservar o livro:\n");
			fflush(stdin);
			scanf("%[^\n]",pessoa);
			fflush(stdin);
			sprintf(aux_nome, "%d", cod);
			strcat(aux_nome, ".txt");
					
			FILE *filelivros, *filelivros2;
		
			filelivros = fopen(aux_nome, "r");
		
			if(!filelivros){
                printf("Não foi possível abrir o arquivo\n");
        	}
        
        	filelivros2 = fopen(temp,"w");
       		if(!filelivros2){
                printf("Não foi possível abrir o arquivo\n");
                fclose(filelivros);
        	}
        
       		while(!feof(filelivros)){
	           	strcpy(str, "\0");
	           	
	            fgets(str, 50, filelivros);
				fprintf(filelivros2, "%s", str);
				
				fgets(str,256, filelivros);
				fprintf(filelivros2, "%s", str);
				
				fgets(str,256, filelivros);
				fprintf(filelivros2, "%s", str);
				
				fgets(str,256, filelivros);
				fprintf(filelivros2, "%s", str);
				
				fgets(str, 50, filelivros);
				strcpy(aux->status,"Indisponivel");
				fprintf(filelivros2, "%s\n", "Indisponivel");
				
				fgets(str, 50, filelivros);
				fprintf(filelivros2, "%s", pessoa);
	        }
        
	        fclose(filelivros);
	        fclose(filelivros2);
	        remove(aux_nome);
	        rename(temp, aux_nome);
	        printf(" Livro reservado com sucesso! \n");
	  	}  
	}
}

//Função para doar um livro
livro *Doar(livro *l){
  livro *novo, *inicio, *fim;
  char aux_nome[50];

  sprintf(aux_nome, "%d", num_livros);
  strcat(aux_nome, ".txt");
  FILE *filelivros = fopen(aux_nome, "a");

  inicio = l;
  fim = l;

  if(l != NULL){
    while(fim->prox != NULL){
      fim = fim->prox;
    }
  }

  else fim = l;

  //Lista vazia
	if(l == NULL){
	    novo = (livro*) malloc(sizeof(livro));
	
	    novo->codigo = num_livros;
	    fprintf(filelivros, "%d", novo->codigo);
		
		fflush(stdin);
	    printf("Digite o título do livro:\n");
	    scanf("%[^\n]",novo->nome);
	    fflush(stdin);
	    fprintf(filelivros, "\n%s", novo->nome);

				
		printf("Digite o autor do livro:\n");
		scanf("%[^\n]",novo->autor);
	    fflush(stdin);
	    fprintf(filelivros, "\n%s", novo->autor);
	
	    printf("Digite o ano do livro:\n");
	    scanf("%d",&novo->ano);
	    fprintf(filelivros, "\n%d", novo->ano);
		
		strcpy(novo->status,"Disponivel");
	    fprintf(filelivros,"\n%s","Disponivel");
	
		l = novo;
		novo->prox = NULL;
	}

	  //Insere final
	  else{
		novo = (livro*) malloc(sizeof(livro));
	
	    novo->codigo = num_livros;
	
	    fprintf(filelivros, "%d", novo->codigo);
		
		fflush(stdin);
		printf("Digite o titulo do livro:\n");
		scanf("%[^\n]",novo->nome);
		fflush(stdin);
		
	    fprintf(filelivros, "\n%s", novo->nome);
					
					
		printf("Digite o autor do livro:\n");
		scanf("%[^\n]",novo->autor);
	    fprintf(filelivros, "\n%s", novo->autor);
	    
	     printf("Digite o ano do livro:\n");
	    scanf("%d",&novo->ano);
	    fprintf(filelivros, "\n%d", novo->ano);
	    
		strcpy(novo->status,"Disponivel");
	    fprintf(filelivros,"\n%s","Disponivel");
				
		fim->prox = novo;
		novo->prox = NULL;
	}
	  fclose(filelivros);
  return l;
}

//Função para devolver um livro
void Devolve(livro *l){
	livro *aux, *anterior;
	aux = l;
	int cod,linha = 0;
	char aux_nome[50],  temp[] = "temp.txt";
	char str[256];
	
	printf("Você pode retirar um dos seguintes livros:\n\n");
	Disponiveis(l);
	
	if(l == NULL)
		printf("Portanto não é possível retirar nenhum livro.\n");
	
	else{
	    printf("\nDigite o código do livro que gostaria de devolver:\n");
	    scanf("%d",&cod);
	
		while(aux != NULL){
			if(cod == aux->codigo){
				break;	
			}
			else aux = aux->prox;
		}
		
		printf("Código: %d\n",aux->codigo);
		printf("Título: %s\n",aux->nome);
		printf("Autor: %s\n",aux->autor);
		printf("Ano: %d\n",aux->ano);
		printf("Status: %s\n",aux->status);
		printf("Emprestado para: %s", aux->emprestado_p);
		
		sprintf(aux_nome, "%d", cod);
		strcat(aux_nome, ".txt");
		FILE *filelivros, *filelivros2;
		
		filelivros = fopen(aux_nome, "r");
		
		if (!filelivros){
                printf("Não foi possível abrir o arquivo\n");
        }
        
        filelivros2 = fopen(temp,"w");
        if (!filelivros2){
                printf("Não foi possível abrir o arquivo\n");
                fclose(filelivros);
        }
        
       	while(!feof(filelivros)){
            strcpy(str, "\0");
	           	
	        fgets(str, 50, filelivros);
			fprintf(filelivros2, "%s", str);
				
			fgets(str,256, filelivros);
			fprintf(filelivros2, "%s", str);
				
			fgets(str,256, filelivros);
			fprintf(filelivros2, "%s", str);
			
			fgets(str,256, filelivros);
			fprintf(filelivros2, "%s", str);
				
			fgets(str, 50, filelivros);
			strcpy(aux->status,"Disponivel");
			fprintf(filelivros2, "%s", "Disponivel");
				
			fgets(str, 50, filelivros);
			fprintf(filelivros2, "%s", "\0");
        }
        
        fclose(filelivros);
        fclose(filelivros2);
        remove(aux_nome);
        rename(temp, aux_nome);
        printf("\nLivro devolvido com sucesso! \n");
	  }  
}

//Função que adiciona os 3 livros iniciais
livro *livros_inicio(livro *l){
	livro *novo, *inicio, *fim;
	char aux_nome[50];
	FILE *filelivros;
	
	sprintf(aux_nome,"%d",num_livros);
	strcat(aux_nome, ".txt");
	
	filelivros = fopen(aux_nome,"a");
	
	inicio = l;
	fim = l;
  	
  	//Livro Como fazer sentido e bater o martelo

	novo = (livro*) malloc(sizeof(livro));
	
	novo->codigo = num_livros;
	fflush(stdin);
	fprintf(filelivros, "%d", novo->codigo);
		
	strcpy(novo->nome,"Como fazer sentido e bater o martelo");
	fprintf(filelivros, "\n%s", novo->nome);

	strcpy(novo->autor,"Alexandro Aolchique");
	fprintf(filelivros, "\n%s", novo->autor);

	novo->ano = 2017;
	fprintf(filelivros, "\n%d", novo->ano);
	
	strcpy(novo->status,"Disponivel");
	fprintf(filelivros,"\n%s","Disponivel");
	
	l = novo;
	novo->prox = NULL;
	fclose(filelivros);
	
	//Livro Código Limpo
	
	num_livros++;
	sprintf(aux_nome,"%d",num_livros);
	strcat(aux_nome, ".txt");
	
	filelivros = fopen(aux_nome,"a");

	novo = (livro*) malloc(sizeof(livro));
	
	novo->codigo = num_livros;
	
	fprintf(filelivros, "%d", novo->codigo);
		
	strcpy(novo->nome,"Código Limpo");
	fprintf(filelivros, "\n%s", novo->nome);

	strcpy(novo->autor,"Tio Bob");
	fprintf(filelivros, "\n%s", novo->autor);

	novo->ano = 2001;
	fprintf(filelivros, "\n%d", novo->ano);
	
	strcpy(novo->status,"Disponivel");
	fprintf(filelivros,"\n%s","Disponivel");
		
	l->prox = novo;			
	fim = novo;
	novo->prox = NULL;

	fclose(filelivros);
	
	//Livro Basquete 101
	
	num_livros++;
	sprintf(aux_nome,"%d",num_livros);
	strcat(aux_nome, ".txt");
	
	filelivros = fopen(aux_nome,"a");

	novo = (livro*) malloc(sizeof(livro));
	
	novo->codigo = num_livros;
	
	fprintf(filelivros, "%d", novo->codigo);
		
	strcpy(novo->nome,"Basquete 101");
	fprintf(filelivros, "\n%s", novo->nome);

	strcpy(novo->autor,"Hortência Marcari");
	fprintf(filelivros, "\n%s", novo->autor);

	novo->ano = 2010;
	fprintf(filelivros, "\n%d", novo->ano);
	
	strcpy(novo->status,"Disponivel");
	fprintf(filelivros,"\n%s","Disponivel");
				
	fim->prox = novo;
	novo->prox = NULL;
	
	fclose(filelivros);
	num_livros++;
	
	
  return l;
}

livro *leitura_arq(livro *l){
	livro *novo, *inicio, *fim;
	char aux[50], aux_nome[50];
	FILE *filelivros;
	int num = 0;
	
	sprintf(aux_nome,"%d",num);
	strcat(aux_nome, ".txt");
	
	while(1){
		
		if((filelivros = fopen(aux_nome, "r")) != NULL){
			
			inicio = l;
			fim = l;
		
			if(l == NULL){
				novo = (livro*) malloc(sizeof(livro));
				
				fgets(aux, 50, filelivros);
				novo->codigo = atoi(aux);
				
				fgets(novo->nome, 50,filelivros);
				fgets(novo->autor,50, filelivros);
				
				fgets(aux,50, filelivros);
				novo->ano = atoi(aux);
				
				fgets(novo->status,50, filelivros);
				fgets(novo->emprestado_p,50, filelivros);
				
				l = novo;
				novo->prox = NULL;
				num++;
				fclose(filelivros);
			}
			else{
				novo = (livro*)  malloc(sizeof(livro));
				
				fgets(aux, 50, filelivros);
				novo->codigo = atoi(aux);
				
				fgets(novo->nome, 50,filelivros);
				fgets(novo->autor,50, filelivros);
				
				fgets(aux,50, filelivros);
				novo->ano = atoi(aux);
				
				fgets(novo->status,50, filelivros);
				fgets(novo->emprestado_p,50, filelivros);
				
				fim->prox = novo;
				novo->prox = NULL;
				fim = novo;
				num++;
				fclose(filelivros);			
			}
		sprintf(aux_nome,"%d",num);
		strcat(aux_nome, ".txt");
		}
		else{
			break;
		}
	}
		
	
  	return l;
}

int main(){

	setlocale(LC_ALL, "Portuguese");
	
	int op;
	livro *l;
	l = NULL;
	char *nome_arq = "0.txt";
	
	if(!access(nome_arq, F_OK )){
	   printf("Bem vindo ao sistema da Biblioteca do bairro!\n");
	   l = leitura_arq(l);
    }else{
        l = livros_inicio(l);
        printf("Bem vindo ao sistema da Biblioteca do bairro!\n");
    }
	
	while(1){
		    printf("\nMenu: selecione a operação que gostaria de realizar.\n");
		    printf("1-Ver livros disponíveis\n");
		    printf("2-Retirar um livro\n");
		    printf("3-Devolver um livro\n");
		    printf("4-Doar um livro\n");
		    printf("5-Fechar o sistema.\n");
		    printf("Operação:");
		    scanf("%d",&op);
	
		    if(op == 5)
		      break;
		
		    switch(op){
		      case 1:
		        printf("\n");
		        printf("Livros disponíveis:\n");
		        Disponiveis(l);
		        break;
		      
		      case 2:
		        printf("\n");
		        printf("Retirar um livro.\n");
		        Retira(l);
		        break;
		
		      case 3:
		        printf("\n");
		        printf("Devolver um livro.\n");
		        Devolve(l);
		        break;
		
		      case 4:
		        printf("\n");
		        printf("Doar um livro.\n");
		        l = Doar(l);
		        num_livros++;
		        break;
		    }
		  }
	return 0;
}
