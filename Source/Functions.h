// In here there are misc. functions that perform most of the background work.

// This converts an image into the correct format.
SDL_Surface *load_image( std::string filename ) 
{
    //Temporary storage for the image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = SDL_LoadBMP( filename.c_str() );

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );
        
        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //If the image was optimized just fine
    if( optimizedImage != NULL )
    {
        //Map the color key
        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
        
        //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
        SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );
    }

    //Return the optimized image
    return optimizedImage;
}

// A converter to display the images at the correct placement on screen.
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, clip, destination, &offset );
}
