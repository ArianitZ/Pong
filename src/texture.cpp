#include "texture.h"

Texture::Texture()
{
    m_width = 0;
    m_height = 0;
    m_texture = NULL;
}


bool Texture::load_texture_from_font(std::string text, SDL_Renderer* renderer, TTF_Font* font)
{
    // Get rid of pre-exisiting texutre
    free();

    SDL_Surface* tmp_surface{TTF_RenderText_Solid(font, text.c_str(), {0x00, 0x00, 0x00})};
    if(tmp_surface == NULL)
    {
        printf("Failed to load font '%s', SDL ttf error: %s\n", text.c_str(), TTF_GetError());
        return false;
    }

    return load_texture_from_surface(renderer, tmp_surface);
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

    return load_texture_from_surface(renderer, tmp_surface);
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

int Texture::get_width()
{
    return m_width;
}

int Texture::get_height()
{
    return m_height;
}

bool Texture::load_texture_from_surface(SDL_Renderer* renderer, SDL_Surface* surface)
{
    m_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(m_texture == NULL)
    {
        printf("Failed to create texture from surface, SDL error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return false;
    }

    m_width = surface->w;
    m_height = surface->h;
    SDL_FreeSurface(surface);

    return true;
}