#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura da conta no ATM
typedef struct {
    char nome[50];      // Nome do usuário
    char senha[20];     // Senha da conta
    float saldo;        // Saldo em reais
} Conta;

// Função para escrever uma conta no arquivo txt
void escreverConta(Conta conta) {
    FILE *arquivo = fopen("ContasCadastradas.txt", "a"); // Abre o arquivo em modo de adição
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fprintf(arquivo, "%s %s %.2f\n", conta.nome, conta.senha, conta.saldo); // Escreve os dados da conta
    fclose(arquivo);
    printf("\nConta criada com sucesso!\n");
}

// Função para apagar uma conta no arquivo txt
void apagarConta(char *nome) {
    FILE *arquivo = fopen("ContasCadastradas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Conta conta;
    int contaEncontrada = 0;

    if (arquivo == NULL || temp == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        return;
    }

    // Lê e copia todas as contas, exceto a que será apagada
    while (fscanf(arquivo, "%s %s %f", conta.nome, conta.senha, &conta.saldo) != EOF) {
        if (strcmp(conta.nome, nome) != 0) {
            fprintf(temp, "%s %s %.2f\n", conta.nome, conta.senha, conta.saldo);
        } else {
            contaEncontrada = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Remove o arquivo antigo e renomeia o temporário
    remove("ContasCadastradas.txt");
    rename("temp.txt", "ContasCadastradas.txt");

    if (contaEncontrada) {
        printf("\nConta removida com sucesso!\n");
    } else {
        printf("\nConta nao encontrada!\n");
    }
}

// Função para entrar na conta (validar usuário e senha)
int entrarConta(char *nome, char *senha) {
    FILE *arquivo = fopen("ContasCadastradas.txt", "r");
    Conta conta;

    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo!\n");
        return 0;
    }

    // Procura a conta com o nome e senha fornecidos
    while (fscanf(arquivo, "%s %s %f", conta.nome, conta.senha, &conta.saldo) != EOF) {
        if (strcmp(conta.nome, nome) == 0 && strcmp(conta.senha, senha) == 0) {
            fclose(arquivo);
            printf("\nLogin efetuado com sucesso!\n");
            return 1;
        }
    }

    fclose(arquivo);
    printf("\nNome ou senha incorretos!\n");
    return 0;
}

// Função para adicionar ou retirar dinheiro da conta
void atualizarSaldo(char *nome, float valor) {
    FILE *arquivo = fopen("ContasCadastradas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    Conta conta;
    int contaEncontrada = 0;

    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    // Atualiza o saldo da conta
    while (fscanf(arquivo, "%s %s %f", conta.nome, conta.senha, &conta.saldo) != EOF) {
        if (strcmp(conta.nome, nome) == 0) {
            conta.saldo += valor; // Adiciona ou subtrai o valor do saldo
            contaEncontrada = 1;
        }
        fprintf(temp, "%s %s %.2f\n", conta.nome, conta.senha, conta.saldo);
    }

    fclose(arquivo);
    fclose(temp);

    // Remove o arquivo antigo e renomeia o temporário
    remove("ContasCadastradas.txt");
    rename("temp.txt", "ContasCadastradas.txt");

    if (contaEncontrada) {
        printf("\nSaldo atualizado com sucesso!\n");
    } else {
        printf("\nConta nao encontrada!\n");
    }
}