#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

#include ".env.h"
#include "utils.h"

using namespace std;

// Classe genérica Monstro, responsável por ter os atributos e ações dos inimigos do jogador.
class Monstro {
	protected:
		string nome;
    	int _HP, _ATQ, _DEF;
		IndiceMonstros _TIPOMONSTRO;
		int vidaAtual = 0;

	public:
    	Monstro(string nome, int ptVida, int ptDef, int ptAtq, IndiceMonstros tipoMonstro): nome(nome), _HP(ptVida), _DEF(ptDef), _ATQ(ptAtq), _TIPOMONSTRO(tipoMonstro) {
			this->vidaAtual = ptVida;
		}

		// Função que verifica se o monstro está vivo, comparando se sua vida é maior que 0.
    	bool verificaVivo() {
			if(this->vidaAtual > 0) {
				return true;
			} else {
				return false;
			}
		}

		// Função getter para o nome do monstro.
		string getNomeMonstro() {
			return this->nome;
		}

		// Função getter para a defesa do monstro.
		int getDefesaMonstro() {
			return this->_DEF;
		}

		// Função getter para o tipo do monstro.
		IndiceMonstros getTipoMonstro() {
			return _TIPOMONSTRO;
		}

		// Função getter que retorna um vetor com as estatísticas do monstro.
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

		// Função que imprime as estatísticas do monstro.
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

		// Função que faz o monstro tomar dano.
		void tomarDano(int dano){
			if (dano <= this->_DEF) {
				cout << "O monstro defendeu o ataque!" << endl;
				return;
			}

			this->vidaAtual -= (dano - this->_DEF);
		}

		// Função que faz o monstro atacar o jogador.
		int atacar(int defesaJogador) {
			int dano = this->_ATQ - defesaJogador;
			cout << "\nO " << COR_VERMELHA << "monstro" << RESET_COR << " causou " << dano << " de dano!" << endl;

			return this->_ATQ;
		}

		// Função que imprime a vida do monstro.
		void vidaMonstro(){
			int vida = this->vidaAtual < 0 ? 0 : this->vidaAtual;
			cout << "Vida do monstro: " << vida << "/" << this->_HP << endl;
		}
};

class Aranha : public Monstro {
	public:
		Aranha() : Monstro("Aranha",  ARANHA_VIDA, ARANHA_DEFESA, ARANHA_ATAQUE, IndiceMonstros::ARANHA){}
};

class AranhaGrande : public Monstro {
  	public:
    	AranhaGrande() : Monstro("Aranha Grande", ARANHA_GRANDE_VIDA, ARANHA_GRANDE_DEFESA, ARANHA_GRANDE_ATAQUE, IndiceMonstros::ARANHA_GRANDE){}
};

class Escorpiao : public Monstro {
	public:
    	Escorpiao() : Monstro("Escorpião", ESCORPIAO_VIDA, ESCORPIAO_DEFESA, ESCORPIAO_ATAQUE, IndiceMonstros::ESCORPIAO){}
};

// Classe genérica Personagem, responsável por ter os atributos e ações do jogador.
class Personagem {
	protected:
		// Atributos inicias
		string nome;
		int _HP, _ATQ, _DEF, _ESP, _CUSTO_MANA;
		int vidaAtual = 0;
		int manaAtual = 0;
		int grauFerimento = 0;

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

		// Função responsável por dar ao jogador os minérios que ele dropou do monstro.
		void recebeMinerios(int minerio, int quantidade) {
			this->minerios[minerio][1] += quantidade;
		}

		// Função getter para a defesa do jogador.
		int getDefesaPersonagem() {
			return this->_DEF;
		}

		// Função que verifica se o jogador está vivo, comparando se sua vida é maior que 0.
		bool verificaVivo() {
			if(this->vidaAtual > 0) {
				return true;
			} else {
				return false;
			}
		}

		// Função que verifica se o jogador tem mana suficiente para executar um ataque especial, comparando se sua mana atual é maior que o custo.
		// Caso não seja, o jogador recebe 1/4 do custo de mana.
		bool VerificaMana(){
			if(this->manaAtual >= this->_CUSTO_MANA) {
				return true;
			} else {
				this->manaAtual += (this->_CUSTO_MANA / 4);
				return false;
			}
		}

		// Função getter que retorna um vetor com as estatísticas do jogador.
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

		// Função que imprime as estatísticas do jogador e seus minérios.
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

		// Função responsável por solicitar uma cápsula de cura ao jogador, ao custo de NITRA.
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

