#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std;

void printTable(vector<int> cabecalho, vector<vector<string>> tabela);
void printDetalhesClasse(string nome, int vida, int defesa, int ataqueB, int ataqueE);
void printInicio();
void printOpcoes();
void limparTerminal();

int gerarNumeroAleatorio(int min, int max);

#endif