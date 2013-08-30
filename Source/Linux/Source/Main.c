#include <stdio.h>
#include <Game.h>

int main( int p_Argc, char **p_ppArgv )
{
	if( Game_Init( ) == 0 )
	{
		printf( "Failed to initialise the game\n" );
		return 1;		
	}

	return Game_Execute( );
}

