# SimpleTableHashing
Implementação SimpleTableHashing para disciplina de Estrutura de Dados Avançados UFC 2020.1.

Ambiente
------------------------------------------
Este projeto foi desenvolvido usando Visual Studio 2017, com perfil x64/Debug.

Para compilar no linux, basta ir na pasta raiz:
g++ -O3 Hashing.cpp -o hashing

Modo de usar
------------------------------------------
./hashing input.txt output.txt

input.txt: Arquivo de Entrada formato do projeto.
output.txT: Arquivo de Saida formato do projeto. Deve ser criado antes de chamar o programa.


Projeto
------------------------------------------------
Imprementar uma tabela de dispersão usando Simple Tabulation Hashing e endereçamento aberto com tentativa linear junto com table doubling e halving.

Devem ser implementadas as seguintes operações:

Incluir(inteiro x): inclui o inteiro de 64 bits x (manter mais de uma cópia caso seja repetido)
Remover(Inteiro x): remover uma ocorrência do inteiro x (encontrar e remover a primeira ocorrência e não fazer nada caso tal ocorrência não esteja na tabela)
Buscar(Inteiro x): acha a posição na tabela de um elemento que contém o inteiro x ou indica que tal elemento não está na tabela

ENTRADA:
Vocês precisam ler um arquivo de texto que será dado como entrada para realizar um conjunto de operações.
Cada linha deste arquivo pode conter as seguintes infermações

INC:x (incluir o inteiro x)
REM:x (remover o inteiro x)
BUS:x (busca pelo inteiro x)

Exemplo de um arquivo de entrada:

INC:10
INC:20
REM:10
INC:15
INC:15
REM:17
BUS:42
INC:42
INC:43


SAÍDA:
Você deve gerar um arquivo de texto como saída 
As linhas do arquivo de entrada serão copiadas no arquivo de saída separados por duas linhas.
Na linha imediatamente seguinte à cópia da linha de entrada, você deve indicar o resultado da operação no seguinte formato:

INC:x (incluir o inteiro x)
(valor de h(x) - função de dispersão sobre x) (posição onde o elemento entrou na tabela)

REM:x (remover o inteiro x)
(valor de h(x) - função de dispersão sobre x) (posição onde o elemento foi removido da tabela ou -1 se nenhum elemento foi removido)

BUS:x (busca pelo inteiro x)
(valor de h(x) - função de dispersão sobre x) (posição onde uma cópia do elemento está na tabela ou -1 se ele não está na tabela)

A primeira linha do seu arquivo de saída deve conter o tamanho inicial da tabela. Além disto, sempre que ocorrer um table doubling ou halving ou reconstrução da tabela por muitos elementos removidos, você deve indicar cada um no seguinte formato:
Na primeira linha, indicar o tamanho inicial da tabela
TAM:(tamanho inicial da tabela)

Adicionar esta linha logo após a inclusão de um elemento que dobra o tamanho da tabela.
DOBRAR TAM:(novo tamanho da tabela)

Adicionar esta linha logo após a remoção de um elemento que divide o tamanho da tabela.
METADE TAM:(novo tamanho da tabela)

Adicionar esta linha logo após a remoção de um elemento que limpa códigos de remoção
LIMPAR - indica a limpeza de códigos de remoção

Exemplo de saída:

TAM:4

INC:10
1 1

INC:20
3 3

REM:10
1 1

INC:15
0 0

INC:15
0 1

REM:17
2 -1

BUS:42
3 -1

INC:42
7 7

DOBRAR TAM:8

INC:43
2 3

OBSERVAÇÃO:
Lembrar que na tentativa linear, você deve manter a tabela com tamanho pelo menos (1+epsilon)n, para algum epsilon escolhido por vocês.
