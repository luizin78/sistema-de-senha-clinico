
# Sistema de Gerenciamento de Senhas de Atendimento Clínico

## Sobre o projeto

Este projeto foi desenvolvido em linguagem C com o objetivo de criar um sistema para organizar as senhas de atendimento de uma clínica.

O sistema permite cadastrar pacientes, identificar suas prioridades e organizar as filas de atendimento, facilitando a chamada dos pacientes de acordo com cada categoria.

## Funcionalidades

O sistema possui as seguintes funcionalidades:

- Cadastro de pacientes.
- Identificação do gênero e da idade.
- Verificação de gestantes e lactantes.
- Identificação de pessoas com necessidades especiais.
- Identificação de pacientes com obesidade.
- Classificação automática de prioridade.
- Geração de senhas individuais.
- Consulta da próxima senha.
- Chamada de pacientes.
- Finalização de atendimentos.
- Painel para visualizar as filas e quantidades de senhas.

## Classificação das senhas

O sistema trabalha com três categorias:

| Categoria | Identificação | Prioridade |
|---|---|---|
| Urgente | U001, U002... | 1ª |
| Preferencial | P001, P002... | 2ª |
| Normal | N001, N002... | 3ª |

A classificação considera as seguintes regras:

- **Urgente:** pacientes com idade superior a 80 anos.
- **Preferencial:** gestantes, lactantes, pessoas com necessidades especiais, pessoas com obesidade, mulheres a partir de 60 anos e homens a partir de 65 anos.
- **Normal:** pacientes que não se enquadram nas categorias anteriores.

A prioridade urgente tem preferência sobre a preferencial, que tem preferência sobre a normal.

Dentro de cada categoria, o atendimento segue a ordem de chegada (FIFO).

## Tecnologias utilizadas

- Linguagem C.
- Biblioteca stdio.h.
- Biblioteca string.h.
- Biblioteca ctype.h.
- Compilador GCC.

## Como executar o projeto

1. Baixe ou clone este repositório.
2. Abra a pasta do projeto.
3. Compile o arquivo C utilizando um compilador.

Exemplo utilizando GCC:

```bash
gcc main.c -o sistema
```

4. Execute o programa:

No Windows:

```bash
sistema.exe
```

No Linux:

```bash
./sistema
```

## Menu do sistema

Ao executar o programa, será apresentado um menu com as seguintes opções:

1. Cadastrar paciente.
2. Consultar próxima senha.
3. Chamar paciente.
4. Finalizar atendimento.
5. Mostrar painel.
0. Sair do sistema.

## Organização do código

O código foi organizado em funções para facilitar a leitura e a manutenção.

Principais funções:

- `lerNumero()`: realiza a leitura e validação de números.
- `lerGenero()`: verifica o gênero informado.
- `classificarPaciente()`: define a categoria do paciente.
- `gerarSenha()`: cria a senha e adiciona o paciente à fila.
- `cadastrarPaciente()`: realiza o cadastro.
- `consultarProxima()`: consulta a próxima senha.
- `retirarDaFila()`: retira o primeiro paciente da fila.
- `chamarPaciente()`: realiza a chamada.
- `finalizarAtendimento()`: encerra o atendimento atual.
- `mostrarPainel()`: apresenta as informações das filas.
- `mostrarMenu()`: exibe as opções disponíveis.

## Objetivo acadêmico

O projeto tem como objetivo colocar em prática os conhecimentos adquiridos em programação na linguagem C, utilizando estruturas, vetores, funções, condicionais, laços de repetição e validação de dados.

---

**Projeto acadêmico desenvolvido em linguagem C.**

