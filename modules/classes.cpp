#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include ".env.h"

using namespace std;

class Ataque {
	protected:
	string _nomeAtaque;
	int _danoAtaque;
};

class Personagem {
	protected:
	string nome;
	int _HP, _ATQ, _DEF, _ESP, recarga;
	int debuff = 0;
	Ataque ataques[2];

	public:
	Personagem(string nome, int ptVida, int ptDef, int ptAtq): _HP(ptVida), _ATQ(ptDef), _DEF(ptAtq){}

  bool VerificaVivo() {
    if(this->_HP > 0) {
      return true;    
    } else {
      return false;
    }
  }

  int getDebuff() { return this->debuff; }
  void setDebuff(int id) { this->debuff = id; }

	int* getEstatisticas() {
		int *estatisticas = new int[4];
		
		estatisticas[0] = this->_HP;
		estatisticas[1] = this->_DEF;
		estatisticas[2] = this->_ATQ;
		estatisticas[3] = this->_ESP;

		return estatisticas;
	}

	virtual void atacar() {
		cout << "Um personagem atacou!" << endl;
	}

	virtual void morrer() {
		cout << "O personagem morreu!" << endl;
	}

  	void setRecarga(int recarga) {
      this->recarga = recarga;
    }
};

class Batedor : public Personagem {
  private:
   int granadaIncendiaria = BATEDOR_ATQ_ESPECIAL;

  public:
    Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE){}

    // void atacar() override {
    //   int escolha;
      
    //   cout << "Selecione seu ataque: " << endl << "0- Ataque normal do batedor: Tiro de metralhadora - Dano: " << BATEDOR_ATAQUE << endl << "1- Ataque especial do batedor: Granada Incendiária - Dano: " << BATEDOR_ATQ_ESPECIAL << endl << ": ";
    //   cin >> escolha;

    //   if(escolha == 0){
    //     cout << "O batedor usou o ataque normal!";
    //   }

    //   else if(escolha == 1){
    //     if(recargaBatedor == 0){
    //       cout << "O batedor usou o ataque especial!";
    //       srand (time(NULL));

    //        if(rand() % 2 == 0){
    //         cout << "ATAQUE CRITICO!";
    //        }
    //        setRecarga(4);
    //     }
    //     else {
    //       setRecarga();
    //     }
    //   }
    // }
};

class Guerreiro : public Personagem {
  private:
   int miniGun = GUERREIRO_ATQ_ESPECIAL;
  public:
    Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE){}

    
    // void atacar() override {
    //   int escolha;
      
    //   cout << "Selecione seu ataque: " << endl << "0- Ataque normal do guerreiro: Tiro de metralhadora - Dano: " << GUERREIRO_ATAQUE << endl << "1- Ataque especial do Guerreiro: Granada Incendiária - Dano: " << GUERREIRO_ATQ_ESPECIAL << endl << ": ";
    //   cin >> escolha;

    //   if(escolha == 0){
    //     cout << "O guerreiro usou o ataque normal!";
    //   }

    //   else if(escolha == 1){
    //     if(recargaGuerreiro == 0){
    //       cout << "O guerreiro usou o ataque especial!";
    //       srand (time(NULL));

    //        if(rand() % 2 == 0){
    //         cout << "ATAQUE CRITICO!";
    //        }
    //     }
    //     else {
    //       setRecarga();
    //     }
    //   }
    // }
};

class Engenheiro : public Personagem {
  private:
   int sentryGun = ENGENHEIRO_ATQ_ESPECIAL;
  public:
    Engenheiro(string nome) : Personagem(nome, ENGENHEIRO_VIDA, ENGENHEIRO_DEFESA, ENGENHEIRO_ATAQUE){}
};

class Escavador : public Personagem {
  private:
   int lancaChamas = ESCAVADOR_ATQ_ESPECIAL;
  public:
    Escavador(string nome) : Personagem(nome, ESCAVADOR_VIDA, ESCAVADOR_DEFESA, ESCAVADOR_ATAQUE){}
};

class 	Medico : public Personagem {
  private:
   int kitBomba = MEDICO_ATQ_ESPECIAL;
  public:
    Medico(string nome) : Personagem(nome, MEDICO_VIDA, MEDICO_DEFESA, MEDICO_ATAQUE){}
};

class Monstro{
  protected:
	  string nome;
    int _HP, _ATQ, _DEF;
  public:
    Monstro(string nome, int ptVida, int ptDef, int ptAtq): nome(nome), _HP(ptVida), _DEF(ptDef), _ATQ(ptAtq){}

    bool VerificaVivo() {
      if(this->_HP > 0) {
        return true;    
      } else {
        return false;
      }
    }    

    virtual void atacar(){
      cout << "O monstro atacou!" << endl;
    }
};

class Aranha : Monstro {
  private:

  public:
     Aranha() : Monstro("Aranha",  ARANHA_VIDA, ARANHA_DEFESA, ARANHA_ATAQUE){}
         
};

class AranhaGrande : Monstro {
  private:

  public:
    AranhaGrande() : Monstro("Aranha Grande", ARANHA_GRANDE_VIDA, ARANHA_GRANDE_DEFESA, ARANHA_GRANDE_ATAQUE){}
};

class Escorpiao : Monstro {
  private:

  public:
    Escorpiao() : Monstro("Escorpião", ESCORPIAO_VIDA, ESCORPIAO_DEFESA, ESCORPIAO_ATAQUE){}
};

class JogoRPG {
	private:

	
	public:
		// Observação: As classes foram herdadas como "public" para permitir o "cast" da função abaixo
		Personagem* criarPersonagem(string nome, Classe escolha) {
			switch (escolha) {
				case BATEDOR:
					return new Batedor(nome);
					break;
				
				case GUERREIRO:
					return new Guerreiro(nome);
					break;
				
				case ENGENHEIRO:
					return new Engenheiro(nome);
					break;
				
				case ESCAVADOR:
					return new Escavador(nome);
					break;
				
				case MEDICO:
					return new Medico(nome);
					break;
				
				default:
					return new Personagem(nome, 0, 0, 0);
					break;
			}
		}

    int DanoDebuff(Personagem jogador) {
      if(jogador.getDebuff() == 1) {
        return 4;
      }
      else if(jogador.getDebuff() == 2) {
        return 2;
      }
      else {
        return 0;
      }
    }

    // Inicio combate, (rascunho)
    void Batalha(Personagem jogador, Monstro m) {
      while (jogador.VerificaVivo() == true && m.VerificaVivo() == true) {
        // jogador.setDebuff()
      }

	  if (jogador.VerificaVivo() == true) {
		  cout << "Você venceu!" << endl;
	  } else {
		  cout << "Você perdeu!" << endl;
	  }
    }    
};