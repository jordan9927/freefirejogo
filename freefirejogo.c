#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para representar um componente da torre de resgate
typedef struct {
    char nome[30];      // Nome do componente
    char tipo[20];      // Tipo do componente
    int prioridade;     // Prioridade do componente (1 a 10)
} Componente;

// Variável global para contar comparações durante as ordenações
int comparacoes = 0;

// Função para exibir todos os componentes
void mostrarComponentes(Componente componentes[], int total) {
    printf("\n========== COMPONENTES DA TORRE ==========\n");
    printf("%-4s %-25s %-15s %s\n", "Num", "Nome", "Tipo", "Prioridade");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("%-4d %-25s %-15s %d\n", 
               i + 1, componentes[i].nome, componentes[i].tipo, componentes[i].prioridade);
    }
    printf("==========================================\n\n");
}

// Função Bubble Sort - Ordena por nome (ordem alfabética)
void bubbleSortNome(Componente componentes[], int total) {
    comparacoes = 0;
    
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            comparacoes++;
            // Compara os nomes dos componentes
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                // Troca os componentes de posição
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }
        }
    }
    
    printf(">>> Bubble Sort concluido! Total de comparacoes: %d\n", comparacoes);
}

// Função Insertion Sort - Ordena por tipo (ordem alfabética)
void insertionSortTipo(Componente componentes[], int total) {
    comparacoes = 0;
    
    for (int i = 1; i < total; i++) {
        Componente chave = componentes[i];
        int j = i - 1;
        
        // Move os elementos maiores que a chave para a direita
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentes[j].tipo, chave.tipo) > 0) {
                componentes[j + 1] = componentes[j];
                j--;
            } else {
                break;
            }
        }
        
        componentes[j + 1] = chave;
    }
    
    printf(">>> Insertion Sort concluido! Total de comparacoes: %d\n", comparacoes);
}

// Função Selection Sort - Ordena por prioridade (do menor para o maior)
void selectionSortPrioridade(Componente componentes[], int total) {
    comparacoes = 0;
    
    for (int i = 0; i < total - 1; i++) {
        int indiceMenor = i;
        
        // Encontra o menor elemento
        for (int j = i + 1; j < total; j++) {
            comparacoes++;
            if (componentes[j].prioridade < componentes[indiceMenor].prioridade) {
                indiceMenor = j;
            }
        }
        
        // Troca o menor elemento encontrado com o primeiro elemento
        if (indiceMenor != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[indiceMenor];
            componentes[indiceMenor] = temp;
        }
    }
    
    printf(">>> Selection Sort concluido! Total de comparacoes: %d\n", comparacoes);
}

// Função de Busca Binária - Busca por nome (requer vetor ordenado por nome)
int buscaBinariaPorNome(Componente componentes[], int total, char nomeBuscado[]) {
    int esquerda = 0;
    int direita = total - 1;
    int comparacoesBusca = 0;
    
    while (esquerda <= direita) {
        comparacoesBusca++;
        int meio = esquerda + (direita - esquerda) / 2;
        int resultado = strcmp(componentes[meio].nome, nomeBuscado);
        
        if (resultado == 0) {
            // Componente encontrado
            printf("\n>>> COMPONENTE ENCONTRADO! <<<\n");
            printf("Nome: %s\n", componentes[meio].nome);
            printf("Tipo: %s\n", componentes[meio].tipo);
            printf("Prioridade: %d\n", componentes[meio].prioridade);
            printf("Total de comparacoes na busca: %d\n\n", comparacoesBusca);
            return meio;
        }
        
        if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    // Componente não encontrado
    printf("\n>>> Componente '%s' NAO ENCONTRADO! <<<\n", nomeBuscado);
    printf("Total de comparacoes na busca: %d\n\n", comparacoesBusca);
    return -1;
}

// Função para medir o tempo de execução de um algoritmo
double medirTempo(void (*algoritmo)(Componente[], int), Componente componentes[], int total) {
    clock_t inicio = clock();
    algoritmo(componentes, total);
    clock_t fim = clock();
    
    double tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6f segundos\n\n", tempoGasto);
    
    return tempoGasto;
}

// Função para remover o '\n' que o fgets pode capturar
void limparNewline(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Função para cadastrar componentes
int cadastrarComponentes(Componente componentes[], int maxComponentes) {
    int total;
    
    printf("\n========== CADASTRO DE COMPONENTES ==========\n");
    printf("Quantos componentes deseja cadastrar (max %d)? ", maxComponentes);
    scanf("%d", &total);
    getchar(); // Limpa o buffer
    
    if (total > maxComponentes) {
        printf("Numero maximo de componentes excedido. Limitando a %d.\n", maxComponentes);
        total = maxComponentes;
    }
    
    for (int i = 0; i < total; i++) {
        printf("\n--- Componente %d ---\n", i + 1);
        
        printf("Nome do componente: ");
        fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin);
        limparNewline(componentes[i].nome);
        
        printf("Tipo (controle/suporte/propulsao): ");
        fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin);
        limparNewline(componentes[i].tipo);
        
        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar(); // Limpa o buffer
        
        // Valida a prioridade
        if (componentes[i].prioridade < 1 || componentes[i].prioridade > 10) {
            printf("Prioridade invalida! Definindo como 5.\n");
            componentes[i].prioridade = 5;
        }
    }
    
    printf("\n>>> %d componentes cadastrados com sucesso! <<<\n", total);
    return total;
}

