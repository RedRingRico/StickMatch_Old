// GP2X button mapping.
enum MAP_KEY
{
	GP2X_UP         , // 0
	GP2X_UP_LEFT    , // 1
	GP2X_LEFT       , // 2
	GP2X_DOWN_LEFT  , // 3
	GP2X_DOWN       , // 4
	GP2X_DOWN_RIGHT , // 5
	GP2X_RIGHT      , // 6
	GP2X_UP_RIGHT   , // 7
	GP2X_START      , // 8
	GP2X_SELECT     , // 9
	GP2X_FL         , // 10
	GP2X_FR         , // 11
	GP2X_FA         , // 12
	GP2X_FB         , // 13
	GP2X_FX         , // 14
	GP2X_FY         , // 15
	GP2X_VOL_UP     , // 16
	GP2X_VOL_DOWN   , // 17
	GP2X_TAT          // 18
};

// The frames per second.
const int FRAMES_PER_SECOND = 30;
bool Cap = true;

// Volume level.
int volume = 20;

// Called for the quitting of the game.
bool quit = false;

// The generic stick figure vaiables.
const int STICK_WIDTH = 78;
const int STICK_HEIGHT = 175;

// For collisions.
const int SCREEN_WIDTH = 320;
const int SCREEN_HEIGHT = 240;

// The direction status of the stick figure.
const int STICK_RIGHT = 0;
const int STICK_LEFT = 1;
const int STICK_PUNCH_R = 2;
const int STICK_PUNCH_L = 3;

int Blue_Health = 100;
int Red_Health = 100;

int blue_velocity;
int red_velocity;

// The areas of the stick's sprite sheet.
SDL_Rect ClipsRight[ 12 ];
SDL_Rect ClipsLeft[ 12 ];
SDL_Rect ClipsPunchR[ 16 ];
SDL_Rect ClipsPunchL[ 16 ];

/* The screen surface,
       red stick figure,
       blue stick figure,
       menu splash,
       intro splash,
       winner text,
       looser text,
       health status bar.
*/
SDL_Surface *screen = NULL;
SDL_Surface *introInt = new SDL_Surface;
SDL_Surface *menu = new SDL_Surface;
SDL_Surface *blueguy = new SDL_Surface;
SDL_Surface *redguy = new SDL_Surface;
SDL_Surface *background = new SDL_Surface;
SDL_Surface *s_WinText = new SDL_Surface;
SDL_Surface *s_LoseText = new SDL_Surface;
SDL_Surface *One_Bar = new SDL_Surface;
SDL_Surface *Full = new SDL_Surface;

// The collision boxes.
SDL_Rect blue_box;
SDL_Rect red_box;

// Set up the joystick.
SDL_Joystick *joy = NULL;

// The event variable.
SDL_Event event;

// Win/loose/continue status.
bool b_Win = false;
bool b_Loose = false;

// Are we in the menu or the main loop?
bool b_menu = false;
bool b_MainLoop = false;

// Who's punching?
bool blue_punch = false;
bool red_punch = false;

// Are we facing the left or the right?
bool face_left = false;
bool face_right = true;

// The main loop's prototype.
void Main_Loop();

bool check_collision(SDL_Rect &A, SDL_Rect &B)
{
     // The sides of the rectangles
     int leftA, leftB;
     int rightA, rightB;
     int topA, topB;
     int bottomA, bottomB;
     
     // Calculate the sides of the blue stick
     leftA = A.x;
     rightA = A.x + A.w;
     topA = A.y;
     bottomA = A.y + A.h;
     
     // Claculate the sides of the red stick
     leftB = B.x;
     rightB = B.x + B.w;
     topB = B.y;
     bottomB = B.y + B.h;
     
     // If any sides are outside the red stick
     if (bottomA <= topB)
     {
                 return false;
     }
     
     if(topA >= bottomB)
     {
             return false;
     }
     
     if(rightA <= leftB)
     {
               return false;
     }

     if(leftA >= rightB)
     {
               return false;
     }
     
     return true;
}

// The blue stick figure.
class BlueStick
{
    private:    
    // Its frame.
    int frame;
    
    // The punch frame.
    int punchframe;

    public:
    // Initialises the variables.
    BlueStick();
    
    // Health ststus.
    void Health_Status();
    
    // Handles input.
    void handle_events();
    
    // Shows the stick figure.
    void show();

    // The offset.
    int offSet;

    // The animation status.
    int status;
};

BlueStick::BlueStick()
{ 
    // Initialize movement variables.
    offSet = 0;
    blue_velocity = 0;
    
    // Initialize animation variables.
    frame = 0;
    punchframe = 0;
    status = STICK_RIGHT;
}

