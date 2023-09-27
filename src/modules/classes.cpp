#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include ".env.h"
#include "utils.h"

using namespace std;

class Ataque {
	protected:
	string _nomeAtaque;
	int _danoAtaque;
};

class Personagem {
	protected:
		// Atributos inicias
		string nome;
		int _HP, _ATQ, _DEF, _ESP, _MANA;
		int vidaAtual = 0;
		int manaAtual = 0;
		int debuff = 0;

		Ataque ataques[2];

		int minerios[4][2] = {
			{OURO, 0},
			{MORKITA, 0},
			{DYSTRUM, 0},
			{NITRA, 0}
		};

	public:
		Personagem(string nome, int ptVida, int ptDef, int ptAtq, int mana): nome(nome), _HP(ptVida), _ATQ(ptDef), _DEF(ptAtq), _MANA(mana) {
			this->vidaAtual = ptVida;
		}

		bool VerificaVivo() {
			if(this->_HP > 0) {
			return true;    
			} else {
			return false;
			}
		}

		bool VerificaMana(int mana){
			if(this->manaAtual >= this->_MANA) {
			return true;    
			} else {
				this->manaAtual += mana;
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

		void printDetalhesClasse() {
			int* estatisticas = this->getEstatisticas();

			vector<string> cabecalho = {"Estatísticas:\n", ""};
			vector<vector<string>> tabela = {
				{"Nome:", this->nome},
				{"Vida:", to_string(estatisticas[0])},
				{"Defesa:", to_string(estatisticas[1])},
				{"Dano de ataque:", to_string(estatisticas[2])},
				{"Dano do especial:", to_string(estatisticas[3])}
			};

			delete [] estatisticas;

			printTable(cabecalho, tabela, true);
		}

		void solicitaCapsula() {
			if (*this->minerios[NITRA] > CUSTO_CAPSULA) {
				this->vidaAtual += int((this->_HP / 2));
				cout << "Você se curou em " << int((this->_HP / 2)) << " pontos de vida!" << endl;
			}
		}

		void tomarDano(int dano){
			this->vidaAtual -= (dano - this->_DEF);
		} 

		virtual int atacar() {
			cout << "Um personagem atacou!" << endl;
			return 1;
		}

		virtual void morrer() {
			cout << "O personagem morreu!" << endl;
		}
};

class Batedor : public Personagem {
  	private:
   		int granadaIncendiaria = BATEDOR_ATQ_ESPECIAL;

  	public:
		Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE, BATEDOR_MANA){}

		int atacar() override {
			int escolha = -1;
			
			while(escolha < 0 && escolha > 1){
				cout << "Selecione seu ataque: " << endl << "0- Ataque normal do batedor: Tiro de metralhadora - Dano: " << BATEDOR_ATAQUE << endl << "1- Ataque especial do batedor: Granada Incendiária - Dano: " << BATEDOR_ATQ_ESPECIAL << endl << ": ";
				cin >> escolha;
				if(escolha != 0 || escolha != 1){
					cout << "Escolha inválida, por favor escolha entre 0 ou 1!!" << endl;
				}
			}

			if(escolha == 0){
				cout << "O batedor usou o ataque normal!";
				return BATEDOR_ATAQUE;
			} else{
				if(this->manaAtual >= this->_MANA){
					cout << "O batedor usou o ataque especial!";
				
					int ran = gerarNumeroAleatorio(0, 1);

					if(ran == 0){
						cout << "ATAQUE CRÍTICO!";
						this->manaAtual -= BATEDOR_CUSTO_ESPECIAL;
						return BATEDOR_ATQ_ESPECIAL * 2;
					}
					this->manaAtual -= BATEDOR_CUSTO_ESPECIAL;
					return BATEDOR_ATQ_ESPECIAL;
				} else {
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
    	Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE, GUERREIRO_MANA){}

		int atacar() override {
			int escolha = -1;
			
			while(escolha < 0 && escolha > 1){
				cout << "Selecione seu ataque: " << endl << "0- Ataque normal do guerreiro: Tiro de metralhadora - Dano: " << GUERREIRO_ATAQUE << endl << "1- Ataque especial do guerreiro: Granada Incendiária - Dano: " << GUERREIRO_ATQ_ESPECIAL << endl << ": ";
				cin >> escolha;
				if(escolha != 0 || escolha != 1){
					cout << "Escolha inválida, por favor escolha entre 0 ou 1!!" << endl;
				}
			}

			if(escolha == 0){
				cout << "O guerreiro usou o ataque normal!";
				return GUERREIRO_ATAQUE;
			} else{
				if(this->manaAtual >= this->_MANA){
					cout << "O guerreiro usou o ataque especial!";
				
					int ran = gerarNumeroAleatorio(0, 1);

					if(ran == 0){
						cout << "ATAQUE CRÍTICO!";
						this->manaAtual -= GUERREIRO_CUSTO_ESPECIAL;
						return GUERREIRO_ATQ_ESPECIAL * 2;
					}
					this->manaAtual -= GUERREIRO_CUSTO_ESPECIAL;
					return GUERREIRO_ATQ_ESPECIAL;
				} else {
					cout << "O ataque especial não está pronto! O personagem trocou para o ataque normal!" << endl;
					return GUERREIRO_ATAQUE;
				}
			}
		}
};

class Engenheiro : public Personagem {
  	private:
   		int sentryGun = ENGENHEIRO_ATQ_ESPECIAL;
  	public:
    	Engenheiro(string nome) : Personagem(nome, ENGENHEIRO_VIDA, ENGENHEIRO_DEFESA, ENGENHEIRO_ATAQUE, ENGENHEIRO_MANA){}

		int atacar() override {
			int escolha = -1;
			
			while(escolha < 0 && escolha > 1){
				cout << "Selecione seu ataque: " << endl << "0- Ataque normal do engenheiro: Tiro de metralhadora - Dano: " << ENGENHEIRO_ATAQUE << endl << "1- Ataque especial do engenheiro: Granada Incendiária - Dano: " << ENGENHEIRO_ATQ_ESPECIAL << endl << ": ";
				cin >> escolha;
				if(escolha != 0 || escolha != 1){
					cout << "Escolha inválida, por favor escolha entre 0 ou 1!!" << endl;
				}
			}

			if(escolha == 0){
				cout << "O engenheiro usou o ataque normal!";
				return ENGENHEIRO_ATAQUE;
			} else{
				if(this->manaAtual >= this->_MANA){
					cout << "O engenheiro usou o ataque especial!";
				
					int ran = gerarNumeroAleatorio(0, 1);

					if(ran == 0){
						cout << "ATAQUE CRÍTICO!";
						this->manaAtual -= ENGENHEIRO_CUSTO_ESPECIAL;
						return ENGENHEIRO_ATQ_ESPECIAL * 2;
					}
					this->manaAtual -= ENGENHEIRO_CUSTO_ESPECIAL;
					return ENGENHEIRO_ATQ_ESPECIAL;
				} else {
					cout << "O ataque especial não está pronto! O personagem trocou para o ataque normal!" << endl;
					return ENGENHEIRO_ATAQUE;
				}
			}
		}
};

class Escavador : public Personagem {
	private:
   		int lancaChamas = ESCAVADOR_ATQ_ESPECIAL;
  	public:
    	Escavador(string nome) : Personagem(nome, ESCAVADOR_VIDA, ESCAVADOR_DEFESA, ESCAVADOR_ATAQUE, ESCAVADOR_MANA){}

		int atacar() override {
			int escolha = -1;
			
			while(escolha < 0 && escolha > 1){
				cout << "Selecione seu ataque: " << endl << "0- Ataque normal do escavador: Tiro de metralhadora - Dano: " << ESCAVADOR_ATAQUE << endl << "1- Ataque especial do escavador: Granada Incendiária - Dano: " << ESCAVADOR_ATQ_ESPECIAL << endl << ": ";
				cin >> escolha;
				if(escolha != 0 || escolha != 1){
					cout << "Escolha inválida, por favor escolha entre 0 ou 1!!" << endl;
				}
			}

			if(escolha == 0){
				cout << "O escavador usou o ataque normal!";
				return ESCAVADOR_ATAQUE;
			} else{
				if(this->manaAtual >= this->_MANA){
					cout << "O escavador usou o ataque especial!";
				
					int ran = gerarNumeroAleatorio(0, 1);

					if(ran == 0){
						cout << "ATAQUE CRÍTICO!";
						this->manaAtual -= ESCAVADOR_CUSTO_ESPECIAL;
						return ESCAVADOR_ATQ_ESPECIAL * 2;
					}
					this->manaAtual -= ESCAVADOR_CUSTO_ESPECIAL;
					return ESCAVADOR_ATQ_ESPECIAL;
				} else {
					cout << "O ataque especial não está pronto! O personagem trocou para o ataque normal!" << endl;
					return ESCAVADOR_ATAQUE;
				}
			}
		}
};

class Medico : public Personagem {
	private:
   		int kitBomba = MEDICO_ATQ_ESPECIAL;
  	public:
    	Medico(string nome) : Personagem(nome, MEDICO_VIDA, MEDICO_DEFESA, MEDICO_ATAQUE, MEDICO_MANA){}

		int atacar() override {
			int escolha = -1;
			
			while(escolha < 0 && escolha > 1){
				cout << "Selecione seu ataque: " << endl << "0- Ataque normal do médico: Tiro de metralhadora - Dano: " << MEDICO_ATAQUE << endl << "1- Ataque especial do médico: Granada Incendiária - Dano: " << MEDICO_ATQ_ESPECIAL << endl << ": ";
				cin >> escolha;
				if(escolha != 0 || escolha != 1){
					cout << "Escolha inválida, por favor escolha entre 0 ou 1!!" << endl;
				}
			}

			if(escolha == 0){
				cout << "O médico usou o ataque normal!";
				return MEDICO_ATAQUE;
			} else{
				if(this->manaAtual >= this->_MANA){
					cout << "O médico usou o ataque especial!";
				
					int ran = gerarNumeroAleatorio(0, 1);

					if(ran == 0){
						cout << "ATAQUE CRÍTICO!";
						this->manaAtual -= MEDICO_CUSTO_ESPECIAL;
						return MEDICO_ATQ_ESPECIAL * 2;
					}
					this->manaAtual -= MEDICO_CUSTO_ESPECIAL;
					return MEDICO_ATQ_ESPECIAL;
				} else {
					cout << "O ataque especial não está pronto! O personagem trocou para o ataque normal!" << endl;
					return MEDICO_ATAQUE;
				}
			}
		}
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

		void tomarDano(int dano){
			this->_HP -= (dano - this->_DEF);
		}    

		virtual int atacar(){
			cout << "O monstro atacou!" << endl;
			return 1;

		}
};

class Aranha : public Monstro {
  	private:
	
	public:
		Aranha() : Monstro("Aranha",  ARANHA_VIDA, ARANHA_DEFESA, ARANHA_ATAQUE){}

		int atacar() override{
			return ARANHA_ATAQUE;
		}
};

class AranhaGrande : public Monstro {
	private:

  	public:
    	AranhaGrande() : Monstro("Aranha Grande", ARANHA_GRANDE_VIDA, ARANHA_GRANDE_DEFESA, ARANHA_GRANDE_ATAQUE){}

		int atacar() override{
			return ARANHA_GRANDE_ATAQUE;
		}
};

class Escorpiao : public Monstro {
	private:

	public:
    	Escorpiao() : Monstro("Escorpião", ESCORPIAO_VIDA, ESCORPIAO_DEFESA, ESCORPIAO_ATAQUE){}
		
		int atacar() override{
			return ESCORPIAO_ATAQUE;
		}
};

class JogoRPG {
	private:
		Personagem *jogador;
		vector<Monstro *> monstros;

		int monstroAtual = 0;

		Secoes mapa[4];
		
	public:
		JogoRPG() {
			this->iniciaJogo();
			this->generateMap();
			this->mainLoop();
		}

		~JogoRPG() { 
			delete this->jogador; 

			for (int monstro = 0; monstro < this->monstros.size(); monstro++) {
				delete this->monstros[monstro];
			}

			this->monstros.clear();
		}

		void iniciaJogo() {
			// Obtendo o nome do jogador.
			string nomeJogador = getNomeJogador();

			// Exibindo a mensagem de início do jogo. 
			printBoasVindas(nomeJogador);

			// Obtendo a classe do jogador.
			int classeAtual = getClasseJogador();

			// Limpando o terminal.
			limparTerminal();
			
			cout << "Classe escolhida: " << CLASSES[classeAtual] << "!" << endl;

			// Instânciando o personagem do jogador
			this->jogador = this->criarPersonagem(nomeJogador, Classe(classeAtual));
			this->monstros = this->GeraMonstros();

			// Exibindo a história do jogo.
			printInicio();
			
			// Exibindo os atributos da classe escolhida
			jogador->printDetalhesClasse();
		}

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
					return new Personagem(nome, 0, 0, 0, 0);
					break;
			}
		}

		// O objetivo é ser aleatório, mas por enquanto, vamos deixar fixo.
		void generateMap() {
			this->mapa[0] = BATALHA;
			this->mapa[1] = BATALHA;
			this->mapa[2] = LOOTBUG;
			this->mapa[3] = EXTRATOR;
		}
		
		vector<Monstro *> GeraMonstros() {
			int quantidadeMonstros = gerarNumeroAleatorio(3, 5);

			vector<Monstro *> monstros = {};
				
			for(int i=0; i<quantidadeMonstros; i++) {
				int IndiceMonstro = gerarNumeroAleatorio(0, 2);
				
				switch(IndiceMonstro) {
					case ARANHA:
						monstros.push_back(new Aranha());	
					case ARANHA_GRANDE:
						monstros.push_back(new AranhaGrande());	
					case ESCORPIAO:
						monstros.push_back(new Escorpiao());
				}			
			}

			return monstros;
		}

		// Inicio combate, (rascunho)
		void Batalha() {
			// Obtendo o monstro que o jogador irá enfrentar.
			Monstro* monstro = this->monstros[monstroAtual];
			
			cout << "Que a batalha se inicie!" << endl;
			while (jogador->VerificaVivo() == true && monstro->VerificaVivo() == true) {
				cout << "É a sua vez!" << endl;

				int danoJogador = jogador->atacar();
				monstro->tomarDano(danoJogador);

				cout << "É a vez do monstro!" << endl;

				// O monstro ainda está vivo, então ele pode tentar atacar
				if (monstro->VerificaVivo())  {
					int danoMonstro = monstro->atacar();
					jogador->tomarDano(danoMonstro);
				}
			}

			if (jogador->VerificaVivo() == true) {
				cout << "Você venceu!" << endl;
			} else {
				cout << "Você perdeu!" << endl;
			}
		}

		void mainLoop() {
			for (int secaoAtual = 0; secaoAtual < 4; secaoAtual++) {
				switch (this->mapa[secaoAtual]) {
					case BATALHA:
						cout << "Batalha!" << endl;
						break;
					
					case LOOTBUG:
						cout << "Lootbug!" << endl;
						break;
					
					case EXTRATOR:
						cout << "Extrator!" << endl;
						break;
					
					default:
						cout << "Erro no programa, seção indefinida!" << endl;
						exit(1);
						break;
				}
			}
		}
};