		// Função que faz o jogador tomar dano.
		void tomarDano(int dano){
			if (dano <= this->_DEF) {
				cout << "Você defendeu o ataque!" << endl;
				return;
			}

			this->vidaAtual -= (dano - this->_DEF);
		}

		// Função que faz o jogador ser ferido pelo monstro (sangramento).
		void aumentaFerimento() {
			cout << "Você foi ferido!" << endl;

			this->grauFerimento += 1;
		}

		// Função que calcula o dano do sangramento.
		int danoFerimento() {
			return DANO_SANGRAMENTO * this->grauFerimento;
		}

		// Função que faz o jogador sangrar, caso ele esteja ferido.
		void sangrar(int dano) {
			if (this->grauFerimento == 0) return;

			cout << "\nVocê está sangrando!" << endl;
			cout << "Você recebeu " << dano << " de dano!\n" << endl;
			this->vidaAtual -= dano;

			if (this->vidaAtual <= 0) {
				this->morrer();
			}
		}

		// Função que faz o jogador atacar o monstro.
		int atacar(Monstro *monstro) {
			int escolha = NAO_ESPECIFICADO;

			// Mostra as opções e obtém a escolha do jogador
			while(escolha == NAO_ESPECIFICADO){
				printOpcoes();

				cin >> escolha;

				// Caso a escolha do jogador não seja nenhuma das opções, ele é solicitado a escolher novamente.
				if(escolha != NORMAL && escolha != ESPECIAL && escolha != INFORMACOES_PLAYER && escolha != INFORMACOES_MONSTRO && escolha != CAPSULA_CURA){
					cout << "Escolha inválida, por favor escolha entre ataque NORMAL ou ESPECIAL!!" << endl;
					escolha = NAO_ESPECIFICADO;
				}

				// Caso a escolha seja INFORMACOES_PLAYER, mostramos os atributos do jogador e resetamos o loop.
				else if(escolha == INFORMACOES_PLAYER){
					limparTerminal();
					printDetalhesClasse(true);
					escolha = NAO_ESPECIFICADO;
				}

				// Caso a escolha seja INFORMACOES_MONSTRO, mostramos os atributos do monstro e resetamos o loop.
				else if (escolha == INFORMACOES_MONSTRO) {
					limparTerminal();
					monstro->printDetalhesMonstro(true);
					escolha = NAO_ESPECIFICADO;
				}

				// Caso a escolha seja CAPSULA_CURA, tentamos curar o jogador e resetamos o loop.
				else if (escolha == CAPSULA_CURA) {
					limparTerminal();
					solicitaCapsula();
					escolha = NAO_ESPECIFICADO;
				}

				cout << endl;
			}

			// Por fim, calculamos o dano de ataque do jogador, verificamos sua mana e verificamos o ataque escolhido.
			int dano = this->_ATQ - monstro->getDefesaMonstro();
			bool manaSuficiente = this->VerificaMana();

			// Se for diferente de normal, quer dizer que é o especial
			if(escolha != Escolha::NORMAL) {
				if(manaSuficiente){
					// O número aleatório aqui é para simular um ataque crítico
					int ran = gerarNumeroAleatorio(0, 4);

					// O dano é composto pelo especial menos a defesa do monstro
					dano = this->_ESP - monstro->getDefesaMonstro();

					// Se o número aleatório for 2, o ataque é crítico e é multiplicado por 2
					if(ran == 2){
						cout << "ATAQUE CRÍTICO!\n";
						dano = this->_ESP * 2;
					}

					// A mana é diminuída pelo custo do especial
					this->manaAtual -= this->_CUSTO_MANA;

					// O dano é mostrado na tela
					cout << COR_VERDE << "\nVocê " << RESET_COR << "causou " << dano << " de dano!" << endl;
					return this->_ESP;
				} else {
					cout << "O ataque especial não está pronto! Você trocou para o ataque normal!" << endl;
				}
			}

			cout << COR_VERDE << "\nVocê " << RESET_COR << "causou " << dano << " de dano!" << endl;
			return this->_ATQ;
		}

		// Função que imprime a vida do jogador.
		void vidaPersonagem(){
			int vida = this->vidaAtual < 0 ? 0 : this->vidaAtual;
			cout << "Sua vida: " << vida << "/" << this->_HP << endl;
		}

		// Função que imprime a morte do jogador.
		void morrer() {
			cout << "Você morreu!" << endl;
		}
};