void BlueStick::Health_Status()
{
     // Here come the if statements!
     if( Blue_Health <= 100 )
     {
         apply_surface( 5, 3, Full, screen, NULL );
     }
     if( Blue_Health <= 99 )
     {
         apply_surface( 104, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 98 )
     {
         apply_surface( 103, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 97 )
     {
         apply_surface( 102, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 96 )
     {
         apply_surface( 101, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 95 )
     {
         apply_surface( 100, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 94 )
     {
         apply_surface( 99, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 93 )
     {
         apply_surface( 98, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 92 )
     {
         apply_surface( 97, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 91 )
     {
         apply_surface( 96, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 90 )
     {
         apply_surface( 95, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 89 )
     {
         apply_surface( 94, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 88 )
     {
         apply_surface( 93, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 87 )
     {
         apply_surface( 92, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 86 )
     {
         apply_surface( 91, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 85 )
     {
         apply_surface( 90, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 84 )
     {
         apply_surface( 89, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 83 )
     {
         apply_surface( 88, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 82 )
     {
         apply_surface( 87, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 81 )
     {
         apply_surface( 86, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 80 )
     {
         apply_surface( 85, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 79 )
     {
         apply_surface( 84, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 78 )
     {
         apply_surface( 83, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 77 )
     {
         apply_surface( 82, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 76 )
     {
         apply_surface( 81, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 75 )
     {
         apply_surface( 80, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 74 )
     {
         apply_surface( 79, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 73 )
     {
         apply_surface( 78, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 72 )
     {
         apply_surface( 77, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 71 )
     {
         apply_surface( 76, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 70 )
     {
         apply_surface( 75, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 69 )
     {
         apply_surface( 74, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 68 )
     {
         apply_surface( 73, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 67 )
     {
         apply_surface( 72, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 66 )
     {
         apply_surface( 71, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 65 )
     {
         apply_surface( 70, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 64 )
     {
         apply_surface( 69, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 63 )
     {
         apply_surface( 68, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 62 )
     {
         apply_surface( 67, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 61 )
     {
         apply_surface( 66, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 60 )
     {
         apply_surface( 65, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 59 )
     {
         apply_surface( 64, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 58 )
     {
         apply_surface( 63, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 57 )
     {
         apply_surface( 62, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 56 )
     {
         apply_surface( 61, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 55 )
     {
         apply_surface( 60, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 54 )
     {
         apply_surface( 59, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 53 )
     {
         apply_surface( 58, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 52 )
     {
         apply_surface( 57, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 51 )
     {
         apply_surface( 56, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 50 )
     {
         apply_surface( 55, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 49 )
     {
         apply_surface( 54, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 48 )
     {
         apply_surface( 53, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 47 )
     {
         apply_surface( 52, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 46 )
     {
         apply_surface( 51, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 45 )
     {
         apply_surface( 50, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 44 )
     {
         apply_surface( 49, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 43 )
     {
         apply_surface( 48, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 42 )
     {
         apply_surface( 47, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 41 )
     {
         apply_surface( 46, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 40 )
     {
         apply_surface( 45, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 39 )
     {
         apply_surface( 44, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 38 )
     {
         apply_surface( 43, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 37 )
     {
         apply_surface( 42, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 36 )
     {
         apply_surface( 41, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 35 )
     {
         apply_surface( 40, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 34 )
     {
         apply_surface( 39, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 33 )
     {
         apply_surface( 38, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 32 )
     {
         apply_surface( 37, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 31 )
     {
         apply_surface( 36, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 30 )
     {
         apply_surface( 35, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 29 )
     {
         apply_surface( 34, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 28 )
     {
         apply_surface( 33, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 27 )
     {
         apply_surface( 32, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 26 )
     {
         apply_surface( 31, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 25 )
     {
         apply_surface( 30, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 24 )
     {
         apply_surface( 29, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 23 )
     {
         apply_surface( 28, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 22 )
     {
         apply_surface( 27, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 21 )
     {
         apply_surface( 26, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 20 )
     {
         apply_surface( 25, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 19 )
     {
         apply_surface( 24, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 18 )
     {
         apply_surface( 23, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 17 )
     {
         apply_surface( 22, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 16 )
     {
         apply_surface( 21, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 15 )
     {
         apply_surface( 20, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 14 )
     {
         apply_surface( 19, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 13 )
     {
         apply_surface( 18, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 12 )
     {
         apply_surface( 17, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 11 )
     {
         apply_surface( 16, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 10 )
     {
         apply_surface( 15, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 9 )
     {
         apply_surface( 14, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 8 )
     {
         apply_surface( 13, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 7 )
     {
         apply_surface( 12, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 6 )
     {
         apply_surface( 11, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 5 )
     {
         apply_surface( 10, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 4 )
     {
         apply_surface( 9, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 3 )
     {
         apply_surface( 8, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 2 )
     {
         apply_surface( 7, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 1 )
     {
         apply_surface( 6, 3, One_Bar, screen, NULL );
     }
     if( Blue_Health <= 0 )
     {
         apply_surface( 5, 3, One_Bar, screen, NULL );
         b_Loose = true;
     }
}

void BlueStick::handle_events()
{
    // If a GP2X button is pressed or a stick positioned...
    if( event.type == SDL_JOYBUTTONDOWN )
    {
        switch( event.jbutton.button )
                if( b_Win == false || b_Loose == false )
                {
                    case GP2X_RIGHT:
                         blue_velocity += STICK_WIDTH / 8;
                         break;
                    
                    case GP2X_LEFT:
                         blue_velocity -= STICK_WIDTH / 8;
                         break;
                    
                    case GP2X_FX:
                         if( blue_punch == false )
                         {
                             blue_punch = true;
                         }
                         break;
                }
                
                if( b_Win == true )
                {
                    switch( event.jbutton.button )
                    {
                            case GP2X_FX:
                                 b_Win = false;
                                 b_MainLoop = false;
                                 break;
                            
                            case GP2X_FB:
                                 quit = true;
                                 break;
                    }
                }
                
                if( b_Loose == true )
                {
                    switch( event.jbutton.button )
                    {
                            case GP2X_FX:
                                 b_Loose = false;
                                 b_MainLoop = false;
                                 break;
                            
                            case GP2X_FB:
                                 quit = true;
                                 break;
                    }
                }
        
    }
    
    // If a GP2X button/stick was released...
    else if( event.type == SDL_JOYBUTTONUP )
    {
        switch( event.jbutton.button )
        {
            // Set the velocity
            case GP2X_RIGHT:
                 blue_velocity -= STICK_WIDTH / 8;
                 break;
            
            case GP2X_LEFT:
                 blue_velocity += STICK_WIDTH / 8;
                 break;
                    case GP2X_VOL_UP:
                         if(volume <= 0)
                         {
                                   volume = 1;
                         }                         
                         volume += 2;
                         break;
                    case GP2X_VOL_DOWN:
                         volume -= 2;
                         break;
        }
    }
    
    // If a key was pressed...
    if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        if( b_Win == false || b_Loose == false )
        {
            // Set the velocity
            case SDLK_RIGHT:
                 blue_velocity += STICK_WIDTH / 8;
                 break;
            
            case SDLK_LEFT:
                 blue_velocity -= STICK_WIDTH / 8;
                 break;
                 
            case SDLK_x:
                 if( blue_punch == false )
                 {
                     blue_punch = true;
                 }
                 break;
        }
        
        if(b_Win == true)
        {
            switch( event.key.keysym.sym )
            {
                 case SDLK_x:
                      b_Win = false;
                      b_MainLoop = false;
                      break;
                 case SDLK_b:
                      quit = true;
                      break;
            }
        }
        
        if(b_Loose == true)
        {
            switch( event.key.keysym.sym )
            {
                 case SDLK_x:
                      b_Loose = false;
                      b_MainLoop = false;
                      break;
                 case SDLK_b:
                      quit = true;
                      break;
            }
        }
    }
    // If a key was released...
    else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            // Set the velocity
            case SDLK_RIGHT:
                 blue_velocity -= STICK_WIDTH / 8;
            break;
            
            case SDLK_LEFT:
                 blue_velocity += STICK_WIDTH / 8;
            break;
        }
    }
}

void BlueStick::show()
{
     // The collision box.
     blue_box.x += blue_velocity;
     blue_box.y = SCREEN_HEIGHT - STICK_HEIGHT;
     blue_box.w = STICK_WIDTH;
     blue_box.h = STICK_HEIGHT;
     
    // Move.
    offSet += blue_velocity;
    
    // Keep the figure in bounds.
    if( ( offSet < 0 ) || ( offSet + STICK_WIDTH > SCREEN_WIDTH ) )
    {
        offSet -= blue_velocity;
        blue_box.x -= blue_velocity;   
    }
    
    if((blue_box.x < 0 ) || ( blue_box.x + STICK_WIDTH > SCREEN_WIDTH ))
    {
        blue_box.x -= blue_velocity;
    }
    
    // If the player is moving left...
    if( blue_velocity < 0 )
    {
        face_right = false;
        face_left = true;
        if( blue_punch == false )
        {
            // Set the animation to left.
            status = STICK_LEFT;
        
            // Move to the next frame in the animation.
            frame++;
        }
        
        if( blue_punch == true)
        {
            // Set the animation to be punching left.
            status = STICK_PUNCH_L;
            
            // Move to the next frame in the animation.
            punchframe++;
        }
    }
    
    // If the player is moving right...
    else if( blue_velocity > 0 )
    {
         face_right = true;
         face_left = false;
         
         if( blue_punch == false )
         {
             // Set the animation to right.
             status = STICK_RIGHT;
        
             // Move to the next frame in the animation.
             frame++;
        }
        
        if( blue_punch == true)
        {
            status = STICK_PUNCH_R;
            punchframe++;
        }
    }
    
    else if( blue_velocity == 0 )
    {
         // While idle, reset the walk animation.
         frame = 0;
         
         // If the user pressed the punch button...
         if( blue_punch == true )
         {
             // While the stick figure is facing right, set the status of the punch
             // animation to the right, too.
             if( face_right == true )
             {
                  status = STICK_PUNCH_R;
             }
             // Replace 'right' with 'left'.
             else if(face_right == false )
             {
                  status = STICK_PUNCH_L;
             }
             // Increase the punch counter for the animation.
             punchframe++;
         }
    }
    
    if(check_collision(blue_box, red_box))
    {
         if( event.type == SDL_KEYDOWN )
         {
             switch( event.key.keysym.sym )
             {
                     // Make sure the animation is correct before issuing a health deduction.               
            case SDLK_x:
                 if(punchframe == 8)
                 {
                               srand( time( 0 ) ); 
                               int randomNum = rand();
    
                               int HealthDown = (randomNum % 10) + 1;
                               Red_Health -= HealthDown;
                 }
                 break;
              }
        }
        
        if( event.type == SDL_JOYBUTTONDOWN )
        {
            switch( event.jbutton.button )
            {
                    case GP2X_FX:
                         if(punchframe == 8)
                         {
                                       srand( time( 0 ) ); 
                                       int randomNum = rand();
    
                                       int HealthDown = (randomNum % 10) + 1;
                                       Red_Health -= HealthDown;
                         }
                         break;
             }
        }
                         
        
        if( event.type == SDL_KEYUP)
        {
            switch( event.key.keysym.sym )
            {
                    // Set the velocity                 
                    case SDLK_x:
                         if(punchframe == 8)
                         {
                                       srand( time( 0 ) ); 
                                       int randomNum = rand();
    
                                       int HealthDown = (randomNum % 10) + 1;
                                       Red_Health -= HealthDown;
                          }
                          break;
            }
        }
    

        if( event.type == SDL_JOYBUTTONUP )
        {
            switch( event.jbutton.button )
            {
                    case GP2X_FX:
                         if(punchframe == 8)
                         {
                                       srand( time( 0 ) ); 
                                       int randomNum = rand();
    
                                       int HealthDown = (randomNum % 10) + 1;
                                       Red_Health -= HealthDown;
                         }
                         break;
             }
        }
    }
    
    // Loop the animation.
    if( frame >= 12 )
    {
        frame = 0;
    }
    
    if( punchframe >= 14 )
    {
         punchframe = 0;
         blue_punch = false;
    }
    
    // Show the stick figure.
    if( status == STICK_RIGHT )
    {
        apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, blueguy, screen, &ClipsRight[ frame ] );
    }
    else if( status == STICK_LEFT )
    {
        apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, blueguy, screen, &ClipsLeft[ frame ] );
    }
    else if( status == STICK_PUNCH_R )
    {
         apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, blueguy, screen, &ClipsPunchR[ punchframe ] );
    }
    else if( status == STICK_PUNCH_L )
    {
         apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, blueguy, screen, &ClipsPunchL[ punchframe ] );
    }
}

// The red stick figure
class RedStick
{
    private:    
    // Its current frame.
    int frame;
    
    int red_punchframe;

    public:
    // Initializes the variables.
    RedStick();
    
    // Shows the stick figure.
    void show();

    // The offset.
    int offSet;
    
    // Its animation status.
    int status;
    
    // The red stick figures health.
    void Health_Status();
    
    // The 'AI' System
    int EnemyAI();
};

RedStick::RedStick()
{ 
    // Initialize movement variables.
    offSet = 242;
    red_velocity = 0;
    
    // Initialize animation variables.
    frame = 0; 
    red_punchframe = 0;
    status = STICK_LEFT;
}

void RedStick::Health_Status()
{
     if( Red_Health <= 100 )
     {
         apply_surface( 216, 3, Full, screen, NULL );
     }
     if( Red_Health <= 99 )
     {
         apply_surface( 216, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 98 )
     {
         apply_surface( 217, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 97 )
     {
         apply_surface( 218, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 96 )
     {
         apply_surface( 219, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 95 )
     {
         apply_surface( 220, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 94 )
     {
         apply_surface( 221, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 93 )
     {
         apply_surface( 222, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 92 )
     {
         apply_surface( 223, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 91 )
     {
         apply_surface( 224, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 90 )
     {
         apply_surface( 225, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 89 )
     {
         apply_surface( 226, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 88 )
     {
         apply_surface( 227, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 87 )
     {
         apply_surface( 228, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 86 )
     {
         apply_surface( 229, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 85 )
     {
         apply_surface( 230, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 84 )
     {
         apply_surface( 231, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 83 )
     {
         apply_surface( 232, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 82 )
     {
         apply_surface( 233, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 81 )
     {
         apply_surface( 234, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 80 )
     {
         apply_surface( 235, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 79 )
     {
         apply_surface( 236, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 78 )
     {
         apply_surface( 237, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 77 )
     {
         apply_surface( 238, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 76 )
     {
         apply_surface( 239, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 75 )
     {
         apply_surface( 240, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 74 )
     {
         apply_surface( 241, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 73 )
     {
         apply_surface( 242, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 72 )
     {
         apply_surface( 243, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 71 )
     {
         apply_surface( 244, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 70 )
     {
         apply_surface( 245, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 69 )
     {
         apply_surface( 246, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 68 )
     {
         apply_surface( 247, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 67 )
     {
         apply_surface( 248, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 66 )
     {
         apply_surface( 249, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 65 )
     {
         apply_surface( 250, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 64 )
     {
         apply_surface( 251, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 63 )
     {
         apply_surface( 252, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 62 )
     {
         apply_surface( 253, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 61 )
     {
         apply_surface( 254, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 60 )
     {
         apply_surface( 255, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 59 )
     {
         apply_surface( 256, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 58 )
     {
         apply_surface( 257, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 57 )
     {
         apply_surface( 258, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 56 )
     {
         apply_surface( 259, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 55 )
     {
         apply_surface( 260, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 54 )
     {
         apply_surface( 261, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 53 )
     {
         apply_surface( 262, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 52 )
     {
         apply_surface( 263, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 51 )
     {
         apply_surface( 264, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 50 )
     {
         apply_surface( 265, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 49 )
     {
         apply_surface( 266, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 48 )
     {
         apply_surface( 267, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 47 )
     {
         apply_surface( 268, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 46 )
     {
         apply_surface( 269, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 45 )
     {
         apply_surface( 270, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 44 )
     {
         apply_surface( 271, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 43 )
     {
         apply_surface( 272, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 42 )
     {
         apply_surface( 273, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 41 )
     {
         apply_surface( 274, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 40 )
     {
         apply_surface( 275, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 39 )
     {
         apply_surface( 276, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 38 )
     {
         apply_surface( 277, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 37 )
     {
         apply_surface( 278, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 36 )
     {
         apply_surface( 279, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 35 )
     {
         apply_surface( 280, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 34 )
     {
         apply_surface( 281, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 33 )
     {
         apply_surface( 282, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 32 )
     {
         apply_surface( 283, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 31 )
     {
         apply_surface( 284, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 30 )
     {
         apply_surface( 285, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 29 )
     {
         apply_surface( 286, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 28 )
     {
         apply_surface( 287, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 27 )
     {
         apply_surface( 288, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 26 )
     {
         apply_surface( 289, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 25 )
     {
         apply_surface( 290, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 24 )
     {
         apply_surface( 291, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 23 )
     {
         apply_surface( 292, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 22 )
     {
         apply_surface( 293, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 21 )
     {
         apply_surface( 294, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 20 )
     {
         apply_surface( 295, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 19 )
     {
         apply_surface( 296, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 18 )
     {
         apply_surface( 297, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 17 )
     {
         apply_surface( 298, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 16 )
     {
         apply_surface( 299, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 15 )
     {
         apply_surface( 300, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 14 )
     {
         apply_surface( 301, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 13 )
     {
         apply_surface( 302, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 12 )
     {
         apply_surface( 303, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 11 )
     {
         apply_surface( 304, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 10 )
     {
         apply_surface( 305, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 9 )
     {
         apply_surface( 306, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 8 )
     {
         apply_surface( 307, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 7 )
     {
         apply_surface( 308, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 6 )
     {
         apply_surface( 309, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 5 )
     {
         apply_surface( 310, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 4 )
     {
         apply_surface( 311, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 3 )
     {
         apply_surface( 312, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 2 )
     {
         apply_surface( 313, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 1 )
     {
         apply_surface( 314, 3, One_Bar, screen, NULL );
     }
     if( Red_Health <= 0 )
     {
         apply_surface( 315, 3, One_Bar, screen, NULL );
         b_Win = true;
     }
}

void RedStick::show()
{
     bool red_face_left = true;
     bool red_face_right = false;
     
     red_box.x += red_velocity;
     red_box.y = SCREEN_HEIGHT - STICK_HEIGHT;
     red_box.w = STICK_WIDTH;
     red_box.h = STICK_HEIGHT;
     
     // Move.
     offSet += red_velocity;
    // Keep the figure in bounds.
    if( ( offSet < 0 ) || ( offSet + STICK_WIDTH > SCREEN_WIDTH ) )
    {
        offSet -= red_velocity;
        red_box.x -=red_velocity;   
    }
    
    if((red_box.x < 0 ) || ( red_box.x + STICK_WIDTH > SCREEN_WIDTH ))
    {
        red_box.x -= red_velocity;
    }
    
    // If the player is moving left...
    if( red_velocity < 0 )
    {
        red_face_left = false;
        red_face_left = true;
        if( red_punch == false )
        {
            // Set the animation to left.
            status = STICK_LEFT;
        
            // Move to the next frame in the animation.
            frame++;
        }
        
        if( red_punch == true)
        {
            // Set the animation to be punching left.
            status = STICK_PUNCH_L;
            
            // Move to the next frame in the animation.
            red_punchframe++;
        }
    }
    // If the player is moving right...
    else if( red_velocity > 0 )
    {
        red_face_left = true;
        red_face_left = false;
        if( red_punch == false )
        {
            // Set the animation to left.
            status = STICK_RIGHT;
        
            // Move to the next frame in the animation.
            frame++;
        }
        
        if( red_punch == true)
        {
            // Set the animation to be punching left.
            status = STICK_PUNCH_R;
            
            // Move to the next frame in the animation.
            red_punchframe++;
        }
    }
    
    else if( red_velocity == 0 )
    {
         // While idle, reset the walk animation.
         frame = 0;
         
         // If the user pressed the punch button...
         if( red_punch == true )
         {
             // While the stick figure is facing right, set the status of the punch
             // animation to the right, too.
             if( face_right == true )
             {
                  status = STICK_PUNCH_R;
             }
             // Replace 'right' with 'left'.
             else if(face_right == false )
             {
                  status = STICK_PUNCH_L;
             }
             // Increase the punch counter for the animation.
             red_punchframe++;
         }
    }

    if(check_collision(red_box, blue_box))
    {
                 if(red_punchframe == 8)
                 {
                               srand( time( 0 ) ); 
                               int randomNum = rand();
    
                               int HealthDown = (randomNum % 10) + 1;
                               Blue_Health -= HealthDown;
                 }

    }
    
    // Loop the animation.
    if( frame >= 12 )
    {
        frame = 0;
    }
    
    if( red_punchframe >= 14 )
    {
         red_punchframe = 0;
         red_punch = false;
    }
    
    // Show the stick figure.
    if( status == STICK_RIGHT )
    {
        apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, redguy, screen, &ClipsRight[ frame ] );
    }
    else if( status == STICK_LEFT )
    {
        apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, redguy, screen, &ClipsLeft[ frame ] );
    }
    else if( status == STICK_PUNCH_R )
    {
         apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, redguy, screen, &ClipsPunchR[ red_punchframe ] );
    }
    else if( status == STICK_PUNCH_L )
    {
         apply_surface( offSet, SCREEN_HEIGHT - STICK_HEIGHT, redguy, screen, &ClipsPunchL[ red_punchframe ] );
    }
}

void set_clips()
{
// Clip the sprites...
//Walking sprite sheetBlue sprite sheet////////////////////////////////////
//Right////////////////////////////////////////////////////////////////////////////////////////
    ClipsRight[ 0 ].x = 0;
    ClipsRight[ 0 ].y = 0;
    ClipsRight[ 0 ].w = STICK_WIDTH;
    ClipsRight[ 0 ].h = STICK_HEIGHT;
    
    ClipsRight[ 1 ].x = STICK_WIDTH;
    ClipsRight[ 1 ].y = 0;
    ClipsRight[ 1 ].w = STICK_WIDTH;
    ClipsRight[ 1 ].h = STICK_HEIGHT;
    
    ClipsRight[ 2 ].x = STICK_WIDTH * 2;
    ClipsRight[ 2 ].y = 0;
    ClipsRight[ 2 ].w = STICK_WIDTH;
    ClipsRight[ 2 ].h = STICK_HEIGHT;
    
    ClipsRight[ 3 ].x = STICK_WIDTH * 3;
    ClipsRight[ 3 ].y = 0;
    ClipsRight[ 3 ].w = STICK_WIDTH;
    ClipsRight[ 3 ].h = STICK_HEIGHT;

    ClipsRight[ 4 ].x = STICK_WIDTH * 4;
    ClipsRight[ 4 ].y = 0;
    ClipsRight[ 4 ].w = STICK_WIDTH;
    ClipsRight[ 4 ].h = STICK_HEIGHT;

    ClipsRight[ 5 ].x = STICK_WIDTH * 5;
    ClipsRight[ 5 ].y = 0;
    ClipsRight[ 5 ].w = STICK_WIDTH;
    ClipsRight[ 5 ].h = STICK_HEIGHT;

    ClipsRight[ 6 ].x = STICK_WIDTH * 6;
    ClipsRight[ 6 ].y = 0;
    ClipsRight[ 6 ].w = STICK_WIDTH;
    ClipsRight[ 6 ].h = STICK_HEIGHT;

    ClipsRight[ 7 ].x = STICK_WIDTH * 7;
    ClipsRight[ 7 ].y = 0;
    ClipsRight[ 7 ].w = STICK_WIDTH;
    ClipsRight[ 7 ].h = STICK_HEIGHT;
    
    ClipsRight[ 8 ].x = STICK_WIDTH * 8;
    ClipsRight[ 8 ].y = 0;
    ClipsRight[ 8 ].w = STICK_WIDTH;
    ClipsRight[ 8 ].h = STICK_HEIGHT;
    
    ClipsRight[ 9 ].x = STICK_WIDTH * 9;
    ClipsRight[ 9 ].y = 0;
    ClipsRight[ 9 ].w = STICK_WIDTH;
    ClipsRight[ 9 ].h = STICK_HEIGHT;
    
    ClipsRight[ 10 ].x = STICK_WIDTH * 10;
    ClipsRight[ 10 ].y = 0;
    ClipsRight[ 10 ].w = STICK_WIDTH;
    ClipsRight[ 10 ].h = STICK_HEIGHT;
    
    ClipsRight[ 11 ].x = STICK_WIDTH * 11;
    ClipsRight[ 11 ].y = 0;
    ClipsRight[ 11 ].w = STICK_WIDTH;
    ClipsRight[ 11 ].h = STICK_HEIGHT;
    
//Left/////////////////////////////////////////////////////////////////////
    
    ClipsLeft[ 0 ].x = 0;
    ClipsLeft[ 0 ].y = STICK_HEIGHT;
    ClipsLeft[ 0 ].w = STICK_WIDTH;
    ClipsLeft[ 0 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 1 ].x = STICK_WIDTH;
    ClipsLeft[ 1 ].y = STICK_HEIGHT;
    ClipsLeft[ 1 ].w = STICK_WIDTH;
    ClipsLeft[ 1 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 2 ].x = STICK_WIDTH * 2;
    ClipsLeft[ 2 ].y = STICK_HEIGHT;
    ClipsLeft[ 2 ].w = STICK_WIDTH;
    ClipsLeft[ 2 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 3 ].x = STICK_WIDTH * 3;
    ClipsLeft[ 3 ].y = STICK_HEIGHT;
    ClipsLeft[ 3 ].w = STICK_WIDTH;
    ClipsLeft[ 3 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 4 ].x = STICK_WIDTH * 4;
    ClipsLeft[ 4 ].y = STICK_HEIGHT;
    ClipsLeft[ 4 ].w = STICK_WIDTH;
    ClipsLeft[ 4 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 5 ].x = STICK_WIDTH * 5;
    ClipsLeft[ 5 ].y = STICK_HEIGHT;
    ClipsLeft[ 5 ].w = STICK_WIDTH;
    ClipsLeft[ 5 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 6 ].x = STICK_WIDTH * 6;
    ClipsLeft[ 6 ].y = STICK_HEIGHT;
    ClipsLeft[ 6 ].w = STICK_WIDTH;
    ClipsLeft[ 6 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 7 ].x = STICK_WIDTH * 7;
    ClipsLeft[ 7 ].y = STICK_HEIGHT;
    ClipsLeft[ 7 ].w = STICK_WIDTH;
    ClipsLeft[ 7 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 8 ].x = STICK_WIDTH * 8;
    ClipsLeft[ 8 ].y = STICK_HEIGHT;
    ClipsLeft[ 8 ].w = STICK_WIDTH;
    ClipsLeft[ 8 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 9 ].x = STICK_WIDTH * 9;
    ClipsLeft[ 9 ].y = STICK_HEIGHT;
    ClipsLeft[ 9 ].w = STICK_WIDTH;
    ClipsLeft[ 9 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 10 ].x = STICK_WIDTH * 10;
    ClipsLeft[ 10 ].y = STICK_HEIGHT;
    ClipsLeft[ 10 ].w = STICK_WIDTH;
    ClipsLeft[ 10 ].h = STICK_HEIGHT;
    
    ClipsLeft[ 11 ].x = STICK_WIDTH * 11;
    ClipsLeft[ 11 ].y = STICK_HEIGHT;
    ClipsLeft[ 11 ].w = STICK_WIDTH;
    ClipsLeft[ 11 ].h = STICK_HEIGHT;

//Punch RightLeft/right//////////////////////////////////////////////////////////////

    ClipsPunchR[ 0 ].x = 0;
    ClipsPunchR[ 0 ].y = 0;
    ClipsPunchR[ 0 ].w = STICK_WIDTH;
    ClipsPunchR[ 0 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 1 ].x = 0;
    ClipsPunchR[ 1 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 1 ].w = STICK_WIDTH;
    ClipsPunchR[ 1 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 2 ].x = STICK_WIDTH;
    ClipsPunchR[ 2 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 2 ].w = STICK_WIDTH;
    ClipsPunchR[ 2 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 3 ].x = STICK_WIDTH * 2;
    ClipsPunchR[ 3 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 3 ].w = STICK_WIDTH;
    ClipsPunchR[ 3 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 4 ].x = STICK_WIDTH * 3;
    ClipsPunchR[ 4 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 4 ].w = STICK_WIDTH;
    ClipsPunchR[ 4 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 5 ].x = STICK_WIDTH * 4;
    ClipsPunchR[ 5 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 5 ].w = STICK_WIDTH;
    ClipsPunchR[ 5 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 6 ].x = STICK_WIDTH * 5;
    ClipsPunchR[ 6 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 6 ].w = STICK_WIDTH;
    ClipsPunchR[ 6 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 7 ].x = STICK_WIDTH * 6;
    ClipsPunchR[ 7 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 7 ].w = STICK_WIDTH;
    ClipsPunchR[ 7 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 8 ].x = STICK_WIDTH * 5;
    ClipsPunchR[ 8 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 8 ].w = STICK_WIDTH;
    ClipsPunchR[ 8 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 9 ].x = STICK_WIDTH * 4;
    ClipsPunchR[ 9 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 9 ].w = STICK_WIDTH;
    ClipsPunchR[ 9 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 10 ].x = STICK_WIDTH * 3;
    ClipsPunchR[ 10 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 10 ].w = STICK_WIDTH;
    ClipsPunchR[ 10 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 11 ].x = STICK_WIDTH * 2;
    ClipsPunchR[ 11 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 11 ].w = STICK_WIDTH;
    ClipsPunchR[ 11 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 12 ].x = STICK_WIDTH;
    ClipsPunchR[ 12 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 12 ].w = STICK_WIDTH;
    ClipsPunchR[ 12 ].h = STICK_HEIGHT;
    
    ClipsPunchR[ 13 ].x = 0;
    ClipsPunchR[ 13 ].y = STICK_HEIGHT * 2;
    ClipsPunchR[ 13 ].w = STICK_WIDTH;
    ClipsPunchR[ 13 ].h = STICK_HEIGHT;
    
//Punch Left/right/////Blue punch right/////////////////////////////////////////////////////////

    ClipsPunchL[ 0 ].x = 0;
    ClipsPunchL[ 0 ].y = STICK_HEIGHT;
    ClipsPunchL[ 0 ].w = STICK_WIDTH;
    ClipsPunchL[ 0 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 1 ].x = STICK_WIDTH * 6;
    ClipsPunchL[ 1 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 1 ].w = STICK_WIDTH;
    ClipsPunchL[ 1 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 2 ].x = STICK_WIDTH * 5;
    ClipsPunchL[ 2 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 2 ].w = STICK_WIDTH;
    ClipsPunchL[ 2 ].h = STICK_HEIGHT;

    ClipsPunchL[ 3 ].x = STICK_WIDTH * 4;
    ClipsPunchL[ 3 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 3 ].w = STICK_WIDTH;
    ClipsPunchL[ 3 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 4 ].x = STICK_WIDTH * 3;
    ClipsPunchL[ 4 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 4 ].w = STICK_WIDTH;
    ClipsPunchL[ 4 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 5 ].x = STICK_WIDTH * 2;
    ClipsPunchL[ 5 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 5 ].w = STICK_WIDTH;
    ClipsPunchL[ 5 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 6 ].x = STICK_WIDTH;
    ClipsPunchL[ 6 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 6 ].w = STICK_WIDTH;
    ClipsPunchL[ 6 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 7 ].x = 0;
    ClipsPunchL[ 7 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 7 ].w = STICK_WIDTH;
    ClipsPunchL[ 7 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 8 ].x = STICK_WIDTH;
    ClipsPunchL[ 8 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 8 ].w = STICK_WIDTH;
    ClipsPunchL[ 8 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 9 ].x = STICK_WIDTH * 2;
    ClipsPunchL[ 9 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 9 ].w = STICK_WIDTH;
    ClipsPunchL[ 9 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 10 ].x = STICK_WIDTH * 3;
    ClipsPunchL[ 10 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 10 ].w = STICK_WIDTH;
    ClipsPunchL[ 10 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 11 ].x = STICK_WIDTH * 4;
    ClipsPunchL[ 11 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 11 ].w = STICK_WIDTH;
    ClipsPunchL[ 11 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 12 ].x = STICK_WIDTH * 5;
    ClipsPunchL[ 12 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 12 ].w = STICK_WIDTH;
    ClipsPunchL[ 12 ].h = STICK_HEIGHT;
    
    ClipsPunchL[ 13 ].x = STICK_WIDTH * 6;
    ClipsPunchL[ 13 ].y = STICK_HEIGHT * 3;
    ClipsPunchL[ 13 ].w = STICK_WIDTH;
    ClipsPunchL[ 13 ].h = STICK_HEIGHT;
}

int RedStick::EnemyAI( )
{
    srand( time( 0 ) );
    
    int randomNum = rand( );
    
    int Action = (randomNum % 3) + 1;
    if( check_collision( red_box, blue_box ) )
    {
        if( Action == 1 )
        {
            // Do nothing.
        }
        else if( Action == 2 )
        {
            if( red_punch == false )
            {
                red_punch = true;
            }
        }
        else if( Action == 3 )
        {
             // Do nothing.
        }
    }
    return 0;
}

// Make the stick figure.
BlueStick bluemade;
RedStick redmade;

void Winner()
{    
     apply_surface( 84, 5, s_WinText, screen, NULL );
}

void Looser()
{
     apply_surface( 84, 5, s_LoseText, screen, NULL );
}

void Menu()
{
     apply_surface( 0, 0, menu, screen, NULL );
     
     if(SDL_GetTicks() >= 9000)
     {
           if(event.type == SDL_KEYDOWN)
           {
           // Go to Main Loop
           switch(event.key.keysym.sym)
           {
                case SDLK_RETURN:
                b_MainLoop = true;
                break;
           }
           }
        if( event.type == SDL_JOYBUTTONDOWN )
        {
            switch( event.jbutton.button )
            {
                case GP2X_START:
                b_MainLoop = true;
                break;
            }
        }
     }
}

void Main_Loop()
{     
     // Fill the screen black.
     SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
     apply_surface( 0, 0, background, screen, NULL );

     redmade.show();
     bluemade.show();
     bluemade.Health_Status();
     redmade.Health_Status();
     redmade.EnemyAI();
     if(b_Win == false && b_Loose == false)
     {
     if(bluemade.offSet < redmade.offSet)
     {
           red_velocity--;           
     }
     else if(bluemade.offSet > redmade.offSet)
     {
          red_velocity++;
     }
     }          
}

void Reset()
{
     // Reset the health status.
     Blue_Health = 100;
     Red_Health = 100;
     
     // Reset the stick's variables.
     bluemade.offSet = 0;
     blue_box.x = 0;
     bluemade.status = STICK_RIGHT;
     blue_velocity = 0;
     
     redmade.offSet = 242;
     red_box.x = 242;
     redmade.status = STICK_LEFT;
     red_velocity = 0;

}

void Intro()
{
     if(SDL_GetTicks() >= 2000)
	 {
         apply_surface(0, 0, introInt, screen, NULL);
     }
        
     if(SDL_GetTicks() >= 4500)
     {
         SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0x00, 0x00, 0x00 ) );
     }
     
     if(SDL_GetTicks() >= 7500)
     {
         delete introInt;
         b_menu = true;
     }
}
