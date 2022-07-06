/*
Aluno: Vinícius Toni Rocha
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data{
  int dia, mes, ano;
};

struct evento{
  char nome[30];
  int horario_inicio; 
  int horario_fim;
  char local[30];
  struct data cadastro;
};

void scan_data(struct data *v);
void novo_registro(struct evento *v);

void remove_evento(struct evento *v, int n);

void relatorio(struct evento *v, int n);

int verifica_registro(struct evento *v, int n, char *chave);
int acha_posicao(struct evento *v, int n, char *chave);
void print_data(struct evento *v, int i);
void consultar(struct evento *v, int n);

void ordena_eventos(struct evento *v, int n);


int main(){
  struct evento *v = NULL;
  int i, n = 0;
  
  FILE *f = fopen("registro.txt", "rt");

  if(f == NULL){
    printf("Arquivo nao encontrado!\n");
  }else{
    fscanf( f, "%d", &n);
		printf("%d evento(s) registradas.\n", n);
		v = malloc(sizeof(struct evento) * n);
		for( i = 0 ; i < n ; i++ ){
			fscanf(f, " %[^\n]", v[i].nome);
			fscanf(f, " %d%d\n", &v[i].horario_inicio);
      fscanf(f, " %d%d\n", &v[i].horario_fim);
      fscanf(f, " %[^\n]", v[i].local);
			fscanf(f, "%d/%d/%d", &v[i].cadastro.dia, &v[i].cadastro.mes, &v[i].cadastro.ano);
    }
    fclose(f);
  }
    int escolha;
    do{

  printf("\n\t--MENU PRINCIPAL--\n\n");
  printf("[1] Inserir novos registros\n");
  printf("[2] Remover registros existentes\n");
  printf("[3] Exibir todos os eventos!\n");
  printf("[4] Consultar registros\n");
  printf("[5] Ordenar os registros em ordem crescente\n");
  printf("[6] Salvar e Sair\n");
  printf("\nInsira o numero da opcao desejada:\n ");
  scanf("%d", &escolha);

  switch(escolha){

    case 1:
      n++;
			v = realloc(v, sizeof(struct evento) * n);
			printf("\tRegistro do %do evento\n\n", n);
			novo_registro(&v[n-1]);
      break;

    case 2:
      remove_evento(v,n);
      n--;
      v = realloc(v, sizeof(struct evento) * n);
      relatorio(v, n);
      break;

    case 3:
      relatorio(v, n);
      break;

    case 4:
      consultar(v, n);
      break;

    case 5:
      ordena_eventos(v, n);
      relatorio(v,n);
      break;

  }

  }while(escolha != 6);

f = fopen("registro.txt", "wt");
	fprintf(f, "%d\n", n);
	for(i = 0 ; i < n ; i++){
		fprintf(f, "%s\n", v[i].nome);
		fprintf(f, "%d:%d\n", v[i].horario_inicio);
    fprintf(f, "%d:%d\n", v[i].horario_fim);
    fprintf(f, "%s\n", v[i].local);
		fprintf(f, "%d/%d/%d\n", v[i].cadastro.dia, v[i].cadastro.mes, v[i].cadastro.ano);
	}
fclose(f);
free(v);

return 0;
}

void scan_data(struct data *v){
printf("Insira o dia: ");
scanf("%d", &v->dia);
printf("Insira o mes: ");
scanf("%d", &v->mes);
printf("Insira o ano: ");
scanf("%d", &v->ano);
}

void novo_registro(struct evento *v){
printf("Digite o nome do evento: \n");
scanf(" %[^\n]", v->nome);
printf("\nDigite o Horario de Inicio: \n");
scanf("%d%d", &v->horario_inicio);
printf("\nDigite o Horario de Fim: \n");
scanf("%d%d", &v->horario_fim);
printf("\nDigite o local: \n");
scanf(" %[^\n]", v->local);
printf("\nDigite a data do evento!\n\n");
scan_data(&v->cadastro);
}

void remove_evento(struct evento *v, int n){
char chave[20];
int i, pos;

printf("Digite o nome do evento a ser removido: ");
scanf(" %[^\n]", chave);
pos = acha_posicao(v, n, chave);

if (verifica_registro(v, n, chave) == 0 ){
     printf("\nO evento nao esta registrado.\n");
  }else{
    for(i = pos; i < n; i++){
     v[i] = v[i+1];
    }
    printf("Evento %s removido", chave);
  }

}

void relatorio(struct evento *v, int n){
FILE *f = fopen("relatorio.txt","wt");
int i;
char s1[20], s2[20], s3[20];

strcpy(s1, "Nome do Evento");
strcpy(s2, "Horario");
strcpy(s3, "Data do Evento");
fprintf(f, "%-20s%-20s%-20s%-20s\n", s1, s2, s3);
fprintf(f,"----------------------------------------------------------------------------\n");
for(i = 0; i < n; i++){
fprintf(f, "%-20s ", v[i].nome);
fprintf(f, "%d:%dh ate %d:%dh\n", v[i].horario_inicio, v[i].horario_fim);
fprintf(f, "%d/%d/%d\n", v[i].cadastro.dia, v[i].cadastro.mes, v[i].cadastro.ano);
}
fclose(f);
system("relatorio.txt");
}

int verifica_registro(struct evento *v, int n, char *chave){
int i, cont = 0;
for(i = 0; i < n; i++)
  if(strcmp(v[i].nome, chave) == 0)
    cont++;

return cont;
}

int acha_posicao(struct evento *v, int n, char *chave){
int i, pos = 0;
for(i = 0; i < n; i++)
  if(strcmp(v[i].nome, chave) == 0)
    pos = i;

return pos;
}

void print_data(struct evento *v, int i){
printf("Data do evento: %d/%d/%d\n", v[i].cadastro.dia, v[i].cadastro.mes, v[i].cadastro.ano);
}

void consultar(struct evento *v, int n){
char chave[20];
int i, cont=0, pos;

printf("\nDigite o nome do evento para consulta: \n");
scanf(" %[^\n]", chave);
pos = acha_posicao(v, n, chave);

  if (verifica_registro(v, n, chave) == 0 ){
     printf("\nRegistro nao encontrado.\n");
  }else{

      printf("Nome: %s\n", v[pos].nome);
      printf("Horario de Inicio: %d:%d\n", v[pos].horario_inicio);
      printf("Horario de Fim: %d:%d\n", v[pos].horario_fim);
      printf("local: %s\n", v[pos].local);
      print_data(v, pos);
  }

}

void ordena_eventos( struct evento *v, int n ){
	int i;
	for(i = 0; i < n-1; i++){
		int j, i_menor = i;
		for(j = i+1; j < n; j++){
			if( strcmp( v[j].nome, v[i_menor].nome) < 0 )
				i_menor = j;
    }

		struct evento aux = v[i];
		v[i] = v[i_menor];
		v[i_menor] = aux;
	}
}