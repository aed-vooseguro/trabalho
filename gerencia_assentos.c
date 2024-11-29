#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"


#define MAX_ASSENTOS 200

int assentos[MAX_VOOS][MAX_ASSENTOS] = {0}; // Inicializa todos como livres

// Função para exibir os assentos de um voo
void exibir_assentos(int codigo_voo, int qtd_assentos) {
    printf("Mapa de Assentos do Voo %d:\n", codigo_voo);
    for (int i = 0; i < qtd_assentos; i++) {
        printf("[%d: %s] ", i + 1, assentos[codigo_voo][i] == 0 ? "Livre" : "Ocupado");
        if ((i + 1) % 10 == 0) printf("\n"); // Quebra de linha para melhor visualização
    }
    printf("\n");
}

// Cadastro de assentos
void cadastro_assento(int codigo_voo) {
    FILE *arquivo_assentos = fopen("assentos.dat", "ab");
    if (!arquivo_assentos) {
        printf("Erro ao abrir o arquivo de assentos.\n");
        return;
    }

    int qtd_assentos;
    printf("Digite a quantidade de assentos no voo %d: ", codigo_voo);
    scanf("%d", &qtd_assentos);

    for (int i = 0; i < qtd_assentos; i++) {
        Assento a;
        a.numero = i + 1;
        a.codigoVoo = codigo_voo;
        a.status = 0; // 0 = Livre
        fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
        assentos[codigo_voo][i] = 0; // Atualiza a matriz
    }

    printf("Assentos cadastrados com sucesso para o voo %d.\n", codigo_voo);
    exibir_assentos(codigo_voo, qtd_assentos);

    fclose(arquivo_assentos);
}

// Realizar reserva
void realizar_reserva(int codigo_voo, int numero_assento, int codigo_passageiro) {
    FILE *arquivo_assentos = fopen("assentos.dat", "r+b");
    FILE *arquivo_reservas = fopen("reservas.dat", "ab");
    if (!arquivo_assentos || !arquivo_reservas) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    int encontrou_assento = 0;
    Assento a;

    while (fread(&a, sizeof(Assento), 1, arquivo_assentos)) {
        if (a.codigoVoo == codigo_voo && a.numero == numero_assento) {
            encontrou_assento = 1;
            if (a.status == 1) { // Assento já ocupado
                printf("Assento %d já ocupado.\n", numero_assento);
                fclose(arquivo_assentos);
                fclose(arquivo_reservas);
                return;
            }

            a.status = 1; // Marca como ocupado
            fseek(arquivo_assentos, -sizeof(Assento), SEEK_CUR);
            fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
            assentos[codigo_voo][numero_assento - 1] = 1; // Atualiza a matriz
            break;
        }
    }

    if (!encontrou_assento) {
        printf("Assento não encontrado.\n");
    } else {
        Reserva r;
        r.codigoVoo = codigo_voo;
        r.numeroAssento = numero_assento;
        r.codigoPassageiro = codigo_passageiro;
        fwrite(&r, sizeof(Reserva), 1, arquivo_reservas);

        printf("Reserva realizada com sucesso.\n");
        exibir_assentos(codigo_voo, MAX_ASSENTOS);
    }

    fclose(arquivo_assentos);
    fclose(arquivo_reservas);
}

// Cancelar reserva
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

    while (fread(&a, sizeof(Assento), 1, arquivo_assentos)) {
        if (a.codigoVoo == codigo_voo && a.numero == numero_assento) {
            encontrou_assento = 1;
            a.status = 0; // Marca como livre
            fseek(arquivo_assentos, -sizeof(Assento), SEEK_CUR);
            fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
            assentos[codigo_voo][numero_assento - 1] = 0; // Atualiza a matriz
            break;
        }
    }

    if (!encontrou_assento) {
        printf("Assento não encontrado.\n");
    } else {
        Reserva r;
        while (fread(&r, sizeof(Reserva), 1, arquivo_reservas)) {
            if (!(r.codigoVoo == codigo_voo && r.numeroAssento == numero_assento)) {
                fwrite(&r, sizeof(Reserva), 1, arquivo_reservas_temp);
            }
        }

        printf("Reserva cancelada e assento liberado.\n");
        exibir_assentos(codigo_voo, MAX_ASSENTOS);
    }

    fclose(arquivo_assentos);
    fclose(arquivo_reservas);
    fclose(arquivo_reservas_temp);

    remove("reservas.dat");
    rename("reservas_temp.dat", "reservas.dat");
}

// Main
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
