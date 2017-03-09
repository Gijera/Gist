#include "texture.h"
#include "global.h"

Texture::Texture()
{
    texture = NULL;
    tWidth = 0;
    tHeight = 0;
}

Texture::~Texture()
{
    free();
}

bool Texture::loadFromFile(std::string path)
{
    free();
    SDL_Texture *newTexture = NULL;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }else{
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }else{
            tWidth = loadedSurface->w;
            tHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    texture = newTexture;
    return texture != NULL;
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    free();

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
    if(textSurface == NULL){
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }else{
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(texture == NULL){
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }else{
            tWidth = textSurface->w;
            tHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return texture != NULL;
}

void Texture::free()
{
    if(texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
        tWidth = 0;
        tHeight = 0;
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    SDL_SetTextureColorMod( texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
    SDL_SetTextureBlendMode( texture, blending );
}
		
void Texture::setAlpha( Uint8 alpha )
{
    SDL_SetTextureAlphaMod( texture, alpha );
}

void Texture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, tWidth, tHeight};
    if(clip != NULL){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}

int Texture::getWidth()
{
    return tWidth;
}

int Texture::getHeight()
{
    return tHeight;
}
