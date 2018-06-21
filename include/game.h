#ifndef _GAME_H_
#define _GAME_H_

#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <ncurses.h> 
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

//Variaveis globais 
int global_contador;
WINDOW *global_janela;

//ENUM 
typedef enum lado {UP = 0 ,DOWN = 1 ,LEFT = 2 ,RIGHT = 3,STOP = 4} ELado;
//Strings fixas
#define TITULO "METAL GEAR"
#define NOVOJOGO "NOVO JOGO (n)"
#define TOP10 "TOP 10 (t)"
#define SAIR "SAIR (r)"
#define MAPA1 "MAPA 1" 
#define ERROR_A "ERROR DE ABERTURA (Pressione qualquer tecla para sair)"
#define DIGITA_NOME "Digite seu nome : (3 Caracteres)"


//Caracteres dos Personagens 
#define PLAYER_UP 'o'  
#define REFEN '0'
#define DARDO '*'
#define ENEMY_UP '^'
#define ENEMY_DOWN 'v'
#define ENEMY_LEFT '<'
#define ENEMY_RIGHT '>'
#define PAREDE '#'
#define CHAVE1 'o'
#define CHAVE2 '='
#define TIROX '-'
#define TIROY '|' 
#define SFECHADA '#'
#define SABERTA 'x'
#define VIDA ACS_DIAMOND
#define DARDOV '|'
#define VISAO '.'

//Quantidades e Tamanhos 
#define QUANTINI 10
#define QUANTREF 10
#define TAMNOME 3
#define CICLO 1000000
#define CAMPVIS 3
//Posicoes do visor
#define VIDAY 1
#define VIDAX 2
#define DARDOY 1
#define DARDOX 13 
#define NOMEY 2
#define NOMEX 2
#define PONTOX LARGURA - 20 
#define PONTOY 1
#define CHAVEX LARGURA - 20 
#define CHAVEY 2
#define INICIOVY 1 
#define INICIOVX 1
#define FIMVY 3
#define FIMVX LARGURA - 1
//Max 
#define VIDAMAX 3
#define DARDOMAX 5
#define PONTOMAX 10000

//Visor strings 
#define VIDAT "VIDA: "
#define DARDOT "DARDOS: "
#define NOMET "NOME: "
#define PONTOT "PONTOS: "

//Posicoes do menu
#define M_TOPOY 2
#define M_TOPO_ABAIXOY 3
#define M_MEIO_ACIMAY 18
#define M_MEIO_MEIOY  20
#define M_MEIO_ABAIXOY 22
#define M_MEIOX LARGURA/2

//Dimensoes do menu 
#define ALTURA 26
#define LARGURA 83
#define XSHIFT 2
#define CSHIFT 1
#define YSHIFT 3

#define URL1 "maps/map1.txt"

//Estruturas 
typedef struct inimigo {
	int posy, posx; // pos x e y do inimigo
	char visao[3][3]; //campo de visao do inimigo
	ELado dir; //direcao do inimigo
	int passos; //quantidade de passos sortiados para ele andar
	bool vivo; // saber se ele esta acordado ou nao 
}Inimigos;

typedef struct player { 
	int posiniy, posinix;
	int posy, posx;
	char nome[3];
	int speed;
	int dardos;
	int vidas;
	bool ganhou;
	bool perdeu;
	int pontos;
	char proximo;
	}Players;

typedef struct chave{
	int posy , posx[2];
	int saidaposy, saidaposx;
	bool tem_chave;
} Chaves;

typedef struct refen {
	int posy, posx;
	
} Refens;
typedef struct mapa {
	Inimigos ini[10];	
	}Mapa;


void Recarrega();

void Message(int y , int x , char mensagem[]);

void LeNome(Players *jogador);

void ImprimeMapa(); 

void LeMapa(Players *jogador, Inimigos *inimigo, Chaves *chave, Refens *refen);

void Cwindow();

bool Realmente();

void Menu();

void NovoJogo();

void ImprimeChave(int posy , int posx);

void ImprimeJogador(int posy , int posx);  

void ImprimeInimigo (int posy, int posx , ELado lado);

void ImprimeRefens(Refens refens[]);

void ImprimeSaida(Chaves *chave);

void ImprimeInimigos(Inimigos inimigo[]);

void RodandoJogo(Players *jogador , Inimigos inimigos[] , Refens *refen, Chaves *chave);

void AndaJogador(Players *jogador, Chaves *chave); 

void Visor(Players *jogador, Chaves *chave);

bool Pega (Players *jogador , Chaves *chave, ELado lado);

char Proximo (int posy ,int posx , ELado lado);

void DeletaCaracter (int posy , int posx);

void Morre (Players *jogador , Chaves *chave);

void DropaChave (Players *jogador , Chaves *chave);

void AtualizaVisor(Players *jogador , Chaves *chave);

void Pausado ();

void MoveInimigos(Inimigos inimigo[]);

int SorteiaPas();

void AndaInimigo(Inimigos *inimigo , Players *jogador, Chaves *chave);

bool ValidoInim(Inimigos *inimigo, Players *jogador, Chaves *chave, ELado lado);

void Sleep(float temp);

int Kbhit();

bool ValidaProximo(int posy, int posx, ELado lado);

void GeraVisao(int posy, int posx, ELado lado , char gerado);

int SorteiaDir();

char Atual(int posy , int posx);

bool ValidaAtual(int posy, int posx);

void MoveInimigo(Inimigos *inimigo);

void Anda(Inimigos *inimigo);

void ApagaRastro(int posy, int posx, ELado lado);
#endif

