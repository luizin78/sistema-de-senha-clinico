
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    int idade;
    char genero;
    int gestante;
    int lactante;
    int especial;
    int obeso;
    char senha[10];
    char categoria[20];
} Paciente;

Paciente pacientes[MAX];

int total = 0;

int contN = 0;
int contP = 0;
int contU = 0;

int filaN[MAX], filaP[MAX], filaU[MAX];
int qtdN = 0, qtdP = 0, qtdU = 0;

int atual = -1;

// Leitura e validacao de numeros
int lerNumero(char mensagem[], int minimo, int maximo) {
    int valor;
    char entrada[100];
    char extra;

    while (1) {
        printf("%s", mensagem);

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            continue;
        }

        if (sscanf(entrada, " %d %c", &valor, &extra) != 1) {
            printf("Entrada invalida! Digite apenas um numero.\n");
        }
        else if (valor < minimo || valor > maximo) {
            printf("Valor invalido! Digite entre %d e %d.\n",
                   minimo, maximo);
        }
        else {
            return valor;
        }
    }
}

// Leitura e validacao do genero
char lerGenero() {
    char entrada[100];
    char genero;

    while (1) {
        printf("Genero (M/F): ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            continue;
        }

        if (sscanf(entrada, " %c", &genero) != 1) {
            printf("Entrada invalida!\n");
            continue;
        }

        genero = toupper((unsigned char)genero);

        if (genero == 'M' || genero == 'F') {
            return genero;
        }

        printf("Digite M para masculino ou F para feminino.\n");
    }
}

// Classifica a prioridade do paciente
int classificarPaciente(Paciente p) {
    if (p.idade > 80) {
        return 3;
    }

    if (p.gestante == 1 || p.lactante == 1 ||
        p.especial == 1 || p.obeso == 1) {
        return 2;
    }

    if (p.genero == 'F' && p.idade >= 60) {
        return 2;
    }

    if (p.genero == 'M' && p.idade >= 65) {
        return 2;
    }

    return 1;
}

// Gera a senha e adiciona o paciente na fila
void gerarSenha(int posicao, int tipo) {
    if (tipo == 3) {
        contU++;
        sprintf(pacientes[posicao].senha, "U%03d", contU);
        strcpy(pacientes[posicao].categoria, "Urgente");

        filaU[qtdU] = posicao;
        qtdU++;
    }
    else if (tipo == 2) {
        contP++;
        sprintf(pacientes[posicao].senha, "P%03d", contP);
        strcpy(pacientes[posicao].categoria, "Preferencial");

        filaP[qtdP] = posicao;
        qtdP++;
    }
    else {
        contN++;
        sprintf(pacientes[posicao].senha, "N%03d", contN);
        strcpy(pacientes[posicao].categoria, "Normal");

        filaN[qtdN] = posicao;
        qtdN++;
    }
}

// Cadastra um novo paciente
void cadastrarPaciente() {
    int tipo;

    if (total >= MAX) {
        printf("\nLimite de cadastros atingido!\n");
        return;
    }

    printf("\n===== CADASTRO DE PACIENTE =====\n");

    pacientes[total].genero = lerGenero();

    pacientes[total].idade = lerNumero(
        "Idade: ", 0, 120
    );

    pacientes[total].gestante = 0;
    pacientes[total].lactante = 0;

    if (pacientes[total].genero == 'F') {
        pacientes[total].gestante = lerNumero(
            "Gestante? (1-Sim / 0-Nao): ", 0, 1
        );

        pacientes[total].lactante = lerNumero(
            "Lactante? (1-Sim / 0-Nao): ", 0, 1
        );
    }

    pacientes[total].especial = lerNumero(
        "Possui necessidade especial? (1-Sim / 0-Nao): ",
        0, 1
    );

    pacientes[total].obeso = lerNumero(
        "Possui obesidade? (1-Sim / 0-Nao): ",
        0, 1
    );

    tipo = classificarPaciente(pacientes[total]);

    gerarSenha(total, tipo);

    printf("\nPaciente cadastrado com sucesso!\n");
    printf("Senha: %s\n", pacientes[total].senha);
    printf("Categoria: %s\n", pacientes[total].categoria);

    total++;
}

