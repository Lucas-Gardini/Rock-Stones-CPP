#include <iostream>
#include <string>
#include <vector>
#include <environment.h>

using namespace std;

class JogoRPG {};

class Ataque {
protected:
  string _nomeAtaque;
  int _danoAtaque;
}

class Personagem {
protected:
  string nome;
  int ptVida, ptAtq, ptDef;
  int sangrando = 0;
  Ataque ataques[2];

public:
  Personagem(int ptVida, int ptDef, int ptAtq): ptVida(ptVida), ptDef(ptDef), ptAtq(ptAtq){}

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
    int granadaIncendiaria = 20, ptVida, ptDef, ptAtq; 
  public:

    Batedor(){
		  this->ptVida = BATEDOR_VIDA;
    	this->ptDef = BATEDOR_DEFESA;
    	this->ptAtq = BATEDOR_ATAQUE;
	}

    void atacar() override{
      
    }
};

class Guerreiro : Personagem {
  private:
    int miniGun = 30, ptVida, ptDef, ptAtq;
  public:

    Guerreiro(){
      this->ptVida = GUERREIRO_VIDA;
      this->ptDef = GUERREIRO_DEFESA;
      this->ptAtq = GUERREIRO_ATAQUE;
    }

    void atacar() override{
        
    }
};

class Engenheiro : Personagem {
  private:
    int sentryGun = 20, ptVida, ptDef, ptAtq;
  public:

    Engenheiro(){
      this->ptVida = ENGENHEIRO_VIDA;
      this->ptDef = ENGENHEIRO_DEFESA;
      this->ptAtq = ENGENHEIRO_ATAQUE;
    }

    void atacar() override{
      
    }
};

class Escavador : Personagem {
  private:
    int lancaChamas = 20, ptVida, ptDef, ptAtq;
  public:

    Escavador(){
      this->ptVida = ESCAVADOR_VIDA;
      this->ptDef = ESCAVADOR_DEFESA;
      this->ptAtq = ESCAVADOR_ATAQUE;
    }

    void atacar() override{
      
    }
};

class Medico : Personagem {
  private:
    int quitBomba = 30, ptVida, ptDef, ptAtq;
  public:

    Medico(){
      this->ptVida = MEDICO_VIDA;
      this->ptDef = MEDICO_DEFESA;
      this->ptAtq = MEDICO_ATAQUE;
    }

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
