#ifndef Tetris_proj_title_h
#define Tetris_proj_title_h

void titleInit()
{
    glutDisplayFunc(titleDisplay);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0.0f, .3f, 0.0, 0, 0, 0, 0.0, 1, 0.0);
    glClearColor(1.0,1.0,1.0,1);
    piezaActual=Pieza(rand() % MAX_SHAPES, tetris.getHeight());
    tetris.insertar(piezaActual);
    glutTimerFunc(300, tetrisLoop, 0);

}

#endif
