#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int codigo_existente(int codigos[], int j, int codigo)
{

    for (int i = 0; i < j; i++)
    {
        if (codigos[i] == codigo)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void cadastro_tripulacao(int codigo, const char *nome, const char *telefone, const char *cargo)
{

    tripulacao t[50];
    int codigos[50];
    int i = 0, j = 0;
    char a[6];
    int qtdTripulacao;
    int verificadorCodigo;


    FILE *arquivo = fopen("tripulacao.dat", "ab");
    if (!arquivo)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    do
    {
        printf("Digite a quantidade de tripulantes a serem cadastrados: ");
        scanf("%d", &qtdTripulacao);
    } while (qtdTripulacao <= 0);

    do
    {

        printf("Cadastro da Tripulacao %d.\n", i + 1);

        do{
            verificadorCodigo = 0;
            printf("Digite o codigo da pessoa %d: ", i + 1);
            scanf("%d", &t[i].codigo);
            getchar();

            if (t[i].codigo < 0)
            {
                printf("Codigos negativos sao invalidos. Digite novamente.\n");
                verificadorCodigo = 1;
            }

            if (codigo_existente(codigos, j, t[i].codigo))
            {
                printf("Esse codigo ja existe. Digite novamente.\n");
                verificadorCodigo = 1;
            }

        } while (verificadorCodigo == 1);

        printf("Digite o nome da pessoa %d: ", i + 1);
        fgets(t[i].nome, 20, stdin);

        t[i].nome[strcspn(t[i].nome, "\n")] = '\0';

        // if (strcmp(t[i].nome, "SAIR") == 0){
        //     printf("Voce saiu do sistema.");
        //     break;
        // }

        printf("Digite o telefone da pessoa %d: ", i + 1);
        fgets(t[i].telefone, 20, stdin);

        t[i].telefone[strcspn(t[i].telefone, "\n")] = '\0';

        // if (strcmp(t[i].telefone, "SAIR") == 0){
        //     printf("Voce saiu do sistema.");
        //     break;
        // }

        printf("Digite o cargo da pessoa %d: (Piloto, Copiloto ou Comissario)", i + 1);
        fgets(t[i].cargo, 10, stdin);

        t[i].cargo[strcspn(t[i].cargo, "\n")] = '\0';

        // if (strcmp(t[i].cargo, "SAIR") == 0){
        //     printf("Voce saiu do sistema.");
        //     break;
        // }

        codigos[j] = t[i].codigo;
        j++;
        fwrite(&t[i], sizeof(tripulacao), 1, arquivo);
        i++;

    } while (i < qtdTripulacao);
    fclose(arquivo);
}

int cadastroTripulacaoMain()
{
    int codigo;
    char nome[20], telefone[15], cargo[10];

    cadastro_tripulacao(codigo, nome, telefone, cargo);
}
