#include <Game.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <stdio.h>
#include <unistd.h>

SDL_Surface	*g_pScreen = NULL;
SDL_Joystick *g_pJoyStick= NULL;

void Game_Terminate( void );

int InitialiseSDL( void )
{
	if( ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK )
		< 0 ) )
	{
		printf( "Failed to initialise SDL\n" );
		return 0;
	}

	SDL_ShowCursor( SDL_DISABLE );

	g_pScreen = SDL_SetVideoMode( 320, 240, 16, SDL_SWSURFACE );

	if( !g_pScreen )
	{	
		printf( "Failed to create SDL surface [320x240@16]\n" );
		return 0;
	}

	if( SDL_NumJoysticks( ) > 0 )
	{
		printf( "Found a joystick\n" );
		g_pJoyStick = SDL_JoystickOpen( 0 );

		if( !g_pJoyStick )
		{
			printf( "Non-fatal error, attempt to get joystick failed\n" );
		}
	}

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		printf( "Failed to open audio device\n" );
		return 0;
	}

	return 1;
}

void Game_Terminate( void )
{
	if( SDL_JoystickOpened( 0 ) )
	{
		SDL_JoystickClose( g_pJoyStick );
	}

	Mix_CloseAudio( );

	if( g_pScreen )
	{
		SDL_FreeSurface( g_pScreen );
	}

	SDL_Quit( );
}

int Game_Initialise( void )
{
	if( InitialiseSDL( ) == 0 )
	{
		printf( "Failed to initialise SDL\n" );
		Game_Terminate( );
		return 0;
	}

	return 1;
}

int Game_Execute( void )
{
	sleep( 3 );

	Game_Terminate( );

	return 1;
}

