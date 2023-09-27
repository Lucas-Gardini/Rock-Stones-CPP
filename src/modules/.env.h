#ifndef ENV_H
#define ENV_H

#include <string>

enum Classe {
	BATEDOR,
	GUERREIRO,
	ENGENHEIRO,
	ESCAVADOR,
	MEDICO
};

const std::string CLASSES[5] = {"Batedor", "Guerreiro", "Engenheiro", "Escavador", "Medico"};

enum Debuffs {
	SANGRAMENTO,
	ENVENENAMENTO,
};

const std::string DEBUFFS[2] = {"Sangramento", "Envenenado"};

enum Secoes {
	SECAO_INDEFINIDA,
	BATALHA,
	LOOTBUG,
	EXTRATOR
};

const std::string SECOES[4] = {"Seção Indefinida", "Batalha", "Lootbug", "Extrator"};

enum Minerios {
	OURO,
	MORKITA,
	DYSTRUM,
	NITRA
};

const std::string MINERIOS[4] = {"Ouro", "Morkita", "Dystrum", "Nitra"};

enum IndiceMonstros {
	ARANHA,
	ARANHA_GRANDE,
	ESCORPIAO
};

const int CUSTO_CAPSULA = 100;
const int CURA_CAPSULA = 20;

const int MINIMO_SANGRAMENTO = 2;
const int MAXIMO_SANGRAMENTO = 6;
const int DANO_SANGRAMENTO = 3;

const int BATEDOR_VIDA = 60;
const int BATEDOR_ATAQUE = 20;
const int BATEDOR_DEFESA = 0;
const int BATEDOR_ATQ_ESPECIAL = 40;
const int BATEDOR_CUSTO_ESPECIAL = 100;
const int BATEDOR_MANA = 200;

const int GUERREIRO_VIDA = 100;
const int GUERREIRO_ATAQUE = 27;
const int GUERREIRO_DEFESA = 7;
const int GUERREIRO_ATQ_ESPECIAL = 35;
const int GUERREIRO_CUSTO_ESPECIAL = 100;
const int GUERREIRO_MANA = 200;

const int ENGENHEIRO_VIDA = 70;
const int ENGENHEIRO_ATAQUE = 25;
const int ENGENHEIRO_DEFESA = 3;
const int ENGENHEIRO_ATQ_ESPECIAL = 35;
const int ENGENHEIRO_CUSTO_ESPECIAL = 100;
const int ENGENHEIRO_MANA = 200;

const int ESCAVADOR_VIDA = 80;
const int ESCAVADOR_ATAQUE = 20;
const int ESCAVADOR_DEFESA = 3;
const int ESCAVADOR_ATQ_ESPECIAL = 32;
const int ESCAVADOR_CUSTO_ESPECIAL = 100;
const int ESCAVADOR_MANA = 200;

const int MEDICO_VIDA = 60;
const int MEDICO_ATAQUE = 20;
const int MEDICO_DEFESA = 4;
const int MEDICO_ATQ_ESPECIAL = 30;
const int MEDICO_CUSTO_ESPECIAL = 100;
const int MEDICO_MANA = 200;

const int ARANHA_VIDA = 20;
const int ARANHA_ATAQUE = 7;
const int ARANHA_DEFESA = 0;

const int ARANHA_GRANDE_VIDA = 30;
const int ARANHA_GRANDE_ATAQUE = 10;
const int ARANHA_GRANDE_DEFESA = 3;

const int ESCORPIAO_VIDA = 23;
const int ESCORPIAO_ATAQUE = 13;
const int ESCORPIAO_DEFESA = 2;

#endif
