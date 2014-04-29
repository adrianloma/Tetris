#ifndef Tetris_proj_display_h
#define Tetris_proj_display_h

#include <cmath>
#include <stdlib.h>
#include <time.h>


const int INICIO = 0, JUEGO = 1, FINAL = 2, SALIR = 3, CONTROLES = 4;

int estado = INICIO;
bool pausado = false, terminar = false;
int score;
int angulo = 0;
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

void luces(){

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(estado == INICIO)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        glColor3f(1.0f, 1.0f, 1.0f);
        
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
        glPushMatrix();
        glRotatef(angulo, 0.0, 0.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glScalef(12*1.178, 12, 1);
        
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(-1.0f/10, -1.0f/10);
        
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f( 1.0f/10, -1.0f/10);
        
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f( 1.0f/10, 1.0f/10);
        
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(-1.0f/10, 1.0f/10);
        glEnd();
        
        glPopMatrix();
        
        glMatrixMode(GL_TEXTURE);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        
        glDisable(GL_TEXTURE_2D);

        escribirCentrado("TETRIS", 0, 0);
        escribirCentrado("Adrian Lozano    A00812725", 0, -.15);
        escribirCentrado("Alfredo Altamirano    A01191157", 0, -.3);
        escribirCentrado("Presiona j para jugar.", 0, -.5);
        escribirCentrado("Presiona i para ver los controles.", 0, -.7);
    } else if(estado == JUEGO)
    {
        luces();
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

void reshape (int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,1,-1,1, 2, 20);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

void rotacionTextura(int value)
{
    angulo = (angulo + 1) % 360;
    if(estado == INICIO)
    {
        glutTimerFunc(30, rotacionTextura, 0);
    }
    glutPostRedisplay();
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
    glClearColor(.3, 0.2 , 0.8 ,1);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    //gluLookAt(0.0f, .3f, 0.0, 0, 0, 0, 0.0, 1, 0.0);
    glutTimerFunc(300, tetrisLoop, 0);

    /*
     ####### LUCES #######
     */
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); //para eliminar las caras ocultas
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    

    
    
    score = 0;
    rotacion = 0;
    vista = 1;
    tetris = Tetris(5, 20, 5, .2f);
    score = 0;
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

void loadTexture(Image* image)
{
    glGenTextures(1, &texture); //Make room for our texture
    glBindTexture(GL_TEXTURE_2D, texture); //Tell OpenGL which texture to edit
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}

void initTextures()
{
    glEnable(GL_TEXTURE_2D);
    Image* image = loadBMP("/Users/alfredo_altamirano/Documents/Tetris/Tetris/textures/tetris.bmp");
    loadTexture(image);
    delete image;
}

void displayInit()
{
    glutDisplayFunc(display);
    glutTimerFunc(10, rotacionTextura, 0);
    srand((unsigned int) time(0));
    initMenu();
    glClearColor(.5, .5 , 1.0 ,1);
    initTextures();
}

#endif
