#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

#include "modules/.env.h"
// #include "modules/classes.cpp" // arquivo já é importando em utils.cpp
#include "modules/utils.cpp"
// #include "modules/utils.cpp"

using namespace std;

int main() { 
	// Definindo que o terminal deve utilizar utf-8.
	SetConsoleOutputCP(CP_UTF8);

	// Obtendo o nome do jogador.
	string nomeJogador = Utilities::getNomeJogador();

	// Exibindo a mensagem de início do jogo. 
	Utilities::printBoasVindas(nomeJogador);

	// Obtendo a classe do jogador.
	int classeAtual = Utilities::getClasseJogador();

	// Limpando o terminal.
	Utilities::limparTerminal();
	
	cout << "Classe escolhida: " << CLASSES[classeAtual] << "!" << endl;

	// Instânciando o jogo e criando o jogador.
	JogoRPG *jogo = new JogoRPG();
	Personagem *jogador = jogo->criarPersonagem(nomeJogador, Classe(classeAtual));

	// Exibindo a história do jogo.
	Utilities::printInicio();

	// Loop principal do jogo.
	// while(true) {
	// 	Utilities::printOpcoes();
	// 	Utilities::printDetalhesClasse(nomeJogador, jogador);

	// 	break;
	// }

	return 0; 
}