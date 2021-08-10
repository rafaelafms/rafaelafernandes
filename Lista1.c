#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

typedef struct{
  int nthreads; //numero de threads a serem criadas
  int n; //numero de execucoes
  int id; //id para definir o tamanho dos blocos
}

void * tarefa(void *arg){
	
	tArgs *args = (tArgs*)  arg;
	double *somaLocal;
	long int tamBloco =  (args->n)/(args->nthreads); //divide o bloco
	long int ini = (args->id) * tamBloco; //onde cada thread comeca a execucao
	long int fim; //fim do bloco

	somaLocal = (double*) malloc(sizeof(double));
	if(somaLocal == NULL){
		pritnf(“ERRO-- malloc\n”); exit(1);

	//determina o inicio e o fim do bloco
	if(args->id == (args->nthreads)-1)
		fim = args->n
	else
		fim = ini + tamBloco;

	//somatorio
	for(long int i=ini; i<fim; i++)
		*somaLocal += pow(-1,i)*(1.0/((2*i)+1));

	pthread_exit((void *) somaLocal);
}

int main(int argc, char* argv[]){

	int n, nthreads; //numero de execucoes e threads
	double piConc=0; //resultado final
  	double *retorno; //retorno das threads
  	tArgs *args; //struct a ser passada para tarefa
  	pthread_t *tid; //id das threads
  
  	if (argc<3){
    		printf("Digite: %s <n> <numero de threads>\n", argv[0]);
    		return 1;
  	}
  	n = atoi(argv[1]);
  	nthreads = atoi(argv[2]);
  
  	tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  	if(tid == NULL){
    		printf("ERRO--malloc\n");
    		return 2;
  	}
  
  	//aloca a struct
  	args = (tArgs*)malloc(sizeof(tArgs)*nthreads);
  	if(args == NULL){puts("ERRO--malloc"); return 2;}
  
  	//criar as threads
  	for(long int i=0; i<nthreads; i++){
		if(pthread_join*(tid+i), (void**) &retorno){
			printf(“ERRO--”);
			return 3;
    		}
    		piConc += *retorno; //soma os resultados dos blocos
    		free(retorno);
  	}
  	piConc = 4*piConc; //finaliza o valor de pi
  	printf(“Pi = %lf\n”, piConc);

  	return 0;
}
