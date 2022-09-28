#include "texture.h"

Texture::Texture()
{
    m_width = 0;
    m_height = 0;
    m_texture = NULL;
}

bool Texture::load_texture_from_file(std::string path, SDL_Renderer* renderer)
{
    // Get rid of pre-existing texture
    free();

    SDL_Surface* tmp_surface{IMG_Load(path.c_str())};
    if(tmp_surface == NULL)
    {
        printf("Failed to load image '%s', SDL image Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }

    m_texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    if(m_texture == NULL)
    {
        printf("Failed to create texture from surface, SDL error: %s\n", SDL_GetError());
        SDL_FreeSurface(tmp_surface);
        return false;
    }

    m_width = tmp_surface->w;
    m_height = tmp_surface->h;
    SDL_FreeSurface(tmp_surface);

    return true;
}

void Texture::render(int x, int y, SDL_Renderer* renderer)
{
    SDL_Rect tmp_dest_rect{x, y, m_width, m_height};
    SDL_RenderCopyEx(renderer, m_texture, NULL, &tmp_dest_rect, 0.0, NULL, SDL_FLIP_NONE);
}

void Texture::free()
{
    if(m_texture != NULL)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = NULL;

        m_width = 0;
        m_height = 0;
    }
}