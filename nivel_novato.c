#include <stdio.h>
#include <string.h>

typedef struct {
    char nome_territorio[50];
    char cor_exercito[20];
    int numero_tropas;
} Territorio;

int main() {
    Territorio territorios[5];
for(int i = 0; i < 5; i++) {
    printf("-------------------------------------------------\n");
    printf("=======Cadastro do territorio %d=======\n", i + 1);
    printf("Digite o nome do territorio: ");
    fgets(territorios[i].nome_territorio, sizeof(territorios[i].nome_territorio), stdin);
    territorios[i].nome_territorio[strcspn(territorios[i].nome_territorio, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Digite a cor do exercito: ");
    fgets(territorios[i].cor_exercito, sizeof(territorios[i].cor_exercito), stdin);
    territorios[i].cor_exercito[strcspn(territorios[i].cor_exercito, "\n")] = '\0'; // Remove o caractere de nova linha

    printf("Digite o numero de tropas: ");
    scanf("%d", &territorios[i].numero_tropas);
    getchar(); // Limpa o buffer de entrada
} 
printf("=====================================\n");
printf("    MAPA DO MUNDO - ESTADO ATUAL\n");
printf("=====================================\n");
    for(int i = 0; i < 5; i++) {
    printf("TERRITORIO %d:\n", i + 1);
    printf("  - Nome: %s\n", territorios[i].nome_territorio);
    printf("  - Cor do Exercito: %s\n", territorios[i].cor_exercito);
    printf("  - Numero de Tropas: %d\n\n", territorios[i].numero_tropas);
    printf("-------------------------------------------------\n");
}
return 0;
}
