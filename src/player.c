#include <game.h>


void AndaJogador(Players *jogador , Chaves *chave){
	keypad(global_janela , TRUE);
	char ch;
	ch = wgetch(global_janela);
	switch(ch){
	case 'w': 	
		if(Pega(jogador , chave , UP)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posy --;	
			ImprimeJogador(jogador->posy, jogador->posx);
		}
		break;
		
	case 's':
		if(Pega(jogador , chave , DOWN)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posy ++;	
			ImprimeJogador(jogador->posy, jogador->posx);
		}
		break;
		
	
	case 'a':
		if(Pega(jogador , chave , LEFT)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posx --;	
			ImprimeJogador(jogador->posy, jogador->posx);
		}
		break;
	
	case 'd':
		if(Pega(jogador , chave , RIGHT)){	
			mvwaddch(global_janela, jogador->posy , jogador->posx , ' ');
			jogador->posx ++;	
			ImprimeJogador(jogador->posy, jogador->posx);
		}
		break;
	case 'p':
		Pausado();
		break;

	case 'u':
		chave->tem_chave = true;
		DeletaCaracter(chave->posy, chave->posx[0]);
		DeletaCaracter(chave->posy, chave->posx[1]);
		ImprimeSaida(chave);
		Visor(jogador, chave);
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
