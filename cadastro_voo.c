#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int voosCadastrados[100];
/*
VOO: c�digo do voo, data, hora, origem, destino, c�digo do avi�o, c�digo do piloto,
c�digo do copiloto, c�digo do comiss�rio, status (ativo/inativo), tarifa.

Cadastro de Voo:
o Deve ser poss�vel cadastrar informa��es sobre data, hora, origem, destino, tarifa,
tripula��o e o avi�o.
o Deve verificar a presen�a de ao menos um piloto e um copiloto para que o voo
seja marcado como ativo.

*/


void cadastro_voo(int codigo_voo, char data, char hora, char origem, char destino, int codigo_aviao, int codigo_piloto, int codigo_copiloto, int codigo_comissario, float tarifa){

     Voo v;
     int qtd_piloto = 0, qtd_copiloto = 0, i = 0;
     int qtdVoos;
     int vooJaExiste = 0;

    do
    {
        printf("Digite a quantidade de voos a serem cadastrados: ");
        scanf("%d", &qtdVoos);
    } while (qtdVoos <= 0);

    FILE *arquivo = fopen("voos.dat", "ab");

     do{
      if (!arquivo){
         printf("Erro ao abrir o arquivo.\n");
         return;
      }

     printf("Cadastro de Voo %d\n", i + 1);

   do{
      printf("Digite o Codigo do Voo %d: ", i + 1);
     scanf("%d", &v.codigo_voo);

     for (int i = 0; i < 100; i++){
         if (v.codigo_voo == voosCadastrados[i]){
            printf("Codigo de Voo ja existente. Digite outro codigo.\n");
            vooJaExiste = 1;
            break;
         }
      }
   }while (vooJaExiste == 1);

   
     

      //  if (v.codigo_voo == 0){
      //   printf("Voce saiu do sistema");
      //   break;
      //  }

     Data(data);
     Hora(hora);

     printf("\nDigite a Origem: ");
     fgets(v.origem, 20, stdin);

       v.origem[strcspn(v.origem, "\n")] = '\0';

      //  if (strcmp(v.origem, "SAIR") == 0){
      //     printf("Voce saiu do sistema");
      //     break;
      //  }

     printf("Digite o Destino: ");
     fgets(v.destino, 20, stdin);

       v.destino[strcspn(v.destino, "\n")] = '\0';

      //  if (strcmp(v.destino, "SAIR") == 0){
      //     printf("Voce saiu do sistema");
      //     break;
      //  }


     printf("Digite o Codigo do Aviao %d: ", i + 1);
     scanf("%d", &v.codigo_aviao);

      //   if (v.codigo_aviao == 0){
      //   printf("Voce saiu do sistema");
      //   break;
      //   }

     printf("Digite o Codigo do Piloto %d", i + 1);
     printf("\nCaso nao tenha Piloto, digite -1: ");
     scanf("%d", &v.codigo_piloto);

      //   if (v.codigo_piloto == 0){
      //   printf("Voce saiu do sistema");
      //   break;
      //   }

     if (v.codigo_piloto > 0){
        qtd_piloto++;
     }

     printf("Digite o Codigo do Copiloto %d", i + 1);
     printf("\nCaso nao tenha Copiloto, digite -1: ");
     scanf("%d", &v.codigo_copiloto);

      //   if (v.codigo_copiloto == 0){
      //   printf("Voce saiu do sistema");
      //   break;
      //   }

     if (v.codigo_copiloto > 0){
        qtd_copiloto++;
     }

     if (qtd_piloto > 0 && qtd_copiloto > 0){
        printf("Status: Voo %d Ativo\n", i + 1);
     }
     else{
        printf("Status: Voo %d Inativo\n", i + 1);
     }

     printf("Digite o Codigo do Comissario %d: ", i + 1);
     scanf("%d", &v.codigo_comissario);

      //   if (v.codigo_comissario == 0){
      //   printf("Voce saiu do sistema");
      //   break;
      //   }

     printf("Digite o valor da tarifa do Voo %d: ", i + 1);
     scanf("%f", v.tarifa);

      //   if (v.tarifa == 0){
      //   printf("Voce saiu do sistema");
      //   break;
      //   }

     i++;

       fwrite(&v, sizeof(Voo), 1, arquivo);

      for (int i = 0; i < 100; i++){
         if (!voosCadastrados[i]){
            voosCadastrados[i] = v.codigo_voo;
            break;
         }
      }

     }while(i < qtdVoos);

      fclose(arquivo);

}

void Data (char data){

     int dia, mes, ano;

     printf("\nInformacao sobre a data.\n");

     do{
     printf("Digite o dia: ");
     scanf("%d", &dia);
     if (dia < 0 || dia > 31){
        printf("Dia Invalido. Digite novamente.\n");
        continue;
     }
     }while(dia < 0 || dia > 31);

     do{
     printf("Digite o mes: ");
     scanf("%d", &mes);
     if (mes < 0 || mes > 12){
        printf("Mes Invalido. Digite novamente.\n");
        continue;
     }
     }while(mes < 0 || mes > 12);

     do{
     printf("Digite o ano: ");
     scanf("%d", &ano);
     if (ano != 2024){
        printf("Ano Invalido. Digite novamente.\n");
        continue;
     }
     }while(ano != 2024);

     printf("A data eh %d/%d/%d\n", dia, mes, ano);
}

void Hora (char hora){

     int time, minuto;

     printf("\nInformacao sore a hora\n");

     do{
        printf("Digite a hora: ");
        scanf("%d", &time);
        if (time < 0 || time > 24){
            printf("Hora Invalida. Digite Novamente");
            continue;
        }
     }while(time < 0 || time > 24);

     do{
        printf("Digite os minutos: ");
        scanf("%d", &minuto);
        getchar();
        if (minuto < 0 || minuto > 60){
            printf("Hora Invalida. Digite Novamente");
            continue;
        }
     }while(minuto < 0 || minuto > 60);

     printf("Sao %d:%d\n", time, minuto);
}


int cadastroVooMain()
{
    int codigo_voo, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario;
    float tarifa;
    char data, hora, origem, destino;

    cadastro_voo(codigo_voo, data, hora, origem, destino, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario, tarifa);
}
