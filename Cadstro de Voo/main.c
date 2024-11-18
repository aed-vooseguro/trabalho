#include <stdio.h>
#include <stdlib.h>

/*
VOO: código do voo, data, hora, origem, destino, código do avião, código do piloto,
código do copiloto, código do comissário, status (ativo/inativo), tarifa.

Cadastro de Voo:
o Deve ser possível cadastrar informações sobre data, hora, origem, destino, tarifa,
tripulação e o avião.
o Deve verificar a presença de ao menos um piloto e um copiloto para que o voo
seja marcado como ativo.

*/

typedef struct{
   int codigo_voo;
   char data[10];
   char hora[10];
   char origem[20];
   char destino[20];
   int codigo_aviao[6];
   int codigo_piloto[6];
   int codigo_copiloto[6];
   int codigo_comissario[6];
   float tarifa[6];
}Voo;

void cadastro_voo(int codigo_voo, char data, char hora, char origem, char destino, int codigo_aviao, int codigo_piloto, int codigo_copiloto, int codigo_comissario, float tarifa){

     Voo v;
     int qtd_piloto = 0, qtd_copiloto = 0, i = 0;

     do{

     printf("Cadastro de Voo %d.\n", i + 1);

     printf("Digite o Codigo do Voo %d: ", i + 1);
     scanf("%d", &v.codigo_voo);

     Data(data);
     Hora(hora);

     printf("\nDigite a Origem: ");
     fgets(v.origem, 20, stdin);
     fflush(stdin);

     printf("Digite o Destino: ");
     fgets(v.destino, 20, stdin);
     fflush(stdin);

     printf("Digite o Codigo do Aviao %d: ", i + 1);
     scanf("%d", &v.codigo_aviao);

     printf("Digite o Codigo de Piloto %d", i + 1);
     printf("\nCaso nao tenha Piloto, digite -1: ");
     scanf("%d", &v.codigo_piloto);

     if (v.codigo_piloto > 0){
        qtd_piloto++;
     }

     printf("Digite o Codigo de Copiloto %d", i + 1);
     printf("\nCaso nao tenha Copiloto, digite -1: ");
     scanf("%d", &v.codigo_copiloto);

     if (v.codigo_copiloto > 0){
        qtd_copiloto++;
     }

     if (qtd_piloto > 0 && qtd_copiloto > 0){
        printf("Status: Voo %d Ativo\n", i + 1);
     }
     else{
        printf("Status: Voo %d Inativo\n", i + 1);
     }


     i++;

     }while(1);

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
        if (time < 0 || time > 60){
            printf("Hora Invalida. Digite Novamente");
            continue;
        }
     }while(time < 0 || time > 60);

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


int main()
{
    int codigo_voo, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario;
    float tarifa;
    char data, hora, origem, destino;

    cadastro_voo(codigo_voo, data, hora, origem, destino, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario, tarifa);
}
