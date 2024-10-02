#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FuncContasATM.c" // Inclui as funções do arquivo FuncContasATM

// Declaração de funções para o menu
void menu();

// Função principal
int main() {
    menu(); // Abre o menu de interação
    return 0;
}

// Função para exibir o menu e controlar o fluxo de opções
void menu() {
    int opcao;
    char nome[50], senha[20];
    float valor;
    Conta novaConta;

    do {
        printf("\n--- Caixa Eletronico ---\n");
        printf("1. Entrar na conta\n");
        printf("2. Criar nova conta\n");
        printf("3. Apagar conta\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Entrar na conta
                printf("\n--- Entrar na conta ---\n");
                printf("Nome: ");
                scanf("%s", nome);
                printf("Senha: ");
                scanf("%s", senha);

                if (entrarConta(nome, senha)) { // Verifica se o login foi bem-sucedido
                    
                    // Vamos abrir o arquivo para capturar o saldo da conta
                    FILE *arquivo = fopen("ContasCadastradas.txt", "r");
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo!\n");
                        break;
                    }

                    // Encontrar a conta e obter o saldo
                    while (fscanf(arquivo, "%s %s %f", novaConta.nome, novaConta.senha, &novaConta.saldo) != EOF) {
                        if (strcmp(novaConta.nome, nome) == 0 && strcmp(novaConta.senha, senha) == 0) {
                            break; // Conta encontrada, podemos parar a busca
                        }
                    }
                    fclose(arquivo);
                    
                    int subOpcao;
                    do {
                        printf("\n--- Menu da Conta ---\n");
                        printf("Saldo atual: R$ %.2f\n\n", novaConta.saldo);
                        printf("1. Depositar\n");
                        printf("2. Retirar\n");
                        printf("3. Sair da conta\n");
                        printf("Escolha uma opcao: ");
                        scanf("%d", &subOpcao);

                        switch (subOpcao) {
                            case 1: // Depositar dinheiro
                                printf("\nDigite o valor para depositar: ");
                                scanf("%f", &valor);
                                atualizarSaldo(nome, valor);
                                break;
                            case 2: // Retirar dinheiro
                                printf("\nDigite o valor para retirar: ");
                                scanf("%f", &valor);
                                atualizarSaldo(nome, -valor); // Valor negativo para retirada
                                break;
                            case 3: // Sair da conta
                                printf("\nSaindo da conta...\n");
                                break;
                            default:
                                printf("\nOpcao invalida!\n");
                        }
                    } while (subOpcao != 3);
                }
                break;

            case 2: // Criar nova conta
                printf("\n--- Criar nova conta ---\n");
                printf("Nome: ");
                scanf("%s", novaConta.nome);
                printf("Senha: ");
                scanf("%s", novaConta.senha);
                novaConta.saldo = 0.0; // Conta criada com saldo inicial 0
                escreverConta(novaConta);
                break;

            case 3: // Apagar conta
                printf("\n--- Apagar conta ---\n");
                printf("Nome da conta a apagar: ");
                scanf("%s", nome);
                apagarConta(nome);
                break;

            case 4: // Sair do sistema
                printf("Saindo do sistema...\n");
                exit(1);

            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (1);
}