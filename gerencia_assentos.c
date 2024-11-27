#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"



// aqui e o cadastro de assnetos (ele só funciona quando puxa o código do voo)
void cadastro_assento(int codigo_voo) {
    FILE *arquivo_voos = fopen("voos.dat", "rb");
    FILE *arquivo_assentos = fopen("assentos.dat", "ab");
    if (!arquivo_voos || !arquivo_assentos) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Voo v;
    int encontrou = 0, qtd_assentos;

    while (fread(&v, sizeof(Voo), 1, arquivo_voos)) {
        if (v.codigo_voo == codigo_voo) {
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

    for (int i = 1; i <= qtd_assentos; i++) {
        Assento a;
        a.numero_assento = i;
        a.codigo_voo = codigo_voo;
        a.status = 0; // 0 = Livre
        fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
    }

    printf("Assentos cadastrados com sucesso para o voo %d.\n", codigo_voo);

    fclose(arquivo_voos);
    fclose(arquivo_assentos);
}


// Aqui ele reserva o assento 

void realizar_reserva(int codigo_voo, int numero_assento, int codigo_passageiro) {
    FILE *arquivo_voos = fopen("voos.dat", "rb");
    FILE *arquivo_assentos = fopen("assentos.dat", "r+b");
    FILE *arquivo_reservas = fopen("reservas.dat", "ab");
    if (!arquivo_voos || !arquivo_assentos || !arquivo_reservas) {
        printf("Erro ao abrir os arquivos.\n");
        return;
    }

    Voo v;
    int encontrou_voo = 0;

    while (fread(&v, sizeof(Voo), 1, arquivo_voos)) {
        if (v.codigo_voo == codigo_voo && v.status == 1) { // Status 1 = Ativo
            encontrou_voo = 1;
            break;
        }
    }

    if (!encontrou_voo) {
        printf("Voo não encontrado ou inativo.\n");
        fclose(arquivo_voos);
        fclose(arquivo_assentos);
        fclose(arquivo_reservas);
        return;
    }

    Assento a;
    int encontrou_assento = 0;

    while (fread(&a, sizeof(Assento), 1, arquivo_assentos)) {
        if (a.codigo_voo == codigo_voo && a.numero_assento == numero_assento) {
            encontrou_assento = 1;
            if (a.status == 1) { // 1 = Ocupado
                printf("Assento já ocupado.\n");
                fclose(arquivo_voos);
                fclose(arquivo_assentos);
                fclose(arquivo_reservas);
                return;
            }
            a.status = 1; // Marca como ocupado
            fseek(arquivo_assentos, -sizeof(Assento), SEEK_CUR);
            fwrite(&a, sizeof(Assento), 1, arquivo_assentos);
            break;
        }
    }

    if (!encontrou_assento) {
        printf("Assento não encontrado.\n");
        fclose(arquivo_voos);
        fclose(arquivo_assentos);
        fclose(arquivo_reservas);
        return;
    }

    Reserva r;
    r.codigo_voo = codigo_voo;
    r.numero_assento = numero_assento;
    r.codigo_passageiro = codigo_passageiro;
    fwrite(&r, sizeof(Reserva), 1, arquivo_reservas);

    printf("Reserva realizada com sucesso.\n");

    fclose(arquivo_voos);
    fclose(arquivo_assentos);
    fclose(arquivo_reservas);
}


// Aqui voce voce consegue cancelar um assento reservado

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
        if (a.codigo_voo == codigo_voo && a.numero_assento == numero_assento) {
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

    Reserva r;
    while (fread(&r, sizeof(Reserva), 1, arquivo_reservas)) {
        if (!(r.codigo_voo == codigo_voo && r.numero_assento == numero_assento)) {
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
