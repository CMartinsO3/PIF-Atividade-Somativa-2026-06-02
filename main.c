#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO_DADOS "contas.dat"


typedef struct {
    int numero_conta;
    char nome[50];
    double saldo;
    int ativo;
} Cliente;


void cadastrar_cliente(FILE *arq);
void consultar_cliente(FILE *arq);
void atualizar_saldo(FILE *arq);
void encerrar_conta(FILE *arq);
void listar_clientes(FILE *arq);
void restaurar_arquivo(FILE *arq);

int main() {
    
    FILE *arq = fopen(ARQUIVO_DADOS, "r+b");
    if (arq == NULL) {
        arq = fopen(ARQUIVO_DADOS, "w+b");
        if (arq == NULL) {
            printf("Erro ao abrir/criar o arquivo de dados.\n");
            return 1;
        }
    }

    int opcao;
    do {
        printf("\n=== SISTEMA DE MANUTENÇÃO DE CONTAS ===\n");
        printf("1. Cadastrar um novo cliente em uma posicao especifica\n");
        printf("2. Consultar um cliente pelo numero da conta\n");
        printf("3. Atualizar o saldo de um cliente\n");
        printf("4. Encerrar conta (remover cliente)\n");
        printf("5. Listar todos os clientes\n");
        printf("6. Restaurar a leitura do arquivo do inicio (rewind)\n");
        printf("7. Encerrar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrar_cliente(arq); break;
            case 2: consultar_cliente(arq); break;
            case 3: atualizar_saldo(arq); break;
            case 4: encerrar_conta(arq); break;
            case 5: listar_clientes(arq); break;
            case 6: restaurar_arquivo(arq); break;
            case 7: printf("Saindo do sistema...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while (opcao != 7);

    fclose(arq);
    return 0;
}


void cadastrar_cliente(FILE *arq) {
    int posicao;
    Cliente c;

    printf("Digite a posicao de gravacao (0, 1, 2...): ");
    scanf("%d", &posicao);
    getchar();

    fseek(arq, posicao * sizeof(Cliente), SEEK_SET);

    printf("Digite o numero da conta: ");
    scanf("%d", &c.numero_conta);
    getchar();
    printf("Digite o nome do cliente: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';
    printf("Digite o saldo inicial: ");
    scanf("%lf", &c.saldo);
    c.ativo = 1;

    fwrite(&c, sizeof(Cliente), 1, arq);
    printf("Cliente cadastrado com sucesso na posicao %d!\n", posicao);
}

void consultar_cliente(FILE *arq) {
    Cliente c;
    int conta, encontrado = 0;

    printf("Digite o numero da conta para consulta: ");
    scanf("%d", &conta);

    rewind(arq);
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo && c.numero_conta == conta) {
            printf("\n--- Cliente Encontrado ---\n");
            printf("Nome: %s\n", c.nome);
            printf("Conta: %d\n", c.numero_conta);
            printf("Saldo: R$ %.2f\n", c.saldo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Conta %d nao encontrada ou inativa.\n", conta);
    }
}

void atualizar_saldo(FILE *arq) {
    Cliente c;
    int conta, encontrado = 0;
    double novo_saldo;

    printf("Digite o numero da conta para atualizar o saldo: ");
    scanf("%d", &conta);

    rewind(arq);
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo && c.numero_conta == conta) {
            encontrado = 1;
            printf("Cliente: %s | Saldo Atual: R$ %.2f\n", c.nome, c.saldo);
            printf("Digite o novo saldo: ");
            scanf("%lf", &novo_saldo);
            
            c.saldo = novo_saldo;

            fseek(arq, -((long)sizeof(Cliente)), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, arq);
            
            printf("Saldo atualizado com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Conta %d nao encontrada.\n", conta);
    }
}

void encerrar_conta(FILE *arq) {
    Cliente c;
    int conta, encontrado = 0;

    printf("Digite o numero da conta que deseja encerrar: ");
    scanf("%d", &conta);

    rewind(arq);
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo && c.numero_conta == conta) {
            encontrado = 1;
            c.ativo = 0;

            fseek(arq, -((long)sizeof(Cliente)), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, arq);

            printf("Conta de %s encerrada com sucesso!\n", c.nome);
            break;
        }
    }

    if (!encontrado) {
        printf("Conta %d nao encontrada.\n", conta);
    }
}

void listar_clientes(FILE *arq) {
    Cliente c;
    int total = 0;

    printf("\n--- LISTA DE CLIENTES ATIVOS ---\n");
    printf("%-10s %-30s %-15s\n", "CONTA", "NOME", "SALDO");
    printf("---------------------------------------------------------\n");

    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo) {
            printf("%-10d %-30s R$ %-12.2f\n", c.numero_conta, c.nome, c.saldo);
            total++;
        }
    }

    if (total == 0) {
        printf("Nenhum cliente ativo encontrado a partir do ponteiro atual ou fim do arquivo atingido.\n");
    }
}

void restaurar_arquivo(FILE *arq) {
    rewind(arq);
    printf("Ponteiro de leitura restaurado para o inicio do arquivo com sucesso!\n");
}