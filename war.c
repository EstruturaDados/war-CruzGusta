#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// definição de struct
typedef struct{
    char nome[30];
    char cor[10];
    int tropas;
}Territorio;

// cadastrar territorios
void cadastrarTerritorios(Territorio *territorios, int quantidade){
    printf("  Cadastro para territorios  \n\n");

    for(int i = 0; i < quantidade; i++){
        printf("Numero de territorio: %d \n", i + 1);

        printf("Nome do territorio: ");
        scanf("%s", territorios[i].nome);

        printf("Cor do territorio: ");
        scanf("%s", territorios[i].cor);

        printf("Numero de tropas: ");
        scanf("%d", &(territorios + i)->tropas);

        printf("\n---------------------------------\n");
    }
}

// mostrar territorios
void mostrarTerritorios(Territorio* territorios, int quantidade){
    printf("\n   relatorio de territorios cadastrados   \n");

    for(int i = 0; i < quantidade; i++){
        printf("\n territorio: %d", i + 1);
        printf(" Nome: %s\n", territorios[i].nome);
        printf(" Cor: %s\n", territorios[i].cor);
        printf(" Tropas: %d\n", territorios[i].tropas);
        printf("-----------------------------------------\n");
    }
}

// ataque
void atacar(Territorio* atacante, Territorio *defensor){
    int ladoAtacante = rand() % 6 + 1;
    int ladoDefensor = rand() % 6 + 1;

    printf("Atacante : %d\n", ladoAtacante);
    printf("Defensor: %d\n", ladoDefensor);

    if(ladoAtacante > ladoDefensor){
        printf("   O atacante venceu! \n");

        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;

    }else{
        printf("   o defensor venceu! \n");

        if(atacante->tropas > 1){
            atacante->tropas--;
        }
    }
}

// liberar memoria
void liberarMemoria(Territorio* territorios){
    free(territorios);
}

// sortear missao
void atribuirMissao(char* destino, char* missoes[], int totalMissoes){
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}

// verificar missao (versão simples)
int verificarMissao(char* missao, Territorio* mapa, int tamanho){

    int contador = 0;

    if(strcmp(missao, "Conquistar 2 territorios") == 0){

        for(int i = 0; i < tamanho; i++){
            if(strcmp(mapa[i].cor, "azul") == 0){
                contador++;
            }
        }

        if(contador >= 2){
            return 1;
        }
    }

    return 0;
}

// main
int main(){

    srand(time(NULL));

    // missões
    char *missoes[] = {
        "Conquistar 2 territorios",
        "Eliminar a cor vermelha",
        "possuir 15 tropas"
    };

    // missão do jogador
    char *missaoJogador = malloc(100 * sizeof(char));

    // território
    int quantidade;

    printf("Quantos territorios você deseja cadastrar ? ");
    scanf("%d", &quantidade);

    Territorio *territorios = calloc(quantidade, sizeof(Territorio));

    // verificação de memória (CORRETA com ||)
    if(territorios == NULL || missaoJogador == NULL){
        printf("Erro ao alocar memoria.\n");

        free(territorios);
        free(missaoJogador);

        return 1;
    }

    // missão
    atribuirMissao(missaoJogador, missoes, 3);
    printf("Sua missao eh: %s\n", missaoJogador);

    // cadastro
    cadastrarTerritorios(territorios, quantidade);
    mostrarTerritorios(territorios, quantidade);

    // escolha de ataque
    int atacante, defensor;

    printf("Escolha o territorio do atacante: ");
    scanf("%d", &atacante);
    atacante--;

    printf("Escolha o territorio do defensor: ");
    scanf("%d", &defensor);
    defensor--;

    // regra de combate
    if(strcmp(territorios[atacante].cor, territorios[defensor].cor) == 0){
        printf("Nao eh permitido combate da mesma cor.\n");
    }else{

        atacar(&territorios[atacante], &territorios[defensor]);

        if(verificarMissao(missaoJogador, territorios, quantidade)){
            printf("Missao cumprida\n");
            printf("Jogador venceu\n");
        }

        printf("\n=== TERRITORIOS APOS O ATAQUE ===\n");
        mostrarTerritorios(territorios, quantidade);
    }

    // liberar memoria
    free(missaoJogador);
    liberarMemoria(territorios);

    return 0;
}