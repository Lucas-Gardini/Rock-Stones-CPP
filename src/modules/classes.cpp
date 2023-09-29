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
		int _HP, _ATQ, _DEF, _ESP, _MANA, _CUSTO_MANA;
		int vidaAtual = 0;
		int manaAtual = 0;
		int grauFerimento = 0;

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

		int danoFerimento() {
			return 1 * this->grauFerimento;
			// 1 pois o dano so sangramento não esta definido
		}

		void aumentaFerimento(int ferida) {
			this->grauFerimento += ferida;
		}

		int* getEstatisticas(bool valoresAtuais = false) {
			int *estatisticas = new int[4];
			
			if (valoresAtuais)
				estatisticas[0] = this->vidaAtual;
			else
				estatisticas[0] = this->_HP;

			estatisticas[1] = this->_DEF;
			estatisticas[2] = this->_ATQ;
			estatisticas[3] = this->_ESP;

			return estatisticas;
		}

		void printDetalhesClasse(bool valoresAtuais = false) {
			int* estatisticas = this->getEstatisticas(valoresAtuais);

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

		void sangrar(int dano) {
			this->vidaAtual -= dano;
		}

		int atacar() {
			int escolha = NAO_ESPECIFICADO;
			
			while(escolha == NAO_ESPECIFICADO){
				printOpcoes();

				cin >> escolha;

				if(escolha != NORMAL && escolha != ESPECAL){
					cout << "Escolha inválida, por favor escolha entre ataque NORMAL ou ESPECIAL!!" << endl;
					escolha = NAO_ESPECIFICADO;
				}

				if(escolha == INFORMACOES){
					printDetalhesClasse(true);
				}
			}

			if(escolha == Escolha::NORMAL){
				cout << "Você atacou!" << endl;
				return this->_ATQ;
			} else {
				if(this->manaAtual >= this->_CUSTO_MANA){
					cout << "Você usou o ataque especial!";
				
					int ran = gerarNumeroAleatorio(0, 4);

					if(ran == 2){
						cout << "ATAQUE CRÍTICO!";
						this->manaAtual -= this->_CUSTO_MANA;
						return this->_ESP * 2;
					}

					this->manaAtual -= this->_CUSTO_MANA;

					return this->_ESP;
				} else {
					cout << "O ataque especial não está pronto! Você trocou para o ataque normal!" << endl;
					return this->_ATQ;
				}
			}
		}

		void vidaPersonagem(){
			cout << "Sua vida: " << this->_HP;
		}

		void morrer() {
			cout << "Você morreu!" << endl;
		}
};

class Batedor : public Personagem {
  	private:
   		int granadaIncendiaria = BATEDOR_ATQ_ESPECIAL;

  	public:
		Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE, BATEDOR_MANA){}
};

class Guerreiro : public Personagem {
	private:
   		int miniGun = GUERREIRO_ATQ_ESPECIAL;
  	public:
    	Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE, GUERREIRO_MANA){}
};

class Engenheiro : public Personagem {
  	private:
   		int sentryGun = ENGENHEIRO_ATQ_ESPECIAL;
  	public:
    	Engenheiro(string nome) : Personagem(nome, ENGENHEIRO_VIDA, ENGENHEIRO_DEFESA, ENGENHEIRO_ATAQUE, ENGENHEIRO_MANA){}
};

class Escavador : public Personagem {
	private:
   		int lancaChamas = ESCAVADOR_ATQ_ESPECIAL;
  	public:
    	Escavador(string nome) : Personagem(nome, ESCAVADOR_VIDA, ESCAVADOR_DEFESA, ESCAVADOR_ATAQUE, ESCAVADOR_MANA){}
};

class Medico : public Personagem {
	private:
   		int kitBomba = MEDICO_ATQ_ESPECIAL;
  	public:
    	Medico(string nome) : Personagem(nome, MEDICO_VIDA, MEDICO_DEFESA, MEDICO_ATAQUE, MEDICO_MANA){}
};

class Monstro{
	protected:
		string nome;
    	int _HP, _ATQ, _DEF;
		IndiceMonstros _TIPOMONSTRO;
  	public:
    	Monstro(string nome, int ptVida, int ptDef, int ptAtq, IndiceMonstros tipoMonstro): nome(nome), _HP(ptVida), _DEF(ptDef), _ATQ(ptAtq), _TIPOMONSTRO(tipoMonstro) {}

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

		int atacar(){
			cout << "O monstro atacou!" << endl;
			return this->_ATQ;
		}

		void vidaMonstro(){
			cout << "Vida do monstro: " << this->_HP;
		}

		virtual int ferirJogador() {
			return 0;
		}
};

class Aranha : public Monstro {
  	private:
	
	public:
		Aranha() : Monstro("Aranha",  ARANHA_VIDA, ARANHA_DEFESA, ARANHA_ATAQUE, IndiceMonstros::ARANHA){}
};

class AranhaGrande : public Monstro {
	private:

  	public:
    	AranhaGrande() : Monstro("Aranha Grande", ARANHA_GRANDE_VIDA, ARANHA_GRANDE_DEFESA, ARANHA_GRANDE_ATAQUE, IndiceMonstros::ARANHA_GRANDE){}
};

class Escorpiao : public Monstro {
	private:

	public:
    	Escorpiao() : Monstro("Escorpião", ESCORPIAO_VIDA, ESCORPIAO_DEFESA, ESCORPIAO_ATAQUE, IndiceMonstros::ESCORPIAO){}
};

class JogoRPG {
	private:
		Personagem *jogador;
		vector<Monstro *> monstros;

		int monstroAtual = 0;

		Secoes mapa[4];
		
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

		void secaoBatalha() {
			// Obtendo o monstro que o jogador irá enfrentar.
			Monstro* monstro = this->monstros[monstroAtual];

			
			
			cout << "Que a batalha se inicie!" << endl;
			while (jogador->VerificaVivo() == true && monstro->VerificaVivo() == true) {
				cout << "É a sua vez!" << endl;

				int danoJogador = jogador->atacar();
				monstro->tomarDano(danoJogador);
				monstro->vidaMonstro();

				cout << "É a vez do monstro!" << endl;

				// O monstro ainda está vivo, então ele pode tentar atacar
				if (monstro->VerificaVivo())  {
					int danoMonstro = monstro->atacar();
					jogador->tomarDano(danoMonstro);
					jogador->vidaPersonagem();
				}

				// sangramento
				jogador->sangrar(jogador->danoFerimento());
			}

			if (jogador->VerificaVivo() == true) {
				cout << "Você venceu!" << endl;

				this->monstroAtual = this->monstroAtual + 1;
			} else {
				cout << "Você perdeu!" << endl;
			}
		}

		void secaoLootbug() {}
		void secaoExtrator() {}

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

		void mainLoop() {
			for (int secaoAtual = 0; secaoAtual < 4; secaoAtual++) {
				switch (this->mapa[secaoAtual]) {
					case BATALHA:
						this->secaoBatalha();
						break;
					
					case LOOTBUG:
						this->secaoLootbug();
						break;
					
					case EXTRATOR:
						this->secaoExtrator();
						break;
					
					default:
						cout << "Erro no programa, seção indefinida!" << endl;
						exit(1);
						break;
				}
			}
		}
};
