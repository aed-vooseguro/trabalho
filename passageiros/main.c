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

int verificarUsuario(int *codigoUsuario) {
    int tipoUsuario;
    printf("Escolha o tipo de usuário:\n1. Administrador\n2. Passageiro\n");
    printf("Opção: ");
    scanf("%d", &tipoUsuario);

    if (tipoUsuario == 1) {
        char username[20], senha[20];
        printf("Digite o nome de usuário do administrador: ");
        scanf("%s", username);
        printf("Digite a senha: ");
        scanf("%s", senha);

        // Verifica o username e a senha com dados armazenados
        if (strcmp(username, "admin") == 0 && strcmp(senha, "1234") == 0) {
            printf("Login de administrador bem-sucedido!\n");
            return 1;
        } else {
            printf("Usuário ou senha incorretos!\n");
            return -1;
        }
    } else if (tipoUsuario == 2) {
        printf("Você possui cadastro? (1-Sim, 0-Não): ");
        int possuiCadastro;
        scanf("%d", &possuiCadastro);

        if (possuiCadastro) {
            printf("Informe o código do passageiro: ");
            scanf("%d", codigoUsuario);
            return 2;
        } else {
            *codigoUsuario = -1; // Código -1 indica novo cadastro
            return 0;
        }
    } else {
        printf("Opção invalida!\n");
        return -1;
    }
}

void atualizarPontosFidelidade(Passageiro *passageiro) {
    if (passageiro->fidelidade == 1) {
        passageiro->pontosFidelidade += 10;
        printf("Pontos de fidelidade atualizados. Total de pontos: %d\n", passageiro->pontosFidelidade);
    } else {
        printf("Passageiro não participa do programa de fidelidade.\n");
    }
}



int main()
{
    printf("Hello world!\n");
    return 0;
}
