#include<GL/gl.h>
#include<GL/glut.h>
#include "game.h"
#include<stdlib.h>

#define COLUMNS 40
#define ROWS 40
#define FPS 8

extern short sDirection; //Da pokupimo promenljivu iz drugog fajla.
bool gameOver=false;

int score=0;

void timer_callback(int);
void display_callback();
void reshape_callback(int, int); //Funkcija koja menja velicinu ekrana
void keyborad_callback(int,int,int);


void init()
{
    glClearColor(0.0,0.0,0.0,0.0); //Funkcija u kojoj unosimo vrednosti za promenu boje ekrana.
    initGrid(COLUMNS,ROWS); //Za crtanje linija, granica, koje ce nam pomoci da se lakse pozicioniramo na ekranu
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv); //Inicijalizacija Glata. Prvi argument se dodaje zajedno sa & jer nije pointer dok se drugi dodaje direktno posto je pointer.
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //Inicijalizacija moda ekrana, na RGB mod. Inicijalizacija double buffera. Jedan bafer se koristi za iscrtavanje sledece animacije, prvi bafer se koristi za prikaz, oni se zamenjuju medjusobno.
	glutInitWindowSize(800,800); //Velicina ekrana
	glutCreateWindow("ZMIJICA"); //Pravi glavni prozor, argument je ime prozora.
	glutDisplayFunc(display_callback); //Funkcija koju koristimo za iscrtavanje stvari po ekranu
	glutReshapeFunc(reshape_callback); //Za menjanje velicine ekrana, poziva se svaki put kad se ekran minimajzuje, fullskrinuje itd.
	glutTimerFunc(0,timer_callback,0); //Prvi argument, cim se upali program, ne zelimo odlaganje, tako da se koristimo 0 milisekundi.
	glutSpecialFunc(keyborad_callback); //Funkcija za pritiskanje tastera
	init(); //Menjanje boje pozadine ekrana
	glutMainLoop();
	return 0;
}

void display_callback()
{
    glClear(GL_COLOR_BUFFER_BIT); //Cisti bafer, a argumentu je bafer koji cistimo, u ovom slucaju baffer za boju
    drawGrid();
    drawSnake();
    drawFood();
	glutSwapBuffers(); //Zamena bafera.
	if(gameOver)
    {
        char _score[10];
        itoa(score,_score,10);
        char text[50]="Vas skor je: ";
        strcat(text,_score);
        MessageBox(NULL,text,"GAME OVER",0);
        exit(0);
    }
}
void reshape_callback(int w, int h) //W za sirinu u H za visinu ekrana
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);//Svaki put kada se prozor prosiri ili smanji, nas poligon ce to pratiti, poligon ili view board, ugao gledanja. Tako da sve sto je u prozoru pokriva ceo prozor koji je otvoren.
    glMatrixMode(GL_PROJECTION); //Namestanje matrice na matricu pojektovanja, trenutno smo u matrici za modelovanje objekata, prebacujemo sa na matricu za projektovanje.
    glLoadIdentity(); //Da bi bili sigurno da nema promena na matrici dok sami ne pocenmo da ih unosimo
    glOrtho(0.0,COLUMNS,0.0,ROWS,-1.0,1.0); //Koristimo ortografsku projekciju, zato sto je igrica 2D nema potrebe da koristimo perspektivnu.Unosimo takodje i koordinate. Z osa je namestena na od -1 do 1 jer je 2D u pitanju.
    glMatrixMode(GL_MODELVIEW); //Posto smo zavrsili sa namestanjem kordinata projekcije, vracamo se na modelovanje projekciju
}
void timer_callback(int)
{
    glutPostRedisplay(); //Tera kompajler da pozove display funkciju, novi ekran ce se pokazati svakim pozivom
    glutTimerFunc(1000/FPS,timer_callback,0); //Funkcija dispeja ce se pozivati 10 puta u jednoj sekundi.
}
void keyborad_callback(int key,int,int) //Funkcija za unos specijalnih karaktera, ostala 2 argumenta su nam za poziciju misa u trenutku kada je to posebno dugme stisnuto
{
    switch(key)
    {
    case GLUT_KEY_UP:
        if(sDirection!=DOWN) //U slucaju da ide na gore, moramo da proverimo da li je pritisnuto na dole, jer zmija ne moze da ide u nazad, tek onda mozemo da menjamo kuda ide
            sDirection=UP;
        break;
    case GLUT_KEY_DOWN:
        if(sDirection!=UP)
            sDirection=DOWN;
        break;
    case GLUT_KEY_RIGHT:
        if(sDirection!=LEFT)
            sDirection=RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if(sDirection!=RIGHT)
            sDirection=LEFT;
        break;

    }
}
