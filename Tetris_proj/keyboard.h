

#ifndef Tetris_proj_keyboard_h
#define Tetris_proj_keyboard_h





void keyboardListener(unsigned char key, int mouseX, int mouseY)
{
    
    switch (key)
    {
        case 'w':
            //rotacion
            break;
        case 'a':
            rotacion-=.1;
            glutPostRedisplay();
            break;
        case 'd':
            rotacion+=.1;
            glutPostRedisplay();
            break;
        case 's':
            BASS_Stop();
            break;
        case 'p':
            BASS_Pause();
            break;
        case 'P':
            BASS_Start();
            break;
        case 'r':
            BASS_Start();
            BASS_ChannelPlay(music, true);
            break;
        case 'E':
            endProg();
            break;
        case ' ':
            while (mover(piezaActual, 0, -1, 0)) {}
            break;
        case 'y':
            rotateCCW(piezaActual);
            break;
        case 'u':
            rotateCW(piezaActual);
            break;
        case 'h':
            barrelCCW(piezaActual);
            break;
        case 'j':
            barrelCW(piezaActual);
            break;
        default:
            break;
    }
}

void specialKeyboardListener(int key, int mouseX, int mouseY)
{
    switch (key) {
        case GLUT_KEY_DOWN:
            mover(piezaActual, 0, 0, 1);
            break;
        case GLUT_KEY_UP:
            mover(piezaActual, 0, 0, -1);
            break;
        case GLUT_KEY_LEFT:
            mover(piezaActual, -1, 0, 0);
            break;
        case GLUT_KEY_RIGHT:
            mover(piezaActual, 1, 0, 0);
            break;
        default:
            break;

    }
    /*
    BASS_ChannelSetAttribute(music, BASS_ATTRIB_VOL, volume);
     case GLUT_KEY_DOWN:
     if (volume >= 0.1)
     {
     volume -= 0.1;
     }
     break;
     case GLUT_KEY_UP:
     if (volume <= .9) {
     volume += 0.1;
     }*/
}

void KBinit()
{
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyboardListener);
}


#endif
