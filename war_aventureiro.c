#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Estrutura
typedef struct {
    char nome_territorio[30];
    char cor_exercito[10];
    int numero_tropas;
} Territorio;

// ---------- FUNÇÕES ----------

// Cadastro
void cadastrarTerritorios(Territorio* territorios, int* total) {
    for (int i = 0; i < *total; i++) {
        printf("\n======= Cadastro do territorio %d =======\n", i + 1);

        printf("Nome: ");
        fgets((territorios + i)->nome_territorio, 30, stdin);
        (territorios + i)->nome_territorio[strcspn((territorios + i)->nome_territorio, "\n")] = '\0';

        printf("Cor do exercito: ");
        fgets((territorios + i)->cor_exercito, 10, stdin);
        (territorios + i)->cor_exercito[strcspn((territorios + i)->cor_exercito, "\n")] = '\0';

        printf("Numero de tropas: ");
        scanf("%d", &((territorios + i)->numero_tropas));
        getchar();
    }
}

// Exibir mapa
void exibirTerritorios(Territorio* territorios, int* total) {
    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < *total; i++) {
        printf("%d. %s | Exercito: %s | Tropas: %d\n",
               i + 1,
               (territorios + i)->nome_territorio,
               (territorios + i)->cor_exercito,
               (territorios + i)->numero_tropas);
    }
}

// Ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n%s ataca %s!\n", atacante->nome_territorio, defensor->nome_territorio);
    printf("Atacante rolou: %d | Defensor rolou: %d\n", dadoA, dadoD);

    if (dadoA > dadoD) {
        printf(">> Atacante venceu!\n");
        if (defensor->numero_tropas > 0){
            defensor->numero_tropas--;
        }
        if (defensor->numero_tropas == 0) {
            printf(">> Territorio conquistado!\n");
            strcpy(defensor->cor_exercito, atacante->cor_exercito);
        }

    } else if (dadoA < dadoD) {
        printf(">> Defensor venceu!\n");
        if (atacante->numero_tropas > 0){
            atacante->numero_tropas--;
        }
        if (atacante->numero_tropas == 0) {
            printf(">> Territorio conquistado!\n");
            strcpy(atacante->cor_exercito, defensor->cor_exercito);
        }
    } else {
        printf(">> Empate!\n");
    }
}

// Interface de ataque
void menuAtaque(Territorio* territorios, int* total) {
    int escolhaA, escolhaD;

    while (1) {
        exibirTerritorios(territorios, total);

        printf("\nEscolha o TERRITORIO ATACANTE (1-%d) ou 0 para sair: ", *total);
        scanf("%d", &escolhaA);
        getchar();

        if (escolhaA == 0) break;

        if (escolhaA < 1 || escolhaA > *total) {
            printf("Territorio atacante invalido!\n");
            continue;
        }

        Territorio* atacante = territorios + (escolhaA - 1);

        if (atacante->numero_tropas == 0) {
            printf("Esse territorio nao possui tropas!\n");
            continue;
        }

        printf("Escolha o TERRITORIO DEFENSOR (1-%d): ", *total);
        scanf("%d", &escolhaD);
        getchar();

        if (escolhaD < 1 || escolhaD > *total) {
            printf("Territorio defensor invalido!\n");
            continue;
        }

        if (escolhaA == escolhaD) {
            printf("Nao pode atacar o mesmo territorio!\n");
            continue;
        }

        Territorio* defensor = territorios + (escolhaD - 1);

        atacar(atacante, defensor);
    }
}

// Liberação de memória
void liberarMemoria(Territorio* territorios, int* total) {
    free(territorios);
    free(total);
}

// ---------- MAIN ----------

int main() {
    srand(time(NULL));

    int* total = malloc(sizeof(int));

    if (total == NULL) {
        printf("Erro de memoria!\n");
        return 1;
    }

    printf("Quantos territorios deseja cadastrar? ");
    if (scanf("%d", total) != 1 || *total <= 0) {
        printf("Entrada invalida!\n");
        free(total);
        return 1;
    }
    getchar();

    Territorio* territorios = malloc((*total) * sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro de memoria!\n");
        free(total);
        return 1;
    }

    cadastrarTerritorios(territorios, total);
    menuAtaque(territorios, total);

    liberarMemoria(territorios, total);

    printf("\nJogo encerrado com sucesso!\n");
    return 0;
}