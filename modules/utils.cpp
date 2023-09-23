#include <chrono>  // Biblioteca de conversão de tempo
#include <ctype.h>
#include <iomanip> // Biblioteca para manipulação de tabelas
#include <iostream>
#include <string>
#include <thread> // Biblioteca para manipulação da thread
#include <vector>
#include <fstream>

#include ".env.h"
#include "classes.cpp"

using namespace std;

class Utilities {
	public:
		static string readArquivo(string nomeArquivo) {
			string caminho = "assets/" + nomeArquivo;

			string retorno = "";

			// Objeto ifstream para ler o arquivo
    		ifstream arquivo(caminho);

			// Verifica se o arquivo foi aberto com sucesso
			if (arquivo.is_open()) {
				std::string linha;
				while (std::getline(arquivo, linha)) {
					// Processa cada linha do arquivo aqui
					retorno += linha + "\n";
				}

				// Fecha o arquivo após a leitura
				arquivo.close();
			} else {
				std::cerr << "Não foi possível abrir o arquivo." << std::endl;
			}

			return retorno;
		};

		static void printTable(vector<string> cabecalho, vector<vector<string>> tabela) {
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

		static string generateVida(int vida) {return "Vida: " + to_string(vida);}
		static string generateArmadura(int armadura) {return "Armadura: " + to_string(armadura);}
		static string generateAtaque(int ataque) {return "Ataque: " + to_string(ataque);}
		static string generateAtaqueEspecial(int ataque_especial) {return "Ataque Especial: " + to_string(ataque_especial);}

		static string getNomeJogador() {
			string nomeJogador = "";
			char confirmacao = '_';

			// Início do jogo.
			while (nomeJogador == "") {
				cout << "Digite seu nome: ";
				cin >> nomeJogador;

				if (nomeJogador == "") {
					cout << "Nome inválido!" << endl;
				}

				cout << "\nSeu nome é: " << nomeJogador << ", correto? (S/N)" << endl;

				while (confirmacao != 'S' && confirmacao != 'N') {
					cout << "Escolha: ";
					cin >> confirmacao;

					confirmacao = toupper(confirmacao);

					if (confirmacao != 'S' && confirmacao != 'N') {
						cout << "Escolha inválida!" << endl;
					}
					else if (confirmacao == 'N' || confirmacao == 'n') {
						nomeJogador = "";
					}

				}
				confirmacao = '_';
			}

			return nomeJogador;
		}

		static int getClasseJogador() {
			int classeAtual = 0;
			while (classeAtual < 1 || classeAtual > 6) {
				cout << "\nEscolha: ";
				cin >> classeAtual;

				if (classeAtual < 1 || classeAtual > 6) {
					cout << "Escolha inválida!" << endl;
				}
			}

			return classeAtual - 1; // Ajusta o valor para o índice do vetor.
		}

		static void printBoasVindas(string nomeJogador) {
			limparTerminal();
			cout << "⛏️" << nomeJogador << ", bem vindo ao \033[32m\033[1mDeep Rock Galactic - Terminal Edition!\033[0m\n" << endl;

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

		static void printInicio() {
			enum Escolha {SEM_ESCOLHA, SIM, NAO};
			char pularHistoria = '_';
			
			Escolha escolha = SEM_ESCOLHA;
			while (escolha == SEM_ESCOLHA) {
				cout << "Deseja pular a história? (S/N): ";
				cin >> pularHistoria;

				pularHistoria = toupper(pularHistoria);

				if (pularHistoria == 'S') {
					escolha = SIM;
				} else if (pularHistoria == 'N') {
					escolha = NAO;
				} else {
					cout << "Escolha inválida!" << endl;
				}
			}

			limparTerminal();

			// Sai da função caso o jogador não queira ver a história.
			if (escolha == SIM) return;

			string historia = readArquivo("historia.txt");

			maquinaDeEscrever(historia);
		}

		static void printDetalhesClasse(string nome, Personagem *jogador) {
			int* estatisticas = jogador->getEstatisticas();

			vector<string> cabecalho = {"Estatísticas do jogador:\n\n"};
			vector<vector<string>> tabela = {
						{nome},
						{to_string(estatisticas[0])},
						{to_string(estatisticas[1])},
						{to_string(estatisticas[2])},
						{to_string(estatisticas[3])}
					};

			delete [] estatisticas;

			printTable(cabecalho, tabela);
		}

		static void printOpcoes() {
			cout << "Escolha uma opção:" << endl << endl;

			printTable({"1 - Atacar", "2 - Atacar Especial", "3 - Defender", "4 - Usar Item", "5 - Ver detalhes da classe"}, {});
		}

		static void limparTerminal() {
			system("clear||cls");
		}

		static void maquinaDeEscrever(string texto) {
			for (int i = 0; i < texto.length(); i++) {
				cout << texto[i] << flush;
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		}

		static int gerarNumeroAleatorio(int min, int max) {
			srand(time(NULL));
			return (rand() % (max - min + 1) + min);
		}
};