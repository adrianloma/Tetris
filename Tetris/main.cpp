#include <cstdio>
#include <cstdlib>
#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenAL/al.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdlib.h>
#include "Tetris.h"

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1

ALfloat listenerPos[]={0.0,0.0,4.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};

ALfloat source0Pos[]={ -2.0, 0.0, 0.0};
ALfloat source0Vel[]={ 0.0, 0.0, 0.0};

ALuint  buffer[NUM_BUFFERS];
ALuint  source[NUM_SOURCES];
ALuint  environment[NUM_ENVIRONMENTS];

ALsizei size,freq;
ALenum  format;
ALvoid  *data;

Tetris tetris(10, 10, 10, .2f); //width, height, depth, square width

void initGL(void)
{
    glEnable(GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 10);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 3, 0, 0, 0, 0.0, 1, 0.0);
    Pieza p;
    p.posiciones.push_back(Point(5, 9, 5));
    p.cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
    p.posiciones.push_back(Point(4, 9, 5));
    p.cuadritos.push_back(Cuadrito(Color(1, 1, 0, 1)));
    p.posiciones.push_back(Point(6, 9, 5));
    p.cuadritos.push_back(Cuadrito(Color(0, 1, 1, 1)));
    p.posiciones.push_back(Point(5, 9, 4));
    p.cuadritos.push_back(Cuadrito(Color(0, 0, 1, 1)));
    p.posiciones.push_back(Point(5, 9, 6));
    p.cuadritos.push_back(Cuadrito(Color(0, 1, 0, 1)));
    p.posiciones.push_back(Point(5, 8, 5));
    p.cuadritos.push_back(Cuadrito(Color(1, 0, 1, 1)));
    tetris.insertar(p);
}

void tetrisLoop(int value)
{
    glutPostRedisplay();
    glutTimerFunc(2000, tetrisLoop, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tetris.dibuja();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
            
    }
    glutPostRedisplay();
}

void playSound()
{
    alListenerfv(AL_POSITION, listenerPos);
    alListenerfv(AL_VELOCITY, listenerVel);
    alListenerfv(AL_ORIENTATION, listenerOri);
    
    alGetError();
    
    alGenBuffers(NUM_BUFFERS, buffer);
    
    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating buffers.\n");
        exit(1);
    }
    
    alutLoadWAVFile("sound.wav",&format,&data,&size,&freq);
    alBufferData(buffer[0],format,data,size,freq);
    alutUnloadWAV(format,data,size,freq);
    
    alGetError(); /* clear error */
    alGenSources(NUM_SOURCES, source);
    
    if(alGetError() != AL_NO_ERROR)
    {
        printf("- Error creating sources !!\n");
        exit(2);
    }
    else
    {
        printf("init - no errors after alGenSources\n");
    }
    
    alSourcef(source[0], AL_PITCH, 1.0f);
    alSourcef(source[0], AL_GAIN, 1.0f);
    alSourcefv(source[0], AL_POSITION, source0Pos);
    alSourcefv(source[0], AL_VELOCITY, source0Vel);
    alSourcei(source[0], AL_BUFFER,buffer[0]);
    alSourcei(source[0], AL_LOOPING, AL_TRUE);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    playSound();
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(3000, tetrisLoop, 0);
    glutMainLoop();
    return 0;
}