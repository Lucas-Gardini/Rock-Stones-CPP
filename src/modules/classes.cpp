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

class Monstro {
	protected:
		string nome;
    	int _HP, _ATQ, _DEF;
		int vidaAtual = 0;
		IndiceMonstros _TIPOMONSTRO;

	public:
    	Monstro(string nome, int ptVida, int ptDef, int ptAtq, IndiceMonstros tipoMonstro): nome(nome), _HP(ptVida), _DEF(ptDef), _ATQ(ptAtq), _TIPOMONSTRO(tipoMonstro) {
			this->vidaAtual = ptVida;
		}

    	bool verificaVivo() {
			if(this->vidaAtual > 0) {
				return true;
			} else {
				return false;
			}
		}

		string getNomeMonstro() {
			return this->nome;
		}

		int getDefesaMonstro() {
			return this->_DEF;
		}

		int* getEstatisticas(bool valoresAtuais = false) {
			int *estatisticas = new int[4];

			if (valoresAtuais)
				estatisticas[0] = this->vidaAtual;
			else
				estatisticas[0] = this->_HP;

			estatisticas[1] = this->_DEF;
			estatisticas[2] = this->_ATQ;

			return estatisticas;
		}

		void printDetalhesMonstro(bool valoresAtuais = false) {
			int* estatisticas = this->getEstatisticas(valoresAtuais);

			vector<string> cabecalho = {"Estatísticas:\n", ""};
			vector<vector<string>> tabela = {
				{"Nome:", this->nome},
				{"Vida:", to_string(estatisticas[0])},
				{"Defesa:", to_string(estatisticas[1])},
				{"Dano de ataque:", to_string(estatisticas[2])},
			};

			delete [] estatisticas;

			printTable(cabecalho, tabela, true);
		}

		void tomarDano(int dano){
			if (dano <= this->_DEF) {
				cout << "O monstro defendeu o ataque!" << endl;
				return;
			}

			this->vidaAtual -= (dano - this->_DEF);
		}

		int atacar(int defesaJogador) {
			int dano = this->_ATQ - defesaJogador;
			cout << "\nO " << COR_VERMELHA << "monstro" << RESET_COR << " causou " << dano << " de dano!" << endl;

			return this->_ATQ;
		}

		void vidaMonstro(){
			int vida = this->vidaAtual < 0 ? 0 : this->vidaAtual;
			cout << "Vida do monstro: " << vida << "/" << this->_HP << endl;
		}

