// Arquivo Principal Utilizado
// Resolvedor ISFN_CC
// Desenvolvido pelo alunos Diogo Casal, Gabriel Nardy, Henrique Castro e Matheus Pego
// Alunos do curso Ciencia da Computacao da PUC Minas
// Materia Arquitetura de Computadores II

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "clause.c"

#define TRUE 1
#define FALSE 0

// O metodo findSAT() utiliza dessas flags, checar o metodo para entende funcionameto
#define UNDEFINED -1
#define OVERUSED 1

int numOfClauses;
int numOfLiterals;

Clause** clauses;
int* literals;

void parseInput(){
    char* c = (char*)malloc(sizeof(char)*1024);
    while (strcmp(c, "p") != 0){
        scanf("%s", c);
    }
    scanf("%s %d %d", c,  &numOfLiterals, &numOfClauses);
    free(c);
    literals = (int*)malloc(sizeof(int) *(numOfLiterals+1));
    clauses = (Clause**)malloc(sizeof(Clause*) * numOfClauses);
    for(int i = 0; i < numOfClauses; i++)
        clauses[i] = readClause();
    
    for(int i = 1; i < numOfLiterals+1; i++)
        literals[i] = UNDEFINED;
}

int applyUptade(int uptadedVariable, int value, int method){
    int success = 0;
    for (int i = 0; i < numOfClauses; i++){
        updateClause(clauses[i], uptadedVariable, value, method);
        success += clauses[i]->redFlag;
    }
    return success;
}

void resetLiterals(int offset){
    for(int i = offset+1; i < numOfLiterals+1; i++)
        literals[i] = UNDEFINED;
}

/*
    O metodo findSAT() tetna encontrar a resolucao para as clausulas.
    No caso desse algoritmo, o valor inicial testado e sempre 0 comecando da primeira variavel.
    Quando uma variavel tem seu valor colocado para 'testar', o vetor literals tem seu valor atualizado.
    Se val == -1, entao a var ainda nao foi avaliado. Se val == 0, entao valor 0 foi testado.
    Se val == 1, entao a var ja teve o valor 0 e 1 testado.

    O algoritmo vai tracando um caminho similar ao formato de uma arvore binaria.
    Caso a variavel que esta sendo testada, tenha seu status como OVERUSED(1), entao
    o algoritmo volta para a variavel que foi testada anterior e atualiza para o proximo
    valor de status. Depois disso as clausulas subsequentes tem seus status resetados.
*/
void findSAT(){
    for(int currentVariable = 1; currentVariable < numOfLiterals+1; currentVariable++){

        if(literals[currentVariable] != OVERUSED){
            literals[currentVariable] += 1; // Mude o status
            if(applyUptade(currentVariable, literals[currentVariable], ADD) == 0){}else{
                applyUptade(currentVariable, literals[currentVariable], REMOVE);
                currentVariable--;
            }
        }else if (literals[currentVariable] == OVERUSED && currentVariable != 1){
            resetLiterals(currentVariable);
            currentVariable -= 2; //Va para o pai
        }else{
            printf("\nEsse sistema e NAO SAT");
            return;
        }


    }
    printf("\nEsse sistema e SAT");
}

int main (){
    clock_t start, end;
    double cpu_time_used;
    parseInput();
    start = clock();
    findSAT();
    end = clock();
    printf("\n");
    for(int i = 1; i < numOfLiterals+1; i++){
        if(literals[i] == FALSE){
            printf("%d ", -1 * i);
        }else{
            printf("%d ", i);
        }
    }
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTempo gasto = %lf\n", cpu_time_used);
    
    return 0;
}
