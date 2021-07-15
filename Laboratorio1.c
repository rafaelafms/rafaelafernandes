#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <math.h>

#define NTHREADS  10000 //total de threads a serem criadas

//funcao executada pelas threads
void * quadrado (void* arg) {
    int idThread = * (int*) arg;
    idThread = idThread*idThread;
    *(int*)arg = idThread;

    pthread_exit(NULL);
}

//funcao principal do programa
int main() {
    pthread_t tid[NTHREADS]; //identificadores das threads no sistema
    int thread; //variavel auxiliar
    int elementos[NTHREADS]; //identificadores locais das threads
    
    //inicializa e escreve em tela o vetor inicial
    printf("vetor inicial = [");
    for(int i=0; i<NTHREADS; i++){
        elementos[i] = i+1;
        printf("%d ", elementos[i]);
    }
    printf("]\n");
    
    //cria as duas threads
    for(thread=0; thread<NTHREADS; thread=thread+2) {
        if (pthread_create(&tid[thread], NULL, quadrado, (void*) &elementos[thread])){
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
        if (pthread_create(&tid[thread+1], NULL, quadrado, (void*) &elementos[thread+1])){
            printf("--ERRO: pthread_create()\n"); exit(-1);
        }
    }
    
    //espera as threads terminarem
    for (thread=0; thread<NTHREADS; thread++) {
        if (pthread_join(tid[thread], NULL)) {
            printf("--ERRO: pthread_join() \n"); exit(-1); 
        } 
    }
    
    //escreve em tela o vetor final
    printf("vetor final = [");
    for(thread=0; thread<NTHREADS; thread++) {
        printf("%d ", elementos[thread]);
    }
    printf("]\n"); 
    
    //teste: verifica se os valores finais estão corretos 
    for(int i=0; i<NTHREADS; i++){
        if(sqrt(elementos[i]) != i+1){
            printf("--ERRO: potencia errada"); exit(-1);
        }
    }
    
    printf("--Execucao bem sucedida\n");
    
}
