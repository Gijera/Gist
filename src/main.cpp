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

    font = TTF_OpenFont("../ttf/game.ttf", 30);
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    if(!mainTexture.loadFromFile("../image/background.png")){
        printf("Failed to load background.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!heroTexture[0].loadFromFile("../image/hero1.png") || !heroTexture[1].loadFromFile("../image/hero2.png")){
        printf("Failed to load hero.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!heroBlowUpTexture[0].loadFromFile("../image/hero_blowup_n1.png") || !heroBlowUpTexture[1].loadFromFile("../image/hero_blowup_n2.png") || !heroBlowUpTexture[2].loadFromFile("../image/hero_blowup_n3.png") || !heroBlowUpTexture[3].loadFromFile("../image/hero_blowup_n4.png")){
        printf("Failed to laod hero_blowup.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!enemy1Texture.loadFromFile("../image/enemy1.png")){
        printf("Failed to load enemy1.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    
    if(!enemy1DownTexture[0].loadFromFile("../image/enemy1_down1.png") || !enemy1DownTexture[1].loadFromFile("../image/enemy1_down2.png") || !enemy1DownTexture[2].loadFromFile("../image/enemy1_down3.png") || !enemy1DownTexture[3].loadFromFile("../image/enemy1_down4.png")){
        printf("Failed to load enemy1_down.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!enemy2Texture.loadFromFile("../image/enemy2.png")){
        printf("Failed to load enemy2.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    
    if(!enemy2DownTexture[0].loadFromFile("../image/enemy2_down1.png") || !enemy2DownTexture[1].loadFromFile("../image/enemy2_down2.png") || !enemy2DownTexture[2].loadFromFile("../image/enemy2_down3.png") || !enemy2DownTexture[3].loadFromFile("../image/enemy2_down4.png")){
        printf("Failed to load enemy2_down.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if(!enemy3Texture.loadFromFile("../image/enemy3.png")){
        printf("Failed to load enemy3.png! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    
    if(!enemy3DownTexture[0].loadFromFile("../image/enemy3_down1.png") || !enemy3DownTexture[1].loadFromFile("../image/enemy3_down2.png") || !enemy3DownTexture[2].loadFromFile("../image/enemy3_down3.png") || !enemy3DownTexture[3].loadFromFile("../image/enemy3_down4.png") || !enemy3DownTexture[4].loadFromFile("../image/enemy3_down5.png") || !enemy3DownTexture[5].loadFromFile("../image/enemy3_down6.png")){
        printf("Failed to load enemy3_down.png! SDL Error: %s\n", SDL_GetError());
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
    return success;
}

void close()
{
    mainTexture.free();
    for(int i = 0; i < HERO; i++)
        heroTexture[i].free();
    for(int i = 0; i < HEROBLOWUP; i++)
        heroBlowUpTexture[i].free();
    enemy1Texture.free();
    for(int i = 0; i < ENEMY1DOWN; i++)
        enemy1DownTexture[i].free();
    enemy2Texture.free();
    for(int i = 0; i < ENEMY2DOWN; i++)
        enemy2DownTexture[i].free();
    enemy3Texture.free();
    for(int i = 0; i < ENEMY3DOWN; i++)
        enemy3DownTexture[i].free();
    heroBulletTexture.free();
    enemyBulletTexture.free();
    bombBulletTexture.free();
    ufo1Texture.free();
    ufo2Texture.free();
    pauseTexture.free();
    resumeTexture.free();

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
