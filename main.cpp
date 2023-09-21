#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>

#include "modules/.env.h"
#include "modules/utils.h"

using namespace std;

int main() { 
	// Definindo que o terminal deve utilizar utf-8.
	SetConsoleOutputCP(CP_UTF8);

	// Variáveis iniciais.
	string nomeJogador = "";
	int classeAtual = 0;

	// Início do jogo.
	while (nomeJogador == "") {
		cout << "Digite seu nome: ";
		cin >> nomeJogador;

		if (nomeJogador == "") {
			cout << "Nome inválido!" << endl;
		}

		cout << "Seu nome é: " << nomeJogador << ", correto? (S/N)" << endl;
		char confirmacao;

		while (confirmacao != 'S' && confirmacao != 'N') {
			cout << "Escolha: ";
			cin >> confirmacao;

			confirmacao = toupper(confirmacao);

			if (confirmacao != 'S' && confirmacao != 'N') {
				cout << "Escolha inválida!" << endl;
			}
		}
		
		if (confirmacao == 'N' || confirmacao == 'n') {
			nomeJogador = "";
		}
	}


	printInicio();

	while (classeAtual < 1 || classeAtual > 6) {
		cout << "\nEscolha: ";
		cin >> classeAtual;

		if (classeAtual < 1 || classeAtual > 6) {
			cout << "Escolha inválida!" << endl;
		}
	}

	limparTerminal();
	
	cout << "Classe escolhida: " << CLASSES[classeAtual] << "!" << endl;

	

	// Loop principal do jogo.
	while(true) {
		printOpcoes();
		printDetalhesClasse(nomeJogador, );

		break;
	}

	return 0; 

}