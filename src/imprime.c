#include <game.h>





void ImprimeJogador(int posy , int posx){
	mvwaddch(global_janela, posy ,posx , (char) PLAYER_UP);
	wrefresh(global_janela);
	}
void ImprimeInimigo(int posy , int posx, ELado lado ) { 
	switch (lado) {	
	case UP:
		mvwaddch(global_janela, posy , posx, ENEMY_UP);	
		wrefresh(global_janela); 
		break;
	case DOWN:
		mvwaddch(global_janela, posy  , posx, ENEMY_DOWN);	
		wrefresh(global_janela); 
		break;
	case LEFT:
		mvwaddch(global_janela, posy, posx , ENEMY_LEFT);	
		wrefresh(global_janela); 
		break;
	case RIGHT:
		mvwaddch(global_janela, posy, posx , ENEMY_RIGHT);	
		wrefresh(global_janela); 
		break;

	}
}
				
void ImprimeRefens (Refens vecref[]) { 
	int i;
	for (i = 0 ; i < QUANTREF; i ++){
		if(vecref[i].posy !=0  && vecref[i].posx != 0){
			mvwaddch(global_janela, vecref[i].posy, vecref[i].posx, (char) REFEN);	
			wrefresh(global_janela);
		}
	}
}		

void ImprimeChave (int posy , int posx){
	mvwaddch(global_janela, posy, posx, CHAVE1);	
	waddch(global_janela, CHAVE2); 
	wrefresh(global_janela);
}

void ImprimeSaida(Chaves *chave){
	char saida = SFECHADA;
	if(chave->tem_chave == true) 
		saida = SABERTA;	
	mvwaddch(global_janela, chave->saidaposy , chave->saidaposx , saida);
	wrefresh(global_janela);

	}
void AtualizaVisor (Players *jogador, Chaves *chave){
	int x = INICIOVX , y = INICIOVY;
	wmove (global_janela, INICIOVY ,INICIOVX);	
	
	while( x != FIMVX && y != FIMVY){
		waddch(global_janela,  ' '); 
		x++;
		if(x == FIMVX){
			wmove(global_janela, y + 1 , INICIOVX);
			x = INICIOVX;
			y++;
		}
	}
	Visor(jogador , chave);
}
void Visor(Players *jogador, Chaves *chave) {
		int i;
		if (chave->tem_chave){
		mvwaddch(global_janela, CHAVEY , CHAVEX, CHAVE1);  
		mvwaddch(global_janela, CHAVEY , CHAVEX + 1, CHAVE2);  
			}

		mvwprintw(global_janela, VIDAY , VIDAX , VIDAT);   
		for(i = 0; i < jogador->vidas; i++)	
			waddch(global_janela, VIDA);

		mvwprintw(global_janela, DARDOY , DARDOX , DARDOT);   
		for(i = 0; i < jogador->dardos; i++)	
			waddch(global_janela, DARDOV);

		mvwprintw(global_janela, PONTOY , PONTOX , PONTOT);
			wprintw(global_janela, "%d" , jogador->pontos);

		wrefresh(global_janela);
		for (i = 0; i < TAMNOME; i ++)
			jogador->nome[i] = toupper(jogador->nome[i]);
		mvwprintw(global_janela, NOMEY, NOMEX , NOMET);
			wprintw(global_janela , jogador->nome);

		wrefresh(global_janela);
}

void ImprimeMapa() { 
	char ch;	
	int x = XSHIFT , y = YSHIFT;
	FILE *arq;
	Recarrega();
	if ((arq = fopen(URL1 , "r+")) == NULL){
		Message(M_TOPOY, M_MEIOX - (int) strlen(ERROR_A)/2, ERROR_A);
		}
	wmove(global_janela , y , x);
	while(!feof(arq)){
		ch = getc(arq);
		if (ch == '\n'){
			getyx(global_janela, y, x);
			wmove(global_janela, y + 1, XSHIFT);	
			ch = getc(arq);
			}
		waddch(global_janela, ch);
		}
}	

void ImprimeInimigos (Inimigos inimigos[]){
	int i;	
	for (i = 0; i < QUANTINI; i ++){
		inimigos[i].dir = SorteiaDir();
		ImprimeInimigo(inimigos[i].posy , inimigos[i].posx , inimigos[i].dir , VISAO); 
	}
}



		
		
		
			
		
		
		

