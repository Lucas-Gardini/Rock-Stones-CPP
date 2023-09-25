#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

#include "modules/.env.h"
#include "modules/classes.cpp"
#include "modules/utils.h"

using namespace std;

int main() { 
	// Definindo que o terminal deve utilizar utf-8.
	SetConsoleOutputCP(CP_UTF8);

	// Obtendo o nome do jogador.
	string nomeJogador = getNomeJogador();

	// Exibindo a mensagem de início do jogo. 
	printBoasVindas(nomeJogador);

	// Obtendo a classe do jogador.
	int classeAtual = getClasseJogador();

	// Limpando o terminal.
	limparTerminal();
	
	cout << "Classe escolhida: " << CLASSES[classeAtual] << "!" << endl;

	// Instânciando o jogo e criando o jogador.
	JogoRPG *jogo = new JogoRPG();
	Personagem *jogador = jogo->criarPersonagem(nomeJogador, Classe(classeAtual));

	// Exibindo a história do jogo.
	printInicio();

	// Loop principal do jogo.
	// while(true) {
	// 	printOpcoes();
	jogador->printDetalhesClasse();

	// 	break;
	// }

	return 0; 
}