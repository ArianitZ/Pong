#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Texture
{
    public:
        Texture();
        bool load_texture_from_font(std::string text, SDL_Renderer* renderer, TTF_Font* font);
        bool load_texture_from_file(std::string path, SDL_Renderer* renderer);
        void render(int x, int y, SDL_Renderer* renderer);
        void free();

        int get_width();
        int get_height();

    private:
        int m_width{0};
        int m_height{0};

        SDL_Texture* m_texture{NULL};
        bool load_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface);
};

#endif