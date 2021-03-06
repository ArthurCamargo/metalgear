#include <game.h> 
//funcoes referentes aos inimigos
	
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
	

void MoveInimigos(Inimigos *inimigo){
		DeletaInimigos(inimigo);
		Anda(inimigo);
		ImprimeInimigos(inimigo);
	}
		
void Anda (Inimigos *inimigo){
	int i;
	if(ValidaProximo(inimigo->posy, inimigo->posx, inimigo->dir) && (!Parado(inimigo))){
		switch(inimigo->dir){
			case UP:
				inimigo->posy -= 1;		
				break;
			case DOWN:
				inimigo->posy += 1;		
				break;
			case LEFT:
				inimigo->posx -= 1;		
				break;
			case RIGHT:
				inimigo->posx += 1;		
				break;
		}
	}
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
					
				if(!ValidaVisao(posgy, posgx)){
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
	if ((Proximo(posy,posx,STOP) == ' '))
			retorno = true;
	if((Proximo(posy,posx,STOP) == '.'))
			retorno = true;
	if((Proximo(posy,posx,STOP) == 'o'))
		if((Proximo(posy, posx + 1, STOP) == '='))
			retorno = false;
		else
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

bool VerificaIni(Inimigos inimigos[]){
	int i;
	for (i = 0; i < QUANTINI; i ++){
		if(Proximo(inimigos[i].posy, inimigos[i].posx , STOP) == '*'){
			MorreInim(&inimigos[i]);
			inimigos[i].vivo = false;
			return true;
		}
		else 
			return false;
	}
}

void MorreInim(Inimigos *inimigo){
	GeraVisao(inimigo->posy, inimigo->posx, inimigo->dir, NADA);
	mvwaddch(global_janela, inimigo->posy, inimigo->posx, 'Z');
 	inimigo->parado = true;
}
void Dorme(Inimigos inimigos[]){ 
	int i;
	for (i = 0 ; i < QUANTINI; i++){
		if (!inimigos[i].vivo)
			mvwaddch(global_janela, inimigos[i].posy, inimigos[i].posx, 'Z');
	}
}
void Vive (Inimigos inimigos[]){
	int i;
	for (i = 0; i < QUANTINI; i++){
			inimigos[i].vivo = true;
	}
}