		IndiceMonstros getTipoMonstro() {
			return _TIPOMONSTRO;
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

class Personagem {
	protected:
		// Atributos inicias
		string nome;
		int _HP, _ATQ, _DEF, _ESP, _CUSTO_MANA;
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
		Personagem(string nome, int ptVida, int ptDef, int ptAtq, int ptAtqEsp, int mana): nome(nome), _HP(ptVida), _ATQ(ptAtq), _ESP(ptAtqEsp) ,_DEF(ptDef), _CUSTO_MANA(mana) {
			this->manaAtual = mana;
			this->vidaAtual = ptVida;
		}

		void recebeMinerios(int minerio, int quantidade) {
			this->minerios[minerio][1] += quantidade;
		}

		int getDefesaPersonagem() {
			return this->_DEF;
		}

		bool verificaVivo() {
			if(this->_HP > 0) {
				return true;
			} else {
				return false;
			}
		}

		bool VerificaMana(){
			if(this->manaAtual >= this->_CUSTO_MANA) {
				return true;
			} else {
				this->manaAtual += (this->_CUSTO_MANA / 4);
				return false;
			}
		}

		int* getEstatisticas(bool valoresAtuais = false) {
			int *estatisticas = new int[5];

			if (valoresAtuais)
				estatisticas[0] = this->vidaAtual;
			else
				estatisticas[0] = this->_HP;

			estatisticas[1] = this->_DEF;
			estatisticas[2] = this->_ATQ;
			estatisticas[3] = this->_ESP;
			estatisticas[4] = this->grauFerimento;

			return estatisticas;
		}

		void printDetalhesClasse(bool valoresAtuais = false) {
			int* estatisticas = this->getEstatisticas(valoresAtuais);

			vector<string> cabecalho = {"Estatísticas:", "     ", " Minérios:", "\n"};
			vector<vector<string>> tabela = {
				{"Nome:", this->nome, "Ouro: ", to_string(this->minerios[OURO][1])},
				{"Vida:", to_string(estatisticas[0]), "Morkita: ", to_string(this->minerios[MORKITA][1])},
				{"Defesa:", to_string(estatisticas[1]), "Dystrum: ", to_string(this->minerios[DYSTRUM][1])},
				{"Dano de ataque:", to_string(estatisticas[2]), "Nitra: ", to_string(this->minerios[NITRA][1])},
				{"Dano do especial:", to_string(estatisticas[3]), "", ""},
				{"Grau de sangramento: ", to_string(estatisticas[4]), "", ""}
			};

			delete [] estatisticas;

			printTable(cabecalho, tabela, true);
		}

		void solicitaCapsula() {
			if (this->minerios[NITRA][1] >= CUSTO_CAPSULA) {
				this->vidaAtual += int((this->_HP / 2));

				if (this->vidaAtual > this->_HP) this->vidaAtual = this->_HP;

				this->grauFerimento = 0;
				cout << "Você se curou em " << int((this->_HP / 2)) << " pontos de vida e curou suas feridas!" << endl;
			}
			else{
				cout << "Você não possue nitra suficiente para chamar uma capsula de cura." << endl;
			}
		}

		void tomarDano(int dano){
			if (dano <= this->_DEF) {
				cout << "Você defendeu o ataque!" << endl;
				return;
			}

			this->vidaAtual -= (dano - this->_DEF);
		}

		void aumentaFerimento() {
			cout << "Você foi ferido!" << endl;

			this->grauFerimento += 1;
		}

		int danoFerimento() {
			return DANO_SANGRAMENTO * this->grauFerimento;
		}

		void sangrar(int dano) {
			if (this->grauFerimento == 0) return;

			cout << "\nVocê está sangrando!" << endl;
			cout << "Você recebeu " << dano << " de dano!\n" << endl;
			this->vidaAtual -= dano;

			if (this->vidaAtual <= 0) {
				this->morrer();
			}
		}

		int atacar(Monstro *monstro) {
			int escolha = NAO_ESPECIFICADO;

			while(escolha == NAO_ESPECIFICADO){
				printOpcoes();

				cin >> escolha;

				if(escolha != NORMAL && escolha != ESPECIAL && escolha != INFORMACOES_PLAYER && escolha != INFORMACOES_MONSTRO && escolha != CAPSULA_CURA){
					cout << "Escolha inválida, por favor escolha entre ataque NORMAL ou ESPECIAL!!" << endl;
					escolha = NAO_ESPECIFICADO;
				}

				else if(escolha == INFORMACOES_PLAYER){
					limparTerminal();
					printDetalhesClasse(true);
					escolha = NAO_ESPECIFICADO;
				}

				else if (escolha == INFORMACOES_MONSTRO) {
					limparTerminal();
					monstro->printDetalhesMonstro(true);
					escolha = NAO_ESPECIFICADO;
				}

				else if (escolha == CAPSULA_CURA) {
					limparTerminal();
					solicitaCapsula();
					escolha = NAO_ESPECIFICADO;
				}

				cout << endl;
			}

			int dano = this->_ATQ - monstro->getDefesaMonstro();
			bool manaSuficiente = this->VerificaMana();
			if(escolha != Escolha::NORMAL) {
				if(manaSuficiente){
					int ran = gerarNumeroAleatorio(0, 4);

					dano = this->_ESP - monstro->getDefesaMonstro();

					if(ran == 2){
						cout << "ATAQUE CRÍTICO!\n";
						dano = this->_ESP * 2;
					}

					this->manaAtual -= this->_CUSTO_MANA;

					cout << COR_VERDE << "\nVocê " << RESET_COR << "causou " << dano << " de dano!" << endl;
					return this->_ESP;
				} else {
					cout << "O ataque especial não está pronto! Você trocou para o ataque normal!" << endl;
				}
			}

			cout << COR_VERDE << "\nVocê " << RESET_COR << "causou " << dano << " de dano!" << endl;
			return this->_ATQ;
		}

		void vidaPersonagem(){
			int vida = this->vidaAtual < 0 ? 0 : this->vidaAtual;
			cout << "Sua vida: " << vida << "/" << this->_HP << endl;
		}

		void morrer() {
			cout << "Você morreu!" << endl;
		}
};

class Batedor : public Personagem {
  	private:
   		int granadaIncendiaria = BATEDOR_ATQ_ESPECIAL;

  	public:
		Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE, BATEDOR_ATQ_ESPECIAL, BATEDOR_MANA){}
};

class Guerreiro : public Personagem {
	private:
   		int miniGun = GUERREIRO_ATQ_ESPECIAL;
  	public:
    	Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE, GUERREIRO_ATQ_ESPECIAL, GUERREIRO_MANA){}
};

