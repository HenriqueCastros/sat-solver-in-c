// Funcoes relevantes para o struct Clause
// Desenvolvido pelo alunos Diogo Casal, Gabriel Nardy, Henrique Castro e Matheus Pego
// Alunos do curso Ciencia da Computacao da PUC Minas
// Materia Arquitetura de Computadores II

typedef struct Clause{
    int* variables;
    int numOfVariables;
    int positiveVariables; //Numero de var que estao positivos
    int negativeVariables;  //Numero de var que estao negadas
    short redFlag;          //Se negativeVariables == numOfVariables, ou seja, tudo esta negado, entao ha um redFlags
} Clause;

//Metodo utiizado para criar nova Clause 
Clause* newClause(int vars[], int len){
    Clause* newClause = (Clause*)malloc(sizeof(Clause));
    newClause->numOfVariables = len;
    newClause->variables = (int*)malloc(sizeof(int) * len);
    for (int i = 0; i < len; i++){
        newClause->variables[i] = vars[i];
    }
    newClause->positiveVariables = 0;
    newClause->negativeVariables = 0;
    newClause->redFlag = 0;
    return newClause;
}

void printClause(Clause* clause){
    printf("\nCLAUSE || VAR = [ ");
    for (int i = 0; i < clause->numOfVariables; i++)
    {
        printf("%d ",  clause->variables[i]);
    }
    printf("] current state ");
    printf("pos : %d - neg: %d",  clause->positiveVariables,  clause->negativeVariables);
}

Clause* readClause(){
    int var[100];
    int i = 0;

    scanf("%d", &var[0]);
    while( var[i] != 0 ){
        var[i] = var[i] > 0 ? var[i]*2: abs(var[i])*2+1;
        scanf("%d", &var[++i]);
    }

    return newClause(var, i);
}

#define ADD 1
#define REMOVE -1

//Metodo utilizado para atualizar as variaveis de uma Clause
void updateClause(Clause* clause, int updatedVariable, int value, int method){
    for (int i = 0; i < clause->numOfVariables; i++){
        if ((clause->variables[i] >> 1) == updatedVariable){    // Se o valor e encontrado dentro da Clause 
            if((clause->variables[i] % 2 ^ value))              //  var % 2 retorna 0 se ela nao esta negada ou 1 se negada
                clause->positiveVariables += method;                    //  value 0 == FALSE and 1 == TRUE
            else{
                clause->negativeVariables += method;
                clause->redFlag = clause->negativeVariables == clause->numOfVariables;
            }
            return;
        }
    }
    
}