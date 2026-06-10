#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FAMILIAS 100

// Estrutura para armazenar os dados das famílias
typedef struct {
    char nomeResponsavel[50];
    char cpf[15];
    int qtdFilhos;
    int recebeuCesta; // 0 = Não, 1 = Sim
} Familia;

// Variáveis Globais para o controle do sistema
Familia bancoFamilias[MAX_FAMILIAS];
int totalFamilias = 0;
int estoqueCestas = 0;

// Protótipos das funções
void cadastrarFamilia();
void gerenciarEstoque();
void registrarEntrega();
void exibirRelatorio();
void limparTela();

int main() {
    int opcao;

    do {
        limparTela();
        printf("=============================================\n");
        printf("    SISTEMA DE GESTAO SOLIDARIA - ONG v1.0   \n");
        printf("=============================================\n");
        printf("[1] Cadastrar Familia\n");
        printf("[2] Gerenciar Estoque de Cestas\n");
        printf("[3] Registrar Entrega de Cesta\n");
        printf("[4] Relatorio Geral / Auditoria\n");
        printf("[0] Sair do Sistema\n");
        printf("---------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch(opcao) {
            case 1:
                cadastrarFamilia();
                break;
            case 2:
                gerenciarEstoque();
                break;
            case 3:
                registrarEntrega();
                break;
            case 4:
                exibirRelatorio();
                break;
            case 0:
                printf("\nEncerrando o sistema. Trabalho concluido com sucesso!\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                printf("Pressione ENTER para continuar...");
                getchar();
        }
    } while(opcao != 0);

    return 0;
}

// Função para cadastrar uma nova família necessitada
void cadastrarFamilia() {
    limparTela();
    if (totalFamilias >= MAX_FAMILIAS) {
        printf("Erro: Limite maximo de familias cadastradas atingido!\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("--- CADASTRO DE NOVA FAMILIA ---\n");
    printf("Nome do Responsavel: ");
    fgets(bancoFamilias[totalFamilias].nomeResponsavel, 50, stdin);
    // Remove a quebra de linha (\n) capturada pelo fgets
    bancoFamilias[totalFamilias].nomeResponsavel[strcspn(bancoFamilias[totalFamilias].nomeResponsavel, "\n")] = 0;

    printf("CPF (apenas numeros): ");
    fgets(bancoFamilias[totalFamilias].cpf, 15, stdin);
    bancoFamilias[totalFamilias].cpf[strcspn(bancoFamilias[totalFamilias].cpf, "\n")] = 0;

    printf("Quantidade de filhos/dependentes: ");
    scanf("%d", &bancoFamilias[totalFamilias].qtdFilhos);
    getchar();

    bancoFamilias[totalFamilias].recebeuCesta = 0; // Começa sem ter recebido nada no mês

    totalFamilias++;
    printf("\nFamilia cadastrada com sucesso!\n");
    printf("\nPressione ENTER para voltar...");
    getchar();
}

// Função para entrada de insumos no estoque (Evita o desperdício)
void gerenciarEstoque() {
    limparTela();
    int qtd;
    printf("--- GERENCIAMENTO DE ESTOQUE ---\n");
    printf("Estoque atual: %d cestas basicas.\n", estoqueCestas);
    printf("Quantidade de cestas recebidas para adicionar: ");
    scanf("%d", &qtd);
    getchar();

    if (qtd < 0) {
        printf("\nErro: Nao e possivel adicionar quantidades negativas!\n");
    } else {
        estoqueCestas += qtd;
        printf("\nEstoque atualizado com sucesso!\n");
    }
    printf("\nPressione ENTER para voltar...");
    getchar();
}

// Função para realizar a entrega de forma justa e controlada
void registrarEntrega() {
    limparTela();
    char cpfBusca[15];
    int achou = 0;

    printf("--- REGISTRAR ENTREGA DE DONATIVO ---\n");
    if (estoqueCestas <= 0) {
        printf("Alerta: Estoque zerado! Abasteça o estoque antes de realizar entregas.\n");
        printf("\nPressione ENTER para voltar...");
        getchar();
        return;
    }

    printf("Digite o CPF da familia cadastrada: ");
    fgets(cpfBusca, 15, stdin);
    cpfBusca[strcspn(cpfBusca, "\n")] = 0;

    for (int i = 0; i < totalFamilias; i++) {
        if (strcmp(bancoFamilias[i].cpf, cpfBusca) == 0) {
            achou = 1;
            if (bancoFamilias[i].recebeuCesta == 1) {
                printf("\n[ALERTA] Esta familia ja recebeu uma cesta basica este mes!\n");
                printf("Evite duplicidade para garantir o atendimento a outros beneficiarios.\n");
            } else {
                bancoFamilias[i].recebeuCesta = 1;
                estoqueCestas--;
                printf("\nSucesso: Cesta basica entregue para %s!\n", bancoFamilias[i].nomeResponsavel);
                printf("Estoque restante: %d\n", estoqueCestas);
            }
            break;
        }
    }

    if (!achou) {
        printf("\nCPF nao encontrado no sistema. Realize o cadastro da familia primeiro.\n");
    }

    printf("\nPressione ENTER para voltar...");
    getchar();
}

// Função de auditoria e relatório exigida pelo projeto
void exibirRelatorio() {
    limparTela();
    printf("--- RELATORIO GERAL E AUDITORIA ---\n");
    printf("Total de Familias Cadastradas: %d\n", totalFamilias);
    printf("Total de Cestas Disponiveis no Estoque: %d\n", estoqueCestas);
    printf("-----------------------------------------------------------------\n");
    printf("%-20s | %-12s | %-8s | %-10s\n", "Responsavel", "CPF", "Filhos", "Status Cesta");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < totalFamilias; i++) {
        printf("%-20s | %-12s | %-8d | %-10s\n", 
            bancoFamilias[i].nomeResponsavel, 
            bancoFamilias[i].cpf, 
            bancoFamilias[i].qtdFilhos, 
            bancoFamilias[i].recebeuCesta ? "RECEBEU" : "PENDENTE");
    }
    printf("-----------------------------------------------------------------\n");
    printf("\nPressione ENTER para voltar...");
    getchar();
}

// Função utilitária para limpar a tela dependendo do Sistema Operacional
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}