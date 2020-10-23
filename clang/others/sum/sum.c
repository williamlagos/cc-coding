/*																		*
 * Sum - Programa para distribuicao de numeros em pares de somas		*
 * O programa possui o seguinte objetivo: distribuir os numeros em		*
 * pares de forma que os conjuntos possuam a mesma soma. A estrategia	*
 * utilizada para isso sera um algoritmo de backtracking por meio		*
 * de estruturas de vetores e chamadas recursivas.						*
 *																		*
 * William Oliveira de Lagos <william.lagos1@gmail.com>					*
 * Luiz Botton <lbotton@gmail.com>										*
 *																		*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sum.h"

#define SUM "SUM"
#define MAIN "MAIN"
#define COMBO "COMBO"
#define PAIRS "PAIRS"
#define ACTIVATED 1
#define DEACTIVATED 0
#define MAX_BUFFER 10
#ifndef WIN32
#define FOPEN(f,n,m) (f = fopen(n,m)) == NULL
#define FREOPEN(f,n,m,s) (f = freopen(n,m,s)) == NULL
#else
#define FOPEN(f,n,m) fopen_s(&f,n,m) != 0
#define FREOPEN(f,n,m,s) freopen_s(&f,n,m,s) != 0
#endif

int main(int argc, char** argv)
{
	/* Declaracao de variaveis e vetores */
	int i = 0;
	int goal = 0;
	int count = 0;
	size_t digits = 0;
	node* root = NULL;
	char* program = argv[0];
	nu = malloc(sizeof(numbers));
	nu->count = 0;

	/* Inicio do arquivo de log de erros. Toda saida apontada	*
	 * para output sendo deslocada para um arquivo.				*/
	if((FREOPEN(errors,"errors.log","a", stderr))){
		fprintf(stderr,"%s: Nao foi possivel acessar o arquivo de log.\n",program);
		exit(EXIT_FAILURE);
	}

	/* Checagem de erros para execucao */
	if(argc < 4){
		fprintf(stdout,"%s: Digite pelo menos a quantidade e dois numeros.\n",program);
		fprintf(stderr,"%s: Digite pelo menos a quantidade e dois numeros.\n",program);
		exit(EXIT_FAILURE);
	}
	nu->quantity = atoi(argv[1]);
	if(nu->quantity != (argc-2)){
		fprintf(stdout,"%s: O tamanho fornecido e a quantidade de numeros nao coincidem.\n",program);
		fprintf(stderr,"%s: O tamanho fornecido e a quantidade de numeros nao coincidem.\n",program);
		exit(EXIT_FAILURE);
	}

	/* Inicio do arquivo de log. Toda saida apontada	*
	 * para output sendo deslocada para um arquivo.		*/
	if((FOPEN(output,"sum.log","a"))){
		fprintf(stdout,"%s: Nao foi possivel acessar o arquivo de log.\n",program);
		fprintf(stderr,"%s: Nao foi possivel acessar o arquivo de log.\n",program);
		exit(EXIT_FAILURE);
	}

	/* Criacao de vetor com os numeros. A quantidade	*
	 * esta ja armazenada em outra variavel. A soma		*
	 * de todos os numeros vai ser armazenada tambem.	*/
	digits = nu->quantity;
	nu->digits = calloc(digits,sizeof(unsigned int));
	for(i = 2; i < argc; i++){
		nu->digits[i-2] = atoi(argv[i]);
		goal += nu->digits[i-2];
	}
	goal = (goal - (goal % 2)) / 2;

	/* Preparacao do nodo raiz para execucao recursiva	*
	 * Alocacao do nodo inicial pelo primeiro elemento	*/
	root = malloc(sizeof(node));
	root->parent = NULL;
	root->pos = 0;
	root->sum = nu->digits[0];
	fprintf(output,"\n[%s] Inicio da busca por combinacoes\n",MAIN);
	count = depth(root,goal);

	if(count == 0){
		fprintf(stdout,"Nenhuma combinacao foi encontrada.\n");
		fprintf(output,"[%s] Nenhuma combinacao foi encontrada.\n",MAIN);
	}else{
		fprintf(stdout,"%d combinacoes foram encontradas.\n",count);
		fprintf(output,"[%s] %d combinacoes foram encontradas.\n",MAIN,count);
	}

	/* Liberando recursos e terminando o programa */
	free(nu->digits);
	free(nu);
	free(root);
	fclose(output);
	fclose(errors);
	exit(EXIT_SUCCESS);
}

