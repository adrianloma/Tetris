#ifndef Tetris_proj_display_h
#define Tetris_proj_display_h

#include <cmath>
#include <stdlib.h>
#include <time.h>

const int INICIO = 0, JUEGO = 1, FINAL = 2, SALIR = 3, CONTROLES = 4;

int estado = INICIO;
bool pausado = false, terminar = false;
int score;
GLuint texture;

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
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glutSolidSphere(2, 10, 10);
        glDisable(GL_TEXTURE_2D);
        glColor3f(0, 0, 0);
        escribirCentrado("TETRIS", 0, 0);
        escribirCentrado("Adrian Lozano    A00812725", 0, -.15);
        escribirCentrado("Alfredo Altamirano    A01191157", 0, -.3);
        escribirCentrado("Presiona j para jugar.", 0, -.5);
        escribirCentrado("Presiona i para ver los controles.", 0, -.7);
    } else if(estado == JUEGO)
    {
        tetris.dibuja();
        
        string sc = "";
        int s = score;
        if(!s)
        {
            sc = "0";
        }
        while(s)
        {
            sc = string(1, (char)(s%10 + '0')) + sc;
            s /= 10;
        }
        escribirCentrado("Puntaje: " + sc, 1.5, .75);
    
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
        escribirCentrado("Presiona j para volver a jugar.", 0, -.5);
    } else if (estado == CONTROLES) {
        glColor3f(0, 0, 0);
        escribirCentrado("Controles", 0, .9);
        escribirCentrado("a - rotar la vista a la izquierda (solo con la vista 1)", 0, .7);
        escribirCentrado("d - rotar la vista a la derecha (solo con la vista 1)", 0, .6);
        escribirCentrado("s - detener la musica", 0, .5);
        escribirCentrado("p - pausar la musica", 0, .4);
        escribirCentrado("P - resumir la musica", 0, .3);
        escribirCentrado("r - reiniciar la musica", 0, .2);
        escribirCentrado("E - salir", 0, .1);
        escribirCentrado("SPACE - mover la pieza hasta abajo", 0, 0);
        escribirCentrado("y - rotar ???", 0, -.1);
        escribirCentrado("u - rotar ???", 0, -.2);
        escribirCentrado("h - rotar ???", 0, -.3);
        escribirCentrado("j - rotar ???", 0, -.4);
        escribirCentrado("1 - cambiar a la vista 1", 0, -.5);
        escribirCentrado("2 - cambiar a la vista 2", 0, -.6);
        escribirCentrado("Presiona v para volver.", 0, -.8);

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
    
    if(terminar)
    {
        terminar = false;
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
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
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
    glEnable(GL_DEPTH_TEST); //para eliminar las caras ocultas
    glEnable(GL_NORMALIZE);
    /*
     ####### LUCES #######
     */
    GLfloat position[] = {
                        static_cast<GLfloat>(tetris.getWidth() * tetris.getUnitWidth() / 4.0),
                        static_cast<GLfloat>(tetris.getHeight()),
                        static_cast<GLfloat>(tetris.getDepth() *tetris.getUnitWidth() / 4.0), 0.0};
    //luz direccional
//    GLfloat position[]=
//    {
//        0.1f, 3.0f, 0.1f
//    };
    
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE,lightIntensity);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    GLfloat direction[ ] = {(GLfloat)(tetris.getWidth()*tetris.getUnitWidth()/2.0),
                            0.0,
                            (GLfloat)(tetris.getWidth()*tetris.getUnitWidth()/2.0)};
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
    GLfloat thetaLight = 45.0;
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, thetaLight);
    score = 127;
    rotacion = 0;
    vista = 1;
    tetris = Tetris(5, 20, 5, .2f);
    piezaActual = Pieza(rand() % MAX_SHAPES, tetris.getHeight(), tetris.getWidth(), tetris.getDepth());
    tetris.insertar(piezaActual);
}

const int REINICIAR = 0, PAUSA = 1, RESUMIR = 2;

void menu(int opcion) {
	switch(opcion) {
        case REINICIAR:
            init3d();
            terminar = true;
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

void initTextures()
{
    Image* image;
    
    image = loadBMP("/Users/alfredo_altamirano/Documents/Tetris/Tetris/textures/textura.jpg");

    
    glBindTexture(GL_TEXTURE_2D, texture); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    
    delete image;
}

void displayInit()
{
    glutDisplayFunc(display);
    srand((unsigned int) time(0));
    initMenu();
    glClearColor(1.0,1.0,1.0,1);
    initTextures();
}

#endif
