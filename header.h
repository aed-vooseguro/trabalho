#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

//structs e funções de passageiros.c
typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[15];
    int fidelidade; // 1 para sim, 0 para n�o
    int pontosFidelidade;
} Passageiro;

typedef struct {
    char username[20];
    char senha[20];
} Administrador;

void cadastrarPassageiro(Passageiro *passageiro, int *codigoAtual);
int verificarUsuario(int *codigoUsuario);
int passageirosMain();
void atualizarPontosFidelidade(Passageiro *passageiro);
void buscarEEditarPassageiro(Passageiro *passageiros, int totalPassageiros, int codigo);

#endif // HEADER_H_INCLUDED