class Batedor : public Personagem {
  	public:
		Batedor(string nome) : Personagem(nome, BATEDOR_VIDA, BATEDOR_DEFESA, BATEDOR_ATAQUE, BATEDOR_ATQ_ESPECIAL, BATEDOR_MANA){}
};

class Guerreiro : public Personagem {
  	public:
    	Guerreiro(string nome) : Personagem(nome, GUERREIRO_VIDA, GUERREIRO_DEFESA, GUERREIRO_ATAQUE, GUERREIRO_ATQ_ESPECIAL, GUERREIRO_MANA){}
};

class Engenheiro : public Personagem {
  	public:
    	Engenheiro(string nome) : Personagem(nome, ENGENHEIRO_VIDA, ENGENHEIRO_DEFESA, ENGENHEIRO_ATAQUE, ENGENHEIRO_ATQ_ESPECIAL, ENGENHEIRO_MANA){}
};

class Escavador : public Personagem {
  	public:
    	Escavador(string nome) : Personagem(nome, ESCAVADOR_VIDA, ESCAVADOR_DEFESA, ESCAVADOR_ATAQUE, ESCAVADOR_ATQ_ESPECIAL, ESCAVADOR_MANA){}
};

class Medico : public Personagem {
  	public:
    	Medico(string nome) : Personagem(nome, MEDICO_VIDA, MEDICO_DEFESA, MEDICO_ATAQUE, MEDICO_ATQ_ESPECIAL, MEDICO_MANA){}
};

class JogoRPG {
	private:
		// Ponteiro para o jogador
		Personagem *jogador;

		// Vetor de ponteiros para os monstros
		vector<Monstro *> monstros = {};

		// Índice do monstro atual
		int monstroAtual = 0;

		// Vetor de seções do mapa
		Secoes mapa[6]; // 6 é o máximo

		// Função que gera a classe do jogador
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

		// Função responsável por gerar o mapa do jogo.
		void geraMapa() {
			for (int i = 0; i < this->monstros.size(); i++) {
				this->mapa[i] = BATALHA;
			}
			
			this->mapa[this->monstros.size()] = EXTRATOR;
		}

		// Função responsável por gerar os monstros do jogo.
		void geraMonstros() {
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

		// Função responsável por executar a seção de batalha, onde a luta entre jogador e monstro acontece.
		void secaoBatalha() {

			// Obtendo o monstro que o jogador irá enfrentar.
			Monstro* monstro = this->monstros[monstroAtual];
			printEncontroMonstro(monstro->getNomeMonstro(), monstroAtual != 0);

			// Mostra o desenho do monstro
			if (monstro->getTipoMonstro() == IndiceMonstros::ARANHA) cout << lerArquivo("aranha.txt");
			else if (monstro->getTipoMonstro() == IndiceMonstros::ARANHA_GRANDE) cout << lerArquivo("aranha_grande.txt");
			else cout << lerArquivo("escorpiao.txt");

			// Aguarda 2 segundos e inicia a batalha
			dormir(2);
			while (jogador->verificaVivo() == true && monstro->verificaVivo() == true) {
				cout << "\nÉ a sua vez!" << endl;
				dormir(1);

				// Monstro é passado por referência somente para exibir seus atributos caso o jogador queira
				int danoJogador = jogador->atacar(monstro);

				// O monstro toma dano
				monstro->tomarDano(danoJogador);
				monstro->vidaMonstro();

				dormir(1);

				// O monstro ainda está vivo, então ele pode tentar atacar
				if (monstro->verificaVivo())  {
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
				cout << "Você morreu!" << endl;
                return;
            }
        }

		// Seção responsável por executar o extrator, onde o jogador deve digitar uma combinação de botões para conseguir escapar.
		void secaoExtrator() {
			int botao;
			limparTerminal();
			jogador->printDetalhesClasse(true);

			maquinaDeEscrever(lerArquivo("secao_extrator.txt"), false);

			pressioneUmaTecla(true);

			// while(true){
			// 	cout << "Digite um número para a combinação: ";
			// 	cin >> botao

			// 	// if(){
					
			// 	// }
			// 	// else{

			// 	// }
			// }
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
			this->geraMonstros();

			cout << this->monstros.size() << " monstros estão no seu caminho!\n" << endl;

			this->geraMapa();

			// Exibindo a história do jogo.
			printInicio();

			// // Exibindo os atributos da classe escolhida
			// jogador->printDetalhesClasse();
		}

		void mainLoop() {
			// Loop das seções do mapa
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
