#include <game.h>



int main (int argc, char *argv[]) { 
srand(time(NULL));
int tempo;
global_loop = &tempo;

//Prototipos 
initscr();  // inicia o ncurses
noecho(); // faz com que nao se imprima o que eh digitado no teclado
cbreak();//passo tudo pra mim 
curs_set(false); // Some com o cursor
start_color(); //Aplica cores ao jogo


Menu();


endwin() ; // termina ncurses 

 return 0;
}

