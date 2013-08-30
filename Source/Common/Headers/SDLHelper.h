#ifndef __STICKMATCH_SDLHELPER_H__
#define __STICKMATCH_SDLHELPER_H__

#include <SDL/SDL.h>

#pragma pack( 1 )
typedef struct __tagCOLOUR_KEY
{
	char Use;
	char R;
	char G;
	char B;
}COLOUR_KEY;
#pragma pack( )

typedef enum
{
	IMAGE_FORMAT_BMP
} IMAGE_FORMAT;

SDL_Surface *SDLH_LoadImage( const char *p_pFileName,
	const IMAGE_FORMAT p_Format, const COLOUR_KEY p_ColourKey );
void SDLH_ApplySurface( const int p_X, const int p_Y, SDL_Surface *p_pSource,
	SDL_Surface *p_pDestination, SDL_Rect *p_pClip );

void SDLH_ClearColourKey( COLOUR_KEY p_ColourKey );
void SDLH_SetColourKey( COLOUR_KEY p_ColourKey, const char p_Red,
	const char p_Green, const char p_Blue );

#endif

