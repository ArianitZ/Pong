#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <cstdio>
#include "renderable.h"

class Window
{
    public:
        Window(int width, int m_height, std::string title);

        bool init();
        void free();

        void render_present();
        void render_clear();
        void render(IRenderable &rendering_object);

        SDL_Renderer* get_renderer();

    private:
        int m_width{};
        int m_height{};
        std::string m_title{};

        SDL_Window* m_window{NULL};
        SDL_Renderer* m_renderer{NULL};
};

#endif