#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int codigo;
    char nome[20];
    char telefone[20];
    char cargo[10];
}tripulacao;

void cadastro_tripulacao(int codigo, char nome, char telefone, char cargo){

}

int main()
{
    int codigo;
    char nome[20], telefone[15], cargo[10];

    cadastro_tripulacao(codigo, nome, telefone, cargo);
}
