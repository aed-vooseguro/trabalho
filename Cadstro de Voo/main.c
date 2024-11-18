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
   char detino[20];
   int codigo_aviao[6];
   int codigo_piloto[6];
   int codigo_copiloto[6];
   int codigo_comissario[6];
   float tarifa[6];
}voo;

void cadastro_voo(int codigo_voo, char data, char hora, char origem, char destino, int codigo_aviao, int codigo_piloto, int codigo_copiloto, int codigo_comissario, float tarifa){


}

int main()
{
    int codigo_voo, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario;
    float tarifa;
    char data, hora, origem, destino;

    cadastro_voo(codigo_voo, data, hora, origem, destino, codigo_aviao, codigo_piloto, codigo_copiloto, codigo_comissario, tarifa);
}
