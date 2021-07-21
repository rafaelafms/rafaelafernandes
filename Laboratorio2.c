/* Multiplicacao matriz-matriz (matrizes quadradas) */

#include<stdio.h>
#include<stdlib.h> 
#include<pthread.h>
//#include"timer.h"

float *mat1; //matriz de entrada
float *mat2; //matriz de entrada
float *saida; //vetor de saida
int dim; //dimensao da matriz
int nthreads; // numero de threads pedidos pelo usuario

//teste de corretude
int corretude(){
    float *saida2;
    
    saida2 = (float *)malloc(sizeof(float) * dim * dim); 
    if(saida2 == NULL) {printf("ERRO--malloc\n"); return 2;}

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            for(int k=0; k<dim; k++)
                saida2[i*dim+j] += mat1[i*dim+j]*mat2[i*dim+j];
            if(saida[i*dim+j] != saida2[i*dim+j]){
                free(saida2);
                return 4;
            }
        }
    } 
    
    free(saida2);
    return 5;
}

//funcao que as threads executarao
void * tarefa(void *arg){
    int ident = *(int *) arg;

    //ideia: dividir de forma mais igual possivel para cada thread executar um numero parecido de linhas 
    for(; ident<dim; ident+=nthreads){ //linha 
        for(int j=0; j<dim; j++){   //coluna
            for(int k=0; k<dim; k++){ //soma dos elementos para chegar na matriz de saida
                saida[ident*dim+j] += mat1[ident*dim+j]*mat2[ident*dim+j];
            }
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){ 

    pthread_t *tid; //identificadores das threads no sistema
    int ident[nthreads]; //identificador local da thread
    //double inicio, fim, delta;

    //leitura e avaliacao dos parametros de entrada (pela linha de comando) (SEQUENCIAL)
    if (argc<3){
        printf("Digite: %s <dimensao da matriz> <numero de threads>\n", argv[0]); 
        return 1;        
    }
    dim = atoi(argv[1]); 
    nthreads = atoi(argv[2]); 
    if (nthreads>dim) {nthreads = dim;}
    
    //alocacao de memoria para as matrizes (SEQUENCIAL)
    mat1 = (float *)malloc(sizeof(float) * dim * dim);
    if(mat1 == NULL) {printf("ERRO--malloc\n"); return 2;}

    mat2 = (float *)malloc(sizeof(float) * dim * dim); 
    if(mat2 == NULL) {printf("ERRO--malloc\n"); return 2;}

    saida = (float *)malloc(sizeof(float) * dim * dim); 
    if(saida == NULL) {printf("ERRO--malloc\n"); return 2;}

    //inicializacao das estruturas de dados de entrada (SEQUENCIAL)
    //GET_TIME(inicio);
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            mat1[i*dim+j] = 1; 
            mat2[i*dim+j] = 1;
            saida[i*dim+j] = 0;
        }
    }
    /*GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de inicializacao das estruturas de dados %lf\n",delta);*/

    //criacao das threads(CONCORRENTE)
    //GET_TIME(inicio);
    tid = (pthread_t*)malloc(sizeof(pthread_t)*nthreads);
    if(tid == NULL){puts("ERRO--malloc"); return 2;}

    for(int i=0; i<nthreads; i++){
        ident[i] = i;
        if(pthread_create(tid+i, NULL, tarefa, (void*) &ident[i])){
            puts("ERRO--pthread_create"); return 3;    
        }
    } 

    //espera pelo termino da thread 
    for(int i=0; i<nthreads ; i++){ 
        pthread_join(*(tid+i), NULL);
    }
    /*GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de criacao, execucao e termino das threads %lf\n",delta);*/


    //exibicao dos resultados (SEQUENCIAL)
    /*puts("Saida:"); 
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++)
            printf("%1f ", saida[i*dim+j]);
        puts("");
    }*/

    //teste de corretude
    //GET_TIME(inico);
    if(corretude() == 5) printf("--Execucao bem sucedida\n");
    else printf("--Erro na matriz de saida\n");
    /*GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de execucao sequencial %lf\n",delta);*/

    //liberacao da memoria (SEQUENCIAL)
    //GET_TIME(inicio);
    free(mat1);
    free(mat2);
    free(saida);  
    free(tid);  
    /*GET_TIME(fim);
    delta = fim - inicio;
    printf("Tempo de finalizacao do programa %lf\n",delta);*/


    return 0;
}
