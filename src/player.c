#include <game.h>


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
	case 'p':
		Pausado();
		break;
	case ' ': 
		if (jogador->dardos > 0){
			JogaDardo(jogador , dardo);
			jogador->dardos -= 1;
			AtualizaVisor(jogador, chave);
		}
		break;
		
	case 'u':
		chave->tem_chave = true;
		DeletaCaracter(chave->posy, chave->posx[0]);
		DeletaCaracter(chave->posy, chave->posx[1]);
		ImprimeSaida(chave);
		Visor(jogador, chave);
		break; 
	case 'k':
		jogador->dardos += 5;
		break;
		
	}
}

bool Pega(Players *jogador , Chaves *chave, ELado lado){
	bool pode_andar = true;	
	switch(Proximo(jogador->posy , jogador->posx , lado)){
			case '%':
				jogador->dardos += 1;
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
	switch(dir){
		case UP:
			if(Proximo(jogador->posy , jogador->posx , UP) == ' '){
				dardo->posx = jogador->posx;
				dardo->posy = jogador->posy - 1;
			}
		break;
		case DOWN:
			if(Proximo(jogador->posy , jogador->posx , DOWN) == ' '){
				dardo->posx = jogador->posx;
				dardo->posy = jogador->posy + 1;
			}
		break;
		case LEFT:
			if(Proximo(jogador->posy , jogador->posx , LEFT) == ' '){
				dardo->posx = jogador->posx - 1;
				dardo->posy = jogador->posy;
			}
		break;
		case RIGHT:
			if(Proximo (jogador->posy , jogador->posx , RIGHT) == ' '){
				dardo->posx = jogador->posx + 1;
				dardo->posy = jogador->posy;
			}
		break;
	}
	dardo->existe = true;
	dardo->andados = 1;
	dardo->dir = dir;
}

void MoveTiro(Players *jogador ,Dardos *dardo ){
	if(dardo->andados == DARDODIS)
		dardo->existe = false;

	switch(dardo->dir){
		case UP:
			if (ValidaDardo){
				DeletaCaracter(dardo->posy, dardo->posx);
				dardo->posy = dardo->posy - 1 ;
				dardo->posx = dardo->posx;
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
			break;
		case DOWN:
			if (ValidaDardo){
				DeletaCaracter(dardo->posy , dardo->posx);
				dardo->posy = dardo->posy + 1;
				dardo->posx = dardo->posx;
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
			break;
		case LEFT:
			if (ValidaDardo){
				DeletaCaracter(dardo->posy , dardo->posx);
				dardo->posy = dardo->posy; 
				dardo->posx = dardo->posx - 1;
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
			break;
		case RIGHT:
			if (ValidaDardo){
				DeletaCaracter(dardo->posy , dardo->posx);
				dardo->posy = dardo->posy;
				dardo->posx = dardo->posx + 1; 
				dardo->andados += 1;
				mvwaddch(global_janela, dardo->posy , dardo->posx, DARDO); 
			}
		break;
	}
	
}

bool ValidaDardo(Dardos *dardo){
	if (Proximo (dardo->posy , dardo->posx , dardo->dir) != NADA &&
		Proximo (dardo->posy , dardo->posx , dardo->dir) != ENEMY_UP && 	 
		Proximo (dardo->posy , dardo->posx , dardo->dir) != ENEMY_RIGHT &&	 
		Proximo (dardo->posy , dardo->posx , dardo->dir) != ENEMY_LEFT &&	 
		Proximo (dardo->posy , dardo->posx , dardo->dir) != ENEMY_DOWN &&
		Proximo (dardo->posy , dardo->posx , dardo->dir) != '.'
	){	
		dardo->existe = false;
		return false;
	}
	else 
		return true;

}

