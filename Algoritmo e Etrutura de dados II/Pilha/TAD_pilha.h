#define TAM_PILHA 5
typedef struct
{
    int topo;
    int memoria[TAM_PILHA];
} pilha;

void inicializapilha(pilha *p);           // pilha que vai ser inicializada
int pilhacheia(pilha *p);                 // retorna 1 se a pilha está cheia ou 0 se não está cheia
int pilhavazia(pilha *p);                 // retorna 1 se a pilha está vazia ou 0 se não está vazia
void empilha(pilha *p, int elemento);     // recebe a pilha e o elemento que será empilhado
void desempilha(pilha *p);                // retira elemento do topo da pilha
int topopilha(pilha *p);                  // retorna elemento do topo da pilha;
int tamanhopilha(pilha *p);               // retorna o tamanho da pilha;
void replicapilha(pilha *a, pilha *b);    // Replica pilha utilizando vetor
void replicaauxpilha(pilha *a, pilha *b); /// Replica a pilha sem a utilização de vetores
void invertepilha(pilha *p);              // Inverte a pilha sem utilizar vetores