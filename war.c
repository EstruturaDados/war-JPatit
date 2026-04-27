#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//função main
int main(){
    struct Territorio Pais[max_territorio];
    int totalterritorio=0;

//cadastro
for(int i = 0; i < 5; i++){
    printf("Cadastro de Territorios!\n\n");
    printf("Cadastro do Territorio %d\n", i+1);
    printf("Nome do Territorio: ");
    fgets(Pais[i].nome_territorio, sizeof(Pais[i].nome_territorio), stdin);

    printf("Cor do Exercito: ");
    fgets(Pais[i].cor_exercito, sizeof(Pais[i].cor_exercito), stdin);

    Pais[totalterritorio].nome_territorio[strcspn(Pais[totalterritorio].nome_territorio, "\n")]= '\0';
    Pais[totalterritorio].cor_exercito[strcspn(Pais[totalterritorio].cor_exercito, "\n")]= '\0';

    printf("Numero de Tropas: ");
    scanf("%d", &Pais[totalterritorio].tropas);

    limparBufferEntrada();

    printf("\n");  
    
    totalterritorio++;
}

//exibição dos territorios
printf("Territorios cadastrados:\n\n");

for (int i = 0; i < totalterritorio; i++){
    printf("Territorio %d:\n", i+1);
    printf("Nome do territorio: %s\n", Pais[i].nome_territorio);
    printf("Cor do Exercito: %s\n", Pais[i].cor_exercito);
    printf("Numero de Tropas: %d\n", Pais[i].tropas);
    printf("\n\n");
}

return 0;
}