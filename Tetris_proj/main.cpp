
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "bass.h"
//#include "title.h"


void endProg()
{
    if(BASS_Free())
        exit(EXIT_SUCCESS);
    else
        exit(EXIT_FAILURE);
}




#include "Formas.h"

#define MAX_SHAPES 6

Tetris tetris(5, 20, 5, .2f);
Pieza piezaActual(TETRIS_SHAPE_SQUARE, tetris.getHeight(),  tetris.getWidth(), tetris.getDepth());

float rotacion=0.0f;

bool mover(Pieza &pieza, int x, int y, int z)
{
    tetris.quitar(pieza);
    pieza.mover(x, y , z);
    if (tetris.estaOcupado(pieza)) {
        pieza.mover(-x, -y, -z);
        tetris.insertar(pieza);
        return false;
    }
    tetris.insertar(pieza);
    return true;
}

bool rotateCW(Pieza &pieza)
{
    tetris.quitar(pieza);
    pieza.rotateCW();
    if (tetris.estaOcupado(pieza)) {
        pieza.rotateCCW();
        tetris.insertar(pieza);
        return false;
    }
    tetris.insertar(pieza);
    return true;
}

bool rotateCCW(Pieza &pieza)
{
    tetris.quitar(pieza);
    pieza.rotateCCW();
    if (tetris.estaOcupado(pieza)) {
        pieza.rotateCW();
        tetris.insertar(pieza);
        return false;
    }
    tetris.insertar(pieza);
    return true;
}

bool barrelCW(Pieza &pieza)
{
    tetris.quitar(pieza);
    pieza.barrelCW();
    if (tetris.estaOcupado(pieza)) {
        pieza.barrelCCW();
        tetris.insertar(pieza);
        return false;
    }
    tetris.insertar(pieza);
    return true;
}

bool barrelCCW(Pieza &pieza)
{
    tetris.quitar(pieza);
    pieza.barrelCCW();
    if (tetris.estaOcupado(pieza)) {
        pieza.barrelCW();
        tetris.insertar(pieza);
        return false;
    }
    tetris.insertar(pieza);
    return true;
}



#include "display.h"
#include "sound.h"
#include "keyboard.h"




void init()
{
    srand((unsigned int) time(0));
    
    CBInit(); //display callbacks init
    displayInit();
    //titleInit();
    soundInit();
    KBinit();
    
}


int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    init();
    
    glutMainLoop();
    
    return 0;
}

