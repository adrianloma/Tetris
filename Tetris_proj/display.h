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
//    float x = 3*sin(rotacion);
//    float z = 3*cos(rotacion);
//    gluLookAt(x, 0.3f, z, 0, 0, 0, 0.0, 1, 0.0);
    
    gluLookAt(0.0f, 3.0f, 0.5, 0, 0, 0, 0.0, 1, 0.0);


    


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
        piezaActual=Pieza(rand() % MAX_SHAPES, tetris.getHeight(), tetris.getWidth(), tetris.getDepth());
        //piezaActual=Pieza(TETRIS_SHAPE_HUGESQUARE, tetris.getHeight());
        tetris.checarCompletos();
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
}

void displayInit()
{
    glutDisplayFunc(display);
    srand((unsigned int) time(0));
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0.0f, .3f, 0.0, 0, 0, 0, 0.0, 1, 0.0);
    glClearColor(1.0,1.0,1.0,1);
    piezaActual=Pieza(rand() % MAX_SHAPES, tetris.getHeight(), tetris.getWidth(), tetris.getDepth());
    tetris.insertar(piezaActual);
    glutTimerFunc(300, tetrisLoop, 0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
//    GLfloat position[] = {
//                        static_cast<GLfloat>(tetris.getWidth() * tetris.getUnitWidth() / 2.0),
//                        static_cast<GLfloat>(tetris.getHeight() * tetris.getUnitWidth()),
//                        static_cast<GLfloat>(tetris.getDepth() *tetris.getUnitWidth() / 2.0), 1.0};
    GLfloat position[]=
    {
        0.0f, .5f, 0.5f
    };
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    

}

#endif
