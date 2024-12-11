#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

#include "cadastro_voo.c"
#include "cadastro_tripulacao.c"
#include "passageiros.c"
#include "gerencia_assentos.c"


int main() {
    Passageiro passageiros[100]; // Supondo um limite de 100 passageiros
    int totalPassageiros = 0;
    int opcao, codigoUsuario;
    int codigoAtual = 1;

    while (1)
    {
        int tipoUsuario = verificarUsuario(&codigoUsuario);

        if (tipoUsuario == 1)
        {
            printf("Menu do Administrador:\n");
            printf("1. Cadastrar Passageiro\n2. Cadastrar tripulacao\n3. Cadastrar voos\n4. Gerenciar Assentos\n5. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            printf("\n");

            if (opcao == 1)
            {
                cadastrarPassageiro(&passageiros[totalPassageiros++], &codigoAtual);
            }
            else if (opcao == 2)
            {
                cadastroTripulacaoMain();
            }
            else if (opcao == 3)
            {
                cadastroVooMain();
            }
            else if (opcao == 4)
            {
                gerenciaAssentosMain();
            }
            else if (opcao == 5)
            {
                printf("Saindo...\n");
                break;
            }
            else
            {
                printf("Opcao invalida!\n");
            }
        }
        else if (tipoUsuario == 2)
        {
            printf("Menu do Passageiro:\n");
            printf("1. Atualizar Pontos de Fidelidade\n2. Buscar e Editar Dados\n3. Sair\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            printf("\n");

            if (opcao == 1)
            {
                for (int i = 0; i < totalPassageiros; i++)
                {
                    if (passageiros[i].codigo == codigoUsuario)
                    {
                        atualizarPontosFidelidade(&passageiros[i]);
                        break;
                    }
                }
            }
            else if (opcao == 2)
            {
                buscarEEditarPassageiro(passageiros, totalPassageiros, codigoUsuario);
            }
            else if (opcao == 3)
            {
                printf("Saindo...\n");
                break;
            }
            else
            {
                printf("Opcao invalida!\n");
            }
        }
        else if (tipoUsuario == 0)
        {
            cadastrarPassageiro(&passageiros[totalPassageiros++], &codigoAtual);
            printf("Bem-vindo! Voce agora pode acessar as funcionalidades do sistema.\n");
        }
        else if (tipoUsuario == 3)
        {
            break;
        }

    }

    return 0;
}
