#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include "Timer.h"
#include "Functions.h"
#include "Stick_Figures.h"
#include "Clock.h"

//The music that will be played 
Mix_Music *bgm_voodoo = NULL;
std::ofstream out("Out.txt");
std::ofstream err("Error.txt");

void Terminate(void);

bool init()
{
	// Initialize SDL.
	if ( SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK ) < 0 )
    {
		err << "Couldn't initialize SDL: %s\n", SDL_GetError ();
		printf("Couldn't initialize SDL: %s\n", SDL_GetError ());
		exit (1);
	}
	atexit (Terminate);

	SDL_ShowCursor(SDL_DISABLE);

	// Set 320x240 16-bits video mode.
	screen = SDL_SetVideoMode ( 320, 240, 16, SDL_SWSURFACE );
	if (screen == NULL)
    {
		err << "Couldn't set 320x240x16 video mode: %s\n", SDL_GetError();
		printf("Couldn't set 320x240x16 video mode: %s\n", SDL_GetError());
		exit (2);
	}

	// Check and open joystick device.
	if (SDL_NumJoysticks() > 0)
    {
		joy = SDL_JoystickOpen(0);
		if(!joy)
        {
			err << "Couldn't open joystick 0: %s\n", SDL_GetError();
			printf("Couldn't open joystick 0: %s\n", SDL_GetError());
		}
	}
    
    //Initialize SDL_mixer 
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "StickMatch", NULL );
    
    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the music
    bgm_voodoo = Mix_LoadMUS( "../Media/Sounds/Jimmi Hendrix - VooDoo Child.ogg" );
    
    //If there was a problem loading the music
    if( bgm_voodoo == NULL )
    {
        err << "Sound: Jimmi Hendrix - VooDoo Child.wav did not load, check file.\n";
        printf("Sound: Jimmi Hendrix - VooDoo Child.wav did not load, check file.\n");
        return false;
    }
    else
    {
        printf("bgm_voodoo address: %p\n", &bgm_voodoo);
        }
    
    //Load the image
    introInt = load_image( "../Media/Graphics/Interactive Laboratories.bmp" );
    
    //If there was an error in loading the image
    if( introInt == NULL )
    {
        err << "Image: Interactive Laboratories.bmp did not load, check file.\n";
        printf("Image: Interactive Laboratories.bmp did not load, check file.\n");
        return false;    
    }
    
    else
    {
        printf("introInt address:   %p\n", &introInt);
        }
    
    //Load the image
    menu = load_image( "../Media/Graphics/Menu.bmp" );
    
    //If there was an error in loading the image
    if( menu == NULL )
    {
        err << "Image: Menu.bmp did not load, check file.\n";
        printf("Image: Menu.bmp did not load, check file.\n");
        return false;
    }

    else
    {
        printf("menu address:       %p\n", &menu);
        }
    
    //Load the image
    blueguy = load_image( "../Media/Graphics/Blue Animation.bmp" );
    
    //If there was an error in loading the image
    if( blueguy == NULL )
    {
        err << "Image: Blue Animation.bmp did not load, check file.\n";
        printf("Image: Blue Animation.bmp did not load, check file.\n");
        return false;
    }
    
    else
    {
        printf("blueguy address:    %p\n", &blueguy);
        }
    
    //Load the image
    redguy = load_image( "../Media/Graphics/Red Animation.bmp" );
    
    //If there was an error in loading the image
    if( redguy == NULL )
    {
        err << "Image: Blue Animation.bmp did not load, check file.\n";
        printf("Image: Blue Animation.bmp did not load, check file.\n");
        return false;
    }
    
    else
    {
        printf("redguy address:     %p\n", &redguy);
        }
    
    //Load the image
    background = load_image( "../Media/Graphics/Background.bmp" );
    
    //If there was an error in loading the image
    if( background == NULL )
    {
        err << "Image: Background.bmp did not load, check file.\n";
        printf("Image: Background.bmp did not load, check file.\n");
        return false;
    }
    
    else
    {
        printf("background address: %p\n", &background);
        }
    
    // Load the image
    s_WinText = load_image( "../Media/Graphics/WinText.bmp" );
    
    // If there was an error in loading the image...
    if(s_WinText == NULL)
    {
       err << "Image: Wintext.bmp did not load, check file.\n";
       printf("Image: Wintext.bmp did not load, check file.\n");
       return false;
    }
    
    else
    {
        printf("s_WinText address:  %p\n", &s_WinText);
        }
    
    // Load the image
    s_LoseText = load_image( "../Media/Graphics/LooseText.bmp" );
    
    // If there was an error in loading the image...
    if(s_LoseText == NULL)
    {
       err << "Image: Loosetext.bmp did not load, check file.\n";
       printf("Image: Loosetext.bmp did not load, check file.\n");
       return false;
    }
    
    else
    {
        printf("s_LoseText address: %p\n", &s_LoseText);
        }
    
    // Load the image
    One_Bar = load_image( "../Media/Graphics/One_Bar.bmp" );

    // If there was an error in loading the image...
    if(One_Bar == NULL)
    {
       err << "Image: One_Bar.bmp did not load, check file.\n";
       printf("Image: One_Bar.bmp did not load, check file.\n");
       return false;
    }
    
    else
    {
        printf("One_Bar address:    %p\n", &One_Bar);
        }
    
    // Load the image
    Full = load_image( "../Media/Graphics/Full.bmp" );

    // If there was an error in loading the image...
    if(Full == NULL)
    {
       err << "Image: Full.bmp did not load, check file.\n";
       printf("Image: Full.bmp did not load, check file.\n");
       return false;
    }
    
    else
    {
        printf("Full address:       %p\n", &Full);
        }
    
    //If everything loaded fine
    printf("All media files loaded sucessfully.\n");
    out << "All media files loaded sucessfully.\n";
    return true;  
}

