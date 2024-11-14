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

void cadastrarPassageiro(Passageiro *passageiro, int *codigoAtual) {
    passageiro->codigo = (*codigoAtual)++; // Incrementa o código automaticamente

    printf("Cadastro de Passageiro\n");
    printf("Informe o nome do passageiro: ");
    scanf(" %[^\n]", passageiro->nome);

    printf("Informe o endereco do passageiro: ");
    scanf(" %[^\n]", passageiro->endereco);

    printf("Informe o telefone do passageiro: ");
    scanf(" %[^\n]", passageiro->telefone);

    printf("O passageiro participa do programa de fidelidade? (1-Sim, 0-Não): ");
    scanf("%d", &passageiro->fidelidade);

    passageiro->pontosFidelidade = 0; // Inicializa com zero pontos de fidelidade

    printf("Passageiro cadastrado com sucesso! Codigo do passageiro: %d\n", passageiro->codigo);
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
