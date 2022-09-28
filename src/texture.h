#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
    public:
        Texture();
        bool load_texture_from_file(std::string path, SDL_Renderer* renderer);
        void render(int x, int y, SDL_Renderer* renderer);
        void free();

    private:
        int m_width{0};
        int m_height{0};

        SDL_Texture* m_texture{NULL};
};

#endif