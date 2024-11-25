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

//structs e funções de cadastro_tripulacao.c
typedef struct{
    int codigo;
    char nome[20];
    char telefone[20];
    char cargo[10];
}tripulacao;

void cadastro_tripulacao(int codigo, const char *nome, const char *telefone, const char *cargo);
int codigo_existente (int codigos[], int j, int codigo);
int cadastroTripulacaoMain();

#endif // HEADER_H_INCLUDED