void pairs(unsigned int* activated, unsigned int count)
{
	/* Divisao das combinacoes em pares atraves do arranjo de ativadas	*
	 * Cada posicao corresponde a equivalente no arranjo original, se	*
	 * estiver em 1, esta ativa, e se estiver em 0, inativa.			*/
	static unsigned int index,index1,index2,digit;
	unsigned int* pair1 = NULL;
	unsigned int* pair2 = NULL;

	/* Preparacao de limites de cada par, de acordo com o contador */
	size_t max = nu->quantity;
	size_t max1 = count;
	size_t max2 = max-count;
	index = index1 = index2 = digit = 0;
	fprintf(output,"[%s] Quantidade do Par 1: %d\n",PAIRS,(int) max1);
	fprintf(output,"[%s] Quantidade do Par 2: %d\n",PAIRS,(int) max2);

	pair1 = calloc(max1,sizeof(int));
	pair2 = calloc(max2,sizeof(int));

	/* Dividindo valores em pares para impressao */
	while(index < max){
		fprintf(output,"[%s] Codigo de ativacao: %d\n",PAIRS,activated[index]);
		digit = nu->digits[index];
		if(activated[index] == ACTIVATED){
			pair1[index1] = digit;
			index1++;
		}else{
			pair2[index2] = digit;
			index2++;
		}
		index++;
	}

	/* Realizando impressao de pares */
	for(index1 = 0; index1 < max1; index1++)
		fprintf(stdout,"%d ",pair1[index1]);
	fprintf(stdout,"\n");
	for(index2 = 0; index2 < max2; index2++)
		fprintf(stdout,"%d ",pair2[index2]);
	fprintf(stdout,"\n");

	free(pair1);
	free(pair2);
}

void combo(node *n)
{
	/* Imprime a combinacao encontrada e constroi *
	 * o par de somas realizado a partir da busca */
	unsigned int* activated = NULL;
	unsigned int count = 0;
	size_t max_array_size = nu->quantity;
	activated = calloc(max_array_size,sizeof(unsigned int));
	/* Alocando o maximo de tamanho para cada par */
	memset((void*) activated,0,max_array_size - 1);

	while(n->parent != NULL){
		if(n->pos == ((node*) n->parent)->pos){
			/* Pequena correcao para o caminhamento, quando	*
			 * encontrado nodos de mesma posicao, ignorar.	*/
			n = n->parent;
			continue;
		}else{
			/* Impressao de cada nodo do caminhamento */
			activated[n->pos] = ACTIVATED;
			fprintf(output,"[%d] %d ",n->pos,nu->digits[n->pos]);
			fprintf(output,"P:([%d] %d) ",((node*) n->parent)->pos,nu->digits[((node*) n->parent)->pos]);
			count++;
		}
		n = n->parent;
	}
	activated[n->pos] = ACTIVATED;
	count++;
	fprintf(output,"[%d] %d \n",n->pos,nu->digits[n->pos]);
	/* Chamada da funcao para impressao dos pares */
	pairs(activated,count);
	free(activated);
	return;
}

int depth(node *no, unsigned int goal)
{
	/* Instancia as combinacoes possiveis para um determinado		*
	 * numero. Os nodos em seguida serao visitados e verificados.	*/
	int i = 0;
	unsigned int index = 0;
	size_t child_size = nu->quantity - (no->pos + 1);
	no->childs = calloc(child_size,sizeof(node*));

	for(i = no->pos + 1; i < nu->quantity; i++){
		/* Criacao de nodos filho */
		index = i - (no->pos + 1);
		((node**) no->childs)[index] = malloc(sizeof(node));
		((node**) no->childs)[index]->parent = (void*) no;
		((node**) no->childs)[index]->childs = NULL;
		((node**) no->childs)[index]->pos = i;
		((node**) no->childs)[index]->sum = no->sum;
		/* Apontamento de nodo filho para pai e chamada recursiva */
		fprintf(output,"[%s] Posicao para verificacao: %d\n",COMBO,i);
		fprintf(output,"[%s] Numero armazenado: %d\n",COMBO,nu->digits[((node** )no->childs)[index]->pos]);
		sum(((node**) no->childs)[index],goal);
		free(((node**) no->childs)[index]);
	}
	free(no->childs);
	return nu->count;
}

int sum(node* no, unsigned int goal)
{
	/* Realiza a soma do nodo com o resto dos numeros do caminho e	* 
	 * verifica se passou do criterio de parada ou uma combinacao	*
	 * foi encontrada.						 						*/
	node* n = NULL;
	no->sum = no->sum + nu->digits[no->pos];
	fprintf(output,"[%s] Soma atual: %d\n",SUM,no->sum);

	/* Inicio da funcao e apontamento da arvore */
	if(no->sum >= goal){
		fprintf(output,"[%s] Entrada em retorno de arvore\n",SUM);
		/* Retorno de busca em caso de criterio de parada */
		if(no->sum == goal){
			nu->count += 1;
			/* Uma combinacao encontrada */
			fprintf(output,"[%s] Combinacao encontrada:\n",SUM);
			fprintf(stdout,"Combinacao encontrada:\n");
			/* Envia uma copia do nodo para a funcao de divisao */
			combo(no);
		}else{
			/* Passou do limite do criterio de parada,	*
			 * retorna e diminui a soma encontrada		*/
			return nu->count;
		}
	}else{
		/* Busca em profundidade para o proximo nodo */
		fprintf(output,"[%s] Busca em profundidade\n",SUM);

		if(no->pos == nu->quantity-1){
			/* Verifica se todos os nodos filhos ja foram	*
			 * visitados para evitar uma nova busca em		*
			 * profundidade.								*/
			fprintf(output,"[%s] Todos os filhos visitados, retornar\n",SUM);
			return nu->count;
		}

		n = malloc(sizeof(node));
		n->parent = (void*) no;
		n->pos = no->pos;
		n->sum = no->sum;
		/* Comeco da chamada recursiva para a busca em profundidade */
		depth(n,goal);
		free(n);
	}
	return nu->count;
}