void Terminate(void)
{
     delete Full;
     delete One_Bar;
     delete s_LoseText;
     delete s_WinText;
     delete background;
     delete redguy;
     delete blueguy;
     delete menu;
     delete screen;
     
     Mix_FreeMusic( bgm_voodoo );
     
     out << "Sucessful exit.\n";
     printf("Successful exit.\n");
     
     Mix_CloseAudio( );
     
     SDL_Quit();
#ifdef GP2X
       chdir("/usr/gp2x");
       execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
#endif
}

int main (int argc, char *argv[])
{
    //hw_set_cpu(200);
    printf("StickMatch has begun!\n");
    set_clips();

    //The frame rate regulator
    Timer fps;
	
    //Initialize
    if( init() == false )
    {
        return 1;    
    }
    
    //Load the files
    if( load_files() == false )
    {
        return 1;    
    }
    
    Mix_PlayMusic(bgm_voodoo, 1);
    
#ifdef GP2X
	SetClock( 250 );
#endif

#ifdef WIN32
	/* Only use Windows code here */
#endif

	while (!quit)
    {
        Mix_VolumeMusic(volume);
        //Start the frame timer
        fps.start();
		// Check for events.
		while (SDL_PollEvent (&event))
		{
            bluemade.handle_events();
			switch (event.type)
			{
				case SDL_KEYDOWN:
					// If Ctrl + C is pressed, terminate program.
					if ( (event.key.keysym.sym == SDLK_c) && (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) )
						quit = true;
					    break;
		        // If window ix 'X'ed, quit.
				case SDL_QUIT:
					quit = true;
					break;
				default:
					break;
			}
		}
		
		if( !b_menu )
		{
            Intro();
        }
        
        if( b_menu )
        {
            Menu();
        }

        if( b_MainLoop )
        {
            Main_Loop();
        }
        
        if( b_Win )
        {
            Reset();
            Winner();
        }
        
        if( b_Loose )
        {
            Reset();
            Looser();
        }
        
		//Update the screen
        if( SDL_Flip( screen ) == -1 )
        {
            return 1;    
        }

        //If we want to cap the frame rate
        if( Cap == true )
        {
            //While the frame time is not up
            while( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
            {
                //wait...    
            }
        }
	}
	Terminate();
	return 0;
}
