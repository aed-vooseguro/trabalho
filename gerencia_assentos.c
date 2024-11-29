#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

// Definindo a matriz tridimensional de assentos
#define MAX_VOOS 100
#define MAX_ASSENTOS 200

Assento voosAssentos[MAX_VOOS][MAX_ASSENTOS];

// Função para calcular a quantidade de assentos disponíveis em um voo
int quantidade_assentos_disponiveis(int codigo_voo) {
    int count = 0;
    for (int i = 0; i < MAX_ASSENTOS; i++) {
        if (voosAssentos[codigo_voo][i].status == 0) { // 0 = Livre
            count++;
        }
    }
    return count;
}

// Função para cadastrar assentos para um voo
void cadastro_assento(int codigo_voo) {
    FILE *arquivo_voos = fopen("voos.dat", "rb");
    FILE *arquivo_assentos = fopen("assentos.dat", "ab");
    if (!arquivo_voos || !arquivo_assentos) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int encontrou = 0, qtd_assentos;

    // Verifica se o voo existe na lista de voos cadastrados
    for (int i = 0; i < 100; i++) {
        if (voosCadastrados[i] == codigo_voo) {
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Voo não encontrado.\n");
        fclose(arquivo_voos);
        fclose(arquivo_assentos);
        return;
    }

    printf("Digite a quantidade de assentos no voo %d: ", codigo_voo);
    scanf("%d", &qtd_assentos);

    // Cadastra os assentos para o voo
    for (int i = 1; i <= qtd_assentos; i++) {
        Assento a;
        a.numero = i;
        a.codigoVoo = codigo_voo;
        a.status = 0; // 0 = Livre
        voosAssentos[codigo_voo][i - 1] = a;  // Atribui o assento à matriz tridimensional
        fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
    }

    printf("Assentos cadastrados com sucesso para o voo %d.\n", codigo_voo);

    fclose(arquivo_voos);
    fclose(arquivo_assentos);
}

// Função para realizar reserva de um assento
void realizar_reserva(int codigo_voo, int numero_assento, int codigo_passageiro) {
    FILE *arquivo_assentos = fopen("assentos.dat", "r+b");
    FILE *arquivo_reservas = fopen("reservas.dat", "ab");
    if (!arquivo_assentos || !arquivo_reservas) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Assento a;
    int encontrou_assento = 0;

    // Verifica se o voo e assento estão disponíveis
    if (numero_assento <= 0 || numero_assento > MAX_ASSENTOS) {
        printf("Número de assento inválido.\n");
        fclose(arquivo_assentos);
        fclose(arquivo_reservas);
        return;
    }

    if (voosAssentos[codigo_voo][numero_assento - 1].status == 1) {
        printf("Assento já reservado.\n");
        fclose(arquivo_assentos);
        fclose(arquivo_reservas);
        return;
    }

    // Marca o assento como reservado
    voosAssentos[codigo_voo][numero_assento - 1].status = 1; // 1 = Ocupado
    voosAssentos[codigo_voo][numero_assento - 1].codigoPassageiro = codigo_passageiro;

    fseek(arquivo_assentos, -sizeof(Assento), SEEK_CUR);
    fwrite(&voosAssentos[codigo_voo][numero_assento - 1], sizeof(Assento), 1, arquivo_assentos);

    // Registra a reserva
    Reserva r;
    r.codigoVoo = codigo_voo;
    r.numeroAssento = numero_assento;
    r.codigoPassageiro = codigo_passageiro;
    fwrite(&r, sizeof(Reserva), 1, arquivo_reservas);

    printf("Reserva realizada com sucesso.\n");

    // Exibe a quantidade de assentos disponíveis
    int assentos_disponiveis = quantidade_assentos_disponiveis(codigo_voo);
    printf("Assentos disponíveis para o voo %d: %d\n", codigo_voo, assentos_disponiveis);

    fclose(arquivo_assentos);
    fclose(arquivo_reservas);
}

// Função para cancelar a reserva de um assento
void cancelar_reserva(int codigo_voo, int numero_assento) {
    FILE *arquivo_assentos = fopen("assentos.dat", "r+b");
    FILE *arquivo_reservas = fopen("reservas.dat", "rb");
    FILE *arquivo_reservas_temp = fopen("reservas_temp.dat", "wb");

    if (!arquivo_assentos || !arquivo_reservas || !arquivo_reservas_temp) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Assento a;
    int encontrou_assento = 0;

    // Encontra o assento e marca como livre
    while (fread(&a, sizeof(Assento), 1, arquivo_assentos)) {
        if (a.codigoVoo == codigo_voo && a.numero == numero_assento) {
            encontrou_assento = 1;
            a.status = 0; // Marca como livre
            fseek(arquivo_assentos, -sizeof(Assento), SEEK_CUR);
            fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
            break;
        }
    }

    if (!encontrou_assento) {
        printf("Assento não encontrado.\n");
        fclose(arquivo_assentos);
        fclose(arquivo_reservas);
        fclose(arquivo_reservas_temp);
        return;
    }

    // Cancela a reserva no arquivo de reservas
    Reserva r;
    while (fread(&r, sizeof(Reserva), 1, arquivo_reservas)) {
        if (!(r.codigoVoo == codigo_voo && r.numeroAssento == numero_assento)) {
            fwrite(&r, sizeof(Reserva), 1, arquivo_reservas_temp);
        }
    }

    fclose(arquivo_assentos);
    fclose(arquivo_reservas);
    fclose(arquivo_reservas_temp);

    remove("reservas.dat");
    rename("reservas_temp.dat", "reservas.dat");

    printf("Reserva cancelada e assento liberado.\n");
}

void gerenciaAssentosMain() {
    int opcao;

    do {
        printf("Menu de Gerenciamento de Assentos:\n");
        printf("1. Cadastrar Assento\n");
        printf("2. Reservar Assento\n");
        printf("3. Cancelar Reserva\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int codigo_voo;
                printf("Digite o codigo do voo: ");
                scanf("%d", &codigo_voo);
                cadastro_assento(codigo_voo);
                break;
            }
            case 2: {
                int codigo_voo, numero_assento, codigo_passageiro;
                printf("Digite o codigo do voo: ");
                scanf("%d", &codigo_voo);
                printf("Digite o numero do assento: ");
                scanf("%d", &numero_assento);
                printf("Digite o codigo do passageiro: ");
                scanf("%d", &codigo_passageiro);
                realizar_reserva(codigo_voo, numero_assento, codigo_passageiro);
                break;
            }
            case 3: {
                int codigo_voo, numero_assento;
                printf("Digite o codigo do voo: ");
                scanf("%d", &codigo_voo);
                printf("Digite o numero do assento: ");
                scanf("%d", &numero_assento);
                cancelar_reserva(codigo_voo, numero_assento);
                break;
            }
            case 4:
                printf("Saindo...\n");
                return;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 4);
}
