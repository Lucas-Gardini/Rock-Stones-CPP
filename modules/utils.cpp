#include "utils.h"

#include <chrono>  // Biblioteca de conversão de tempo
#include <iomanip> // Biblioteca para manipulação de tabelas
#include <iostream>
#include <string>
#include <thread> // Biblioteca para manipulação da thread
#include <vector>

#include ".env.h"

using namespace std;

void printTable(vector<string> cabecalho, vector<vector<string>> tabela) {
  int num_colunas = cabecalho.size();
  vector<int> larguras(num_colunas, 0); // Inicializa todas as larguras das colunas como 0.

  // Encontre a largura máxima para cada coluna.
  for (int i = 0; i < num_colunas; i++) {
    larguras[i] = cabecalho[i].length() + 2; // Inicializa com a largura do cabeçalho + 2 espaços.
    for (const vector<string> &linha : tabela) {
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
  for (const vector<string> &linha : tabela) {
    for (int i = 0; i < num_colunas; i++) {
      cout << setw(larguras[i]) << left << linha[i] << "| ";
    }
    cout << endl;
  }
}

string generateVida(int vida) {return "Vida: " + to_string(vida);}
string generateArmadura(int armadura) {return "Armadura: " + to_string(armadura);}
string generateAtaque(int ataque) {return "Ataque: " + to_string(ataque);}
string generateAtaqueEspecial(int ataque_especial) {return "Ataque Especial: " + to_string(ataque_especial);}

void printInicio() {
  cout << "Bem vindo ao jogo de RPG!" << endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  cout << "Para inciar, selecione uma classe:" << endl << endl;

  std::this_thread::sleep_for(std::chrono::seconds(1));

  vector<string> cabecalho = {"1 - Batedor", "2- Guerreiro", "3 - Engenheiro", "4 - Escavador", "5 - Medico"};

  vector<vector<string>> tabela = {
      {generateVida(BATEDOR_VIDA), generateVida(GUERREIRO_VIDA),  generateVida(ENGENHEIRO_VIDA), generateVida(ESCAVADOR_VIDA), generateVida(MEDICO_VIDA)},
      {generateArmadura(BATEDOR_DEFESA), generateArmadura(GUERREIRO_DEFESA), generateArmadura(ENGENHEIRO_DEFESA), generateArmadura(ESCAVADOR_DEFESA), generateArmadura(MEDICO_DEFESA)},
      {generateAtaque(BATEDOR_ATAQUE), generateAtaque(GUERREIRO_ATAQUE), generateAtaque(ENGENHEIRO_ATAQUE), generateAtaque(ESCAVADOR_ATAQUE), generateAtaque(MEDICO_ATAQUE)},
      {generateAtaqueEspecial(0), generateAtaqueEspecial(0), generateAtaqueEspecial(0), generateAtaqueEspecial(0), generateAtaqueEspecial(0)},
  };

  printTable(cabecalho, tabela);
}

void printDetalhesClasse(string nome, int vida, int defesa, int ataqueB, int ataqueE) {
 	vector<string> cabecalho = {"Estatísticas do jogador:\n\n"};
	vector<vector<string>> tabela = {
				{nome},
				{to_string(vida)},
				{to_string(defesa)},
				{to_string(ataqueB)},
				{to_string(ataqueE)}
			};

	printTable(cabecalho, tabela);
}

void printOpcoes() {
	cout << "Escolha uma opção:" << endl << endl;

	printTable({"1 - Atacar", "2 - Atacar Especial", "3 - Defender", "4 - Usar Item", "5 - Ver detalhes da classe"}, {});
}

void limparTerminal() {
	system("clear||cls");
}

int gerarNumeroAleatorio(int min, int max) {
	srand(time(NULL));
	return (rand() % (max - min + 1) + min);
}