#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
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

        window = SDL_CreateWindow( "word", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }

                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

                if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
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

    font = TTF_OpenFont("./ttf/word.ttf", 30);
    if( font == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }

    music = Mix_LoadMUS("./music/background.wav");
    if(music == NULL){
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    down = Mix_LoadWAV("./music/down.wav");
    if(down == NULL){
        printf( "Failed to load down sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    wipe = Mix_LoadWAV("./music/wipe.wav");
    if(wipe == NULL){
        printf( "Failed to load wipe sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    error = Mix_LoadWAV("./music/error.wav");
    if(error == NULL){
        printf( "Failed to load error sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }
        
    if(!interfaceTexture.loadFromFile("./image/interface.png")){
        printf("Failed to load image interface.png, error: %s", SDL_GetError());
        success = false;
    }

    if(!settingTexture.loadFromFile("./image/setting.png")){
        printf("Failed to load image setting.png, error: %s", SDL_GetError());
        success = false;
    }

    if(!settingButtonTexture.loadFromFile("./image/setbutton.png")){
        printf("Failed to load image setbutton.png, error: %s", SDL_GetError());
        success = false;
    }

    if(!editTexture.loadFromFile("./image/edit.png")){
        printf("Failed to load image edit.png, error: %s", SDL_GetError());
        success = false;
    }

    if(!editDeleteTexture.loadFromFile("./image/editdelete.png")){
        printf("Failed to load image editdelete.png, error: %s", SDL_GetError());
        success = false;
    }

    if(!gameTexture.loadFromFile("./image/begin.png")){
        printf("Failed to load image begin.png, error: %s", SDL_GetError());
        success = false;
    }

    if(!gameOverTexture.loadFromFile("./image/gameover.png")){
        printf("Failed to load image begin.png, error: %s", SDL_GetError());
        success = false;
    }
    if( !alphaTexture[A].loadFromFile("./image/A.png") ||
        !alphaTexture[B].loadFromFile("./image/B.png") ||
        !alphaTexture[C].loadFromFile("./image/C.png") ||
        !alphaTexture[D].loadFromFile("./image/D.png") ||
        !alphaTexture[E].loadFromFile("./image/E.png") ||
        !alphaTexture[F].loadFromFile("./image/F.png") ||
        !alphaTexture[G].loadFromFile("./image/G.png") ||
        !alphaTexture[H].loadFromFile("./image/H.png") ||
        !alphaTexture[I].loadFromFile("./image/I.png") ||
        !alphaTexture[J].loadFromFile("./image/J.png") ||
        !alphaTexture[K].loadFromFile("./image/K.png") ||
        !alphaTexture[L].loadFromFile("./image/L.png") ||
        !alphaTexture[M].loadFromFile("./image/M.png") ||
        !alphaTexture[N].loadFromFile("./image/N.png") ||
        !alphaTexture[O].loadFromFile("./image/O.png") ||
        !alphaTexture[P].loadFromFile("./image/P.png") ||
        !alphaTexture[Q].loadFromFile("./image/Q.png") ||
        !alphaTexture[R].loadFromFile("./image/R.png") ||
        !alphaTexture[S].loadFromFile("./image/S.png") ||
        !alphaTexture[T].loadFromFile("./image/T.png") ||
        !alphaTexture[U].loadFromFile("./image/U.png") ||
        !alphaTexture[V].loadFromFile("./image/V.png") ||
        !alphaTexture[W].loadFromFile("./image/W.png") ||
        !alphaTexture[X].loadFromFile("./image/X.png") ||
        !alphaTexture[Y].loadFromFile("./image/Y.png") ||
        !alphaTexture[Z].loadFromFile("./image/Z.png") ){
        printf("Failed to load alpha image,error %s", SDL_GetError());
        success = false;
    }
    
    if( !alphaCTexture[A].loadFromFile("./image/AC.png") ||
        !alphaCTexture[B].loadFromFile("./image/BC.png") ||
        !alphaCTexture[C].loadFromFile("./image/CC.png") ||
        !alphaCTexture[D].loadFromFile("./image/DC.png") ||
        !alphaCTexture[E].loadFromFile("./image/EC.png") ||
        !alphaCTexture[F].loadFromFile("./image/FC.png") ||
        !alphaCTexture[G].loadFromFile("./image/GC.png") ||
        !alphaCTexture[H].loadFromFile("./image/HC.png") ||
        !alphaCTexture[I].loadFromFile("./image/IC.png") ||
        !alphaCTexture[J].loadFromFile("./image/JC.png") ||
        !alphaCTexture[K].loadFromFile("./image/KC.png") ||
        !alphaCTexture[L].loadFromFile("./image/LC.png") ||
        !alphaCTexture[M].loadFromFile("./image/MC.png") ||
        !alphaCTexture[N].loadFromFile("./image/NC.png") ||
        !alphaCTexture[O].loadFromFile("./image/OC.png") ||
        !alphaCTexture[P].loadFromFile("./image/PC.png") ||
        !alphaCTexture[Q].loadFromFile("./image/QC.png") ||
        !alphaCTexture[R].loadFromFile("./image/RC.png") ||
        !alphaCTexture[S].loadFromFile("./image/SC.png") ||
        !alphaCTexture[T].loadFromFile("./image/TC.png") ||
        !alphaCTexture[U].loadFromFile("./image/UC.png") ||
        !alphaCTexture[V].loadFromFile("./image/VC.png") ||
        !alphaCTexture[W].loadFromFile("./image/WC.png") ||
        !alphaCTexture[X].loadFromFile("./image/XC.png") ||
        !alphaCTexture[Y].loadFromFile("./image/YC.png") ||
        !alphaCTexture[Z].loadFromFile("./image/ZC.png") ){
        printf("Failed to load alphac image,error %s", SDL_GetError());
        success = false;
    }
    //create word.txt
    SDL_RWops *file = SDL_RWFromFile("./file/word.txt", "r");
    if(file == NULL){
        SDL_RWops *file = SDL_RWFromFile("./file/word.txt", "w");
        if(file == NULL){
            printf("Error: Unable to create file!SDL Error: %s", SDL_GetError());
            success = false;
        }else{
            SDL_RWclose(file);
        }
    }else{
        readFileToVector();
        SDL_RWclose(file);
    }
    return success;
}

void close()
{
    writeVectorToFile();
    
    mainTexture.free();
    interfaceTexture.free();
    settingTexture.free();
    settingButtonTexture.free();
    editTexture.free();
    editAddTexture.free();
    editFindTexture.free();
    editCountTexture.free();
    editInfoTexture.free();
    editDeleteTexture.free();
    gameTexture.free();
    gameScoreTexture.free();
    gameWordTexture.free();
    
    for(int i = 0; i < ALPHA; i++){
        alphaTexture[i].free();
        alphaCTexture[i].free();
    }

    TTF_CloseFont(font);
    font = NULL;

    Mix_FreeMusic(music);
    music = NULL;
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    Mix_Quit();
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
            quit = false;
            SDL_Event e;

            Mix_PlayMusic(music, -1);
            
            SDL_StartTextInput();
            
            while(!quit){
                while(SDL_PollEvent(&e) != 0){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }

                    switch(windowState){
                    case BEGIN:
                        game.handleEvent(&e);
                        break;
                    case INTERFACE:
                        interface.handleEvent(&e);
                        break;
                    case SETTING:
                        setting.handleEvent(&e);
                        break;
                    case EDIT:
                        edit.handleEvent(&e);
                        break;
                    case EXIT:
                        quit = true;
                        break;
                    default:
                        break;
                    }
                }

                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(renderer);

                switch(windowState){
                case BEGIN:
                    game.render();
                    break;
                case INTERFACE:
                    interface.render();
                    break;
                case SETTING:
                    setting.render();
                    break;
                case EDIT:
                    edit.render();
                    break;
                case GAMEOVER:
                    gameOverTexture.render(0, 0);
                    break;
                case EXIT:
                    quit = true;
                    break;
                default:
                    break;
                }

                SDL_RenderPresent(renderer);
            }
            
            SDL_StopTextInput();
        }
    }
    close();
    
    return 0;
}
