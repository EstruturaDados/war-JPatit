#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_territorio 5

//definição da struct
struct Territorio{
    char nome_territorio[30];
    char cor_exercito[10];
    int tropas;
};

//limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while((c=getchar())!='\n' && c != EOF);
}

//simulação de ataque
void ataque(struct Territorio* atacante, struct Territorio* defensor){
    //impede ataque da mesma cor
    if (strcmp(atacante->cor_exercito, defensor->cor_exercito) == 0){
        printf("Nao pode atacar seu aliado");
    }  
//randomiza o numero dos dados 
int dado1 = rand() % 6 + 1;
int dado2 = rand() % 6 + 1;

printf("\n%s (cor %s) atacou %s (cor %s)\n", atacante->nome_territorio, atacante->cor_exercito,
                                             defensor->nome_territorio, defensor->cor_exercito);

printf("Dado de ataque: %d /// Dado de defesa %d \n", dado1, dado2);

if (dado1 > dado2){
    printf("%s venceu\n\n", atacante->nome_territorio);

    atacante->tropas++;
    defensor->tropas--;

//muda a cor do exercito
if(defensor->tropas <= 0){
    printf("%s foi conquistado por %s!\n", defensor->nome_territorio, atacante->nome_territorio);
    strcpy(defensor->cor_exercito, atacante->cor_exercito);
    defensor->tropas = 1;
}

} else if (dado2 > dado1){
    printf("%s defendeu com sucesso\n", defensor->nome_territorio);
} else { printf("Empate\n");
}}

//função main
int main(){
//deixar aleatorio
    srand(time(NULL));

    struct Territorio* pais = malloc(max_territorio *sizeof(struct Territorio));
    int totalterritorio=0;

//cadastro
for(int i = 0; i < 5; i++){
    printf("Cadastro de Territorios!\n\n");
    printf("Cadastro do Territorio %d\n", i+1);
    printf("Nome do Territorio: ");
    fgets(pais[i].nome_territorio, sizeof(pais[i].nome_territorio), stdin);

    printf("Cor do Exercito: ");
    fgets(pais[i].cor_exercito, sizeof(pais[i].cor_exercito), stdin);

    pais[totalterritorio].nome_territorio[strcspn(pais[totalterritorio].nome_territorio, "\n")]= '\0';
    pais[totalterritorio].cor_exercito[strcspn(pais[totalterritorio].cor_exercito, "\n")]= '\0';

    printf("Numero de Tropas: ");
    scanf("%d", &pais[totalterritorio].tropas);

    limparBufferEntrada();

    printf("\n");  
    
    totalterritorio++;
}

//exibição dos territorios
printf("Territorios cadastrados:\n\n");

for (int i = 0; i < totalterritorio; i++){
    printf("Territorio %d:\n", i+1);
    printf("Nome do territorio: %s\n", pais[i].nome_territorio);
    printf("Cor do Exercito: %s\n", pais[i].cor_exercito);
    printf("Numero de Tropas: %d\n", pais[i].tropas);
    printf("\n\n");
}

char continuar = 's';

while (continuar == 's'){
    for (int i = 0; i < totalterritorio; i++){
        printf("%d - %s(Cor: %s, Tropas: %d)\n", i + 1, pais[i].nome_territorio, 
                        pais[i].cor_exercito, pais[i].tropas);
    }


char entrada[10];
int atk, def;

printf("==============\n");
printf("Hora da Guerra\n");
printf("==============\n\n");

// atacante
printf("\nEscolha quem vai atacar (1 a %d): ", totalterritorio);
fgets(entrada, sizeof(entrada), stdin);
atk = atoi(entrada);

// defensor
printf("Escolha quem vai defender (1 a %d): ", totalterritorio);
fgets(entrada, sizeof(entrada), stdin);
def = atoi(entrada);

atk--;
def--;

//valida o combate
if (atk >= 0 && atk < totalterritorio && def >= 0 && def < totalterritorio && atk != def){
    ataque(&pais[atk], &pais[def]);
} else { printf("Escolha invalida\n");}

printf("Deseja continuar? (s/n):  \n\n");
scanf("%c", &continuar);
limparBufferEntrada();
}

//ultima exibição
printf("//Pós Combate//\n\n");
for (int i = 0; i < totalterritorio; i++){
    printf("Territorio %d:\n", i+1);
    printf("Nome do territorio: %s\n", pais[i].nome_territorio);
    printf("Cor do Exercito: %s\n", pais[i].cor_exercito);
    printf("Numero de Tropas: %d\n", pais[i].tropas);
    printf("\n\n");
}

//liberação de memoria
free(pais);

return 0;
}