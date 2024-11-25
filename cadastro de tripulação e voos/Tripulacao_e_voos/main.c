#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para usar isdigit()

// Estruturas
typedef struct {
    int codigo;
    char nome[100];
    char telefone[20];
    char cargo[20];
} Tripulacao;

typedef struct {
    int codigoVoo;
    char data[12];
    char hora[6];
    char origem[50];
    char destino[50];
    int codigoAviao;
    int codigoPiloto;
    int codigoCopiloto;
    float tarifa;
    char status[20];
} Voo;

// Funções
int cadastrarTripulacao();
int cadastrarVoo();
int pesquisarTripulacao();
int validarTripulacao(int piloto, int copiloto);

int main() {
    int opcao;

    do {
        printf("\n===== Sistema de Gerenciamento de Voos =====\n");
        printf("1. Cadastrar Tripulação\n");
        printf("2. Cadastrar Voo\n");
        printf("3. Pesquisar Tripulação\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) { // Validação de entrada
            printf("Erro: Digite apenas números.\n");
            while (getchar() != '\n'); // Limpa o buffer
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarTripulacao();
                break;
            case 2:
                cadastrarVoo();
                break;
            case 3:
                pesquisarTripulacao();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

int cadastrarTripulacao() {
    Tripulacao trip;
    FILE *arquivo = fopen("tripulacao.dat", "ab");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para cadastro de tripulação.\n");
        return 1;
    }

    printf("\n===== Cadastro de Tripulação =====\n");

    printf("Código (apenas números): ");
    if (scanf("%d", &trip.codigo) != 1) {
        printf("Erro: Digite um número válido.\n");
        while (getchar() != '\n'); // Limpa o buffer
        fclose(arquivo);
        return 1;
    }

    printf("Nome: ");
    getchar(); // Limpa o '\n' deixado pelo scanf
    fgets(trip.nome, sizeof(trip.nome), stdin);
    trip.nome[strcspn(trip.nome, "\n")] = '\0'; // Remove o '\n'

    printf("Telefone: ");
    fgets(trip.telefone, sizeof(trip.telefone), stdin);
    trip.telefone[strcspn(trip.telefone, "\n")] = '\0';
