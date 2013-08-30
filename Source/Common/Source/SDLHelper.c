#include <SDLHelper.h>

SDL_Surface *SDLH_LoadImage( const char *p_pFileName,
	const IMAGE_FORMAT p_Format, const COLOUR_KEY p_ColourKey )
{
	/* The image in memory and the converted image */
	SDL_Surface *pLoadedImage = NULL;
	SDL_Surface *pOptimisedImage = NULL;

	switch( p_Format )
	{
		case IMAGE_FORMAT_BMP:
		{
			pLoadedImage = SDL_LoadBMP( p_pFileName );
			break;
		}
		default:
		{
			printf( "Failed to load image %s | Unknown format\n",
				p_pFileName );
			return NULL;
		}
	}

	if( pLoadedImage )
	{
		pOptimisedImage = SDL_DisplayFormat( pLoadedImage );
		SDL_FreeSurface( pLoadedImage );
	}

	if( pOptimisedImage )
	{
		if( p_ColourKey.Use )
		{
			unsigned int ImageColourKey = SDL_MapRGB( pOptimisedImage->format,
				p_ColourKey.R, p_ColourKey.G, p_ColourKey.B );
			SDL_SetColorKey( pOptimisedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY,
				ImageColourKey );
		}
	}

	return pOptimisedImage;
}

void SDLH_ApplySurface( const int p_X, const int p_Y, SDL_Surface *p_pSource,
	SDL_Surface *p_pDestination, SDL_Rect *p_pClip )
{
	SDL_Rect Offset;
	Offset.x = p_X;
	Offset.y = p_Y;

	SDL_BlitSurface( p_pSource, p_pClip, p_pDestination, &Offset );
}

void SDLH_ClearColourKey( COLOUR_KEY p_ColourKey )
{
	memset( &p_ColourKey, 0x00, sizeof( COLOUR_KEY ) );
}

void SDLH_SetColourKey( COLOUR_KEY p_ColourKey, const char p_Red,
	const char p_Green, const char p_Blue )
{
	p_ColourKey.Use = 0x01;
	p_ColourKey.R = p_Red;
	p_ColourKey.G = p_Green;
	p_ColourKey.B = p_Blue;
}

