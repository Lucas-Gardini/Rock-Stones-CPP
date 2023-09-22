#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

#include "modules/.env.h"
// #include "modules/classes.cpp" // arquivo já é importando em utils.cpp
#include "modules/utils.cpp"

using namespace std;

int main() { 
	// Definindo que o terminal deve utilizar utf-8.
	SetConsoleOutputCP(CP_UTF8);

	string nomeJogador = Utilities::getNomeJogador();

	Utilities::printInicio();

	int classeAtual = 0;
	while (classeAtual < 1 || classeAtual > 6) {
		cout << "\nEscolha: ";
		cin >> classeAtual;

		if (classeAtual < 1 || classeAtual > 6) {
			cout << "Escolha inválida!" << endl;
		}
	}

	classeAtual = classeAtual - 1; // Ajusta o valor para o índice do vetor.

	Utilities::limparTerminal();
	
	cout << "Classe escolhida: " << CLASSES[classeAtual] << "!" << endl;

	JogoRPG *jogo = new JogoRPG();
	Personagem *jogador = jogo->criarPersonagem(nomeJogador, Classe(classeAtual));

	// Loop principal do jogo.
	while(true) {
		Utilities::printOpcoes();
		Utilities::printDetalhesClasse(nomeJogador, jogador);

		break;
	}

	return 0; 
}