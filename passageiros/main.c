#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int fidelidade; // 1 para sim, 0 para não
    int pontosFidelidade;
} Passageiro;

typedef struct {
    char username[20];
    char senha[20];
} Administrador;

int main()
{
    printf("Hello world!\n");
    return 0;
}
