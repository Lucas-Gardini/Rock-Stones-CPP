#ifndef UTILS_H
#define UTILS_H

#include <chrono>  // Biblioteca de conversão de tempo
#include <ctype.h>
#include <iomanip> // Biblioteca para manipulação de tabelas
#include <iostream>
#include <string>
#include <thread> // Biblioteca para manipulação da thread
#include <vector>
#include <fstream>

#include ".env.h"

using namespace std;

void limparTerminal();

void maquinaDeEscrever(string texto);

int gerarNumeroAleatorio(int min, int max);

string readArquivo(string nomeArquivo);

void printTable(vector<string> cabecalho, vector<vector<string>> tabela, bool removerSeparador = false);
string generateVida(int vida);
string generateArmadura(int armadura);
string generateAtaque(int ataque);
string generateAtaqueEspecial(int ataque_especial);
string getNomeJogador();

int getClasseJogador();

void printBoasVindas(string nomeJogador);
void printInicio();
void printOpcoes();

#endif
