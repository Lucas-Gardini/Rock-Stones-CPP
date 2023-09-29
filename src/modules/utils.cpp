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

void limparTerminal() {
	system("clear||cls");
}

void maquinaDeEscrever(string texto) {
	for (int i = 0; i < texto.length(); i++) {
		cout << texto[i] << flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}

	std::cout << std::endl;
}

int gerarNumeroAleatorio(int min, int max) {
	srand(time(NULL));
	return (rand() % (max - min + 1) + min);
}

string lerArquivo(string nomeArquivo) {
	string caminho = "./src/assets/" + nomeArquivo;

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

void printTable(vector<string> cabecalho, vector<vector<string>> tabela, bool removerSeparador = false) {
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
		cout << setw(larguras[i]) << left << cabecalho[i] << (removerSeparador ? "" : "| ");
	}
	cout << endl;

	// Imprimir linhas da tabela
	for (const vector<string> &linha : tabela) {
		for (int i = 0; i < num_colunas; i++) {
			cout << setw(larguras[i]) << left << linha[i] << (removerSeparador ? "" : "| ");
		}
		cout << endl;
	}
}

string generateVida(int vida) {return "Vida: " + to_string(vida);}
string generateArmadura(int armadura) {return "Armadura: " + to_string(armadura);}
string generateAtaque(int ataque) {return "Ataque: " + to_string(ataque);}
string generateAtaqueEspecial(int ataque_especial) {return "Ataque Especial: " + to_string(ataque_especial);}

string getNomeJogador() {
	string nomeJogador = "";
	char confirmacao = '_';

	// Início do jogo.
	while (nomeJogador == "") {
		cout << "Digite seu nome: ";
   		std::getline(cin, nomeJogador);

		if (nomeJogador == "") {
			cout << "Nome inválido!" << endl;
		}

		cout << "\nSeu nome é: " << nomeJogador << ", correto? (S/N)" << endl;

		while (confirmacao != 'S' && confirmacao != 'N') {
			cout << "Escolha: ";
			cin.get(confirmacao);

			confirmacao = toupper(confirmacao);

			if (confirmacao != 'S' && confirmacao != 'N') {
				cout << "Escolha inválida!" << endl;
			}
			else if (confirmacao == 'N' || confirmacao == 'n') {
				nomeJogador = "";
			}
		}
		
		// Limpar o buffer do cin para evitar problemas
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		confirmacao = '_';
	}

	return nomeJogador;
}

int getClasseJogador() {
	int classeAtual = 0;
	while (classeAtual < 1 || classeAtual >= 6) {
		cout << "\nEscolha: ";
		cin >> classeAtual;

		if (classeAtual < 1 || classeAtual >= 6) {
			cout << "Escolha inválida!" << endl;
		}
	}

	return classeAtual - 1; // Ajusta o valor para o índice do vetor.
}

void printBoasVindas(string nomeJogador) {
	limparTerminal();
	cout << "⛏️ " << nomeJogador << ", bem vindo ao \033[32m\033[1mDeep Rock Galactic - Terminal Edition!\033[0m\n" << endl;

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

void printInicio() {
	enum Escolha {SEM_ESCOLHA, SIM, NAO};
	char pularHistoria = '_';
	
	Escolha escolha = SEM_ESCOLHA;
	while (escolha == SEM_ESCOLHA) {
		// Limpando o buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Deseja pular a história? (S/N): ";
		cin.get(pularHistoria);

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

	string historia = lerArquivo("historia.txt");

	// Sai da função caso o jogador não queira ver a história.
	if (escolha == NAO)
		maquinaDeEscrever(historia);

	char pularTutorial = '_';
	escolha = SEM_ESCOLHA;
	while (escolha == SEM_ESCOLHA) {
		// Limpando o buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Deseja ver o tutorial? (S/N): ";
		cin.get(pularTutorial);

		pularTutorial = toupper(pularTutorial);

		if (pularTutorial == 'S') {
			escolha = SIM;
		} else if (pularTutorial == 'N') {
			escolha = NAO;
		} else {
			cout << "Escolha inválida!" << endl;
		}
	}

	// Sai da função caso o jogador não queira ver o tutorial.
	if (escolha == NAO) return;

	string tutorial = lerArquivo("tutorial.txt");

	std::cout << "\n\n";

	maquinaDeEscrever(tutorial);
}

void printOpcoes() {
	cout << "Escolha uma opção:" << endl << endl;

	printTable({"1 - Atacar", "2 - Atacar Especial", "3 - Ver detalhes da classe"}, {});
}
