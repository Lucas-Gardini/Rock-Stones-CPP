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


void maquinaDeEscrever(string texto, bool muitoRapido = false);

void dormir(int segundos);

int gerarNumeroAleatorio(int min, int max);

string readArquivo(string nomeArquivo);

void printTable(vector<string> cabecalho, vector<vector<string>> tabela, bool removerSeparador = false);
void printEncontroMonstro(string nomeMonstro, bool _limparTerminal);

string generateVida(int vida);
string generateArmadura(int armadura);
string generateAtaque(int ataque);
string generateAtaqueEspecial(int ataque_especial);
string getNomeJogador();

int getClasseJogador();

void printBoasVindas(string nomeJogador);
void printInicio();
void printOpcoes();

int* droparMinerios();

string lerArquivo(string nomeArquivo);

void pressioneUmaTecla(bool limpar = true);

char* gerarCodigoExtrator();

#endif
