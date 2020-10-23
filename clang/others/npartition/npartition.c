#include<limits.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<omp.h>
#include<mpi.h>
#include<math.h>
#include<time.h>

#define round(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))
	
void combinate_numbers(int number, long *count);

/* Soma os divisores de n */
void divisors(int number, long *count){
	int aux = number-1;
	while(aux != 1){
		if(number%aux == 0) (*count)++;
		aux--;
	}
}

/* Busca pelas combinações restantes */	
void combinations(int number, long *count){
	int modu,half,odd,aux,diff;
	
	// Tratamento de pares e ímpares
	odd = 0;
	half = number/2;
	modu = (number%2 != 0);
	if(modu){ odd += 1; }
	
	for(aux = number; aux != 1; aux--){
		diff = number-aux;
		if(diff != 0){
			// Combinações de inteiros até n/2
			if(aux < half+odd) (*count)++;
//#pragma omp task
			combinate_numbers(diff,count);
//#pragma omp taskwait
		}
	}
}

void combinate_numbers(int number, long *count){
	// Caso n = 1,2
	if(number == 1){
		(*count)++;
	}else if(number == 2){
		(*count)++;
	}else{
		(*count)++;
		divisors(number,count);
		combinations(number,count);
	}
}

int main(int argc, char** argv){
	int final_n,initial,num,i,n,pid,tid;
	double ratio,max_v,root,q,sum,quantity,number,interval = 1.0;
	time_t start;
	sum = 0.0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &n);
	if(argc > 1) final_n = atoi(argv[1]);
	else final_n = 1;
	puts("Programa de combinações");
	// Razao entre o numero de operacoes e numero de processos
	quantity = n;
	number = final_n;
	ratio = number/quantity;
	max_v = ratio*(quantity/2);
	/* Interpolacao em meio geometrico para por itens mais baratos 
	em maior quantidade, e os itens mais caros em menor quantidade 
	Formula utilizada (Progressao Geometrica): q = rt(an/a1,n-1) */
	root = 1/(quantity-1);
	q = pow(max_v,root);
	if(pid != n-1){
		for(i = 0; i < pid; i++){
			interval /= q;
			if(i != 0) sum += interval;
		}
		if(interval < 1.0) interval += 1.0;
	}else{
		interval = max_v;
		sum = n-max_v;
	}
	printf("PID: %i Intervalo: %lf - Razão: %lf - Posição: %lf\n",pid,interval,q,sum);
	initial = round(sum+interval/q);
	final_n = round(sum+interval);
	printf("Inicial: %d - Final: %d\n",initial,final_n);
	omp_set_num_threads(4);
	start = time(NULL);
#pragma omp parallel for private(num),schedule(dynamic) 
	for(num = initial; num < final_n+1; num++){
		tid = omp_get_thread_num();
		long *count = malloc(sizeof(long));
		*count = 0;
		combinate_numbers(num,count);
		printf("THID: %d || Numero: %d || Combinações: %ld\n",
			 tid, num, *count);
		free(count);
	}
	printf("Time elapsed: %ds", (int) difftime(time(NULL), start));
	puts("\n");
	MPI_Finalize();
	return 0;
}
