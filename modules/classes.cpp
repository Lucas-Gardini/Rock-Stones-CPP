#include <iostream>
#include <string>
#include <vector>

using namespace std;

class JogoRPG {};

class Ataque {
protected:
  string _nomeAtaque;
  int _danoAtaque;
}

class Personagem {
private:
  string nome;
  int ptVida, ptAtq, ptDef;
  Ataque ataques[2];

public:
  Personagem(string nome, int ptVida, int ptAtq, int ptDef)
      : nome(nome), ptVida(ptVida), ptAtq(ptAtq), ptDef(ptDef) {}
};

class Bruxo : Personagem {
private:
  string circuloDeFogo public:
};

class Ladrao : Personagem {
private:
  string Furto

      public:
};

class Arqueiro : Personagem {
private:
  string FlechaFogo

      public:
};

class Guerreiro : Personagem {};

class Elfo : Personagem {};

class Clerigo : Personagem {};