// Função para copiar o vetor de componentes (para preservar original)
void copiarComponentes(Componente origem[], Componente destino[], int total) {
    for (int i = 0; i < total; i++) {
        destino[i] = origem[i];
    }
}

// Função principal com menu interativo
int main() {
    Componente componentes[20];      // Vetor original
    Componente componentesTemp[20];  // Vetor temporário para ordenações
    int totalComponentes = 0;
    int opcao;
    char nomeBusca[30];
    
    printf("\n");
    printf("*************************************************\n");
    printf("*   SISTEMA DE MONTAGEM DA TORRE DE RESGATE    *\n");
    printf("*************************************************\n");
    
    // Cadastra os componentes
    totalComponentes = cadastrarComponentes(componentes, 20);
    
    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1. Exibir componentes cadastrados\n");
        printf("2. Ordenar por NOME (Bubble Sort)\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Buscar componente por NOME (Busca Binaria)\n");
        printf("6. Cadastrar novos componentes\n");
        printf("0. Sair\n");
        printf("====================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer
        
        switch (opcao) {
            case 1:
                // Exibir componentes
                mostrarComponentes(componentes, totalComponentes);
                break;
                
            case 2:
                // Ordenar por nome usando Bubble Sort
                printf("\n>>> Executando Bubble Sort (ordenacao por NOME)...\n");
                copiarComponentes(componentes, componentesTemp, totalComponentes);
                medirTempo(bubbleSortNome, componentesTemp, totalComponentes);
                mostrarComponentes(componentesTemp, totalComponentes);
                
                // Pergunta se deseja salvar a ordenação
                printf("Deseja manter esta ordenacao? (s/n): ");
                char resp;
                scanf("%c", &resp);
                getchar();
                if (resp == 's' || resp == 'S') {
                    copiarComponentes(componentesTemp, componentes, totalComponentes);
                    printf("Ordenacao salva!\n");
                }
                break;
                
            case 3:
                // Ordenar por tipo usando Insertion Sort
                printf("\n>>> Executando Insertion Sort (ordenacao por TIPO)...\n");
                copiarComponentes(componentes, componentesTemp, totalComponentes);
                medirTempo(insertionSortTipo, componentesTemp, totalComponentes);
                mostrarComponentes(componentesTemp, totalComponentes);
                
                printf("Deseja manter esta ordenacao? (s/n): ");
                scanf("%c", &resp);
                getchar();
                if (resp == 's' || resp == 'S') {
                    copiarComponentes(componentesTemp, componentes, totalComponentes);
                    printf("Ordenacao salva!\n");
                }
                break;
                
            case 4:
                // Ordenar por prioridade usando Selection Sort
                printf("\n>>> Executando Selection Sort (ordenacao por PRIORIDADE)...\n");
                copiarComponentes(componentes, componentesTemp, totalComponentes);
                medirTempo(selectionSortPrioridade, componentesTemp, totalComponentes);
                mostrarComponentes(componentesTemp, totalComponentes);
                
                printf("Deseja manter esta ordenacao? (s/n): ");
                scanf("%c", &resp);
                getchar();
                if (resp == 's' || resp == 'S') {
                    copiarComponentes(componentesTemp, componentes, totalComponentes);
                    printf("Ordenacao salva!\n");
                }
                break;
                
            case 5:
                // Busca binária por nome
                printf("\n>>> BUSCA BINARIA <<<\n");
                printf("ATENCAO: O vetor deve estar ordenado por NOME!\n");
                printf("Digite o nome do componente a buscar: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                limparNewline(nomeBusca);
                
                // Ordena primeiro por nome (necessário para busca binária)
                copiarComponentes(componentes, componentesTemp, totalComponentes);
                bubbleSortNome(componentesTemp, totalComponentes);
                
                // Realiza a busca
                buscaBinariaPorNome(componentesTemp, totalComponentes, nomeBusca);
                break;
                
            case 6:
                // Cadastrar novos componentes
                totalComponentes = cadastrarComponentes(componentes, 20);
                break;
                
            case 0:
                printf("\n>>> ENCERRANDO O SISTEMA <<<\n");
                printf("Torre de resgate finalizada!\n\n");
                break;
                
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
        
    } while (opcao != 0);
    
    return 0;
}
