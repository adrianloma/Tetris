#ifndef Tetris_proj_display_h
#define Tetris_proj_display_h

#include <cmath>
#include <stdlib.h>
#include <time.h>

const int INICIO = 0, JUEGO = 1, FINAL = 2, SALIR = 3;

int estado = INICIO;
bool pausado = false;
int score;

int vista;

void draw3dString (void *font, char *s, float x, float y, float z) ;

void escribirCentrado(string mensaje, float x, float y)
{
    glRasterPos2f(x - .01 * (int)mensaje.length(), y);
    for(int i = 0; i < mensaje.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mensaje[i]);
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(estado == INICIO)
    {
        glColor3f(0, 0, 0);
        escribirCentrado("TETRIS", 0, 0);
        escribirCentrado("Adrian Lozano    A00812725", 0, -.15);
        escribirCentrado("Alfredo Altamirano    A01191157", 0, -.3);
        escribirCentrado("Presiona J para jugar.", 0, -.5);
    } else if(estado == JUEGO)
    {
        tetris.dibuja();
    
        //glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        if(vista == 1)
        {
            float x = 3*sin(rotacion);
            float z = 3*cos(rotacion);
            gluLookAt(x, 0.3f, z, 0, 0, 0, 0.0, 1, 0.0);
        } else if(vista == 2)
        {
            gluLookAt(0.0f, 3.0f, 0.5, 0, 0, 0, 0.0, 1, 0.0);
        }
    } else if (estado == FINAL) {
        glColor3f(0, 0, 0);
        escribirCentrado("GAME OVER", 0, 0);
        escribirCentrado("Presiona J para volver a jugar.", 0, -.5);
    }

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
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1, 2, 20);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

void tetrisLoop(int value)
{
    if(pausado)
    {
        return;
    }
    glutPostRedisplay();
    tetris.quitar(piezaActual);
    piezaActual.mover(0, -1, 0);
    if (tetris.estaOcupado(piezaActual))
    {
        piezaActual.mover(0, 1, 0);
        tetris.insertar(piezaActual);
        piezaActual=Pieza(rand() % MAX_SHAPES, tetris.getHeight(), tetris.getWidth(), tetris.getDepth());
        piezaActual.mover(0, -1, 0);
        if(tetris.estaOcupado(piezaActual))
        {
            estado = FINAL;
            return;
        }
        piezaActual.mover(0, 1, 0);
        //piezaActual=Pieza(TETRIS_SHAPE_HUGESQUARE, tetris.getHeight());
        int niveles = tetris.checarCompletos();
        if(niveles)
        {
            score += niveles*(100 + time(NULL)%100);
            cout << score << endl;
        }
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

void init3d()
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0.0f, .3f, 0.0, 0, 0, 0, 0.0, 1, 0.0);
    glutTimerFunc(300, tetrisLoop, 0);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    GLfloat position[] = {
        static_cast<GLfloat>(tetris.getWidth() * tetris.getUnitWidth() / 2.0),
        static_cast<GLfloat>(tetris.getHeight() * tetris.getUnitWidth()),
        static_cast<GLfloat>(tetris.getDepth() *tetris.getUnitWidth() / 2.0), 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    score = 0;
    rotacion = 0;
    vista = 1;
    tetris = Tetris(5, 20, 5, .2f);
    piezaActual=Pieza(rand() % MAX_SHAPES, tetris.getHeight(), tetris.getWidth(), tetris.getDepth());
    tetris.insertar(piezaActual);
}

const int REINICIAR = 0, PAUSA = 1, RESUMIR = 2;

void menu(int opcion) {
	switch(opcion) {
        case REINICIAR:
            init3d();
            break;
        case PAUSA:
            pausado = true;
            break;
        case RESUMIR:
            pausado = false;
            glutTimerFunc(500, tetrisLoop, 0);
            break;
        case SALIR:
            endProg();
    }
	glutPostRedisplay();
}

void initMenu()
{
    int menuPrincipal;
    
	menuPrincipal = glutCreateMenu(menu);
	glutAddMenuEntry("Reiniciar", REINICIAR);
	glutAddMenuEntry("Pausa", PAUSA);
	glutAddMenuEntry("Resumir", RESUMIR);
    glutAddMenuEntry("Salir", SALIR);
    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void displayInit()
{
    glutDisplayFunc(display);
    srand((unsigned int) time(0));
    initMenu();
    glClearColor(1.0,1.0,1.0,1);
}

#endif
