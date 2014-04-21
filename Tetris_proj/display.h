#ifndef Tetris_proj_display_h
#define Tetris_proj_display_h

#include <cmath>
#include <stdlib.h>
#include <time.h>



void draw3dString (void *font, char *s, float x, float y, float z) ;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    tetris.dibuja();
    
    //glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    float x = 3*sin(rotacion);
    float z = 3*cos(rotacion);
    gluLookAt(x, 0.3f, z, 0, 0, 0, 0.0, 1, 0.0);

    

    glutSwapBuffers();
    
    
}



void draw3dString (void *font, char *s, float x, float y, float z) {
    unsigned int i;
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(1.0, 0, 0);
    glScaled(5, 5, 5);
    //glRotatef(xMin, 1, 1, 0);
    for (i = 0; s[i] != '\0'; i++)
        glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, s[i]);
    glPopMatrix();
}



void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glOrtho(-1,1,-1,1, 2, 20);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity() ;
    
}

void tetrisLoop(int value)
{
    glutPostRedisplay();
    tetris.quitar(piezaActual);
    piezaActual.mover(0, -1, 0);
    if (tetris.estaOcupado(piezaActual)) {
        piezaActual.mover(0, 1, 0);
        tetris.insertar(piezaActual);
        piezaActual=Pieza(rand() % MAX_SHAPES, tetris.getHeight());
        
    }
        glutTimerFunc(500, tetrisLoop, 0);
        tetris.insertar(piezaActual);
    
}

void CBInit()
{
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);

}

void displayInit()
{
    srand((unsigned int) time(0));
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0f, .3f, 3, 0, 0, 0, 0.0, 1, 0.0);
    glClearColor(1.0,1.0,1.0,1);
    tetris.insertar(piezaActual);
    glutTimerFunc(300, tetrisLoop, 0);

}



#endif
