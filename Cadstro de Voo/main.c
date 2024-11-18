#include <stdio.h>
#include <stdlib.h>

/*
VOO: c�digo do voo, data, hora, origem, destino, c�digo do avi�o, c�digo do piloto,
c�digo do copiloto, c�digo do comiss�rio, status (ativo/inativo), tarifa.

Cadastro de Voo:
o Deve ser poss�vel cadastrar informa��es sobre data, hora, origem, destino, tarifa,
tripula��o e o avi�o.
o Deve verificar a presen�a de ao menos um piloto e um copiloto para que o voo
seja marcado como ativo.

*/

typedef struct{
   int codigo_voo;
   char data[10];
   char hora[10];
   char origem[20];
   char detino[20];
   int codigo_aviao[6];
   int codigo_piloto[6];
   int codigo_copiloto[6];
   int codigo_comissario[6];
   float tarifa[6];
}Voo;

void cadastro_voo(int codigo_voo, char data, char hora, char origem, char destino, int codigo_aviao, int codigo_piloto, int codigo_copiloto, int codigo_comissario, float tarifa){

     Voo v;
     int qtd_piloto = 0, qtd_copiloto = 0, i = 0;

     printf("Cadastro de Voo.\n");

     do{

     printf("Digite o Codigo do Aviao %d: ", i + 1);
     scanf("%d", &v.codigo_aviao);

     Data(data);

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

     int hora, int minuto;

     printf("Informacao sore a hora");
}


int main()
{
    int codigo_voo, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario;
    float tarifa;
    char data, hora, origem, destino;

    cadastro_voo(codigo_voo, data, hora, origem, destino, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario, tarifa);
}
