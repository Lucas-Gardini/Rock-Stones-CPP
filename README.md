# Deep Rock Galactic - Terminal Edition

## Atenção!

O projeto foi desenvolvido e testado em um ambiente *WINDOWS*, portanto, não há garantias de que o projeto irá funcionar em outros sistemas operacionais.

## Introdução

O projeto foi baseado no jogo `Deep Rock Galactic`, um jogo de tiro em primeira pessoa com elementos de exploração e mineração.

Nosso jogo porém, tem o foco em um combate em turnos com alguns inimigos deste jogo, com o objetivo final de escapar do planeta
com o máximo de recursos possíveis.

## Compilando e executando

Para facilitar a vida dos desenvolvedores JavaScript que desenvolveram o projeto, existe um arquivo package.json na raiz do projeto
com os comandos `start` e `start:linux` que executa o comando de compilação e execução do projeto.

Então, caso tenha o nodejs instalado, simplesmente execute

```bash
npm start

# ou

npm run start:linux
```

Agora, caso esteja sem o nodejs instalado, copie o comando de compilação no arquivo package.json para seu
sistema operacional e execute-o na raiz do projeto.

## Como o projeto foi desenvolvido

O projeto se baseia bastante na orientação a objetos, mas também tem alguns elementos de programação funcional, principalmente nas funções utilitárias.

### Linguagem

O projeto foi desenvolvido em C++.

### Estrutura do projeto

O projeto foi dividido em 3 pastas principais:

- `src`: Contém os arquivos de código fonte do projeto
- `src/modules`: Contém os arquivos de código fonte externos (módulos)
- `src/assets`: Contém os arquivos utilizados pelo projeto

### Módulos

Os módulos utilizados no projeto foram:

- `.env.h`: Arquivo de variáveis de ambiente, contendo variáveis constantes de dano, vida, enums, textos e etc
- `utils.h`: Arquivo de funções utilitárias, contendo funções de leitura de arquivos, de texto, de números e etc
- `classes.h`: Arquivo de classes, contendo as classes do jogo (jogador, inimigo, jogo e etc)
  
### Assets

Dentre os assets do projeto, basicamente temos arquivos de textos contendo os diálogos do jogo, e arquivos de imagens contendo os sprites dos personagens e inimigos.

Utilizamos assim para evitar uma grande quantidade de textos no código fonte, e também para facilitar a manutenção dos textos.

### Código fonte

#### Arquivo main.cpp

Vamos iniciar explicando o arquivo `main.cpp`, que é o arquivo principal do projeto.

É um arquivo bem simples, que contém simplesmente um método que define a saída do terminal como UTF-8 e instância a classe `JogoRPG`, que é responsável por executar nosso jogo.

--------------------

#### Arquivo .env.h

Indo para o arquivo `.env.h`, temos as variáveis de ambiente do projeto.

Dentre elas temos todas as variáveis constantes das classes, como dano, vida, mana e etc.

Temos enums de escolhas, de classes, de inimigos e de eventos.

--------------------

#### Arquivo utils.h

Indo para o arquivo `utils.h`, temos as funções utilitárias do projeto.

Dentre elas temos funções de leitura de arquivos, uma função para escrever no terminal letra por letra, prints de textos, um função de espera do terminal, print de estrutura de tabela, etc.

Recomendamos a leitura do arquivo para entender melhor as funções.

#### Arquivo classes.cpp

Indo para o arquivo `classes.cpp`, temos as classes do projeto.

Dentre elas, as principais são Monstro, Personagem e JogoRPG.

A classe Monstro é responsável por instanciar os inimigos do jogo, e a classe Personagem é responsável por instanciar o jogador.

A classe JogoRPG é responsável por executar o jogo, e é a classe que contém toda a lógica do jogo.

Temos diversas classes que extendem o Personagem, contendo seus próprios atributos, porém, todas elas tem os mesmos métodos, como atacar, defender, usar habilidade e etc.

O mesmo se aplica para os Monstros.

Recomendamos a leitura do arquivo para entender melhor as classes.

## Como jogar

O jogo é bem simples, você escolhe uma classe e de maneira aleatória, um evento acontece ou um inimigo é escolhido para você enfrentar.

Cada classe tem suas próprias habilidades e armas, e cada inimigo tem suas próprias habilidades e fraquezas.

O jogo é baseado em turnos, então você tem um turno para atacar e um turno para se defender, e assim por diante.

Ganha quem conseguir sobreviver a todos os inimigos e conseguir escapar do planeta com o máximo de recursos possíveis.
