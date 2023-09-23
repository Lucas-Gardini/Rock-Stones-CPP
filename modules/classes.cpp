#include <iostream>
#include <string>
#include <vector>
#include ".env.h"

// #include "utils.cpp"

using namespace std;

class Ataque {
	protected:
	string _nomeAtaque;
	int _danoAtaque;
};

class Personagem {
	protected:
	string nome;
	int _HP, _ATQ, _DEF, _ESP, recargaTempo;
	int debuff = 0;
	Ataque ataques[2];

	public:
	Personagem(string nome, int ptVida, int ptDef, int ptAtq, int recarga): nome(nome), _HP(ptVida), _ATQ(ptDef), _DEF(ptAtq), recargaTempo(recarga) {}

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

	virtual int atacar(int turno) {
		cout << "Um personagem atacou!" << endl;
	}

	virtual void morrer() {
		cout << "O personagem morreu!" << endl;
	}
};

class Batedor : public Personagem {
  private:
   int granadaIncendiaria = BATEDOR_ATQ_ESPECIAL;

  public:

    Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE, recargaTempo){}

    int atacar(int turno) override {
      int escolha;
      
      while(true){
        cout << "Selecione seu ataque: " << endl << "0- Ataque normal do batedor: Tiro de metralhadora - Dano: " << BATEDOR_ATAQUE << endl << "1- Ataque especial do batedor: Granada Incendiária - Dano: " << BATEDOR_ATQ_ESPECIAL << endl << ": ";
        cin >> escolha;
        if(escolha != 0 || escolha != 1){
          cout << "Escolha inválida, por favor escolha entre 0 ou 1!!" << endl;
        }
        else{
          break;
        }
      }

      if(escolha == 0){
        cout << "O batedor usou o ataque normal!";
        return BATEDOR_ATAQUE;
      }
      else{
        if(recarga == 0){
          cout << "O batedor usou o ataque especial!";
           
           int ran = Utilities::gerarNumeroAleatorio(0, 1);

           if(ran == 0){
            cout << "ATAQUE CRÍTICO!";
            return BATEDOR_ATQ_ESPECIAL * 2;
           }

          return BATEDOR_ATQ_ESPECIAL;
        }
        else {
          cout << "O ataque especial não está pronto! O personagem trocou para o ataque normal!" << endl;
          return BATEDOR_ATAQUE;
        }
      }
    }
};

class Guerreiro : public Personagem {
  private:
   int miniGun = GUERREIRO_ATQ_ESPECIAL;
  public:
    Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE){}

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

    void setVida(int dano){
      this->_HP -= dano;
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
      int turno = 0;
      while (jogador.VerificaVivo() == true && m.VerificaVivo() == true) {
        // jogador.setDebuff()

        cout << "A batalha se inicia!" << endl;

        int personAtq = jogador.atacar(turno);
        m.setVida(personAtq);

        turno ++;
      }

	  if (jogador.VerificaVivo() == true) {
		  cout << "Você venceu!" << endl;
	  } else {
		  cout << "Você perdeu!" << endl;
	  }
    }    
};