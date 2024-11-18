#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ASSENTOS 100


// structs para usar
typedef struct {
    int numero;
    int codigoVoo;
    char status; // 'L' para livre, 'O' para ocupado
} Assento;

typedef struct {
    int codigoVoo;
    int numeroAssento;
    int codigoPassageiro;
} Reserva;

// Prototipa��o
int cadastrarAssentos();
int reservarAssento();
int liberarReserva();
void exibirAssentos(int codigoVoo);
int validarEntradaNumerica(const char *mensagem);

// Fun��o principal
int main() {
    int opcao;

    do {
        printf("\n=== Sistema de Gerenciamento de Voos ===\n");
        printf("1. Cadastrar Assentos\n");
        printf("2. Reservar Assento\n");
        printf("3. Liberar Reserva\n");
        printf("4. Sair\n");
        printf("Escolha uma op��o: ");
        opcao = validarEntradaNumerica("");

        switch (opcao) {
            case 1:
                cadastrarAssentos();
                break;
            case 2:
                reservarAssento();
                break;
            case 3:
                liberarReserva();
                break;
            case 4:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Op��o inv�lida. Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}

// Fun��o cadastrar assento

int cadastrarAssentos() {
    FILE *arquivo = fopen("assentos.dat", "ab");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return 1;
    }

    Assento assento;
    int total;

    printf("Digite o c�digo do voo: ");
    assento.codigoVoo = validarEntradaNumerica("");

    printf("Quantos assentos deseja cadastrar? ");
    total = validarEntradaNumerica("");

    for (int i = 0; i < total; i++) {
        printf("Digite o n�mero do assento: ");
        assento.numero = validarEntradaNumerica("");

        assento.status = 'L'; // Todos os assentos come�am livres
        fwrite(&assento, sizeof(Assento), 1, arquivo);
        printf("Assento %d cadastrado com sucesso!\n", assento.numero);
    }

    fclose(arquivo);
    return 0;
}