// Consulta a proxima senha
void consultarProxima() {
    printf("\n===== PROXIMA SENHA =====\n");

    if (qtdU > 0) {
        printf("Proxima senha: %s\n",
               pacientes[filaU[0]].senha);
    }
    else if (qtdP > 0) {
        printf("Proxima senha: %s\n",
               pacientes[filaP[0]].senha);
    }
    else if (qtdN > 0) {
        printf("Proxima senha: %s\n",
               pacientes[filaN[0]].senha);
    }
    else {
        printf("Nao existem pacientes aguardando.\n");
    }
}

// Retira o primeiro paciente de uma fila
int retirarDaFila(int fila[], int *quantidade) {
    int posicao;
    int i;

    if (*quantidade == 0) {
        return -1;
    }

    posicao = fila[0];

    for (i = 0; i < *quantidade - 1; i++) {
        fila[i] = fila[i + 1];
    }

    (*quantidade)--;

    return posicao;
}

// Chama o proximo paciente seguindo a prioridade
void chamarPaciente() {
    int posicao = -1;

    if (atual != -1) {
        printf("\nFinalize o atendimento atual antes de chamar outro.\n");
        return;
    }

    if (qtdU > 0) {
        posicao = retirarDaFila(filaU, &qtdU);
    }
    else if (qtdP > 0) {
        posicao = retirarDaFila(filaP, &qtdP);
    }
    else if (qtdN > 0) {
        posicao = retirarDaFila(filaN, &qtdN);
    }

    if (posicao == -1) {
        printf("\nNao existem pacientes na fila.\n");
        return;
    }

    atual = posicao;

    printf("\n===== CHAMADA DE PACIENTE =====\n");
    printf("Senha chamada: %s\n", pacientes[atual].senha);
    printf("Categoria: %s\n", pacientes[atual].categoria);
}

// Finaliza o atendimento atual
void finalizarAtendimento() {
    if (atual == -1) {
        printf("\nNao existe atendimento em andamento.\n");
        return;
    }

    printf("\nAtendimento da senha %s finalizado!\n",
           pacientes[atual].senha);

    atual = -1;
}

// Mostra os pacientes que estao aguardando
void mostrarFila(char titulo[], int fila[], int quantidade) {
    int i;

    printf("\n%s\n", titulo);

    if (quantidade == 0) {
        printf("Nenhum paciente.\n");
        return;
    }

    for (i = 0; i < quantidade; i++) {
        printf("%s\n", pacientes[fila[i]].senha);
    }
}

// Exibe o painel de atendimento
void mostrarPainel() {
    printf("\n========== PAINEL DE ATENDIMENTO ==========\n");

    if (atual == -1) {
        printf("Atendimento atual: Nenhum\n");
    }
    else {
        printf("Atendimento atual: %s\n",
               pacientes[atual].senha);
        printf("Categoria: %s\n",
               pacientes[atual].categoria);
    }

    mostrarFila("FILA URGENTE:", filaU, qtdU);
    mostrarFila("FILA PREFERENCIAL:", filaP, qtdP);
    mostrarFila("FILA NORMAL:", filaN, qtdN);

    printf("\n========== QUANTIDADE DE SENHAS ==========\n");
    printf("Urgentes: %d\n", contU);
    printf("Preferenciais: %d\n", contP);
    printf("Normais: %d\n", contN);
    printf("Total de pacientes cadastrados: %d\n", total);
}

// Exibe o menu principal
void mostrarMenu() {
    printf("\n========== SISTEMA DE ATENDIMENTO ==========\n");
    printf("1 - Cadastrar paciente\n");
    printf("2 - Consultar proxima senha\n");
    printf("3 - Chamar paciente\n");
    printf("4 - Finalizar atendimento\n");
    printf("5 - Mostrar painel\n");
    printf("0 - Sair\n");
}

// Funcao principal
int main() {
    int opcao;

    do {
        mostrarMenu();

        opcao = lerNumero("Escolha uma opcao: ", 0, 5);

        switch (opcao) {
            case 1:
                cadastrarPaciente();
                break;

            case 2:
                consultarProxima();
                break;

            case 3:
                chamarPaciente();
                break;

            case 4:
                finalizarAtendimento();
                break;

            case 5:
                mostrarPainel();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
