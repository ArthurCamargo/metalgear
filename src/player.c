#include <game.h>
//funcoes referentes ao jogador

//funcao que faz o jogador andar 
void AndaJogador(Players *jogador , Chaves *chave , Dardos *dardo){
	keypad(global_janela , TRUE);
	char ch;
	ch = wgetch(global_janela);
	switch(ch){ 
	case 'w': 	
		if(Pega(jogador , chave , UP)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posy --;	
			ImprimeJogador(jogador->posy, jogador->posx);
			jogador->dir = UP;
		}
		break;
		
	case 's':
		if(Pega(jogador , chave , DOWN)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posy ++;	
			ImprimeJogador(jogador->posy, jogador->posx);
			jogador->dir = DOWN;
		}
		break;
		
	
	case 'a':
		if(Pega(jogador , chave , LEFT)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posx --;	
			ImprimeJogador(jogador->posy, jogador->posx);
			jogador->dir = LEFT;
		}
		break;
	
	case 'd':
		if(Pega(jogador , chave , RIGHT)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posx ++;	
			ImprimeJogador(jogador->posy, jogador->posx);
			jogador->dir = RIGHT;
		}
		break;
	case 'p': // Pausa o jogo 
		Pausado();
		break;
	case ' ':  // Atira com o dardo 
		if (jogador->dardos > 0){
			JogaDardo(jogador , dardo);
			jogador->dardos -= 1;
			AtualizaVisor(jogador, chave);
		}
		break;
	//cheat-codes	
//	case 'u':
	//pega a chave 
//		chave->tem_chave = true;
//		DeletaCaracter(chave->posy, chave->posx[0]);
//		DeletaCaracter(chave->posy, chave->posx[1]);
//		ImprimeSaida(chave);
//		Visor(jogador, chave);
//		break; 
    // mais 5 dardos
//	case 'k':
//		jogador->dardos += 5;
//		break;    c
		
	}
}

bool Pega(Players *jogador , Chaves *chave, ELado lado){
	bool pode_andar = true;	
	switch(Proximo(jogador->posy , jogador->posx , lado)){
			case '%':
				jogador->dardos += 2;
				Visor(jogador, chave);
				break;
			case '0':
				jogador->pontos += 100;
				Visor(jogador, chave);
				break;
			case 'x':
				jogador->ganhou = true;	
				break;
			case 'o':
				chave->tem_chave = true;
				DeletaCaracter(chave->posy, chave->posx[0]);
				DeletaCaracter(chave->posy, chave->posx[1]);
				ImprimeSaida(chave);
				Visor(jogador, chave);
				break;
			case '=':
				chave->tem_chave = true;
				DeletaCaracter(chave->posy, chave->posx[0]);
				DeletaCaracter(chave->posy, chave->posx[1]);
				ImprimeSaida(chave);
				Visor(jogador, chave);
				break;
			case ' ':
				break;
			case '.':
				Morre(jogador, chave);
				pode_andar = false;
				break;
			case '>':
				Morre(jogador, chave);
				pode_andar = false;
				break;
			case '<':
				Morre(jogador, chave);
				pode_andar = false;
				break;
			case '^':
				Morre(jogador, chave);
				pode_andar = false;
				break;
			case 'v':
				Morre(jogador, chave);
				pode_andar = false;
				break;
			 
			default:
				pode_andar = false;
				break;
		}
	return pode_andar;
}

void Morre(Players *jogador, Chaves *chave) {
	jogador->vidas -= 1;
	if(chave->tem_chave)
		DropaChave(jogador, chave);
	ImprimeJogador(jogador->posiniy, jogador->posinix);
	DeletaCaracter(jogador->posy , jogador->posx);
	jogador->posy = jogador->posiniy;
	jogador->posx = jogador->posinix;
	AtualizaVisor(jogador , chave);
	if(jogador->vidas == 0) 
		jogador->perdeu = true;
	}

void DropaChave (Players *jogador, Chaves *chave) { 
	ImprimeChave(jogador->posy, jogador->posx + 1);	
	chave->tem_chave = false;
	ImprimeSaida(chave);
	chave->posy = jogador->posy;
	chave->posx[0] = jogador->posx + 1;
	chave->posx[1] =jogador->posx + 2;
	
	
}

void VerificaVivo(Players *jogador, Chaves *chave){
	if((Proximo(jogador->posy, jogador->posx, STOP) == '.'))	
		Morre(jogador ,chave);
}

void JogaDardo(Players *jogador , Dardos *dardo) {
	ELado dir;
	dir = jogador->dir;
	switch(dir){ // joga o dardo de acordo com a posicao do jogador 
		case UP:
				dardo->posx = jogador->posx;
				dardo->posy = jogador->posy - 1;
		break;
		case DOWN:
				dardo->posx = jogador->posx;
				dardo->posy = jogador->posy + 1;
		break;
		case LEFT:
				dardo->posx = jogador->posx - 1;
				dardo->posy = jogador->posy;
		break;
		case RIGHT:
				dardo->posx = jogador->posx + 1;
				dardo->posy = jogador->posy;
		break;
	}
	dardo->existe = true; //existencia do dardo
	dardo->andados = 0;  // quantidade de passos dado pelo dardo
	dardo->dir = dir; //direcao do dardo
}

void MoveTiro(Players *jogador ,Dardos *dardo ){ // funcao que move o dardo pelo mapa
	if(dardo->andados == DARDODIS)
		dardo->existe = false; // se o dardo for igual a distancia maxima ele deixa de existir

	switch(dardo->dir){ //Anda com o dardo de acordo com a direcao do mesmo
		case UP:
			if (ValidaDardo(dardo)){
				DeletaCaracter(dardo->posy, dardo->posx);
				dardo->posy = dardo->posy - 1 ;
				dardo->posx = dardo->posx;
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
			break;
		case DOWN:
			if (ValidaDardo(dardo)){
				DeletaCaracter(dardo->posy , dardo->posx);
				dardo->posy = dardo->posy + 1;
				dardo->posx = dardo->posx;
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
			break;
		case LEFT:
			if (ValidaDardo(dardo)){
				DeletaCaracter(dardo->posy , dardo->posx);
				dardo->posy = dardo->posy; 
				dardo->posx = dardo->posx - 1;
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
			break;
		case RIGHT:
			if (ValidaDardo(dardo)){
				DeletaCaracter(dardo->posy , dardo->posx);
				dardo->posy = dardo->posy;
				dardo->posx = dardo->posx + 1; 
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
		break;
	}
	
}

bool ValidaDardo(Dardos *dardo){ // Verifica se a proxima posicao do dardo e valida 
	if (Proximo (dardo->posy , dardo->posx ,  dardo->dir) != NADA && 
		Proximo (dardo->posy , dardo->posx ,  dardo->dir) != ENEMY_UP && 	 
		Proximo (dardo->posy , dardo->posx ,  dardo->dir) != ENEMY_RIGHT && 	 
		Proximo (dardo->posy , dardo->posx ,  dardo->dir) != ENEMY_LEFT  &&	 
		Proximo (dardo->posy , dardo->posx ,  dardo->dir) != ENEMY_DOWN  && 
		Proximo (dardo->posy , dardo->posx ,  dardo->dir) != '.'
	){

		dardo->existe = false;
		return false;
	}
	else 
		return true;

}

