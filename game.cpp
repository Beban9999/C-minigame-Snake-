#include<GL/glut.h>
#include<GL/glut.h>
#include<ctime>
#include "game.h"

extern int score;

int gridX,gridY;
int snake_length=5;
bool food=true; //Da li je hrana pojedena
int foodX,foodY; //Koordinate hrane

short sDirection=LEFT; //Promenljiva koja cuva unos sa tastature, po defaultu zmija ce se kretati desno
extern bool gameOver;

int posX[60]={20,20,20,20,20},posY[60]={20,19,18,17,16}; //Pozicija zmije od 5 kocki koja se pojavljuje na pocetku igre

void initGrid(int x, int y) //Za crtanje resetaka na ekranu.
{
    gridX=x;
    gridY=y;
}

void unit(int,int);
void drawGrid()
{
    for(int x=0;x<gridX;x++)
    {
        for(int y=0;y<gridY;y++)
        {
            unit(x,y); //Pisemo funkciju za crtanje kvadrata u petlji tako da bi iscrtao kvadrata po celom ekranu
        }
    }
}


void unit(int x,int y) //Crtanje kvadrata na mesto na koju pokazu drawGrid fukcija
{
    if(x==0 || y==0 || x==gridX-1 || y==gridY-1) //Proveravamo da li su kvadratici koje crtamo na krajnjim delovima ekrana tako da mozemo da im promenimo boju
    {
        glLineWidth(3.0); //Debljina linije
        glColor3f(1.0,0.0,0.0); //Boja linije
    }
    else
    {
        glLineWidth(1.0); //Debljina ako nije u krajnjim delovima ekrana
        glColor3f(0.5,0.5,0.5);
    }

    glBegin(GL_LINE_LOOP); //Crtace zatvorenu figuru, ustvari crta linije u petlji koje ce se na kraju spojiti, poslednja i prva tacka ce biti iste
        glVertex2f(x,y); //Prva tacka
        glVertex2f(x+1,y); //Linija ide desno
        glVertex2f(x+1,y+1); //Linija ide gore
        glVertex2f(x,y+1); //Linija ide levo,tj vraca se na pocetnu ali na novoj visini, konkretno, ovime smo napravili kocku
    glEnd(); //Za kraj crtanja
}

void drawFood() //Za crtanje hrane za zmiju
{
    if(food)
        random(foodX,foodY);
    food=false;
    glColor3f(1.0,0.0,0.0);
    glRectf(foodX,foodY,foodX+1,foodY+1); //Crtanje hrane
}
void drawSnake() //Crtanje zmije
{
    for(int i=snake_length-1;i > 0; i--)
    {
        posX[i]=posX[i-1];
        posY[i]=posY[i-1];
    }
    if(sDirection==UP)
        posY[0]++;
    else if(sDirection==DOWN)
        posY[0]--;
    else if(sDirection==RIGHT)
        posX[0]++;
    else if(sDirection==LEFT)
        posX[0]--;
    for(int i=0; i< snake_length; i++)
    {
        if(i==0)
            glColor3f(0.0,1.0,0.0);
        else
            glColor3f(0.0,0.5,1.0);
        glRectd(posX[i],posY[i],posX[i]+1,posY[i]+1);
    }
    if(posX[0]==0 || posX[0]==gridX-1 || posY[0]==0 || posY[0]==gridY-1) //Ako se sudarimo za ivicom ekrana, kraj igre
        gameOver=true;

    if(posX[0]==foodX && posY[0]==foodY)//Proverava da li je hrana pojedena
        {
            score++;
            snake_length++;
            if(snake_length>MAX)
                snake_length=MAX;
            food=true;
        }
}

void random(int &x,int &y)
{
    int _maxX=gridX-2;
    int _maxY=gridY-2;
    int _min=1;
    srand(time(NULL));
    x= _min + rand() % (_maxX-_min); //Trik da se dobiju brojevi koji nisu preveliki
    y= _min + rand() % (_maxY-_min);


}