class Engenheiro : public Personagem {
  	private:
   		int sentryGun = ENGENHEIRO_ATQ_ESPECIAL;
  	public:
    	Engenheiro(string nome) : Personagem(nome, ENGENHEIRO_VIDA, ENGENHEIRO_DEFESA, ENGENHEIRO_ATAQUE, ENGENHEIRO_ATQ_ESPECIAL, ENGENHEIRO_MANA){}
};

class Escavador : public Personagem {
	private:
   		int lancaChamas = ESCAVADOR_ATQ_ESPECIAL;
  	public:
    	Escavador(string nome) : Personagem(nome, ESCAVADOR_VIDA, ESCAVADOR_DEFESA, ESCAVADOR_ATAQUE, ESCAVADOR_ATQ_ESPECIAL, ESCAVADOR_MANA){}
};

class Medico : public Personagem {
	private:
   		int kitBomba = MEDICO_ATQ_ESPECIAL;
  	public:
    	Medico(string nome) : Personagem(nome, MEDICO_VIDA, MEDICO_DEFESA, MEDICO_ATAQUE, MEDICO_ATQ_ESPECIAL, MEDICO_MANA){}
};


class JogoRPG {
	private:
		Personagem *jogador;
		vector<Monstro *> monstros = {};

		int monstroAtual = 0;

