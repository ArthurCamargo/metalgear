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
bool ValidaAtual(int posy, int posx){
	bool retorno;
	if (Atual(posy, posx) == ' ')
		retorno = true;
	else 
		retorno = false;
	return retorno;
}
	
void MoveInimigo(Inimigos *inimigo){
	inimigo->dir = SorteiaDir();	
	inimigo->passos = SorteiaPas();			
	if (ValidaProximo(inimigo->posx , inimigo->posy , inimigo->dir)){
		Anda(inimigo);	
		inimigo->passos -= 1;
		if (inimigo->passos  == 0){
			inimigo->dir = SorteiaDir();
			inimigo->passos = SorteiaPas();
		}
	}
}
void MoveInimigos(Inimigos inimigos[]){
	int i;
	for(i = 0; i < QUANTINI; i ++){
		MoveInimigo(&inimigos[i]);
		}
}


void Anda (Inimigos *inimigo){
	GeraVisao(inimigo->posy,inimigo->posx, inimigo->dir, VISAO);
	switch(inimigo->dir){
		case UP:
			inimigo->posy -= 1;		
			ImprimeInimigo(inimigo->posy , inimigo->posx , inimigo->dir); 
			break;
		case DOWN:
			inimigo->posy += 1;		
			ImprimeInimigo(inimigo->posy , inimigo->posx , inimigo->dir); 
			break;
		case LEFT:
			ImprimeInimigo(inimigo->posy , inimigo->posx , inimigo->dir); 
			inimigo->posx -= 1;		
			ImprimeInimigo(inimigo->posy , inimigo->posx , inimigo->dir); 
			break;
		case RIGHT:
			ImprimeInimigo(inimigo->posy , inimigo->posx , inimigo->dir); 
			inimigo->posx += 1;		
			ImprimeInimigo(inimigo->posy , inimigo->posx , inimigo->dir); 
			break;
		default:
			break;
	}
}

void Espera(int quantc){
	quantc = 1;
	while(global_contador%quantc != 0)
	global_contador ++;
	global_contador = 0;	
}

