#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int passageirosCadastrados[100];

void cadastrarPassageiro(Passageiro *passageiro, int *codigoAtual)
{
    FILE *arquivo = fopen("novoPassageiro.dat", "ab");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    passageiro->codigo = (*codigoAtual)++; // Incrementa o c�digo automaticamente

    printf("Cadastro de Passageiro\n");
    printf("Informe o nome do passageiro: ");
    scanf(" %[^\n]", passageiro->nome);

    printf("Informe o endereco do passageiro: ");
    scanf(" %[^\n]", passageiro->endereco);

    printf("Informe o telefone do passageiro: ");
    scanf(" %[^\n]", passageiro->telefone);

    printf("O passageiro participa do programa de fidelidade? (1-Sim, 0-Nao): ");
    scanf("%d", &passageiro->fidelidade);

    passageiro->pontosFidelidade = 0; // Inicializa com zero pontos de fidelidade

    fwrite(passageiro, sizeof(Passageiro), 1, arquivo);
    fclose(arquivo);

    for (int i = 0; i < 100; i++){
         if (!passageirosCadastrados[i]){
            passageirosCadastrados[i] = passageiro->codigo;
            break;
         }
      }

    printf("Passageiro cadastrado com sucesso! Codigo do passageiro: %d\n", passageiro->codigo);
}

int verificarUsuario(int *codigoUsuario)
{
    int tipoUsuario;
    printf("Escolha o tipo de usuario:\n1. Administrador\n2. Passageiro\n3. Sair\n");
    printf("Opcao: ");
    scanf("%d", &tipoUsuario);

    if (tipoUsuario == 1)
    {
        char username[20], senha[20];
        printf("Digite o nome de usuario do administrador: ");
        scanf("%s", username);
        printf("Digite a senha: ");
        scanf("%s", senha);

        // Verifica o username e a senha com dados armazenados
        if (strcmp(username, "admin") == 0 && strcmp(senha, "1234") == 0)
        {
            printf("-----------------------------------\n");
            printf("Login de administrador bem sucedido!\n");
            printf("-----------------------------------\n");
            return 1;
        }
        else
        {
            printf("\nUsuario ou senha incorretos!\n");
            return -1;
        }
    }
    else if (tipoUsuario == 2)
    {
        printf("Voce possui cadastro? (1-Sim, 0-Nao): ");
        int possuiCadastro;
        scanf("%d", &possuiCadastro);

        if (possuiCadastro)
        {
            printf("\nInforme o codigo do passageiro: ");
            scanf("%d", codigoUsuario);
            return 2;
        }
        else
        {
            *codigoUsuario = -1; // C�digo -1 indica novo cadastro
            return 0;
        }
    }
    else if (tipoUsuario == 3)
    {
        printf("Saindo...\n");
        return 3;
    }
    else
    {
        printf("Opcao invalida!\n");
        return -1;
    }
}

void atualizarPontosFidelidade(Passageiro *passageiro)
{
    if (passageiro->fidelidade == 1)
    {
        FILE *arquivo = fopen("passageiroAtualizadoFidelidade.dat", "ab");
        passageiro->pontosFidelidade += 10;
        fwrite(passageiro, sizeof(Passageiro), 1, arquivo);
        fclose(arquivo);
        printf("-----------------------------------\n");
        printf("Pontos de fidelidade atualizados. Total de pontos: %d\n", passageiro->pontosFidelidade);
        printf("-----------------------------------\n");

    }
    else
    {
        printf("Passageiro nao participa do programa de fidelidade.\n");
    }
}

void buscarEEditarPassageiro(Passageiro *passageiros, int totalPassageiros, int codigo)
{
    for (int i = 0; i < totalPassageiros; i++)
    {
        if (passageiros[i].codigo == codigo)
        {
            FILE *arquivo = fopen("passageiroEditado.dat", "ab");
            if (!arquivo)
            {
                printf("Erro ao abrir o arquivo.\n");
                return;
            }
            printf("Passageiro encontrado:\n");
            printf("Nome: %s\n", passageiros[i].nome);
            printf("Endereco: %s\n", passageiros[i].endereco);
            printf("Telefone: %s\n", passageiros[i].telefone);
            printf("Deseja editar as informacoes? (1-Sim, 0-Nao): ");
            int editar;
            scanf("%d", &editar);

            if (editar == 1)
            {
                printf("Novo endere�o: ");
                scanf(" %[^\n]", passageiros[i].endereco);
                printf("Novo telefone: ");
                scanf(" %[^\n]", passageiros[i].telefone);
                printf("Informacoes atualizadas com sucesso!\n");
            }

            fwrite(&passageiros[i], sizeof(Passageiro), 1, arquivo);
            fclose(arquivo);
            return;
        }
    }
    printf("Passageiro nao encontrado.\n");
}

// int passageirosMain()
// {
//     Passageiro passageiros[100]; // Supondo um limite de 100 passageiros
//     int totalPassageiros = 0;
//     int opcao, codigoUsuario;
//     int codigoAtual = 1;

//     while (1)
//     {
//         int tipoUsuario = verificarUsuario(&codigoUsuario);

//         if (tipoUsuario == 1)
//         {
//             printf("Menu do Administrador:\n");
//             printf("1. Cadastrar Passageiro\n2. Cadastrar tripulacao\n3. Cadastrar voos\n4. Gerenciar Assentos\n5. Sair\n");
//             printf("Escolha uma opcao: ");
//             scanf("%d", &opcao);

//             if (opcao == 1)
//             {
//                 cadastrarPassageiro(&passageiros[totalPassageiros++], &codigoAtual);
//             }
//             else if (opcao == 2)
//             {
//                 cadastroTripulacaoMain();
//             }
//             else if (opcao == 3)
//             {
//                 cadastroVooMain();
//             }
//             else if (opcao == 4)
//             {
//                 gerenciaAssentosMain();
//             }
//             else if (opcao == 5)
//             {
//                 printf("Saindo...\n");
//                 break;
//             }
//             else
//             {
//                 printf("Opcao invalida!\n");
//             }
//         }
//         else if (tipoUsuario == 2)
//         {
//             printf("Menu do Passageiro:\n");
//             printf("1. Atualizar Pontos de Fidelidade\n2. Buscar e Editar Dados\n3. Sair\n");
//             printf("Escolha uma opcao: ");
//             scanf("%d", &opcao);

//             if (opcao == 1)
//             {
//                 for (int i = 0; i < totalPassageiros; i++)
//                 {
//                     if (passageiros[i].codigo == codigoUsuario)
//                     {
//                         atualizarPontosFidelidade(&passageiros[i]);
//                         break;
//                     }
//                 }
//             }
//             else if (opcao == 2)
//             {
//                 buscarEEditarPassageiro(passageiros, totalPassageiros, codigoUsuario);
//             }
//             else if (opcao == 3)
//             {
//                 printf("Saindo...\n");
//                 break;
//             }
//             else
//             {
//                 printf("Op��o invalida!\n");
//             }
//         }
//         else if (tipoUsuario == 0)
//         {
//             cadastrarPassageiro(&passageiros[totalPassageiros++], &codigoAtual);
//             printf("Bem-vindo! Voce agora pode acessar as funcionalidades do sistema.\n");
//         }
//         else if (tipoUsuario == 3)
//         {
//             break;
//         }

//     }

//     return 0;
// }
