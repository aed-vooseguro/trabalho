#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



// Estruturas
typedef struct {
    int codigoVoo;
    char origem[50];
    char destino[50];
    char status; // 'A' para ativo, 'I' para inativo
    float tarifa;
} Voo;

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

// Prototipação
int cadastrarAssentos();
int reservarAssento();
int liberarReserva();
void exibirAssentos(int codigoVoo);
int validarEntradaNumerica(const char *mensagem);
int vooValido(int codigoVoo);

// Função principal
int main() {
    int opcao;

    do {
        printf("\n=== Sistema de Gerenciamento de Voos ===\n");
        printf("1. Cadastrar Assentos\n");
        printf("2. Reservar Assento\n");
        printf("3. Liberar Reserva\n");
        printf("4. Exibir Assentos\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
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
                printf("Digite o código do voo: ");
                int codigo = validarEntradaNumerica("");
                exibirAssentos(codigo);
                break;
            case 5:
                printf("Encerrando o sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}

// Função para validar se o voo é válido
int vooValido(int codigoVoo) {
    FILE *arquivo = fopen("voos.dat", "rb");
    Voo voo;

    if (!arquivo) {
        printf("Erro ao abrir o arquivo de voos.\n");
        return 0;
    }

    while (fread(&voo, sizeof(Voo), 1, arquivo)) {
        if (voo.codigoVoo == codigoVoo && voo.status == 'A') {
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;
}

// Função para cadastrar assentos
int cadastrarAssentos() {
    FILE *arquivo = fopen("assentos.dat", "ab");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return 1;
    }

    Assento assento;
    int total;

    printf("Digite o código do voo: ");
    assento.codigoVoo = validarEntradaNumerica("");

    if (!vooValido(assento.codigoVoo)) {
        printf("Erro: Código de voo inválido ou inativo.\n");
        fclose(arquivo);
        return 1;
    }

    printf("Quantos assentos deseja cadastrar? ");
    total = validarEntradaNumerica("");

    for (int i = 0; i < total; i++) {
        printf("Digite o número do assento: ");
        assento.numero = validarEntradaNumerica("");
        assento.status = 'L'; // Todos os assentos começam livres

        fwrite(&assento, sizeof(Assento), 1, arquivo);
        printf("Assento %d cadastrado com sucesso!\n", assento.numero);
    }

    fclose(arquivo);
    return 0;
}

// Função para reservar um assento
int reservarAssento() {
    FILE *arquivo = fopen("assentos.dat", "rb+");
    FILE *reservas = fopen("reservas.dat", "ab");
    if (!arquivo || !reservas) {
        printf("Erro ao abrir arquivos necessários.\n");
        return 1;
    }

    Reserva reserva;
    Assento assento;
    int encontrado = 0;

    printf("Digite o código do voo: ");
    reserva.codigoVoo = validarEntradaNumerica("");

    if (!vooValido(reserva.codigoVoo)) {
        printf("Erro: Código de voo inválido ou inativo.\n");
        fclose(arquivo);
        fclose(reservas);
        return 1;
    }

    printf("Digite o número do assento: ");
    reserva.numeroAssento = validarEntradaNumerica("");

    printf("Digite o código do passageiro: ");
    reserva.codigoPassageiro = validarEntradaNumerica("");

    while (fread(&assento, sizeof(Assento), 1, arquivo)) {
        if (assento.codigoVoo == reserva.codigoVoo && assento.numero == reserva.numeroAssento) {
            encontrado = 1;

            if (assento.status == 'O') {
                printf("Erro: Assento já está ocupado.\n");
                fclose(arquivo);
                fclose(reservas);
                return 1;
            }

            assento.status = 'O';
            fseek(arquivo, -sizeof(Assento), SEEK_CUR);
            fwrite(&assento, sizeof(Assento), 1, arquivo);

            fwrite(&reserva, sizeof(Reserva), 1, reservas);
            printf("Reserva realizada com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Erro: Assento não encontrado para este voo.\n");
    }

    fclose(arquivo);
    fclose(reservas);
    return 0;
}

// Função para liberar uma reserva
int liberarReserva() {
    FILE *arquivo = fopen("assentos.dat", "rb+");
    FILE *reservas = fopen("reservas.dat", "rb+");
    if (!arquivo || !reservas) {
        printf("Erro ao abrir arquivos necessários.\n");
        return 1;
    }

    Reserva reserva;
    Assento assento;
    int encontrado = 0, codigoVoo, numeroAssento;

    printf("Digite o código do voo: ");
    codigoVoo = validarEntradaNumerica("");

    if (!vooValido(codigoVoo)) {
        printf("Erro: Código de voo inválido ou inativo.\n");
        fclose(arquivo);
        fclose(reservas);
        return 1;
    }

    printf("Digite o número do assento: ");
    numeroAssento = validarEntradaNumerica("");

    while (fread(&assento, sizeof(Assento), 1, arquivo)) {
        if (assento.codigoVoo == codigoVoo && assento.numero == numeroAssento) {
            encontrado = 1;

            if (assento.status == 'L') {
                printf("Erro: Assento já está livre.\n");
                fclose(arquivo);
                fclose(reservas);
                return 1;
            }

            assento.status = 'L';
            fseek(arquivo, -sizeof(Assento), SEEK_CUR);
            fwrite(&assento, sizeof(Assento), 1, arquivo);

            // Atualizar as reservas
            FILE *temp = fopen("temp.dat", "wb");
            if (!temp) {
                printf("Erro ao criar arquivo temporário.\n");
                fclose(arquivo);
                fclose(reservas);
                return 1;
            }

            while (fread(&reserva, sizeof(Reserva), 1, reservas)) {
                if (!(reserva.codigoVoo == codigoVoo && reserva.numeroAssento == numeroAssento)) {
                    fwrite(&reserva, sizeof(Reserva), 1, temp);
                }
            }

            fclose(reservas);
            fclose(temp);

            remove("reservas.dat");
            rename("temp.dat", "reservas.dat");

            printf("Reserva liberada com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Erro: Assento não encontrado para este voo.\n");
    }

    fclose(arquivo);
    return 0;
}

// Função para exibir assentos de um voo
void exibirAssentos(int codigoVoo) {
    FILE *arquivo = fopen("assentos.dat", "rb");
    Assento assento;

    if (!arquivo) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }

    printf("Assentos do voo %d:\n", codigoVoo);
    printf("Número\tStatus\n");

    while (fread(&assento, sizeof(Assento), 1, arquivo)) {
        if (assento.codigoVoo == codigoVoo) {
            printf("%d\t%c\n", assento.numero, assento.status);
        }
    }

    fclose(arquivo);
}

// Função para validar entradas numéricas
int validarEntradaNumerica(const char *mensagem) {
    char entrada[100];
    int valido = 0;

    while (!valido) {
        printf("%s", mensagem);
        scanf("%s", entrada);

        valido = 1;
        for (int i = 0; i < strlen(entrada); i++) {
            if (!isdigit(entrada[i])) {
                valido = 0;
                printf("Erro: Digite apenas números.\n");
                break;
            }
        }
    }

    return atoi(entrada);
}
