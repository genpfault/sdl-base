#include <SDL.h>

int main( int argc, char** argv )
{
    SDL_Init( SDL_INIT_EVERYTHING );

    SDL_Window* window = SDL_CreateWindow(
        "Window",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        800,
        600,
        SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    bool running = true;
    while( running )
    {
        // process events
        SDL_Event ev;
        while( SDL_PollEvent( &ev ) )
        {
            switch( ev.type )
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYUP:
                if( SDL_SCANCODE_ESCAPE == ev.key.keysym.scancode ||
                    SDL_SCANCODE_AC_BACK == ev.key.keysym.scancode )
                {
                    running = false;
                }
                break;

            default:
                break;
            }
        }

        SDL_SetRenderDrawColor( renderer, 255, 255, 206, SDL_ALPHA_OPAQUE );
        SDL_RenderClear( renderer );

        SDL_RenderPresent( renderer );
    }

    SDL_DestroyRenderer( renderer );
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
