#include <chrono>  // Biblioteca de conversão de tempo
#include <ctype.h>
#include <iomanip> // Biblioteca para manipulação de tabelas
#include <iostream>
#include <string>
#include <thread> // Biblioteca para manipulação da thread
#include <vector>
#include <fstream>
#include <random>

#include ".env.h"

using namespace std;

// Função utilizada para limpar o terminal.
void limparTerminal() {
	system("clear||cls");
}

// Função utilizada para escrever o texto letra por letra.
// Ela espera um tempo entre cada letra, simulando uma máquina de escrever.
// Apresenta a opção de escrever muito rápido, para textos grandes.
void maquinaDeEscrever(string texto, bool muitoRapido = false) {
	for (int i = 0; i < texto.length(); i++) {
		cout << texto[i] << flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(muitoRapido ? 5 : 25));
	}

	std::cout << std::endl;
}

// Função utilizada para simular um tempo de espera.
// Ela espera um tempo em segundos.
void dormir(int segundos) {
	std::this_thread::sleep_for(std::chrono::seconds(segundos));
}

// Função utilizada para mostrar no terminal a mensagem de encontro com um monstro.
void printEncontroMonstro(string nomeMonstro, bool _limparTerminal) {
	dormir(1);
	
	if (_limparTerminal) limparTerminal();

	cout << "Caminhando pela caverna, você encontra um(a) " << nomeMonstro << "!" << endl;
	dormir(1);
	cout << "Prepare-se para lutar!" << endl;
	dormir(1);
}

// Função utilizada para gerar um número aleatório dentro de um intervalo.
int gerarNumeroAleatorio(int min, int max) {
    std::random_device                  rand_dev;
    std::mt19937                        generator(rand_dev());
    std::uniform_int_distribution<int>  distr(min, max);

    return distr(generator);
}

// Função utilizada para ler um arquivo da pasta assets e retornar seu conteúdo.
string lerArquivo(string nomeArquivo) {
	// Caminho do arquivo
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

// Função utilizada para exibir uma estrutura de tabela no terminal, a partir de um array de cabeçaçho e um array de linhas.
void printTable(vector<string> cabecalho, vector<vector<string>> tabela, bool removerSeparador = false) {
	try {
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
	} catch (string e) {
		cout << "Erro ao mostrar tabela";
	}
}

// Funções que servem simplesmente para concatenar um texto com um número.
// Para facilitar o seu uso abaixo.
string generateVida(int vida) {return "Vida: " + to_string(vida);}
string generateArmadura(int armadura) {return "Armadura: " + to_string(armadura);}
string generateAtaque(int ataque) {return "Ataque: " + to_string(ataque);}
string generateAtaqueEspecial(int ataque_especial) {return "Ataque Especial: " + to_string(ataque_especial);}

// Função utilizada para obter o nome do jogador.
string getNomeJogador() {
	string nomeJogador = "";
	char confirmacao = '_';

	// Loop de obtenção de nome
	while (nomeJogador == "") {
		cout << "Digite seu nome: ";
   		std::getline(cin, nomeJogador);

		// Caso o nome do jogador não seja informado.
		if (nomeJogador == "") {
			cout << "Nome inválido!" << endl;
			continue;
		}

		// Pergunta e verifica se o nome está correto.
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

// Função utilizada para obter a classe do jogador.
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

// Função utilizada para mostrar no terminal a mensagem de boas vindas e de escolha de classe.
void printBoasVindas(string nomeJogador) {
	limparTerminal();
	cout << nomeJogador << ", bem vindo ao \033[32m\033[1mDeep Rock Galactic - Terminal Edition!\033[0m\n" << endl;

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

// Função utilizada para mostrar no terminal os textos de introdução do jogo.
// Como tutorial e história.
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
	string chegando = lerArquivo("chegando_no_planeta.txt");
	// Sai da função caso o jogador não queira ver a história.
	if (escolha == NAO) {
		maquinaDeEscrever(historia, true);
		dormir(1);
		cout << "\n\n";
		dormir(3);
		cout << chegando;
	}
	
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

	maquinaDeEscrever(tutorial, true);
}

// Função utilizada para mostrar no terminal as opções de ação do jogador.
void printOpcoes() {
	cout << "Escolha uma opção:" << endl << endl;

	printTable({"1 - Atacar", "2 - Atacar Especial", "3 - Ver seus atributos", "4 - Ver atributos do monstro", "5 - Invocar uma capsula de cura"}, {});
}

int* droparMinerios() {
	// Array de minérios e suas quantidades.
	int minerios[4][2] = {
		{OURO, 0},
		{MORKITA, 0},
		{DYSTRUM, 0},
		{NITRA, 0}
	};

    int* resultado = new int[4];  // Aloca um array dinâmico para armazenar os resultados

    for (int i = 0; i < 4; ++i) {
        // Gera um número aleatório entre 1 e 255
        minerios[i][1] = gerarNumeroAleatorio(1, 255);
        
        // Atualiza o array de resultados com a quantidade gerada
        resultado[i] = minerios[i][1];
    }

    return resultado;
}

// Função utilizada para aguardar o jogador pressionar uma tecla.
void pressioneUmaTecla(bool limpar = true) {
	cout << "\nPressione uma tecla para continuar...";
	
	// Limpar o buffer de entrada
	if (limpar)
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	cin.get();
}

char* gerarCodigoExtrator() {
    // Inicializa o gerador de números aleatórios com o tempo atual
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Array para armazenar os dígitos
    char* digitos = new char[5]{'\0'};  // Adicionando '\0' para garantir que seja tratado como uma string

    // Preenche o array com os números de '1' a '4'
    for (int i = 0; i < 4; ++i) {
        digitos[i] = static_cast<char>('1' + i);
    }

    // Embaralha os dígitos usando o algoritmo de Fisher-Yates
    for (int i = 3; i > 0; --i) {
        int j = std::rand() % (i + 1);
        std::swap(digitos[i], digitos[j]);
    }

    return digitos;
}