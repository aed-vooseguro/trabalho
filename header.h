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

//structs e funções de cadastro_voo.c
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

void Hora (char hora);
void Data (char data);
int cadastroVooMain();
void cadastro_voo(int codigo_voo, char data, char hora, char origem, char destino, int codigo_aviao, int codigo_piloto, int codigo_copiloto, int codigo_comissario, float tarifa);

//structs e funções de gerencia_assentos.c
typedef struct {
    int codigoVoo;
    char origem[50];
    char destino[50];
    char status; // 'A' para ativo, 'I' para inativo
    float tarifa;
} VooAssento;

typedef struct {
    int numero;
    int codigoVoo;
    char status; // 'L' para livre, 'O' para ocupado
} Assento;

typedef struct {
    int codigoVoo;
    int numeroAssento;
    int codigoPassageiro;
} Reserva;

int cadastrarAssentos();
int reservarAssento();
int liberarReserva();
void exibirAssentos(int codigoVoo);
int validarEntradaNumerica(const char *mensagem);
int vooValido(int codigoVoo);
int gerenciaAssentosMain();

#endif // HEADER_H_INCLUDED
