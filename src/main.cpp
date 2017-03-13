#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "global.h"

bool init();
bool loadMedia();
void close();

bool init()
{
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }else{
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ){
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        window = SDL_CreateWindow( "SpaceWar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }else{
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( renderer == NULL ){
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }else{
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ){
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( TTF_Init() == -1 ){
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
                
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;

    font = TTF_OpenFont("../ttf/game.ttf", 50);
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    if(!mainTexture.loadFromFile("../image/background.png")){
        printf("Failed to load background.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!heroTexture.loadFromFile("../image/hero1.png")){
        printf("Failed to load hero.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!enemy1Texture.loadFromFile("../image/enemy1.png")){
        printf("Failed to load enemy1.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!enemy2Texture.loadFromFile("../image/enemy2.png")){
        printf("Failed to load enemy2.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    
    if(!enemy3Texture.loadFromFile("../image/enemy3.png")){
        printf("Failed to load enemy3.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    
    if(!heroBulletTexture.loadFromFile("../image/bullet2.png")){
        printf("Failed to load bullet2.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!enemyBulletTexture.loadFromFile("../image/bullet1.png")){
        printf("Failed to load bullet1.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!bombBulletTexture.loadFromFile("../image/bomb.png")){
        printf("Failed to load bomb.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!ufo1Texture.loadFromFile("../image/ufo1.png")){
        printf("Failed to load ufo1.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!ufo2Texture.loadFromFile("../image/ufo2.png")){
        printf("Failed to load ufo2.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!pauseTexture.loadFromFile("../image/pause.png")){
        printf("Failed to load pause.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!resumeTexture.loadFromFile("../image/resume.png")){
        printf("Failed to load resume.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    if(!restartTexture.loadFromFile("../image/restart.png")){
        printf("Failed to load restart.png! SDL Error: %s\n", SDL_GetError());
        success = false;   
    }
    return success;
}

void close()
{
    mainTexture.free();
    heroTexture.free();

    enemy1Texture.free();

    enemy2Texture.free();

    enemy3Texture.free();

    heroBulletTexture.free();
    enemyBulletTexture.free();
    bombBulletTexture.free();
    ufo1Texture.free();
    ufo2Texture.free();
    pauseTexture.free();
    resumeTexture.free();
    scoreTexture.free();
    restartTexture.free();

    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[])
{
    if(!init()){
        printf( "Failed to initialize!\n" );
    }else{
        if(!loadMedia()){
            printf( "Failed to load media!\n" );
        }else{
            bool quit = false;
            SDL_Event e;

            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }

                    scheduler.handleEvent(e);
                }

                scheduler.move();
                
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);
                
                scheduler.render();
                
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    
    return 0;
}
