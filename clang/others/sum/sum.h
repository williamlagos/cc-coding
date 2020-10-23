/*																		*
 * Sum - Programa para distribuicao de numeros em pares de somas		*
 * O programa possui o seguinte objetivo: distribuir os numeros em		*
 * pares de forma que os conjuntos possuam a mesma soma. A estrategia	*
 * utilizada para isso sera um algoritmo de backtracking por meio 		*
 * de estruturas de vetores e chamadas recursivas.						*
 *																		*
 * William Oliveira de Lagos <william.lagos1@gmail.com> 				*
 * Luiz Botton <lbotton@gmail.com>										*
 *																		*/	

/* Estrutura para armazenar vetor principal */
typedef struct {
	int quantity;
	unsigned int count;
	unsigned int* digits;
} numbers;

/* Estrutura para armazenar numeros em arvore */
typedef struct {
	void* parent;
	void** childs;
	unsigned int sum;
	int pos;
} node;

/* Membro global para estrutura unica de numeros */
static numbers* nu;
FILE* output;
FILE* errors;

void combo(node* n);
int sum(node* no, unsigned int goal);
int depth(node* no, unsigned int goal);
void pairs(unsigned int* activated, unsigned int count);
