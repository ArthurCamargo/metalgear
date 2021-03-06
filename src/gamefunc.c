#include <game.h> 
//Funcoes do jogo em geral

void Cwindow(){
	int inity;
	int initx;
	inity = (LINES - ALTURA)/ 2; /* coloca a janela no meio da tela*/
	initx = (COLS - LARGURA)/ 2; /*                              */
	
	global_janela = newwin(ALTURA , LARGURA , inity, initx); //janela global   
	box(global_janela, 0, 0); //cria uma caixa como janela 

	wrefresh(global_janela);

}
//recarrega a janela do jogo
void Recarrega(){
	Cwindow ();
	wrefresh(global_janela);
}
//exibe um mensagem em uma nova janela
void Message (int y , int x , char mensagem[]){
	Recarrega();
	mvwprintw(global_janela , y , x , "%s", mensagem);	
	wrefresh(global_janela);

}	


//Pergunta ao usuario se realmente deseja sair do jogo
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
//Menu do jogo
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

		opt = wgetch(global_janela); //Pega um caracter na janela colcada como parametro

		if(opt == 'n') {
			NovoJogo(); //Comeca um novo jogo 
			continua = true;
		}
		if(opt == 't') {
		}
		if(opt == 'r') {
			continua = Realmente(); //Pergunta se realmente desja sair
		}
	}
}
//Comeca um novo jogo 
void NovoJogo() {
	int i;
	*global_loop = 0; //Coloca o tempo global em 0
	Players jogador;      /* Cria um jogador com parametros iniciais*/
	jogador.vidas = 3;
	jogador.dardos = 5;
	jogador.pontos = 0;
	jogador.perdeu = false;
	jogador.ganhou = false;

	Dardos dardo; //Cria uma dardo
	dardo.existe = false;
	Chaves chave; // Cria a chave 
	chave.tem_chave = false; 
	Inimigos inimigos[QUANTINI];  /* Cria uma matriz de inimigos para colocar na fase */
	for (i = 0; i < QUANTINI; i ++)
		inimigos[i].passos = 0;

	Refens refens[QUANTREF];  /* Cria uma matriz de refens para colocar na fase */

	LeNome(&jogador); //Le o nome do jogador 
	LeMapa(&jogador , inimigos , &chave, refens); //Le a posicao do jogador , inimigos , chave, e refens no mapa) 
	ImprimeMapa(); //Imprime o mapa
	ImprimeSaida(&chave);
	ImprimeJogador(jogador.posy, jogador.posx); //imprime o jogador no local apresentado no mapa 
	Vive(inimigos); //Certifica que todos os inimigos estarao vivos 
	for(i = 0; i < QUANTINI; i ++)
		ImprimeInimigos(&inimigos[i]);
		wrefresh(global_janela);

	ImprimeRefens(refens); // imprime os refens nos locais lidos no mapa ImprimeChave(&chave);
	ImprimeChave(chave.posy , chave.posx[0]);// imprime a chave no local lido no mapa
	Visor(&jogador, &chave); // imprime a interface 
	RodandoJogo(&jogador, inimigos, refens, &chave , &dardo);
}

void LeMapa(Players *jogador, Inimigos inimigos[], Chaves *chave , Refens refens[]) {
	int contini = 0 , contref = 0;// Contador de inimigos e refens 
	int linha = CSHIFT, coluna = YSHIFT ; //linha e coluna dos inimigos
	char ch; // variavel para pegar os char no mapa 1 a 1;
	FILE *arq;
	if ((arq = fopen(URL1 , "r+")) == NULL){
		Message(M_TOPOY, M_MEIOX - (int) strlen(ERROR_A)/2, ERROR_A);
		ch =  wgetch(global_janela);
	}
	else{
		rewind(arq);
		while(!feof(arq)){
			ch = getc(arq);	
			linha ++;
			if (ch == '\n'){
				coluna ++;	
				linha = CSHIFT;
				}
			if (ch == '@'){	
				inimigos[contini].posx = linha; 
				inimigos[contini].posy = coluna; 
				contini ++;
			}
			if (ch == 'k'){
				chave->posx[0]  = linha;	
				chave->posx[1]  = linha + 1;
				chave->posy = coluna;
			}		
			if (ch == '0'){
				refens[contref].posx = linha;
				refens[contref].posy = coluna;
				contref++;
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


void RodandoJogo(Players *jogador ,Inimigos inimigos[] , Refens refens[] , Chaves *chave , Dardos *dardo) {
	nodelay(global_janela, TRUE);
	*global_loop = 0;
	int i;

	while(!jogador->ganhou && !jogador->perdeu){
		AndaJogador(jogador, chave , dardo);
		while (!Kbhit()){
			if (*global_loop % INIMIGOST == 0){
				for (i = 0; i < QUANTINI; i ++)	
					MoveInimigos(&inimigos[i]);
			}
			if (*global_loop % DARDOST == 0 && dardo->existe == true){
				MoveTiro(jogador , dardo);
				ValidaDardo(dardo);
				if (dardo->existe == false) 
					DeletaCaracter(dardo->posy, dardo->posx);
			}
			VerificaVivo(jogador, chave);
			if (VerificaIni(inimigos)){
				*global_loop = 0;
				Dorme(inimigos);
			if (*global_loop % INIMIGOSMT == 0)
				Vive(inimigos);
			}

			*global_loop += 1; 
		}
	}	
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
	
