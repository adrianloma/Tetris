//
//  main.cpp
//  Tetris_proj
//
//  Created by Adrian Lozano on 3/19/14.
//  Copyright (c) 2014 Adrian Lozano. All rights reserved.
//


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


void endProg()
{
    if(BASS_Free())
        exit(EXIT_SUCCESS);
    else
        exit(EXIT_FAILURE);
}




#include "Formas.h"



Tetris tetris(10, 20, 10, .2f);
Pieza piezaActual(TETRIS_SHAPE_SQUARE);

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

#include "display.h"
#include "sound.h"
#include "keyboard.h"




void init()
{
    srand((unsigned int) time(0));

    piezaActual=Pieza(rand() % 5);
    
    CBInit(); //display callbacks init
    displayInit();
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

