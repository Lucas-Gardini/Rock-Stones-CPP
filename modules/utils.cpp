#include <iostream>
#include <string>
#include <vector>
#include <iomanip> // Biblioteca para manipulação de tabelas
#include <thread> // Biblioteca para manipulação da thread
#include <chrono> // Biblioteca de conversão de tempo

#include "utils.h"
#include "environment.h"

using namespace std;

void printTable(vector<string> cabecalho, vector<vector<string>> tabela) {
    int num_colunas = cabecalho.size();
    vector<int> larguras(num_colunas, 0); // Inicializa todas as larguras das colunas como 0.

    // Encontre a largura máxima para cada coluna.
    for (int i = 0; i < num_colunas; i++) {
        larguras[i] = cabecalho[i].length() + 2; // Inicializa com a largura do cabeçalho + 2 espaços.
        for (const vector<string>& linha : tabela) {
            if (i < linha.size() && linha[i].length() + 2 > larguras[i]) {
                larguras[i] = linha[i].length() + 2;
            }
        }
    }

    // Imprimir cabeçalho
    for (int i = 0; i < num_colunas; i++) {
        cout << setw(larguras[i]) << left << cabecalho[i] << "| ";
    }
    cout << endl;

    // Imprimir linhas da tabela
    for (const vector<string>& linha : tabela) {
        for (int i = 0; i < num_colunas; i++) {
            cout << setw(larguras[i]) << left << linha[i] << "| ";
        }
        cout << endl;
    }
}

void printInicio() {
	cout << "Bem vindo ao jogo de RPG!" << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

	cout << "Para inciar, selecione uma classe:" << endl << endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));

	vector<string> cabecalho = {"1 - Batedor", "2- Guerreiro", "3 - Engenheiro", "4 - Escavador", "5 - Medico"};
	vector<vector<string>> tabela = {
		{
			"Vida: " + BATEDOR_VIDA,
			"Vida: " + GUERREIRO_VIDA,
			"Vida: " + ENGENHEIRO_VIDA,
			"Vida: " + ESCAVADOR_VIDA,
			"Vida: " + MEDICO_VIDA,
		},
		{"Armadura: 0", "Armadura: 0", "Armadura: 0", "Armadura: 0", "Armadura: 0"},
		{"Ataque: 0", "Ataque: 0", "Ataque: 0", "Ataque: 0", "Ataque: 0"},
		{"Ataque Especial: 0", "Ataque Especial: 0", "Ataque Especial: 0", "Ataque Especial: 0", "Ataque Especial: 0"},
	};

	printTable(cabecalho, tabela);
}