#include <iostream>
#include <string>
#include <vector>

#include ".env.h"

using namespace std;

class JogoRPG {
	private:
	

	public:
};

class Ataque {
	protected:
	string _nomeAtaque;
	int _danoAtaque;
};

class Personagem {
	protected:
	string nome;
	int _HP, _ATQ, _DEF;
	int sangrando = 0;
	Ataque ataques[2];

	public:
	Personagem(string nome, int ptVida, int ptDef, int ptAtq): _HP(ptVida), _ATQ(ptDef), _DEF(ptAtq){}

	void showEstatisticas() {
		
	}

	virtual void atacar(){
		cout << "Um personagem atacou!" << endl;
	}

	virtual void morrer() {
		cout << "O personagem morreu!" << endl;
	}
};

class Batedor : Personagem {
  private:
   int granadaIncendiaria = BATEDOR_ATQ_ESPECIAL;

  public:
    Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE){}

    void atacar() override{
      
    }
};

class Guerreiro : Personagem {
  private:
   int miniGun = GUERREIRO_ATQ_ESPECIAL;

  public:
    Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE){}

    void atacar() override{
        
    }
};

class Engenheiro : Personagem {
  private:
   int sentryGun = ENGENHEIRO_ATQ_ESPECIAL;

  public:
    Engenheiro(string nome) : Personagem(nome, ENGENHEIRO_VIDA, ENGENHEIRO_DEFESA, ENGENHEIRO_ATAQUE){}

    void atacar() override{
      
    }
};

class Escavador : Personagem {
  private:
   int lancaChamas = ESCAVADOR_ATQ_ESPECIAL;

  public:
    Escavador(string nome) : Personagem(nome, ESCAVADOR_VIDA, ESCAVADOR_DEFESA, ESCAVADOR_ATAQUE){}

    void atacar() override{
      
    }
};

class Medico : Personagem {
  private:
   int kitBomba = MEDICO_ATQ_ESPECIAL;

  public:
    Medico(string nome) : Personagem(nome, MEDICO_VIDA, MEDICO_DEFESA, MEDICO_ATAQUE){}

    void atacar() override{
      
    }
};

class Monstro{
  private:
    int ptVida, ptDef, ptAtq;

  public:
    Monstro(int ptVida, int ptDef, int ptAtq): ptVida(ptVida), ptDef(ptDef), ptAtq(ptAtq){}

    virtual void atacar(){
      cout << "O monstro atacou!" << endl;
    }
};

Personagem* criarPersonagem(string nome, Classe escolha) {}