		Secoes mapa[6]; // 6 é o máximo

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
					return new Personagem(nome, 0, 0, 0, 0, 0);
					break;
			}
		}

		// O objetivo é ser aleatório, mas por enquanto, vamos deixar fixo.
		void geraMapa() {
			for (int i = 0; i < this->monstros.size(); i++) {
				this->mapa[i] = BATALHA;
			}
			
			this->mapa[this->monstros.size()] = EXTRATOR;
		}

		void GeraMonstros() {
			int quantidadeMonstros = gerarNumeroAleatorio(3, 5);

			for(int i = 0; i < quantidadeMonstros; i++) {
				int IndiceMonstro = gerarNumeroAleatorio(0, 2);

				switch(IndiceMonstro) {
					case ARANHA:
						this->monstros.push_back(new Aranha());
						break;
					case ARANHA_GRANDE:
						this->monstros.push_back(new AranhaGrande());
						break;
					case ESCORPIAO:
						this->monstros.push_back(new Escorpiao());
						break;
				}
			}
		}

		void secaoBatalha() {
			// Obtendo o monstro que o jogador irá enfrentar.
			Monstro* monstro = this->monstros[monstroAtual];
			printEncontroMonstro(monstro->getNomeMonstro(), monstroAtual != 0);

			if (monstro->getTipoMonstro() == IndiceMonstros::ARANHA) cout << lerArquivo("aranha.txt");
			else if (monstro->getTipoMonstro() == IndiceMonstros::ARANHA_GRANDE) cout << lerArquivo("aranha_grande.txt");
			else cout << lerArquivo("escorpiao.txt");

			dormir(2);
			while (jogador->verificaVivo() == true && monstro->verificaVivo() == true) {
				cout << "\nÉ a sua vez!" << endl;
				dormir(1);

				// Monstro é passado por referência somente para exibir seus atributos caso o jogador queira
				int danoJogador = jogador->atacar(monstro);
				monstro->tomarDano(danoJogador);
				monstro->vidaMonstro();

				dormir(1);

				// O monstro ainda está vivo, então ele pode tentar atacar
				if (monstro->verificaVivo())  {
					// cout << "\nÉ a vez do monstro!" << endl;

					int danoMonstro = monstro->atacar(jogador->getDefesaPersonagem());
					jogador->tomarDano(danoMonstro);

					bool ferir = false;
					int chanceFerir = 0;
					switch(monstro->getTipoMonstro()) {
						case ARANHA:
							chanceFerir = gerarNumeroAleatorio(0, 6);
							if(chanceFerir == 3) { ferir = true; }
							break;

						case ARANHA_GRANDE:
							chanceFerir = gerarNumeroAleatorio(0, 4);
							if(chanceFerir == 2) { ferir = true; }
							break;


						case ESCORPIAO:
							chanceFerir = gerarNumeroAleatorio(0, 1);
							if(chanceFerir == 1) { ferir = true; }
							break;

					}

					if(ferir) {
						jogador->aumentaFerimento();
					}
				}

				// sangramento
				jogador->sangrar(jogador->danoFerimento());

				jogador->vidaPersonagem();

				pressioneUmaTecla();
			}

			if (jogador->verificaVivo() == true) {
				cout << "Você venceu!" << endl;

				dormir(2);

				this->monstroAtual = this->monstroAtual + 1;

				int* minerios = droparMinerios();

				for (int minerio = 0; minerio < 4; minerio++) {
					this->jogador->recebeMinerios(minerio, minerios[minerio]);
				}

				cout << "Você recebeu:" << endl;
				for (int minerio = 0; minerio < 4; minerio++) {
					cout << MINERIOS[minerio] << ": " << minerios[minerio] << endl;
				}

				delete [] minerios;

				cout << ".";
				dormir(1);
				cout << ".";
				dormir(1);
				cout << "." << endl;
			} else {
				cout << "Você perdeu!" << endl;
			}
		}

		void secaoExtrator() {
			int botao;
			limparTerminal();
			jogador->printDetalhesClasse(true);

			maquinaDeEscrever(lerArquivo("secao_extrator.txt"), false);

			pressioneUmaTecla(true);

			while(true){
				cout << "Digite um número para a combinação: ";
				cin >> botao

				// if(){
					
				// }
				// else{

				// }
			}
		}

	public:
		JogoRPG() {
			this->iniciaJogo();

			cout << lerArquivo("personagem.txt");
			dormir(1);

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
			this->GeraMonstros();

			cout << this->monstros.size() << " monstros estão no seu caminho!\n" << endl;

			this->geraMapa();

			// Exibindo a história do jogo.
			printInicio();

			// // Exibindo os atributos da classe escolhida
			// jogador->printDetalhesClasse();
		}

		void mainLoop() {
			for (int secaoAtual = 0; secaoAtual < this->monstros.size() + 1; secaoAtual++) {
				switch (this->mapa[secaoAtual]) {
					case BATALHA:
						this->secaoBatalha();
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

			limparTerminal();
			cout << "Fim de jogo!" << endl;

			this->jogador->printDetalhesClasse(true);

			pressioneUmaTecla();

			limparTerminal();

			cout << lerArquivo("fuga_do_planeta.txt");
		}
};
