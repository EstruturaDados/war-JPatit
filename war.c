#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_territorio 5
#define total_missoes 5

//definição da struct
struct Territorio{
    char nome_territorio[30];
    char cor_exercito[10];
    int tropas;
};

//comando de missoes
char missoes[total_missoes][100] = {
    "Conquistar 3 territorios seguidos",
    "Eliminar todas as tropas da cor vermelha",
    "Controlar todos os territorios",
    "Ter pelo menos 10 tropas em um territorio",
    "Conquistar pelo menos 2 territorios inimigos"
};

//limpar o buffer de entrada
void limparBufferEntrada(){
    int c;
    while((c=getchar())!='\n' && c != EOF);
}

//dar missao ao exercito
void entregarmissao(char* destino, char missoes[][100], int totalMissoes){
    int indice = rand() % totalMissoes; // sorteia uma missão
    strcpy(destino, missoes[indice]);   // copia para o jogador
}

//simulação de ataque
void ataque(struct Territorio* atacante, struct Territorio* defensor){
    //impede ataque da mesma cor
    if (strcmp(atacante->cor_exercito, defensor->cor_exercito) == 0){
        printf("Nao pode atacar seu aliado");
        return;
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

int verificarMissao(char* missao, struct Territorio* mapa, int tamanho){

// Missão: controlar todos os territorios
    if (strstr(missao, "Controlar todos os territorios") != NULL){
        char cor[10];
        strcpy(cor, mapa[0].cor_exercito);

        for(int i = 1; i < tamanho; i++){
            if(strcmp(cor, mapa[i].cor_exercito) != 0){
                return 0;
            }
        }
        return 1;
    }

// Missão: ter pelo menos 10 tropas em um territorio
    if (strstr(missao, "10 tropas") != NULL){
        for(int i = 0; i < tamanho; i++){
            if(mapa[i].tropas >= 10){
                return 1;
            }
        }
        return 0;
    }
    // Missão: conquistar 2 territorios inimigos (simples)
    if (strstr(missao, "2 territorios") != NULL){
        int contador = 0;

        for(int i = 0; i < tamanho; i++){
            if(mapa[i].tropas > 1){
                contador++;
            }
        }
        if(contador >= 2){
            return 1;
        }
        return 0;
    }
    return 0;
}

//função main
int main(){
//deixar aleatorio
    srand(time(NULL));

    struct Territorio* pais = malloc(max_territorio *sizeof(struct Territorio));
    int totalterritorio=0;

    char *missaojogador;
    missaojogador = (char*) malloc(100 * sizeof(char));

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

entregarmissao(missaojogador, missoes, total_missoes);

//exibição dos territorios
printf("Territorios cadastrados:\n\n");

for (int i = 0; i < totalterritorio; i++){
    printf("Territorio %d:\n", i+1);
    printf("Nome do territorio: %s\n", pais[i].nome_territorio);
    printf("Cor do Exercito: %s\n", pais[i].cor_exercito);
    printf("Numero de Tropas: %d\n", pais[i].tropas);
    printf("\n\n");
}

printf("Sua missao é: %s \n", missaojogador);

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

//verifica se a missao foi concluida
if (verificarMissao(missaojogador, pais, totalterritorio)){
    printf("\n Missao Cumprida! Você venceu!\n");
    break;
}

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
free(missaojogador);

return 0;
}