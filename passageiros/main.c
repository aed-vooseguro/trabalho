#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int fidelidade; // 1 para sim, 0 para n�o
    int pontosFidelidade;
} Passageiro;

int main()
{
    printf("Hello world!\n");
    return 0;
}
