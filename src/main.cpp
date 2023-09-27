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

	// Instânciando o jogo e criando o jogador.
	// Toda a lógica se encontra na classe abaixo.
	new JogoRPG();

	return 0; 
}