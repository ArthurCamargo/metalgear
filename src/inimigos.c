#include <game.h> 
	
bool ValidaProximo(int posy, int posx, ELado lado){
	bool retorno;
	char ch;

	if (Proximo(posy, posx, lado) == ' ')		
		retorno = true;
	else if (Proximo(posy, posx , lado) == 'o'){
		if(Proximo(posy + 1, posx, lado) == '='){
			retorno = true;
		}		
		else 
			retorno = false;
	}
	else
		retorno = false;

	return retorno;
}
	

void MoveInimigos(Inimigos inimigos[]){
		DeletaInimigos(inimigos);
		Anda(inimigos);
		ImprimeInimigos(inimigos);
	}
		
void Anda (Inimigos inimigos[]){
	int i;
	for (i = 0; i < QUANTINI; i++){
		if(ValidaProximo(inimigos[i].posy, inimigos[i].posx, inimigos[i].dir) && (Parado(&inimigos[i]))){
			switch(inimigos[i].dir){
				case UP:
					inimigos[i].posy -= 1;		
					break;
				case DOWN:
					inimigos[i].posy += 1;		
					break;
				case LEFT:
					inimigos[i].posx -= 1;		
					break;
				case RIGHT:
					inimigos[i].posx += 1;		
					break;
				default:
					break;
			}
		}
	}
}

void Espera(int quantc){
	quantc = 1;
	while(global_contador%quantc != 0)
	global_contador ++;
	global_contador = 0;	
}

void ContaPassos(Inimigos *inimigo){
	if (inimigo->passos == 0){
		SorteiaDir(inimigo);	
		SorteiaPas(inimigo);	
	}
	else
		inimigo->passos -=1;
	
}
void SorteiaDir(Inimigos *inimigo) {
	int direcao;
	int parado;

	direcao = rand()%5;
	if (direcao == 4){
		inimigo->parado = true;
		direcao = rand()%4;
	}
	else
		inimigo->parado = false;
	

	inimigo->dir = direcao;
}

void SorteiaPas(Inimigos *inimigo) {
	int passos;

		if (inimigo->dir != STOP)
			passos = rand()%3 + 2;
		else
			passos = 4*(rand()%3 + 2);
			
	inimigo->passos = passos;
}


void GeraVisao(int posy , int posx, ELado lado , char gerado){
	int i = 0 , j = 0;
	int posgy , posgx;
	while ( i < CAMPVIS){
		while (j < CAMPVIS){	
				switch(lado){	
					case UP:
						posgy = posy - j;
						posgx = posx + i - 1;
						break;
					case DOWN:
						posgy = posy + j;	
						posgx = posx + i - 1;
						break;
					case LEFT:
						posgy = posy + i - 1;	
						posgx = posx - j;
						break;
					case RIGHT:	
						posgy = posy + i - 1;	
						posgx = posx + j;
						break;
						
				}
					
				if(ValidaVisao(posgy, posgx)){
						j = CAMPVIS;
				}
				else 
					mvwaddch(global_janela,posgy, posgx, gerado);

				wrefresh(global_janela);
				j++;
		}
	i++;
	j = 0;
	}	
}

bool ValidaVisao(int posy, int posx){
	bool retorno = false;
	if ((Proximo(posy,posx,STOP) != ' '))
		if((Proximo(posy,posx,STOP) != '.'))
			if((Proximo(posy,posx,STOP) != 'o'))
			retorno = true;
	return retorno;
	}

bool Parado(Inimigos *inimigos){
	int i;
	bool retorno;
		if (inimigos->parado == true)	
			retorno = true;
		else 
			retorno = false;
	
	return retorno;
}
