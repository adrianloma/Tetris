//
//  sound.h
//  Tetris_proj
//
//  Created by Adrian Lozano on 3/20/14.
//  Copyright (c) 2014 Adrian Lozano. All rights reserved.
//

#ifndef Tetris_proj_sound_h
#define Tetris_proj_sound_h

float volume;
HSTREAM music;


void soundInit()
{
    
    int device = -1; // Default Sounddevice
    DWORD freq = 44100; // Sample rate (Hz)
    //HSTREAM streamHandle; // Handle for open stream
    
    /* Initialize output device */
    BASS_Init(device, freq, 0, 0, NULL);
    
    volume=0.5f;
    if(!(music = BASS_StreamCreateFile(FALSE, "resources/sounds/test.mp3", 0, 0, BASS_SAMPLE_LOOP)))
    {
        std::cout<<"Error code: " << BASS_ErrorGetCode();
        endProg();
    }
    BASS_ChannelPlay(music, FALSE);
    BASS_Pause();
    
    
    
}


#endif
