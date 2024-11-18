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
