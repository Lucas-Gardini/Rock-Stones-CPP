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

	int classeAtual = 0;

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
		printDetalhesClasse(classeAtual);

		break;
	}

	return 0; 

}