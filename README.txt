Integrantes do Grupo: Pedro Mariano e Arthur Vinícius

Esse é uma simulação do jogo Metal Gear Solid em ASCII.

O jogo começa com um menu que exige uma escolha.
(n) para começar o jogo
(r) para sair

se for precionado (r):
o jogo pergunta se realmente deseja sair.
se sim a aplicação finaliza.
se não retorna pra tela inicial do menu.

se for precionado (n):
Algumas variaveis iniciais são inicializadas 
o jogo pede o nome do jogador, no qual será gravado apenas os 3 primeiros caracteres
depois disso se le o mapa o jogo imprime os personagens e os itens e começa um loop
que inicia o jogo.

O jogador pode andar para os 4 lados:
pra cima
pra baixo 
pra direita
pra esquerda

os inimigos andam de forma semi-aleatória

e quando o jogador entra no campo de visão do inimigo ou encosta nele ele morre e volta para o inicio
se o jogador perder todas as vidas ele morre e vai pro menu inicial

se o jogador pegar a chave, aparece a saida, que se o jogador chegar ate ela ele vence o jogo e volta para o menu inicial 

OBS:Não foram implementadas tudo o que foi pedido no jogo, há bugs em relação ao dardo e quanto ao tempo de parada dos inimigos, não foi implementado o sistema de pontos do jogo da maneira como deveria.

Para compilar o jogo no linux basta digitar make game na pasta src e depois executar o jogo, é necessario o uso da biblioteca ncurses e das bibliotecas padrão da linguagem c.
a biblioteca ncurses esta disponivel na pasta libs para instalar.







