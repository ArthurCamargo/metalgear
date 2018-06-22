#include <game.h> 


void Cwindow(){
	int inity;
	int initx;
inity = (LINES - ALTURA)/ 2; /* coloca a janela no meio da tela*/
	initx = (COLS - LARGURA)/ 2; /*                              */
	
	global_janela = newwin(ALTURA , LARGURA , inity, initx);
	box(global_janela, 0, 0);

	wrefresh(global_janela);

}

void Recarrega(){
	Cwindow ();
	wrefresh(global_janela);
}

void Message (int y , int x , char mensagem[]){
	Recarrega();
	mvwprintw(global_janela , y , x , "%s", mensagem);	
	wrefresh(global_janela);

}	



bool Realmente() { 
	char saida;
	bool retorno= true; //retorno da funcao 
	bool continua = true; //verifica se eh para continuar perguntando pra sair
	Message(2, LARGURA/2 - 10 , "Deseja realmente sair? (s/n)");
	while (continua){
		saida = wgetch(global_janela);
		if (saida == 's'){
			continua = false;
			retorno = false;	
			}
		else
			if (saida == 'n'){
				retorno = true;
				continua = false;
				}
	}	
	return retorno;		
}	

void Menu() { 

	char opt; // character das opcoes 
	bool continua; // bool para descobrir se vai sair ou nao

 
	continua = true; // comeca com saida em false 

	while(continua) {
		Recarrega();
		mvwprintw(global_janela, M_TOPOY , M_MEIOX - strlen(TITULO)/2 , TITULO);				/*Imprime o menu na tela*/
		mvwprintw(global_janela, M_MEIO_ACIMAY,  M_MEIOX - strlen (NOVOJOGO)/2  ,  NOVOJOGO);
		mvwprintw(global_janela, M_MEIO_MEIOY,   M_MEIOX - strlen (TOP10)/2  ,  TOP10);
		mvwprintw(global_janela, M_MEIO_ABAIXOY, M_MEIOX - strlen (SAIR)/2 ,  SAIR);               
		wrefresh(global_janela);

		opt = wgetch(global_janela); //pega um caracter na janela colcada como parametro

		if(opt == 'n') {
			NovoJogo(); //comeca um novo jogo 
			continua = true;
		}
		if(opt == 't') {
		}
		if(opt == 'r') {
			continua = Realmente(); //pergunta se realmente desja sair
		}
	}
}
void NovoJogo() {

	Players jogador;      /* Cria um jogador com parametros iniciais*/
	jogador.vidas = 3;
	jogador.dardos = 5;
	jogador.pontos = 0;

	Chaves chave; // Cria a chave 
	chave.tem_chave = false;
	Inimigos inimigos[QUANTINI];  /* Cria uma matriz de inimigos para colocar na fase */

	Refens refens[QUANTREF];  /* Cria uma matriz de refens para colocar na fase */

	LeNome(&jogador); //le o nome do jogador 
	LeMapa(&jogador , inimigos , &chave, refens); //le a posicao do jogador , inimigos , chave, e refens no mapa) 
	ImprimeMapa(); //imprime o mapa
	ImprimeSaida(&chave);
	ImprimeJogador(jogador.posy, jogador.posx); //imprime o jogador no local apresentado no mapa 
	
	ImprimeInimigos(inimigos);
	//DeletaInimigos(inimigos);
	ImprimeRefens(refens); // imprime os refens nos locais lidos no mapa ImprimeChave(&chave);
	ImprimeChave(chave.posy , chave.posx[0]);// imprime a chave no local lido no mapa
	Visor(&jogador, &chave);
	RodandoJogo(&jogador, inimigos, refens, &chave);

}

void LeMapa(Players *jogador, Inimigos vecini[], Chaves *chave , Refens vecref[]) {
	int contini=0 , contref = 0;// Contador de inimigos e refens 
	int numini = 0 , numref = 0;
	int linha = CSHIFT, coluna = YSHIFT ; //linha e coluna dos inimigos
	char ch; // variavel para pegar os char no mapa 1 a 1;
	FILE *arq;
	if ((arq = fopen(URL1 , "r+")) == NULL){
		Message(M_TOPOY, M_MEIOX - (int) strlen(ERROR_A)/2, ERROR_A);
		ch =  wgetch(global_janela);
	}
	else{
		while(!feof(arq)){
			ch = getc(arq);	
			linha ++;
			if (ch == '\n'){
				coluna ++;	
				linha = CSHIFT;
				}
			if (ch == '@'){	
				vecini[contini].posx = linha; 
				vecini[contini].posy = coluna; 
				contini ++;
				numini ++;
			}
			if (ch == 'k'){
				chave->posx[0]  = linha;	
				chave->posx[1]  = linha + 1;
				chave->posy = coluna;
			}		
			if (ch == '0'){
				vecref[contref].posx = linha;
				vecref[contref].posy = coluna;
				contref++;
				numref ++;
			}
			if (ch == 'o'){
				jogador->posx = linha;
				jogador->posy = coluna;
				jogador->posinix = linha;
				jogador->posiniy = coluna;
			}
			if (ch == 'x') {
				chave->saidaposx = linha;
				chave->saidaposy = coluna;
			}
		}
	fclose(arq);
	}
}


void RodandoJogo(Players *jogador ,Inimigos inimigos[] , Refens refens[] , Chaves *chave) {
	nodelay(global_janela, TRUE);
	while(!jogador->ganhou && !jogador->perdeu){
		AndaJogador(jogador, chave);

		while (!Kbhit()){
			usleep(120000);
			MoveInimigos(inimigos);
			
		}
	}
}

		

//void VisaoInimigos(Inimigos
	
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

char Proximo(int posy , int posx ,ELado lado) { 
	char ch;
	switch(lado){
	case UP:
		ch = mvwinch(global_janela , posy - 1, posx );
		break;
	case DOWN:
		ch = mvwinch(global_janela , posy + 1 , posx );
		break;
	case LEFT:
		ch = mvwinch(global_janela , posy , posx - 1);
		break;
	case RIGHT:
		ch = mvwinch(global_janela , posy , posx + 1);
		break;
	default:
		ch = mvwinch(global_janela, posy ,posx);
	}
	return ch;
}

void LeNome(Players *jogador) {

Recarrega();
mvwprintw(global_janela, M_TOPOY, M_MEIOX - strlen(DIGITA_NOME)/2 , DIGITA_NOME);  
echo();
mvwscanw(global_janela,M_TOPO_ABAIXOY, M_MEIOX, "%3s" , jogador->nome);
noecho();

}

void DeletaCaracter(int posy ,int  posx) {
	mvwaddch(global_janela , posy , posx , ' ');
	wrefresh(global_janela);
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

void Pausado () {
	bool pausado = true;
	char ch;
	
	while(pausado){
		ch = wgetch(global_janela);	
		mvwprintw(global_janela , M_TOPOY , M_MEIOX , PAUSADO);    
		if (ch == 'p'){
			mvwprintw(global_janela, M_TOPOY , M_MEIOX , APAGADO);
			pausado = false;	
			}
	}
}

int Kbhit() {
	int ch;  
	ch = wgetch(global_janela);
	if (ch != ERR){
		ungetch(ch);
		return 1;
	}		
	else 
		return 0;
	
}
	
